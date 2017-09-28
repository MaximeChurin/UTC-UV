<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Supprimer un thème
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

$id_theme=$_POST['id_theme'];

	if(!empty($id_theme) )
	{
	$query=mysqli_query($connect, "UPDATE themes SET supprime='1' WHERE id_theme=$id_theme"); 
	$result = mysqli_query($connect, "select * from themes where id_theme='$id_theme'");
	$row=mysqli_fetch_array($result, MYSQL_NUM);

	echo "<br><center> Le thème $row[1] a bien été supprimé</center>";

		if(empty($query))
		{
		echo "<br>pas bon".mysqli_error($connect);
		}
	}

	else
	{
	echo "<br><center>Le thème n'a pas été choisi <br><br>";
	echo "<form method = 'post' action='suppression_theme.php'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}


mysqli_close($connect);

?>

</body>

</html>
