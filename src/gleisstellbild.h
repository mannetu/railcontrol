#ifndef GLEISSTELLBILD_H
#define GLEISSTELLBILD_H
//******************************************************************
// gleisstellbild.h
//******************************************************************


#include <gtkmm.h>


class Canbus;

//-------------------------------------------------------------
// Class GleisStellBild
//-------------------------------------------------------------

class GleisStellBild : public Gtk::Window
{
public:
  GleisStellBild();
  ~GleisStellBild();

protected:
  void on_button_clicked(int); // Signal handler
  bool timeout_handler(); // Setup regular check if CAN message arrived

  // Member widgets:
  Gtk::VBox m_Maingrid;

    Gtk::Label m_Label;
    Gtk::Frame m_Weichenframe;
      Gtk::HBox m_Weichentaster;
      Gtk::Button m_button0, m_button1, m_button2;

    Gtk::Label m_Message;
    Gtk::Frame m_Messageframe;
      Gtk::VBox m_Messagebox;
      Gtk::Label m_ID;
      Gtk::Label m_DLC;
      Gtk::Label m_Data[8];

private:
  int SetupGui();
};

#endif // GLEISSTELLBILD_H
