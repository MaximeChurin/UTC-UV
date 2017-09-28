<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Ajouter une séance
</title>

</head>

<center>
<h1>
Résultat
</h1>
</center>
<br>

<body>

<?php

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$id_seance=$_POST['id_seances'];
$id_eleve=$_POST['id_eleves'];

	if(!empty($id_eleve) )
	{
	$query=mysqli_query($connect, "delete from Inscription where id_seance=$id_seance and id_eleve=$id_eleve");
	$result= mysqli_query($connect,"SELECT * FROM eleves Where id_eleve='$id_eleve'");
	$row = mysqli_fetch_array($result, MYSQL_NUM);
	 
	echo "<br><center> L'élève $row[1] $row[2] a bien été désinscrit de la séance</center><br>";
	}

	else
	{
	echo "<br> <center>Elève non choisi ";
	echo "<form method = 'post' action='annulation_seance.php'>";
	echo "<input type='hidden' name='id_seances' value='$_POST[id_seances]'> ";
	echo "<input type='hidden' name='enregistrer' value='enregistrer'> ";
	echo"<br><br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}

mysqli_close($connect);

?>

</body>

</html>
