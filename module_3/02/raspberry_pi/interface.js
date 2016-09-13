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

// Automation
setInterval(function() {

  // Get devices
  if (rest.getDevice('motion_sensor') && rest.getDevice('alarm_module')) {

    var motionSensor = rest.getDevice('motion_sensor');
    var alarmModule = rest.getDevice('alarm_module');

    motionSensor.digitalRead(5, function (error, response, body) {

      if (!err) {
        // If motion was detected
        if (body.return_value == true) {

          alarmModule.digitalWrite(5, 1);

        }
        else if (body.return_value == false) {

          alarmModule.digitalWrite(5, 0);

        }
      }

    });

  }
  
}, 2000);

// Start server
app.listen(3000, function () {
  console.log('Home automation system started');
});
