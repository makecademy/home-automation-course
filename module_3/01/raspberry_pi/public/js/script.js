$( document ).ready(function() {

  // Set pin to output
  $.get('/lamp/mode/5/o');

  // Buttons
  $( "#on" ).click(function() {

    // Set lamp ON
    $.get('/lamp/digital/5/1');


  });

  $( "#off" ).click(function() {

    // Set lamp OFF
    $.get('/lamp/digital/5/0');

  });

});
