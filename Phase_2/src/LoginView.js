class LoginView {
  constructor(model) {
    this.model = model;
    this.form = document.getElementById("loginForm");
  }

  bindSubmit(handler) {
    this.form.addEventListener("submit", () => {
      const name = document.getElementById("name").value;
      const password = document.getElementById("password").value;
      const mode = this.getMode();
      handler(name, password, mode);
    });
  }

  getMode() {
    return document.getElementById("isRegister").checked ? "register" : "login";
  }

  setFormAction(mode) {
    this.form.action = mode === "register" ? "register.php" : "login.php";
    this.form.method = "POST";
  }
}