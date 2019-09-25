# BikeLocator 

This program takes an already made MySQL database that contains data shown in the query of this repository called bikeLocator.sql and using C++, allows for edits, additions, and removals of data within the terminal. This is all done through a Python wrapper that will help with prompting on the options of actions that can be taken. It also simultaneously opens up a server on another terminal window. This is so that the locations of the Divvy Bikes can be shown on Google Maps. In the C++ executable, there is also a feature that allows for certain stations to be shown on the map (the "write" feature). To see the map, go to localhost:8080/static/map-display.html.

# Instructions 

Follow the prompts on the terminal. Open start.bat to get started.

# Note 

When prompted to enter in a condition, write what you would usually write on SQL, at least what you would write after the WHERE part. </br> 
</br> 
That also means include the quotations for strings and decimal for floats/doubles/decimals. </br> 
</br> 
Also, when you go into the \x64\release folder, you will see the map-display.html file. You will need your own API key in order for Google Maps to work. You will place in the API key in the section that says API-KEY-HERE in the link that is in the script tag in the body of the file.