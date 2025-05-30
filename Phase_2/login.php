<?php
require_once ("connect.php");

$username = $_POST['Name'];
$password = $_POST['Password'];
$isAdmin = $_POST['isAdmin'] === 'true' ? 1 : 0;

$sql = "INSERT INTO user (Name, Password, isAdmin) VALUES (?, ?, ?)";
$stmt = $connection->prepare($sql);
$stmt->bind_param("ssi", $username, $password, $isAdmin);

if ($stmt->execute()) {
    echo json_encode(["status" => "success"]);
} else {
    echo json_encode(["status" => "error", "message" => $stmt->error]);
}
?>

