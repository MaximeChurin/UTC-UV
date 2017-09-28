<html>
<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Ajouter une séance
</title>

</head>

<body>

<center>
<h1>
Ajouter une séance
</h1>
</center>

<br>
<br>

<?php

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$result = mysqli_query($connect,"SELECT * FROM themes where supprime='0'");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if (!empty($row) )
	{
	echo "<FORM METHOD='POST' ACTION='ajouter_seance.php'>";

	?>

	<center><table>
		<tr>
			<th>
			Date de la séance :
			</th>

			<td>
			<select name="jour_seance" size="1">  
				<option >Jour</option>
				<option value="01">1</option>
				<option value="02">2</option>
				<option value="03">3</option>
				<option value="04">4</option>
				<option value="05">5</option>
				<option value="06">6</option>
				<option value="07">7</option>
				<option value="08">8</option>
				<option value="09">9</option>
				<option value="10">10</option>
				<option value="11">11</option>  
				<option value="12">12</option>
				<option value="13">13</option>  
				<option value="14">14</option>
				<option value="15">15</option>  
				<option value="16">16</option>
				<option value="17">17</option>  
				<option value="18">18</option>
				<option value="19" >19</option>
				<option value="20">20</option>  
				<option value="21">21</option>
				<option value="22">22</option>  
				<option value="23">23</option>
				<option value="24">24</option>
				<option value="25">25</option> 
				<option value="26">26</option>
				<option value="27">27</option>
				<option value="28">28</option>
				<option value="29" >29</option> 
				<option value="30">30</option>   
				<option value="31">31</option>  
			</select>

			<select name="mois_seance" size="1">  	
				<option >Mois</option>
				<option value="01">Janvier</option>
				<option value="02">Février</option>
				<option value="03">Mars</option>
				<option value="04">Avril</option>
				<option value="05">Mai</option>
				<option value="06">Juin</option>
				<option value="07" >Juillet</option>
				<option value="08">Août</option>
				<option value="09">Septembre</option>
				<option value="10">Octobre</option>  
				<option value="11">Novembre</option> 
				<option value="12">Décembre</option>
			</select>

			<select Name="annee_seance" size="1">	
				<option >Année</option>
				<option value="2014">2014</option>
				<option value="2015">2015</option>
				<option value="2016">2016</option>
				<option value="2017">2017</option>
				<option value="2018">2018</option>
			</select>
			</td>	
		</tr>	

		<tr>
			<td>
			&nbsp
			</td>

			<td>
			&nbsp
			</td>
		</tr>		

		<tr>
			<th>
			Heure :
			</th>

			<td>
			<select Name="heure_seance" size="1">	
				<option value=""></option>
				<option value="10:00">10:00</option>
				<option value="11:00">11:00</option>
				<option value="13:00">13:00</option>
				<option value="14:00">14:00</option>
				<option value="15:00">15:00</option>
				<option value="16:00">16:00</option>
				<option value="17:00">17:00</option>
				<option value="18:00">18:00</option>			                

			</select>
			</td>	
		</tr>	

		<tr>
			<td>
			&nbsp
			</td>

			<td>
			&nbsp
			</td>
		</tr>		

		<tr>
			<th>

			<?php 

			$result = mysqli_query($connect,"SELECT * FROM themes where supprime='0'");

			echo "Thème : </th>"; 
			echo"<td> <select name='id_theme' size='1'>";
			echo "<option value=''>";
			echo "</option>";
				while ($row = mysqli_fetch_array($result, MYSQL_NUM)) 
				{
				echo "<option value='$row[0]'>";
				echo $row[1];
				echo "</option>";
				}
			echo "</select></td>";
		echo"</tr>";
			?>	

		<tr>
			<td>
			&nbsp
			</td>

			<td>
			&nbsp
			</td>
		</tr>

		<tr>
			<td>
			&nbsp
			</td>

			<td>
			&nbsp
			</td>
		</tr>		
		
		<tr>
			<td><center>
			<INPUT VALUE="Ajouter" TYPE="SUBMIT" class="bouton">
			</center></td>

			<td><center>
			<INPUT VALUE="Annuler" TYPE="RESET" class="bouton">
			</center></td>
		</tr>

	</table></center>
	</form>
	
	<?php			
	}

	else
	{
	echo "<center>La tables des thèmes est vide <br><br>";
	echo "<form method = 'post' action='ajout_seance.php'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}


	mysqli_close($connect);
?>

</body>

</html>
