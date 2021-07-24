#include "window.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainFrame *mainframe = new MainFrame(lan.frame_label);
    mainframe->Show(true);
    list_selection = 1;
    return true;
}