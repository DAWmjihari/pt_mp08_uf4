<?php
$mysqli = new mysqli('127.0.0.1', 'root', '', 'm8uf4');
if ($mysqli->connect_error) {
	die('Connect Error (' . $mysqli->connect_errno . ') ' . $mysqli->connect_error);
}else {
	$mysqli->autocommit(false);

	// Afegir usuari
	if (isset($_POST['nameDesc']) && isset($_POST['user']) && isset($_POST['password'])){
		$s = "INSERT into usuaris (nameDesc,user,password) values (?, ?, ?)";
		if ($stmt = $mysqli->prepare($s)){
			$stmt->bind_param("sss", $_POST['nameDesc'],$_POST['user'],$_POST['password']);
			$stmt->execute();
			$stmt->close();
			$mysqli->commit();
		}
		// Consulta password
	}else if (isset($_POST['user'])) {
		$s = "select password from usuaris where user = \"" .$_POST['user'] . "\"";
		$res = $mysqli->query($s);
	}

	// LListat usuaris
	$s = "select user from usuaris";
	$users = $mysqli->query($s);
}


?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<title>Part PHP</title>
	<style type="text/css" media="screen">
		* {
			font-family: Arial;
			margin: 3px;
		}
	</style>
</head>
<body>
	<h3>Afegir usuari</h3>
	<hr>
	<form action="index.php" method='post'>
		Nom descriptiu cotrasenya<br><input type="text" name="nameDesc" required><br>
		Nom d'usuari <br><input type="text" name="user" required><br>
		Contrasenya <br><input type="password" name="password" required><br>
		<input type="submit" value="afegir">
	</form>
	<br>
	<h3>Consultar contrasenya</h3>
	<hr>
	<form action="index.php" method='post'>
		Nom d'usuari <br><input type="text" name="user" required><br>
		<input type="submit" value="Consulta">
		<?php
		if (isset($res) && $res->num_rows == 1) {
			while (($row = $res->fetch_row())) {
				printf("<br><br>La contrasenya ha sigut recuperada, i es aquesta : '%s'", $row[0]);
			}
		}
		?>
	</form>
	<h3>Llista Usuaris </h3>
	<hr>
	<?php
	if (isset($users) && $users->num_rows >= 1) {
		while (($row = $users->fetch_row())) {
			printf("NOM......: %s <br>", $row[0]);
		}
	}
	?>
</body>
</html>