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