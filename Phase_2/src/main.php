<?php
session_start();

if (!isset($_SESSION['UserID'])) {
    header("Location: login.php");
    exit;
}

$name = htmlspecialchars($_SESSION['Name']);
$isAdmin = $_SESSION['isAdmin'];

$page = isset($_GET['page']) ? $_GET['page'] : null;
$allowedPages = ['create_survey', 'select_survey', 'view_responses', 'take_survey', 'submit_response', 'save_survey'];
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Main Page</title>
  <link rel="stylesheet" href="style.css">

</head>
<body>
  <header>
    <h2>Welcome, <?= $name ?>!</h2>
  </header>

  <nav>
    <a href="main.php">🏠 Home</a>
    <?php if ($isAdmin) { ?>
      <a href="main.php?page=create_survey">🛠️ Create Survey</a>
    <?php } ?>
    <a href="main.php?page=select_survey">📝 Take Survey</a>
    <a href="main.php?page=view_responses">📄 View Responses</a>
    <a href="logout.php">🚪 Logout</a>
  </nav>

  <main>
  <?php if (!$page) { ?>
    <!-- default menu code -->
  <?php } elseif (in_array($page, $allowedPages)) {
    if ($page === "save_survey" && isset($_GET['success'])) {
      echo "<h2 style='color: green;'>✅ Survey created successfully!</h2>";
      echo '<a href="main.php" style="text-decoration:none; font-size:1.1rem;">🏠 Return to Dashboard</a>';
    } else {
      include $page . '.php';
    }
  } else {
    echo "<p>Page not found.</p>";
  } ?>
</main>
</body>
</html>
