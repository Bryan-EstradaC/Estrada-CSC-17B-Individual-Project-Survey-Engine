class SurveyModel {
  constructor() {
    this.title = "";
    this.questions = []; // { text, isMultipleChoice, choices: [] }
  }

  setTitle(title) {
    this.title = title;
  }

  addQuestion(question) {
    this.questions.push(question);
  }

  getPayload() {
    return {
      title: this.title,
      questions: this.questions,
    };
  }
}
