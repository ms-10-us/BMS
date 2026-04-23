#ifndef CADWIDGET_H
#define CADWIDGET_H

#include <AIS_InteractiveContext.hxx>
#include <QWidget>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <vector>
#include <AIS_Shape.hxx>

class CADWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CADWidget(QWidget *parent = nullptr);

  void loadStep(const std::string &path);

  void displayShape(const TopoDS_Shape &shape);

protected:
  void paintEvent(QPaintEvent *paintEvent) override;

  void resizeEvent(QResizeEvent *resizeEvent) override;

  void showEvent(QShowEvent *event) override;

private:
  bool isOCCTReady = false;

  std::vector<Handle(AIS_Shape)> pendingShapes;

  Handle(V3d_View) view;

  Handle(AIS_InteractiveContext) context;
};

#endif