//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE1D_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE1D_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/image/image_format.hpp>
#include <boost/compute/image/image_object.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

// forward declarations
class command_queue;

/// \class image1d
/// \brief An OpenCL 1D image object
///
/// \opencl_version_warning{1,2}
///
/// \see image_format, image2d
class image1d : public image_object
{
public:
    /// Creates a null image1d object.
    image1d()
        : image_object()
    {
    }

    /// Creates a new image1d object.
    ///
    /// \see_opencl_ref{clCreateImage}
    image1d(const context &context,
            size_t image_width,
            const image_format &format,
            cl_mem_flags flags = read_write,
            void *host_ptr = 0)
    {
    #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        cl_image_desc desc;
        desc.image_type = CL_MEM_OBJECT_IMAGE1D;
        desc.image_width = image_width;
        desc.image_height = 1;
        desc.image_depth = 1;
        desc.image_array_size = 0;
        desc.image_row_pitch = 0;
        desc.image_slice_pitch = 0;
        desc.num_mip_levels = 0;
        desc.num_samples = 0;
    #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        desc.mem_object = 0;
    #else
        desc.buffer = 0;
    #endif

        cl_int error = 0;

        m_mem = clCreateImage(
            context, flags, format.get_format_ptr(), &desc, host_ptr, &error
        );

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    #else
        // image1d objects are only supported in OpenCL 1.2 and later
        BOOST_THROW_EXCEPTION(opencl_error(CL_IMAGE_FORMAT_NOT_SUPPORTED));
    #endif
    }

    /// Creates a new image1d as a copy of \p other.
    image1d(const image1d &other)
      : image_object(other)
    {
    }

    /// Copies the image1d from \p other.
    image1d& operator=(const image1d &other)
    {
        image_object::operator=(other);

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new image object from \p other.
    image1d(image1d&& other) BOOST_NOEXCEPT
        : image_object(std::move(other))
    {
    }

    /// Move-assigns the image from \p other to \c *this.
    image1d& operator=(image1d&& other) BOOST_NOEXCEPT
    {
        image_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the image1d object.
    ~image1d()
    {
    }

    /// Returns the size (width) of the image.
    extents<1> size() const
    {
        extents<1> size;
        size[0] = get_info<size_t>(CL_IMAGE_WIDTH);
        return size;
    }

    /// Returns the origin of the image (\c 0).
    extents<1> origin() const
    {
        return extents<1>();
    }

    /// Returns information about the image.
    ///
    /// \see_opencl_ref{clGetImageInfo}
    template<class T>
    T get_info(cl_image_info info) const
    {
        return get_image_info<T>(info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<image1d, Enum>::type
    get_info() const;

    /// Returns the supported image formats for the context.
    ///
    /// \see_opencl_ref{clGetSupportedImageFormats}
    static std::vector<image_format>
    get_supported_formats(const context &context, cl_mem_flags flags = read_write)
    {
    #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        return image_object::get_supported_formats(context, CL_MEM_OBJECT_IMAGE1D, flags);
    #else
        return std::vector<image_format>();
    #endif
    }

    /// Returns \c true if \p format is a supported 1D image format for
    /// \p context.
    static bool is_supported_format(const image_format &format,
                                    const context &context,
                                    cl_mem_flags flags = read_write)
    {
    #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        return image_object::is_supported_format(
            format, context, CL_MEM_OBJECT_IMAGE1D, flags
        );
    #else
        return false;
    #endif
    }

    /// Creates a new image with a copy of the data in \c *this. Uses \p queue
    /// to perform the copy operation.
    image1d clone(command_queue &queue) const;
};

/// \internal_ define get_info() specializations for image1d
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(image1d,
    ((cl_image_format, CL_IMAGE_FORMAT))
    ((size_t, CL_IMAGE_ELEMENT_SIZE))
    ((size_t, CL_IMAGE_ROW_PITCH))
    ((size_t, CL_IMAGE_SLICE_PITCH))
    ((size_t, CL_IMAGE_WIDTH))
    ((size_t, CL_IMAGE_HEIGHT))
    ((size_t, CL_IMAGE_DEPTH))
)

namespace detail {

// set_kernel_arg() specialization for image1d
template<>
struct set_kernel_arg<image1d> : public set_kernel_arg<image_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::image1d, image1d_t)

#endif // BOOST_COMPUTE_IMAGE_IMAGE1D_HPP

/* image1d.hpp
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
*/