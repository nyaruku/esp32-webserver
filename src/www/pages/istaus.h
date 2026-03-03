namespace www {
    namespace pages {
        void istausCallback() {

        }
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
                <div style="margin-bottom: 2rem;">
                    <a href="/istan"><img src="{{gelbAus}}" /></a>
                </div>
                <div>
                    <p>Registered Pages</p>
                    {{pageMap}}
                </div>
            </body>
        </html>
        )";
    }
}
