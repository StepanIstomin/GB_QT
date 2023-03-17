function getInfo() {
    var xmlhttp = new XMLHttpRequest();

     // получаем дату и время
    var date  = new Date();
     var day = date.getDate();
    if (day < 10)
        day = "0" + day
    var month = date.getMonth();
    if (month < 10)
        month = "0" + month
    var today = day + "/" + month + "/" + date.getFullYear();
    //print(today);

    var url = "http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1="+today+"&date_req2="+today+"&VAL_NM_RQ=R01235";

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState === XMLHttpRequest.DONE && xmlhttp.status === 200) {
            print(xmlhttp.responseText)
            parse(xmlhttp.responseText);
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}
// Парсинг строки ответа от сервера и запись значений
function parse(response) {
    var rate = response.slice(response.indexOf('<Value>') + 7, response.indexOf('</Value>'))
    rate = rate.replace(/\,/g, '.');

    if (usdInput.text === "" && rubInput.text !== "" || usdInput.text !== "" && rubInput.text !== "")
        usdInput.text = (rubInput.text / rate).toFixed(2);
    if (usdInput.text !== "" && rubInput.text === "")
        rubInput.text = (usdInput.text * rate).toFixed(2);
}
