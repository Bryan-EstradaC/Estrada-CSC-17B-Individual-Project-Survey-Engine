<?php
if (session_status() === PHP_SESSION_NONE) {
    session_start();
}

require_once("connect.php");

if (!isset($_SESSION['UserID'])) {
    echo "You must be logged in to view this page.";
    exit;
}

$userId = $_SESSION['UserID'];
$userName = $_SESSION['Name'];

// Fetch responses by the user
$sql = "
    SELECT r.ResponseID, s.Title AS SurveyTitle, r.SurveyID
    FROM response r
    JOIN survey s ON r.SurveyID = s.SurveyID
    WHERE r.UserID = ?
";
$stmt = $connection->prepare($sql);
$stmt->bind_param("i", $userId);
$stmt->execute();
$result = $stmt->get_result();

$responses = [];
while ($row = $result->fetch_assoc()) {
    $responses[] = $row;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Dashboard</title>
</head>
<body>
    <h2>Welcome, <?= htmlspecialchars($userName) ?>!</h2>
    <a href="logout.php">Logout</a>
    <h3>Your Past Survey Responses:</h3>

    <?php if (empty($responses)): ?>
        <p>You haven’t taken any surveys yet.</p>
    <?php else: ?>
        <?php foreach ($responses as $response): ?>
            <div style="margin-bottom: 20px; padding: 10px; border: 1px solid #ccc;">
                <h4>Survey: <?= htmlspecialchars($response['SurveyTitle']) ?></h4>

                <?php
                // Fetch questions and answers for this response
                $sqlQA = "
                    SELECT q.Text AS QuestionText, a.Text AS AnswerText
                    FROM answer a
                    JOIN question q ON a.QuestionID = q.QuestionID
                    WHERE a.ResponseID = ?
                ";
                $stmtQA = $connection->prepare($sqlQA);
                $stmtQA->bind_param("i", $response['ResponseID']);
                $stmtQA->execute();
                $qaResult = $stmtQA->get_result();

                while ($qa = $qaResult->fetch_assoc()):
                ?>
                    <p><strong><?= htmlspecialchars($qa['QuestionText']) ?>:</strong> <?= htmlspecialchars($qa['AnswerText']) ?></p>
                <?php endwhile; ?>
            </div>
        <?php endforeach; ?>
    <?php endif; ?>
</body>
</html>
