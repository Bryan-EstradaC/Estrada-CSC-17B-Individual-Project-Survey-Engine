<?php
if (session_status() === PHP_SESSION_NONE) session_start();
require_once("connect.php");

if (!isset($_GET['id'])) die("Survey ID missing");
$surveyID = (int)$_GET['id'];

$survey = $connection->query("SELECT * FROM survey WHERE SurveyID = $surveyID")->fetch_assoc();
$questions = $connection->query("
  SELECT q.QuestionID, q.Text, q.isMultipleChoice, c.ChoiceID, c.Text AS ChoiceText
  FROM question q
  LEFT JOIN choice c ON c.QuestionID = q.QuestionID
  WHERE q.SurveyID = $surveyID
  ORDER BY q.QuestionID, c.ChoiceID
")->fetch_all(MYSQLI_ASSOC);

$data = [];
foreach ($questions as $row) {
    $qId = $row['QuestionID'];
    if (!isset($data[$qId])) {
        $data[$qId] = [
            'text' => $row['Text'],
            'mc'   => $row['isMultipleChoice'],
            'choices' => []
        ];
    }
    if ($row['ChoiceID']) {
        $data[$qId]['choices'][] = $row['ChoiceText'];
    }
}
?>

<h2><?= htmlspecialchars($survey['Title']) ?></h2>
<form method="POST" action="main.php?page=submit_response">
  <input type="hidden" name="survey_id" value="<?= $surveyID ?>">
  <?php foreach ($data as $qId => $q): ?>
    <p><?= htmlspecialchars($q['text']) ?></p>
    <?php if ($q['mc']): ?>
      <?php foreach ($q['choices'] as $choice): ?>
        <input type="radio" name="answers[<?= $qId ?>]" value="<?= htmlspecialchars($choice) ?>"> <?= htmlspecialchars($choice) ?><br>
      <?php endforeach; ?>
    <?php else: ?>
      <input type="text" name="answers[<?= $qId ?>]"><br>
    <?php endif; ?>
  <?php endforeach; ?>
  <br><button type="submit">Submit Survey</button>
</form>
