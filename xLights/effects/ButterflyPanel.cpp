#include "ButterflyPanel.h"
#include "../../include/padlock16x16-blue.xpm"
#include "EffectPanelUtils.h"

//(*InternalHeaders(ButterflyPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/bitmap.h>
#include <wx/slider.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(ButterflyPanel)
const long ButterflyPanel::ID_CHOICE_Butterfly_Colors = wxNewId();
const long ButterflyPanel::ID_BITMAPBUTTON_CHOICE_Butterfly_Color = wxNewId();
const long ButterflyPanel::ID_SLIDER_Butterfly_Style = wxNewId();
const long ButterflyPanel::IDD_TEXTCTRL_Butterfly_Style = wxNewId();
const long ButterflyPanel::ID_BITMAPBUTTON_SLIDER_Butterfly_Style = wxNewId();
const long ButterflyPanel::ID_SLIDER_Butterfly_Chunks = wxNewId();
const long ButterflyPanel::IDD_TEXTCTRL_Butterfly_Chunks = wxNewId();
const long ButterflyPanel::ID_BITMAPBUTTON_SLIDER_Butterfly_Chunks = wxNewId();
const long ButterflyPanel::ID_SLIDER_Butterfly_Skip = wxNewId();
const long ButterflyPanel::IDD_TEXTCTRL_Butterfly_Skip = wxNewId();
const long ButterflyPanel::ID_BITMAPBUTTON15 = wxNewId();
const long ButterflyPanel::ID_SLIDER_Butterfly_Speed = wxNewId();
const long ButterflyPanel::IDD_TEXTCTRL_Butterfly_Speed = wxNewId();
const long ButterflyPanel::ID_BITMAPBUTTON_SLIDER_Butterfly_Skip = wxNewId();
const long ButterflyPanel::ID_CHOICE_Butterfly_Direction = wxNewId();
const long ButterflyPanel::ID_BITMAPBUTTON9 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ButterflyPanel,wxPanel)
	//(*EventTable(ButterflyPanel)
	//*)
END_EVENT_TABLE()

ButterflyPanel::ButterflyPanel(wxWindow* parent)
{
	//(*Initialize(ButterflyPanel)
	wxChoice* Choice_Butterfly_Colors;
	wxStaticText* StaticText175;
	wxBitmapButton* BitmapButton_ButterflyStyle;
	wxTextCtrl* TextCtrl16;
	wxStaticText* StaticText26;
	wxSlider* Slider_Butterfly_Chunks;
	wxStaticText* StaticText58;
	wxStaticText* StaticText27;
	wxBitmapButton* BitmapButton8;
	wxBitmapButton* BitmapButton1;
	wxBitmapButton* BitmapButton_ButterflySkip;
	wxTextCtrl* TextCtrl18;
	wxTextCtrl* TextCtrl17;
	wxBitmapButton* BitmapButton_ButterflyColors;
	wxStaticText* StaticText28;
	wxSlider* Slider8;
	wxTextCtrl* TextCtrl25;
	wxChoice* Choice_Butterfly_Direction;
	wxFlexGridSizer* FlexGridSizer36;
	wxSlider* Slider_Butterfly_Style;
	wxStaticText* StaticText25;
	wxBitmapButton* BitmapButton_ButterflyChunks;
	wxSlider* Slider_Butterfly_Skip;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer36 = new wxFlexGridSizer(0, 4, 0, 0);
	FlexGridSizer36->AddGrowableCol(1);
	StaticText25 = new wxStaticText(this, wxID_ANY, _("Colors"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer36->Add(StaticText25, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	Choice_Butterfly_Colors = new wxChoice(this, ID_CHOICE_Butterfly_Colors, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Butterfly_Colors"));
	Choice_Butterfly_Colors->SetSelection( Choice_Butterfly_Colors->Append(_("Rainbow")) );
	Choice_Butterfly_Colors->Append(_("Palette"));
	FlexGridSizer36->Add(Choice_Butterfly_Colors, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer36->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton_ButterflyColors = new wxBitmapButton(this, ID_BITMAPBUTTON_CHOICE_Butterfly_Color, padlock16x16_blue_xpm, wxDefaultPosition, wxSize(13,13), wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON_CHOICE_Butterfly_Color"));
	BitmapButton_ButterflyColors->SetDefault();
	BitmapButton_ButterflyColors->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	FlexGridSizer36->Add(BitmapButton_ButterflyColors, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	StaticText26 = new wxStaticText(this, wxID_ANY, _("Style"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer36->Add(StaticText26, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Butterfly_Style = new wxSlider(this, ID_SLIDER_Butterfly_Style, 1, 1, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly_Style"));
	FlexGridSizer36->Add(Slider_Butterfly_Style, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	TextCtrl16 = new wxTextCtrl(this, IDD_TEXTCTRL_Butterfly_Style, _("1"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("IDD_TEXTCTRL_Butterfly_Style"));
	TextCtrl16->SetMaxLength(1);
	FlexGridSizer36->Add(TextCtrl16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton_ButterflyStyle = new wxBitmapButton(this, ID_BITMAPBUTTON_SLIDER_Butterfly_Style, padlock16x16_blue_xpm, wxDefaultPosition, wxSize(13,13), wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON_SLIDER_Butterfly_Style"));
	BitmapButton_ButterflyStyle->SetDefault();
	BitmapButton_ButterflyStyle->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	FlexGridSizer36->Add(BitmapButton_ButterflyStyle, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	StaticText27 = new wxStaticText(this, wxID_ANY, _("Bkgrd Chunks"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer36->Add(StaticText27, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Butterfly_Chunks = new wxSlider(this, ID_SLIDER_Butterfly_Chunks, 1, 1, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly_Chunks"));
	FlexGridSizer36->Add(Slider_Butterfly_Chunks, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	TextCtrl17 = new wxTextCtrl(this, IDD_TEXTCTRL_Butterfly_Chunks, _("1"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("IDD_TEXTCTRL_Butterfly_Chunks"));
	TextCtrl17->SetMaxLength(2);
	FlexGridSizer36->Add(TextCtrl17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton_ButterflyChunks = new wxBitmapButton(this, ID_BITMAPBUTTON_SLIDER_Butterfly_Chunks, padlock16x16_blue_xpm, wxDefaultPosition, wxSize(13,13), wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON_SLIDER_Butterfly_Chunks"));
	BitmapButton_ButterflyChunks->SetDefault();
	BitmapButton_ButterflyChunks->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	FlexGridSizer36->Add(BitmapButton_ButterflyChunks, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	StaticText28 = new wxStaticText(this, wxID_ANY, _("Bkgrd Skip"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer36->Add(StaticText28, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Butterfly_Skip = new wxSlider(this, ID_SLIDER_Butterfly_Skip, 2, 2, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly_Skip"));
	FlexGridSizer36->Add(Slider_Butterfly_Skip, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	TextCtrl18 = new wxTextCtrl(this, IDD_TEXTCTRL_Butterfly_Skip, _("2"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("IDD_TEXTCTRL_Butterfly_Skip"));
	TextCtrl18->SetMaxLength(2);
	FlexGridSizer36->Add(TextCtrl18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton1 = new wxBitmapButton(this, ID_BITMAPBUTTON15, padlock16x16_blue_xpm, wxDefaultPosition, wxSize(13,13), wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON15"));
	BitmapButton1->SetDefault();
	BitmapButton1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	FlexGridSizer36->Add(BitmapButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText175 = new wxStaticText(this, wxID_ANY, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer36->Add(StaticText175, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Slider8 = new wxSlider(this, ID_SLIDER_Butterfly_Speed, 10, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly_Speed"));
	FlexGridSizer36->Add(Slider8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	TextCtrl25 = new wxTextCtrl(this, IDD_TEXTCTRL_Butterfly_Speed, _("10"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(20,-1)), 0, wxDefaultValidator, _T("IDD_TEXTCTRL_Butterfly_Speed"));
	TextCtrl25->SetMaxLength(3);
	FlexGridSizer36->Add(TextCtrl25, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BitmapButton_ButterflySkip = new wxBitmapButton(this, ID_BITMAPBUTTON_SLIDER_Butterfly_Skip, padlock16x16_blue_xpm, wxDefaultPosition, wxSize(13,13), wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON_SLIDER_Butterfly_Skip"));
	BitmapButton_ButterflySkip->SetDefault();
	BitmapButton_ButterflySkip->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	FlexGridSizer36->Add(BitmapButton_ButterflySkip, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	StaticText58 = new wxStaticText(this, wxID_ANY, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer36->Add(StaticText58, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Choice_Butterfly_Direction = new wxChoice(this, ID_CHOICE_Butterfly_Direction, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Butterfly_Direction"));
	Choice_Butterfly_Direction->SetSelection( Choice_Butterfly_Direction->Append(_("Normal")) );
	Choice_Butterfly_Direction->Append(_("Reverse"));
	FlexGridSizer36->Add(Choice_Butterfly_Direction, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer36->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton8 = new wxBitmapButton(this, ID_BITMAPBUTTON9, padlock16x16_blue_xpm, wxDefaultPosition, wxSize(13,13), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
	BitmapButton8->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	FlexGridSizer36->Add(BitmapButton8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer36);
	FlexGridSizer36->Fit(this);
	FlexGridSizer36->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON_CHOICE_Butterfly_Color,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ButterflyPanel::OnLockButtonClick);
	Connect(ID_SLIDER_Butterfly_Style,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedTextCtrl);
	Connect(IDD_TEXTCTRL_Butterfly_Style,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedSlider);
	Connect(ID_BITMAPBUTTON_SLIDER_Butterfly_Style,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ButterflyPanel::OnLockButtonClick);
	Connect(ID_SLIDER_Butterfly_Chunks,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedTextCtrl);
	Connect(IDD_TEXTCTRL_Butterfly_Chunks,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedSlider);
	Connect(ID_BITMAPBUTTON_SLIDER_Butterfly_Chunks,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ButterflyPanel::OnLockButtonClick);
	Connect(ID_SLIDER_Butterfly_Skip,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedTextCtrl);
	Connect(IDD_TEXTCTRL_Butterfly_Skip,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedSlider);
	Connect(ID_BITMAPBUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ButterflyPanel::OnLockButtonClick);
	Connect(ID_SLIDER_Butterfly_Speed,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedTextCtrl);
	Connect(IDD_TEXTCTRL_Butterfly_Speed,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ButterflyPanel::UpdateLinkedSlider);
	Connect(ID_BITMAPBUTTON_SLIDER_Butterfly_Skip,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ButterflyPanel::OnLockButtonClick);
	//*)
    
    SetName("ID_PANEL_BUTTERFLY");
}

ButterflyPanel::~ButterflyPanel()
{
	//(*Destroy(ButterflyPanel)
	//*)
}

PANEL_EVENT_HANDLERS(ButterflyPanel)