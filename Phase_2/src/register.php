<?php
require_once("connect.php");

$error = "";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!isset($_POST['Name'], $_POST['Password'])) {
        $error = "Missing required fields.";
    } else {
        $name = $_POST['Name'];
        $password = $_POST['Password'];
        $isAdmin = 0;

        if (!preg_match('/^[A-Za-z][A-Za-z0-9_-]{5,19}$/', $name)) {
            $error = "❌ Username must start with a letter and be 6–20 characters long. Allowed characters: letters, numbers, underscores (_), and hyphens (-).";
        } elseif (!preg_match('/^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%]).{6,20}$/', $password)) {
            $error = "❌ Password must be 6–20 characters and include at least one uppercase letter, one lowercase letter, one number, and one special character (@, #, $, or %).";
        } else {
            $stmt = $connection->prepare("SELECT UserID FROM user WHERE Name = ?");
            $stmt->bind_param("s", $name);
            $stmt->execute();
            $stmt->store_result();

            if ($stmt->num_rows > 0) {
                $error = "❌ Username already taken. Please choose another one.";
            } else {
                $stmt->close();

                $stmt = $connection->prepare("INSERT INTO user (Name, Password, isAdmin) VALUES (?, ?, ?)");
                $stmt->bind_param("ssi", $name, $password, $isAdmin);

                if ($stmt->execute()) {
                    session_start();
                    $_SESSION['UserID'] = $stmt->insert_id;
                    $_SESSION['Name'] = $name;
                    $_SESSION['isAdmin'] = $isAdmin;
                    ?>
                    <!DOCTYPE html>
                    <html>
                    <head><title>Registration Successful</title></head>
                    <body>
                        <h2>✅ Registration successful. Welcome, <?= htmlspecialchars($name) ?>!</h2>
                        <form action="main.php" method="get">
                            <button type="submit">Go to main page</button>
                        </form>
                    </body>
                    </html>
                    <?php
                    exit;
                } else {
                    $error = "Registration failed: " . $stmt->error;
                }
            }
        }
    }
}
?>
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Register New User</title>
  <style>
    body {
      background-image: url('images/hello.jpg');
      background-size: cover;
      background-position: center;
      background-repeat: no-repeat;
      font-family: Arial, sans-serif;
      color: rgb(21, 15, 15);
      margin: 0;
      padding: 0;
    }
    form {
      background-color: rgba(0, 0, 0, 0.72);
      padding: 20px;
      border-radius: 8px;
      max-width: 300px;
      margin: 100px auto;
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
    .error {
      color: #ff6961;
      font-weight: bold;
      margin-bottom: 1rem;
    }
    button {
      margin-top: 10px;
    }
  </style>
</head>
<body>
  <div style="text-align: center;">
    <h2>Create an Account</h2>
  </div>

  <form method="POST" action="register.php">
    <?php if (!empty($error)): ?>
      <div class="error"><?= $error ?></div>
    <?php endif; ?>

    <label for="name">Username:</label><br>
    <input type="text" id="name" name="Name" required
           title="6–20 characters. Must start with a letter. Only letters, digits, _ or - allowed."><br><br>

    <label for="password">Password:</label><br>
    <input type="password" id="password" name="Password" required
           title="6–20 characters with at least one uppercase letter, one lowercase letter, one number, and one of @#$%"><br><br>

    <button type="submit">Register</button>
  </form>
</body>
</html>
