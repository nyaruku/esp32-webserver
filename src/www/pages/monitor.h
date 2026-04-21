namespace www {
    namespace pages {
        std::string monitor = R"(
            <html>
                <head>
                    <meta charset="utf-8">
                </head>
                <body>
                    <div>
                        <h1>ESP8266 DHT Server</h2>
                        <p>
                            <span class="dht-labels">Temperature</span>
                            <span id="temperature">Start</span>
                            <sup class='units'>°C</sup>
                        </p>
                    </div>
                </body>
                <script>
                    function fetchTemperature() {
                        fetch('/rawTemperature')
                            .then(response => response.text())
                            .then(data =>
                                {
                                let temperature = Number.parseFloat(data).toFixed(1);
                                document.getElementById("temperature").innerHTML = temperature;
                            })
                    }                
                    setInterval(function () {
                        fetchTemperature();
                    }, 1000);
                </script>
            </html>
        )";
    }
}