<?php
require_once("connect.php");

$result = $connection->query("SELECT SurveyID, Title FROM survey");

echo "<h2>Select a Survey</h2>";
echo "<form method='GET' action='take_survey.php'>";
echo "<select name='survey_id' required>";
while ($row = $result->fetch_assoc()) {
    echo "<option value='{$row['SurveyID']}'>{$row['Title']}</option>";
}
echo "</select><br><br>";
echo "<input type='submit' value='Take Survey'>";
echo "</form>";
?>
