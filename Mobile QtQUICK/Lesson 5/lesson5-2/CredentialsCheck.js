var login = "login";
var password = "password";

// Javascript-функция для проверки данных
function checkCredentials(loginText, passwordText) {

    if (login === loginText && password === passwordText){
        successAnimation.start()
    }
    else
        failAnimation.start()

}
