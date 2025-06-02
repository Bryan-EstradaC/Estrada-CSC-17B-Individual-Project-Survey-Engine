<?php
require_once("connect.php");

if (!isset($_GET['survey_id'])) {
    echo "Survey not selected.";
    exit;
}

$surveyID = intval($_GET['survey_id']);
$surveyTitle = $connection->query("SELECT Title FROM survey WHERE SurveyID = $surveyID")->fetch_assoc()['Title'];

echo "<h2>Survey: $surveyTitle</h2>";
echo "<form method='POST' action='submit_response.php'>";

$questions = $connection->query("SELECT * FROM question WHERE SurveyID = $surveyID");

while ($q = $questions->fetch_assoc()) {
    echo "<p><strong>{$q['Text']}</strong></p>";
    $qid = $q['QuestionID'];

    if ($q['isMultipleChoice']) {
        $choices = $connection->query("SELECT * FROM choice WHERE QuestionID = $qid");
        while ($c = $choices->fetch_assoc()) {
            echo "<label><input type='radio' name='answers[$qid]' value='{$c['Text']}' required> {$c['Text']}</label><br>";
        }
    } else {
        echo "<input type='text' name='answers[$qid]' required><br>";
    }
}

echo "<input type='hidden' name='survey_id' value='$surveyID'>";
echo "<br><input type='submit' value='Submit Survey'>";
echo "</form>";
?>
