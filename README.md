PocketRunnerPebble
==================

Pebble app that acompanies the [PocketRunner project](https://github.com/rickyman20/PocketRunner). This app allows a user to log a run, using a fixed lap length, in either feet, miles, kilometers or meters. It works like a kilometer, except with a distance measurement. All the configuration for this app is done on the android app and is sent to the pebble via Pebble's `AppMessage` API. At the end of the run, when the user presses the done button, the run is sent to the Android app through more `AppMessage` packages. An explanation of how this is done follows:

NOTE: First off, all `AppMessage` message keys used can be found in the file [message_keys.h](https://github.com/rickyman20/PocketRunnerPebble/blob/master/src/message_keys.h). 

Ok, now to the explanation. Keys 0-5 are all used to receive the configuration data. Basically, the Pebble app first sends a message with key `REQUEST_INITIAL` with nothing. This simply tells the android app to return all the data. The android app will then proceed to send out the 5 other keys with their respective data (`LAP_LENGTH_KEY`, `UNITS_KEY`, `USE_DISTANCE_ALARM_KEY`, `END_DISTANCE_KEY` and `END_TIME_KEY`). The Android app will also send it when the app is opened and when the settings are changed.

The way each run is sent is more elaborate. When the done button is pressed, the Pebble app has to send a `RUN_OPEN` message with no data. The android app should then respond with a `RUN_UUID_DEFINE` message, containing the 16 bytes of a UUID used to identify this run. Once both the ack for the `RUN_OPEN` and the UUID are received, the run data will begin to be sent. It is important to note that every package will also send the run UUID in the form of the message key `RUN_UUID_ACK`. Firstly, a package with `RUN_TIME` and `RUN_LAPS` is sent, with the run duration and the number of laps. Next, inidivual packages are sent with each lap time, using the message key `RUN_LAP_TIME`. The final package sent has the key `RUN_CLOSE` with simply signifies an end of transmition, stating that it is safe to save the run.

Links
-----
* [This app in the Pebble app marketplace](https://apps.getpebble.com/applications/54ad8b9d32203eb1200000b3)
* [Android app in the Google Play Store](https://play.google.com/store/apps/details?id=com.foxtailgames.pocketrunner)
* [Android app on Github](https://github.com/rickyman20/PocketRunner)
