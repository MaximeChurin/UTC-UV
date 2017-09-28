<?php
    session_start();
?>
<!DOCTYPE html>
<html>
    <head>
        <link href="bootstrap-3.3.6-dist/css/bootstrap.css" rel="stylesheet">
        <link href="global.css" rel="stylesheet">
    </head>
    <body>
        <h1>CONNEXION</h1>
        <form class="container connexion-form" action="" method="post">
            <div class="row">
                <p class="col-sm-3 col-sm-offset-3">email</p><input id="email" class="col-sm-3" type="text" name="email" />
            </div>
            <div class="row">
                <p class="col-sm-3 col-sm-offset-3">password</p><input id="password" class="col-sm-3" type="password" name="password"  onkeydown="if (event.keyCode == 13) exec()" />
            </div>
                <br>
                <input type="button" id="click-button" value="OK"/>
        </form>
        <script>
            var redirect = function(url, method, sessionId, email, password, firstname) {
                var form = document.createElement('form');
                form.method = method;
                form.action = url;

                var inputSessionId = document.createElement('input');
                inputSessionId.type = "text";
                inputSessionId.name = "session-id";
                inputSessionId.value = sessionId;
                inputSessionId.setAttribute("type", "hidden");
                form.appendChild(inputSessionId);

                var inputEmail = document.createElement('input');
                inputEmail.type = "text";
                inputEmail.name = "email";
                inputEmail.value = email;
                inputEmail.setAttribute("type", "hidden");
                form.appendChild(inputEmail);

                var inputPassword = document.createElement('input');
                inputPassword.type = "text";
                inputPassword.name = "password";
                inputPassword.value = password;
                inputPassword.setAttribute("type", "hidden");
                form.appendChild(inputPassword);

                var inputFirstname = document.createElement('input');
                inputFirstname.type = "text";
                inputFirstname.name = "firstname";
                inputFirstname.value = firstname;
                inputFirstname.setAttribute("type", "hidden");
                form.appendChild(inputFirstname);

                document.body.appendChild(form);
                form.submit();
            };

            function testEmail(emailAControler) {
                var formatEmail = /^[0-9a-z._-]+@{1}[0-9a-z.-]{2,}[.]{1}[a-z]{2,5}$/;

                return formatEmail.test(emailAControler);
            }

            function testText(champAControler) {
                var formatTexte = /^[a-zàäâéèêëïîöôùüû\s]*$/i;

                return formatTexte.test(champAControler);
            }

            function exec() {
                var xhr = new XMLHttpRequest();
                var email = document.getElementById('email').value;
                var password = document.getElementById('password').value;

                if(!testEmail(email) || !testText(password)) {
                    return;
                }

                xhr.open('GET', 'http://127.0.0.1:8180/videoGameAPI/rest/jeux/customer?email=' + email + '&password=' + password);

                xhr.addEventListener('readystatechange', function() {
                    if (xhr.readyState === XMLHttpRequest.DONE) {
                        var response = JSON.parse(xhr.responseText);
                        if(200 == xhr.status) {
                            redirect('index.php', 'post', response.id, response.email, response.password, response.firstName);
                        }
                    }
                });

                xhr.send();
            }

            document.getElementById("click-button").onclick = exec;
        </script>
    </body>
</html>
