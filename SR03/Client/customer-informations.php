<?php
    session_start();

    if(!isset($_SESSION['session_id'])) {
        header('Location: connexion.php');
        exit();
    }
?>

<!DOCTYPE html>
<html>
    <head>
        <link href="bootstrap-3.3.6-dist/css/bootstrap.css" rel="stylesheet">
        <link href="global.css" rel="stylesheet">
    </head>
    <body>
        <nav class="navbar navbar-inverse sticky-navbar navbar-fixed-top" role="navigation">
            <div class="container-fluid">
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar_content">
                    </button>
                </div>
                <a class="navbar-brand" href="index.php">Home</a>
                <div class="collapse navbar-collapse" id="navbar_content">
                    <ul class="nav navbar-nav navbar-left">
                        <li class="pull-left"><p class="navbar-text">Hello  <?php echo json_encode($_SESSION['firstname'], JSON_HEX_TAG); ?></p></li>
                    </ul>
                    <ul class="nav navbar-nav navbar-right">
                        <li class="pull-right">
                            <a href="customer-informations.php"><span class="glyphicon glyphicon-user" aria-hidden="true"></span></a>
                        </li>
                        <li class="pull-right">
                            <a href="logout.php"><span class="glyphicon glyphicon-off" aria-hidden="true"></span></a>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>
        <div id="customer-infos">
            <h1>My profile</h1>
        </div>
        <script>
            function makeRow(firstText, secondText) {
                var row = document.createElement('div');
                row.classList.add('row');

                firstColumn = document.createElement('p');
                firstColumn.innerHTML = firstText
                firstColumn.classList.add('col-sm-3');
                firstColumn.classList.add('col-sm-offset-3');

                secondColumn = document.createElement('p');
                secondColumn.innerHTML = secondText
                secondColumn.classList.add('col-sm-3');

                row.appendChild(firstColumn);
                row.appendChild(secondColumn);

                return row;
            }

            function makeUL(jsonCustomer) {
                var list = document.createElement('div');
                list.classList.add('container');

                list.appendChild(makeRow('Mail', jsonCustomer['email']));
                list.appendChild(makeRow('Password', jsonCustomer['password']));
                list.appendChild(makeRow('First Name', jsonCustomer['firstName']));
                list.appendChild(makeRow('Last Name', jsonCustomer['lastName']));
                list.appendChild(makeRow('Phone Number', jsonCustomer['phoneNumber']));

                return list;
            }

            function showCustomerInformations() {
                var xhr = new XMLHttpRequest();
                var email = <?php echo json_encode($_SESSION['email'], JSON_HEX_TAG); ?>;
                var password = <?php echo json_encode($_SESSION['password'], JSON_HEX_TAG); ?>;
                xhr.open('GET', 'http://127.0.0.1:8180/videoGameAPI/rest/jeux/customer?email=' + email + '&password=' + password);

                xhr.addEventListener('readystatechange', function() {
                    if (xhr.readyState === XMLHttpRequest.DONE) {
                        var response = JSON.parse(xhr.responseText);
                        if(200 == xhr.status) {
                            divCustomer = document.getElementById('customer-infos');

                            oldList =  document.getElementById('customer-elements');
                            if(oldList) {
                                divCustomer.removeChild(oldList);
                            }

                            var list = makeUL(response);

                            list.setAttribute('id', 'customer-elements');
                            divCustomer.appendChild(list);
                        }
                    }
                });

                xhr.send();
            }

            var callback = function(){
                // Handler when the DOM is fully loaded
                showCustomerInformations();
            };

            if (
                document.readyState === "complete" ||
                (document.readyState !== "loading" && !document.documentElement.doScroll)
            ) {
              callback();
            } else {
              document.addEventListener("DOMContentLoaded", callback);
            }
        </script>
    </body>
</html>
