namespace www {
    namespace pages {
        std::string istaus = R"(
        <html>
            <body>
                <h1>ESP32 Web Server</h1>
                <p>Informationen</p>
                <ul>
                    <li>IP Addresse: <span>{{ipAddress}}</span></li>
                    <li>Gateway: <span>{{gateway}}</span></li>
                    <li>Netmask: <span>{{netmask}}</span></li>
                </ul>
                <div>
                    <a href="/istan"><img src="{{gelbAus}}" /></a>
                </div>
            </body>
        </html>
        )";
    }
}
