#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/xml/xml.h>

#include "DmxColorAbility.h"
#include "../BaseObject.h"

DmxColorAbility::DmxColorAbility()
{
}

DmxColorAbility::~DmxColorAbility()
{
    //dtor
}

void DmxColorAbility::AddColorTypeProperties(wxPropertyGridInterface *grid) {

    wxPGProperty* p = grid->Append(new wxUIntProperty("Red Channel", "DmxRedChannel", red_channel));
    p->SetAttribute("Min", 0);
    p->SetAttribute("Max", 512);
    p->SetEditor("SpinCtrl");

    p = grid->Append(new wxUIntProperty("Green Channel", "DmxGreenChannel", green_channel));
    p->SetAttribute("Min", 0);
    p->SetAttribute("Max", 512);
    p->SetEditor("SpinCtrl");

    p = grid->Append(new wxUIntProperty("Blue Channel", "DmxBlueChannel", blue_channel));
    p->SetAttribute("Min", 0);
    p->SetAttribute("Max", 512);
    p->SetEditor("SpinCtrl");

    p = grid->Append(new wxUIntProperty("White Channel", "DmxWhiteChannel", white_channel));
    p->SetAttribute("Min", 0);
    p->SetAttribute("Max", 512);
    p->SetEditor("SpinCtrl");
}

int DmxColorAbility::OnColorPropertyGridChange(wxPropertyGridInterface *grid, wxPropertyGridEvent& event, wxXmlNode* ModelXml, BaseObject* base) {

    if ("DmxRedChannel" == event.GetPropertyName()) {
        ModelXml->DeleteAttribute("DmxRedChannel");
        ModelXml->AddAttribute("DmxRedChannel", wxString::Format("%d", (int)event.GetPropertyValue().GetLong()));
        base->AddASAPWork(OutputModelManager::WORK_RGBEFFECTS_CHANGE, "DMXModel::OnPropertyGridChange::DMXRedChannel");
        base->AddASAPWork(OutputModelManager::WORK_RELOAD_MODEL_FROM_XML, "DMXModel::OnPropertyGridChange::DMXRedChannel");
        base->AddASAPWork(OutputModelManager::WORK_MODELS_CHANGE_REQUIRING_RERENDER, "DMXModel::OnPropertyGridChange::DMXRedChannel");
        base->AddASAPWork(OutputModelManager::WORK_REDRAW_LAYOUTPREVIEW, "DMXModel::OnPropertyGridChange::DMXRedChannel");
        return 0;
    } else if ("DmxGreenChannel" == event.GetPropertyName()) {
        ModelXml->DeleteAttribute("DmxGreenChannel");
        ModelXml->AddAttribute("DmxGreenChannel", wxString::Format("%d", (int)event.GetPropertyValue().GetLong()));
        base->AddASAPWork(OutputModelManager::WORK_RGBEFFECTS_CHANGE, "DMXModel::OnPropertyGridChange::DMXGreenChannel");
        base->AddASAPWork(OutputModelManager::WORK_RELOAD_MODEL_FROM_XML, "DMXModel::OnPropertyGridChange::DMXGreenChannel");
        base->AddASAPWork(OutputModelManager::WORK_MODELS_CHANGE_REQUIRING_RERENDER, "DMXModel::OnPropertyGridChange::DMXGreenChannel");
        base->AddASAPWork(OutputModelManager::WORK_REDRAW_LAYOUTPREVIEW, "DMXModel::OnPropertyGridChange::DMXGreenChannel");
        return 0;
    } else if ("DmxBlueChannel" == event.GetPropertyName()) {
        ModelXml->DeleteAttribute("DmxBlueChannel");
        ModelXml->AddAttribute("DmxBlueChannel", wxString::Format("%d", (int)event.GetPropertyValue().GetLong()));
        base->AddASAPWork(OutputModelManager::WORK_RGBEFFECTS_CHANGE, "DMXModel::OnPropertyGridChange::DMXBlueChannel");
        base->AddASAPWork(OutputModelManager::WORK_RELOAD_MODEL_FROM_XML, "DMXModel::OnPropertyGridChange::DMXBlueChannel");
        base->AddASAPWork(OutputModelManager::WORK_MODELS_CHANGE_REQUIRING_RERENDER, "DMXModel::OnPropertyGridChange::DMXBlueChannel");
        base->AddASAPWork(OutputModelManager::WORK_REDRAW_LAYOUTPREVIEW, "DMXModel::OnPropertyGridChange::DMXBlueChannel");
        return 0;
    } else if ("DmxWhiteChannel" == event.GetPropertyName()) {
        ModelXml->DeleteAttribute("DmxWhiteChannel");
        ModelXml->AddAttribute("DmxWhiteChannel", wxString::Format("%d", (int)event.GetPropertyValue().GetLong()));
        base->AddASAPWork(OutputModelManager::WORK_RGBEFFECTS_CHANGE, "DMXModel::OnPropertyGridChange::DMXWhiteChannel");
        base->AddASAPWork(OutputModelManager::WORK_RELOAD_MODEL_FROM_XML, "DMXModel::OnPropertyGridChange::DMXWhiteChannel");
        base->AddASAPWork(OutputModelManager::WORK_MODELS_CHANGE_REQUIRING_RERENDER, "DMXModel::OnPropertyGridChange::DMXWhiteChannel");
        base->AddASAPWork(OutputModelManager::WORK_REDRAW_LAYOUTPREVIEW, "DMXModel::OnPropertyGridChange::DMXWhiteChannel");
        return 0;
    }
    return -1;
}
