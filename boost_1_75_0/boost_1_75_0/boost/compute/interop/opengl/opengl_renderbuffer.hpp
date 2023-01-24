//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_RENDERBUFFER_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_RENDERBUFFER_HPP

#include <boost/compute/image/image_object.hpp>
#include <boost/compute/interop/opengl/gl.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

/// \class opengl_renderbuffer
///
/// A OpenCL buffer for accessing an OpenGL renderbuffer object.
class opengl_renderbuffer : public image_object
{
public:
    /// Creates a null OpenGL renderbuffer object.
    opengl_renderbuffer()
        : image_object()
    {
    }

    /// Creates a new OpenGL renderbuffer object for \p mem.
    explicit opengl_renderbuffer(cl_mem mem, bool retain = true)
        : image_object(mem, retain)
    {
    }

    /// Creates a new OpenGL renderbuffer object in \p context for
    /// \p renderbuffer with \p flags.
    ///
    /// \see_opencl_ref{clCreateFromGLRenderbuffer}
    opengl_renderbuffer(const context &context,
                        GLuint renderbuffer,
                        cl_mem_flags flags = read_write)
    {
        cl_int error = 0;

        m_mem = clCreateFromGLRenderbuffer(
            context, flags, renderbuffer, &error
        );

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new OpenGL renderbuffer object as a copy of \p other.
    opengl_renderbuffer(const opengl_renderbuffer &other)
        : image_object(other)
    {
    }

    /// Copies the OpenGL renderbuffer object from \p other.
    opengl_renderbuffer& operator=(const opengl_renderbuffer &other)
    {
        if(this != &other){
            image_object::operator=(other);
        }

        return *this;
    }

    /// Destroys the OpenGL buffer object.
    ~opengl_renderbuffer()
    {
    }

    /// Returns the size (width, height) of the renderbuffer.
    extents<2> size() const
    {
        extents<2> size;
        size[0] = get_image_info<size_t>(CL_IMAGE_WIDTH);
        size[1] = get_image_info<size_t>(CL_IMAGE_HEIGHT);
        return size;
    }

    /// Returns the origin of the renderbuffer (\c 0, \c 0).
    extents<2> origin() const
    {
        return extents<2>();
    }

    /// Returns the OpenGL memory object ID.
    ///
    /// \see_opencl_ref{clGetGLObjectInfo}
    GLuint get_opengl_object() const
    {
        GLuint object = 0;
        clGetGLObjectInfo(m_mem, 0, &object);
        return object;
    }

    /// Returns the OpenGL memory object type.
    ///
    /// \see_opencl_ref{clGetGLObjectInfo}
    cl_gl_object_type get_opengl_type() const
    {
        cl_gl_object_type type;
        clGetGLObjectInfo(m_mem, &type, 0);
        return type;
    }
};

namespace detail {

// set_kernel_arg() specialization for opengl_renderbuffer
template<>
struct set_kernel_arg<opengl_renderbuffer> : public set_kernel_arg<image_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::opengl_renderbuffer, image2d_t)

#endif // BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_RENDERBUFFER_HPP

/* opengl_renderbuffer.hpp
EXLGH236HNrz2oTc+eD37eT3dKOrHO0dnsd6Zbcvv258tMG5rfgtdbAdQhg+jaM3RJxgaa4TQoTAobcSy6fw+mY0mS9G7mp0LzLW4QydlpLkgQS6nF6IcwzKHhpteyk4mT3sH5aw03Z5L7XBuLrgllG5pS8R11tSgbQzyi6Sy7dEkX1DaPP0Y0OmnY3I+51bDEbx3h3/+PVvGmI//h3tu3Sq1uCW2XdpSdkzKEjWL70ETZuVz1t7VV9EGRqYn+wzX9Kd/RXYQEyHuNlB9zLtfMObjG8bn5siJ5aJgueC49S5edPbDc616wcr72uJxGv/l4Pz8Kf6/6N4mWWWnR1l69rKuqmQEdnbtWVLtuveuIkISVa6iKzMbkaE65Kyr52Vfe1x3XuNy73Xz/f3L3wen/frdc7zfc77bG4DPV+geoPJq23+/dfIwNjAIgqXIsPiEc3D6zFBeuTR/vxUXM/9A5oCj+beAYFPHqADU8/iYsQTAr4o3NnYWG5HF6JgbiVr/YVjHXrAZ26PNSrZt+ebGx/0BAbv6gUhUtopMJ23VxjXfDJDXL6eWyXfeLURdvrmQbu2qX2hrQHo8o8++u6bHsH5mxxoZgfTmxU5KVGtQrulIK2YdqG2FHi3xtsRk5lbZDZSjvwbzvprghwtNzwHxwt+idR/pZIrWO0Bkbbw+gxE4RIRvgspXfuM4/Y17Se6h8mpUTti7Ba/YWAb
*/