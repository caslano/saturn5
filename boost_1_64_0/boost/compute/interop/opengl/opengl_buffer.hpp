//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_BUFFER_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_BUFFER_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/interop/opengl/gl.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>

namespace boost {
namespace compute {

/// \class opengl_buffer
///
/// A OpenCL buffer for accessing an OpenGL memory object.
class opengl_buffer : public buffer
{
public:
    /// Creates a null OpenGL buffer object.
    opengl_buffer()
        : buffer()
    {
    }

    /// Creates a new OpenGL buffer object for \p mem.
    explicit opengl_buffer(cl_mem mem, bool retain = true)
        : buffer(mem, retain)
    {
    }

    /// Creates a new OpenGL buffer object in \p context for \p bufobj
    /// with \p flags.
    ///
    /// \see_opencl_ref{clCreateFromGLBuffer}
    opengl_buffer(const context &context,
                  GLuint bufobj,
                  cl_mem_flags flags = read_write)
    {
        cl_int error = 0;
        m_mem = clCreateFromGLBuffer(context, flags, bufobj, &error);
        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new OpenGL buffer object as a copy of \p other.
    opengl_buffer(const opengl_buffer &other)
        : buffer(other)
    {
    }

    /// Copies the OpenGL buffer object from \p other.
    opengl_buffer& operator=(const opengl_buffer &other)
    {
        if(this != &other){
            buffer::operator=(other);
        }

        return *this;
    }

    /// Destroys the OpenGL buffer object.
    ~opengl_buffer()
    {
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

// set_kernel_arg specialization for opengl_buffer
template<>
struct set_kernel_arg<opengl_buffer> : set_kernel_arg<memory_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_BUFFER_HPP

/* opengl_buffer.hpp
yP0eqOEuUp/OvVY5x3c/SNCxFiqDJMgVG3Q+9qD3t5l0cY7jDm3Sq/FADjqTLibHw+Q9gNPZGps9ixhjPJeV/A6RPu44mx4maHIWidhTwvwYfd+7U+Jo+ARmoL53Hkl0nDFs/JRx2Q2auj5q+qNAV/pWt/3jPZzeO8f3j4WlpVexUa3pNx+j0vGz1TrdxxId55bO2+sfB5rJG3LSgg7e6jEffzyj05is9Clqcb/2hXgC/67HO5rCTRi4z7ficLvFHe2dT2zH0c0WmLn9LRgjz+26J7VgDF+HnwmMccxrtnWXn9yOMWNInX4KcPXwGTZzBw60YebJdolHw6zfaG044+3/+qe2YIwx2P20Fkw1lLWuqw1j+N+Br6e3Yon5GjOcaMHgnSXuv79V7wSJGxZxkkQWNarfN0IVV1qRk+R5kFq66Kwqslbqo679hpXRIeIkxP7/M/p7+piOkRak8Jte28SYd99Pt2Hqu6+I4dHEqHffr7bQzbvv3vUMg30DOA2zgTBYvxoG+8dvGAZv/1MvKisHAi4jezutBaIU7lQ5XeQ+6Up1OegVhT4V5d2UIFMll6MB875WDESBvJ0PKRhGjTyd/pkGH7wN0L9c06vM4ob+79n0hs/9U1OuTb2bKpNIyDO/YpQz2/1mgy+93e+b5Q195eZdUu4YdTuizR806kQZTv9Ro6+cJ4znT1vHk9eB/j7H6K/tduq5xd4RY9pocOOZjh77xMTIkwW2/DfGGKZM3P+Sdt2xXX1VvOwqoIiouFFRcSNQqLNv7yUFtyml/WKrpa39tlqNicQVjXtrYqKJJm7FFfdeuHFvxY1RIxr/0ESj59537+fde997VTS/tL/yzuecu9e555w7eWIqnpw8Te+B2IU3NUlaYzujYJ/km6/dKz56K8NjnQEA42+bRp9bXSUvorPzS+pa9u3tKoZnG/K3jrZo7Jla0P8KOp/1kQHsT24IOtU5yEj7DztVup72bXbrNDPtXTfS6Fik4XsDOtIF78Ie0LQ6gY/oTQQd93oQARujf+wFhucbNl378B15xt70ZqCJ/CJNEkw0eSdbrcw/kSbJlFJmWYN9cQ/mnOI79vZbAIO7TiZEi1e/v40hIZBBd0GC7rtGVoA5dCsdg6yo9/MKRs0K7ntvrdKRDdTX628j6XxMMF7QXn5bnUZ82Ms/83YqbXyqOhk/lAV+5DuxuhjAnrn9BlguVbHJOaBhtfzsuoNOI06U8/ug6e2Bct4R9FZbzN0JNK0lNBvug22MKmPkzpJ+srdv/UPDdPetv95FxXBjmla/+MNdWxgpBphfHQKmt49+8G4aBvWCd7rvLumYn7gE9PF7mHS9b67eE3Qxh+j8c/cy6Zwfbfboe6t0zgtadh+Vppf9gYeJxvcP/eN8332B6W2Lq8D0j/OPHgGmc5y/+Kik94/z2WPA9I7z8TFgOsf5ruOgd47zH4PeHueXT4DWGuefHFdp4032YjKHNMb5gftvhOXFAfbCAwT2v5g/Hv1Agf0v5o/xB2lYrZyjDwatNX98G7Tu+eONE6C32njVAq13/ojsNkaVcRtH0vvnj/0uML19do8HTO/8MeoD0zt/jATA9Pb9bwPTPX+8OZT07vnjtRHonfPHi2PQO+ePZyagd84f6ynorfljLlNpKDt88u5V7yFm8IJx/ZQtbF+W/6DbJpaZnxVpcN22iapv8T2NvevZ48dg7XQX3Ld34waLOm55axtHCj2x2QKOfIzbuCFwjc7kHxyH+PtaXd0De0SFVdXlbTIxCIbOg+fjrmKziWN7OP6+Pup93Kx3Oyiz/Prjo8DPmf1t2iaIAzRTkhaxB+yVzRtjSycB9ldbN8aurjf62QM=
*/