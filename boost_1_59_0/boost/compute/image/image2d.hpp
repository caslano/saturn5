//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE2D_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE2D_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/image/image_format.hpp>
#include <boost/compute/image/image_object.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

// forward declarations
class command_queue;

/// \class image2d
/// \brief An OpenCL 2D image object
///
/// For example, to create a 640x480 8-bit RGBA image:
///
/// \snippet test/test_image2d.cpp create_image
///
/// \see image_format, image3d
class image2d : public image_object
{
public:
    /// Creates a null image2d object.
    image2d()
        : image_object()
    {
    }

    /// Creates a new image2d object.
    ///
    /// \see_opencl_ref{clCreateImage}
    image2d(const context &context,
            size_t image_width,
            size_t image_height,
            const image_format &format,
            cl_mem_flags flags = read_write,
            void *host_ptr = 0,
            size_t image_row_pitch = 0)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        cl_image_desc desc;
        desc.image_type = CL_MEM_OBJECT_IMAGE2D;
        desc.image_width = image_width;
        desc.image_height = image_height;
        desc.image_depth = 1;
        desc.image_array_size = 0;
        desc.image_row_pitch = image_row_pitch;
        desc.image_slice_pitch = 0;
        desc.num_mip_levels = 0;
        desc.num_samples = 0;
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        desc.mem_object = 0;
        #else
        desc.buffer = 0;
        #endif

        m_mem = clCreateImage(context,
                              flags,
                              format.get_format_ptr(),
                              &desc,
                              host_ptr,
                              &error);
        #else
        m_mem = clCreateImage2D(context,
                                flags,
                                format.get_format_ptr(),
                                image_width,
                                image_height,
                                image_row_pitch,
                                host_ptr,
                                &error);
        #endif

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// \internal_ (deprecated)
    image2d(const context &context,
            cl_mem_flags flags,
            const image_format &format,
            size_t image_width,
            size_t image_height,
            size_t image_row_pitch = 0,
            void *host_ptr = 0)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        cl_image_desc desc;
        desc.image_type = CL_MEM_OBJECT_IMAGE2D;
        desc.image_width = image_width;
        desc.image_height = image_height;
        desc.image_depth = 1;
        desc.image_array_size = 0;
        desc.image_row_pitch = image_row_pitch;
        desc.image_slice_pitch = 0;
        desc.num_mip_levels = 0;
        desc.num_samples = 0;
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        desc.mem_object = 0;
        #else
        desc.buffer = 0;
        #endif

        m_mem = clCreateImage(context,
                              flags,
                              format.get_format_ptr(),
                              &desc,
                              host_ptr,
                              &error);
        #else
        m_mem = clCreateImage2D(context,
                                flags,
                                format.get_format_ptr(),
                                image_width,
                                image_height,
                                image_row_pitch,
                                host_ptr,
                                &error);
        #endif

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new image2d as a copy of \p other.
    image2d(const image2d &other)
      : image_object(other)
    {
    }

    /// Copies the image2d from \p other.
    image2d& operator=(const image2d &other)
    {
        image_object::operator=(other);

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new image object from \p other.
    image2d(image2d&& other) BOOST_NOEXCEPT
        : image_object(std::move(other))
    {
    }

    /// Move-assigns the image from \p other to \c *this.
    image2d& operator=(image2d&& other) BOOST_NOEXCEPT
    {
        image_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the image2d object.
    ~image2d()
    {
    }

    /// Returns the size (width, height) of the image.
    extents<2> size() const
    {
        extents<2> size;
        size[0] = get_info<size_t>(CL_IMAGE_WIDTH);
        size[1] = get_info<size_t>(CL_IMAGE_HEIGHT);
        return size;
    }

    /// Returns the origin of the image (\c 0, \c 0).
    extents<2> origin() const
    {
        return extents<2>();
    }

    /// Returns information about the image.
    ///
    /// \see_opencl_ref{clGetImageInfo}
    template<class T>
    T get_info(cl_image_info info) const
    {
        return detail::get_object_info<T>(clGetImageInfo, m_mem, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<image2d, Enum>::type
    get_info() const;

    /// Returns the supported image formats for the context.
    ///
    /// \see_opencl_ref{clGetSupportedImageFormats}
    static std::vector<image_format>
    get_supported_formats(const context &context, cl_mem_flags flags = read_write)
    {
        return image_object::get_supported_formats(context, CL_MEM_OBJECT_IMAGE2D, flags);
    }

    /// Returns \c true if \p format is a supported 2D image format for
    /// \p context.
    static bool is_supported_format(const image_format &format,
                                    const context &context,
                                    cl_mem_flags flags = read_write)
    {
        return image_object::is_supported_format(
            format, context, CL_MEM_OBJECT_IMAGE2D, flags
        );
    }

    /// Creates a new image with a copy of the data in \c *this. Uses \p queue
    /// to perform the copy operation.
    image2d clone(command_queue &queue) const;
};

/// \internal_ define get_info() specializations for image2d
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(image2d,
    ((cl_image_format, CL_IMAGE_FORMAT))
    ((size_t, CL_IMAGE_ELEMENT_SIZE))
    ((size_t, CL_IMAGE_ROW_PITCH))
    ((size_t, CL_IMAGE_SLICE_PITCH))
    ((size_t, CL_IMAGE_WIDTH))
    ((size_t, CL_IMAGE_HEIGHT))
    ((size_t, CL_IMAGE_DEPTH))
)

namespace detail {

// set_kernel_arg() specialization for image2d
template<>
struct set_kernel_arg<image2d> : public set_kernel_arg<image_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::image2d, image2d_t)

#endif // BOOST_COMPUTE_IMAGE_IMAGE2D_HPP

/* image2d.hpp
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
*/