#include <3rd_assignment.h>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

void calc_mesh_normals(glm::vec3 * normals,           //
                       glm::vec3 const * const verts, //
                       int const * const faces,       //
                       int const nverts,              //
                       int const nfaces)
{
    for (int i = 0; i < nfaces; i += 3) {
        glm::vec3 const p1 = verts[faces[i]];
        glm::vec3 const p2 = verts[faces[i + 1]];
        glm::vec3 const p3 = verts[faces[i + 2]];

        glm::vec3 n = glm::cross(p2 - p1, p3 - p1);
        n = glm::normalize(n);

        float const angle1 = glm::angle(p2 - p1, p3 - p1);
        float const angle2 = glm::angle(p3 - p2, p1 - p2);
        float const angle3 = glm::angle(p1 - p3, p2 - p3);

        normals[faces[i]] += n * angle1;
        normals[faces[i + 1]] += n * angle2;
        normals[faces[i + 2]] += n * angle3;
    }

    for (int i = 0; i < nverts; ++i) {
        normals[i] = glm::normalize(normals[i]);
    }
}
