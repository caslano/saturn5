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
O7qw1FpC24m89uLgc9bsL0fbWNPm8Wo3ppVutLMT153uLg3LYzaQU/fKk1HnhNnTg5EVrrbP3h6sqHBg+VvfPVhZ4UrZt+5XsTIqSw3X9CK30nEcIByy0W9vLTGwLWmV+Tm3aWNIoTZY7yjztdv2YVFmlOMft29jV+l+TIgF7o136MYJkRjn63dmOIxz6PsO3oW+d9yri4oD7m89OCoA8zkCbvQQcJ22BPCPBa7zPh9+24fXb0rXwOvC/4V8MedpYjHm17sZdyCNH1aDqza1cc39pDJ2OnC4l1RwFzbrONNvCHdEW0wc9NbA7NtqYvBuCdJ7cwujZR84a5uJ07KPvvh9Ddfts4QybDexmL+VuU7F8LbqrN9rbZxev/Bf0nGok3ppafbhN2jhkDfYad1Qw3BlMM6XOzUa3RxQaEN17tkFumi3Vh+DDurY7m6sft/e4L/Sg1f9MQkG/OyNTDwrryleOcvfuAuvi8dZZQ9hpZ8WqgO+WtJGnTAb6/O/D0yn/h2xalsYwy++ut+IcufvZZEbO15kiXtF2AcI3zvV1933i9LLHMdafvzM8IRpq/Ccp25SbQ/C0HOivLSG52le4SNAMMAX7Pe6r2fuVXbo5hZtQ8j9eX6waLzZe03H515UFEVacTxVPPVN3Td0xNj3pEVQBNn1G1uzu/eP05lu+XckD3f8q9NnFwacxs57Iz9n9//c9UFQlPduuE8lrRhTZ4fk1D0zVyPQl/62idFblrhsLZZBW4D1tvRjZcKI17KtF3vfqbklpjgE9u3bu7HcDX3q3ML0Y4fN/LyjEyuvPoCLRjtx0nUeaY/coB8npiSM09duhF0eDFYM/ANv2Ivn4chE4Brk5cf9eLGDAZbibvRjZwfLq3MMiz1eP5bXrpLna/1YFplZ4iH7xbv78eaafs8bdWIRzRpnnD2dOHkrjby++SbdOPYgG9pDWe8u7+3Ea7Ek5m7aiZEhFVDuV+/rx8mXy6CTuVkvFmPhLtBnb4CdX2767f4NcfSs7Qyw67fsx6KPS+yt+rGIg6Tg/3CbPnx3H79823682W9ff7t+rNlvl2/fi+VVbOK9A3347n6+/w79+OW1leWlIeZU6nB9WIwJYC/1Y+tgG0qe33inbiyfevlsubi2XPtoQQd+SNUBSFsO/p3ZkvH9N184EMNEYJbv2sagModNGm+8O8NxMru1B/+pe9D3/vgdyMtnO3DmmWL2noT5L2J8ePcCrjeO2/57A9Mbv+8PElNWZHExmZEN90m6AqX+OVjmN6BK3nYd7sRiPULM0h4cqoTlEbbEbawZa+5SNwbVop3JjnRiZdVA5jOPCly7iyEIKuKuHOvFcsMT2OiMAdc17QJ3pR9HxVbyeLwXh6IjntSJfiwVHTKj8T4cTG3Q3w/ej2NXV+qOgO8X8Z1nAd8feH/2nY9QbXz8Qf8+5Uz69kk3mnLzaioolPh/D2C49eZ+VAzFpwxWhL5b7Dd3Nn5/fJI5fgwxmEf+hrM2D/zLtaQcpMQBvarvV5MiDqskjq53vypjmayr8rzYip3YLdOiO5QJtbAay+S+/IGikP+MzZC2XpH7SS2fpeVkYRR6sbOx4JIeL1KFztdfreYdob+Z5bejNIrtrFsu3WDXT/ZQAhRylSZqEhWelDb5v9NleVmWOUmU/FeFV0STTI/t8W9B/fMAzx+9scA8l8Vm+3ZE272HxhinFadz/qZfHf55Uvitz2s+acxbvN5OrlD41UXht3Z7ks+mBc8ufOnv/pgWn1xgiE9g7jzObURmpxcHqwvDqRVSfa/MwnSlxiy05fA+KHNwd6TVxignYILW8u7WmSbMUrhdyj0IowNq3nt38cLspa/cYtw=
*/