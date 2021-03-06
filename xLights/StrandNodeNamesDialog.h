#ifndef STRANDNODENAMESDIALOG_H
#define STRANDNODENAMESDIALOG_H

//(*Headers(StrandNodeNamesDialog)
#include <wx/grid.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

class Model;

class StrandNodeNamesDialog: public wxDialog
{
	public:

		StrandNodeNamesDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~StrandNodeNamesDialog();

		//(*Declarations(StrandNodeNamesDialog)
		wxGrid* NodesGrid;
		wxGrid* StrandsGrid;
		//*)

        void Setup(const Model *md, const std::string &nodeNames, const std::string &strandNames);
    
        std::string GetNodeNames();
        std::string GetStrandNames();
	protected:

		//(*Identifiers(StrandNodeNamesDialog)
		static const long ID_GRID2;
		static const long ID_GRID1;
		//*)

	private:

		//(*Handlers(StrandNodeNamesDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
