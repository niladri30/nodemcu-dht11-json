# nodemcu-dht11-json
Sending DHT11 sensor data (Json format) using Wi-Fi to a registered IP-Port. DNS can be used in place of IP and port

For testing we have used http://posttestserver.com for posting sample data.

JSON output:
-----------
{
	"organizationId": "marvel",
	"deviceType": "Building",
	"assetId": "oscorp_dht11",
	"haName": "Wilson Building",
	"deviceId": "oscorp_device1",
	"site": "Kents Hill",
	"region": "South East England",
	"country": "Something",
	"latitude": 51.518111,
	"longitude": -0.087496,
	"eventTime": "2017-07-12T12:33:33.752Z",
	"properties": {
		"temperature": " 23.00 ",
		"humidity": " 57.00 "
	}
}
