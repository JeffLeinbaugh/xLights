#include "xlGridCanvasPictures.h"
#include "BitmapCache.h"
#include "DrawGLUtils.h"
#include <wx/filefn.h>
#include <wx/filename.h>

static const wxString strSupportedImageTypes = "PNG files (*.png)|*.png|BMP files (*.bmp)|*.bmp|JPG files(*.jpg)|*.jpg|All files (*.*)|*.*";

BEGIN_EVENT_TABLE(xlGridCanvasPictures, xlGridCanvas)
EVT_PAINT(xlGridCanvasPictures::render)
EVT_MOTION(xlGridCanvasPictures::mouseMoved)
EVT_LEFT_DOWN(xlGridCanvasPictures::mouseLeftDown)
EVT_LEFT_UP(xlGridCanvasPictures::mouseLeftUp)
EVT_RIGHT_DOWN(xlGridCanvasPictures::mouseRightDown)
EVT_RIGHT_UP(xlGridCanvasPictures::mouseRightUp)
END_EVENT_TABLE()

xlGridCanvasPictures::xlGridCanvasPictures(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size,long style, const wxString &name)
:   xlGridCanvas(parent, id, pos, size, style, name),
    mRightDown(false),
    mLeftDown(false),
    img_mode(IMAGE_NONE),
    mModified(false),
    imageCount(1),
    imageIndex(0),
    imageWidth(1),
    imageHeight(1),
    frame(0),
    maxmovieframes(0),
    use_ping(true),
    scaleh(0.0),
    scalew(0.0),
    imageGL_ping(NULL),
    imageGL_pong(NULL),
    mImage(NULL),
    sprite(NULL),
    PictureName(wxEmptyString),
    NewPictureName(wxEmptyString),
    mPaintColor(xlRED),
    mEraseColor(xlBLACK),
    mPaintMode(PAINT_PENCIL)
{
}

xlGridCanvasPictures::~xlGridCanvasPictures()
{
}

void xlGridCanvasPictures::ProcessNewImage()
{
    // process loading new image
    if( mModified )
    {
        PictureName = wxEmptyString;
        mModified = false;
    }

    if ( NewPictureName != PictureName )
    {
        wxLogNull logNo;  // suppress popups from png images. See http://trac.wxwidgets.org/ticket/15331
        imageCount = wxImage::GetImageCount(NewPictureName);
        imageIndex = 0;
        if (!image.LoadFile(NewPictureName,wxBITMAP_TYPE_ANY,0))
        {
            image.Create(mColumns, mRows, true);
        }
        if (!image.IsOk())
            return;
    }

    wxCommandEvent eventImage(EVT_IMAGE_FILE_SELECTED);
    eventImage.SetClientData(&NewPictureName);
    wxPostEvent(GetParent(), eventImage);

    int imgwidth=image.GetWidth();
    int imght   =image.GetHeight();
    if( imgwidth > mColumns || imght > mRows )
    {
        if( imageCount > 1 )
        {
            img_mode = IMAGE_MULTIPLE_OVERSIZED;
        }
        else
        {
            img_mode = IMAGE_SINGLE_OVERSIZED;
        }
    }
    else
    {
        if( imageCount > 1 )
        {
            img_mode = IMAGE_MULTIPLE_FITS;
        }
        else
        {
            img_mode = IMAGE_SINGLE_FITS;
        }
    }
    Refresh(false);
}

void xlGridCanvasPictures::LoadImage()
{
    wxFileName dummy_file(PictureName);
    // prompt for new filename
    wxFileDialog fd(this,
                    "Choose Image File to Load:",
                    dummy_file.GetPath(),
                    wxEmptyString,
                    strSupportedImageTypes,
                    wxFD_OPEN);
    int result = fd.ShowModal();
    wxString new_filename = fd.GetPath();
    if( result == wxID_CANCEL || new_filename == "" ) {
        return;
    }

    PictureName = new_filename;
    UpdateRenderedImage();

    mModified = true;
    NewPictureName = PictureName;
    ProcessNewImage();
}

void xlGridCanvasPictures::SaveAsImage()
{
    wxFileName save_file(PictureName);
    // prompt for new filename
    wxFileDialog fd(this,
                    "Choose filename to Save Image:",
                    save_file.GetPath(),
                    wxEmptyString,
                    wxFileSelectorDefaultWildcardStr,
                    wxFD_SAVE);
    int result = fd.ShowModal();
    wxString new_filename = fd.GetPath();
    if( result == wxID_CANCEL || new_filename == "" ) {
        return;
    }
    wxFileName file_check(new_filename);
    if( file_check.GetExt() == "" )
    {
        file_check.SetExt("png");
    }
    PictureName = file_check.GetFullPath();

     if( wxFile::Exists(PictureName)) {
        if( wxMessageBox("Are you sure you want to overwrite this image file?\n" + PictureName, "Confirm Overwrite?", wxICON_QUESTION | wxYES_NO) == wxYES )
        {
            SaveImageToFile();
        }
    }

    SaveImageToFile();
    mModified = true;
    NewPictureName = PictureName;
    ProcessNewImage();
}

void xlGridCanvasPictures::SaveImage()
{
    bool reload = false;
    wxFileName save_file(PictureName);
    if( save_file.GetFullName() == "NewImage.png" )
    {
        // prompt for new filename
        wxFileDialog fd(this,
                        "Choose filename to Save Image:",
                        save_file.GetPath(),
                        wxEmptyString,
                        wxFileSelectorDefaultWildcardStr,
                        wxFD_SAVE);
        int result = fd.ShowModal();
        wxString new_filename = fd.GetPath();
        if( result == wxID_CANCEL || new_filename == "" ) {
            return;
        }
        reload = true;
        wxFileName file_check(new_filename);
        if( file_check.GetExt() == "" )
        {
            file_check.SetExt("png");
        }
        PictureName = file_check.GetFullPath();
        SaveImageToFile();
    }

    if( wxFile::Exists(PictureName)) {
        if( wxMessageBox("Are you sure you want to overwrite this image file?\n" + PictureName, "Confirm Overwrite?", wxICON_QUESTION | wxYES_NO) == wxYES )
        {
            SaveImageToFile();
        }
    }

    if( reload ) {
        mModified = true;
        NewPictureName = PictureName;
        ProcessNewImage();
    }
}

void xlGridCanvasPictures::SaveImageToFile()
{
    image.SetOption("quality", 100);
    image.SaveFile(PictureName);
    UpdateRenderedImage();
}

void xlGridCanvasPictures::UpdateRenderedImage()
{
    wxString settings = mEffect->GetSettingsAsString();
    wxArrayString all_settings = wxSplit(settings, ',');
    for( int s = 0; s < all_settings.size(); s++ )
    {
        wxArrayString parts = wxSplit(all_settings[s], '=');
        int percent = wxAtoi(parts[1]);
        if( parts[0] == "E_FILEPICKER_Pictures_Filename" ) {
            parts[1] = PictureName;
        }
        all_settings[s] = wxJoin(parts, '=');
    }
    settings = wxJoin(all_settings, ',');
    mEffect->SetSettings(settings);

    wxCommandEvent eventEffectChanged(EVT_EFFECT_CHANGED);
    eventEffectChanged.SetClientData(mEffect);
    wxPostEvent(GetParent(), eventEffectChanged);
}

void xlGridCanvasPictures::CreateNewImage(wxString& image_dir)
{
    if( image_dir == wxEmptyString )
    {
        wxMessageBox("Error creating new image file.  Image Directory is not defined.");
        return;
    }
    wxFileName new_file;
    new_file.SetPath(image_dir);
    new_file.SetFullName("NewImage.png");
    NewPictureName = new_file.GetFullPath();
    if( wxFile::Exists(NewPictureName)) {
        ::wxRemoveFile(NewPictureName);
    }
    image.Create(mColumns, mRows, true);
    image.SaveFile(NewPictureName, wxBITMAP_TYPE_PNG);

    if (!image.IsOk())
    {
        wxMessageBox("Error creating image file!");
        return;
    }
    mModified = true;
    ProcessNewImage();
}

void xlGridCanvasPictures::ForceRefresh()
{
    NewPictureName = GetImageFilename();
    ProcessNewImage();
}

void xlGridCanvasPictures::SetEffect(Effect* effect_)
{
    mEffect = effect_;

    if( mEffect == NULL ) return;

    NewPictureName = GetImageFilename();

    if( NewPictureName == "" ) return;

    ProcessNewImage();
}

wxString xlGridCanvasPictures::GetImageFilename()
{
    wxString settings = mEffect->GetSettingsAsString();
    wxArrayString all_settings = wxSplit(settings, ',');
    for( int s = 0; s < all_settings.size(); s++ )
    {
        wxArrayString parts = wxSplit(all_settings[s], '=');
        if( parts[0] == "E_FILEPICKER_Pictures_Filename" ) {
            return parts[1];
        }

    }
    return wxEmptyString;
}

void xlGridCanvasPictures::mouseRightDown(wxMouseEvent& event)
{
    if( !mLeftDown )
    {
        mRightDown = true;
        mouseDown(event.GetX(), event.GetY());
    }
}

void xlGridCanvasPictures::mouseLeftDown(wxMouseEvent& event)
{
    if( !mRightDown )
    {
        mLeftDown = true;
        mouseDown(event.GetX(), event.GetY());
    }
}

void xlGridCanvasPictures::mouseDown(int x, int y)
{
    if( mEffect == NULL ) return;

    if( img_mode == IMAGE_SINGLE_FITS )
    {
        int column =  GetCellFromPosition(x);
        int row = GetCellFromPosition(y);
        if( column >= 0 && column < mColumns && row >= 0 && row < mRows )
        {
            int draw_row = mRows - row - 1;
            SetCurrentGLContext();
            if( mPaintMode == PAINT_PENCIL && !mRightDown ) {
                DrawGLUtils::UpdateTexturePixel(mImage->getID(), (double)column, (double)draw_row, mPaintColor, mImage->hasAlpha());
                image.SetRGB(column, row, mPaintColor.red, mPaintColor.green, mPaintColor.blue);
                if( mImage->hasAlpha() ) {
                    image.SetAlpha(column, row, mPaintColor.alpha);
                }
            } else if( mPaintMode == PAINT_ERASER || mRightDown ) {
                DrawGLUtils::UpdateTexturePixel(mImage->getID(), (double)column, (double)draw_row, mEraseColor, mImage->hasAlpha());
                image.SetRGB(column, row, mEraseColor.red, mEraseColor.green, mEraseColor.blue);
                if( mImage->hasAlpha() ) {
                    image.SetAlpha(column, row, mEraseColor.alpha);
                }
            } else if( mPaintMode == PAINT_EYEDROPPER && !mRightDown ) {
                xlColor eyedrop_color;
                eyedrop_color.red = image.GetRed(column, row);
                eyedrop_color.green = image.GetGreen(column, row);
                eyedrop_color.blue = image.GetBlue(column, row);
                wxCommandEvent eventEyedrop(EVT_EYEDROPPER_COLOR);
                eventEyedrop.SetClientData(&eyedrop_color);
                wxPostEvent(GetParent(), eventEyedrop);
            }
        }
        mModified = true;
        mDragging = true;
        CaptureMouse();
        Refresh(false);
    }
}

void xlGridCanvasPictures::mouseMoved(wxMouseEvent& event)
{
    if( mEffect == NULL ) return;

    int column =  GetCellFromPosition(event.GetX());
    int row = GetCellFromPosition(event.GetY());
    if( img_mode == IMAGE_SINGLE_FITS && column >= 0 && column < mColumns && row >= 0 && row < mRows )
    {
        if( mRightDown )
        {
            SetCursor(wxCURSOR_PAINT_BRUSH);
        }
        else
        {
            switch(mPaintMode)
            {
            case PAINT_PENCIL:
                SetCursor(wxCURSOR_PENCIL);
                break;
            case PAINT_ERASER:
                SetCursor(wxCURSOR_PAINT_BRUSH);
                break;
            case PAINT_EYEDROPPER:
                SetCursor(wxCURSOR_BULLSEYE);
                break;
            }
        }

        if( mDragging )
        {
            int draw_row = mRows - row - 1;
            SetCurrentGLContext();
            if( mPaintMode == PAINT_PENCIL && !mRightDown ) {
                DrawGLUtils::UpdateTexturePixel(mImage->getID(), (double)column, (double)draw_row, mPaintColor, mImage->hasAlpha());
                image.SetRGB(column, row, mPaintColor.red, mPaintColor.green, mPaintColor.blue);
                if( mImage->hasAlpha() ) {
                    image.SetAlpha(column, row, mPaintColor.alpha);
                }
            } else if( mPaintMode == PAINT_ERASER || mRightDown ) {
                DrawGLUtils::UpdateTexturePixel(mImage->getID(), (double)column, (double)draw_row, mEraseColor, mImage->hasAlpha());
                image.SetRGB(column, row, mEraseColor.red, mEraseColor.green, mEraseColor.blue);
                if( mImage->hasAlpha() ) {
                    image.SetAlpha(column, row, mEraseColor.alpha);
                }
            } else if( mPaintMode == PAINT_EYEDROPPER && !mRightDown ) {
                xlColor eyedrop_color;
                eyedrop_color.red = image.GetRed(column, row);
                eyedrop_color.green = image.GetGreen(column, row);
                eyedrop_color.blue = image.GetBlue(column, row);
                wxCommandEvent eventEyedrop(EVT_EYEDROPPER_COLOR);
                eventEyedrop.SetClientData(&eyedrop_color);
                wxPostEvent(GetParent(), eventEyedrop);
            }
            Refresh(false);
            Update();
        }
    }
    else
    {
        SetCursor(wxCURSOR_DEFAULT);
    }
}

void xlGridCanvasPictures::mouseLeftUp(wxMouseEvent& event)
{
    mouseUp();
}

void xlGridCanvasPictures::mouseRightUp(wxMouseEvent& event)
{
    mouseUp();
}

void xlGridCanvasPictures::mouseUp()
{
    if( mEffect == NULL ) return;
    if( mDragging )
    {
        ReleaseMouse();
        mDragging = false;
    }
    mRightDown = false;
    mLeftDown = false;
}

void xlGridCanvasPictures::InitializeGLCanvas()
{
    if(!IsShownOnScreen()) return;
    SetCurrentGLContext();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black Background
    glDisable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    prepare2DViewport(0,0,mWindowWidth, mWindowHeight);
    mIsInitialized = true;
}

void xlGridCanvasPictures::render( wxPaintEvent& event )
{
    if(!mIsInitialized) { InitializeGLCanvas(); }
    if(!IsShownOnScreen()) return;

    SetCurrentGLContext();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    wxPaintDC(this);
    if( mWindowResized )
    {
        prepare2DViewport(0,0,mWindowWidth, mWindowHeight);
    }

    if( mEffect != nullptr )
    {
        DrawPicturesEffect();
        DrawBaseGrid();
    }

    glFlush();
    SwapBuffers();
}

void xlGridCanvasPictures::DrawPicturesEffect()
{
    if( NewPictureName == "" ) return;
    if( NewPictureName != PictureName )
    {
        if( sprite != NULL ) {
            delete sprite;
        }
        if( use_ping )
        {
            imageGL_ping = new Image(NewPictureName);
            sprite = new xLightsDrawable(imageGL_ping);
            imageWidth = imageGL_ping->width;
            imageHeight = imageGL_ping->height;
            mImage = imageGL_ping;
        }
        else
        {
            imageGL_pong = new Image(NewPictureName);
            sprite = new xLightsDrawable(imageGL_pong);
            imageWidth = imageGL_pong->width;
            imageHeight = imageGL_pong->height;
            mImage = imageGL_pong;
        }
        sprite->setFlip(false, false);
    }
    scaleh= float(mCellSize*mRows) / float(imageHeight);
    scalew = float(mCellSize*mColumns) / float(imageWidth);
    sprite->scale(scalew, scaleh);
    sprite->setHotspot(-(float)mCellSize/scalew, -(float)mCellSize/scaleh);

    glPushMatrix();

    //glScalef(scalew, scaleh, 1.0);

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);   // textures
    sprite->render();
    glDisable(GL_TEXTURE_2D);   // textures
    glPopMatrix();

    if( NewPictureName != PictureName )
    {
        if( use_ping ) {
            if( imageGL_pong != NULL ) {
                delete imageGL_pong;
            }
            use_ping = false;
        } else {
            if( imageGL_ping != NULL ) {
                delete imageGL_ping;
            }
            use_ping = true;
        }
        PictureName = NewPictureName;
    }
}

