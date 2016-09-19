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

// Start server
app.listen(3000, function () {
  console.log('Remote monitor system started');
});
