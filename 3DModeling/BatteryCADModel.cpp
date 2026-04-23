#include "BatteryCADModel.h"
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Compound.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <STEPControl_Writer.hxx>

BatteryCADModel::BatteryCADModel() = default;

void BatteryCADModel::generateBatteryCADModel(const std::string &path)
{
    BRep_Builder repBuilder;
    TopoDS_Compound batteryPack;
    repBuilder.MakeCompound(batteryPack);

    TopoDS_Shape enclosure = BRepPrimAPI_MakeBox(300, 200, 80).Shape();
    repBuilder.Add(batteryPack, enclosure);

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            gp_Trsf moveCursor;
            moveCursor.SetTranslation(gp_Vec(40 + x * 60, 40 + y * 50, 10));

            TopoDS_Shape batteryCell = BRepPrimAPI_MakeCylinder(10, 60).Shape();
            batteryCell = BRepBuilderAPI_Transform(batteryCell, moveCursor).Shape();
            repBuilder.Add(batteryPack, batteryCell);
        }
    }
    STEPControl_Writer writer;
    writer.Transfer(batteryPack, STEPControl_AsIs);
    writer.Write(path.c_str());
}