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
$questionSql = "INSERT INTO question (Text, isMultipleChoice, SurveyID) VALUES (?, ?, ?)";
$questionStmt = $connection->prepare($questionSql);

$choiceSql = "INSERT INTO choice (Text, QuestionID) VALUES (?, ?)";
$choiceStmt = $connection->prepare($choiceSql);

foreach ($questions as $q) {
    $text = $q['text'];
    $isMultipleChoice = $q['isMultipleChoice'];

    $questionStmt->bind_param("sii", $text, $isMultipleChoice, $surveyId);
    if (!$questionStmt->execute()) {
        echo json_encode(["status" => "error", "message" => $questionStmt->error]);
        exit;
    }

    $questionId = $questionStmt->insert_id;

    // If multiple choice, insert choices
    if ($isMultipleChoice && isset($q['choices']) && is_array($q['choices'])) {
        foreach ($q['choices'] as $choiceText) {
            $choiceStmt->bind_param("si", $choiceText, $questionId);
            if (!$choiceStmt->execute()) {
                echo json_encode(["status" => "error", "message" => $choiceStmt->error]);
                exit;
            }
        }
    }
}


echo json_encode(["status" => "success"]);
?>
