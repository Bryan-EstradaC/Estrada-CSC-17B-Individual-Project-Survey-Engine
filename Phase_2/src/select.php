<?php

require_once("connect.php");

$result = $connection->query("SELECT `Name`, `Password` FROM `survey_enginedb`.`user` AS `user`");

debug($result);

for( $i = 0; $i < $result->num_rows; $i++ ){
    $row = $result->fetch_assoc();
    echo ' u: ' . $row['Name'] . ' p: ' . $row['Password'] . '<br>';
}
?>

