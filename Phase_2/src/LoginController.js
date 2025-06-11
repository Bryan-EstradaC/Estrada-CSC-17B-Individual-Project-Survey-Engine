class LoginController {
  constructor(model, view) {
    this.model = model;
    this.view = view;
  }

  init() {
    // Only sets form action and method based on selected mode
    this.view.bindSubmit((name, password, mode) => {
      this.model.setCredentials(name, password);
      this.view.setFormAction(mode);
    });
  }
}

