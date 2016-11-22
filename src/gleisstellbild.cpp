//******************************************************************
// gleisstellbild.cpp
//******************************************************************

#include "gleisstellbild.h"

#include <iostream>
#include <vector>
#include <string>
#include "canbus.h"
#include "railroad.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------

GleisStellBild::GleisStellBild()
{
  std::cout << std::endl << "********** railCONTROL ************\n";

  // Setup GUI
  SetupGui();

  // Setup regular check if CAN message arrived
  Glib::signal_timeout().connect(
    sigc::mem_fun(*this, &GleisStellBild::timeout_handler), 1000);
}

GleisStellBild::~GleisStellBild()
{
}

//--------------------------------------------------------------------
// Button handler
//--------------------------------------------------------------------
void GleisStellBild::on_button_clicked(int data)
{
  std::cout << "Weiche " << data << " clicked" << std::endl;
  int state = turnout[data].get_state();
  turnout[data].set_state(!state);
};


//--------------------------------------------------------------------
// Timeout handler checks CAN messages
//--------------------------------------------------------------------
bool GleisStellBild::timeout_handler()
{
  //std::cout << "timeout..." << std::endl;
  struct can_frame frame;
  if (railbus.get_msg(frame) > 0)
  {
    // Update label with CAN message
    std::stringstream message_stream;
    message_stream << "CAN_ID: " << std::showbase << std::hex << frame.can_id;
    std::string message = message_stream.str();
    message_stream.str(std::string());
    m_ID.set_text(message);


    message_stream << "\nDLC: " << std::hex << int(frame.can_dlc);
    message = message_stream.str();
    message_stream.str(std::string());
    m_DLC.set_text(message);

    for (int i = 0; i < int(frame.can_dlc); i++)
    {
      message_stream << "\nData" << std::dec << i << ": " << std::hex << int(frame.data[i]);
      message = message_stream.str();
      message_stream.str(std::string());
      m_Data[i].set_text(message);
    }

    for (int i = int(frame.can_dlc); i < 8; i++)
    {
      message_stream << "\n";
      message = message_stream.str();
      message_stream.str(std::string());
      m_Data[i].set_text(message);
    }
  }
  return true;
};


//----------------------------------------------------------------
// Setup GUI
//----------------------------------------------------------------
int GleisStellBild::SetupGui()
{
  set_title("Gleisstellbild");
  set_border_width(50); // Sets the border width of the window

  add(m_Maingrid);

  m_Label.set_text("Bruno's RailroadController");

  m_Weichenframe.set_label("Turnouts");
    // Button0
    m_button0.set_label("1");
    m_button0.signal_clicked().connect(sigc::bind<int>(
          sigc::mem_fun(*this, &GleisStellBild::on_button_clicked), 0));
    m_Weichentaster.pack_start(m_button0, Gtk::PACK_EXPAND_WIDGET,20);
    m_button0.show();

    // Button1
    m_button1.set_label("2");
    m_button1.signal_clicked().connect(sigc::bind<int>(
          sigc::mem_fun(*this, &GleisStellBild::on_button_clicked), 1));
    m_Weichentaster.pack_start(m_button1, Gtk::PACK_EXPAND_WIDGET,20);
    m_button1.show();

    // Button2
    m_button2.set_label("3");
    m_button2.signal_clicked().connect(sigc::bind<int>(
          sigc::mem_fun(*this, &GleisStellBild::on_button_clicked), 2));
    m_Weichentaster.pack_start(m_button2, Gtk::PACK_EXPAND_WIDGET,20);
    m_button2.show();

  m_Weichentaster.set_border_width(20);
  m_Weichentaster.show();

  m_Weichenframe.add(m_Weichentaster);
  m_Label.show();
  m_Weichenframe.show();


  m_Messageframe.set_label("Received CAN Message");
    m_Messagebox.pack_start(m_ID); m_ID.show();
    m_Messagebox.pack_start(m_DLC); m_DLC.show();
    for (int i = 0; i < 8; i++)
    {
      m_Messagebox.pack_start(m_Data[i]);
      m_Data[i].show();
    }

    m_Messagebox.set_border_width(20);
    m_Messagebox.show();

    m_Messageframe.add(m_Messagebox);
    m_Messageframe.show();





  m_Maingrid.pack_start(m_Label, Gtk::PACK_EXPAND_WIDGET, 20);
  m_Maingrid.pack_start(m_Weichenframe, Gtk::PACK_EXPAND_WIDGET, 20);
  m_Maingrid.pack_start(m_Messageframe, Gtk::PACK_EXPAND_WIDGET, 20);
  m_Maingrid.show();
  return 0;
};
