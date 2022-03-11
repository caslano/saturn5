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