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

  setInterval(function () {

    // Temperature
    $.get('/sensors/temperature', function(data) {

      $( "#temperature-status" ).text(data.temperature);
   
    });

  }, 2000);

  setInterval(function () {

    // Temperature
    $.get('/sensors/humidity', function(data) {

      $( "#humidity-status" ).text(data.humidity);
   
    });

  }, 2000);

});
