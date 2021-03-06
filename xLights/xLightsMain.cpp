/***************************************************************
 * Name:      xLightsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-11-03
 * Copyright: Matt Brown ()
 * License:
 **************************************************************/

#include "xLightsMain.h"
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>
#include <wx/dir.h>
#include <wx/textdlg.h>
#include <wx/numdlg.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/valnum.h>
#include <wx/clipbrd.h>
#include <wx/debugrpt.h>
#include <wx/protocol/http.h>
#include <wx/textctrl.h>
#include "xLightsApp.h" //global app run-time flags
#include "heartbeat.h" //DJ
#include "SeqSettingsDialog.h"
#include <wx/grid.h>
#include <wx/mimetype.h>

#include "RenderCommandEvent.h"
#include "effects/RenderableEffect.h"
#include "LayoutPanel.h"
#include "models/ModelGroup.h"
#include "models/CustomModel.h"

#include "TestDialog.h"
#include "ConvertDialog.h"
#include "GenerateCustomModelDialog.h"
#include "SequenceCheck.h"
#include "FPPConnectDialog.h"

// scripting language
#include "xLightsBasic.cpp"

// image files
#include "../include/xLights.xpm"
#include "../include/xLights-16.xpm"
#include "../include/xLights-32.xpm"
#include "../include/xLights-64.xpm"
#include "../include/xLights-128.xpm"
#include "../include/control-pause-blue-icon.xpm"
#include "../include/control-play-blue-icon.xpm"



//(*InternalHeaders(xLightsFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#define TOOLBAR_SAVE_VERSION "0002:"

#include "osxMacUtils.h"

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(xLightsFrame)
const long xLightsFrame::ID_AUITOOLBAR_OPENSHOW = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_NEWSEQUENCE = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_OPEN = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_SAVE = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_SAVEAS = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_RENDERALL = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_MAIN = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_PLAY_NOW = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_PAUSE = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_STOP = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_FIRST_FRAME = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_LAST_FRAME = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_REPLAY_SECTION = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_PLAY = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM2 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM5 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM7 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM3 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM1 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM4 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM6 = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM8 = wxNewId();
const long xLightsFrame::ID_AUIWINDOWTOOLBAR = wxNewId();
const long xLightsFrame::ID_PASTE_BY_TIME = wxNewId();
const long xLightsFrame::ID_PASTE_BY_CELL = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_EDIT = wxNewId();
const long xLightsFrame::ID_AUITOOLBARITEM14 = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_VIEW = wxNewId();
const long xLightsFrame::ID_BITMAPBUTTON_TAB_INFO = wxNewId();
const long xLightsFrame::ID_BUTTON_STOP_NOW = wxNewId();
const long xLightsFrame::ID_BUTTON_GRACEFUL_STOP = wxNewId();
const long xLightsFrame::ID_BUTTON_LIGHTS_OFF = wxNewId();
const long xLightsFrame::ID_CHECKBOX_LIGHT_OUTPUT = wxNewId();
const long xLightsFrame::ID_AUITOOLBAR_OUTPUT = wxNewId();
const long xLightsFrame::ID_AUIEFFECTSTOOLBAR = wxNewId();
const long xLightsFrame::ID_BUTTON3 = wxNewId();
const long xLightsFrame::ID_STATICTEXT4 = wxNewId();
const long xLightsFrame::ID_BUTTON_CHANGE_MEDIA_DIR = wxNewId();
const long xLightsFrame::ID_ANY = wxNewId();
const long xLightsFrame::ID_BITMAPBUTTON_Link_Dirs = wxNewId();
const long xLightsFrame::ID_BUTTON_SAVE_SETUP = wxNewId();
const long xLightsFrame::ID_BUTTON_ADD_DONGLE = wxNewId();
const long xLightsFrame::ID_BUTTON_ADD_E131 = wxNewId();
const long xLightsFrame::ID_BUTTON1 = wxNewId();
const long xLightsFrame::ID_BUTTON2 = wxNewId();
const long xLightsFrame::ID_BUTTON_NETWORK_CHANGE = wxNewId();
const long xLightsFrame::ID_BUTTON_NETWORK_DELETE = wxNewId();
const long xLightsFrame::ID_BUTTON_NETWORK_DELETE_ALL = wxNewId();
const long xLightsFrame::ID_STATICTEXT8 = wxNewId();
const long xLightsFrame::ID_SPINCTRL1 = wxNewId();
const long xLightsFrame::ID_BITMAPBUTTON1 = wxNewId();
const long xLightsFrame::ID_BITMAPBUTTON2 = wxNewId();
const long xLightsFrame::ID_LISTCTRL_NETWORKS = wxNewId();
const long xLightsFrame::ID_PANEL_SETUP = wxNewId();
const long xLightsFrame::ID_PANEL_PREVIEW = wxNewId();
const long xLightsFrame::ID_TREECTRL1 = wxNewId();
const long xLightsFrame::ID_CHECKBOX_RUN_SCHEDULE = wxNewId();
const long xLightsFrame::ID_BUTTON_SAVE_SCHEDULE = wxNewId();
const long xLightsFrame::ID_BUTTON_ADD_SHOW = wxNewId();
const long xLightsFrame::ID_BUTTON_UPDATE_SHOW = wxNewId();
const long xLightsFrame::ID_BUTTON_DELETE_SHOW = wxNewId();
const long xLightsFrame::ID_STATICTEXT2 = wxNewId();
const long xLightsFrame::ID_BUTTON_SHOW_DATES_CHANGE = wxNewId();
const long xLightsFrame::ID_STATICTEXT3 = wxNewId();
const long xLightsFrame::ID_STATICTEXT_SHOWSTART = wxNewId();
const long xLightsFrame::ID_STATICTEXT5 = wxNewId();
const long xLightsFrame::ID_STATICTEXT_SHOWEND = wxNewId();
const long xLightsFrame::ID_PANEL3 = wxNewId();
const long xLightsFrame::ID_STATICTEXT1 = wxNewId();
const long xLightsFrame::ID_TEXTCTRL_LOG = wxNewId();
const long xLightsFrame::ID_BUTTON_CLEARLOG = wxNewId();
const long xLightsFrame::ID_BUTTON_SAVELOG = wxNewId();
const long xLightsFrame::ID_PANEL2 = wxNewId();
const long xLightsFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long xLightsFrame::ID_PANEL_CAL = wxNewId();
const long xLightsFrame::ID_PANEL7 = wxNewId();
const long xLightsFrame::ID_NOTEBOOK1 = wxNewId();
const long xLightsFrame::ID_STATICTEXT6 = wxNewId();
const long xLightsFrame::ID_GAUGE1 = wxNewId();
const long xLightsFrame::ID_PANEL5 = wxNewId();
const long xLightsFrame::ID_STATICTEXT7 = wxNewId();
const long xLightsFrame::ID_PANEL1 = wxNewId();
const long xLightsFrame::ID_NEW_SEQUENCE = wxNewId();
const long xLightsFrame::ID_OPEN_SEQUENCE = wxNewId();
const long xLightsFrame::IS_SAVE_SEQ = wxNewId();
const long xLightsFrame::ID_SAVE_AS_SEQUENCE = wxNewId();
const long xLightsFrame::ID_CLOSE_SEQ = wxNewId();
const long xLightsFrame::ID_MENUITEM2 = wxNewId();
const long xLightsFrame::ID_FILE_BACKUP = wxNewId();
const long xLightsFrame::ID_FILE_ALTBACKUP = wxNewId();
const long xLightsFrame::ID_MENUITEM13 = wxNewId();
const long xLightsFrame::ID_MENUITEM_CONVERT = wxNewId();
const long xLightsFrame::ID_MENUITEM_GenerateCustomModel = wxNewId();
const long xLightsFrame::ID_MNU_CHECKSEQ = wxNewId();
const long xLightsFrame::ID_MENU_VIEW_LOG = wxNewId();
const long xLightsFrame::ID_MENUITEM18 = wxNewId();
const long xLightsFrame::ID_EXPORT_MODELS = wxNewId();
const long xLightsFrame::ID_MNU_EXPORT_EFFECTS = wxNewId();
const long xLightsFrame::ID_MENU_FPP_CONNECT = wxNewId();
const long xLightsFrame::idMenuSaveSched = wxNewId();
const long xLightsFrame::idMenuAddList = wxNewId();
const long xLightsFrame::idMenuRenameList = wxNewId();
const long xLightsFrame::idMenuDelList = wxNewId();
const long xLightsFrame::ID_MENUITEM1 = wxNewId();
const long xLightsFrame::idCustomScript = wxNewId();
const long xLightsFrame::ID_MENUITEM_SAVE_PERSPECTIVE = wxNewId();
const long xLightsFrame::ID_MENUITEM_SAVE_AS_PERSPECTIVE = wxNewId();
const long xLightsFrame::ID_MENUITEM_LOAD_PERSPECTIVE = wxNewId();
const long xLightsFrame::ID_MENUITEM7 = wxNewId();
const long xLightsFrame::ID_MENUITEM_DISPLAY_ELEMENTS = wxNewId();
const long xLightsFrame::ID_MENUITEM12 = wxNewId();
const long xLightsFrame::ID_MENUITEM3 = wxNewId();
const long xLightsFrame::ID_MENUITEM14 = wxNewId();
const long xLightsFrame::ID_MENUITEM15 = wxNewId();
const long xLightsFrame::ID_MENUITEM16 = wxNewId();
const long xLightsFrame::ID_MENUITEM9 = wxNewId();
const long xLightsFrame::ID_MENUITEM17 = wxNewId();
const long xLightsFrame::ID_MENUITEM_EFFECT_ASSIST_WINDOW = wxNewId();
const long xLightsFrame::ID_MENUITEM_WINDOWS_PERSPECTIVE = wxNewId();
const long xLightsFrame::ID_MENUITEM_WINDOWS_DOCKALL = wxNewId();
const long xLightsFrame::ID_MENUITEM11 = wxNewId();
const long xLightsFrame::ID_MENUITEM10 = wxNewId();
const long xLightsFrame::ID_PLAY_FULL = wxNewId();
const long xLightsFrame::ID_PLAY_3_4 = wxNewId();
const long xLightsFrame::ID_PLAY_1_2 = wxNewId();
const long xLightsFrame::ID_PLAY_1_4 = wxNewId();
const long xLightsFrame::ID_IMPORT_EFFECTS = wxNewId();
const long xLightsFrame::ID_SEQ_SETTINGS = wxNewId();
const long xLightsFrame::ID_RENDER_ON_SAVE = wxNewId();
const long xLightsFrame::ID_BACKUP_ON_SAVE = wxNewId();
const long xLightsFrame::ID_MENU_BACKUP_ON_LAUNCH = wxNewId();
const long xLightsFrame::ID_ALT_BACKUPLOCATION = wxNewId();
const long xLightsFrame::ID_MENUITEM_ICON_SMALL = wxNewId();
const long xLightsFrame::ID_MENUITEM_ICON_MEDIUM = wxNewId();
const long xLightsFrame::ID_MENUITEM_ICON_LARGE = wxNewId();
const long xLightsFrame::ID_MENUITEM_ICON_XLARGE = wxNewId();
const long xLightsFrame::ID_MENUITEM4 = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_XSMALL = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_SMALL = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_MEDIUM = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_LARGE = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_XLARGE = wxNewId();
const long xLightsFrame::ID_MENUITEM6 = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_BACKGROUND_ON = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_ICON_BACKGROUND_OFF = wxNewId();
const long xLightsFrame::ID_MENUITEM_Grid_Icon_Backgrounds = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_NODE_VALUES_ON = wxNewId();
const long xLightsFrame::ID_MENUITEM_GRID_NODE_VALUES_OFF = wxNewId();
const long xLightsFrame::ID_MENUITEM8 = wxNewId();
const long xLightsFrame::ID_MENU_CANVAS_ERASE_MODE = wxNewId();
const long xLightsFrame::ID_MENU_CANVAS_CANVAS_MODE = wxNewId();
const long xLightsFrame::ID_MENUITEM_RENDER_MODE = wxNewId();
const long xLightsFrame::ID_MENUITEM_EFFECT_ASSIST_ALWAYS_ON = wxNewId();
const long xLightsFrame::ID_MENUITEM_EFFECT_ASSIST_ALWAYS_OFF = wxNewId();
const long xLightsFrame::ID_MENUITEM_EFFECT_ASSIST_TOGGLE = wxNewId();
const long xLightsFrame::ID_MENUITEM_EFFECT_ASSIST = wxNewId();
const long xLightsFrame::ID_MENU_OPENGL_AUTO = wxNewId();
const long xLightsFrame::ID_MENU_OPENGL_3 = wxNewId();
const long xLightsFrame::ID_MENU_OPENGL_2 = wxNewId();
const long xLightsFrame::ID_MENU_OPENGL_1 = wxNewId();
const long xLightsFrame::ID_MENUITEM19 = wxNewId();
const long xLightsFrame::ID_MENUITEM_AUTOSAVE_0 = wxNewId();
const long xLightsFrame::ID_MENUITEM_AUTOSAVE_3 = wxNewId();
const long xLightsFrame::ID_MENUITEM_AUTOSAVE_10 = wxNewId();
const long xLightsFrame::ID_MENUITEM_AUTOSAVE_15 = wxNewId();
const long xLightsFrame::ID_MENUITEM_AUTOSAVE_30 = wxNewId();
const long xLightsFrame::ID_MENUITEM20 = wxNewId();
const long xLightsFrame::ID_E131_Sync = wxNewId();
const long xLightsFrame::ID_MENUITEM5 = wxNewId();
const long xLightsFrame::idMenuHelpContent = wxNewId();
const long xLightsFrame::ID_MENU_HELP_FORMUM = wxNewId();
const long xLightsFrame::ID_MENU_HELP_DOWNLOAD = wxNewId();
const long xLightsFrame::ID_MNU_HELP_RELEASE_NOTES = wxNewId();
const long xLightsFrame::ID_MENU_HELP_ISSUE = wxNewId();
const long xLightsFrame::ID_MENU_HELP_FACEBOOK = wxNewId();
const long xLightsFrame::ID_TIMER1 = wxNewId();
const long xLightsFrame::ID_TIMER2 = wxNewId();
const long xLightsFrame::ID_TIMER_EFFECT_SETTINGS = wxNewId();
//*)

// For new sequencer
const long xLightsFrame::ID_PANEL_EFFECTS1 = wxNewId();
const long xLightsFrame::ID_PANEL_EFFECTS = wxNewId();
const long xLightsFrame::ID_NOTEBOOK_EFFECTS = wxNewId();
// End

const long xLightsFrame::ID_PLAYER_DIALOG = wxNewId();
const long xLightsFrame::ID_DELETE_EFFECT = wxNewId();
const long xLightsFrame::ID_IGNORE_CLICK = wxNewId();
const long xLightsFrame::ID_PROTECT_EFFECT = wxNewId();
const long xLightsFrame::ID_UNPROTECT_EFFECT = wxNewId();
const long xLightsFrame::ID_RANDOM_EFFECT = wxNewId();
const long xLightsFrame::ID_COPYROW_EFFECT = wxNewId(); //copy random effect across row -DJ
const long xLightsFrame::ID_CLEARROW_EFFECT = wxNewId(); //clear all effects on this row -DJ

const long xLightsFrame::ID_MENU_ITEM_PREVIEWS = wxNewId();
const long xLightsFrame::ID_MENU_ITEM_PREVIEWS_SHOW_ALL = wxNewId();

wxDEFINE_EVENT(EVT_ZOOM, wxCommandEvent);
wxDEFINE_EVENT(EVT_GSCROLL, wxCommandEvent);
wxDEFINE_EVENT(EVT_TIME_SELECTED, wxCommandEvent);
wxDEFINE_EVENT(EVT_MOUSE_POSITION, wxCommandEvent);
wxDEFINE_EVENT(EVT_ROW_HEADINGS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_WINDOW_RESIZED, wxCommandEvent);
wxDEFINE_EVENT(EVT_SELECTED_ROW_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_EFFECT_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_UNSELECTED_EFFECT, wxCommandEvent);
wxDEFINE_EVENT(EVT_PLAY_MODEL_EFFECT, wxCommandEvent);
wxDEFINE_EVENT(EVT_EFFECT_DROPPED, wxCommandEvent);
wxDEFINE_EVENT(EVT_EFFECT_UPDATED, wxCommandEvent);
wxDEFINE_EVENT(EVT_EFFECT_PALETTE_UPDATED, wxCommandEvent);
wxDEFINE_EVENT(EVT_FORCE_SEQUENCER_REFRESH, wxCommandEvent);
wxDEFINE_EVENT(EVT_LOAD_PERSPECTIVE, wxCommandEvent);
wxDEFINE_EVENT(EVT_PERSPECTIVES_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_SAVE_PERSPECTIVES, wxCommandEvent);
wxDEFINE_EVENT(EVT_EXPORT_MODEL, wxCommandEvent);
wxDEFINE_EVENT(EVT_PLAY_MODEL, wxCommandEvent);
wxDEFINE_EVENT(EVT_COPY_MODEL_EFFECTS, wxCommandEvent);
wxDEFINE_EVENT(EVT_PASTE_MODEL_EFFECTS, wxCommandEvent);
wxDEFINE_EVENT(EVT_MODEL_SELECTED, wxCommandEvent);
wxDEFINE_EVENT(EVT_PLAY_SEQUENCE, wxCommandEvent);
wxDEFINE_EVENT(EVT_PAUSE_SEQUENCE, wxCommandEvent);
wxDEFINE_EVENT(EVT_TOGGLE_PLAY, wxCommandEvent);
wxDEFINE_EVENT(EVT_STOP_SEQUENCE, wxCommandEvent);
wxDEFINE_EVENT(EVT_SEQUENCE_FIRST_FRAME, wxCommandEvent);
wxDEFINE_EVENT(EVT_SEQUENCE_LAST_FRAME, wxCommandEvent);
wxDEFINE_EVENT(EVT_SEQUENCE_REPLAY_SECTION, wxCommandEvent);
wxDEFINE_EVENT(EVT_SHOW_DISPLAY_ELEMENTS, wxCommandEvent);
wxDEFINE_EVENT(EVT_IMPORT_TIMING, wxCommandEvent);
wxDEFINE_EVENT(EVT_IMPORT_NOTES, wxCommandEvent);
wxDEFINE_EVENT(EVT_CONVERT_DATA_TO_EFFECTS, wxCommandEvent);
wxDEFINE_EVENT(EVT_PROMOTE_EFFECTS, wxCommandEvent);
wxDEFINE_EVENT(EVT_RGBEFFECTS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_RENDER_RANGE, RenderCommandEvent);
wxDEFINE_EVENT(EVT_SELECTED_EFFECT_CHANGED, SelectedEffectChangedEvent);

BEGIN_EVENT_TABLE(xLightsFrame,wxFrame)
    //(*EventTable(xLightsFrame)
    //*)
    EVT_COMMAND(wxID_ANY, EVT_ZOOM, xLightsFrame::Zoom)
    EVT_COMMAND(wxID_ANY, EVT_GSCROLL, xLightsFrame::Scroll)
    EVT_COMMAND(wxID_ANY, EVT_TIME_SELECTED, xLightsFrame::TimeSelected)
    EVT_COMMAND(wxID_ANY, EVT_MOUSE_POSITION, xLightsFrame::MousePositionUpdated)
    EVT_COMMAND(wxID_ANY, EVT_ROW_HEADINGS_CHANGED, xLightsFrame::RowHeadingsChanged)
    EVT_COMMAND(wxID_ANY, EVT_WINDOW_RESIZED, xLightsFrame::WindowResized)
    EVT_COMMAND(wxID_ANY, EVT_SELECTED_ROW_CHANGED, xLightsFrame::SelectedRowChanged)
    EVT_COMMAND(wxID_ANY, EVT_EFFECT_CHANGED, xLightsFrame::EffectChanged)
    EVT_COMMAND(wxID_ANY, EVT_UNSELECTED_EFFECT, xLightsFrame::UnselectedEffect)
    EVT_COMMAND(wxID_ANY, EVT_EFFECT_DROPPED, xLightsFrame::EffectDroppedOnGrid)
    EVT_COMMAND(wxID_ANY, EVT_PLAY_MODEL_EFFECT, xLightsFrame::PlayModelEffect)
    EVT_COMMAND(wxID_ANY, EVT_EFFECT_UPDATED, xLightsFrame::UpdateEffect)
    EVT_COMMAND(wxID_ANY, EVT_EFFECT_PALETTE_UPDATED, xLightsFrame::UpdateEffectPalette)
    EVT_COMMAND(wxID_ANY, EVT_FORCE_SEQUENCER_REFRESH, xLightsFrame::ForceSequencerRefresh)
    EVT_COMMAND(wxID_ANY, EVT_LOAD_PERSPECTIVE, xLightsFrame::LoadPerspective)
    EVT_COMMAND(wxID_ANY, EVT_SAVE_PERSPECTIVES, xLightsFrame::OnMenuItemViewSavePerspectiveSelected)
    EVT_COMMAND(wxID_ANY, EVT_PERSPECTIVES_CHANGED, xLightsFrame::PerspectivesChanged)
    EVT_COMMAND(wxID_ANY, EVT_EXPORT_MODEL, xLightsFrame::ExportModel)
    EVT_COMMAND(wxID_ANY, EVT_PLAY_MODEL, xLightsFrame::PlayModel)
    EVT_COMMAND(wxID_ANY, EVT_COPY_MODEL_EFFECTS, xLightsFrame::CopyModelEffects)
    EVT_COMMAND(wxID_ANY, EVT_PASTE_MODEL_EFFECTS, xLightsFrame::PasteModelEffects)
    EVT_COMMAND(wxID_ANY, EVT_MODEL_SELECTED, xLightsFrame::ModelSelected)
    EVT_COMMAND(wxID_ANY, EVT_PLAY_SEQUENCE, xLightsFrame::PlaySequence)
    EVT_COMMAND(wxID_ANY, EVT_PAUSE_SEQUENCE, xLightsFrame::PauseSequence)
    EVT_COMMAND(wxID_ANY, EVT_STOP_SEQUENCE, xLightsFrame::StopSequence)
    EVT_COMMAND(wxID_ANY, EVT_SEQUENCE_FIRST_FRAME, xLightsFrame::SequenceFirstFrame)
    EVT_COMMAND(wxID_ANY, EVT_SEQUENCE_LAST_FRAME, xLightsFrame::SequenceLastFrame)
    EVT_COMMAND(wxID_ANY, EVT_SEQUENCE_REPLAY_SECTION, xLightsFrame::SequenceReplaySection)
    EVT_COMMAND(wxID_ANY, EVT_TOGGLE_PLAY, xLightsFrame::TogglePlay)
    EVT_COMMAND(wxID_ANY, EVT_SHOW_DISPLAY_ELEMENTS, xLightsFrame::ShowDisplayElements)
    EVT_COMMAND(wxID_ANY, EVT_IMPORT_TIMING, xLightsFrame::ExecuteImportTimingElement)
    EVT_COMMAND(wxID_ANY, EVT_IMPORT_NOTES, xLightsFrame::ExecuteImportNotes)
    EVT_COMMAND(wxID_ANY, EVT_CONVERT_DATA_TO_EFFECTS, xLightsFrame::ConvertDataRowToEffects)
    EVT_COMMAND(wxID_ANY, EVT_PROMOTE_EFFECTS, xLightsFrame::PromoteEffects)
    EVT_COMMAND(wxID_ANY, EVT_RGBEFFECTS_CHANGED, xLightsFrame::PerspectivesChanged)
    wx__DECLARE_EVT1(EVT_RENDER_RANGE, wxID_ANY, &xLightsFrame::RenderRange)
    wx__DECLARE_EVT1(EVT_SELECTED_EFFECT_CHANGED, wxID_ANY, &xLightsFrame::SelectedEffectChanged)

END_EVENT_TABLE()



void AddEffectToolbarButtons(EffectManager &manager, xlAuiToolBar *EffectsToolBar) {

    for (int x = 0; x < manager.size(); x++) {
        DragEffectBitmapButton *BitmapButton34 = new DragEffectBitmapButton(EffectsToolBar, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(16,16),
                                                    wxBU_AUTODRAW|wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON38"));
        int size = 16;
        BitmapButton34->SetMinSize(wxSize(size,size));
        BitmapButton34->SetMaxSize(wxSize(size,size));
#ifndef LINUX
        BitmapButton34->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
#endif
        BitmapButton34->SetEffect(manager[x]);
        BitmapButton34->SetBitmapMargins(0,0);
        EffectsToolBar->AddControl(BitmapButton34, BitmapButton34->GetToolTipText());

        EffectsToolBar->FindToolByIndex(x)->SetMinSize(wxSize(size, size));
        EffectsToolBar->FindToolByIndex(x)->GetWindow()->SetSizeHints(size, size, size, size);
        EffectsToolBar->FindToolByIndex(x)->GetWindow()->SetMinSize(wxSize(size, size));
        EffectsToolBar->FindToolByIndex(x)->GetWindow()->SetMaxSize(wxSize(size, size));

    }
    EffectsToolBar->Realize();
}


xLightsFrame::xLightsFrame(wxWindow* parent,wxWindowID id) : mSequenceElements(this), AllModels(NetInfo, this)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    logger_base.debug("xLightsFrame being constructed.");
    _fps = -1;
    mCurrentPerpective = nullptr;
    MenuItemPreviews = nullptr;

    Bind(EVT_SELECTED_EFFECT_CHANGED, &xLightsFrame::SelectedEffectChanged, this);
    Bind(EVT_RENDER_RANGE, &xLightsFrame::RenderRange, this);

    //(*Initialize(xLightsFrame)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxMenuItem* MenuItem31;
    wxMenu* MenuHelp;
    wxMenuItem* MenuItem8;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizerSetup;
    wxMenuItem* MenuItem26;
    wxMenuItem* MenuItemCustomScript;
    wxMenuItem* MenuItem25;
    wxMenuItem* MenuItem5;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItemAddList;
    wxGridBagSizer* GridBagSizer1;
    wxFlexGridSizer* FlexGridSizer27;
    wxMenuItem* MenuItem46;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem14;
    wxFlexGridSizer* FlexGridSizer5;
    wxMenuItem* MenuItem11;
    wxMenuItem* MenuItem29;
    wxStaticText* StaticText38;
    wxFlexGridSizer* FlexGridSizer9;
    wxMenuItem* MenuItem22;
    wxPanel* Panel1;
    wxMenuItem* MenuItem17;
    wxBoxSizer* BoxSizer2;
    wxMenuItem* MenuItem13;
    wxFlexGridSizer* FlexGridSizer7;
    wxMenuItem* MenuItem10;
    wxFlexGridSizer* FlexGridSizerCal;
    wxMenu* MenuItem_Grid_Icon_Backgrounds;
    wxMenuItem* MenuItemDelList;
    wxMenuItem* MenuItem12;
    wxMenuItem* MenuItem24;
    wxMenuItem* MenuItem27;
    wxMenuItem* MenuItem44;
    wxFlexGridSizer* FlexGridSizerNetworks;
    wxFlexGridSizer* FlexGridSizer29;
    wxMenuItem* MenuItem20;
    wxFlexGridSizer* FlexGridSizerPreview;
    wxMenuItem* MenuItem28;
    wxMenuItem* MenuItemDisplayElements;
    wxMenuItem* MenuItem6;
    wxMenuItem* MenuItem23;
    wxStaticText* StaticText28;
    wxBoxSizer* BoxSizer1;
    wxMenuItem* MenuItemRenameList;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxMenuItem* MenuItem21;
    wxMenu* Menu2;
    wxMenuItem* MenuItem9;
    wxMenuItem* MenuItem45;
    wxMenuItem* MenuItem47;
    wxMenuItem* MenuItem30;
    wxMenuItem* MenuItem48;
    wxFlexGridSizer* FlexGridSizer28;
    wxMenu* MenuPlaylist;
    wxMenuItem* MenuItem19;
    wxButton* Button03;

    Create(parent, wxID_ANY, _("<use variables in xLightsMain.h>"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1411,1103));
    MainAuiManager = new wxAuiManager(this, wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_DEFAULT);
    MainToolBar = new xlAuiToolBar(this, ID_AUITOOLBAR_MAIN, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    MainToolBar->AddTool(ID_AUITOOLBAR_OPENSHOW, _("Open Show Directory"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FOLDER_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Select Show Directory"), wxEmptyString, NULL);
    MainToolBar->AddTool(ID_AUITOOLBAR_NEWSEQUENCE, _("New Sequence"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("New Sequence"), wxEmptyString, NULL);
    MainToolBar->AddTool(ID_AUITOOLBAR_OPEN, _("Open Sequence"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Open Sequence"), wxEmptyString, NULL);
    MainToolBar->AddTool(ID_AUITOOLBAR_SAVE, _("Save"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save"), wxEmptyString, NULL);
    MainToolBar->AddTool(ID_AUITOOLBAR_SAVEAS, _("Save As"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save As"), wxEmptyString, NULL);
    MainToolBar->AddTool(ID_AUITOOLBAR_RENDERALL, _("Render All"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_RENDER_ALL")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Render All"), wxEmptyString, NULL);
    MainToolBar->Realize();
    MainAuiManager->AddPane(MainToolBar, wxAuiPaneInfo().Name(_T("Main Tool Bar")).ToolbarPane().Caption(_("Main Tool Bar")).CloseButton(false).Layer(10).Top().Gripper());
    PlayToolBar = new xlAuiToolBar(this, ID_AUITOOLBAR_PLAY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    PlayToolBar->AddTool(ID_AUITOOLBAR_PLAY_NOW, _("Play"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_PLAY")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Play"), wxEmptyString, NULL);
    PlayToolBar->AddTool(ID_AUITOOLBAR_PAUSE, _("Pause"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_PAUSE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Pause"), wxEmptyString, NULL);
    PlayToolBar->AddTool(ID_AUITOOLBAR_STOP, _("Stop"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_STOP")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Stop"), wxEmptyString, NULL);
    PlayToolBar->AddTool(ID_AUITOOLBAR_FIRST_FRAME, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_BACKWARD")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("First Frame"), wxEmptyString, NULL);
    PlayToolBar->AddTool(ID_AUITOOLBAR_LAST_FRAME, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_FORWARD")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Last Frame"), wxEmptyString, NULL);
    PlayToolBar->AddTool(ID_AUITOOLBAR_REPLAY_SECTION, _("Item label"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_REPLAY")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Replay Section"), wxEmptyString, NULL);
    PlayToolBar->Realize();
    MainAuiManager->AddPane(PlayToolBar, wxAuiPaneInfo().Name(_T("Play Tool Bar")).ToolbarPane().Caption(_("Play Tool Bar")).CloseButton(false).Layer(10).Position(11).Top().Gripper());
    WindowMgmtToolbar = new xlAuiToolBar(this, ID_AUIWINDOWTOOLBAR, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM2, _("Effect Settings"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_EFFECTSETTINGS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Effect Settings"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM5, _("Effect Colors"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_COLORS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Effect Colors"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM7, _("Layer Settings"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_LAYERS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Layer Settings"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM3, _("Layer Blending"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_LAYERS2")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Layer Blending"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM1, _("Model Preview"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_MODEL_PREVIEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Model Preview"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM4, _("House Preview"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_HOUSE_PREVIEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("House Preview"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM6, _("Models"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_SEQUENCE_ELEMENTS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Display Elements"), wxEmptyString, NULL);
    WindowMgmtToolbar->AddTool(ID_AUITOOLBARITEM8, _("Effects"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_EFFECTS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Effects"), wxEmptyString, NULL);
    WindowMgmtToolbar->Realize();
    MainAuiManager->AddPane(WindowMgmtToolbar, wxAuiPaneInfo().Name(_T("Windows Tool Bar")).ToolbarPane().Caption(_("Windows Tool Bar")).CloseButton(false).Layer(10).Position(12).Top().Gripper());
    EditToolBar = new xlAuiToolBar(this, ID_AUITOOLBAR_EDIT, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    EditToolBar->AddTool(ID_PASTE_BY_TIME, _("Paste By Time"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_PASTE_BY_TIME")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Paste By Time"), wxEmptyString, NULL);
    EditToolBar->AddTool(ID_PASTE_BY_CELL, _("Paste By Cell"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_PASTE_BY_CELL")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Paste By Cell"), wxEmptyString, NULL);
    EditToolBar->Realize();
    MainAuiManager->AddPane(EditToolBar, wxAuiPaneInfo().Name(_T("Edit Tool Bar")).ToolbarPane().Caption(_("Pane caption")).CloseButton(false).Layer(10).Position(5).Top().Gripper());
    ViewToolBar = new xlAuiToolBar(this, ID_AUITOOLBAR_VIEW, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    ViewToolBar->AddTool(wxID_ZOOM_IN, _("Zoom In"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_ZOOM_IN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Zoom In"), wxEmptyString, NULL);
    ViewToolBar->AddTool(wxID_ZOOM_OUT, _("Zoom Out"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_ZOOM_OUT")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Zoom Out"), wxEmptyString, NULL);
    ViewToolBar->AddTool(ID_AUITOOLBARITEM14, _("Sequence Settings"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_SETTINGS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Settings"), wxEmptyString, NULL);
    ViewToolBar->Realize();
    MainAuiManager->AddPane(ViewToolBar, wxAuiPaneInfo().Name(_T("View Tool Bar")).ToolbarPane().Caption(_("Pane caption")).CloseButton(false).Layer(10).Position(13).Top().Gripper());
    OutputToolBar = new xlAuiToolBar(this, ID_AUITOOLBAR_OUTPUT, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    OutputToolBar->AddTool(ID_BITMAPBUTTON_TAB_INFO, _("Information"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Tips for using current tab"), wxEmptyString, NULL);
    OutputToolBar->AddTool(ID_BUTTON_STOP_NOW, _("Stop"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_STOP_NOW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Stop Now!"), wxEmptyString, NULL);
    OutputToolBar->AddTool(ID_BUTTON_GRACEFUL_STOP, _("Graceful Stop"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_GRACEFUL_STOP")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Graceful Stop"), wxEmptyString, NULL);
    OutputToolBar->AddTool(ID_BUTTON_LIGHTS_OFF, _("Lights Off"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_LIGHTS_OFF")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Lights Off"), wxEmptyString, NULL);
    OutputToolBar->AddTool(ID_CHECKBOX_LIGHT_OUTPUT, _("Output To Lights"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_OUTPUT_LIGHTS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_CHECK, _("Output To Lights"), wxEmptyString, NULL);
    OutputToolBar->Realize();
    MainAuiManager->AddPane(OutputToolBar, wxAuiPaneInfo().Name(_T("Output Tool Bar")).ToolbarPane().Caption(_("Output Tool Bar")).CloseButton(false).Layer(10).Position(25).Top().Gripper());
    EffectsToolBar = new xlAuiToolBar(this, ID_AUIEFFECTSTOOLBAR, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    EffectsToolBar->Realize();
    MainAuiManager->AddPane(EffectsToolBar, wxAuiPaneInfo().Name(_T("EffectsToolBar")).ToolbarPane().Caption(_("Effects")).CloseButton(false).Layer(5).Top().Gripper());
    Notebook1 = new wxAuiNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_EXTERNAL_MOVE|wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_TOP|wxNO_BORDER);
    PanelSetup = new wxPanel(Notebook1, ID_PANEL_SETUP, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_SETUP"));
    FlexGridSizerSetup = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizerSetup->AddGrowableCol(0);
    FlexGridSizerSetup->AddGrowableRow(1);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, PanelSetup, _("Directories"));
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    StaticText38 = new wxStaticText(PanelSetup, wxID_ANY, _("Show Directory:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    GridBagSizer1->Add(StaticText38, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button03 = new wxButton(PanelSetup, ID_BUTTON3, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridBagSizer1->Add(Button03, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ShowDirectoryLabel = new wxStaticText(PanelSetup, ID_STATICTEXT4, _("{Show Directory not set}"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    GridBagSizer1->Add(ShowDirectoryLabel, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText28 = new wxStaticText(PanelSetup, wxID_ANY, _("Media Directory:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    GridBagSizer1->Add(StaticText28, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Button_Change_Media_Dir = new wxButton(PanelSetup, ID_BUTTON_CHANGE_MEDIA_DIR, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CHANGE_MEDIA_DIR"));
    GridBagSizer1->Add(Button_Change_Media_Dir, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MediaDirectoryLabel = new wxStaticText(PanelSetup, ID_ANY, _("{Media Directory not set}"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ANY"));
    GridBagSizer1->Add(MediaDirectoryLabel, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton_Link_Dirs = new wxBitmapButton(PanelSetup, ID_BITMAPBUTTON_Link_Dirs, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_UNLINK")),wxART_OTHER), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_Link_Dirs"));
    BitmapButton_Link_Dirs->SetToolTip(_("Link Directories"));
    GridBagSizer1->Add(BitmapButton_Link_Dirs, wxGBPosition(0, 3), wxGBSpan(2, 1), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(GridBagSizer1, 1, wxALL|wxEXPAND, 5);
    FlexGridSizerSetup->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, PanelSetup, _("Lighting Networks"));
    FlexGridSizerNetworks = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizerNetworks->AddGrowableCol(2);
    FlexGridSizerNetworks->AddGrowableRow(0);
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    ButtonSaveSetup = new wxButton(PanelSetup, ID_BUTTON_SAVE_SETUP, _("Save Setup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVE_SETUP"));
    BoxSizer1->Add(ButtonSaveSetup, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    ButtonAddDongle = new wxButton(PanelSetup, ID_BUTTON_ADD_DONGLE, _("Add USB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_DONGLE"));
    BoxSizer1->Add(ButtonAddDongle, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    ButtonAddE131 = new wxButton(PanelSetup, ID_BUTTON_ADD_E131, _("Add E1.31"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_E131"));
    BoxSizer1->Add(ButtonAddE131, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    ButtonAddNull = new wxButton(PanelSetup, ID_BUTTON1, _("Add Null"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(ButtonAddNull, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonArtNET = new wxButton(PanelSetup, ID_BUTTON2, _("Add ArtNET"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer1->Add(ButtonArtNET, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonNetworkChange = new wxButton(PanelSetup, ID_BUTTON_NETWORK_CHANGE, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETWORK_CHANGE"));
    BoxSizer1->Add(ButtonNetworkChange, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    ButtonNetworkDelete = new wxButton(PanelSetup, ID_BUTTON_NETWORK_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETWORK_DELETE"));
    BoxSizer1->Add(ButtonNetworkDelete, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    ButtonNetworkDeleteAll = new wxButton(PanelSetup, ID_BUTTON_NETWORK_DELETE_ALL, _("Delete All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETWORK_DELETE_ALL"));
    BoxSizer1->Add(ButtonNetworkDeleteAll, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText5 = new wxStaticText(PanelSetup, ID_STATICTEXT8, _("\nE1.31 Sync Universe:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 0);
    SpinCtrl_SyncUniverse = new wxSpinCtrl(PanelSetup, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 63999, 0, _T("ID_SPINCTRL1"));
    SpinCtrl_SyncUniverse->SetValue(_T("0"));
    SpinCtrl_SyncUniverse->SetToolTip(_("This should be left as 0 unless you have controllers which support it."));
    BoxSizer1->Add(SpinCtrl_SyncUniverse, 1, wxALL|wxEXPAND, 5);
    FlexGridSizerNetworks->Add(BoxSizer1, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
    BitmapButtonMoveNetworkUp = new wxBitmapButton(PanelSetup, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_UP")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    BitmapButtonMoveNetworkUp->SetDefault();
    BitmapButtonMoveNetworkUp->SetToolTip(_("Move selected item up"));
    FlexGridSizer9->Add(BitmapButtonMoveNetworkUp, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonMoveNetworkDown = new wxBitmapButton(PanelSetup, ID_BITMAPBUTTON2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_DOWN")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
    BitmapButtonMoveNetworkDown->SetDefault();
    BitmapButtonMoveNetworkDown->SetToolTip(_("Move selected item down"));
    FlexGridSizer9->Add(BitmapButtonMoveNetworkDown, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerNetworks->Add(FlexGridSizer9, 1, wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    GridNetwork = new wxListCtrl(PanelSetup, ID_LISTCTRL_NETWORKS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL_NETWORKS"));
    GridNetwork->SetToolTip(_("Drag an item to reorder the list"));
    FlexGridSizerNetworks->Add(GridNetwork, 1, wxEXPAND, 5);
    StaticBoxSizer2->Add(FlexGridSizerNetworks, 1, wxALL|wxEXPAND, 5);
    FlexGridSizerSetup->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
    PanelSetup->SetSizer(FlexGridSizerSetup);
    FlexGridSizerSetup->Fit(PanelSetup);
    FlexGridSizerSetup->SetSizeHints(PanelSetup);
    PanelPreview = new wxPanel(Notebook1, ID_PANEL_PREVIEW, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_PREVIEW"));
    FlexGridSizerPreview = new wxFlexGridSizer(1, 1, 0, 0);
    FlexGridSizerPreview->AddGrowableCol(0);
    FlexGridSizerPreview->AddGrowableRow(0);
    PanelPreview->SetSizer(FlexGridSizerPreview);
    FlexGridSizerPreview->Fit(PanelPreview);
    FlexGridSizerPreview->SetSizeHints(PanelPreview);
    PanelCal = new wxPanel(Notebook1, ID_PANEL_CAL, wxPoint(49,10), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CAL"));
    FlexGridSizerCal = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizerCal->AddGrowableCol(0);
    FlexGridSizerCal->AddGrowableRow(0);
    SplitterWindow1 = new wxSplitterWindow(PanelCal, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_NOBORDER|wxSP_NO_XP_THEME, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0.5);
    Panel3 = new wxPanel(SplitterWindow1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(0);
    ListBoxSched = new wxTreeCtrl(Panel3, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_MULTIPLE|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    FlexGridSizer4->Add(ListBoxSched, 0, wxEXPAND, 0);
    FlexGridSizer27 = new wxFlexGridSizer(0, 1, 0, 0);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    CheckBoxRunSchedule = new wxCheckBox(Panel3, ID_CHECKBOX_RUN_SCHEDULE, _("Run Schedule"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUN_SCHEDULE"));
    CheckBoxRunSchedule->SetValue(false);
    BoxSizer2->Add(CheckBoxRunSchedule, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSaveSchedule = new wxButton(Panel3, ID_BUTTON_SAVE_SCHEDULE, _("Save Schedule"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVE_SCHEDULE"));
    ButtonSaveSchedule->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    BoxSizer2->Add(ButtonSaveSchedule, 1, wxALL|wxEXPAND, 5);
    ButtonAddShow = new wxButton(Panel3, ID_BUTTON_ADD_SHOW, _("Schedule Playlist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_SHOW"));
    ButtonAddShow->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    BoxSizer2->Add(ButtonAddShow, 1, wxALL|wxEXPAND, 3);
    ButtonUpdateShow = new wxButton(Panel3, ID_BUTTON_UPDATE_SHOW, _("Update Selected Items"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_UPDATE_SHOW"));
    ButtonUpdateShow->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    BoxSizer2->Add(ButtonUpdateShow, 1, wxALL|wxEXPAND, 3);
    ButtonDeleteShow = new wxButton(Panel3, ID_BUTTON_DELETE_SHOW, _("Delete Selected Items"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DELETE_SHOW"));
    ButtonDeleteShow->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    BoxSizer2->Add(ButtonDeleteShow, 1, wxALL|wxEXPAND, 3);
    FlexGridSizer27->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText2 = new wxStaticText(Panel3, ID_STATICTEXT2, _("Show Dates"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(wxDEFAULT,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer7->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonShowDatesChange = new wxButton(Panel3, ID_BUTTON_SHOW_DATES_CHANGE, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SHOW_DATES_CHANGE"));
    ButtonShowDatesChange->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    FlexGridSizer7->Add(ButtonShowDatesChange, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextShowStart = new wxStaticText(Panel3, ID_STATICTEXT_SHOWSTART, _("xx/xx/xxxx"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_SHOWSTART"));
    FlexGridSizer7->Add(StaticTextShowStart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel3, ID_STATICTEXT5, _("End"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer7->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextShowEnd = new wxStaticText(Panel3, ID_STATICTEXT_SHOWEND, _("xx/xx/xxxx"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_SHOWEND"));
    FlexGridSizer7->Add(StaticTextShowEnd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer27->Add(FlexGridSizer7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer27, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel3->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel3);
    FlexGridSizer4->SetSizeHints(Panel3);
    Panel2 = new wxPanel(SplitterWindow1, ID_PANEL2, wxPoint(13,93), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    FlexGridSizer28 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer28->AddGrowableCol(0);
    FlexGridSizer28->AddGrowableRow(1);
    StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("While the scheduler is running, each item that is played is logged here"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer28->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer29 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer29->AddGrowableCol(0);
    FlexGridSizer29->AddGrowableRow(0);
    TextCtrlLog = new wxTextCtrl(Panel2, ID_TEXTCTRL_LOG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOG"));
    FlexGridSizer29->Add(TextCtrlLog, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
    ButtonClearLog = new wxButton(Panel2, ID_BUTTON_CLEARLOG, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEARLOG"));
    ButtonClearLog->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    FlexGridSizer5->Add(ButtonClearLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSaveLog = new wxButton(Panel2, ID_BUTTON_SAVELOG, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVELOG"));
    ButtonSaveLog->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    FlexGridSizer5->Add(ButtonSaveLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer29->Add(FlexGridSizer5, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer28->Add(FlexGridSizer29, 1, wxALL|wxEXPAND, 5);
    Panel2->SetSizer(FlexGridSizer28);
    FlexGridSizer28->Fit(Panel2);
    FlexGridSizer28->SetSizeHints(Panel2);
    SplitterWindow1->SplitVertically(Panel3, Panel2);
    FlexGridSizerCal->Add(SplitterWindow1, 1, wxALL|wxEXPAND, 5);
    PanelCal->SetSizer(FlexGridSizerCal);
    FlexGridSizerCal->Fit(PanelCal);
    FlexGridSizerCal->SetSizeHints(PanelCal);
    PanelSequencer = new wxPanel(Notebook1, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxWANTS_CHARS, _T("ID_PANEL7"));
    m_mgr = new wxAuiManager(PanelSequencer, wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_DEFAULT);
    Notebook1->AddPage(PanelSetup, _("Setup"), true);
    Notebook1->AddPage(PanelPreview, _("Layout"));
    Notebook1->AddPage(PanelCal, _("Schedule"));
    Notebook1->AddPage(PanelSequencer, _("Sequencer"));
    MainAuiManager->AddPane(Notebook1, wxAuiPaneInfo().Name(_T("MainPain")).CenterPane().Caption(_("Pane caption")).Floatable().PaneBorder(false));
    AUIStatusBar = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StatusBarSizer = new wxGridBagSizer(0, 0);
    StatusBarSizer->AddGrowableRow(0);
    StatusText = new wxStaticText(AUIStatusBar, ID_STATICTEXT6, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StatusBarSizer->Add(StatusText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxEXPAND, 2);
    Panel1 = new wxPanel(AUIStatusBar, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    Panel1->SetMinSize(wxDLG_UNIT(AUIStatusBar,wxSize(100,-1)));
    GaugeSizer = new wxFlexGridSizer(1, 1, 0, 0);
    GaugeSizer->AddGrowableCol(0);
    ProgressBar = new wxGauge(Panel1, ID_GAUGE1, 100, wxDefaultPosition, wxDLG_UNIT(Panel1,wxSize(100,-1)), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    GaugeSizer->Add(ProgressBar, 0, wxEXPAND, 0);
    Panel1->SetSizer(GaugeSizer);
    GaugeSizer->Fit(Panel1);
    GaugeSizer->SetSizeHints(Panel1);
    StatusBarSizer->Add(Panel1, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FileNameText = new wxStaticText(AUIStatusBar, ID_STATICTEXT7, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    StatusBarSizer->Add(FileNameText, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxEXPAND, 2);
    AUIStatusBar->SetSizer(StatusBarSizer);
    StatusBarSizer->Fit(AUIStatusBar);
    StatusBarSizer->SetSizeHints(AUIStatusBar);
    MainAuiManager->AddPane(AUIStatusBar, wxAuiPaneInfo().Name(_T("Status Bar")).DefaultPane().Caption(_("Status bar")).CaptionVisible(false).CloseButton(false).Bottom().DockFixed().Dockable(false).Floatable(false).FloatingPosition(wxPoint(0,0)).FloatingSize(wxSize(0,0)).Movable(false).PaneBorder(false));
    MainAuiManager->Update();
    MenuBar = new wxMenuBar();
    MenuFile = new wxMenu();
    MenuItem3 = new wxMenuItem(MenuFile, ID_NEW_SEQUENCE, _("New Sequence\tCtrl-n"), wxEmptyString, wxITEM_NORMAL);
    MenuItem3->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_OTHER));
    MenuFile->Append(MenuItem3);
    MenuItem_File_Open_Sequence = new wxMenuItem(MenuFile, ID_OPEN_SEQUENCE, _("Open Sequence\tCTRL-o"), wxEmptyString, wxITEM_NORMAL);
    MenuItem_File_Open_Sequence->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_OTHER));
    MenuFile->Append(MenuItem_File_Open_Sequence);
    MenuItem_File_Save_Sequence = new wxMenuItem(MenuFile, IS_SAVE_SEQ, _("Save Sequence\tCTRL-S"), wxEmptyString, wxITEM_NORMAL);
    MenuItem_File_Save_Sequence->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_OTHER));
    MenuFile->Append(MenuItem_File_Save_Sequence);
    MenuItem_File_Save_Sequence->Enable(false);
    MenuItem_File_SaveAs_Sequence = new wxMenuItem(MenuFile, ID_SAVE_AS_SEQUENCE, _("Save Sequence As"), wxEmptyString, wxITEM_NORMAL);
    MenuItem_File_SaveAs_Sequence->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_OTHER));
    MenuFile->Append(MenuItem_File_SaveAs_Sequence);
    MenuItem_File_Close_Sequence = new wxMenuItem(MenuFile, ID_CLOSE_SEQ, _("Close Sequence"), wxEmptyString, wxITEM_NORMAL);
    MenuFile->Append(MenuItem_File_Close_Sequence);
    MenuItem_File_Close_Sequence->Enable(false);
    MenuFile->AppendSeparator();
    MenuItem5 = new wxMenuItem(MenuFile, ID_MENUITEM2, _("Select Show Folder\tF9"), wxEmptyString, wxITEM_NORMAL);
    MenuItem5->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FOLDER")),wxART_OTHER));
    MenuFile->Append(MenuItem5);
    MenuItemBackup = new wxMenuItem(MenuFile, ID_FILE_BACKUP, _("Backup\tF10"), wxEmptyString, wxITEM_NORMAL);
    MenuItemBackup->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_HARDDISK")),wxART_OTHER));
    MenuFile->Append(MenuItemBackup);
    mAltBackupMenuItem = new wxMenuItem(MenuFile, ID_FILE_ALTBACKUP, _("Alternate Backup\tF11"), wxEmptyString, wxITEM_NORMAL);
    MenuFile->Append(mAltBackupMenuItem);
    QuitMenuItem = new wxMenuItem(MenuFile, wxID_EXIT, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    QuitMenuItem->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")),wxART_OTHER));
    MenuFile->Append(QuitMenuItem);
    MenuBar->Append(MenuFile, _("&File"));
    Menu3 = new wxMenu();
    MenuItem37 = new wxMenuItem(Menu3, wxID_UNDO, _("Undo\tCtrl-z"), wxEmptyString, wxITEM_NORMAL);
    MenuItem37->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_UNDO")),wxART_OTHER));
    Menu3->Append(MenuItem37);
    Menu3->AppendSeparator();
    MenuItem34 = new wxMenuItem(Menu3, wxID_CUT, _("Cut\tCTRL-x"), wxEmptyString, wxITEM_NORMAL);
    MenuItem34->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_CUT")),wxART_OTHER));
    Menu3->Append(MenuItem34);
    MenuItem35 = new wxMenuItem(Menu3, wxID_COPY, _("Copy\tCTRL-c"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_COPY")),wxART_OTHER));
    Menu3->Append(MenuItem35);
    MenuItem36 = new wxMenuItem(Menu3, wxID_PASTE, _("Paste\tCTRL-v"), wxEmptyString, wxITEM_NORMAL);
    MenuItem36->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PASTE")),wxART_OTHER));
    Menu3->Append(MenuItem36);
    MenuBar->Append(Menu3, _("&Edit"));
    Menu1 = new wxMenu();
    ActionTestMenuItem = new wxMenuItem(Menu1, ID_MENUITEM13, _("&Test"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(ActionTestMenuItem);
    MenuItemConvert = new wxMenuItem(Menu1, ID_MENUITEM_CONVERT, _("&Convert"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItemConvert);
    Menu_GenerateCustomModel = new wxMenuItem(Menu1, ID_MENUITEM_GenerateCustomModel, _("&Generate Custom Model"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(Menu_GenerateCustomModel);
    MenuItemCheckSequence = new wxMenuItem(Menu1, ID_MNU_CHECKSEQ, _("C&heck Sequence"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItemCheckSequence);
    MenuItem_ViewLog = new wxMenuItem(Menu1, ID_MENU_VIEW_LOG, _("&View Log"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem_ViewLog);
    MenuItem38 = new wxMenuItem(Menu1, ID_MENUITEM18, _("&Package Log FIles"), _("Packages up current configuration, logs and sequence for reporting a problem to development team."), wxITEM_NORMAL);
    Menu1->Append(MenuItem38);
    mExportModelsMenuItem = new wxMenuItem(Menu1, ID_EXPORT_MODELS, _("E&xport Models"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mExportModelsMenuItem);
    MenuItem_ExportEffects = new wxMenuItem(Menu1, ID_MNU_EXPORT_EFFECTS, _("Export &Effects"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem_ExportEffects);
    MenuItem_FPP_Connect = new wxMenuItem(Menu1, ID_MENU_FPP_CONNECT, _("&FPP Connect"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem_FPP_Connect);
    MenuBar->Append(Menu1, _("&Tools"));
    MenuPlaylist = new wxMenu();
    MenuItemSavePlaylists = new wxMenuItem(MenuPlaylist, idMenuSaveSched, _("Save Playlists"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemSavePlaylists);
    MenuItemAddList = new wxMenuItem(MenuPlaylist, idMenuAddList, _("Add"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemAddList);
    MenuItemRenameList = new wxMenuItem(MenuPlaylist, idMenuRenameList, _("Rename"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemRenameList);
    MenuItemDelList = new wxMenuItem(MenuPlaylist, idMenuDelList, _("Delete"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemDelList);
    MenuItemRefresh = new wxMenuItem(MenuPlaylist, ID_MENUITEM1, _("Refresh"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemRefresh);
    MenuItemCustomScript = new wxMenuItem(MenuPlaylist, idCustomScript, _("Custom Script"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemCustomScript);
    MenuBar->Append(MenuPlaylist, _("&Playlist"));
    MenuView = new wxMenu();
    MenuItem_ViewZoomIn = new wxMenuItem(MenuView, wxID_ZOOM_IN, _("Zoom In"), wxEmptyString, wxITEM_NORMAL);
    MenuView->Append(MenuItem_ViewZoomIn);
    MenuItem_ViewZoomOut = new wxMenuItem(MenuView, wxID_ZOOM_OUT, _("Zoom Out"), wxEmptyString, wxITEM_NORMAL);
    MenuView->Append(MenuItem_ViewZoomOut);
    MenuView->AppendSeparator();
    MenuItemPerspectives = new wxMenu();
    MenuItemViewSavePerspective = new wxMenuItem(MenuItemPerspectives, ID_MENUITEM_SAVE_PERSPECTIVE, _("Save Current"), wxEmptyString, wxITEM_NORMAL);
    MenuItemPerspectives->Append(MenuItemViewSavePerspective);
    MenuItemViewSaveAsPerspective = new wxMenuItem(MenuItemPerspectives, ID_MENUITEM_SAVE_AS_PERSPECTIVE, _("Save As New"), wxEmptyString, wxITEM_NORMAL);
    MenuItemPerspectives->Append(MenuItemViewSaveAsPerspective);
    MenuItemLoadEditPerspective = new wxMenuItem(MenuItemPerspectives, ID_MENUITEM_LOAD_PERSPECTIVE, _("Edit/Load"), wxEmptyString, wxITEM_NORMAL);
    MenuItemPerspectives->Append(MenuItemLoadEditPerspective);
    MenuItemPerspectives->AppendSeparator();
    MenuView->Append(ID_MENUITEM7, _("Perspectives"), MenuItemPerspectives, wxEmptyString);
    MenuItem18 = new wxMenu();
    MenuItemDisplayElements = new wxMenuItem(MenuItem18, ID_MENUITEM_DISPLAY_ELEMENTS, _("Display Elements"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItemDisplayElements);
    MenuItem20 = new wxMenuItem(MenuItem18, ID_MENUITEM12, _("Model Preview"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem20);
    MenuItem6 = new wxMenuItem(MenuItem18, ID_MENUITEM3, _("House Preview"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem6);
    MenuItem22 = new wxMenuItem(MenuItem18, ID_MENUITEM14, _("Effect Settings"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem22);
    MenuItem23 = new wxMenuItem(MenuItem18, ID_MENUITEM15, _("Colors"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem23);
    MenuItem24 = new wxMenuItem(MenuItem18, ID_MENUITEM16, _("Layer Blending"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem24);
    MenuItem32 = new wxMenuItem(MenuItem18, ID_MENUITEM9, _("Layer Settings"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem32);
    MenuItem25 = new wxMenuItem(MenuItem18, ID_MENUITEM17, _("Effect Dropper"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem25);
    MenuItemEffectAssistWindow = new wxMenuItem(MenuItem18, ID_MENUITEM_EFFECT_ASSIST_WINDOW, _("Effect Assist"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItemEffectAssistWindow);
    MenuItem18->AppendSeparator();
    MenuItem26 = new wxMenuItem(MenuItem18, ID_MENUITEM_WINDOWS_PERSPECTIVE, _("Perspectives"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem26);
    MenuItem21 = new wxMenuItem(MenuItem18, ID_MENUITEM_WINDOWS_DOCKALL, _("Dock All"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem21);
    MenuItem33 = new wxMenuItem(MenuItem18, ID_MENUITEM11, _("Reset to Defaults"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->Append(MenuItem33);
    MenuView->Append(ID_MENUITEM10, _("Windows"), MenuItem18, wxEmptyString);
    MenuBar->Append(MenuView, _("&View"));
    AudioMenu = new wxMenu();
    MenuItem8 = new wxMenuItem(AudioMenu, ID_PLAY_FULL, _("Play Full Speed"), wxEmptyString, wxITEM_RADIO);
    AudioMenu->Append(MenuItem8);
    MenuItem9 = new wxMenuItem(AudioMenu, ID_PLAY_3_4, _("Play 3/4 Speed"), wxEmptyString, wxITEM_RADIO);
    AudioMenu->Append(MenuItem9);
    MenuItem30 = new wxMenuItem(AudioMenu, ID_PLAY_1_2, _("Play 1/2 Speed"), wxEmptyString, wxITEM_RADIO);
    AudioMenu->Append(MenuItem30);
    MenuItem31 = new wxMenuItem(AudioMenu, ID_PLAY_1_4, _("Play 1/4 Speed"), wxEmptyString, wxITEM_RADIO);
    AudioMenu->Append(MenuItem31);
    MenuBar->Append(AudioMenu, _("&Audio"));
    Menu2 = new wxMenu();
    MenuItem29 = new wxMenuItem(Menu2, ID_IMPORT_EFFECTS, _("Import Effects"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem29);
    MenuBar->Append(Menu2, _("&Import"));
    MenuSettings = new wxMenu();
    Menu_Settings_Sequence = new wxMenuItem(MenuSettings, ID_SEQ_SETTINGS, _("Sequence Settings"), wxEmptyString, wxITEM_NORMAL);
    MenuSettings->Append(Menu_Settings_Sequence);
    mRenderOnSaveMenuItem = new wxMenuItem(MenuSettings, ID_RENDER_ON_SAVE, _("Render On Save"), wxEmptyString, wxITEM_CHECK);
    MenuSettings->Append(mRenderOnSaveMenuItem);
    mRenderOnSaveMenuItem->Check(true);
    mBackupOnSaveMenuItem = new wxMenuItem(MenuSettings, ID_BACKUP_ON_SAVE, _("Backup On Save"), wxEmptyString, wxITEM_CHECK);
    MenuSettings->Append(mBackupOnSaveMenuItem);
    MenuItem_BackupOnLaunch = new wxMenuItem(MenuSettings, ID_MENU_BACKUP_ON_LAUNCH, _("Backup On Launch"), _("Recommended."), wxITEM_CHECK);
    MenuSettings->Append(MenuItem_BackupOnLaunch);
    MenuItem_BackupOnLaunch->Check(true);
    mAltBackupLocationMenuItem = new wxMenuItem(MenuSettings, ID_ALT_BACKUPLOCATION, _("Alt Backup Location"), wxEmptyString, wxITEM_NORMAL);
    MenuSettings->Append(mAltBackupLocationMenuItem);
    ToolIconSizeMenu = new wxMenu();
    MenuItem10 = new wxMenuItem(ToolIconSizeMenu, ID_MENUITEM_ICON_SMALL, _("Small\tALT-1"), wxEmptyString, wxITEM_RADIO);
    ToolIconSizeMenu->Append(MenuItem10);
    MenuItem11 = new wxMenuItem(ToolIconSizeMenu, ID_MENUITEM_ICON_MEDIUM, _("Medium\tALT-2"), wxEmptyString, wxITEM_RADIO);
    ToolIconSizeMenu->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(ToolIconSizeMenu, ID_MENUITEM_ICON_LARGE, _("Large\tALT-3"), wxEmptyString, wxITEM_RADIO);
    ToolIconSizeMenu->Append(MenuItem12);
    MenuItem14 = new wxMenuItem(ToolIconSizeMenu, ID_MENUITEM_ICON_XLARGE, _("Extra Large\tALT-4"), wxEmptyString, wxITEM_RADIO);
    ToolIconSizeMenu->Append(MenuItem14);
    MenuSettings->Append(ID_MENUITEM4, _("Tool Icon Size"), ToolIconSizeMenu, wxEmptyString);
    GridSpacingMenu = new wxMenu();
    MenuItem16 = new wxMenuItem(GridSpacingMenu, ID_MENUITEM_GRID_ICON_XSMALL, _("Extra Small\tCTRL-1"), wxEmptyString, wxITEM_RADIO);
    GridSpacingMenu->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(GridSpacingMenu, ID_MENUITEM_GRID_ICON_SMALL, _("Small\tCTRL-2"), wxEmptyString, wxITEM_RADIO);
    GridSpacingMenu->Append(MenuItem17);
    MenuItem19 = new wxMenuItem(GridSpacingMenu, ID_MENUITEM_GRID_ICON_MEDIUM, _("Medium\tCTRL-3"), wxEmptyString, wxITEM_RADIO);
    GridSpacingMenu->Append(MenuItem19);
    MenuItem27 = new wxMenuItem(GridSpacingMenu, ID_MENUITEM_GRID_ICON_LARGE, _("Large\tCTRL-4"), wxEmptyString, wxITEM_RADIO);
    GridSpacingMenu->Append(MenuItem27);
    MenuItem28 = new wxMenuItem(GridSpacingMenu, ID_MENUITEM_GRID_ICON_XLARGE, _("Extra Large\tCTRL-5"), wxEmptyString, wxITEM_RADIO);
    GridSpacingMenu->Append(MenuItem28);
    MenuSettings->Append(ID_MENUITEM6, _("Grid Spacing"), GridSpacingMenu, wxEmptyString);
    MenuItem_Grid_Icon_Backgrounds = new wxMenu();
    MenuItemGridIconBackgroundOn = new wxMenuItem(MenuItem_Grid_Icon_Backgrounds, ID_MENUITEM_GRID_ICON_BACKGROUND_ON, _("On"), wxEmptyString, wxITEM_CHECK);
    MenuItem_Grid_Icon_Backgrounds->Append(MenuItemGridIconBackgroundOn);
    MenuItemGridIconBackgroundOn->Check(true);
    MenuItemGridIconBackgroundOff = new wxMenuItem(MenuItem_Grid_Icon_Backgrounds, ID_MENUITEM_GRID_ICON_BACKGROUND_OFF, _("Off"), wxEmptyString, wxITEM_CHECK);
    MenuItem_Grid_Icon_Backgrounds->Append(MenuItemGridIconBackgroundOff);
    MenuSettings->Append(ID_MENUITEM_Grid_Icon_Backgrounds, _("Grid Icon Backgrounds"), MenuItem_Grid_Icon_Backgrounds, wxEmptyString);
    MenuItem1 = new wxMenu();
    MenuItemGridNodeValuesOn = new wxMenuItem(MenuItem1, ID_MENUITEM_GRID_NODE_VALUES_ON, _("On"), wxEmptyString, wxITEM_CHECK);
    MenuItem1->Append(MenuItemGridNodeValuesOn);
    MenuItemGridNodeValuesOn->Check(true);
    MenuItemGridNodeValuesOff = new wxMenuItem(MenuItem1, ID_MENUITEM_GRID_NODE_VALUES_OFF, _("Off"), wxEmptyString, wxITEM_CHECK);
    MenuItem1->Append(MenuItemGridNodeValuesOff);
    MenuSettings->Append(ID_MENUITEM8, _("Grid Node Values"), MenuItem1, wxEmptyString);
    MenuItemRenderMode = new wxMenu();
    MenuItemRenderEraseMode = new wxMenuItem(MenuItemRenderMode, ID_MENU_CANVAS_ERASE_MODE, _("Erase Mode"), wxEmptyString, wxITEM_CHECK);
    MenuItemRenderMode->Append(MenuItemRenderEraseMode);
    MenuItemRenderEraseMode->Check(true);
    MenuItemRenderCanvasMode = new wxMenuItem(MenuItemRenderMode, ID_MENU_CANVAS_CANVAS_MODE, _("Canvas Mode"), wxEmptyString, wxITEM_CHECK);
    MenuItemRenderMode->Append(MenuItemRenderCanvasMode);
    MenuSettings->Append(ID_MENUITEM_RENDER_MODE, _("Render Mode"), MenuItemRenderMode, wxEmptyString)->Enable(false);
    MenuItem7 = new wxMenu();
    MenuItemEffectAssistAlwaysOn = new wxMenuItem(MenuItem7, ID_MENUITEM_EFFECT_ASSIST_ALWAYS_ON, _("Always On"), _("Effect Assist Window will always be active if member of perspective."), wxITEM_CHECK);
    MenuItem7->Append(MenuItemEffectAssistAlwaysOn);
    MenuItemEffectAssistAlwaysOff = new wxMenuItem(MenuItem7, ID_MENUITEM_EFFECT_ASSIST_ALWAYS_OFF, _("Always Off"), _("Effect Assist Window will always be inactive."), wxITEM_CHECK);
    MenuItem7->Append(MenuItemEffectAssistAlwaysOff);
    MenuItemEffectAssistToggleMode = new wxMenuItem(MenuItem7, ID_MENUITEM_EFFECT_ASSIST_TOGGLE, _("Toggle Mode"), _("Effect Assist Window will show only when a supported effect is selected."), wxITEM_CHECK);
    MenuItem7->Append(MenuItemEffectAssistToggleMode);
    MenuItemEffectAssistToggleMode->Check(true);
    MenuSettings->Append(ID_MENUITEM_EFFECT_ASSIST, _("Effect Assist Window"), MenuItem7, wxEmptyString);
    OpenGLMenu = new wxMenu();
    MenuItem40 = new wxMenuItem(OpenGLMenu, ID_MENU_OPENGL_AUTO, _("Auto Detect"), wxEmptyString, wxITEM_RADIO);
    OpenGLMenu->Append(MenuItem40);
    MenuItem41 = new wxMenuItem(OpenGLMenu, ID_MENU_OPENGL_3, _("3.x"), wxEmptyString, wxITEM_RADIO);
    OpenGLMenu->Append(MenuItem41);
    MenuItem42 = new wxMenuItem(OpenGLMenu, ID_MENU_OPENGL_2, _("2.x"), wxEmptyString, wxITEM_RADIO);
    OpenGLMenu->Append(MenuItem42);
    MenuItem43 = new wxMenuItem(OpenGLMenu, ID_MENU_OPENGL_1, _("1.x"), wxEmptyString, wxITEM_RADIO);
    OpenGLMenu->Append(MenuItem43);
    MenuSettings->Append(ID_MENUITEM19, _("OpenGL"), OpenGLMenu, wxEmptyString);
    AutoSaveMenu = new wxMenu();
    MenuItem44 = new wxMenuItem(AutoSaveMenu, ID_MENUITEM_AUTOSAVE_0, _("Disabled"), wxEmptyString, wxITEM_RADIO);
    AutoSaveMenu->Append(MenuItem44);
    MenuItem45 = new wxMenuItem(AutoSaveMenu, ID_MENUITEM_AUTOSAVE_3, _("3 Minutes"), wxEmptyString, wxITEM_RADIO);
    AutoSaveMenu->Append(MenuItem45);
    MenuItem46 = new wxMenuItem(AutoSaveMenu, ID_MENUITEM_AUTOSAVE_10, _("10 Minutes"), wxEmptyString, wxITEM_RADIO);
    AutoSaveMenu->Append(MenuItem46);
    MenuItem47 = new wxMenuItem(AutoSaveMenu, ID_MENUITEM_AUTOSAVE_15, _("15 Minutes"), wxEmptyString, wxITEM_RADIO);
    AutoSaveMenu->Append(MenuItem47);
    MenuItem48 = new wxMenuItem(AutoSaveMenu, ID_MENUITEM_AUTOSAVE_30, _("30 Minutes"), wxEmptyString, wxITEM_RADIO);
    AutoSaveMenu->Append(MenuItem48);
    MenuSettings->Append(ID_MENUITEM20, _("Auto Save"), AutoSaveMenu, wxEmptyString);
    MenuItem_e131sync = new wxMenuItem(MenuSettings, ID_E131_Sync, _("Frame Sync"), _("Only enable this if your controllers support e1.31 sync. You will also need to set the synchronisation universe on the setup tab."), wxITEM_CHECK);
    MenuSettings->Append(MenuItem_e131sync);
    MenuItem13 = new wxMenuItem(MenuSettings, ID_MENUITEM5, _("Reset Toolbars"), wxEmptyString, wxITEM_NORMAL);
    MenuSettings->Append(MenuItem13);
    MenuBar->Append(MenuSettings, _("&Settings"));
    MenuHelp = new wxMenu();
    MenuItem4 = new wxMenuItem(MenuHelp, idMenuHelpContent, _("Content\tF1"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem4);
    MenuItem_Help_Forum = new wxMenuItem(MenuHelp, ID_MENU_HELP_FORMUM, _("Forum"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem_Help_Forum);
    MenuItem_Help_Download = new wxMenuItem(MenuHelp, ID_MENU_HELP_DOWNLOAD, _("Download"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem_Help_Download);
    MenuItem_Help_ReleaseNotes = new wxMenuItem(MenuHelp, ID_MNU_HELP_RELEASE_NOTES, _("Release Notes"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem_Help_ReleaseNotes);
    MenuItem_Help_Isue_Tracker = new wxMenuItem(MenuHelp, ID_MENU_HELP_ISSUE, _("Issue Tracker"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem_Help_Isue_Tracker);
    MenuItem_Help_Facebook = new wxMenuItem(MenuHelp, ID_MENU_HELP_FACEBOOK, _("Facebook"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem_Help_Facebook);
    MenuItem2 = new wxMenuItem(MenuHelp, wxID_ABOUT, _("About"), _("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItem2);
    MenuBar->Append(MenuHelp, _("&Help"));
    SetMenuBar(MenuBar);
    DirDialog1 = new wxDirDialog(this, _("Select Show Directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    Timer1.SetOwner(this, ID_TIMER1);
    Timer_AutoSave.SetOwner(this, ID_TIMER2);
    EffectSettingsTimer.SetOwner(this, ID_TIMER_EFFECT_SETTINGS);

    Connect(ID_AUITOOLBAR_OPENSHOW,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenFolderSelected);
    Connect(ID_AUITOOLBAR_NEWSEQUENCE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonNewSequenceClick);
    Connect(ID_AUITOOLBAR_OPEN,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnBitmapButtonOpenSeqClick);
    Connect(ID_AUITOOLBAR_SAVE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnBitmapButtonSaveSeqClick);
    Connect(ID_AUITOOLBAR_SAVEAS,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonClickSaveAs);
    Connect(ID_AUITOOLBAR_RENDERALL,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemRenderAllClick);
    Connect(ID_AUITOOLBAR_PLAY_NOW,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemPlayButtonClick);
    Connect(ID_AUITOOLBAR_PAUSE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemPauseButtonClick);
    Connect(ID_AUITOOLBAR_STOP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemStopClick);
    Connect(ID_AUITOOLBAR_FIRST_FRAME,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarFirstFrameClick);
    Connect(ID_AUITOOLBAR_LAST_FRAME,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarLastFrameClick);
    Connect(ID_AUITOOLBAR_REPLAY_SECTION,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemReplaySectionClick);
    Connect(ID_AUITOOLBARITEM2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideEffectSettingsWindow);
    Connect(ID_AUITOOLBARITEM5,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideColorWindow);
    Connect(ID_AUITOOLBARITEM7,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideBufferSettingsWindow);
    Connect(ID_AUITOOLBARITEM3,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideLayerTimingWindow);
    Connect(ID_AUITOOLBARITEM1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideModelPreview);
    Connect(ID_AUITOOLBARITEM4,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideHousePreview);
    Connect(ID_AUITOOLBARITEM6,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::ShowHideDisplayElementsWindow);
    Connect(ID_AUITOOLBARITEM8,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemShowHideEffects);
    Connect(ID_PASTE_BY_TIME,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemPasteByTimeClick);
    Connect(ID_PASTE_BY_CELL,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemPasteByCellClick);
    Connect(wxID_ZOOM_IN,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemZoominClick);
    Connect(wxID_ZOOM_OUT,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItem_ZoomOutClick);
    Connect(ID_AUITOOLBARITEM14,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnMenu_Settings_SequenceSelected);
    Connect(ID_BITMAPBUTTON_TAB_INFO,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnBitmapButtonTabInfoClick);
    Connect(ID_BUTTON_STOP_NOW,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonStopNowClick);
    Connect(ID_BUTTON_GRACEFUL_STOP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonGracefulStopClick);
    Connect(ID_BUTTON_LIGHTS_OFF,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonLightsOffClick);
    Connect(ID_CHECKBOX_LIGHT_OUTPUT,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnCheckBoxLightOutputClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenFolderSelected);
    Connect(ID_BUTTON_CHANGE_MEDIA_DIR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::ChangeMediaDirectory);
    Connect(ID_BITMAPBUTTON_Link_Dirs,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnBitmapButton_Link_DirsClick);
    Connect(ID_BUTTON_SAVE_SETUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonSaveSetupClick);
    Connect(ID_BUTTON_ADD_DONGLE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonAddDongleClick);
    Connect(ID_BUTTON_ADD_E131,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonAddE131Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonAddNullClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonArtNETClick);
    Connect(ID_BUTTON_NETWORK_CHANGE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonNetworkChangeClick);
    Connect(ID_BUTTON_NETWORK_DELETE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonNetworkDeleteClick);
    Connect(ID_BUTTON_NETWORK_DELETE_ALL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonNetworkDeleteAllClick);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&xLightsFrame::OnSpinCtrl_SyncUniverseChange);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonNetworkMoveUpClick);
    Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonNetworkMoveDownClick);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkBeginDrag);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkItemSelect);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkItemDeselect);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkItemActivated);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_ITEM_FOCUSED,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkItemFocused);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkItemRClick);
    Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&xLightsFrame::OnGridNetworkKeyDown);
    Connect(ID_CHECKBOX_RUN_SCHEDULE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnCheckBoxRunScheduleClick);
    Connect(ID_BUTTON_SAVE_SCHEDULE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonSaveScheduleClick);
    Connect(ID_BUTTON_ADD_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonAddShowClick);
    Connect(ID_BUTTON_UPDATE_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonUpdateShowClick);
    Connect(ID_BUTTON_DELETE_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonDeleteShowClick);
    Connect(ID_BUTTON_SHOW_DATES_CHANGE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonShowDatesChangeClick);
    Connect(ID_BUTTON_CLEARLOG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonClearLogClick);
    Connect(ID_BUTTON_SAVELOG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xLightsFrame::OnButtonSaveLogClick);
    m_mgr->Connect(wxEVT_AUI_PANE_CLOSE,(wxObjectEventFunction)&xLightsFrame::OnPaneClose,0,this);
    PanelSequencer->Connect(wxEVT_PAINT,(wxObjectEventFunction)&xLightsFrame::OnPanelSequencerPaint,0,this);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&xLightsFrame::OnNotebook1PageChanged1);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING,(wxObjectEventFunction)&xLightsFrame::OnNotebook1PageChanging);
    Connect(ID_NEW_SEQUENCE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnButtonNewSequenceClick);
    Connect(ID_OPEN_SEQUENCE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_File_Open_SequenceSelected);
    Connect(IS_SAVE_SEQ,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_File_Save_SequenceSelected);
    Connect(ID_SAVE_AS_SEQUENCE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_File_SaveAs_SequenceSelected);
    Connect(ID_CLOSE_SEQ,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_File_Close_SequenceSelected);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenFolderSelected);
    Connect(ID_FILE_BACKUP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemBackupSelected);
    Connect(ID_FILE_ALTBACKUP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnmAltBackupMenuItemSelected);
    Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnQuit);
    Connect(ID_MENUITEM13,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnActionTestMenuItemSelected);
    Connect(ID_MENUITEM_CONVERT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemConvertSelected);
    Connect(ID_MENUITEM_GenerateCustomModel,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenu_GenerateCustomModelSelected);
    Connect(ID_MNU_CHECKSEQ,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemCheckSequenceSelected);
    Connect(ID_MENU_VIEW_LOG,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_ViewLogSelected);
    Connect(ID_MENUITEM18,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemPackageDebugFiles);
    Connect(ID_EXPORT_MODELS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnmExportModelsMenuItemSelected);
    Connect(ID_MNU_EXPORT_EFFECTS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_ExportEffectsSelected);
    Connect(ID_MENU_FPP_CONNECT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_FPP_ConnectSelected);
    Connect(idMenuSaveSched,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemSavePlaylistsSelected);
    Connect(idMenuAddList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemAddListSelected);
    Connect(idMenuRenameList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemRenameListSelected);
    Connect(idMenuDelList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemDelListSelected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemRefreshSelected);
    Connect(idCustomScript,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemCustomScriptSelected);
    Connect(wxID_ZOOM_IN,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItemZoominClick);
    Connect(wxID_ZOOM_OUT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnAuiToolBarItem_ZoomOutClick);
    Connect(ID_MENUITEM_SAVE_PERSPECTIVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemViewSavePerspectiveSelected);
    Connect(ID_MENUITEM_SAVE_AS_PERSPECTIVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemViewSaveAsPerspectiveSelected);
    Connect(ID_MENUITEM_LOAD_PERSPECTIVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemLoadEditPerspectiveSelected);
    Connect(ID_MENUITEM_DISPLAY_ELEMENTS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideDisplayElementsWindow);
    Connect(ID_MENUITEM12,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideModelPreview);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideHousePreview);
    Connect(ID_MENUITEM14,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideEffectSettingsWindow);
    Connect(ID_MENUITEM15,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideColorWindow);
    Connect(ID_MENUITEM16,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideLayerTimingWindow);
    Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideBufferSettingsWindow);
    Connect(ID_MENUITEM17,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideEffectDropper);
    Connect(ID_MENUITEM_EFFECT_ASSIST_WINDOW,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideEffectAssistWindow);
    Connect(ID_MENUITEM_WINDOWS_PERSPECTIVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHidePerspectivesWindow);
    Connect(ID_MENUITEM_WINDOWS_DOCKALL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuDockAllSelected);
    Connect(ID_MENUITEM11,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ResetWindowsToDefaultPositions);
    Connect(ID_PLAY_FULL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetPlaySpeed);
    Connect(ID_PLAY_3_4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetPlaySpeed);
    Connect(ID_PLAY_1_2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetPlaySpeed);
    Connect(ID_PLAY_1_4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetPlaySpeed);
    Connect(ID_IMPORT_EFFECTS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemImportEffects);
    Connect(ID_SEQ_SETTINGS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenu_Settings_SequenceSelected);
    Connect(ID_RENDER_ON_SAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemRenderOnSave);
    Connect(ID_BACKUP_ON_SAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnmBackupOnSaveSelected);
    Connect(ID_MENU_BACKUP_ON_LAUNCH,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_BackupOnLaunchSelected);
    Connect(ID_ALT_BACKUPLOCATION,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnmAltBackupLocationMenuItemSelected);
    Connect(ID_MENUITEM_ICON_SMALL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetToolIconSize);
    Connect(ID_MENUITEM_ICON_MEDIUM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetToolIconSize);
    Connect(ID_MENUITEM_ICON_LARGE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetToolIconSize);
    Connect(ID_MENUITEM_ICON_XLARGE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetToolIconSize);
    Connect(ID_MENUITEM_GRID_ICON_XSMALL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetIconSize);
    Connect(ID_MENUITEM_GRID_ICON_SMALL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetIconSize);
    Connect(ID_MENUITEM_GRID_ICON_MEDIUM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetIconSize);
    Connect(ID_MENUITEM_GRID_ICON_LARGE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetIconSize);
    Connect(ID_MENUITEM_GRID_ICON_XLARGE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::SetIconSize);
    Connect(ID_MENUITEM_GRID_ICON_BACKGROUND_ON,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnSetGridIconBackground);
    Connect(ID_MENUITEM_GRID_ICON_BACKGROUND_OFF,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnSetGridIconBackground);
    Connect(ID_MENUITEM_GRID_NODE_VALUES_ON,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnSetGridNodeValues);
    Connect(ID_MENUITEM_GRID_NODE_VALUES_OFF,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnSetGridNodeValues);
    Connect(ID_MENU_CANVAS_ERASE_MODE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemRenderEraseModeSelected);
    Connect(ID_MENU_CANVAS_CANVAS_MODE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemRenderCanvasModeSelected);
    Connect(ID_MENUITEM_EFFECT_ASSIST_ALWAYS_ON,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemEffectAssistAlwaysOnSelected);
    Connect(ID_MENUITEM_EFFECT_ASSIST_ALWAYS_OFF,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemEffectAssistAlwaysOffSelected);
    Connect(ID_MENUITEM_EFFECT_ASSIST_TOGGLE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItemEffectAssistToggleModeSelected);
    Connect(ID_MENU_OPENGL_AUTO,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenGLSelected);
    Connect(ID_MENU_OPENGL_3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenGLSelected);
    Connect(ID_MENU_OPENGL_2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenGLSelected);
    Connect(ID_MENU_OPENGL_1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuOpenGLSelected);
    Connect(ID_MENUITEM_AUTOSAVE_0,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::AutoSaveIntervalSelected);
    Connect(ID_MENUITEM_AUTOSAVE_3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::AutoSaveIntervalSelected);
    Connect(ID_MENUITEM_AUTOSAVE_10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::AutoSaveIntervalSelected);
    Connect(ID_MENUITEM_AUTOSAVE_15,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::AutoSaveIntervalSelected);
    Connect(ID_MENUITEM_AUTOSAVE_30,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::AutoSaveIntervalSelected);
    Connect(ID_E131_Sync,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_e131syncSelected);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ResetToolbarLocations);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnBitmapButtonTabInfoClick);
    Connect(ID_MENU_HELP_FORMUM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_Help_ForumSelected);
    Connect(ID_MENU_HELP_DOWNLOAD,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_Help_DownloadSelected);
    Connect(ID_MNU_HELP_RELEASE_NOTES,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_Help_ReleaseNotesSelected);
    Connect(ID_MENU_HELP_ISSUE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_Help_Isue_TrackerSelected);
    Connect(ID_MENU_HELP_FACEBOOK,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnMenuItem_Help_FacebookSelected);
    Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&xLightsFrame::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&xLightsFrame::OnTimer_AutoSaveTrigger);
    Connect(ID_TIMER_EFFECT_SETTINGS,wxEVT_TIMER,(wxObjectEventFunction)&xLightsFrame::OnEffectSettingsTimerTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&xLightsFrame::OnClose);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&xLightsFrame::OnResize);
    //*)

    AddWindowsMenu();

    // This is for keith ... I like my debug version to be distinctive so I can tell it apart from the prior version
    #ifndef NDEBUG
        #ifdef _MSC_VER
            Notebook1->SetBackgroundColour(*wxGREEN);
        #endif
    #endif

    logger_base.debug("xLightsFrame constructor UI code done.");

    //need to direct these menu items to different places depending on what is active
    Connect(wxID_UNDO, wxEVT_MENU,(wxObjectEventFunction)&xLightsFrame::DoMenuAction);
    Connect(wxID_REDO, wxEVT_MENU,(wxObjectEventFunction)&xLightsFrame::DoMenuAction);
    Connect(wxID_CUT, wxEVT_MENU,(wxObjectEventFunction)&xLightsFrame::DoMenuAction);
    Connect(wxID_COPY, wxEVT_MENU,(wxObjectEventFunction)&xLightsFrame::DoMenuAction);
    Connect(wxID_PASTE, wxEVT_MENU,(wxObjectEventFunction)&xLightsFrame::DoMenuAction);

	mRendering = false;

    AddEffectToolbarButtons(effectManager, EffectsToolBar);
    wxSize sz = EffectsToolBar->GetSize();
    wxAuiPaneInfo &info = MainAuiManager->GetPane("EffectsToolBar");
    info.BestSize(sz);
    MainAuiManager->Update();

    SetTitle( xlights_base_name + xlights_qualifier + " (Ver " + xlights_version_string + ") " + xlights_build_date );

    CheckBoxLightOutput = new AUIToolbarButtonWrapper(OutputToolBar, ID_CHECKBOX_LIGHT_OUTPUT);
    ButtonGracefulStop = new AUIToolbarButtonWrapper(OutputToolBar, ID_BUTTON_GRACEFUL_STOP);
    ButtonPasteByTime = new AUIToolbarButtonWrapper(EditToolBar, ID_PASTE_BY_TIME);
    ButtonPasteByCell = new AUIToolbarButtonWrapper(EditToolBar, ID_PASTE_BY_CELL);
    ButtonPasteByTime->SetValue(true);
    ButtonPasteByCell->SetValue(false);
    mResetToolbars = false;
    mRenderOnSave = true;
    mBackupOnSave = false;
    mBackupOnLaunch = true;
    me131Sync = false;
    mAltBackupDir = "";
    mIconSize = 16;
    xout = 0;

    StatusBarSizer->AddGrowableCol(0,2);
    StatusBarSizer->AddGrowableCol(2,1);
    ProgressBar->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&xLightsFrame::OnProgressBarDoubleClick, nullptr, this);
    ProgressBar->Hide();
    renderProgressDialog = nullptr;
    renderProgressInfo = nullptr;
    selectedEffectPalette = "";
    selectedEffect = nullptr;
    playStartTime = playEndTime = 0;
    replaySection = false;
    playType = 0;
    playModel = nullptr;
	mLoopAudio = false;
    playSpeed = 1.0;
    playAnimation = false;

    UnsavedRgbEffectsChanges = false;
    UnsavedPlaylistChanges = false;
    UnsavedNetworkChanges = false;
    mStoredLayoutGroup = "Default";
    mDefaultNetworkSaveBtnColor = ButtonSaveSetup->GetBackgroundColour();


    logger_base.debug("xLightsFrame constructor creating sequencer.");

    CreateSequencer();

    logger_base.debug("xLightsFrame constructor sequencer creation done.");

    layoutPanel = new LayoutPanel(PanelPreview, this, PanelSequencer);
    logger_base.debug("LayoutPanel creation done.");
    FlexGridSizerPreview->Add(layoutPanel, 1, wxALL | wxEXPAND, 5);
    FlexGridSizerPreview->Fit(PanelPreview);
    FlexGridSizerPreview->SetSizeHints(PanelPreview);

    modelPreview = layoutPanel->GetMainPreview();
    logger_base.debug("LayoutPanel setup done.");


    playIcon = wxBitmap(control_play_blue_icon);
    pauseIcon = wxBitmap(control_pause_blue_icon);

    Grid1HasFocus = false; //set this before grid gets any events -DJ


    wxIconBundle icons;
    icons.AddIcon(wxIcon(xlights_16_xpm));
    icons.AddIcon(wxIcon(xlights_32_xpm));
    icons.AddIcon(wxIcon(xlights_64_xpm));
    icons.AddIcon(wxIcon(xlights_128_xpm));
    icons.AddIcon(wxIcon(xlights_xpm));

    SetIcons(icons);
    logger_base.debug("IconBundle creation done.");


    SetName("xLights");
    wxPersistenceManager::Get().RegisterAndRestore(this);
    logger_base.debug("Window Location Restored.");

    wxConfigBase* config = wxConfigBase::Get();
    if (config == nullptr)
    {
        logger_base.error("Null config ... this wont end well.");
    }

    effGridPrevX = 0;
    effGridPrevY = 0;
    mSavedChangeCount = 0;
    mLastAutosaveCount = 0;

    logger_base.debug("xLightsFrame constructor loading network list.");

    // Load headings into network list
    wxListItem itemCol;

    itemCol.SetText(_T("Output #"));
    itemCol.SetImage(-1);
    GridNetwork->InsertColumn(0, itemCol);

    itemCol.SetText(_T("Network Type"));
    itemCol.SetImage(-1);
    GridNetwork->InsertColumn(1, itemCol);

    itemCol.SetText(_T("Port"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    GridNetwork->InsertColumn(2, itemCol);

    itemCol.SetText(_T("Baud Rate or E1.31 Univ"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    GridNetwork->InsertColumn(3, itemCol);

    itemCol.SetText(_T("Num Channels"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    GridNetwork->InsertColumn(4, itemCol);

    itemCol.SetText(_T("xLights/Vixen/FPP Mapping"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    GridNetwork->InsertColumn(5, itemCol);

    itemCol.SetText(_T("Active"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    GridNetwork->InsertColumn(6, itemCol);

	itemCol.SetText(_T("Description"));
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	GridNetwork->InsertColumn(7, itemCol);

    GridNetwork->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    GridNetwork->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    GridNetwork->SetColumnWidth(2, 100);
    GridNetwork->SetColumnWidth(3, wxLIST_AUTOSIZE_USEHEADER);
    GridNetwork->SetColumnWidth(4, 100);
    GridNetwork->SetColumnWidth(5, 170);
    GridNetwork->SetColumnWidth(6, wxLIST_AUTOSIZE_USEHEADER);
	GridNetwork->SetColumnWidth(7, wxLIST_AUTOSIZE);

    // get list of most recently used directories
    wxString dir,mru_name;
    int idx;
    for (int i=0; i<MRU_LENGTH; i++)
    {
        mru_name=wxString::Format("mru%d",i);
        dir.clear();
        if ( config->Read(mru_name, &dir) )
        {
            if (!dir.IsEmpty())
            {
                idx=mru.Index(dir);
                if (idx == wxNOT_FOUND) mru.Add(dir);
            }
        }
        mru_MenuItem[i] = nullptr;
    }

    logger_base.debug("xLightsFrame constructor loading config.");

    dir.clear();
    bool ok = true;
    if (!xLightsApp::showDir.IsNull())
    {
        dir = xLightsApp::showDir;
    }
    else
    {
        ok = config->Read("LastDir", &dir);
        //wxString ConvertDir;
        //ConvertDir.clear();
        //if (ok && !config->Read("ConvertDir", &ConvertDir))
        //{
        //    ConvertDir=dir;
        //}
        //FileDialogConvert->SetDirectory(ConvertDir);
    }
    logger_base.debug("Show directory %s.", (const char *)dir.c_str());

    if (!xLightsApp::mediaDir.IsNull())
    {
        mediaDirectory = xLightsApp::mediaDir;
    }
    else if (ok && !config->Read(_("MediaDir"), &mediaDirectory))
    {
        mediaDirectory=dir;
    }
    ObtainAccessToURL(mediaDirectory.ToStdString());

    logger_base.debug("Media directory %s.", (const char *)mediaDirectory.c_str());
    MediaDirectoryLabel->SetLabel(mediaDirectory);

    wxString tbData = config->Read("ToolbarLocations");
    if (tbData.StartsWith(TOOLBAR_SAVE_VERSION))
    {
        MainAuiManager->LoadPerspective(tbData.Right(tbData.size() - 5));
    }
    logger_base.debug("Perspectives loaded.");

    config->Read("xLightsRenderOnSave", &mRenderOnSave, true);
    mRenderOnSaveMenuItem->Check(mRenderOnSave);
    logger_base.debug("Render on save: %s.", mRenderOnSave? "true" : "false");
    config->Read("xLightsBackupOnSave", &mBackupOnSave, false);
    mBackupOnSaveMenuItem->Check(mBackupOnSave);
    logger_base.debug("Backup on save: %s.", mBackupOnSave? "true" : "false");

    config->Read("xLightsBackupOnLaunch", &mBackupOnLaunch, true);
    MenuItem_BackupOnLaunch->Check(mBackupOnLaunch);
    logger_base.debug("Backup on launch: %s.", mBackupOnLaunch? "true" : "false");

    config->Read(_("xLightsAltBackupDir"), &mAltBackupDir);
    logger_base.debug("Alternate Backup Dir: '%s'.", (const char *)mAltBackupDir.c_str());

    if (wxDir::Exists(mAltBackupDir))
    {
        mAltBackupMenuItem->SetHelp(mAltBackupDir);
    }
    else
    {
        mAltBackupMenuItem->SetHelp("");
    }

    config->Read("xLightsIconSize", &mIconSize, 16);
    int isid = ID_MENUITEM_ICON_SMALL;
    if (mIconSize == 24) {
        isid = ID_MENUITEM_ICON_MEDIUM;
    } else if (mIconSize == 32) {
        isid = ID_MENUITEM_ICON_LARGE;
    } else if (mIconSize == 48) {
        isid = ID_MENUITEM_ICON_XLARGE;
    }
    wxCommandEvent event(wxEVT_NULL, isid);
    SetToolIconSize(event);
    logger_base.debug("Icon size: %d.", mIconSize);

    config->Read("AutoSaveInterval", &AutoSaveInterval, 3);
    id = ID_MENUITEM_AUTOSAVE_0;
    switch (AutoSaveInterval) {
        case 3:
            id = ID_MENUITEM_AUTOSAVE_3;
            break;
        case 10:
            id = ID_MENUITEM_AUTOSAVE_10;
            break;
        case 15:
            id = ID_MENUITEM_AUTOSAVE_15;
            break;
        case 30:
            id = ID_MENUITEM_AUTOSAVE_30;
            break;
    }
    wxCommandEvent asEvent(wxEVT_NULL, id);
    AutoSaveIntervalSelected(asEvent);
    logger_base.debug("Autosave interval: %d.", AutoSaveInterval);

    int glVer = 99;
    config->Read("ForceOpenGLVer", &glVer, 99);
    if (glVer != 99) {
        int lastGlVer;
        config->Read("LastOpenGLVer", &lastGlVer, 0);
        if (lastGlVer == 0) {
            config->Write("ForceOpenGLVer", 99);
            glVer = 99;
        } else if (glVer != lastGlVer) {
            CallAfter(&xLightsFrame::MaybePackageAndSendDebugFiles);
        }
    }
    logger_base.debug("Force OpenGL version: %d.", glVer);

    config->Write("LastOpenGLVer", glVer);
    switch (glVer) {
        case 1:
            OpenGLMenu->Check(ID_MENU_OPENGL_1, true);
            break;
        case 2:
            OpenGLMenu->Check(ID_MENU_OPENGL_2, true);
            break;
        case 3:
            OpenGLMenu->Check(ID_MENU_OPENGL_3, true);
            break;
        default:
            OpenGLMenu->Check(ID_MENU_OPENGL_AUTO, true);
            break;
    }

    config->Read("xLightsGridSpacing", &mGridSpacing, 16);
    if (mGridSpacing != 16)
    {
        int idi = ID_MENUITEM_GRID_ICON_MEDIUM;
        if (mGridSpacing == 32)
        {
            idi = ID_MENUITEM_GRID_ICON_LARGE;
        }
        else if (mGridSpacing >= 48)
        {
            idi = ID_MENUITEM_GRID_ICON_XLARGE;
        }
        else if (mGridSpacing <= 12)
        {
            idi = ID_MENUITEM_GRID_ICON_XSMALL;
        }
        wxCommandEvent eventi(wxEVT_NULL, idi);
        SetIconSize(eventi);
    }
    logger_base.debug("Grid spacing: %d.", mGridSpacing);

    config->Read("xLightsGridIconBackgrounds", &mGridIconBackgrounds, true);
    {
        int idb = mGridIconBackgrounds ? ID_MENUITEM_GRID_ICON_BACKGROUND_ON : ID_MENUITEM_GRID_ICON_BACKGROUND_OFF;
        wxCommandEvent eventb(wxEVT_NULL, idb);
        OnSetGridIconBackground(eventb);
    }
    logger_base.debug("Grid icon backgrounds: %s.", mGridIconBackgrounds ? "true" : "false");

    config->Read("xLightsGridNodeValues", &mGridNodeValues, true);
    {
        int idg = mGridNodeValues ? ID_MENUITEM_GRID_NODE_VALUES_ON : ID_MENUITEM_GRID_NODE_VALUES_OFF;
        wxCommandEvent eventg(wxEVT_NULL, idg);
        OnSetGridNodeValues(eventg);
    }
    logger_base.debug("Grid node values: %s.", mGridNodeValues ? "true" : "false");

    config->Read("xLightsEffectAssistMode", &mEffectAssistMode, EFFECT_ASSIST_TOGGLE_MODE);
    MenuItemEffectAssistAlwaysOn->Check(mEffectAssistMode==EFFECT_ASSIST_ALWAYS_ON);
    MenuItemEffectAssistAlwaysOff->Check(mEffectAssistMode==EFFECT_ASSIST_ALWAYS_OFF);
    MenuItemEffectAssistToggleMode->Check(mEffectAssistMode==EFFECT_ASSIST_TOGGLE_MODE);
    logger_base.debug("Effect Assist Mode: %s.", mEffectAssistMode ? "true" : "false");

    InitEffectsPanel(EffectsPanel1);
    logger_base.debug("Effects panel initialised.");

    EffectTreeDlg = nullptr;  // must be before any call to SetDir

    // Check if schedule should be running
    long RunFlag=0;

    config->Read(_("RunSchedule"), &RunFlag);
    //delete config;  // close config before calling SetDir, which will open config
    if (RunFlag && xLightsApp::RunPrompt) //give user a chance to edit before running -DJ
        if (wxMessageBox("Auto-run schedule?", "Confirm", wxYES_DEFAULT | wxYES_NO) != wxYES) RunFlag = 0; //, main_frame);
    logger_base.debug("Run Schedule: %s.", RunFlag ? "true" : "false");

    SetPlayMode(play_off);
    ResetEffectsXml();
    EnableSequenceControls(true);
    UpdateShowDates(wxDateTime::Now(),wxDateTime::Now());
    if (ok && !dir.IsEmpty())
    {
        if (!SetDir(dir)) {
            while (!PromptForShowDirectory()) {}
        }
    }
    else
    {
        PromptForShowDirectory();
    }

    MixTypeChanged=true;
    basic.setFrame(this);

    // I create this but we only use it for the scheduler
    PlayerDlg = new PlayerFrame(this, ID_PLAYER_DIALOG);
    if (RunFlag && !ShowEvents.IsEmpty())
    {
        // open ports
        Notebook1->ChangeSelection(SCHEDULETAB);
        CheckBoxLightOutput->SetValue(true);
        CheckBoxRunSchedule->SetValue(true);
        EnableOutputs();
        CheckRunSchedule();
    }
    else
    {
        Notebook1->ChangeSelection(SETUPTAB);
        EnableNetworkChanges();
    }
    wxImage::AddHandler(new wxGIFHandler);

    config->Read("xLightse131Sync", &me131Sync, false);
    MenuItem_e131sync->Check(me131Sync);
    logger_base.debug("e1.31 Sync: %s.", me131Sync ? "true" : "false");
    ShowHideSync();

    //start out with 50ms timer, once we load a file or create a new one, we'll reset
    //to whatever the timing that is selected
    Timer1.Start(50, wxTIMER_CONTINUOUS);

    // What makes 4 the right answer ... try 10 ... why ... usually it is one thread that runs slow and that model 
    // holds up others so in the time while we wait for the busy thread we can actually run a lot more models
    // what is the worst that could happen ... all models want to run hard so we lose some efficiency while we churn between
    // threads ... a minor loss of efficiency ... I think the one thread blocks the others is more common.
    // Dan is concerned on 32 bit windows 10 will chew up too much heap memory ... so splitting the difference we get 7
    jobPool.Start(wxThread::GetCPUCount() * 7);

    if (!xLightsApp::sequenceFiles.IsEmpty())
    {
        logger_base.debug("Opening sequence: %s.", (const char *)xLightsApp::sequenceFiles[0].c_str());
        OpenSequence(xLightsApp::sequenceFiles[0], nullptr);
    }

	SetAudioControls();

    logger_base.debug("xLightsFrame construction complete.");
}

xLightsFrame::~xLightsFrame()
{
    Timer_AutoSave.Stop();
    Timer1.Stop();
    selectedEffect = nullptr;

    wxConfigBase* config = wxConfigBase::Get();
    if (mResetToolbars)
    {
        config->DeleteEntry("ToolbarLocations");
    }
    else
    {
        config->Write("ToolbarLocations", TOOLBAR_SAVE_VERSION + MainAuiManager->SavePerspective());
    }
    config->Write("xLightsIconSize", mIconSize);
    config->Write("xLightsGridSpacing", mGridSpacing);
    config->Write("xLightsGridIconBackgrounds", mGridIconBackgrounds);
    config->Write("xLightsGridNodeValues", mGridNodeValues);
    config->Write("xLightsRenderOnSave", mRenderOnSave);
    config->Write("xLightsBackupOnSave", mBackupOnSave);
    config->Write("xLightsBackupOnLaunch", mBackupOnLaunch);
    config->Write("xLightse131Sync", me131Sync);
    config->Write("xLightsEffectAssistMode", mEffectAssistMode);
    config->Write("xLightsAltBackupDir", mAltBackupDir);

    config->Flush();

    wxFileName kbf;
    kbf.AssignDir(CurrentDir);
    kbf.SetFullName("xlights_keybindings.xml");
    mainSequencer->keyBindings.Save(kbf);

    //must call these or the app will crash on exit
    m_mgr->UnInit();
    MainAuiManager->UnInit();

    if( CurrentSeqXmlFile )
    {
        delete CurrentSeqXmlFile;
        CurrentSeqXmlFile = nullptr;
    }

    delete CheckBoxLightOutput;
    delete ButtonGracefulStop;


    //(*Destroy(xLightsFrame)
    //*)
}

void xLightsFrame::DoMenuAction(wxMenuEvent &evt) {
    static bool inMenuAction = false;
    if (inMenuAction) {
        return;
    }
    inMenuAction= true;
    wxWindow *w = FindFocus();
    evt.Skip();
    if (w != nullptr && w->GetEventHandler()) {
        w->GetEventHandler()->ProcessEventLocally(evt);
    }
    inMenuAction= false;
}


void xLightsFrame::OnQuit(wxCommandEvent& event)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    logger_base.info("Quit");
	wxCloseEvent evt;
    if (QuitMenuItem->IsEnabled())
    {
        OnClose(evt);
    }
}

void xLightsFrame::InitEffectsPanel(EffectsPanel* panel)
{
    panel->CurrentDir = &CurrentDir;
}


void xLightsFrame::OnAbout(wxCommandEvent& event)
{
    wxString hdg = wxString::Format(_("About xLights %s"),xlights_version_string);
    wxMessageBox(XLIGHTS_LICENSE, hdg);
}

// return a random number between 0 and 1 inclusive
double xLightsFrame::rand01()
{
    return static_cast<double>(rand())/ static_cast<double>(RAND_MAX);
}

void xLightsFrame::SetPlayMode(play_modes newmode)
{
    switch (newmode)
    {
    case play_off:
        SetStatusText(_("Playback: off"));
        break;
    default:
        break;
    }

    ButtonGracefulStop->Enable(newmode == play_sched || newmode == play_list);
    play_mode=newmode;
    starttime = wxDateTime::UNow();
#ifndef NDEBUG
    TextCtrlLog->AppendText(wxString::Format(_("SetPlayMode mode=%d state=%d\n"),play_mode,SeqPlayerState));
#endif
}

void xLightsFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    if (!gs_xoutCriticalSection.TryEnter()) return;
    if (CheckBoxRunSchedule->IsChecked()) CheckSchedule();
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    long curtime = ts.GetMilliseconds().ToLong();
    if (xout) xout->TimerStart(curtime);
    switch (Notebook1->GetSelection())
    {
    case NEWSEQUENCER:
        if( playAnimation ) {
            TimerRgbSeq(curtime * playSpeed);
        } else {
            TimerRgbSeq(curtime);
        }
        break;
    default:
        OnTimerPlaylist(curtime);
        break;
    }
    if (xout) xout->TimerEnd();
    gs_xoutCriticalSection.Leave();
}

void xLightsFrame::ResetTimer(SeqPlayerStates newstate, long OffsetMsec)
{
    SeqPlayerState = newstate;
#ifndef NDEBUG
    TextCtrlLog->AppendText(wxString::Format(_("ResetTimer mode=%d state=%d\n"),play_mode,SeqPlayerState));
#endif
    //if (newstate == NO_SEQ) SetPlayMode(play_off);
    if (xout) xout->ResetTimer();
    wxTimeSpan offset(0,0,0,OffsetMsec);
    starttime = wxDateTime::UNow() - offset;
}

void xLightsFrame::OnBitmapButtonTabInfoClick(wxCommandEvent& event)
{
    wxString caption,msg,selectmethod;
#ifdef __WXOSX__
    selectmethod=_("cmd-click");
#else
    selectmethod=_("ctrl-click or shift-click");
#endif
    switch (Notebook1->GetSelection())
    {
    case SETUPTAB:
        caption=_("Setup Tab");
        msg=_("Show Directory\n\nThe first thing you need to know about xLights is that it expects you to organize all of your sequence files and associated audio or video files into a single directory. For example, you can have a directory called '2012 Show'. Once you have your show directory created and populated with the relevant files, you are ready to proceed. Tell xLights where your new show directory is by clicking the 'Change' button on the Setup tab, navigate to your show directory, then click 'OK'.\n\nLighting Networks\n\nThe next thing you will need to do is define your lighting network(s). xLights ignores most of the information about your lighting network contained in your LOR or Vixen sequence. Thus this step is very important! Add a row in the lower half of the Setup tab for each network used in your display. xLights can drive a mixture of network types (for example, the first network can be DMX, and the second one LOR, and the third one Renard). When you are finished, do not forget to SAVE YOUR CHANGES by clicking the 'Save Setup' button.");
        break;
    case PREVIEWTAB:
        caption=_("Preview Tab");
        msg=_("Create display elements by clicking on the Models button. Only models that have 'My Display' checked will be included in the Display Elements list and shown in the preview area.\n\nSelect an item in the Display Elements list and it will turn from gray to yellow (you may not see the yellow if the selected element is hidden behind another one). Once selected, you can drag your cursor across the preview area to move the element. You can also use the Element Size slider to make it bigger or smaller. You can rotate elements that have Display As set to 'Single Line'. Don't forget to click the Save button to save your preview!\n\nClick the Open button to select an xLights sequence to be previewed. Note that any xLights sequence can be previewed, not just those created on the Nutcracker tab. Click Play to start preview playback. Use the Pause button to stop play, and then the Play button to resume. You can drag the slider that appears across the top of the preview area to move playback to any spot in your sequence. The Stop Now button in the upper left will also stop playback.");
        break;
    case NEWSEQUENCER:
        caption=_("Sequencer Tab");
        msg=_("The Sequencer tab can be used to create RGB sequences. First, create a model of your RGB display element(s) by clicking on the Models button. Then try the different effects and settings until you create something you like. You can save the settings as a preset by clicking the New Preset button. From then on, that preset will be available in the presets drop-down list. You can combine effects by creating a second effect in the Effect 2 area, then choosing a Layering Method. To create a series of effects that will be used in a sequence, click the open file icon to open an xLights (.xseq) sequence. Choose which display elements/models you will use in this sequence. Then click the insert rows icon and type in the start time in seconds when that effect should begin. Rows will automatically sort by start time. To add an effect to the sequence, click on the grid cell in the desired display model column and the desired start time row, then click the Update button. When you are done creating effects for the sequence, click the save icon and the xLights sequence will be updated with the effects you stored in the grid.");
        break;
    //case PAPAGAYOTAB:
    //    caption=_("Papagayo Tab");
    //    msg=_("The Papagayo tab can be used to create animated faces from a Papagayo file. There are four different types faces that you can create. \n1) Automatic, scaled faces for matrix and megatrees. \n2) You provide 10 images of the Phonemes, they will be selected for you. \n3) You provide moth , eyes and a backgroudn image. A mp4 movie will be created. \n4) You assign channels for each of the 10 Phonemes. This method matches standard coro singing faces ");
    //    break;
    default:
        // playlist
        caption=_("Playlist Tab");
        msg=_("Files in your show directory are listed on the left. Click the 'Audio', 'Video', or 'xLights' checkbox to see files of the desired type. Files in the playlist are listed on the right. To move files between the left and right lists, use the arrow buttons in the middle. You can rename or delete a list by using the Playlist menu. Selecting Playlist > Save Playlists from the menu will save all playlists as well as the schedule. You can play a single item on the playlist by selecting it and then clicking 'Play Item'. Use 'Play All' to play the entire playlist. You can reorder the playlist by dragging items up or down, or selecting items and using the up/down buttons.");
        break;
    }
    wxMessageBox(msg,caption);
}

void xLightsFrame::AllLightsOff()
{
    if (xout)
    {
        xout->alloff();
        wxTimerEvent ev;
        OnTimer1Trigger(ev);
    }
}

void xLightsFrame::ResetAllSequencerWindows()
{
	wxAuiPaneInfoArray &info = m_mgr->GetAllPanes();
	bool update = false;
	for (size_t x = 0; x < info.size(); x++)
	{
		if (info[x].IsFloating() && info[x].IsShown())
		{
			info[x].Dock();
			update = true;
		}
	}
	if (update)
	{
		m_mgr->Update();
	}
}

void xLightsFrame::ShowHideAllSequencerWindows(bool show)
{
    wxAuiPaneInfoArray &info = m_mgr->GetAllPanes();
    bool update = false;
    if (show)
    {
        for (size_t x = 0; x < info.size(); x++)
        {
            if (x < savedPaneShown.size() && info[x].IsFloating() && !info[x].IsShown()
                    && savedPaneShown[x])
            {
                info[x].Show();
                savedPaneShown[x] = true;
                update = true;
            }
        }
    }
    else
    {
        savedPaneShown.resize(info.size());
        for (size_t x = 0; x < info.size(); x++)
        {
            savedPaneShown[x] = info[x].IsShown();
            if (info[x].IsFloating() && info[x].IsShown())
            {
                info[x].Hide();
                update = true;
            }
        }
    }
    if (update)
    {
        m_mgr->Update();
    }

    // show/hide Layout Previews
    for (auto it = LayoutGroups.begin(); it != LayoutGroups.end(); it++) {
        LayoutGroup* grp = (LayoutGroup*)(*it);
        if (grp != nullptr) {
            if( grp->GetMenuItem()->IsChecked() ) {
                grp->SetPreviewActive(show);
            }
        }
    }

}


void xLightsFrame::OnNotebook1PageChanging(wxAuiNotebookEvent& event)
{
    if (event.GetOldSelection() == NEWSEQUENCER)
    {
        ShowHideAllSequencerWindows(false);
    }
}

void xLightsFrame::OnNotebook1PageChanged1(wxAuiNotebookEvent& event)
{
    heartbeat("tab change", true); //tell fido to stop watching -DJ
    int pagenum=event.GetSelection(); //Notebook1->GetSelection();
	if (pagenum == PREVIEWTAB)
    {
        // these commented out lines were already setup when rgbeffects file was loaded and it messes up multiple preview loading.
        //modelPreview->InitializePreview(mBackgroundImage,mBackgroundBrightness);
        //modelPreview->SetScaleBackgroundImage(mScaleBackgroundImage);
        UpdatePreview();
        SetStatusText(_(""));
        EffectSettingsTimer.Stop();
    }
    else if (pagenum == NEWSEQUENCER)
    {
        InitSequencer();
        ShowHideAllSequencerWindows(true);
        EffectSettingsTimer.Start(50);
    }
    else
    {
        SetStatusText(_(""));
        EffectSettingsTimer.Stop();
    }
}


void xLightsFrame::OnButtonLightsOffClick(wxCommandEvent& event)
{
    wxCriticalSectionLocker locker(gs_xoutCriticalSection);
    if (xout)
    {
        CheckBoxLightOutput->SetValue(false);
        AllLightsOff();
        EnableSleepModes();
        CheckBoxLightOutput->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_OUTPUT_LIGHTS")), wxART_TOOLBAR));
        delete xout;
        xout = 0;
        EnableNetworkChanges();
    }
}

bool xLightsFrame::EnableOutputs()
{
    wxCriticalSectionLocker locker(gs_xoutCriticalSection);
    long MaxChan;
    bool ok=true;
    if (CheckBoxLightOutput->IsChecked() && xout==0)
    {
        DisableSleepModes();
        xout = new xOutput(me131Sync, SpinCtrl_SyncUniverse->GetValue());

        for( wxXmlNode* e=NetworkXML.GetRoot()->GetChildren(); e!=nullptr && ok; e=e->GetNext() )
        {
            wxString tagname=e->GetName();
            if (tagname == "network")
            {
                wxString tempstr=e->GetAttribute("MaxChannels", "0");
                tempstr.ToLong(&MaxChan);
                wxString NetworkType=e->GetAttribute("NetworkType", "");
                wxString ComPort=e->GetAttribute("ComPort", "");
                wxString BaudRate=e->GetAttribute("BaudRate", "");
                int baud = (BaudRate == _("n/a")) ? 115200 : wxAtoi(BaudRate);
                bool enabled = e->GetAttribute("Enabled", "Yes") == "Yes";
				wxString Description = xLightsXmlFile::UnXmlSafe(e->GetAttribute("Description", ""));
                static wxString choices;

                int numU = wxAtoi(e->GetAttribute("NumUniverses", "1"));

#ifdef __WXMSW__ //TODO: enumerate comm ports on all platforms -DJ
                TCHAR valname[32];
                /*byte*/TCHAR portname[32];
                DWORD vallen = sizeof(valname);
                DWORD portlen = sizeof(portname);
                HKEY hkey = nullptr;
                DWORD err = 0;

//enum serial comm ports (more user friendly, especially if USB-to-serial ports change):
//logic based on http://www.cplusplus.com/forum/windows/73821/
                if (choices.empty()) //should this be cached?  it's not really that expensive
                {
                    if (!(err = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hkey)))
                        for (DWORD inx = 0; !(err = RegEnumValue(hkey, inx, (LPTSTR)valname, &vallen, nullptr, nullptr, (LPBYTE)portname, &portlen)) || (err == ERROR_MORE_DATA); ++inx)
                        {
                            if (err == ERROR_MORE_DATA) portname[sizeof(portname)/sizeof(portname[0]) - 1] = '\0'; //need to enlarge read buf if this happens; just truncate string for now
//                            debug(3, "found port[%d] %d:'%s' = %d:'%s', err 0x%x", inx, vallen, valname, portlen, portname, err);
                            choices += _(", ") + portname;
                            vallen = sizeof(valname);
                            portlen = sizeof(portname);
                        }
                    if (err && (err != /*ERROR_FILE_NOT_FOUND*/ ERROR_NO_MORE_ITEMS)) choices = wxString::Format(", error %d (can't get serial comm ports from registry)", err);
                    if (hkey) RegCloseKey(hkey);
//                    if (err) SetLastError(err); //tell caller about last real error
                    if (!choices.empty()) choices = "\n(available ports: "+ choices.substr(2) + ")";
                    else choices = "\n(no available ports)";
                }
#endif // __WXMSW__
                wxString msg = _("Error occurred while connecting to ") + NetworkType+ _(" network on ") + ComPort +
                               choices +
                               _("\n\nThings to check:\n1. Are all required cables plugged in?") +
                               _("\n2. Is there another program running that is accessing the port (like the LOR Control Panel)? If so, then you must close the other program and then restart xLights.") +
                               _("\n3. If this is a USB dongle, are the FTDI Virtual COM Port drivers loaded?\n\n");

                try
                {
                    xout->addnetwork(NetworkType,MaxChan,ComPort,baud, numU, enabled);
                    //TextCtrlLog->AppendText(_("Successfully initialized ") + NetworkType + _(" network on ") + ComPort + _("\n"));
                }
                catch (const char *str)
                {
                    wxString errmsg(str,wxConvUTF8);
                    if (wxMessageBox(msg + errmsg + _("\nProceed anyway?"), _("Communication Error"), wxYES_NO | wxNO_DEFAULT) != wxYES)
                        ok = false;
                }
            }
        }
        if (!ok)
        {
            // uncheck checkbox since we were not able to initialize the port(s) successfully
            delete xout;
            xout=0;
            CheckBoxLightOutput->SetValue(false);
            CheckBoxLightOutput->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_OUTPUT_LIGHTS")),wxART_TOOLBAR));
            //CheckBoxLightOutput->Enable(false);
        }
        else
        {
            CheckBoxLightOutput->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_OUTPUT_LIGHTS_ON")),wxART_TOOLBAR));
        }
    }
    else if (!CheckBoxLightOutput->IsChecked() && xout)
    {
        AllLightsOff();
        EnableSleepModes();
        CheckBoxLightOutput->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_OUTPUT_LIGHTS")),wxART_TOOLBAR));
        delete xout;
        xout=0;
    }
    EnableNetworkChanges();
    return ok;
}

void xLightsFrame::EnableNetworkChanges()
{
    bool flag=(xout==0 && !CurrentDir.IsEmpty());
    ButtonAddDongle->Enable(flag);
    ButtonAddE131->Enable(flag);
    ButtonArtNET->Enable(flag);
    ButtonAddNull->Enable(flag);
    ButtonNetworkChange->Enable(flag);
    ButtonNetworkDelete->Enable(flag);
    ButtonNetworkDeleteAll->Enable(flag);
    BitmapButtonMoveNetworkUp->Enable(flag);
    BitmapButtonMoveNetworkDown->Enable(flag);
    SpinCtrl_SyncUniverse->Enable(flag);
    ButtonSaveSetup->Enable(!CurrentDir.IsEmpty());
    ButtonSaveSchedule->Enable(!CurrentDir.IsEmpty());
    CheckBoxLightOutput->Enable(!CurrentDir.IsEmpty());
    CheckBoxRunSchedule->Enable(!CurrentDir.IsEmpty());
}

void xLightsFrame::OnCheckBoxLightOutputClick(wxCommandEvent& event)
{
    EnableOutputs();
    //CheckChannelList=true;  // cause status bar to be updated if in test mode
}


//factored out from below so it can be reused by play/pause button -DJ
void xLightsFrame::StopNow(void)
{
    int actTab = Notebook1->GetSelection();
	if (CurrentSeqXmlFile != nullptr && CurrentSeqXmlFile->GetMedia() != nullptr)
	{
		CurrentSeqXmlFile->GetMedia()->Stop();
	}
    if (play_mode == play_sched)
    {
        CheckBoxRunSchedule->SetValue(false);
        CheckRunSchedule();
    }
    heartbeat("playback end", true); //tell fido to stop watching -DJ
    if (basic.IsRunning()) basic.halt();
    SetPlayMode(play_off);
    ResetTimer(NO_SEQ);
    switch (actTab)
    {
    case NEWSEQUENCER:
        wxCommandEvent playEvent(EVT_STOP_SEQUENCE);
        wxPostEvent(this, playEvent);
        break;
    }
}

void xLightsFrame::OnButtonStopNowClick(wxCommandEvent& event)
{
    StopNow();
}

void xLightsFrame::OnButtonGracefulStopClick(wxCommandEvent& event)
{
    if (play_mode == play_sched)
    {
        EndTimeSec = 0;
    }
    else if (basic.IsRunning())
    {
        SecondsRemaining = 0;
        SetStatusText(_("Finishing playlist"));
        heartbeat("exit", true); //tell fido about graceful exit -DJ
    }
    else
    {
        wxMessageBox(_("Graceful Stop is only useful when a schedule or playlist is running"));
    }
}

//make these static so they can be accessed outside of xLightsFrame: -DJ
//NOTE: this assumes there will only be one xLightsMain object
wxString xLightsFrame::CurrentDir = "";
wxString xLightsFrame::PlaybackMarker = "";
wxString xLightsFrame::xlightsFilename = "";
xLightsXmlFile* xLightsFrame::CurrentSeqXmlFile = nullptr;

void xLightsFrame::OnButtonSaveScheduleClick(wxCommandEvent& event)
{
    SaveScheduleFile();
}

void xLightsFrame::OnMenuItemSavePlaylistsSelected(wxCommandEvent& event)
{
    SaveScheduleFile();
}


#include "TabSchedule.cpp"

void xLightsFrame::OnClose(wxCloseEvent& event)
{
    if (!QuitMenuItem->IsEnabled()) {
        return;
    }

    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
	logger_base.info("xLights Closing");

	StopNow();

	if (!CloseSequence())
    {
		logger_base.info("Closing aborted.");
		event.Veto();
        return;
    }
    selectedEffect = nullptr;

    CheckUnsavedChanges();

    ShowHideAllSequencerWindows(false);

    // destroy preview windows
    for (auto it = PreviewWindows.begin(); it != PreviewWindows.end(); ++it) {
        ModelPreview* preview = *it;
        delete preview;
    }

    heartbeat("exit", true); //tell fido about graceful exit -DJ
    //ScrolledWindow1->Disconnect(wxEVT_SIZE,(wxObjectEventFunction)&xLightsFrame::OnScrolledWindow1Resize,0,this);

    Destroy();
	logger_base.info("xLights Closed.");
}

void xLightsFrame::DoBackup(bool prompt, bool startup)
{
    wxString folderName;
    time_t cur;
    time(&cur);
    wxFileName newDirH;
    wxDateTime curTime(cur);

    //  first make sure there is a Backup sub directory
    wxString newDirBackup = CurrentDir + wxFileName::GetPathSeparator() + "Backup";
    if (!wxDirExists(newDirBackup) && !newDirH.Mkdir(newDirBackup))
    {
        wxMessageBox("Unable to create directory Backup!", "Error", wxICON_ERROR | wxOK);
        return;
    }

    wxString newDir = CurrentDir + wxFileName::GetPathSeparator() + wxString::Format(
        "Backup%c%s-%s", wxFileName::GetPathSeparator(),
        curTime.FormatISODate(), curTime.Format("%H%M%S"));
    if (startup)
    {
        newDir += "_OnStart";
    }

    if (prompt)
    {
        if (wxNO == wxMessageBox("All xml files under 20MB in your xlights directory will be backed up to \"" +
            newDir + "\". Proceed?", "Backup", wxICON_QUESTION | wxYES_NO))
        {
            return;
        }
    }

    if (!newDirH.Mkdir(newDir))
    {
        wxMessageBox("Unable to create directory!", "Error", wxICON_ERROR | wxOK);
        return;
    }

    BackupDirectory(newDir);
}

void xLightsFrame::OnMenuItemBackupSelected(wxCommandEvent& event)
{
    SaveWorking();

    DoBackup(true);
}

void xLightsFrame::CopyFiles(const wxString& wildcard, wxDir& srcDir, wxString& targetDirName)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    wxString fname;
    wxString srcDirName = CurrentDir + wxFileName::GetPathSeparator();
    wxFileName srcFile;
    srcFile.SetPath(CurrentDir);

    bool cont = srcDir.GetFirst(&fname, wildcard, wxDIR_FILES);
    while (cont)
    {
        logger_base.debug("Backing up file %s.", (const char *)fname.c_str());

        srcFile.SetFullName(fname);

        wxULongLong fsize = srcFile.GetSize();
        if (fsize > 20 * 1024 * 1024) // skip any xml files > 20 mbytes, they are something other than xml files
        {
            cont = srcDir.GetNext(&fname);
            continue;
        }
        SetStatusText("Copying File \"" + srcFile.GetFullPath());
        bool success = wxCopyFile(srcDirName + fname,
            targetDirName + wxFileName::GetPathSeparator() + fname);
        if (!success)
        {
            wxMessageBox("Unable to copy file \"" + CurrentDir + wxFileName::GetPathSeparator() + fname + "\"",
                "Error", wxICON_ERROR | wxOK);
        }
        cont = srcDir.GetNext(&fname);
    }
}

void xLightsFrame::BackupDirectory(wxString targetDirName)
{
    wxDir srcDir(CurrentDir);

    if(!srcDir.IsOpened())
    {
        return;
    }

    CopyFiles("*.xml", srcDir, targetDirName);
    CopyFiles("*.xbkp", srcDir, targetDirName);

    SetStatusText("All xml files backed up.");
}


//#define isRandom(ctl)  (buttonState[std::string(ctl->GetName())] == Random)
bool xLightsFrame::isRandom_(wxControl* ctl, const char*debug)
{
//    if (!ctl->GetName().length()) djdebug("NO NAME FOR %s", debug);
    bool retval = (buttonState[std::string(ctl->GetName())] != Locked); //== Random);
//    djdebug("isRandom(%s) = %d", (const char*)ctl->GetName().c_str(), retval);
    return retval;
}

void xLightsFrame::OnEffectsPanel1Paint(wxPaintEvent& event)
{
}

void xLightsFrame::OnGrid1SetFocus(wxFocusEvent& event)
{
    Grid1HasFocus = true;
}

void xLightsFrame::OnGrid1KillFocus(wxFocusEvent& event)
{
    Grid1HasFocus = false;
}


void xLightsFrame::OntxtCtrlSparkleFreqText(wxCommandEvent& event)
{
}


static void AddNonDupAttr(wxXmlNode* node, const wxString& name, const wxString& value)
{
    wxString junk;
    if (node->GetAttribute(name, &junk)) node->DeleteAttribute(name); //kludge: avoid dups
    if (!value.empty()) node->AddAttribute(name, value);
}

//sigh; a function like this should have been built into wxWidgets
wxXmlNode* xLightsFrame::FindNode(wxXmlNode* parent, const wxString& tag, const wxString& attr, const wxString& value, bool create /*= false*/)
{
#if 0
    static struct
    {
        std::unordered_map<const char*, wxXmlNode*> nodes;
        std::string parent, child;
    } cached_names;

    if (parent->GetName() != cached_names.parent) //reload cache
    {
        cached_names.nodes.clear();
        for (wxXmlNode* node = parent->GetChildren(); node != nullptr; node = node->GetNext())
            cached_names.nodes[node->GetName()] = node;
        cached_names.parent = parent;
    }
    if (cached_names.nodes.find(tag) == cached_names.nodes.end()) //not found
    {
        if (!create) return 0;
        parent->AddChild(cached_names.nodes[tag] = new wxXmlNode(wxXML_ELEMENT_NODE, tag));
    }
    return cached_names.nodes[tag];
#endif // 0
    for (wxXmlNode* node = parent->GetChildren(); node != nullptr; node = node->GetNext())
    {
        if (!tag.empty() && (node->GetName() != tag)) continue;
        if (!value.empty() && (node->GetAttribute(attr) != value)) continue;
        return node;
    }
    if (!create) return 0; //CAUTION: this will give null ptr exc if caller does not check
    wxXmlNode* retnode = new wxXmlNode(wxXML_ELEMENT_NODE, tag); //NOTE: assumes !tag.empty()
    parent->AddChild(retnode);
    if (!value.empty()) AddNonDupAttr(retnode, attr, value);
    return retnode;
}
void xLightsFrame::SetPreviewSize(int width,int height)
{
    SetXmlSetting("previewWidth",wxString::Format("%d",width));
    SetXmlSetting("previewHeight",wxString::Format("%d",height));
    modelPreview->SetCanvasSize(width,height);
    modelPreview->Refresh();
    sPreview2->SetVirtualCanvasSize(width, height);
    sPreview2->Refresh();
}
void xLightsFrame::SetXmlSetting(const wxString& settingName,const wxString& value)
{
    wxXmlNode* e;
    // Delete existing setting node
    for(e=SettingsNode->GetChildren(); e!=nullptr; e=e->GetNext())
    {
        if(e->GetName() == settingName)
        {
            SettingsNode->RemoveChild(e);
        }
    }
    // Add new one
    wxXmlNode* setting = new wxXmlNode( wxXML_ELEMENT_NODE, settingName );
    setting->AddAttribute("value",value);
    SettingsNode->AddChild(setting);
}
wxString xLightsFrame::GetXmlSetting(const wxString& settingName,const wxString& defaultValue)
{
    wxXmlNode* e;
    // Delete existing setting node
    for(e=SettingsNode->GetChildren(); e!=nullptr; e=e->GetNext())
    {
        if(e->GetName() == settingName)
        {
            return e->GetAttribute("value",defaultValue);
        }
    }
    return defaultValue;
}

void xLightsFrame::OnButtonClickSaveAs(wxCommandEvent& event)
{
    SaveAsSequence();
}

wxString xLightsFrame::GetSeqXmlFileName()
{
    if (CurrentSeqXmlFile == nullptr)
    {
        return "";
    }
    return CurrentSeqXmlFile->GetFullPath();
}

void xLightsFrame::OnMenu_Settings_SequenceSelected(wxCommandEvent& event)
{
    if( xLightsFrame::CurrentSeqXmlFile == nullptr ) return;
    // populate dialog
    SeqSettingsDialog dialog(this, xLightsFrame::CurrentSeqXmlFile, mediaDirectory, wxEmptyString);
    dialog.Fit();
    int ret_code = dialog.ShowModal();

    if (ret_code != wxID_OK) return;  // user pressed cancel

    if (ret_code == NEEDS_RENDER)
    {
        RenderAll();
    }

	if(CurrentSeqXmlFile->GetMedia() != nullptr)
	{
		if (CurrentSeqXmlFile->GetMedia()->GetFrameInterval() < 0)
		{
			CurrentSeqXmlFile->GetMedia()->SetFrameInterval(CurrentSeqXmlFile->GetSequenceTimingAsInt());
		}
	}
	SetAudioControls();
}


void xLightsFrame::OnAuiToolBarItemPlayButtonClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        wxCommandEvent playEvent(EVT_PLAY_SEQUENCE);
        wxPostEvent(this, playEvent);
    }
}

void xLightsFrame::EnableToolbarButton(wxAuiToolBar* toolbar,int id, bool enable)
{
    wxAuiToolBarItem* button = toolbar->FindTool(id);
	if (button != nullptr)
	{
		int state = enable ? wxAUI_BUTTON_STATE_NORMAL : wxAUI_BUTTON_STATE_DISABLED;
		button->SetState(state);
		toolbar->Refresh();
	}
}

void xLightsFrame::OnAuiToolBarItemPauseButtonClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        wxCommandEvent playEvent(EVT_PAUSE_SEQUENCE);
        wxPostEvent(this, playEvent);
    }
}

void xLightsFrame::OnAuiToolBarItemStopClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        //playStartTime = playEndTime = 0;
        wxCommandEvent playEvent(EVT_STOP_SEQUENCE);
        wxPostEvent(this, playEvent);
    }
}

void xLightsFrame::OnAuiToolBarFirstFrameClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        wxCommandEvent playEvent(EVT_SEQUENCE_FIRST_FRAME);
        wxPostEvent(this, playEvent);
    }
}

void xLightsFrame::OnAuiToolBarLastFrameClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        wxCommandEvent playEvent(EVT_SEQUENCE_LAST_FRAME);
        wxPostEvent(this, playEvent);
    }
}

void xLightsFrame::OnAuiToolBarItemReplaySectionClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        wxCommandEvent playEvent(EVT_SEQUENCE_REPLAY_SECTION);
        wxPostEvent(this, playEvent);
    }
}

void xLightsFrame::OnAuiToolBarItemZoominClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        mainSequencer->PanelTimeLine->ZoomIn();
    }
}

void xLightsFrame::OnAuiToolBarItem_ZoomOutClick(wxCommandEvent& event)
{
    if (Notebook1->GetSelection() == NEWSEQUENCER)
    {
        mainSequencer->PanelTimeLine->ZoomOut();
    }
}


void xLightsFrame::OnMenuItem_File_Open_SequenceSelected(wxCommandEvent& event)
{
    OpenSequence("", nullptr);
}

void xLightsFrame::OnMenuItem_File_Save_SequenceSelected(wxCommandEvent& event)
{
    SaveSequence();
}

void xLightsFrame::OnMenuItem_File_SaveAs_SequenceSelected(wxCommandEvent& event)
{
    SaveAsSequence();
}

void xLightsFrame::OnMenuItem_File_Close_SequenceSelected(wxCommandEvent& event)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    logger_base.info("Closing sequence.");
	CloseSequence();
	logger_base.info("Sequence closed.");

    // force refreshes since grid has been cleared
    mainSequencer->PanelTimeLine->RaiseChangeTimeline();
    wxCommandEvent eventRowHeaderChanged(EVT_ROW_HEADINGS_CHANGED);
    wxPostEvent(this, eventRowHeaderChanged);
}

void xLightsFrame::OnResize(wxSizeEvent& event)
{
}

void xLightsFrame::OnAuiToolBarItemRenderAllClick(wxCommandEvent& event)
{
    RenderAll();
}

bool AUIToolbarButtonWrapper::IsChecked()
{
    return toolbar->GetToolToggled(id);
}
void AUIToolbarButtonWrapper::SetValue(bool b)
{
    toolbar->ToggleTool(id, b);
}
void AUIToolbarButtonWrapper::SetBitmap(const wxBitmap &bmp)
{
    toolbar->SetToolBitmap(id,bmp);
    toolbar->Refresh();
}

void AUIToolbarButtonWrapper::Enable(bool b)
{
    toolbar->EnableTool(id, b);
}

void xLightsFrame::SetIconSize(wxCommandEvent& event)
{
    int size = 48;
    if (event.GetId() == ID_MENUITEM_GRID_ICON_XSMALL)
    {
        size = 10;
    }
    else if (event.GetId() == ID_MENUITEM_GRID_ICON_SMALL)
    {
        size = 16;
    }
    else if (event.GetId() == ID_MENUITEM_GRID_ICON_MEDIUM)
    {
        size = 24;
    }
    else if (event.GetId() == ID_MENUITEM_GRID_ICON_LARGE)
    {
        size = 32;
    }
    mGridSpacing = size;

    DEFAULT_ROW_HEADING_HEIGHT = size + 6;
    mainSequencer->PanelRowHeadings->Refresh();
    mainSequencer->PanelEffectGrid->Refresh();
    GridSpacingMenu->Check(event.GetId(), true);
}

void xLightsFrame::ResetToolbarLocations(wxCommandEvent& event)
{
    wxMessageBox("Toolbar locations will reset to defaults upon restart.");
    mResetToolbars = true;
}

void xLightsFrame::SetToolIconSize(wxCommandEvent& event)
{
    int size = 48;
    if (event.GetId() == ID_MENUITEM_ICON_SMALL)
    {
        size = 16;
    }
    else if (event.GetId() == ID_MENUITEM_ICON_MEDIUM)
    {
        size = 24;
    }
    else if (event.GetId() == ID_MENUITEM_ICON_LARGE)
    {
        size = 32;
    }

    mIconSize = size;

    for (size_t x = 0; x < EffectsToolBar->GetToolCount(); x++)
    {
        EffectsToolBar->FindToolByIndex(x)->GetWindow()->SetSizeHints(size, size, size, size);
        EffectsToolBar->FindToolByIndex(x)->SetMinSize(EffectsToolBar->FindToolByIndex(x)->GetWindow()->GetMinSize());
    }
    EffectsToolBar->Realize();
    wxSize sz = EffectsToolBar->GetSize();
    wxAuiPaneInfo &info = MainAuiManager->GetPane("EffectsToolBar");
    info.BestSize(sz);
    MainAuiManager->Update();

    const wxWindowList& lst =effectPalettePanel->GetChildren();
    for (size_t x = 0; x < lst.size(); x++)
    {
        lst[x]->SetSizeHints(size, size, size, size);
    }
    effectPalettePanel->Layout();
    ToolIconSizeMenu->Check(event.GetId(), true);

    effectsPnl->BitmapButtonSelectedEffect->SetSizeHints(size, size, size, size);
    effectsPnl->Layout();
}

void xLightsFrame::OnMenuItemRenderEraseModeSelected(wxCommandEvent& event)
{
    MenuItemRenderEraseMode->Check(true);
    MenuItemRenderCanvasMode->Check(false);
    CurrentSeqXmlFile->SetRenderMode(xLightsXmlFile::ERASE_MODE);
}

void xLightsFrame::OnMenuItemRenderCanvasModeSelected(wxCommandEvent& event)
{
    MenuItemRenderEraseMode->Check(false);
    MenuItemRenderCanvasMode->Check(true);
    CurrentSeqXmlFile->SetRenderMode(xLightsXmlFile::CANVAS_MODE);
}

void xLightsFrame::UpdateRenderMode()
{
    if( CurrentSeqXmlFile->GetRenderMode() == xLightsXmlFile::CANVAS_MODE )
    {
        MenuItemRenderEraseMode->Check(false);
        MenuItemRenderCanvasMode->Check(true);
    }
    else
    {
        MenuItemRenderEraseMode->Check(true);
        MenuItemRenderCanvasMode->Check(false);
    }
}

void xLightsFrame::SetFrequency(int frequency)
{
    mSequenceElements.SetFrequency(frequency);
    mainSequencer->PanelTimeLine->SetTimeFrequency(frequency);
    mainSequencer->PanelWaveForm->SetTimeFrequency(frequency);
}

void xLightsFrame::OnSetGridIconBackground(wxCommandEvent& event)
{
    if (event.GetId() == ID_MENUITEM_GRID_ICON_BACKGROUND_ON)
    {
        mGridIconBackgrounds = true;
    }
    else if (event.GetId() == ID_MENUITEM_GRID_ICON_BACKGROUND_OFF)
    {
        mGridIconBackgrounds = false;
    }
    MenuItemGridIconBackgroundOn->Check(mGridIconBackgrounds);
    MenuItemGridIconBackgroundOff->Check(!mGridIconBackgrounds);
    mainSequencer->PanelEffectGrid->SetEffectIconBackground(mGridIconBackgrounds);
    mainSequencer->PanelEffectGrid->Refresh();
}

void xLightsFrame::OnSetGridNodeValues(wxCommandEvent& event)
{
    if (event.GetId() == ID_MENUITEM_GRID_NODE_VALUES_ON)
    {
        mGridNodeValues = true;
    }
    else if (event.GetId() == ID_MENUITEM_GRID_NODE_VALUES_OFF)
    {
        mGridNodeValues = false;
    }
    MenuItemGridNodeValuesOn->Check(mGridNodeValues);
    MenuItemGridNodeValuesOff->Check(!mGridNodeValues);
    mainSequencer->PanelEffectGrid->SetEffectNodeValues(mGridNodeValues);
    mainSequencer->PanelEffectGrid->Refresh();
}



void xLightsFrame::SetPlaySpeed(wxCommandEvent& event)
{
    playSpeed = 1.0;
    playAnimation = false;
    if (event.GetId() == ID_PLAY_FULL)
    {
        playSpeed = 1.0;
    }
    else if (event.GetId() == ID_PLAY_3_4)
    {
        playSpeed = 0.75;
    }
    else if (event.GetId() == ID_PLAY_1_2)
    {
        playSpeed = 0.5;
    }
    else if (event.GetId() == ID_PLAY_1_4)
    {
        playSpeed = 0.25;
    }
	AudioManager::SetGlobalPlaybackRate(playSpeed);
	if (CurrentSeqXmlFile != nullptr)
	{
	    if( CurrentSeqXmlFile->GetMedia() != nullptr )
        {
            CurrentSeqXmlFile->GetMedia()->SetPlaybackRate(playSpeed);
        }
        else
        {
            playAnimation = true;
        }
	}
}

void xLightsFrame::OnBitmapButton_Link_DirsClick(wxCommandEvent& event)
{
    wxConfigBase* config = wxConfigBase::Get();
    long LinkFlag=0;
    config->Read(_("LinkFlag"), &LinkFlag);
    if( LinkFlag )
    {
        LinkFlag = 0;
        BitmapButton_Link_Dirs->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_UNLINK")),wxART_OTHER));
        Button_Change_Media_Dir->Enable(true);
        BitmapButton_Link_Dirs->SetToolTip("Link Directories");
    }
    else
    {
        LinkFlag = 1;
        BitmapButton_Link_Dirs->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_LINK")),wxART_OTHER));
        Button_Change_Media_Dir->Enable(false);
        mediaDirectory = CurrentDir;
        config->Write(_("MediaDir"), mediaDirectory);
        MediaDirectoryLabel->SetLabel(mediaDirectory);
        MediaDirectoryLabel->GetParent()->Layout();
        static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
        logger_base.debug("Media directory set to : %s.", (const char *)mediaDirectory.c_str());
        BitmapButton_Link_Dirs->SetToolTip("Unlink Directories");
    }
    config->Write(_("LinkFlag"), LinkFlag);
}

void xLightsFrame::OnMenuItemRenderOnSave(wxCommandEvent& event)
{
    mRenderOnSave = event.IsChecked();
}

void xLightsFrame::OnMenuItemEffectAssistAlwaysOnSelected(wxCommandEvent& event)
{
    MenuItemEffectAssistAlwaysOn->Check(true);
    MenuItemEffectAssistAlwaysOff->Check(false);
    MenuItemEffectAssistToggleMode->Check(false);
    mEffectAssistMode = EFFECT_ASSIST_ALWAYS_ON;
    SetEffectAssistWindowState(true);
}

void xLightsFrame::OnMenuItemEffectAssistAlwaysOffSelected(wxCommandEvent& event)
{
    MenuItemEffectAssistAlwaysOn->Check(false);
    MenuItemEffectAssistAlwaysOff->Check(true);
    MenuItemEffectAssistToggleMode->Check(false);
    mEffectAssistMode = EFFECT_ASSIST_ALWAYS_OFF;
    SetEffectAssistWindowState(false);
}

void xLightsFrame::OnMenuItemEffectAssistToggleModeSelected(wxCommandEvent& event)
{
    MenuItemEffectAssistAlwaysOn->Check(false);
    MenuItemEffectAssistAlwaysOff->Check(false);
    MenuItemEffectAssistToggleMode->Check(true);
    mEffectAssistMode = EFFECT_ASSIST_TOGGLE_MODE;
}

void xLightsFrame::SetEffectAssistWindowState(bool show)
{
    bool visible = m_mgr->GetPane("EffectAssist").IsShown();
    if (visible && !show)
    {
        m_mgr->GetPane("EffectAssist").Hide();
        m_mgr->Update();
    }
    else if(!visible && show)
    {
        m_mgr->GetPane("EffectAssist").Show();
        m_mgr->Update();
    }
}

void xLightsFrame::UpdateEffectAssistWindow(Effect* effect, RenderableEffect* ren_effect)
{
    if( effect == nullptr || ren_effect == nullptr )
    {
        sEffectAssist->SetPanel(nullptr);
        return;
    }

    bool effect_is_supported = ren_effect->HasAssistPanel();

    if( mEffectAssistMode == EFFECT_ASSIST_TOGGLE_MODE )
    {
        if( effect_is_supported )
        {
            SetEffectAssistWindowState(true);
        }
        else
        {
            SetEffectAssistWindowState(false);
        }
    }

    AssistPanel *panel;
    if (effect_is_supported) {
        panel = ren_effect->GetAssistPanel(sEffectAssist, this);
    } else {
        panel = sEffectAssist->GetDefaultAssistPanel();
    }
    panel->SetEffectInfo(effect, this);
    sEffectAssist->SetPanel(panel);
}

void xLightsFrame::CheckUnsavedChanges()
{
    if ( UnsavedPlaylistChanges && wxYES == wxMessageBox("Save Scheduler/Playlist changes?",
            "Scheduler Changes Confirmation", wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT))
    {
        SaveScheduleFile();
    }

    if (UnsavedRgbEffectsChanges)
    {
        // This is not necessary but it shows the user that the save button is red which I am hoping makes it clearer
        // to the user what this prompt is for
        Notebook1->SetSelection(PREVIEWTAB);

        if (wxYES == wxMessageBox("Save Models, Views, Perspectives, and Preset changes?",
            "RGB Effects File Changes Confirmation", wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT))
        {
            SaveEffectsFile();
        }
    }

    if (UnsavedNetworkChanges)
    {
        // This is not necessary but it shows the user that the save button is red which I am hoping makes it clearer
        // to the user what this prompt is for
        Notebook1->SetSelection(SETUPTAB);

        if (wxYES == wxMessageBox("Save Network Setup changes?",
            "Networks Changes Confirmation", wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT))
        {
            SaveNetworksFile();
        }
    }
}

void xLightsFrame::MarkEffectsFileDirty()
{
    layoutPanel->SetDirtyHiLight(true);
    UnsavedRgbEffectsChanges=true;
}

unsigned int xLightsFrame::GetMaxNumChannels() {
    return std::max(NetInfo.GetTotChannels(), AllModels.GetLastChannel() + 1);
}


void xLightsFrame::UpdateSequenceLength()
{
    if( CurrentSeqXmlFile->GetSequenceLoaded() )
    {
        wxString mss = CurrentSeqXmlFile->GetSequenceTiming();
        int ms = wxAtoi(mss);

        SeqData.init(GetMaxNumChannels(), CurrentSeqXmlFile->GetSequenceDurationMS() / ms, ms);
        mSequenceElements.IncrementChangeCount(nullptr);

        mainSequencer->PanelTimeLine->SetTimeLength(CurrentSeqXmlFile->GetSequenceDurationMS());
        mainSequencer->PanelTimeLine->Initialize();
        int maxZoom = mainSequencer->PanelTimeLine->GetMaxZoomLevel();
        mainSequencer->PanelTimeLine->SetZoomLevel(maxZoom);
        mainSequencer->PanelWaveForm->SetZoomLevel(maxZoom);
        mainSequencer->PanelTimeLine->RaiseChangeTimeline();
        mainSequencer->PanelWaveForm->UpdatePlayMarker();
    }
}

void xLightsFrame::OnActionTestMenuItemSelected(wxCommandEvent& event)
{
	// save the media playing state and stop it if it is playing
	MEDIAPLAYINGSTATE mps = MEDIAPLAYINGSTATE::STOPPED;
	if (CurrentSeqXmlFile != nullptr && CurrentSeqXmlFile->GetMedia() != nullptr)
	{
		mps = CurrentSeqXmlFile->GetMedia()->GetPlayingState();
		if (mps == MEDIAPLAYINGSTATE::PLAYING)
		{
			CurrentSeqXmlFile->GetMedia()->Pause();
			SetAudioControls();
		}
	}

	Timer1.Stop();

	// save the output state and turn it off
	bool output = CheckBoxLightOutput->IsChecked();
	if (output)
	{
		AllLightsOff();
	}

	// creating the dialog can take some time so display an hourglass
	SetCursor(wxCURSOR_WAIT);

	// display the test dialog
    TestDialog dialog(this, &NetworkXML, networkFile, &AllModels);
    dialog.CenterOnParent();
    dialog.ShowModal();

	SetCursor(wxCURSOR_DEFAULT);

	// resume output if it was set
	if (output)
	{
		EnableOutputs();
	}

	Timer1.Start();

	// resume playing the media if it was playing
	if (mps == MEDIAPLAYINGSTATE::PLAYING)
	{
		CurrentSeqXmlFile->GetMedia()->Play();
		SetAudioControls();
	}
}

void xLightsFrame::OnAuiToolBarItemPasteByTimeClick(wxCommandEvent& event)
{
    ButtonPasteByTime->SetValue(true);
    ButtonPasteByCell->SetValue(false);
    mainSequencer->SetPasteByCell(false);
}

void xLightsFrame::OnAuiToolBarItemPasteByCellClick(wxCommandEvent& event)
{
    ButtonPasteByTime->SetValue(false);
    ButtonPasteByCell->SetValue(true);
    mainSequencer->SetPasteByCell(true);
}

void xLightsFrame::OnMenuItemConvertSelected(wxCommandEvent& event)
{
    UpdateChannelNames();
    ConvertDialog dialog(this, SeqData, NetInfo, mediaFilename, ChannelNames, ChannelColors, ChNames); // , &NetInfo, &ChNames, mMediaLengthMS);
    dialog.CenterOnParent();
    dialog.ShowModal();
}

void xLightsFrame::OnMenu_GenerateCustomModelSelected(wxCommandEvent& event)
{
    // save the media playing state and stop it if it is playing
    MEDIAPLAYINGSTATE mps = MEDIAPLAYINGSTATE::STOPPED;
    if (CurrentSeqXmlFile != nullptr && CurrentSeqXmlFile->GetMedia() != nullptr)
    {
        mps = CurrentSeqXmlFile->GetMedia()->GetPlayingState();
        if (mps == MEDIAPLAYINGSTATE::PLAYING)
        {
            CurrentSeqXmlFile->GetMedia()->Pause();
            SetAudioControls();
        }
    }

    Timer1.Stop();

    // save the output state and turn it off
    bool output = CheckBoxLightOutput->IsChecked();
    if (output)
    {
        AllLightsOff();
    }

    // creating the dialog can take some time so display an hourglass
    SetCursor(wxCURSOR_WAIT);

    GenerateCustomModelDialog dialog(this, &NetworkXML);
    dialog.CenterOnParent();
    dialog.ShowModal();

    SetCursor(wxCURSOR_DEFAULT);

    // resume output if it was set
    if (output)
    {
        EnableOutputs();
    }

    Timer1.Start();

    // resume playing the media if it was playing
    if (mps == MEDIAPLAYINGSTATE::PLAYING)
    {
        CurrentSeqXmlFile->GetMedia()->Play();
        SetAudioControls();
    }
}

void xLightsFrame::OnPaneClose(wxAuiManagerEvent& event)
{
    SetFocus();
}

void xLightsFrame::SendReport(const wxString &loc, wxDebugReportCompress &report) {
    wxHTTP http;
    http.Connect("dankulp.com");

    const char *bound = "--------------------------b29a7c2fe47b9481";
    int i = wxGetUTCTimeMillis().GetLo();
    i &= 0xFFFFFFF;
    wxString fn = wxString::Format("xlights-%s_%d_%s.zip",  wxPlatformInfo::Get().GetOperatingSystemFamilyName().c_str(), i, xlights_version_string);
    const char *ct = "Content-Type: application/octet-stream\n";
    std::string cd = "Content-Disposition: form-data; name=\"userfile\"; filename=\"" + fn.ToStdString() + "\"\n\n";

    wxMemoryBuffer memBuff;
    memBuff.AppendData(bound, strlen(bound));
    memBuff.AppendData("\n", 1);
    memBuff.AppendData(ct, strlen(ct));
    memBuff.AppendData(cd.c_str(), strlen(cd.c_str()));


    wxFile f_in(report.GetCompressedFileName());
    wxFileOffset fLen=f_in.Length();
    void* tmp=memBuff.GetAppendBuf(fLen);
    size_t iRead=f_in.Read(tmp, fLen);
    memBuff.UngetAppendBuf(iRead);
    f_in.Close();

    memBuff.AppendData("\n", 1);
    memBuff.AppendData(bound, strlen(bound));
    memBuff.AppendData("--\n", 3);

    http.SetMethod("POST");
    http.SetPostBuffer("multipart/form-data; boundary=------------------------b29a7c2fe47b9481", memBuff);
    wxInputStream * is = http.GetInputStream("/" + loc + "/index.php");
    char buf[1024];
    is->Read(buf, 1024);
    //printf("%s\n", buf);
    delete is;
    http.Close();
}

void xLightsFrame::MaybePackageAndSendDebugFiles() {
    wxString message = "You forced the OpenGL setting to a non-default value.  Is it OK to send the debug logs to the developers for analysis?";
    wxMessageDialog dlg(this, message, "Send Debug Files",wxYES_NO|wxCENTRE);
    if (dlg.ShowModal() == wxID_YES) {
        wxTextEntryDialog ted(this, "Can you briefly describe what wasn't working?\n"
                              "Also include who you are (email, forum username, etc..)", "Additional Information", "",
                              wxTE_MULTILINE|wxOK|wxCENTER);
        ted.SetSize(400, 400);
        ted.ShowModal();

        wxDebugReportCompress report;
        report.SetCompressedFileBaseName("xlights_debug");
        report.SetCompressedFileDirectory(wxFileName::GetTempDir());
        report.AddText("description", ted.GetValue(), "description");
        AddDebugFilesToReport(report);
        report.Process();
        SendReport("oglUpload", report);
        wxRemoveFile(report.GetCompressedFileName());
    }
}
void xLightsFrame::OnMenuItemPackageDebugFiles(wxCommandEvent& event)
{
    wxLogNull logNo; //kludge: avoid "error 0" message from wxWidgets after new file is written
    wxFileDialog fd(this, "Zip file to create.", CurrentDir, "xLightsProblem.zip", "zip file(*.zip)|*.zip", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (fd.ShowModal() == wxID_CANCEL) return;

    // check the curent sequence to ensure this analysis is in the log
    CheckSequence(false);

    wxDebugReportCompress report;
    report.SetCompressedFileBaseName(wxFileName(fd.GetFilename()).GetName());
    report.SetCompressedFileDirectory(fd.GetDirectory());
    AddDebugFilesToReport(report);

    // export the models to an easy to read file
    wxString filename = wxFileName::CreateTempFileName("Models") + ".csv";
    ExportModels(filename);
    wxFileName fn(filename);
    report.AddFile(fn.GetFullPath(), "All Models");

    // export the effects to an easy to read file
    if (CurrentSeqXmlFile != nullptr)
    {
        wxString filenamee = wxFileName::CreateTempFileName("Effects") + ".csv";
        ExportEffects(filenamee);
        wxFileName fne(filenamee);
        report.AddFile(fne.GetFullPath(), "All Effects");
    }

    report.Process();

    wxRemoveFile(filename);
}

static void AddLogFile(const wxString &CurrentDir, const wxString &fileName, wxDebugReport &report) {
    wxString dir;
#ifdef __WXMSW__
    wxGetEnv("APPDATA", &dir);
    wxString filename = dir + "/" + fileName;
#endif
#ifdef __WXOSX_MAC__
    wxFileName home;
    home.AssignHomeDir();
    dir = home.GetFullPath();
    wxString filename = dir + "/Library/Logs/" + fileName;
#endif
#ifdef __LINUX__
    wxString filename = "/tmp/" + fileName;
#endif
    if (wxFile::Exists(filename))
    {
        report.AddFile(filename, fileName);
    }
    else if (wxFile::Exists(wxFileName(CurrentDir, fileName).GetFullPath()))
    {
        report.AddFile(wxFileName(CurrentDir, fileName).GetFullPath(), fileName);
    }
    else if (wxFile::Exists(wxFileName(wxGetCwd(), fileName).GetFullPath()))
    {
        report.AddFile(wxFileName(wxGetCwd(), fileName).GetFullPath(), fileName);
    }
}

void xLightsFrame::AddDebugFilesToReport(wxDebugReport &report) {


    wxFileName fn(CurrentDir, "xlights_networks.xml");
    if (fn.Exists()) {
        report.AddFile(fn.GetFullPath(), "xlights_networks.xml");
    }
    if (wxFileName(CurrentDir, "xlights_rgbeffects.xml").Exists()) {
        report.AddFile(wxFileName(CurrentDir, "xlights_rgbeffects.xml").GetFullPath(), "xlights_rgbeffects.xml");
    }
    if (UnsavedRgbEffectsChanges &&  wxFileName(CurrentDir, "xlights_rgbeffects.xbkp").Exists()) {
        report.AddFile(wxFileName(CurrentDir, "xlights_rgbeffects.xbkp").GetFullPath(), "xlights_rgbeffects.xbkp");
    }

    AddLogFile(CurrentDir, "xLights_l4cpp.log", report);
    //if the rolled log exists, add it to just in case it has the information we need
    AddLogFile(CurrentDir, "xLights_l4cpp.log.1", report);

    if (GetSeqXmlFileName() != "") {
        wxFileName fn(GetSeqXmlFileName());
        if (fn.Exists() && !fn.IsDir()) {
            report.AddFile(GetSeqXmlFileName(), fn.GetName());
            if (mSavedChangeCount != mSequenceElements.GetChangeCount())
            {
                wxFileName fnb(fn.GetPath() + "/" + fn.GetName() + ".xbkp");
                if (fnb.Exists())
                {
                    report.AddFile(fnb.GetFullPath(), fnb.GetName());
                }
            }
        }
        else
        {
            if (mSavedChangeCount != mSequenceElements.GetChangeCount())
            {
                wxFileName fnb(CurrentDir + "/" + "__.xbkp");
                if (fnb.Exists())
                {
                    report.AddFile(fnb.GetFullPath(), fnb.GetName());
                }
            }
        }
    }
    else
    {
        if (mSavedChangeCount != mSequenceElements.GetChangeCount())
        {
            wxFileName fnb(CurrentDir + "/" + "__.xbkp");
            if (fnb.Exists())
            {
                report.AddFile(fnb.GetFullPath(), fnb.GetName());
            }
        }
    }
    //report.AddAll(wxDebugReport::Context_Current);
}

void xLightsFrame::OnMenuOpenGLSelected(wxCommandEvent& event)
{
    wxConfigBase* config = wxConfigBase::Get();
    OpenGLMenu->Check(ID_MENU_OPENGL_AUTO, false);
    OpenGLMenu->Check(ID_MENU_OPENGL_3, false);
    OpenGLMenu->Check(ID_MENU_OPENGL_2, false);
    OpenGLMenu->Check(ID_MENU_OPENGL_1, false);

    if (event.GetId() == ID_MENU_OPENGL_AUTO) {
        config->Write("ForceOpenGLVer", 99);
    } else if (event.GetId() == ID_MENU_OPENGL_3) {
        config->Write("ForceOpenGLVer", 3);
    } else if (event.GetId() == ID_MENU_OPENGL_2) {
        config->Write("ForceOpenGLVer", 2);
    } else if (event.GetId() == ID_MENU_OPENGL_1) {
        config->Write("ForceOpenGLVer", 1);
    }
    OpenGLMenu->Check(event.GetId(), true);
    wxMessageBox("OpenGL changes require a restart\n");
}

void xLightsFrame::SaveWorkingLayout()
{
    // update xml with offsets and scale
    for (size_t i = 0; i < modelPreview->GetModels().size(); i++)
    {
        modelPreview->GetModels()[i]->UpdateXmlWithScale();
    }
    SaveEffectsFile(true);
}

void xLightsFrame::SaveWorking()
{
    // dont save if no file in existence
    if (CurrentSeqXmlFile == nullptr) return;

    // dont save if currently saving
    std::unique_lock<std::mutex> lock(saveLock, std::try_to_lock);
    if (!lock.owns_lock()) return;

    wxString p = CurrentSeqXmlFile->GetPath();
    wxString fn = CurrentSeqXmlFile->GetFullName();
    wxString tmp;

    if (fn == "")
    {
        tmp = p + "/" + "__.xbkp";
    }
    else
    {
        wxFileName fnp(fn);
        tmp = p + "/" + fnp.GetName() + ".xbkp";
    }
    wxFileName ftmp(tmp);

    CurrentSeqXmlFile->SetPath(ftmp.GetPath());
    CurrentSeqXmlFile->SetFullName(ftmp.GetFullName());

    CurrentSeqXmlFile->Save(mSequenceElements);

    CurrentSeqXmlFile->SetPath(p);
    CurrentSeqXmlFile->SetFullName(fn);
}

void xLightsFrame::OnTimer_AutoSaveTrigger(wxTimerEvent& event)
{
    // dont save if currently playing
    if (playType != PLAY_TYPE_MODEL) {
        static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
        logger_base.debug("Autosaving backup of sequence.");
        wxStopWatch sw;
        if (mSavedChangeCount != mSequenceElements.GetChangeCount())
        {
            if (mSequenceElements.GetChangeCount() != mLastAutosaveCount)
            {
                SaveWorking();
                mLastAutosaveCount = mSequenceElements.GetChangeCount();
            }
            else
            {
                logger_base.debug("    Autosave skipped ... no changes detected since last autosave.");
            }
        }
        else
        {
            logger_base.debug("    Autosave skipped ... no changes detected since last save.");
            mLastAutosaveCount = mSequenceElements.GetChangeCount();
        }
        if (UnsavedRgbEffectsChanges)
        {
            logger_base.debug("    Autosaving backup of layout.");
            SaveWorkingLayout();
        }
        logger_base.debug("    AutoSave took %d ms.", sw.Time());
    }
    if (AutoSaveInterval > 0) {
        Timer_AutoSave.StartOnce(AutoSaveInterval * 60000);
    }
}

void xLightsFrame::AutoSaveIntervalSelected(wxCommandEvent& event)
{
    wxString v = AutoSaveMenu->GetLabel(event.GetId());
    AutoSaveMenu->Check(event.GetId(), true);
    int nasi = -1;
    if (v == "Disabled") {
        nasi = -1;
        Timer_AutoSave.Stop();
    } else {
        nasi = wxAtoi(v);
    }
    if (nasi != AutoSaveInterval) {
        wxConfigBase* config = wxConfigBase::Get();
        config->Write("AutoSaveInterval", nasi);
        AutoSaveInterval = nasi;
    }
    if (AutoSaveInterval > 0) {
        Timer_AutoSave.StartOnce(AutoSaveInterval * 60000);
    } else {
        Timer_AutoSave.Stop();
    }
}

void xLightsFrame::AddPreviewOption(LayoutGroup* grp)
{
    bool menu_created = false;
    if( MenuItemPreviews == nullptr ) {
        MenuItemPreviews = new wxMenu();
        MenuView->Insert(3, ID_MENU_ITEM_PREVIEWS, _("Previews"), MenuItemPreviews, wxEmptyString);
        menu_created = true;
    }
    if( LayoutGroups.size() > 1 ) {
        wxMenuItem* first_item = MenuItemPreviews->GetMenuItems().GetFirst()->GetData();
        if( first_item->GetId() != ID_MENU_ITEM_PREVIEWS_SHOW_ALL ) {
            wxMenuItem* menu_item = new wxMenuItem(MenuItemPreviews, ID_MENU_ITEM_PREVIEWS_SHOW_ALL, _("Show All"), wxEmptyString, wxITEM_CHECK);
            MenuItemPreviews->Insert(0, menu_item);
            Connect(ID_MENU_ITEM_PREVIEWS_SHOW_ALL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideAllPreviewWindows, nullptr, this);
        }
    }
    grp->AddToPreviewMenu(MenuItemPreviews);
    Connect(grp->GetMenuId(),wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHidePreviewWindow, nullptr, this);
    if( menu_created ) {
        MenuItemPreviewSeparator = MenuView->InsertSeparator(4);
    }
}

void xLightsFrame::RemovePreviewOption(LayoutGroup* grp)
{
    Disconnect(grp->GetMenuId(),wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHidePreviewWindow, nullptr, this);
    grp->RemoveFromPreviewMenu(MenuItemPreviews);
    if( LayoutGroups.size() == 1 ) {
        Disconnect(ID_MENU_ITEM_PREVIEWS_SHOW_ALL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xLightsFrame::ShowHideAllPreviewWindows, nullptr, this);
        MenuView->Delete(ID_MENU_ITEM_PREVIEWS);
        MenuItemPreviews = nullptr;
        MenuView->Delete(MenuItemPreviewSeparator);
    }
}

void xLightsFrame::ShowHidePreviewWindow(wxCommandEvent& event)
{
    wxMenuItem* item = MenuItemPreviews->FindItem(event.GetId());
    for (auto it = LayoutGroups.begin(); it != LayoutGroups.end(); it++) {
        LayoutGroup* grp = (LayoutGroup*)(*it);
        if (grp != nullptr) {
            if( grp->GetMenuItem() == item ) {
                grp->ShowPreview(item->IsChecked());
            }
        }
    }
}

void xLightsFrame::ShowHideAllPreviewWindows(wxCommandEvent& event)
{
    wxMenuItem* first_item = MenuItemPreviews->GetMenuItems().GetFirst()->GetData();
    for (auto it = LayoutGroups.begin(); it != LayoutGroups.end(); it++) {
        LayoutGroup* grp = (LayoutGroup*)(*it);
        if (grp != nullptr) {
            grp->ShowPreview(first_item->IsChecked());
        }
    }
}

void xLightsFrame::OnmBackupOnSaveSelected(wxCommandEvent& event)
{
    mBackupOnSave = event.IsChecked();
}

void xLightsFrame::OnmAltBackupLocationMenuItemSelected(wxCommandEvent& event)
{
    wxDirDialog dir(this, _("Select alternate backup directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    if (dir.ShowModal() == wxID_OK)
    {
        mAltBackupDir = dir.GetPath();
        static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
        logger_base.info("Alternate backup location set to %s.", (const char *)mAltBackupDir.c_str());
    }

    if (wxDir::Exists(mAltBackupDir))
    {
        mAltBackupMenuItem->SetHelp(mAltBackupDir);
    }
    else
    {
        mAltBackupMenuItem->SetHelp("");
    }
}

void xLightsFrame::DoAltBackup(bool prompt)
{

    wxString folderName;
    time_t cur;
    time(&cur);
    wxFileName newDirH;
    wxDateTime curTime(cur);

    //  first make sure there is a Backup sub directory
    wxString newDirBackup = mAltBackupDir + wxFileName::GetPathSeparator() + "Backup";
    if (!wxDirExists(newDirBackup) && !newDirH.Mkdir(newDirBackup))
    {
        wxMessageBox("Unable to create directory Backup!", "Error", wxICON_ERROR | wxOK);
        return;
    }

    wxString newDir = mAltBackupDir + wxFileName::GetPathSeparator() + wxString::Format(
        "Backup%c%s-%s", wxFileName::GetPathSeparator(),
        curTime.FormatISODate(), curTime.Format("%H%M%S"));

    if (prompt)
    {
        if (wxNO == wxMessageBox("All xml files under 20MB in your xlights directory will be backed up to \"" +
            newDir + "\". Proceed?", "Backup", wxICON_QUESTION | wxYES_NO))
        {
            return;
        }
    }

    if (!newDirH.Mkdir(newDir))
    {
        wxMessageBox("Unable to create directory!", "Error", wxICON_ERROR | wxOK);
        return;
    }

    BackupDirectory(newDir);
}

void xLightsFrame::OnmAltBackupMenuItemSelected(wxCommandEvent& event)
{
    if (mAltBackupDir == "")
    {
        OnmAltBackupLocationMenuItemSelected(event);
    }

    if (mAltBackupDir == "")
    {
        return;
    }

    SaveWorking();

    DoAltBackup();
}

void xLightsFrame::ExportModels(wxString filename)
{
    wxFile f(filename);

    if (!f.Create(filename, true) || !f.IsOpened())
    {
        wxMessageBox(wxString::Format("Unable to create file %s. Error %d\n", filename, f.GetLastError()), _("Export Error"));
        return;
    }

    long minchannel = 99999999;
    long maxchannel = -1;

    f.Write(_("Model Name,Description,Display As,String Type,String Count,Node Count,Light Count,Channels Per Node, Channel Count,Start Channel,Start Channel No,End Channel No,My Display,Controller Type,Controller Description,Output,IP,Universe,Controller Channel,Inactive\n"));

    for (auto m = PreviewModels.begin(); m != PreviewModels.end(); ++m)
    {
        Model* model = *m;
        wxString stch = model->GetModelXml()->GetAttribute("StartChannel", wxString::Format("%d?", model->NodeStartChannel(0) + 1)); //NOTE: value coming from model is probably not what is wanted, so show the base ch# instead
        int ch = model->GetNumberFromChannelString(model->ModelStartChannel);
        std::string type, description, ip, universe, inactive;
        int channeloffset, output;
        GetControllerDetailsForChannel(ch, type, description, channeloffset, ip, universe, inactive, output);
        f.Write(wxString::Format("\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,%d,%d,%d,%s,%d,%d,%s,%s,\"%s\",%d,%s,%s,%d,%s\n",
            model->name,
            model->description,
            model->GetDisplayAs(),
            model->GetStringType(),
            model->GetNodeCount() / model->NodesPerString(),
            model->GetNodeCount(),
            model->GetNodeCount() * model->GetLightsPerNode(),
            model->GetChanCountPerNode(),
            model->GetActChanCount(),
            stch,
            ch,
            ch + model->GetChanCount() - 1,
            model->GetLayoutGroup(),
            type,
            description,
            output,
            ip,
            universe,
            channeloffset,
            inactive));
        if (ch < minchannel)
        {
            minchannel = ch;
        }
        if (ch + model->GetChanCount() - 1 > maxchannel)
        {
            maxchannel = ch + model->GetChanCount() - 1;
        }
    }

    int* chused = (int*)malloc((maxchannel - minchannel + 1) * sizeof(int));
    memset(chused, 0x00, (maxchannel - minchannel + 1) * sizeof(int));

    int bulbs = 0;
    for (auto m = PreviewModels.begin(); m != PreviewModels.end(); m++)
    {
        Model* model = *m;
        wxString stch = model->GetModelXml()->GetAttribute("StartChannel", wxString::Format("%d?", model->NodeStartChannel(0) + 1)); //NOTE: value coming from model is probably not what is wanted, so show the base ch# instead
        int ch = model->GetNumberFromChannelString(model->ModelStartChannel);
        int endch = ch + model->GetChanCount() - 1;

        int uniquechannels = 0;
        for (int i = ch; i <= endch; i++)
        {
            if (chused[i - minchannel] == 0)
            {
                uniquechannels++;
            }
            chused[i - minchannel]++;
        }

        if (wxString(model->GetStringType()).StartsWith("Single Color"))
        {
            bulbs += uniquechannels * model->GetNodeCount() * model->GetLightsPerNode();
        }
        else if (wxString(model->GetStringType()).StartsWith("3 Channel"))
        {
            bulbs += uniquechannels * model->GetNodeCount() / 3 * model->GetLightsPerNode();
        }
        else if (wxString(model->GetStringType()).StartsWith("4 Channel"))
        {
            bulbs += uniquechannels * model->GetNodeCount() / 4 * model->GetLightsPerNode();
        }
        else if (wxString(model->GetStringType()).StartsWith("Strobes"))
        {
            bulbs += uniquechannels * model->GetNodeCount() * model->GetLightsPerNode();
        }
        else
        {
            int den = model->GetChanCountPerNode();
            if (den == 0) den = 1;
            bulbs += uniquechannels / den * model->GetLightsPerNode();
        }
    }

    int usedchannels = 0;
    for (int i = 0; i < (maxchannel - minchannel + 1); i++)
    {
        if (chused[i] > 0)
        {
            usedchannels++;
        }
    }

    free(chused);

    f.Write("\n");

    f.Write(wxString::Format("\"Model Count\",%d\n", PreviewModels.size()));
    f.Write(wxString::Format("\"First Used Channel\",%d\n", minchannel));
    f.Write(wxString::Format("\"Last Used Channel\",%d\n", maxchannel));
    f.Write(wxString::Format("\"Actual Used Channel\",%d\n", usedchannels));
    f.Write(wxString::Format("\"Bulbs\",%d\n", bulbs));

    f.Close();
}

void xLightsFrame::OnmExportModelsMenuItemSelected(wxCommandEvent& event)
{
    wxLogNull logNo; //kludge: avoid "error 0" message from wxWidgets after new file is written
    wxString filename = wxFileSelector(_("Choose output file"), wxEmptyString, wxEmptyString, wxEmptyString, "Export files (*.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (filename.IsEmpty()) return;

    ExportModels(filename);
}

void xLightsFrame::OnMenuItem_BackupOnLaunchSelected(wxCommandEvent& event)
{
    mBackupOnLaunch = event.IsChecked();
}

void xLightsFrame::OnMenuItem_ViewLogSelected(wxCommandEvent& event)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    wxString dir;
    wxString fileName = "xLights_l4cpp.log";
#ifdef __WXMSW__
    wxGetEnv("APPDATA", &dir);
    wxString filename = dir + "/" + fileName;
#endif
#ifdef __WXOSX_MAC__
    wxFileName home;
    home.AssignHomeDir();
    dir = home.GetFullPath();
    wxString filename = dir + "/Library/Logs/" + fileName;
#endif
#ifdef __LINUX__
    wxString filename = "/tmp/" + fileName;
#endif
    wxString fn = "";
    if (wxFile::Exists(filename))
    {
        fn = filename;
    }
    else if (wxFile::Exists(wxFileName(CurrentDir, fileName).GetFullPath()))
    {
        fn = wxFileName(CurrentDir, fileName).GetFullPath();
    }
    else if (wxFile::Exists(wxFileName(wxGetCwd(), fileName).GetFullPath()))
    {
        fn = wxFileName(wxGetCwd(), fileName).GetFullPath();
    }

    wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension("txt");
    if (fn != "" && ft)
    {
        wxString command = ft->GetOpenCommand("foo.txt");
        command.Replace("foo.txt", fn);

        logger_base.debug("Viewing log file %s.", (const char *)fn.c_str());

        wxExecute(command);
        delete ft;
    }
    else
    {
        logger_base.warn("Unable to view log file %s.", (const char *)fn.c_str());
        wxMessageBox(_("Unable to show log file."), _("Error"));
    }
}

void LogAndWrite(wxFile& f, const std::string& msg)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    logger_base.debug("CheckSequence: " + msg);
    if (f.IsOpened())
    {
        f.Write(msg + "\r\n");
    }
}

// recursively check whether a start channel refers to a model in a way that creates a referencing loop
bool xLightsFrame::CheckStart(wxFile& f, const std::string& startmodel, std::list<std::string>& seen, std::string& nextmodel)
{
    Model* m = AllModels.GetModel(nextmodel);
    if (m == nullptr)
    {
        return true; // this is actually an error but we have already reported these errors
    }
    else
    {
        std::string start = m->ModelStartChannel;

        if (start[0] == '>' || start[0] == '@')
        {
            seen.push_back(nextmodel);
            size_t colon = start.find(':', 1);
            std::string reference = start.substr(1, colon - 1);

            if (std::find(seen.begin(), seen.end(), reference) != seen.end())
            {
                wxString msg = wxString::Format("    ERR: Model '%s' start channel results in a reference loop.", startmodel);
                LogAndWrite(f, msg.ToStdString());
                for (auto it = seen.begin(); it != seen.end(); ++it)
                {
                    msg = wxString::Format("       '%s' ->", *it);
                    LogAndWrite(f, msg.ToStdString());
                }
                msg = wxString::Format("       '%s'", reference);
                LogAndWrite(f, msg.ToStdString());
                return false;
            }
            else
            {
                return CheckStart(f, startmodel, seen, reference);
            }
        }
        else
        {
            // it resolves to something ok
            return true;
        }
    }
}

void xLightsFrame::CheckSequence(bool display)
{
    static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));

    int errcount = 0;
    int warncount = 0;
    int errcountsave = 0;
    int warncountsave = 0;

    wxFile f;
    wxString filename = wxFileName::CreateTempFileName("xLightsCheckSequence") + ".txt";

    if (display)
    {
        f.Open(filename, wxFile::write);
        if (!f.IsOpened())
        {
            logger_base.warn("Unable to create results file for Check Sequence. Aborted.");
            wxMessageBox(_("Unable to create results file for Check Sequence. Aborted."), _("Error"));
            return;
        }
    }

    LogAndWrite(f, "Checking sequence.");

    wxIPV4address addr;
    addr.Hostname(wxGetHostName());
    LogAndWrite(f, "");
    LogAndWrite(f, "IP Address we are outputing data from: " + addr.IPAddress().ToStdString());
    LogAndWrite(f, "If your PC has multiple network connections (such as wired and wireless) this should be the IP Address of the adapter your controllers are connected to. If it isnt your controllers may not receive output data.");
    LogAndWrite(f, "If you are experiencing this problem you may need to disable this network connection.");

    LogAndWrite(f, "");
    LogAndWrite(f, "Inactive Outputs");

    // Check for inactive outputs
    wxXmlNode* n = NetworkXML.GetRoot();
    int i = 0;
    for (n = n->GetChildren(); n != nullptr; n = n->GetNext())
    {
        if (n->GetName() == "network")
        {
            i++;

            if (n->GetAttribute("Enabled", "Yes") != "Yes")
            {
                wxString NetType = n->GetAttribute("NetworkType", "");
                wxString ip = n->GetAttribute("ComPort", "");
                wxString universe = n->GetAttribute("BaudRate", "1");
                wxString desc = xLightsXmlFile::UnXmlSafe(n->GetAttribute("Description", ""));

                wxString msg = wxString::Format("    WARN: Inactive output %d %s:%s:%s:'%s'.", i, NetType, ip, universe, desc);
                LogAndWrite(f, msg.ToStdString());
                warncount++;
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    LogAndWrite(f, "");
    LogAndWrite(f, "Invalid start channels");

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() != "ModelGroup")
        {
            std::string start = it->second->ModelStartChannel;

            if (start[0] == '>' || start[0] == '@')
            {
                size_t colon = start.find(':', 1);
                std::string reference = start.substr(1, colon - 1);

                if (reference == it->first)
                {
                    wxString msg = wxString::Format("    ERR: Model '%s' start channel '%s' refers to itself.", it->first, start);
                    LogAndWrite(f, msg.ToStdString());
                    errcount++;
                }
                else
                {
                    Model *m = AllModels.GetModel(reference);
                    if (m == nullptr)
                    {
                        wxString msg = wxString::Format("    ERR: Model '%s' start channel '%s' refers to non existent model '%s'.", it->first, start, reference);
                        LogAndWrite(f, msg.ToStdString());
                        errcount++;
                    }
                }
            }
        }
    }

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() != "ModelGroup")
        {
            std::string start = it->second->ModelStartChannel;

            if (start[0] == '>' || start[0] == '@')
            {
                std::list<std::string> seen;
                seen.push_back(it->first);
                size_t colon = start.find(':', 1);
                if (colon != std::string::npos)
                {
                    std::string reference = start.substr(1, colon - 1);
                    if (reference != it->first)
                    {
                        if (!CheckStart(f, it->first, seen, reference))
                        {
                            errcount++;
                        }
                    }
                }
                else
                {
                    wxString msg = wxString::Format("    ERR: Model '%s' start channel '%s' invalid.", it->first, start);
                    LogAndWrite(f, msg.ToStdString());
                    errcount++;
                }
            }
            else if (start[0] == '#')
            {
                size_t colon = start.find(':', 1);
                if (colon != std::string::npos)
                {
                    int universe = wxAtoi(wxString(start.substr(1, colon - 1)));

                    auto universes = AllModels.GetNetInfo().GetUniverses();

                    if (std::find(universes.begin(), universes.end(), universe) == universes.end())
                    {
                        wxString msg = wxString::Format("    ERR: Model '%s' start channel '%s' refers to undefined universe %d.", it->first, start, universe);
                        LogAndWrite(f, msg.ToStdString());
                        errcount++;
                    }
                }
                else
                {
                    wxString msg = wxString::Format("    ERR: Model '%s' start channel '%s' invalid.", it->first, start);
                    LogAndWrite(f, msg.ToStdString());
                    errcount++;
                }
            }
            else if (start.find(':') != std::string::npos)
            {
                size_t colon = start.find(':');
                int output = wxAtoi(wxString(start.substr(0, colon)));

                auto outputs = AllModels.GetNetInfo().GetNumNetworks();

                if (output < 1 || output > outputs)
                {
                    wxString msg = wxString::Format("    ERR: Model '%s' start channel '%s' refers to undefined output %d. Only %d outputs are defined.", it->first, start, output, outputs);
                    LogAndWrite(f, msg.ToStdString());
                    errcount++;
                }
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    LogAndWrite(f, "");
    LogAndWrite(f, "Overlapping model channels");

    // Check for overlapping channels in models
    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() != "ModelGroup")
        {
            int m1start = it->second->GetNumberFromChannelString(it->second->ModelStartChannel);
            int m1end = m1start + it->second->GetChanCount() - 1;
            //int m1end = m1start + it->second->GetActChanCount() - 1; // I dont think this is a good idea

            auto it2 = it;
            ++it2;
            for (; it2 != AllModels.end(); ++it2)
            {
                if (it2->second->GetDisplayAs() != "ModelGroup")
                {
                    int m2start = it2->second->GetNumberFromChannelString(it2->second->ModelStartChannel);
                    int m2end = m2start + it2->second->GetChanCount() - 1;
                    //int m2end = m2start + it2->second->GetActChanCount() - 1; // I dont think this is a good idea

                    if (m2start <= m1end && m2end >= m1start)
                    {
                        wxString msg = wxString::Format("    WARN: Probable model overlap '%s' (%d-%d) and '%s' (%d-%d).", it->first, m1start, m1end, it2->first, m2start, m2end);
                        LogAndWrite(f, msg.ToStdString());
                        warncount++;
                    }
                }
            }
        }
    }
    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    LogAndWrite(f, "");
    LogAndWrite(f, "Model nodes not allocated to layers correctly");

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() != "ModelGroup")
        {
            if (wxString(it->second->GetStringType()).EndsWith("Nodes") && !it->second->AllNodesAllocated())
            {
                wxString msg = wxString::Format("    WARN: %s model '%s' Node Count and Layer Size allocations dont match.", it->second->GetDisplayAs().c_str(), it->first);
                LogAndWrite(f, msg.ToStdString());
                warncount++;
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    LogAndWrite(f, "");
    LogAndWrite(f, "Custom models with odd looking channels");

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() == "Custom")
        {
            CustomModel* cm = dynamic_cast<CustomModel*>(it->second);
            if (cm != nullptr)
            {
                // check for no nodes
                if (cm->GetNodeCount() == 0)
                {
                    wxString msg = wxString::Format("    ERR: Custom model '%s' has no nodes defined.", (const char *)cm->GetName().c_str());
                    LogAndWrite(f, msg.ToStdString());
                    errcount++;
                }

                // check for node gaps
                int maxn = 0;
                for (int ii = 0; ii < cm->GetNodeCount(); ii++)
                {
                    int nn = cm->GetNodeStringNumber(ii);
                    if (nn > maxn) maxn = nn;
                }
                maxn++;
                int chssize = (maxn+1) * sizeof(int);
                logger_base.debug("    CheckSequence: Checking custom model %d nodes", maxn);
                int* chs = (int*)malloc(chssize);
                if (chs == nullptr)
                {
                    wxString msg = wxString::Format("    WARN: Could not check Custom model '%s' for missing nodes. Error allocating memory for %d nodes.", (const char *)cm->GetName().c_str(), maxn);
                    LogAndWrite(f, msg.ToStdString());
                    warncount++;
                }
                else
                {
                    memset(chs, 0x00, chssize);

                    for (int ii = 0; ii < cm->GetNodeCount(); ii++)
                    {
                        int nn = cm->GetNodeStringNumber(ii);
                        chs[nn + 1]++;
                    }

                    for (int ii = 1; ii <= maxn; ii++)
                    {
                        if (chs[ii] == 0)
                        {
                            wxString msg = wxString::Format("    WARN: Custom model '%s' missing node %d.", (const char *)cm->GetName().c_str(), ii);
                            LogAndWrite(f, msg.ToStdString());
                            warncount++;
                        }
                    }
                    free(chs);
                }
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    LogAndWrite(f, "");
    LogAndWrite(f, "Model Groups containing models from different previews");

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() == "ModelGroup")
        {
            std::string mgp = it->second->GetLayoutGroup();

            ModelGroup* mg = dynamic_cast<ModelGroup*>(it->second);
            auto models = mg->ModelNames();

            for (auto it2 = models.begin(); it2 != models.end(); ++it2)
            {
                Model* m = AllModels.GetModel(*it2);
                if (m->GetDisplayAs() != "ModelGroup")
                {
                    // If model is in all previews dont report it as a problem
                    if (m->GetLayoutGroup() != "All Previews" && mgp != m->GetLayoutGroup())
                    {
                        wxString msg = wxString::Format("    WARN: Model Group '%s' in preview '%s' contains model '%s' which is in preview '%s'. This will cause the '%s' model to also appear in the '%s' preview.", mg->GetName(), mg->GetLayoutGroup(), m->GetName(), m->GetLayoutGroup(), m->GetName(), mg->GetLayoutGroup());
                        LogAndWrite(f, msg.ToStdString());
                        warncount++;
                    }
                }
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    // Check for duplicate model/model group names
    LogAndWrite(f, "");
    LogAndWrite(f, "Model/Model Groups without distinct names");

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        auto it2 = it;
        ++it2;
        for (; it2 != AllModels.end(); ++it2)
        {
            if (it->second->GetName() == it2->second->GetName())
            {
                wxString msg = wxString::Format("    ERR: Duplicate Model/Model Group Name '%s'.", it->second->GetName());
                LogAndWrite(f, msg.ToStdString());
                errcount++;
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    // Check for model groups containing itself or other model groups
    LogAndWrite(f, "");
    LogAndWrite(f, "Model Groups containing other model groups or non existent models");

    for (auto it = AllModels.begin(); it != AllModels.end(); ++it)
    {
        if (it->second->GetDisplayAs() == "ModelGroup")
        {
            ModelGroup* mg = dynamic_cast<ModelGroup*>(it->second);
            auto models = mg->ModelNames();

            for (auto m = models.begin(); m != models.end(); ++m)
            {
                Model* model = AllModels.GetModel(*m);

                if (model == nullptr)
                {
                    wxString msg = wxString::Format("    ERR: Model group '%s' refers to non existent model '%s'.", mg->GetName(), model->GetName());
                    LogAndWrite(f, msg.ToStdString());
                    errcount++;
                }
                else
                {
                    if (model->GetDisplayAs() == "ModelGroup")
                    {
                        wxString msg = wxString::Format("    ERR: Model group '%s' contains another model group '%s'. Nested model groups are not supported at this time.", mg->GetName(), model->GetName());
                        LogAndWrite(f, msg.ToStdString());
                        errcount++;
                    }
                    if (model->GetName() == mg->GetName())
                    {
                        wxString msg = wxString::Format("    ERR: Model group '%s' contains reference to itself.", mg->GetName());
                        LogAndWrite(f, msg.ToStdString());
                        errcount++;
                    }
                }
            }
        }
    }

    if (errcount + warncount == errcountsave + warncountsave)
    {
        LogAndWrite(f, "    No problems found");
    }
    errcountsave = errcount;
    warncountsave = warncount;

    if (CurrentSeqXmlFile != nullptr)
    {
        LogAndWrite(f, "");
        LogAndWrite(f, "Render Mode");

        if (CurrentSeqXmlFile->GetRenderMode() == xLightsXmlFile::CANVAS_MODE)
        {
            wxString msg = wxString::Format("    WARN: Render mode set to canvas mode. Unless you specifically know you need this it is not recommended.");
            LogAndWrite(f, msg.ToStdString());
            warncount++;
        }
        else
        {
            LogAndWrite(f, "    No problems found");
        }
        errcountsave = errcount;
        warncountsave = warncount;

        if (CurrentSeqXmlFile->GetSequenceType() == "Media")
        {
            LogAndWrite(f, "");
            LogAndWrite(f, "Checking media file");

            if (!wxFileExists(CurrentSeqXmlFile->GetMediaFile()))
            {
                wxString msg = wxString::Format("    ERR: media file %s does not exist.", CurrentSeqXmlFile->GetMediaFile());
                LogAndWrite(f, msg.ToStdString());
                errcount++;
            }
            else
            {
                LogAndWrite(f, "    No problems found");
            }
        }
        errcountsave = errcount;
        warncountsave = warncount;

        LogAndWrite(f, "");
        LogAndWrite(f, "Checking autosave");

        if (CurrentSeqXmlFile->FileExists())
        {
            // set to log if >1MB and autosave is more than every 10 minutes
            wxULongLong size = CurrentSeqXmlFile->GetSize();
            if (size > 1000000 && AutoSaveInterval < 10)
            {
                wxULongLong mbull = size / 100000;
                double mb = mbull.ToDouble() / 10.0;
                wxString msg = wxString::Format("    WARN: Sequence file size %.1fMb is large. Consider making autosave less frequent to prevent xlights pausing too often when it autosaves.", mb);
                LogAndWrite(f, msg.ToStdString());
                warncount++;
            }

            if (errcount + warncount == errcountsave + warncountsave)
            {
                LogAndWrite(f, "    No problems found");
            }
            errcountsave = errcount;
            warncountsave = warncount;
        }
        else
        {
            LogAndWrite(f, "    Test skipped as sequence has never been saved.");
        }

        LogAndWrite(f, "");
        LogAndWrite(f, "Models hidden by effects on groups");

        // Check for groups that contain models that have appeared before the group at the bottom of the master view
        wxString models = mSequenceElements.GetViewModels(mSequenceElements.GetViewName(0));
        wxArrayString modelnames = wxSplit(models, ',');

        std::list<std::string> seenmodels;
        for (auto it = modelnames.begin(); it != modelnames.end(); ++it)
        {
            Model* m = AllModels.GetModel(it->ToStdString());
            if (m->GetDisplayAs() == "ModelGroup")
            {
                ModelGroup* mg = dynamic_cast<ModelGroup*>(m);
                auto cm = mg->Models();
                for (auto it2 = cm.begin(); it2 != cm.end(); ++it2)
                {
                    if (std::find(seenmodels.begin(), seenmodels.end(), (*it2)->GetName()) != seenmodels.end())
                    {
                        wxString msg = wxString::Format("    WARN: Model Group '%s' will hide effects on model '%s'.", mg->GetName(), (*it2)->GetName());
                        LogAndWrite(f, msg.ToStdString());
                        warncount++;
                    }
                }
            }
            else
            {
                seenmodels.push_back(m->GetName());
            }
        }

        if (errcount + warncount == errcountsave + warncountsave)
        {
            LogAndWrite(f, "    No problems found");
        }
        errcountsave = errcount;
        warncountsave = warncount;

        LogAndWrite(f, "");
        LogAndWrite(f, "Effect problems");

        // check all effects
        EffectManager& em = mSequenceElements.GetEffectManager();
        for (i = 0; i < mSequenceElements.GetElementCount(0); i++)
        {
            Element* e = mSequenceElements.GetElement(i);
            if (e->GetType() != ELEMENT_TYPE_TIMING)
            {
                for (int j = 0; j < e->GetEffectLayerCount(); j++)
                {
                    EffectLayer* el = e->GetEffectLayer(j);

                    for (int k = 0; k < el->GetEffectCount(); k++)
                    {
                        Effect* ef = el->GetEffect(k);

                        SettingsMap& sm = ef->GetSettings();
                        RenderableEffect* re = em.GetEffect(ef->GetEffectIndex());

                        // check excessive fadein/fadeout time
                        float fadein = sm.GetFloat("T_TEXTCTRL_Fadein", 0.0);
                        float fadeout = sm.GetFloat("T_TEXTCTRL_Fadeout", 0.0);
                        float efdur = (ef->GetEndTimeMS() - ef->GetStartTimeMS()) / 1000.0;

                        if (fadein > efdur)
                        {
                            wxString msg = wxString::Format("    WARN: Transition in time %.2f on effect %s at start time %s  on Model '%s' is greater than effect duration %.2f.", fadein, ef->GetEffectName(), FORMATTIME(ef->GetStartTimeMS()), e->GetModelName(), efdur);
                            LogAndWrite(f, msg.ToStdString());
                            warncount++;
                        }
                        if (fadeout > efdur)
                        {
                            wxString msg = wxString::Format("    WARN: Transition out time %.2f on effect %s at start time %s  on Model '%s' is greater than effect duration %.2f.", fadeout, ef->GetEffectName(), FORMATTIME(ef->GetStartTimeMS()), e->GetModelName(), efdur);
                            LogAndWrite(f, msg.ToStdString());
                            warncount++;
                        }
                        if (fadein <= efdur && fadeout <= efdur && fadein + fadeout > efdur)
                        {
                            wxString msg = wxString::Format("    WARN: Transition in time %.2f + transition out time %.2f = %.2f on effect %s at start time %s  on Model '%s' is greater than effect duration %.2f.", fadein, fadeout, fadein + fadeout, ef->GetEffectName(), FORMATTIME(ef->GetStartTimeMS()), e->GetModelName(), efdur);
                            LogAndWrite(f, msg.ToStdString());
                            warncount++;
                        }

                        // effect that runs past end of the sequence
                        if (ef->GetEndTimeMS() > CurrentSeqXmlFile->GetSequenceDurationMS())
                        {
                            wxString msg = wxString::Format("    WARN: Effect %s ends at %s after the sequence end %s. Model: '%s' Start: %s", ef->GetEffectName(), FORMATTIME(ef->GetEndTimeMS()), FORMATTIME(CurrentSeqXmlFile->GetSequenceDurationMS()), e->GetModelName(), FORMATTIME(ef->GetStartTimeMS()));
                            LogAndWrite(f, msg.ToStdString());
                            warncount++;
                        }

                        std::list<std::string> warnings = re->CheckEffectSettings(sm, CurrentSeqXmlFile->GetMedia(), AllModels.GetModel(e->GetModelName()), ef);
                        for (auto s = warnings.begin(); s != warnings.end(); ++s)
                        {
                            LogAndWrite(f, *s);
                            if (s->find("WARN:") != std::string::npos)
                            {
                                warncount++;
                            }
                            else if (s->find("ERR:")  != std::string::npos)
                            {
                                errcount++;
                            }
                        }
                    }
                }
            }
        }

        if (errcount + warncount == errcountsave + warncountsave)
        {
            LogAndWrite(f, "    No problems found");
        }
        errcountsave = errcount;
        warncountsave = warncount;
    }
    else
    {
        LogAndWrite(f, "");
        LogAndWrite(f, "No sequence loaded so sequence checks skipped.");
    }

    LogAndWrite(f, "");
    LogAndWrite(f, "Check sequence done.");
    LogAndWrite(f, wxString::Format("Errors: %d. Warnings: %d", errcount, warncount).ToStdString());

    if (f.IsOpened())
    {
        f.Close();

        wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension("txt");
        if (ft)
        {
            wxString command = ft->GetOpenCommand(filename);

            logger_base.debug("Viewing xLights Check Sequence results %s.", (const char *)filename.c_str());

            wxExecute(command);
            delete ft;
        }
        else
        {
            logger_base.warn("Unable to view xLights Check Sequence results %s.", (const char *)filename.c_str());
            wxMessageBox(_("Unable to show xLights Check Sequence results."), _("Error"));
        }
    }
}

void xLightsFrame::OnMenuItemCheckSequenceSelected(wxCommandEvent& event)
{
    CheckSequence(true);
}

void xLightsFrame::OnMenuItem_e131syncSelected(wxCommandEvent& event)
{
    NetworkChange();
    me131Sync = event.IsChecked();
    ShowHideSync();
    if (me131Sync)
    {
        // recycle output connections if necessary
        EnableOutputs();
    }
}

void xLightsFrame::ShowHideSync()
{
    if (me131Sync)
    {
        SpinCtrl_SyncUniverse->Show();
        StaticText5->Show();
        SetSyncUniverse(SpinCtrl_SyncUniverse->GetValue());
    }
    else
    {
        SpinCtrl_SyncUniverse->Hide();
        StaticText5->Hide();
        SetSyncUniverse(0);
    }
}

void xLightsFrame::OnMenuItem_Help_ForumSelected(wxCommandEvent& event)
{
    ::wxLaunchDefaultBrowser("http://nutcracker123.com/forum/");
}

void xLightsFrame::OnMenuItem_Help_DownloadSelected(wxCommandEvent& event)
{
    ::wxLaunchDefaultBrowser("http://xlights.org");
}

void xLightsFrame::OnMenuItem_Help_ReleaseNotesSelected(wxCommandEvent& event)
{
    wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension("txt");
    if (ft)
    {
        wxString command = ft->GetOpenCommand("README.txt");
        wxExecute(command);
    }
}

void xLightsFrame::OnMenuItem_Help_Isue_TrackerSelected(wxCommandEvent& event)
{
    ::wxLaunchDefaultBrowser("https://github.com/smeighan/xLights/issues");
}

void xLightsFrame::OnMenuItem_Help_FacebookSelected(wxCommandEvent& event)
{
    ::wxLaunchDefaultBrowser("https://www.facebook.com/groups/628061113896314/");
}

int xLightsFrame::ExportNodes(wxFile& f, StrandElement* e, NodeLayer* nl, int n, std::map<std::string, int>& effectfrequency, std::map<std::string, int>& effectTotalTime)
{
    int effects = 0;
    wxString type = "Node";
    wxString name = wxString::Format("%sStrand %d/Node %d", e->GetFullName(), e->GetStrand()+1, n);

    EffectLayer* el = nl;

    for (int k = 0; k < nl->GetEffectCount(); k++)
    {
        Effect* ef = nl->GetEffect(k);
        int duration = ef->GetEndTimeMS() - ef->GetStartTimeMS();
        if (effectfrequency.find(ef->GetEffectName()) != effectfrequency.end())
        {
            effectfrequency[ef->GetEffectName()]++;
            effectTotalTime[ef->GetEffectName()] += duration;
        }
        else
        {
            effectfrequency[ef->GetEffectName()] = 1;
            effectTotalTime[ef->GetEffectName()] = duration;
        }

        SettingsMap& sm = ef->GetSettings();
        f.Write(wxString::Format("\"%s\",%02d:%02d.%03d,%02d:%02d.%03d,%02d:%02d.%03d,\"%s\",\"%s\",%s\n",
            ef->GetEffectName(),
            ef->GetStartTimeMS() / 60000,
            (ef->GetStartTimeMS() % 60000) / 1000,
            ef->GetStartTimeMS() % 1000,
            ef->GetEndTimeMS() / 60000,
            (ef->GetEndTimeMS() % 60000) / 1000,
            ef->GetEndTimeMS() % 1000,
            duration / 60000,
            (duration % 60000) / 1000,
            duration % 1000,
            sm.Contains("X_Effect_Description") ? sm["X_Effect_Description"] : "",
            name,
            type));
        effects++;
    }

    return effects;
}

int xLightsFrame::ExportElement(wxFile& f, Element* e, std::map<std::string, int>& effectfrequency, std::map<std::string, int>& effectTotalTime)
{
    int effects = 0;

    if (e->GetType() != ELEMENT_TYPE_TIMING)
    {
        Model* m = AllModels.GetModel(e->GetModelName());

        wxString type = "Unknown";
        wxString subname = "";
        switch (e->GetType())
        {
        case     ELEMENT_TYPE_MODEL:
            if (m->GetDisplayAs() == "ModelGroup")
            {
                type = "Model Group";
            }
            else
            {
                type = "Model";
            }
            break;
        case ELEMENT_TYPE_SUBMODEL:
            type = "Submodel";
            break;
        case ELEMENT_TYPE_STRAND:
            type = "Strand";
            subname = wxString::Format("Strand %d", dynamic_cast<StrandElement*>(e)->GetStrand() + 1);
            break;
        case ELEMENT_TYPE_TIMING:
            type = "Timing";
            break;
        }

        for (int j = 0; j < e->GetEffectLayerCount(); j++)
        {
            EffectLayer* el = e->GetEffectLayer(j);

            for (int k = 0; k < el->GetEffectCount(); k++)
            {
                Effect* ef = el->GetEffect(k);

                int duration = ef->GetEndTimeMS() - ef->GetStartTimeMS();
                if (effectfrequency.find(ef->GetEffectName()) != effectfrequency.end())
                {
                    effectfrequency[ef->GetEffectName()]++;
                    effectTotalTime[ef->GetEffectName()] += duration;
                }
                else
                {
                    effectfrequency[ef->GetEffectName()] = 1;
                    effectTotalTime[ef->GetEffectName()] = duration;
                }

                SettingsMap& sm = ef->GetSettings();
                f.Write(wxString::Format("\"%s\",%02d:%02d.%03d,%02d:%02d.%03d,%02d:%02d.%03d,\"%s\",\"%s\",%s\n",
                    ef->GetEffectName(),
                    ef->GetStartTimeMS() / 60000,
                    (ef->GetStartTimeMS() % 60000) / 1000,
                    ef->GetStartTimeMS() % 1000,
                    ef->GetEndTimeMS() / 60000,
                    (ef->GetEndTimeMS() % 60000) / 1000,
                    ef->GetEndTimeMS() % 1000,
                    duration / 60000,
                    (duration % 60000) / 1000,
                    duration % 1000,
                    sm.Contains("X_Effect_Description") ? sm["X_Effect_Description"] : "",
                    (const char *)(e->GetFullName() + subname).c_str(),
                    type));
                effects++;
            }
        }
    }

    return effects;
}

void xLightsFrame::OnMenuItem_ExportEffectsSelected(wxCommandEvent& event)
{
    if (CurrentSeqXmlFile == nullptr)
    {
        wxMessageBox("No sequence open", "Error", wxOK|wxCENTRE, this);
        return;
    }

    wxLogNull logNo; //kludge: avoid "error 0" message from wxWidgets after new file is written
    wxString filename = wxFileSelector(_("Choose output file"), wxEmptyString, wxEmptyString, wxEmptyString, "Export files (*.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (filename.IsEmpty()) return;

    ExportEffects(filename);
}

void xLightsFrame::ExportEffects(wxString filename)
{
    wxFile f(filename);

    if (!f.Create(filename, true) || !f.IsOpened())
    {
        wxMessageBox(wxString::Format("Unable to create file %s. Error %d\n", filename, f.GetLastError()), _("Export Error"));
        return;
    }

    std::map<std::string, int> effectfrequency;
    std::map<std::string, int> effecttotaltime;

    int effects = 0;
    f.Write(_("Effect Name,StartTime,EndTime,Duration,Description,Element,ElementType\n"));

    EffectManager& em = mSequenceElements.GetEffectManager();
    for (size_t i = 0; i < mSequenceElements.GetElementCount(0); i++)
    {
        Element* e = mSequenceElements.GetElement(i);
        effects += ExportElement(f, e, effectfrequency, effecttotaltime);

        if (dynamic_cast<ModelElement*>(e) != nullptr)
        {
            for (size_t s = 0; s < dynamic_cast<ModelElement*>(e)->GetSubModelCount(); s++) {
                SubModelElement *se = dynamic_cast<ModelElement*>(e)->GetSubModel(s);
                effects += ExportElement(f, se, effectfrequency, effecttotaltime);
            }
            for (size_t s = 0; s < dynamic_cast<ModelElement*>(e)->GetStrandCount(); s++) {
                StrandElement *se = dynamic_cast<ModelElement*>(e)->GetStrand(s);
                int node = 1;
                for (size_t n = 0; n < se->GetNodeLayerCount(); n++)
                {
                    NodeLayer* nl = se->GetNodeLayer(n);
                    effects += ExportNodes(f, se, nl, node++, effectfrequency, effecttotaltime);
                }
            }
        }
    }
    f.Write(wxString::Format("\"Effect Count\",%d\n", effects));
    f.Write(_("\n"));
    f.Write(_("Effect Usage Summary\n"));
    f.Write(_("Effect Name,Occurences,TotalTime\n"));
    for (auto it = effectfrequency.begin(); it != effectfrequency.end(); ++it)
    {
        int tt = effecttotaltime[it->first];
        f.Write(wxString::Format("\"%s\",%d,%02d:%02d.%03d\n",
            (const char *)it->first.c_str(),
            it->second,
            tt / 60000,
            (tt % 60000) / 1000,
            tt % 1000
        ));
    }
    f.Close();
}

void xLightsFrame::OnMenuItem_FPP_ConnectSelected(wxCommandEvent& event)
{
    FPPConnectDialog dlg(this);

    dlg.ShowModal();
}
