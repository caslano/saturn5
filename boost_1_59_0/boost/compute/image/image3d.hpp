//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE3D_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE3D_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/image/image_format.hpp>
#include <boost/compute/image/image_object.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

// forward declarations
class command_queue;

/// \class image3d
/// \brief An OpenCL 3D image object
///
/// \see image_format, image2d
class image3d : public image_object
{
public:
    /// Creates a null image3d object.
    image3d()
        : image_object()
    {
    }

    /// Creates a new image3d object.
    ///
    /// \see_opencl_ref{clCreateImage}
    image3d(const context &context,
            size_t image_width,
            size_t image_height,
            size_t image_depth,
            const image_format &format,
            cl_mem_flags flags = read_write,
            void *host_ptr = 0,
            size_t image_row_pitch = 0,
            size_t image_slice_pitch = 0)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        cl_image_desc desc;
        desc.image_type = CL_MEM_OBJECT_IMAGE3D;
        desc.image_width = image_width;
        desc.image_height = image_height;
        desc.image_depth = image_depth;
        desc.image_array_size = 0;
        desc.image_row_pitch = image_row_pitch;
        desc.image_slice_pitch = image_slice_pitch;
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
        m_mem = clCreateImage3D(context,
                                flags,
                                format.get_format_ptr(),
                                image_width,
                                image_height,
                                image_depth,
                                image_row_pitch,
                                image_slice_pitch,
                                host_ptr,
                                &error);
        #endif

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// \internal_ (deprecated)
    image3d(const context &context,
            cl_mem_flags flags,
            const image_format &format,
            size_t image_width,
            size_t image_height,
            size_t image_depth,
            size_t image_row_pitch,
            size_t image_slice_pitch = 0,
            void *host_ptr = 0)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        cl_image_desc desc;
        desc.image_type = CL_MEM_OBJECT_IMAGE3D;
        desc.image_width = image_width;
        desc.image_height = image_height;
        desc.image_depth = image_depth;
        desc.image_array_size = 0;
        desc.image_row_pitch = image_row_pitch;
        desc.image_slice_pitch = image_slice_pitch;
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
        m_mem = clCreateImage3D(context,
                                flags,
                                format.get_format_ptr(),
                                image_width,
                                image_height,
                                image_depth,
                                image_row_pitch,
                                image_slice_pitch,
                                host_ptr,
                                &error);
        #endif

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new image3d as a copy of \p other.
    image3d(const image3d &other)
        : image_object(other)
    {
    }

    /// Copies the image3d from \p other.
    image3d& operator=(const image3d &other)
    {
        image_object::operator=(other);

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new image object from \p other.
    image3d(image3d&& other) BOOST_NOEXCEPT
        : image_object(std::move(other))
    {
    }

    /// Move-assigns the image from \p other to \c *this.
    image3d& operator=(image3d&& other) BOOST_NOEXCEPT
    {
        image_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the image3d object.
    ~image3d()
    {
    }

    /// Returns the size (width, height, depth) of the image.
    extents<3> size() const
    {
        extents<3> size;
        size[0] = get_info<size_t>(CL_IMAGE_WIDTH);
        size[1] = get_info<size_t>(CL_IMAGE_HEIGHT);
        size[2] = get_info<size_t>(CL_IMAGE_DEPTH);
        return size;
    }

    /// Returns the origin of the image (\c 0, \c 0, \c 0).
    extents<3> origin() const
    {
        return extents<3>();
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
    typename detail::get_object_info_type<image3d, Enum>::type
    get_info() const;

    /// Returns the supported 3D image formats for the context.
    ///
    /// \see_opencl_ref{clGetSupportedImageFormats}
    static std::vector<image_format>
    get_supported_formats(const context &context, cl_mem_flags flags = read_write)
    {
        return image_object::get_supported_formats(context, CL_MEM_OBJECT_IMAGE3D, flags);
    }

    /// Returns \c true if \p format is a supported 3D image format for
    /// \p context.
    static bool is_supported_format(const image_format &format,
                                    const context &context,
                                    cl_mem_flags flags = read_write)
    {
        return image_object::is_supported_format(
            format, context, CL_MEM_OBJECT_IMAGE3D, flags
        );
    }

    /// Creates a new image with a copy of the data in \c *this. Uses \p queue
    /// to perform the copy operation.
    image3d clone(command_queue &queue) const;
};

/// \internal_ define get_info() specializations for image3d
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(image3d,
    ((cl_image_format, CL_IMAGE_FORMAT))
    ((size_t, CL_IMAGE_ELEMENT_SIZE))
    ((size_t, CL_IMAGE_ROW_PITCH))
    ((size_t, CL_IMAGE_SLICE_PITCH))
    ((size_t, CL_IMAGE_WIDTH))
    ((size_t, CL_IMAGE_HEIGHT))
    ((size_t, CL_IMAGE_DEPTH))
)

namespace detail {

// set_kernel_arg() specialization for image3d
template<>
struct set_kernel_arg<image3d> : public set_kernel_arg<image_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::image3d, image3d_t)

#endif // BOOST_COMPUTE_IMAGE_IMAGE3D_HPP

/* image3d.hpp
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
*/