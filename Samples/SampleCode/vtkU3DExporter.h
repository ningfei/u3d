// .NAME vtU3DExporter - create an u3d/idtf/pdf file
// .SECTION Description
// vtkU3DExporter is a render window exporter which writes out the renderered
// scene into an U3D file. U3D is an open format for 3D models that can be embedded
// into PDF files and diplayed by Adobe viewers. IDTF is a text format (similar to VRML)
// for representation 3D scenes that can be converted to U3D.
// .SECTION Thanks
// U3DExporter is contributed by Michail Vidiassov.
#ifndef __vtkU3DExporter_h
#define __vtkU3DExporter_h

#include "vtkExporter.h"

class vtkLight;
class vtkActor;
class vtkActor2D;
class vtkPoints;
class vtkDataArray;
class vtkUnsignedCharArray;
class vtkRenderer;

class VTK_HYBRID_EXPORT vtkU3DExporter : public vtkExporter
{
public:
  static vtkU3DExporter *New();
  vtkTypeRevisionMacro(vtkU3DExporter,vtkExporter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/Get the output file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Specify if compression of meshes is enabled 
  vtkSetClampMacro(MeshCompression, int, 0, 1);
  vtkBooleanMacro(MeshCompression, int);
  vtkGetMacro(MeshCompression, int);

protected:
  vtkU3DExporter();
  ~vtkU3DExporter();

  // Description:
  // Write data to output.
  void WriteData();

  char *FileName;
  int MeshCompression;

};

#endif
