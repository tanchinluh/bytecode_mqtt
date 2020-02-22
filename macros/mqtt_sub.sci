function str = mqtt_sub(add, topic, id, qos, timeout,username,password)
// Subscribe to MQTT topic
//
//    Copyright 2010-2017 Trity Technologies.
//    
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 2 of the License, or
//    (at your option) any later version.
//    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//    
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/
//
// Calling Sequence
//     str = mqtt_sub(add, topic, id, qos, timeout,username,password)
//
// Parameters
//     add : MQTT Address and port
//     topic : Topic to subscribe to 
//     id : The client identifier 
//     qos : Quality of Service
//     timeout : The length of time to wait for a message in milliseconds.
//     username : Username to login
//     password : Password to login
//     str : Return data in string
//
// Description
//     This function performs a synchronous receive of incoming messages
//
// See also
//     mqtt_pub
//
// Authors
//     Tan C.L.

rhs=argn(2);

// Error Checking
if rhs < 2; error("Expect at least 2 arguments, address and topic"); end    
if rhs < 3; id = 'ScilabSub_'+string(round(rand()*100)); end
if rhs < 4; qos = 0; end
if rhs < 5; timeout = 100; end
if rhs < 6; username = ''; end
if rhs < 7; password = ''; end

if isempty(id); id = 'ScilabPub_'+string(round(rand()*100)); end
if isempty(qos); qos = 0; end
if isempty(timeout); timeout = 100; end
if isempty(username); username = ''; end
if isempty(password); password = ''; end

//h = int_mqtt_client_connect(add,id,username,password);
h = int_mqtt_client_connect(add,id);
int_mqtt_client_sub(h,topic,qos);
sleep(100);
str = int_mqtt_client_receive(h,topic);
int_mqtt_client_disconn(h);
    
endfunction
