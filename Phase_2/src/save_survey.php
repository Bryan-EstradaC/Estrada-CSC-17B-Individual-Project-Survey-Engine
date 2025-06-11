<?php
require_once("connect.php");
if (session_status() === PHP_SESSION_NONE) {
    session_start();
}

if (!isset($_SESSION['UserID']) || !$_SESSION['isAdmin']) {
    die("Only admins can create surveys.");
}

if (!isset($_POST['data'])) {
    die("Missing survey data.");
}

$data = json_decode($_POST['data'], true);
$title = $data['title'];
$questions = $data['questions'];

// Insert survey
$stmt = $connection->prepare("INSERT INTO survey (Title) VALUES (?)");
$stmt->bind_param("s", $title);
$stmt->execute();
$surveyID = $stmt->insert_id;

// Insert questions
$qstmt = $connection->prepare("INSERT INTO question (SurveyID, Text, isMultipleChoice) VALUES (?, ?, ?)");
$cstmt = $connection->prepare("INSERT INTO choice (QuestionID, Text) VALUES (?, ?)");

foreach ($questions as $q) {
    $isMC = $q['isMultipleChoice'] ? 1 : 0;
    $qstmt->bind_param("isi", $surveyID, $q['text'], $isMC);
    $qstmt->execute();
    $questionID = $qstmt->insert_id;

    if ($isMC && isset($q['choices'])) {
        foreach ($q['choices'] as $choice) {
            $cstmt->bind_param("is", $questionID, $choice);
            $cstmt->execute();
        }
    }
}

header("Location: main.php?page=save_survey&success=1");
exit;

// echo <<<HTML
//     <h2>Survey created successfully!</h2>
//     <form action="main.php" method="get">
//         <button type="submit">Go to Dashboard</button>
//     </form>
// HTML;



?>
