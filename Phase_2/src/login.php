<?php
session_start();
require_once("connect.php");

// Handle login POST request
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['Name'], $_POST['Password'])) {
    $username = $_POST['Name'];
    $password = $_POST['Password'];

    $sql = "SELECT * FROM user WHERE Name = ? AND Password = ?";
    $stmt = $connection->prepare($sql);
    $stmt->bind_param("ss", $username, $password);
    $stmt->execute();

    $result = $stmt->get_result();

    if ($result->num_rows === 1) {
        $user = $result->fetch_assoc();

        $_SESSION['UserID'] = $user['UserID'];
        $_SESSION['Name'] = $user['Name'];
        $_SESSION['isAdmin'] = $user['isAdmin'];

        // ✅ Redirect to menu/dashboard after successful login
        header("Location: main.php");
        exit;
    } else {
        echo "<p style='color: red'>Invalid username or password.</p>";
    }
    exit;
}
?>

<!-- If not a POST request, serve the login page -->
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Login</title>
  <style>
    body {
      background-image: url('images/Wall.jpg');
      background-size: cover;
      background-position: center;
      background-repeat: no-repeat;
      font-family: Arial, sans-serif;
      color:rgb(21, 15, 15);
      margin: 0;
      padding: 0;
    }

    form {
      background-color: rgba(0, 0, 0, 0.6);
      padding: 20px;
      border-radius: 8px;
      max-width: 300px;
      margin: 100px auto;
      color: white;
    }

    button {
      margin-top: 10px;
    }

    .center-container {
      text-align: center;
      margin-top: 20px;
      color: white;
    }

    h2 {
      text-align: center;
      margin: 30px auto 5px;
      color: white;
      background-color: rgba(0, 0, 0, 0.6);
      border-radius: 8px;
      padding: 10px 20px;
      display: inline-block;
    }
  </style>
  <link rel="stylesheet" href="login.css">
  <script src="Model.js"></script>
  <script src="View.js"></script>
  <script src="Controller.js"></script>
</head>
<body>
  <div class="center-container">
  <h2>Login</h2>
</div>

<form id="loginForm" method="POST" action="login.php">
  <label for="name">Username:</label><br>
  <input type="text" id="name" name="Name" required><br><br>

  <label for="password">Password:</label><br>
  <input type="password" id="password" name="Password" required><br><br>

  <button type="submit">Login</button>
</form>

<form action="register.php" method="get" class="center-container">
  <p>Don't have an account?</p>
  <button type="submit">Register</button>
</form>


  <div id="loginResponse"></div>

  <script>
    const model = new LoginModel();
    const view = new LoginView(model);
    const controller = new LoginController(model, view);
    controller.init();
  </script>
</body>
</html>