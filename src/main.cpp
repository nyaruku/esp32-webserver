#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WebServer.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "header/mustache.h"
#include "header/routes.h"
#include "www/resources/images.h"

#include "env.h"

WebServer server(SERVER_PORT);

// 192.168.4.100
IPAddress local_ip(192,168,4,100);
IPAddress gateway(192,168,4,254);
IPAddress netmask(255,255,255,0);

#define DHTPIN 35
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void handlePage();
void handleNotFound();

// Requires DHT
#include "www/pages.h"

void initMustache() {
    mustache::storage.clear();
    mustache::set("ipAddress", local_ip.toString().c_str());
    mustache::set("gateway", gateway.toString().c_str());
    mustache::set("netmask", netmask.toString().c_str());
    // mustache::set("logo", www::images::logo.c_str());
    mustache::set("gelbAus", www::images::gelbAus.c_str());
    mustache::set("gelbAn", www::images::gelbAn.c_str());

    std::string pageMapContent = "";
    for (const std::map<std::string, std::string> map : routes::storage) {
        for (const auto& [key, value] : map) {
            pageMapContent += "<a href=\"" + key + "\">" + key + "</a><br>";
        }
    }
    mustache::set("pageMap", pageMapContent.c_str());
}

void initPages() {
    routes::storage.clear();
    routes::set("/", www::pages::index);
    routes::set("/istaus", www::pages::istaus);
    routes::set("/istan", www::pages::istan);
    routes::set("/monitor", www::pages::monitor);
    routes::set("/rawTemperature", www::pages::monitor);
}

void setup() {
    dht.begin();
    pinMode(39, OUTPUT);

    WiFi.softAPConfig(local_ip, gateway, netmask);
    boolean result = WiFi.softAP(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL, WIFI_HIDDEN);  

    // Register routes/pages
    initPages();

    // Register mustaches
    initMustache();

    if (result == true) {
        for (const std::map<std::string, std::string> map : routes::storage) {
            for (const auto& [key, value] : map) {
                server.on(key.c_str(), handlePage);
            }
        }
        server.begin();
    }
}

void loop() {
    server.handleClient();
}

void handlePage() {
    if (server.uri() == "/rawTemperature") {
        server.send(200, "text/plain", std::to_string(dht.readTemperature()).c_str());
    }  

    if (server.uri() == "/istan") {
        digitalWrite(39, HIGH);
    }  
    if (server.uri() == "/istaus") {
        digitalWrite(39, LOW);
    }  

    std::string content = routes::get(server.uri().c_str());
    if (content == ""){
        server.send(404, "text/plain", "404 Not found");
    } else {
        server.send(200, "text/html", mustache::renderMustache(content).c_str());
    }
}