class LoginModel {
  constructor() {
    this.name = "";
    this.password = "";
    this.response = null;
  }

  setCredentials(name, password) {
    this.name = name;
    this.password = password;
  }
}