<?php

// Make sure only 1 PHP script can access the start_game.py script
// at one time.
$fp = fopen("/tmp/mandelbrot_lock.txt", "w");
flock($fp, LOCK_EX);

try
{
  $db = new PDO("sqlite:/var/www/html/mandelbrot_cluster/coordinates.db");
}
catch (PDOException $e)
{
  print "Error: ".$e->getMessage()."<br>";
  die();
}

$move_to = "/var/www/html/mandelbrot_cluster/images/".basename($_FILES['file']['name']);
move_uploaded_file($_FILES['file']['tmp_name'], $move_to);
chmod($move_to, 0666);

$sql = "update coordinates ".
       "set completed=1, ".
       "end_time=".time()." ".
       "where coordinate_id=". $_POST["coordinate_id"];

$query = $db->query($sql);


//$db->close();

flock($fp, LOCK_UN);
fclose($fp);

?>
