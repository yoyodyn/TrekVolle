var m_b_MessagingAvailable = false;
var m_b_Debug = true;

   
   

var xhrRequest = function (url, type, callback) 
{
  if (m_b_Debug)
     console.log("[JS:APP] xhr request: " + url );
  var xhr = new XMLHttpRequest();
  xhr.onload = function () 
  {
     callback(this.responseText);
  };  
  xhr.timeout = 30000; 
  xhr.ontimeout = function () 
  {   
     if (m_b_Debug)
         console.log("[JS:APP] Request timed out...");
     Network_SendReply(false);
  }; 
  xhr.onerror = function () 
  { 
     if (m_b_Debug)
         console.log("[JS:APP] Request failed...");   
     Network_SendReply(false); 
  };  
  xhr.open(type, url);
  xhr.send();
   
};


// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   m_b_MessagingAvailable = true;

   if (m_b_Debug)
         console.log("[JS:APP] JS ready...");
   
   // Listen for when an AppMessage is received
   Pebble.addEventListener('appmessage',function(e) 
   {
      if (m_b_MessagingAvailable)
      {
         if ('KEY_TEMPERATURE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Weather info requested...");
            Weather_GetData();
         }
         else if ('KEY_ONLINE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Online info requested...");
            Network_GetData();
         }
         else if ('KEY_BATTERY_CHARGE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Battery info requested...");
            Battery_GetData();
         }
         else
         {
            if (m_b_Debug)
               console.log("[JS:APP] Unkown info requested..." +e.payload.toString());
         }
      }
   });
     
   // Init the battery service
   Battery_Init();
   
   // Get the initial weather
   Weather_GetData();
});




