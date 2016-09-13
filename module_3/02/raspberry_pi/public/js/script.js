$( document ).ready(function() {

  // Indicators
  setInterval(function () {

    // Current
    $.get('/motion_sensor/5', function(data) {

      if (data.status == true) {
        $( "#motion-status" ).text("No Motion");
      }
      else {
        $( "#motion-status" ).text("Motion Detected");
      }

    });

  }, 2000);

});
