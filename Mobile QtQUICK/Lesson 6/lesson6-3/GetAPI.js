function getInfo() {
    var xmlhttp = new XMLHttpRequest();
    
    var apiKey = "c1b7d8184ef043bfb6812b40256cd102";
    var url = "http://api.weatherbit.io/v2.0/current?city=Nizhniy Novgorod&country=RU&key=" + apiKey;
   
    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState === XMLHttpRequest.DONE && xmlhttp.status === 200) {
            //print(xmlhttp.responseText)
            parseStaff(xmlhttp.responseText);
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}
// Парсинг JSON ответа от сервера и запись значений
function parseStaff(response) {
    var jsonObj = JSON.parse(response);
    var count = jsonObj.count
    var data = jsonObj.data[0]

    city.text = data.city_name
    temp.text = data.app_temp + " °C"
    weather.text = data.weather.description
    wind_cdir_full.text = data.wind_cdir_full + ", "
    wind_spd.text = data.wind_spd.toFixed(1) + " m/sec"
}
    
/*
{
    "count":1,
    "data":[{
        "app_temp":11.7,
        "aqi":46,
        "city_name":"City of London",
        "clouds":90,
        "country_code":"GB",
        "datetime":"2023-03-17:10",
        "dewpt":9.9,
        "dhi":96.04,
        "dni":795.4,
        "elev_angle":30.78,
        "ghi":496.62,
        "gust":6.17,
        "h_angle":-30,
        "lat":51.51279,
        "lon":-0.09184,
        "ob_time":"2023-03-17 10:20",
        "pod":"d",
        "precip":0,
        "pres":1001.9507,
        "rh":90,
        "slp":1003.50555,
        "snow":0,
        "solar_rad":212,
        "sources":["analysis","AV975"],
        "state_code":"ENG",
        "station":"AV975",
        "sunrise":"06:08",
        "sunset":"18:08",
        "temp":11.7,
        "timezone":"Europe/London",
        "ts":1679048440,
        "uv":1.270802,
        "vis":10,
        "weather":{"description":"Broken clouds","icon":"c03d","code":803},
        "wind_cdir":"SSW",
        "wind_cdir_full":"south-southwest",
        "wind_dir":198,
        "wind_spd":3.6
    }]
}
*/
