<?php
session_start();
require_once("connect.php");

// Validate POST input
if (!isset($_POST['Name'], $_POST['Password'])) {
    echo json_encode(["status" => "error", "message" => "Missing username or password"]);
    exit;
}

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

    echo json_encode([
        "status" => "success",
        "message" => "Login successful",
        "data" => [
            "Name" => $user['Name'],
            "isAdmin" => $user['isAdmin']
        ]
    ]);
} else {
    echo json_encode(["status" => "error", "message" => "Invalid username or password"]);
}
?>
