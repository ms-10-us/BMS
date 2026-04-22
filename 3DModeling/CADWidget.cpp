#include "CADWidget.h"
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_Shape.hxx>
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
    controlReader.TransferRoot();
    TopoDS_Shape shape = controlReader.OneShape();

    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
    context->Display(aisShape, true);

    view->FitAll();
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

    view->SetBackgroundColor(Quantity_NOC_BLACK);
    view->MustBeResized();
}