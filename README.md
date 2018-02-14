<h1>Wippschalter</h1>

Der Wippschalter befindet sich auf der rechten Seite der Leinwand am Kabelkanal. Dadurch ist es nun auch ohne MQTT Client möglich die Leinwand hoch und runter zu fahren. 

<h1>Funktionsweise</h1>

Der Taster spricht ebenfalls MQTT. Dabei published er die Werte "up", "down" und "halt" in das 
Topic foobar/oben/lounge/leinwand/action.



