#pragma once

#include <glm/fwd.hpp>

// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//
void calc_mesh_normals(glm::vec3 * normals,     //
                       glm::vec3 const * verts, //
                       int const * faces,       //
                       int nverts,              //
                       int nfaces);
