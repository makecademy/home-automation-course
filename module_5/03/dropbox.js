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
 
var Webcam = NodeWebcam.create( opts );

// Token
var ACCESS_TOKEN = "vRKUx36ee7sAAAAAAABRrhWtpa5Hgw_KPUjWb_3Ap7IhCvCJNXXUm_DK7mE6OFUZ";

// Dropbox object
var dbx = new Dropbox({ accessToken: ACCESS_TOKEN });

var pictureName = ( new Date() ).toISOString() + '.jpg';
Webcam.capture( pictureName, function(location) {
 
    console.log( "Image created!" );

    fs.readFile( __dirname + '/' + pictureName, function (err, file) {
      if (err) {
        throw err; 
      }

      // Upload
      dbx.filesUpload({path: '/' + pictureName, contents: file}, function (err, response) {

        console.log(err);
        console.log(response);

      });

    });

});


