class SurveyView {
  constructor(model) {
    this.model = model;
    this.titleInput = document.getElementById("surveyTitleInput");
    this.container = document.getElementById("questionContainer");
    this.form = document.getElementById("createForm");
    this.preview = document.getElementById("preview");
  }

  bindAddQuestion(handler) {
    document.getElementById("addQuestion").addEventListener("click", () => {
      const block = document.createElement("div");
      block.className = "question-block";

      const qInput = document.createElement("input");
      qInput.type = "text";
      qInput.placeholder = "Enter question text";
      qInput.required = true;

      const mcBox = document.createElement("input");
      mcBox.type = "checkbox";
      mcBox.className = "mc-toggle";

      const label = document.createElement("label");
      label.textContent = " Multiple Choice?";

      const choiceContainer = document.createElement("div");
      choiceContainer.style.display = "none";

      const addChoiceBtn = document.createElement("button");
      addChoiceBtn.type = "button";
      addChoiceBtn.textContent = "Add Choice";
      addChoiceBtn.style.display = "none";

      mcBox.addEventListener("change", () => {
        const show = mcBox.checked;
        choiceContainer.style.display = show ? "block" : "none";
        addChoiceBtn.style.display = show ? "inline" : "none";
      });

      addChoiceBtn.addEventListener("click", () => {
        const choice = document.createElement("input");
        choice.type = "text";
        choice.placeholder = "Choice text";
        choice.className = "choice-input";
        choiceContainer.appendChild(choice);
      });

      block.appendChild(qInput);
      block.appendChild(document.createElement("br"));
      block.appendChild(mcBox);
      block.appendChild(label);
      block.appendChild(addChoiceBtn);
      block.appendChild(choiceContainer);

      this.container.appendChild(block);
    });
  }

  bindSubmit(handler) {
    this.form.addEventListener("submit", (e) => {
      e.preventDefault();
      this.model.setTitle(this.titleInput.value.trim());

      const questionBlocks = document.querySelectorAll(".question-block");
      for (const block of questionBlocks) {
        const text = block.querySelector("input[type='text']").value.trim();
        const isMC = block.querySelector("input[type='checkbox']").checked;
        const choiceInputs = block.querySelectorAll(".choice-input");
        const choices = Array.from(choiceInputs).map(input => input.value.trim()).filter(c => c);

        if (text !== "") {
          this.model.addQuestion({
            text,
            isMultipleChoice: isMC,
            choices: isMC ? choices : []
          });
        }
      }

      // this.preview.value = JSON.stringify(this.model.getPayload(), null, 2);
      handler(this.model.getPayload());
    });
  }
}
