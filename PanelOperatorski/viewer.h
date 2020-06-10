#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include <vector>
#include <glm.hpp>

/*! \class Viewer
    \brief Klasa odpowiedzialna za wyświetlanie modelu manipulatora.
*/

class Viewer :  public QGLViewer
{
 public:
  Viewer(QWidget *pParent = nullptr): QGLViewer(pParent) {}
 protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;

  void drawNode(const std::vector<glm::vec3> & vertices, const std::vector<glm::vec2> & uvs, const std::vector<glm::vec3> & normals);
 private:
  /*!
   * \var m0_vertices
   * \brief m0_vertices - przechowuje współrzędne wierzchołka pierwszego modelu.
   */
  std::vector<glm::vec3> m0_vertices;
  /*!
   * \var m0_uvs
   * \brief m0_uvs - przechowuje współrzędne tekstur pierwszego modelu.
   */
  std::vector<glm::vec2> m0_uvs;
  /*!
   * \var m0_normal
   * \brief m0_normal - przechowuje wektory normalne pierwszego modelu.
   */
  std::vector<glm::vec3> m0_normal;

  std::vector<glm::vec3> m1_vertices;
  std::vector<glm::vec2> m1_uvs;
  std::vector<glm::vec3> m1_normal;

  std::vector<glm::vec3> m2_vertices;
  std::vector<glm::vec2> m2_uvs;
  std::vector<glm::vec3> m2_normal;

  std::vector<glm::vec3> m3_vertices;
  std::vector<glm::vec2> m3_uvs;
  std::vector<glm::vec3> m3_normal;

};

#endif // VIEWER_H
