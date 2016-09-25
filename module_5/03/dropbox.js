// Modules
var Dropbox = require('dropbox');
var fs = require('fs');
var NodeWebcam = require( "node-webcam" );

// Webcam
var opts = {
    width: 1280,
    height: 720,
    delay: 0,
    quality: 100,
    output: "jpeg",
    device: false,
    verbose: true
}
 
var cam = new Webcam( opts );

// Token
var ACCESS_TOKEN = "dropboxToken";

// Dropbox object
var dbx = new Dropbox({ accessToken: ACCESS_TOKEN });

var pictureName = ( new Date() ).toString();
NodeWebcam.capture( pictureName, {}, function(folder) {
 
    console.log( "Image created!" );
    console.log(folder);

    fs.readFile( __dirname + '/' + pictureName + 'jpg', function (err, file) {
      if (err) {
        throw err; 
      }
      console.log(file.toString());

      // Upload
      dbx.filesUpload({path: '/' + pictureName + 'jpg', contents: file}, function (err, response) {

        console.log(err);
        console.log(response);

      });

    });

});


