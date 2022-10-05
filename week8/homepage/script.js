function vanishArrowAndButton() {
  let arrowElement = document.getElementById("arrow-id");
  let buttonToShowQuiz = document.getElementById("button-to-show-quiz");

  arrowElement.style.display = "none";
  buttonToShowQuiz.style.display = "none";
}

function showQuiz() {
  let quizQuestion = document.getElementById("question")
  let quizForm = document.getElementById("body__lego-question");
  let quizHint = document.getElementById("hint");
  quizForm.style.display = "block";
  quizQuestion.style.display = "block";
  quizHint.style.display = "block";
}

function evaluateQuiz() {
  let rightFreeAnswer = "Legolas";
  let textAnswer = document.querySelector('input');
  let quizDiv = document.getElementById("hobby-div");

  if (textAnswer.value === rightFreeAnswer) {
      textAnswer.style.backgroundColor = 'green';
      document.querySelector('#hobby-text').innerHTML = "Ich habe keine Hobbys (KEKW). Spaß beiseite, meine Hobbys sind: <br> &nbsp Zocken, meine Katze lieb haben, multimediale Unterhaltung.<br/>"
      quizDiv.style.display = "block";
  } else {
      textAnswer.style.backgroundColor = 'red';
      document.querySelector('#hobby-text').innerHTML = "Einfach faaaaalsch. mmmmmmm."
  }
}
