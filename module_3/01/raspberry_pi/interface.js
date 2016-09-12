// Modules
var express = require('express');

// Express app
var app = express();

// aREST
var arest = require("arest")(app);

// Use public directory
app.use(express.static('public'));

// Routes
app.get('/', function (req, res) {

  res.sendfile(__dirname + '/public/interface.html');

});

// Add device
rest.addDevice('http','192.168.1.104');

// Start server
app.listen(3000, function () {
  console.log('Home automation system started');
});
