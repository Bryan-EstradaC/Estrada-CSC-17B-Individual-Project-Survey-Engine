class SurveyController {
  constructor(model, view) {
    this.model = model;
    this.view = view;
  }

  init() {
    this.view.bindAddQuestion(this.handleAddQuestion.bind(this));
    this.view.bindSubmit(this.handleSubmit.bind(this));
  }

  handleAddQuestion() {
    // No-op, view handles all UI input creation
  }

  handleSubmit(payload) {
    const form = document.createElement("form");
    form.method = "POST";
    form.action = "save_survey.php";


    const hidden = document.createElement("input");
    hidden.type = "hidden";
    hidden.name = "data";
    hidden.value = JSON.stringify(payload);

    form.appendChild(hidden);
    document.body.appendChild(form);
    form.submit();
  }
}
