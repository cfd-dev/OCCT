// OpenCASCADE�ͱ�׼��ͷ�ļ�
#include <iostream>                        // �����������
#include <Standard_Version.hxx>            // OpenCASCADE�汾��Ϣ
#include <vtkVersion.h>                    // VTK�汾��Ϣ
#include <gp_Circ.hxx>                     // ���λ���Բ����
#include <Geom_Circle.hxx>                 // ����Բ���߶���
#include <GeomAPI_ProjectPointOnCurve.hxx> // ��ͶӰ������API
#include <BRepBuilderAPI_MakeVertex.hxx>   // ���㴴��API
#include <BRepBuilderAPI_MakeEdge.hxx>     // �ߴ���API
#include <TopoDS_Shape.hxx>                // �������ݽṹ����
#include <V3d_Viewer.hxx>                  // 3D�鿴��
#include <AIS_InteractiveContext.hxx>      // ����������
#include <WNT_Window.hxx>                  // Windows���ش���
#include <windows.h>                       // Windows API
#include <OpenGl_GraphicDriver.hxx>        // OpenGLͼ������
#include <TopoDS_Edge.hxx>                 // ���˱߽ṹ
#include <AIS_Shape.hxx>                   // ����ʽ��״
#include <V3d_View.hxx>                    // 3D��ͼ

int main()
{
    // �����汾��Ϣ
    std::cout << "OpenCASCADE Version: "
              << OCC_VERSION_MAJOR << "."
              << OCC_VERSION_MINOR << "."
              << OCC_VERSION_MAINTENANCE
              << std::endl;
    std::cout << "VTK Version: "
              << vtkVersion::GetVTKMajorVersion() << "."
              << vtkVersion::GetVTKMinorVersion() << "."
              << vtkVersion::GetVTKBuildVersion()
              << std::endl;

    // ��������Բ��XYƽ�棬�뾶50��
    gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));            // ��������ϵ��ԭ�㣬Z�᷽��
    gp_Circ circle(axis, 50.0);                               // ����������Բ
    circle.SetLocation(gp_Pnt(0, 0, 0));                      // ����Բ��λ��
    Handle(Geom_Circle) geomCircle = new Geom_Circle(circle); // ת��Ϊ��������

    // �������Ե�
    gp_Pnt point1(20, 40, 0); // ԭʼ��1����Բ�ڲ���
    gp_Pnt point2(60, 0, 0);  // ԭʼ��2����Բ�ⲿ��
    std::cout << "Point 1: "
              << point1.X() << ", "
              << point1.Y() << ", "
              << point1.Z() << std::endl;
    std::cout << "Point 2: "
              << point2.X() << ", "
              << point2.Y() << ", "
              << point2.Z() << std::endl;

    // ��ʼ��ͶӰ��
    GeomAPI_ProjectPointOnCurve projector;

    // ͶӰ��һ����
    projector.Init(point1, geomCircle); // ����ͶӰĿ�������
    if (projector.NbPoints() < 1)       // ���ͶӰ���
    {
        std::cerr << "Error projecting point1" << std::endl;
        return 1;
    }
    gp_Pnt projectedPoint1 = projector.NearestPoint();                // ��ȡ���ͶӰ��
    Standard_Real dist1 = projector.LowerDistance();                  // �������
    Standard_Real parameter1 = projector.Parameter(1);                // ��ȡͶӰ��Ĳ���ֵ
    std::cout << "Parameter of Point 1: " << parameter1 << std::endl; // �������ֵ
    gp_Pnt pointOnCircle1 = geomCircle->Value(parameter1);            // ��ȡ������Ӧ�ĵ㣬Ӧ����projectedPoint1��ͬ
    std::cout << "Point on Circle: "
              << pointOnCircle1.X() << ", "
              << pointOnCircle1.Y() << ", "
              << pointOnCircle1.Z() << std::endl;

    std::cout << "Projected Point 1: "
              << projectedPoint1.X() << ", "
              << projectedPoint1.Y() << ", "
              << projectedPoint1.Z() << std::endl;

    std::cout << "Distance to Point 1: "
              << dist1 << std::endl;

    // ͶӰ�ڶ�����
    projector.Init(point2, geomCircle);
    if (projector.NbPoints() < 1)
    {
        std::cerr << "Error projecting point2" << std::endl;
        return 1;
    }
    gp_Pnt projectedPoint2 = projector.NearestPoint();                // ��ȡ���ͶӰ��
    Standard_Real dist2 = projector.LowerDistance();                  // �������
    Standard_Real parameter2 = projector.Parameter(1);                // ��ȡͶӰ��Ĳ���ֵ
    std::cout << "Parameter of Point 2: " << parameter2 << std::endl; // �������ֵ
    gp_Pnt pointOnCircle2 = geomCircle->Value(parameter2);            // ��ȡ������Ӧ�ĵ㣬Ӧ����projectedPoint2��ͬ
    std::cout << "Point on Circle: "
              << pointOnCircle2.X() << ", "
              << pointOnCircle2.Y() << ", "
              << pointOnCircle2.Z() << std::endl;

    std::cout << "Projected Point 2: "
              << projectedPoint2.X() << ", "
              << projectedPoint2.Y() << ", "
              << projectedPoint2.Z() << std::endl;

    std::cout << "Distance to Point 2: "
              << dist2 << std::endl;

    // ��ʼ�����ӻ�ϵͳ
    Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(NULL); // OpenGL����
    Handle(V3d_Viewer) viewer = new V3d_Viewer(graphicDriver);                   // 3D�鿴��
    Handle(AIS_InteractiveContext) context = new AIS_InteractiveContext(viewer); // ����������

    // ��������ʾԲ��
    TopoDS_Edge circleEdge = BRepBuilderAPI_MakeEdge(geomCircle);      // �������˱�
    Handle(AIS_Shape) aisCircle = new AIS_Shape(circleEdge);           // ��������ʽ��״
    context->SetColor(aisCircle, Quantity_NOC_YELLOW, Standard_False); // ���û�ɫ
    context->Display(aisCircle, Standard_True);                        // ��ʾ��״

    // �����������˽ṹ
    TopoDS_Vertex vertex1 = BRepBuilderAPI_MakeVertex(point1);            // ԭʼ��1����
    TopoDS_Vertex vertex2 = BRepBuilderAPI_MakeVertex(point2);            // ԭʼ��2����
    TopoDS_Vertex projVert1 = BRepBuilderAPI_MakeVertex(projectedPoint1); // ͶӰ��1
    TopoDS_Vertex projVert2 = BRepBuilderAPI_MakeVertex(projectedPoint2); // ͶӰ��2

    // ��ʾԭʼ�㣨��ɫ��
    Handle(AIS_Shape) aisPoint1 = new AIS_Shape(vertex1);
    Handle(AIS_Shape) aisPoint2 = new AIS_Shape(vertex2);
    context->SetColor(aisPoint1, Quantity_NOC_RED, Standard_False); // ���ú�ɫ
    context->SetColor(aisPoint2, Quantity_NOC_RED, Standard_False);
    context->Display(aisPoint1, Standard_True); // ��ʾ��1
    context->Display(aisPoint2, Standard_True); // ��ʾ��2

    // ��ʾͶӰ�㣨��ɫ��
    Handle(AIS_Shape) aisProj1 = new AIS_Shape(projVert1);
    Handle(AIS_Shape) aisProj2 = new AIS_Shape(projVert2);
    context->SetColor(aisProj1, Quantity_NOC_GREEN, Standard_False); // ������ɫ
    context->SetColor(aisProj2, Quantity_NOC_GREEN, Standard_False);
    context->Display(aisProj1, Standard_True); // ��ʾͶӰ��1
    context->Display(aisProj2, Standard_True); // ��ʾͶӰ��2

    // ����������3D��ͼ
    HWND hwnd = GetConsoleWindow(); // ��ȡ����̨���ھ��
    if (hwnd == NULL)
    {
        std::cerr << "Error: Could not get console window" << std::endl;
        return 1;
    }
    Handle(WNT_Window) window = new WNT_Window(hwnd); // ����Windows����
    Handle(V3d_View) view = viewer->CreateView();     // ����3D��ͼ
    view->SetWindow(window);                          // ��������
    view->SetProj(V3d_YnegZpos);                      // X��������Z�Ḻ����
    view->SetTwist(0.0);                              // ������ͼ��ת
    if (!window->IsMapped())                          // ��鴰��ӳ��״̬
    {
        window->Map(); // ӳ�䴰�ڵ���Ļ
    }
    view->FitAll(); // �Զ�������ͼ
    view->Redraw(); // �ػ���ͼ

    // ���ֳ�������
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore(); // �ȴ��û�����
    return 0;
}
