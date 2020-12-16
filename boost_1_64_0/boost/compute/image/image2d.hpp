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
1azsNVA2GoSne2BpOpTJMcslGDkQgHloed2pfF33Gzjy7cpEWNSdBeDNgXPHkq13WgKjnc9OP9wA7ViIhONlpKVloNIc071G2Xiz+ejb48sUb07f1nRTf0I/DomuKyHqP0UaOEdVIozbM4SxowHF97PqOyINhWw8ib5jMEvenqbLMXU36v+c0voD47QjphZDctCfLkbVB5jnFets5oN5uez01q01H0UychF17rhy48jwg9x5A8m1znCEhvP2ZUpXiOCUaaaeTKM25uR4eOE1ym0AV9c+1OXZGZsvKbZdQQ5fpjGuHcHpr3L0fbn9gNNdaPfXz6pDua2Fk1lOn7qnrTCnunLj1uuNzvhz5eotZXoLVRc8vFNjCvm/29XXSCvG1RrxCGGRdUqsOQ0DlNM2CF+YtKQ8vBdtienK7Qqxp+vyBIQzB7mn5aQuuBql14lF2R8pL7swBi8QrtDZkvYpzZdOJ+v22fL8C+39RcI5tiEqBznCiVFtr3y1kM7eV/6mUb5rI3zHoFn2n1zfvIf+PuKSM9cp2KP67IOMdXriN2l/r5lUaj5z8IjHeMUCtan2yEx8JfebzawVV7PATyjB4une9vbiaeOhuMni6cFw8fSEtpT6IiNati7IvLwHG3m1/Vbejtu1PPONp4BVmnW1VzX3YLv8WjtLkzyu+QlPRBwMNxZPj/am472pxYmoB+p9L7vsZtxOw7jlb/TX9h4tXnwQ+AdJfMPE034AbUlU6llSFykWT4skp9me010Xbxmm/JL3Ce02nV5gv053e+t9tb3kG+0/frDV/vU8agdpO5CM0GskstkeIPH7Vv0jPw7a9Xq90hAJqLeJF5aKLus3y5tX5b3CTH+vOM3TahLXfbqOmL2qgz7qpxL/NhMf1vxK1GqkcV71KfRk8TRLQptlp3mVg2UWMB09hFbzaT0SbcHekmL5NVX5Pzfzu3elkdTSdj2R4jYZTyQDi/dQe5MmPvOTRpK3o0poihudGZkoviO1F3n5hxjp7klqOAsD2hKjIuhS8LMCfh+1V2ViKxU/SvIgrjYyv9Of8uwXT6+dY4K80Zcpvaqqz7yZ9l5Jtd4Ko2aFl0NdgPYcqPb0TXxY9SuNVrOdprlRFk83r9tvb1tR9iZ9Em6rPfet8ivNejOPMlG+2Z+LavyeN/G0v1YNmmmTOgHly051y+eRvEvZg7q+56u+ufAQe48vrAWVtJ4q5UFncXukfXZV52w8QOkQMx3pmigKaeQ36ywdFYWEoinQt6cXlEyY6VNWhXYQSCGSm9MqUU+1+9xDjTT1ph+1szZzzIh6i4JVUj2KJ3s7O73dc4vzfBBv7vqe4uH8Qy25zOqkNSutQOkuOrK5NdqQe3uKhwMzTVT3s1qr0q5UmoIHGoLEiNRiIr3FyRq7U8L3DN3xl4dauiOJ86wdkG7i2tYQv5oaEw8z+57aPW41WqRyfUNNKl0NKYQE6Lrf62GW7qxXa7W0GTZEueKxs4LcNayyW341rLcaUSPyqyVl8yyEXjnNKk+EcxM9XvcfZuvApBk269SdJAl5LMJu67QHVmP2v2TkbtB/Ztp7J2TIBLVmIlMuLyUSX1tQ+s/Ep36YxfWkkldVgodQnNKDZZpI8fcBi7+6X29SLFcWRToRXUfAR5Pm8B5qbFhpKzS/hkErardEWnaaOMy4GSOS3VLxedHms1XL6URbUhPJqDWYalb+Asy/D7dkOKwGFDDVzHWaHIkCxd+cmaZS9WkQRVlCuhKJrHqhz25rpaOuipv1elCr2um4fSXZ1HLum2nvXau340YWNHlKShAvywSxKiu3yqrRHBnQJFcT7c/jH/lihy4cIENTJEb7j536NYJWs5I=
*/