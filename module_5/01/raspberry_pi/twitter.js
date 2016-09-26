// Modules
var express = require('express');
var Twitter = require('twitter');
 
// Twitter parameters
var client = new Twitter({
  consumer_key: '',
  consumer_secret: '',
  access_token_key: '',
  access_token_secret: ''
});

// Interval
var postInterval = 10000;

// Express app
var app = express();

// aREST
var rest = require("arest")(app);

// Add device
rest.addDevice('http', '192.168.0.100');

// Start server
app.listen(3000, function () {
  console.log('Home automation system started');
});

// Post on Twitter
setInterval(function() {

	// Get data
	var sensorBoard = rest.getDevice('sensors');
	sensorBoard.getVariable('temperature', function (err, res, body) {

		// Save temperature
		var temperature = body.temperature;

		sensorBoard.getVariable('humidity', function (err, res, body) {

			// Save humdity
			var humidity = body.humidity;

			// Build message
			message = 'Temperature: ' + temperature + 'C Humidity: ' + humidity + '%';
			console.log(message);

			// Post
			client.post('statuses/update', {status: message},  function(error, tweet, response) {
			  if(error) throw error;
			  console.log(tweet);  // Tweet body. 
			  console.log(response);  // Raw response object. 
			});

		});

	});

}, postInterval);
