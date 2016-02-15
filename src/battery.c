#include "battery.h"

// Phone battery vars
struct BatteryData
{
   TextLayer*   l_Text;
   BitmapLayer* l_Image;
   GBitmap*     bmp_Image;
   int i_BatteryLevel;
   bool b_ChargingState;
   bool b_FirstValue;
   char s_Text[5];
};

struct BatteryData m_BatteryPhone;
struct BatteryData m_BatteryPebble;

void BatteryRedrawImage(struct BatteryData* Battery,int Image_ID,GColor Color)
{
   if (m_b_Debug)
      printf("[BATT] Redrawing battery image\n");
   Redraw_Image(Battery->l_Image,Battery->bmp_Image,Image_ID,Color);
}

void Battery_RequestPhone()
{
   if (!m_b_Bluetooth_ConnectionState)
      return;
   
   if (m_b_Debug)
      printf("[BATT] Phone battery requested\n");
   // Begin dictionary
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);

   // Add a key-value pair
   dict_write_uint8(iter, KEY_BATTERY_CHARGE, 0);

   // Send the message!
   app_message_outbox_send();
}



void Battery_Redraw(struct BatteryData* Battery)
{
   if (Battery->l_Text == NULL)
      return;
   
   if (m_b_Debug)
      printf("[BATT] Redrawing battery\n");
  
   if (Battery->i_BatteryLevel < 30)
   {
      text_layer_set_text_color(Battery->l_Text, Color_BatteryLow);
      BatteryRedrawImage(Battery,RESOURCE_ID_IMAGE_BATTERY_LOW,Color_BatteryLow);
   }
   else if (Battery->i_BatteryLevel < 60)
   {
      text_layer_set_text_color(Battery->l_Text, Color_Text);
      BatteryRedrawImage(Battery,RESOURCE_ID_IMAGE_BATTERY_MID,Color_Image);
   }
   else
   {
      text_layer_set_text_color(Battery->l_Text, Color_Text);
      BatteryRedrawImage(Battery,RESOURCE_ID_IMAGE_BATTERY_HIGH,Color_Image);
   }
   
   if (Battery->b_ChargingState )
   {
      text_layer_set_text_color(Battery->l_Text, Color_Charging);
   }
   
   if (Battery->i_BatteryLevel > 99)
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d", Battery->i_BatteryLevel);
   else
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d%%", Battery->i_BatteryLevel);
   text_layer_set_text(Battery->l_Text, Battery->s_Text);
   layer_mark_dirty(text_layer_get_layer(Battery->l_Text));
   
}

static void Battery_Handle_Pebble(BatteryChargeState charge_state) 
{
   if (m_b_Debug)
      printf("[BATT] Pebble battery handler: %d %d\n",charge_state.charge_percent,(int)charge_state.is_charging);
   m_BatteryPebble.i_BatteryLevel = charge_state.charge_percent;
   m_BatteryPebble.b_ChargingState = charge_state.is_charging;
   Battery_Redraw(&m_BatteryPebble);
}

void Battery_Handle_Phone(int i_BatteryLevel,bool b_ChargingState)
{
   if (m_b_Debug)
      printf("[BATT] Phone battery handler: %d %d\n",i_BatteryLevel,(int)b_ChargingState);
   show_PhoneBattery(true);
   
   m_BatteryPhone.i_BatteryLevel = i_BatteryLevel;
   m_BatteryPhone.b_ChargingState = b_ChargingState;
   Battery_Redraw(&m_BatteryPhone);
}

void Battery_RedrawAll()
{
   if (m_b_Debug)
      printf("[BATT] Redrawing everything\n");
   Battery_Redraw(&m_BatteryPhone);
   Battery_Redraw(&m_BatteryPebble);
}


void Battery_Init()
{
   if (m_b_Debug)
      printf("[BATT] Init\n");
   m_BatteryPebble.l_Text =  GetBatteryTextLayerPebble();
   m_BatteryPebble.l_Image = GetBatteryImageLayerPebble();
   m_BatteryPhone.l_Text =   GetBatteryTextLayerPhone();
   m_BatteryPhone.l_Image =  GetBatteryImageLayerPhone();
   show_PhoneBattery(false);
   battery_state_service_subscribe(Battery_Handle_Pebble);
   Battery_Handle_Pebble(battery_state_service_peek());
}

void Battery_Deinit()
{
   if (m_b_Debug)
      printf("[BATT] Deinit\n");
   battery_state_service_unsubscribe();
   if (m_BatteryPhone.bmp_Image)
   {
      gbitmap_destroy(m_BatteryPhone.bmp_Image);
      m_BatteryPhone.bmp_Image = NULL;
   }
      
   if (m_BatteryPebble.bmp_Image)
   {
      gbitmap_destroy(m_BatteryPebble.bmp_Image);
      m_BatteryPebble.bmp_Image = NULL;
   }
      
}