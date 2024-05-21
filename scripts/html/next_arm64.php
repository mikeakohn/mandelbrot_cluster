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

// Get the current time and calculate the curent time minus 5 hours.
// Then query the database for a row whose timestamp is further away
// than 5 hours ago and is not completed.
$timestamp = time();
$start = $timestamp - (60 * 60 * 5);
$ip_address = $_SERVER['REMOTE_ADDR'];

$sql = "select * from coordinates ".
       "where completed=0 ".
       "and timestamp<".$start;

$query = $db->query($sql);

$count = 0;

if ($rs = $query->fetch(PDO::FETCH_ASSOC))
{
  print "coordinate_id: ".$rs["coordinate_id"]."\n";
  print "name: ".$rs["name"]."\n";
  print "r0: ".$rs["r0"]."\n";
  print "r1: ".$rs["r1"]."\n";
  print "i0: ".$rs["i0"]."\n";
  print "i1: ".$rs["i1"]."\n";
  print "rotation: ".$rs["rotation"]."\n";

  $sql = "update coordinates ".
         "set timestamp=$timestamp, ".
         "ip_address='".$ip_address."' ".
         "where coordinate_id=".$rs["coordinate_id"];

  //print "sql: ".$sql;

  $db->query($sql);
}
else
{
  print "empty\n";
}

//$db->close();

flock($fp, LOCK_UN);
fclose($fp);

?>
