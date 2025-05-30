<?php
require_once("connect.php");

if (!isset($_POST['title']) || !isset($_POST['questions'])) {
    echo json_encode(["status" => "error", "message" => "Missing survey title or questions"]);
    exit;
}

$title = $_POST['title'];
$questions = $_POST['questions'];

// Insert survey title
$sql = "INSERT INTO survey (Title) VALUES (?)";
$stmt = $connection->prepare($sql);
$stmt->bind_param("s", $title);

if (!$stmt->execute()) {
    echo json_encode(["status" => "error", "message" => $stmt->error]);
    exit;
}

$surveyId = $stmt->insert_id; // Get newly inserted survey ID

// Insert each question
$sql = "INSERT INTO question (Text, isMultipleChoice, SurveyID) VALUES (?, ?, ?)";
$stmt = $connection->prepare($sql);

foreach ($questions as $q) {
    $text = $q['text'];
    $isMultipleChoice = $q['isMultipleChoice'];
    $stmt->bind_param("sii", $text, $isMultipleChoice, $surveyId);
    if (!$stmt->execute()) {
        echo json_encode(["status" => "error", "message" => $stmt->error]);
        exit;
    }
}

echo json_encode(["status" => "success"]);
?>
