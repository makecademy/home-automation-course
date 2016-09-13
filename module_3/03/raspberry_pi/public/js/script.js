$( document ).ready(function() {

   // Buttons
  $( "#on" ).click(function() {

    // Set lamp ON
    $.get('/lamp_control/digital/5/1');


  });

  $( "#off" ).click(function() {

    // Set lamp OFF
    $.get('/lamp_control/digital/5/0');

  });

  // Indicators
  setInterval(function () {

    // Current
    $.get('/motion_sensor/5', function(data) {

      if (data.return_value == true) {
        $( "#motion-status" ).text("No Motion");
      }
      else {
        $( "#motion-status" ).text("Motion Detected");
      }

    });

  }, 2000);

});
