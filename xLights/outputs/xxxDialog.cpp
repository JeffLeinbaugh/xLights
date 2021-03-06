#include "xxxDialog.h"

//(*InternalHeaders(xxxDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "xxxEthernetOutput.h"
#include "OutputManager.h"
#include "../UtilFunctions.h"

//(*IdInit(xxxDialog)
const long xxxDialog::ID_STATICTEXT1 = wxNewId();
const long xxxDialog::ID_STATICTEXT6 = wxNewId();
const long xxxDialog::ID_SPINCTRL3 = wxNewId();
const long xxxDialog::ID_STATICTEXT2 = wxNewId();
const long xxxDialog::ID_TEXTCTRL1 = wxNewId();
const long xxxDialog::ID_STATICTEXT3 = wxNewId();
const long xxxDialog::ID_SPINCTRL1 = wxNewId();
const long xxxDialog::ID_STATICTEXT4 = wxNewId();
const long xxxDialog::ID_SPINCTRL2 = wxNewId();
const long xxxDialog::ID_CHECKBOX2 = wxNewId();
const long xxxDialog::ID_STATICTEXT5 = wxNewId();
const long xxxDialog::ID_TEXTCTRL2 = wxNewId();
const long xxxDialog::ID_BUTTON_OK = wxNewId();
const long xxxDialog::ID_BUTTON_CANCEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(xxxDialog,wxDialog)
	//(*EventTable(xxxDialog)
	//*)
END_EVENT_TABLE()

xxxDialog::xxxDialog(wxWindow* parent, xxxEthernetOutput* xxx, OutputManager* outputManager, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(xxxDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxStaticText* StaticText9;

	Create(parent, id, _("xxx Ethernet"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Sets up a xxx ethernet output for\na port on a xxx controller."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer2->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_Id = new wxSpinCtrl(this, ID_SPINCTRL3, _T("64001"), wxDefaultPosition, wxDefaultSize, 0, 1, 65535, 64001, _T("ID_SPINCTRL3"));
	SpinCtrl_Id->SetValue(_T("64001"));
	FlexGridSizer2->Add(SpinCtrl_Id, 1, wxALL|wxEXPAND, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("IP Address:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_IPAddress = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl_IPAddress->SetMaxLength(15);
	FlexGridSizer2->Add(TextCtrl_IPAddress, 1, wxALL|wxEXPAND, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_Port = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 16, 1, _T("ID_SPINCTRL1"));
	SpinCtrl_Port->SetValue(_T("1"));
	FlexGridSizer2->Add(SpinCtrl_Port, 1, wxALL|wxEXPAND, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Pixels:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_Pixels = new wxSpinCtrl(this, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 4096, 1, _T("ID_SPINCTRL2"));
	SpinCtrl_Pixels->SetValue(_T("1"));
	FlexGridSizer2->Add(SpinCtrl_Pixels, 1, wxALL|wxEXPAND, 5);
	StaticText9 = new wxStaticText(this, wxID_ANY, _("Suppress duplicate frames"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer2->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox_SuppressDuplicates = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox_SuppressDuplicates->SetValue(false);
	FlexGridSizer2->Add(CheckBox_SuppressDuplicates, 1, wxALL|wxEXPAND, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Description:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText5, 1, wxALL|wxEXPAND, 5);
	TextCtrl_Description = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer2->Add(TextCtrl_Description, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	Button_Ok = new wxButton(this, ID_BUTTON_OK, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_OK"));
	Button_Ok->SetDefault();
	FlexGridSizer3->Add(Button_Ok, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_Cancel = new wxButton(this, ID_BUTTON_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CANCEL"));
	FlexGridSizer3->Add(Button_Cancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&xxxDialog::OnTextCtrl_IPAddressText);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&xxxDialog::OnTextCtrl_DescriptionText);
	Connect(ID_BUTTON_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xxxDialog::OnButton_OkClick);
	Connect(ID_BUTTON_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xxxDialog::OnButton_CancelClick);
	//*)

    _xxx = xxx;
    _outputManager = outputManager;
    SetEscapeId(ID_BUTTON_CANCEL);

    SpinCtrl_Id->SetValue(_xxx->GetId());
    SpinCtrl_Port->SetValue(_xxx->GetPort());
    SpinCtrl_Pixels->SetValue(_xxx->GetChannels() / 3);
    TextCtrl_Description->SetValue(_xxx->GetDescription());
    TextCtrl_IPAddress->SetValue(_xxx->GetIP());
    CheckBox_SuppressDuplicates->SetValue(_xxx->IsSuppressDuplicateFrames());

    ValidateWindow();
}

xxxDialog::~xxxDialog()
{
	//(*Destroy(xxxDialog)
	//*)
}

void xxxDialog::OnButton_OkClick(wxCommandEvent& event)
{
    _xxx->SetIP(TextCtrl_IPAddress->GetValue().ToStdString());
    _xxx->SetId(SpinCtrl_Id->GetValue());
    _xxx->SetPort(SpinCtrl_Port->GetValue());
    _xxx->SetChannels(SpinCtrl_Pixels->GetValue()*3);
    _xxx->SetDescription(TextCtrl_Description->GetValue().ToStdString());
    _xxx->SetSuppressDuplicateFrames(CheckBox_SuppressDuplicates->IsChecked());
    _outputManager->SomethingChanged();
    EndDialog(wxID_OK);
}

void xxxDialog::OnTextCtrl_IPAddressText(wxCommandEvent& event)
{
    ValidateWindow();
}

void xxxDialog::OnButton_CancelClick(wxCommandEvent& event)
{
    EndDialog(wxID_CANCEL);
}

void xxxDialog::OnTextCtrl_DescriptionText(wxCommandEvent& event)
{
    ValidateWindow();
}

void xxxDialog::ValidateWindow() {
    if (TextCtrl_IPAddress->GetValue().IsEmpty() ||
        !IsIPValidOrHostname(TextCtrl_IPAddress->GetValue().ToStdString(), true))
    {
        Button_Ok->Enable(false);
    }
    else {
        Button_Ok->Enable();
    }
}