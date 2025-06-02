<?php
session_start();
require_once("connect.php");

// Use logged-in UserID
if (!isset($_SESSION['UserID'])) {
    echo "You must be logged in to take a survey.";
    exit;
}
$userID = $_SESSION['UserID'];

if (!isset($_POST['survey_id']) || !isset($_POST['answers'])) {
    echo "Invalid submission.";
    exit;
}

$surveyID = intval($_POST['survey_id']);
$answers = $_POST['answers'];

// Insert response
$stmt = $connection->prepare("INSERT INTO response (UserID, SurveyID) VALUES (?, ?)");
$stmt->bind_param("ii", $userID, $surveyID);
$stmt->execute();
$responseID = $stmt->insert_id;

// Insert each answer
$stmt = $connection->prepare("INSERT INTO answer (ResponseID, QuestionID, Text) VALUES (?, ?, ?)");
foreach ($answers as $questionID => $text) {
    $stmt->bind_param("iis", $responseID, $questionID, $text);
    $stmt->execute();
}

echo "<p>Thank you! Your response was recorded.</p>";
?>
