#include <wx-3.1/wx/stattext.h>
#include <wx-3.1/wx/tglbtn.h>
#include <wx-3.1/wx/clipbrd.h>
#include <stdlib.h>
#include <iostream>
#include "languages.h"

en_GB lan;

#define calc_mode_ID 100
#define money_in_ID 102
#define mwst_choose_ID 103
#define calculate_ID 104
#define result_ID 105
#define copy_ID 106

wxString money_in_value;
double money_in_value_num;
wxString selection_type;
double calculated_value;
double calculated_value_prec;
wxString calculated_value_str;
bool state_mode = false; //false is netto, true is brutto
bool state_mwst = false; //false is 19%, true is 7%
int counter_col = 0;
int list_selection;
wxString col_text;

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
    wxToggleButton *calc_mode;
    wxTextCtrl *money_in;
    wxToggleButton *mwst_choose;

private:
    void onModeChanged(wxCommandEvent &event);
    void onTextChanged(wxCommandEvent &event);
    void onMwStChanged(wxCommandEvent &event);
    void onCalcPressed(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

class RightPanel : public wxPanel
{
public:
    RightPanel(wxPanel *parent);
    wxListBox *result;
    wxButton *copy;
private:
    void onCopyPressed(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);
    LeftPanel *m_lp;
    RightPanel *m_rp;
    wxPanel *m_parent;
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 600))
{
    m_parent = new wxPanel(this, wxID_ANY);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    m_lp = new LeftPanel(m_parent);
    m_rp = new RightPanel(m_parent);
    hbox->Add(m_lp, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_rp, 1, wxEXPAND | wxALL, 5);
    m_parent->SetSizer(hbox);
    SetIcon(wxIcon(wxT("/home/simonium/.icons/BigSur/apps/scalable/xfce-ui.svg")));
    this->Centre();
}

LeftPanel::LeftPanel(wxPanel *parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
    wxBoxSizer *lp_sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *text_mode = new wxStaticText(this, wxID_ANY, lan.mode_label);
    calc_mode = new wxToggleButton(this, calc_mode_ID, lan.netto_label, wxDefaultPosition, wxSize(130, 40));
    wxStaticText *command = new wxStaticText(this, wxID_ANY, lan.command_label);
    money_in = new wxTextCtrl(this, money_in_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize);
    wxStaticText *text_mwst = new wxStaticText(this, wxID_ANY, lan.text_mwst_label);
    mwst_choose = new wxToggleButton(this, mwst_choose_ID, lan.nineteen_percent_label, wxDefaultPosition, wxSize(100, 30));
    wxButton *calculate = new wxButton(this, calculate_ID, lan.calculate_label);
    lp_sizer->AddStretchSpacer();
    lp_sizer->Add(text_mode, 0, wxALL | wxALIGN_CENTER, 1);
    lp_sizer->Add(calc_mode, 0, wxALL | wxALIGN_CENTER, 20);
    lp_sizer->Add(command, 0, wxALL | wxALIGN_CENTER, 1);
    lp_sizer->Add(money_in, 0, wxALL | wxALIGN_CENTER, 20);
    lp_sizer->Add(text_mwst, 0, wxALL | wxALIGN_CENTER, 1);
    lp_sizer->Add(mwst_choose, 0, wxALL | wxALIGN_CENTER, 20);
    lp_sizer->Add(calculate, 0, wxALL | wxALIGN_CENTER, 20);
    lp_sizer->AddStretchSpacer();
    SetSizer(lp_sizer);
}

wxBEGIN_EVENT_TABLE(LeftPanel, wxPanel)
    EVT_TOGGLEBUTTON(calc_mode_ID, LeftPanel::onModeChanged)
    EVT_BUTTON(calculate_ID, LeftPanel::onCalcPressed)
    EVT_TEXT(money_in_ID, LeftPanel::onTextChanged)
    EVT_TOGGLEBUTTON(mwst_choose_ID, LeftPanel::onMwStChanged)
wxEND_EVENT_TABLE()

RightPanel::RightPanel(wxPanel *parent) : wxPanel(parent, -1, wxDefaultPosition, wxSize(500, 600), wxBORDER_SUNKEN)
{
    wxBoxSizer *textSizer = new wxBoxSizer(wxVERTICAL);
    result = new wxListBox(this, result_ID, wxDefaultPosition, wxSize(500, 490));
    copy = new wxButton(this, copy_ID, lan.copy_label);
    textSizer->AddStretchSpacer();
    textSizer->Add(result, 0, wxALL | wxALIGN_CENTER, 15);
    textSizer->Add(copy, 0, wxALL | wxALIGN_RIGHT, 5);
    textSizer->AddStretchSpacer();
    SetSizer(textSizer);
}

wxBEGIN_EVENT_TABLE(RightPanel, wxPanel)
    EVT_BUTTON(copy_ID, RightPanel::onCopyPressed)
wxEND_EVENT_TABLE()

void LeftPanel::onModeChanged(wxCommandEvent &WXUNUSED(event))
{
    state_mode = calc_mode->GetValue();
    if (state_mode == 1)
        calc_mode->SetLabel(lan.brutto_label);
    if (state_mode == 0)
        calc_mode->SetLabel(lan.netto_label);
}

void LeftPanel::onMwStChanged(wxCommandEvent &WXUNUSED(event))
{
    state_mwst = mwst_choose->GetValue();
    if (state_mwst == 1)
        mwst_choose->SetLabel(lan.seven_percent_label);
    if (state_mwst == 0)
        mwst_choose->SetLabel(lan.nineteen_percent_label);
}

void LeftPanel::onTextChanged(wxCommandEvent &WXUNUSED(event))
{
    money_in_value = money_in->GetValue();
}

void LeftPanel::onCalcPressed(wxCommandEvent &WXUNUSED(event))
{
    money_in_value_num = atof(money_in_value.c_str());
    std::cout << money_in_value_num << std::endl;
    if(state_mode == 0 && state_mwst == 0) calculated_value = money_in_value_num / 1.19;
    if(state_mode == 0 && state_mwst == 1) calculated_value = money_in_value_num / 1.07;
    if(state_mode == 1 && state_mwst == 0) calculated_value = money_in_value_num * 1.19;
    if(state_mode == 1 && state_mwst == 1) calculated_value = money_in_value_num * 1.07;
    calculated_value_prec = (int)(calculated_value*100+0.5)/100.0; //on two digits after comma
    calculated_value_str << calculated_value_prec;
    MainFrame *comm = (MainFrame *)m_parent->GetParent();
    const wxString *to_col = &calculated_value_str;
    comm->m_rp->result->InsertItems(1, to_col, counter_col);
    calculated_value_str = "";
    counter_col++;
}

void RightPanel::onCopyPressed(wxCommandEvent &WXUNUSED(event))
{
    list_selection = result->GetSelection();
    col_text = result->GetString(list_selection);
    wxCharBuffer buf=col_text.ToUTF8();
    const char* col_text_2(buf.data());
    std::cout << list_selection << " " << col_text_2 << std::endl;
    if(wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(col_text));
        wxTheClipboard->Close();
    }
    else
    {
        std::cout << "error opening clipboard" << std::endl;
    }
}