#include "viewer.h"
#include "manipulator.h"

#include "LoadOBJ.h"

#include <QKeyEvent>
#include <QDebug>

/*!
 * \brief Viewer::drawNode() - Rysuje model.
 * \param vertices - std::vector<> przechowującu współrzędne wierzchołków.
 * \param uvs - std::vector<> przechowujący infotmację na temat współrzędnych teksury.
 * \param normals - std::vector<> przechowujący wektory normalne wierzchołków
 */
void Viewer::drawNode(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uvs, const std::vector<glm::vec3> &normals)
{
  glBegin(GL_TRIANGLES);
    for(int i =0; i< vertices.size()/3; ++i)
    {
        glTexCoord2f(uvs[3*i].x, uvs[3*i].y);
        glNormal3f(normals[3*i].x, normals[3*i].y, normals[3*i].z);
        glVertex3f(vertices[3*i].x, vertices[3*i].y, vertices[3*i].z);
        glTexCoord2f(uvs[i*3 + 1].x, uvs[i*3 + 1].y);
        glNormal3f(normals[3*i+1].x, normals[3*i+1].y, normals[3*i+1].z);
        glVertex3f(vertices[i*3 + 1].x, vertices[i*3 + 1].y, vertices[i*3 + 1].z);
        glTexCoord2f(uvs[i*3 + 2].x, uvs[i*3 + 2].y);
        glNormal3f(normals[3*i+2].x, normals[3*i+2].y, normals[3*i+2].z);
        glVertex3f(vertices[i*3 + 2].x, vertices[i*3 + 2].y, vertices[i*3 + 2].z);
    }
  glEnd();
}

/*!
 * \brief Viewer::draw() - Funkcja opowiedzialna za rysowanie sceny.
 */
void Viewer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Draw Grid (Rotate so it displays poperly)
    glRotatef(90, 1.0, 0.0, 0.0);
    drawGrid(100, 100);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //Draw base
    drawNode(m0_vertices, m0_uvs, m0_normal);

    //Draw first link
    glTranslatef(0.0, 1.5, 0.0);
    glRotatef( Manip.GetQ0_deg(), 0.0, 1.0, 0.0 );
    drawNode(m1_vertices, m1_uvs, m1_normal);

    //Draw second link
    glTranslatef(0.0, 1, 0.0);
    glRotatef( -Manip.GetQ1_deg(), 1.0, 0.0, 0.0 );
    drawNode(m2_vertices, m2_uvs, m2_normal);

    //Draw third link
    glTranslatef(0.0, 3.7, 0.0);
    glRotatef( 90, 1.0, 0.0, 0.0 );
    glRotatef( -Manip.GetQ2_deg(), 1.0, 0.0, 0.0 );
    drawNode(m3_vertices, m3_uvs, m3_normal);

}

/*!
 * \brief Viewer::init() - funckja inicjalizująca scene.
 */
void Viewer::init()
{
    //Load model
    loadOBJ("C:\\Users\\sliwa\\Desktop\\wds\\Model\\podstawa.obj", m0_vertices, m0_uvs, m0_normal);
    loadOBJ("C:\\Users\\sliwa\\Desktop\\wds\\Model\\og_1.obj", m1_vertices, m1_uvs, m1_normal);
    loadOBJ("C:\\Users\\sliwa\\Desktop\\wds\\Model\\og_2.obj", m2_vertices, m2_uvs, m2_normal);
    loadOBJ("C:\\Users\\sliwa\\Desktop\\wds\\Model\\og_3.obj", m3_vertices, m3_uvs, m3_normal);

    // Restore previous viewer state.
    restoreStateFromFile();

    //Set scene properties
    setSceneCenter(qglviewer::Vec(0,0,0));
    setSceneRadius(100);

    this->camera()->setPosition(qglviewer::Vec(-10.65, 9.27, -3.17));
    this->camera()->lookAt(qglviewer::Vec(3,0,3));

    glClearColor (0.2, 0.2, 0.2, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

/*!
 * \brief Viewer::helpString() - domyślna funkcja wyświetlająca pomoc. (Nieużywana)
 * \return tekst wiadomości.
 */
QString Viewer::helpString() const
{
  QString text("<h2>S i m p l e V i e w e r</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}
