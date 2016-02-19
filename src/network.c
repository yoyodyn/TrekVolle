#include "network.h"

// Request a net work check
void Network_Request()
{
   // But only if we have a bluetooth connection
   if (!m_b_Bluetooth_ConnectionState)
   {
      m_b_Network_ConnectionState = false;
      Network_Redraw();
      return;
   }
   
   // Debug printout
   if (m_b_Debug)
         printf("[NET][Network_Request] Connection request");
   
   // Send the request
   Communication_Send(KEY_ONLINE);
}

// Redraw the network image
void Network_Redraw()
{
   // Debug printout
   if (m_b_Debug)
         printf("[NET][Network_Redraw] Redrawing");
   
   // We're going to store the color here
   GColor Color;
   if (m_b_Network_ConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }     
   
   // Redraw the image
   Redraw_Image(&m_Image_Network,RESOURCE_ID_IMAGE_NETWORK,Color);
   
}

// Handle network updates here
void Network_Handle_Reply(Tuple *network_tuple)
{
   // Save the net network state
   bool b_ConnectionState = (bool)network_tuple->value->int32;
   
   // Get out of here if there was no change
   if (m_b_Network_ConnectionState == b_ConnectionState)
      return;
   
   // Debug printout
   if (m_b_Debug)
         printf("[NET][Network_Handle_Reply] Handler");
   
   // Save the new state
   m_b_Network_ConnectionState = b_ConnectionState;
   
   bool b_Vibrate = m_b_Network_VibrationEnabled;
   if (m_b_Clock_Sleep && m_b_Clock_SleepEnabled)
   {
      if (m_b_Debug && b_Vibrate)
         printf("[NET][Network_Handle_Reply] Blocked vibration due to sleep mode");
      b_Vibrate = false;
   }
   
   // Vibrate if the user wants us to
   if (m_b_Network_ConnectionState && b_Vibrate)
   {
      if (m_b_Debug)
         printf("[NET][Network_Handle_Reply] Handler: Connection OK");
      vibes_short_pulse();  
   }
   else if (b_Vibrate)
   {
      if (m_b_Debug)
         printf("[NET][Network_Handle_Reply] Handler: Connection failed");
      vibes_double_pulse();
   }
   
   // Redraw the image
   Network_Redraw();
}

// Init the network variables
void Network_Init()
{
   // Debug printout
   if (m_b_Debug)
         printf("[NET][Network_Init] Init");
   // Init the vars
   m_b_Network_ConnectionState = true;

   // Redraw the image
   Network_Redraw();
}

// Deinitthe variables
void Network_DeInit()
{
   if (m_b_Debug)
         printf("[NET][Network_DeInit] Deinit");
}