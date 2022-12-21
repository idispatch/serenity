/*
 * Copyright (c) 2022, Sahan Fernando <sahan.h.fernando@gmail.com>
 * Copyright (c) 2022, Stephan Unverwerth <s.unverwerth@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/DistinctNumeric.h>

namespace VirtGPU {

AK_TYPEDEF_DISTINCT_ORDERED_ID(u32, ObjectHandle);
AK_TYPEDEF_DISTINCT_ORDERED_ID(u32, ResourceID);

#define VIRGL_BIND_DEPTH_STENCIL (1 << 0)
#define VIRGL_BIND_RENDER_TARGET (1 << 1)
#define VIRGL_BIND_SAMPLER_VIEW (1 << 3)
#define VIRGL_BIND_VERTEX_BUFFER (1 << 4)
#define VIRGL_BIND_INDEX_BUFFER (1 << 5)
#define VIRGL_BIND_CONSTANT_BUFFER (1 << 6)
#define VIRGL_BIND_DISPLAY_TARGET (1 << 7)
#define VIRGL_BIND_COMMAND_ARGS (1 << 8)
#define VIRGL_BIND_STREAM_OUTPUT (1 << 11)
#define VIRGL_BIND_SHADER_BUFFER (1 << 14)
#define VIRGL_BIND_QUERY_BUFFER (1 << 15)
#define VIRGL_BIND_CURSOR (1 << 16)
#define VIRGL_BIND_CUSTOM (1 << 17)
#define VIRGL_BIND_SCANOUT (1 << 18)
#define VIRGL_BIND_STAGING (1 << 19)
#define VIRGL_BIND_SHARED (1 << 20)

namespace Protocol {

enum class TextureFormat : u32 {
    // RGBA Formats
    VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM = 1,
    VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM = 2,
    VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM = 3,
    VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM = 4,

    VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM = 67,
    VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM = 68,

    VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM = 121,
    VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM = 134,

    // Stencil-Depth Formats
    VIRTIO_GPU_FORMAT_Z16_UNORM = 16,
    VIRTIO_GPU_FORMAT_Z32_UNORM = 17,
    VIRTIO_GPU_FORMAT_Z32_FLOAT = 18,
    VIRTIO_GPU_FORMAT_Z24_UNORM_S8_UINT = 19,
    VIRTIO_GPU_FORMAT_S8_UINT_Z24_UNORM = 20,
    VIRTIO_GPU_FORMAT_Z24X8_UNORM = 21,
    VIRTIO_GPU_FORMAT_X8Z24_UNORM = 22,
    VIRTIO_GPU_FORMAT_S8_UINT = 23,
    VIRTIO_GPU_FORMAT_Z32_FLOAT_S8X24_UINT = 128,
    VIRTIO_GPU_FORMAT_X24S8_UINT = 136,
    VIRTIO_GPU_FORMAT_S8X24_UINT = 137,
    VIRTIO_GPU_FORMAT_X32_S8X24_UINT = 138,

};

enum class VirGLCommand : u32 {
    NOP = 0,
    CREATE_OBJECT = 1,
    BIND_OBJECT,
    DESTROY_OBJECT,
    SET_VIEWPORT_STATE,
    SET_FRAMEBUFFER_STATE,
    SET_VERTEX_BUFFERS,
    CLEAR,
    DRAW_VBO,
    RESOURCE_INLINE_WRITE,
    SET_SAMPLER_VIEWS,
    SET_INDEX_BUFFER,
    SET_CONSTANT_BUFFER,
    SET_STENCIL_REF,
    SET_BLEND_COLOR,
    SET_SCISSOR_STATE,
    BLIT,
    RESOURCE_COPY_REGION,
    BIND_SAMPLER_STATES,
    BEGIN_QUERY,
    END_QUERY,
    GET_QUERY_RESULT,
    SET_POLYGON_STIPPLE,
    SET_CLIP_STATE,
    SET_SAMPLE_MASK,
    SET_STREAMOUT_TARGETS,
    SET_RENDER_CONDITION,
    SET_UNIFORM_BUFFER,

    SET_SUB_CTX,
    CREATE_SUB_CTX,
    DESTROY_SUB_CTX,
    BIND_SHADER,
    SET_TESS_STATE,
    SET_MIN_SAMPLES,
    SET_SHADER_BUFFERS,
    SET_SHADER_IMAGES,
    MEMORY_BARRIER,
    LAUNCH_GRID,
    SET_FRAMEBUFFER_STATE_NO_ATTACH,
    TEXTURE_BARRIER,
    SET_ATOMIC_BUFFERS,
    SET_DBG_FLAGS,
    GET_QUERY_RESULT_QBO,
    TRANSFER3D,
    END_TRANSFERS,
    COPY_TRANSFER3D,
    SET_TWEAKS,
    CLEAR_TEXTURE,
    PIPE_RESOURCE_CREATE,
    PIPE_RESOURCE_SET_TYPE,
    GET_MEMORY_INFO,
    SEND_STRING_MARKER,
    MAX_COMMANDS
};

union ClearType {
    struct {
        u32 depth : 1;
        u32 stencil : 1;
        u32 color0 : 1;
        u32 color1 : 1;
        u32 color2 : 1;
        u32 color3 : 1;
        u32 color4 : 1;
        u32 color5 : 1;
        u32 color6 : 1;
        u32 color7 : 1;
    } flags;
    u32 value;
};

enum class ObjectType : u32 {
    NONE,
    BLEND,
    RASTERIZER,
    DSA,
    SHADER,
    VERTEX_ELEMENTS,
    SAMPLER_VIEW,
    SAMPLER_STATE,
    SURFACE,
    QUERY,
    STREAMOUT_TARGET,
    MSAA_SURFACE,
    MAX_OBJECTS,
};

enum class PipeTextureTarget : u32 {
    BUFFER = 0,
    TEXTURE_1D,
    TEXTURE_2D,
    TEXTURE_3D,
    TEXTURE_CUBE,
    TEXTURE_RECT,
    TEXTURE_1D_ARRAY,
    TEXTURE_2D_ARRAY,
    TEXTURE_CUBE_ARRAY,
    MAX
};

enum class PipePrimitiveTypes : u32 {
    POINTS = 0,
    LINES,
    LINE_LOOP,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    QUADS,
    QUAD_STRIP,
    POLYGON,
    LINES_ADJACENCY,
    LINE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY,
    TRIANGLE_STRIP_ADJACENCY,
    PATCHES,
    MAX
};

}

namespace Gallium {

enum class PipeTextureTarget : u32 {
    BUFFER,
    TEXTURE_1D,
    TEXTURE_2D,
    TEXTURE_3D,
    TEXTURE_CUBE,
    TEXTURE_RECT,
    TEXTURE_1D_ARRAY,
    TEXTURE_2D_ARRAY,
    TEXTURE_CUBE_ARRAY,
    MAX_TEXTURE_TYPES,
};

enum class ShaderType : u32 {
    SHADER_VERTEX = 0,
    SHADER_FRAGMENT,
    SHADER_GEOMETRY,
    SHADER_TESS_CTRL,
    SHADER_TESS_EVAL,
    SHADER_COMPUTE,
    SHADER_TYPES
};

}

}
