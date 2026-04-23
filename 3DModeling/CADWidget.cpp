#include "CADWidget.h"
#include <OpenGl_GraphicDriver.hxx>
#include <STEPControl_Reader.hxx>
#include <Xw_Window.hxx>
#include <X11/Xlib.h>

CADWidget::CADWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
}

void CADWidget::loadStep(const std::string &path)
{
    STEPControl_Reader controlReader;
    controlReader.ReadFile(path.c_str());
    controlReader.TransferRoots();

    TopoDS_Shape shape = controlReader.OneShape();
    displayShape(shape);
}

void CADWidget::paintEvent(QPaintEvent *paintEvent)
{
    view->Redraw();
}

void CADWidget::resizeEvent(QResizeEvent *resizeEvent)
{
    if (!view.IsNull())
    {
        view->MustBeResized();
    }
}

void CADWidget::showEvent(QShowEvent *)
{
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;

    Handle(Aspect_DisplayConnection) display = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(display);

    Handle(V3d_Viewer) viewer = new V3d_Viewer(driver);
    viewer->SetDefaultLights();
    viewer->SetLightOn();

    context = new AIS_InteractiveContext(viewer);
    view = viewer->CreateView();

    Handle(Xw_Window) xw =
        new Xw_Window(display, (Window)winId());

    view->SetWindow(xw);

    if (!xw->IsMapped())
        xw->Map();

    view->MustBeResized();
    view->Redraw();

    view->SetBackgroundColor(Quantity_NOC_WHITE);
    view->TriedronDisplay(Aspect_TOTP_RIGHT_LOWER, Quantity_NOC_BLACK, 0.08);

    isOCCTReady = true;
    for (auto &aisPendingShape : pendingShapes)
    {
        context->Display(aisPendingShape, true);
    }

    pendingShapes.clear();
    view->FitAll();
    view->ZFitAll();
}

void CADWidget::displayShape(const TopoDS_Shape &shape)
{
    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
    Quantity_Color lighBlueColor = Quantity_Color(0.4, 0.7, 1.0, Quantity_TOC_RGB);
    aisShape->SetColor(lighBlueColor);

    aisShape->SetMaterial(Graphic3d_NOM_PLASTIC);

    if (!isOCCTReady)
    {
        pendingShapes.push_back(aisShape);
        return;
    }

    context->Display(aisShape, true);
    view->FitAll();
}