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
KpThWC91qbDlOI10/6/IMXkdKTv2gDTkJMvYKOft+UFZvjsIlCy/mejR0pLMgytCjKUV0c7QYUmux8qlWD88KKNpUNCpnVjE1nDUnQqdwsai4FfwxfBMgGW5FyBzuu1voPoOYwhdBpruM5Ahqw1ai68ky7P0sRo70LVs7rmG1AOJUgSqX5VeRf1Eu3re7LlMjfV3U34Y6sZ4TcSA5fX/HNcHOW17QJzK9Jyr5iC7eh7iIsPmIdHurJ2pFDXHHbnjUY9YzDtdfk0QXbcwFbzen9Kw2ZJIyDORmWLOIctVTDni2zkpZ7loI8hIwoVE1O2mZeMS2kHPI3t0xQNdfMT5v6lVV1KMVIsur60uo0HWBnFrz4ei7/g4e1LJ3Ee/Ma2S6BHpSRsD8meyhrEtzQHIEbUc/S5k+ruQaVs2mWErhxL//bJCFljDiHxYnwmB5HX+QbHPkB90KLVdtKz5EN0h52/6XQ49zDMJxdcJ3XErbmcf0t9HXRJ2OZUr7G+fjPPLkEQM6NLi6Oxgmu+O1vuTiafs8yODXu9P26ONve1+g+5K3O4/WMiwwH3bwvFspPvcezD8KU9l64euULXktdkYjMQ1XJvd0Vg8m+PdWeY3dwWdX1diSZB36EbQM5PHi1QEeyH2RZ/G8ibaUBK729rnsM/XHiBZe7ZPNNc0JIeP36T7l7ZBn3/KdQz6ynh7MHwsf9pW8vmXX7B1w2I3ExXo0EOZdNOov3jXxcWTKur79/bvLfwOIp/t/mXJxqZEVb87f7c0japBI277i7es1jqL91i8ZRD43vskdmxg7xpGfqVdo/24ds1nsIz9yNmPiP1I2Y8OfiTsR5f9WGE/xuzHNvsxYD+G7Mdj2Q8qN5b/1gBcnDc/8V8W2I+HyM9N/u/d+M/T7Kdg23uV5PvQ5Lua+XHSDGqNtML53uMMgJUdm70+vvWBm+LXDV3kpp3XOgci15EkgLXguZK3n1u8xX7abof1qNr0kWKkC9nC7xORPyg9sO007Tqos7m5h+TlepuGLFQCPwvCNK83a74Sw2DM5VDW4ZbPkunmN8061P12FMRh3G4X6vD/yEng1qgoLIqPM5KPVYuPwM8bcR430qDAx/+Y/zLabk0LhC54Ua3fL1G+fk+zpXaQ8Hnrylf/+P2Jvx+xMbszebTn8fXt3W7A1rcy7o/WtDV6oLhD00VC1liXTLuIz8mkcZnVVo1CpWf35LwofpfrmHYWriQRbJTuaHOzO9VzHUW1j9TvtxXzAilq8fs/CVALlsiZWOXzAtWptEaYpz2ik+JX68B/U/qdtcmUPzIg7YH2DWasie6m60B3Vp3pTgkv54pj+vvISxZ13g0k/UaXYnStTwXtNpz26Usz2t6Q9PZ2f6c/NN8CPsV1aX/46MGwL26NHfc22GtO1CiK3/ddnc2FYjeVNqGVtQg7/qOCLhz7zlrkGtfmtJXYXTpLG/QP1J7urukN8N3dfaN9IaJdWpRXDCJH5qLsTwkcNuhhTMh8PifobnCEshxQhzmBMzZKkRPP55sox32YCPmgrtaOo8z/ushfBF675d+oUD4QnH6zAt22L79HdMYcd9PLPI8NnpMsa63k9j7PzzRdFybb7ba6PNkxYhPb7fs7OfUCXeZz1/J8Cv30yxnta+JuDrlwg8tRKufpOq486jw4/aItM4pnlPEn0E2nj72+vhQpGS5UMs/L0++UBl4NgF25wG61SHfNa9jjzuX1eqCD1/E5o91uCrrdbu4YvD3hjEGAvRvw5Z7okPnfe0b/uev8OyN/HcVk1t3ZQeff5ylN9KC8S/iGHJZiXwF1Mpx2qJDNt3viQtXr/sgDD8whPSt7kehWJJns+wjptDM=
*/