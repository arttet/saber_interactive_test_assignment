#include <gtest/gtest.h>

#include <3rd_assignment.h>

#include <glm/glm.hpp>

namespace
{
    bool load_obj(char const * const path,           //
                  std::vector<glm::vec3> & vertices, //
                  std::vector<int> & faces)
    {
        FILE * file = std::fopen(path, "r");
        if (!file) {
            return false;
        }

        char line_header[128] = { '\0' };

        while (true) {

            int const res = std::fscanf(file, "%s", line_header);
            if (res == EOF)
                break;

            if (strcmp(line_header, "v") == 0) {
                glm::vec3 vertex;
                std::fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                vertices.push_back(vertex);
            } else if (strcmp(line_header, "f") == 0) {
                int vertex_index[3];
                int uv_index[3];
                int normal_index[3];
                int const matches = std::fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",             //
                                                &vertex_index[0], &uv_index[0], &normal_index[0], //
                                                &vertex_index[1], &uv_index[1], &normal_index[1], //
                                                &vertex_index[2], &uv_index[2], &normal_index[2]);
                if (matches != 9) {
                    return false;
                }

                faces.push_back(vertex_index[0] - 1);
                faces.push_back(vertex_index[1] - 1);
                faces.push_back(vertex_index[2] - 1);
            }
        }

        return true;
    }
}

struct test_normals_t : testing::TestWithParam<char const *>
{
};

TEST_P(test_normals_t, obj_file)
{
    char const * const path = GetParam();
    std::vector<glm::vec3> vertices;
    std::vector<int> faces;

    bool const ok = load_obj(path, vertices, faces);
    EXPECT_TRUE(ok);

    std::vector<glm::vec3> actual_normals(vertices.size());
    calc_mesh_normals(actual_normals.data(), //
                      vertices.data(),       //
                      faces.data(),          //
                      vertices.size(),       //
                      faces.size());         //
}

// clang-format off

INSTANTIATE_TEST_CASE_P(test, test_normals_t, testing::Values(
    "cube.obj"
));

// clang-format on

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
