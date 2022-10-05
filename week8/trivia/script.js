document.addEventListener('DOMContentLoaded', function() {
  let rightDecision = document.querySelector('.rightButton');

  rightDecision.addEventListener('click', function() {
      rightDecision.style.backgroundColor = 'green';
      document.querySelector('#output1').innerHTML = "Your answer is right!";
  });

  let wrongDecisions = document.querySelectorAll('.wrongButton');

  for (let wrongButtonIterator = 0; wrongButtonIterator < wrongDecisions.length; wrongButtonIterator++) {
    wrongDecisions[wrongButtonIterator].addEventListener('click', function() {
      wrongDecisions[wrongButtonIterator].style.backgroundColor = 'red';
      document.querySelector('#output1').innerHTML = "Your answer is wrong!";
    });
  }

  document.querySelector('#submit').addEventListener('click', function() {
    let rightFreeAnswer = "Harry Potter";
    let textAnswer = document.querySelector('input')

    if (textAnswer.value === rightFreeAnswer) {
        textAnswer.style.backgroundColor = 'green';
        document.querySelector('#output2').innerHTML = "Your answer is right!";
    } else {
        textAnswer.style.backgroundColor = 'red';
        document.querySelector('#output2').innerHTML = "Your answer is wrong!";
    }
  });
});
