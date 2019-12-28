#include <3rd_assignment.h>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>

// https://stackoverflow.com/questions/45477806/general-method-for-calculating-smooth-vertex-normals-with-100-smoothness
void calc_mesh_normals(glm::vec3 * normals,           //
                       glm::vec3 const * const verts, //
                       int const * const faces,       //
                       int const nverts,              //
                       int const nfaces)
{
    std::vector<std::vector<glm::vec3>> weighted_normals(nverts);

    for (int i = 0; i < nfaces; i += 3) {
        glm::vec3 const p1 = verts[faces[i]];
        glm::vec3 const p2 = verts[faces[i + 1]];
        glm::vec3 const p3 = verts[faces[i + 2]];

        glm::vec3 n = glm::cross(p2 - p1, p3 - p1);
        n = glm::normalize(n);

        float const angle1 = glm::angle(p2 - p1, p3 - p1);
        float const angle2 = glm::angle(p3 - p2, p1 - p2);
        float const angle3 = glm::angle(p1 - p3, p2 - p3);

        weighted_normals[faces[i]].push_back(n * angle1);
        weighted_normals[faces[i + 1]].push_back(n * angle2);
        weighted_normals[faces[i + 2]].push_back(n * angle3);
    }

    for (int i = 0; i < nverts; ++i) {
        auto const & weighted_normal = weighted_normals[i];
        glm::vec3 target_normal;

        for (glm::vec3 const & n : weighted_normal) {
            target_normal += n;
        }

        normals[i] = glm::normalize(target_normal);
    }
}
