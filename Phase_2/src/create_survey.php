<?php
if (session_status() === PHP_SESSION_NONE) {
    session_start();
}

if (!isset($_SESSION['isAdmin']) || !$_SESSION['isAdmin']) {
    die("Access denied. Admins only.");
}
?>
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Create Survey</title>
  <style>
    .question-block { border: 1px solid #ccc; padding: 1em; margin-bottom: 1em; }
    .choice-input { display: block; margin-top: 0.5em; }
  </style>
</head>
<body>
  <h2>Create a New Survey</h2>
  <form id="createForm">
    <label>Survey Title:</label><br>
    <input type="text" id="surveyTitleInput" required><br><br>

    <div id="questionContainer"></div>

    <button type="button" id="addQuestion">➕ Add Question</button><br><br>
    <!-- <textarea id="preview" rows="10" cols="60" readonly></textarea><br><br> -->

    <button type="submit">Submit Survey</button>
  </form>

  <script src="SurveyModel.js"></script>
  <script src="SurveyView.js"></script>
  <script src="SurveyController.js"></script>
  <script>
    const model = new SurveyModel();
    const view = new SurveyView(model);
    const controller = new SurveyController(model, view);
    controller.init();
  </script>
</body>
</html>