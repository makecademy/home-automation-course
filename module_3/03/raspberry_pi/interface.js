// Modules
var express = require('express');

// Express app
var app = express();

// Use public directory
app.use(express.static('public'));

// Routes
app.get('/', function (req, res) {

  res.sendfile(__dirname + '/public/interface.html');

});

// aREST
var rest = require("arest")(app);

// Add device
rest.addDevice('http','192.168.0.104');
rest.addDevice('http','192.168.0.105');

// Start server
app.listen(3000, function () {
  console.log('Home automation system started');
});
