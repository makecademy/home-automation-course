// Modules
var express = require('express');

// Express app
var app = express();

// Set public folder
app.use(express.static(__dirname + '/public'));

// Routes
app.get('/', function (req, res) {

  res.sendFile(__dirname + '/public/interface.html');

});

// aREST
var rest = require("arest")(app);

// Add device
rest.addDevice('http','192.168.0.104');

// Start server
app.listen(3000, function () {
  console.log('Home automation system started');
});
