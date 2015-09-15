#include "svgglyphctrl.h"
#include "wxcontext.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>

#include <memory>

bool SvgGlyphCtrl::Create(wxWindow *parent, wxWindowID id, const SvgGlyph &glyph, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!SvgPathCtrlBase::Create(parent, id, glyph.data, pos, size, name))
		return false;

	svgGlyph = glyph;

	return true;
}

void SvgGlyphCtrl::SetFontSize(int size)
{
	fontSize = size;
}

int SvgGlyphCtrl::GetFontSize() const
{
	return fontSize;
}

wxSize SvgGlyphCtrl::GetMinClientSize() const
{
	if (svgGlyph.isOk()) return wxSize(static_cast<double>(svgGlyph.horizAdvX) / svgGlyph.unitsPerEm * fontSize, fontSize);
	return wxSize(8, 8);
}

void SvgGlyphCtrl::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	DrawBackground(dc);

	if (!svgPath.isOk() || !svgGlyph.isOk())
		return;

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));
	gc->SetBrush(wxBrush(color));

    RenderGlyph(gc.get(), GetClientRect(), svgPath, svgGlyph, fontSize);
}

void SvgGlyphCtrl::RenderGlyph(wxGraphicsContext *gc, const wxRect &rect, const SvgPath &svgPath, const SvgGlyph &glyph, int size)
{
    int width = glyph.horizAdvX <= 0 ? size : std::round(static_cast<double>(glyph.horizAdvX) / glyph.unitsPerEm * size);
	int height = size;
    double scale = static_cast<double>(width) / (glyph.horizAdvX > 0 ? glyph.horizAdvX : glyph.unitsPerEm);

	wxContext pathContext(gc);

    double xCenterOffset = std::round(rect.x + (rect.GetWidth() - width) / 2);
    double yCenterOffset = std::round(rect.y + (rect.GetHeight() - height) / 2);

    gc->PushState();
    gc->Translate(xCenterOffset, yCenterOffset + height);
	gc->Scale(scale, -scale);

	svgPath.render(&pathContext);

	pathContext.fill();
	gc->PopState();
}

void SvgGlyphCtrl::OnResize(wxSizeEvent &event)
{
	Refresh();
}


IMPLEMENT_DYNAMIC_CLASS(SvgGlyphCtrl, SvgPathCtrlBase)