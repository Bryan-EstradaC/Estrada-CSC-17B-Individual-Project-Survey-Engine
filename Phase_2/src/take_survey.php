<?php
require_once("connect.php");

$surveyId = $_GET['survey_id'];

$sql = "SELECT s.Title AS surveyTitle, q.QuestionID, q.Text AS questionText, q.isMultipleChoice,
               c.ChoiceID, c.Text AS choiceText
        FROM survey s
        JOIN question q ON s.SurveyID = q.SurveyID
        LEFT JOIN choice c ON q.QuestionID = c.QuestionID
        WHERE s.SurveyID = ?";
        
$stmt = $connection->prepare($sql);
$stmt->bind_param("i", $surveyId);
$stmt->execute();
$result = $stmt->get_result();

$survey = [];
while ($row = $result->fetch_assoc()) {
    $qId = $row['QuestionID'];

    if (!isset($survey['title'])) {
        $survey['title'] = $row['surveyTitle'];
    }

    if (!isset($survey['questions'][$qId])) {
        $survey['questions'][$qId] = [
            "text" => $row['questionText'],
            "isMultipleChoice" => $row['isMultipleChoice'],
            "choices" => []
        ];
    }

    if ($row['choiceText']) {
        $survey['questions'][$qId]['choices'][] = [
            "choiceID" => $row['ChoiceID'],
            "text" => $row['choiceText']
        ];
    }
}

echo json_encode($survey);
?>
