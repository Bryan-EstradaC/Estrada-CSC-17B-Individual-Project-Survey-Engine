<?php
require_once("connect.php");

$userId = $_POST['UserID'];
$answers = $_POST['answers'];

// Get any one question to get the survey ID
$firstQId = array_key_first($answers);
$qInfo = $connection->query("SELECT SurveyID FROM question WHERE QuestionID = $firstQId")->fetch_assoc();
$surveyId = $qInfo['SurveyID'];

// Insert into `response`
$stmt = $connection->prepare("INSERT INTO response (UserID, SurveyID) VALUES (?, ?)");
$stmt->bind_param("ii", $userId, $surveyId);
$stmt->execute();
$responseId = $stmt->insert_id;

// Insert answers
$stmt = $connection->prepare("INSERT INTO answer (ResponseID, QuestionID, Text) VALUES (?, ?, ?)");
foreach ($answers as $questionId => $text) {
    $stmt->bind_param("iis", $responseId, $questionId, $text);
    $stmt->execute();
}

echo json_encode(["status" => "success"]);
?>
