//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE_SAMPLER_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE_SAMPLER_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {

/// \class image_sampler
/// \brief An OpenCL image sampler object
///
/// \see image2d, image_format
class image_sampler
{
public:
    enum addressing_mode {
        none = CL_ADDRESS_NONE,
        clamp_to_edge = CL_ADDRESS_CLAMP_TO_EDGE,
        clamp = CL_ADDRESS_CLAMP,
        repeat = CL_ADDRESS_REPEAT
    };

    enum filter_mode {
        nearest = CL_FILTER_NEAREST,
        linear = CL_FILTER_LINEAR
    };

    image_sampler()
        : m_sampler(0)
    {
    }

    image_sampler(const context &context,
                  bool normalized_coords,
                  cl_addressing_mode addressing_mode,
                  cl_filter_mode filter_mode)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        std::vector<cl_sampler_properties> sampler_properties;
        sampler_properties.push_back(CL_SAMPLER_NORMALIZED_COORDS);
        sampler_properties.push_back(cl_sampler_properties(normalized_coords));
        sampler_properties.push_back(CL_SAMPLER_ADDRESSING_MODE);
        sampler_properties.push_back(cl_sampler_properties(addressing_mode));
        sampler_properties.push_back(CL_SAMPLER_FILTER_MODE);
        sampler_properties.push_back(cl_sampler_properties(filter_mode));
        sampler_properties.push_back(cl_sampler_properties(0));

        m_sampler = clCreateSamplerWithProperties(
            context, &sampler_properties[0], &error
        );
        #else
        m_sampler = clCreateSampler(
            context, normalized_coords, addressing_mode, filter_mode, &error
        );
        #endif

        if(!m_sampler){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    explicit image_sampler(cl_sampler sampler, bool retain = true)
        : m_sampler(sampler)
    {
        if(m_sampler && retain){
            clRetainSampler(m_sampler);
        }
    }

    /// Creates a new image sampler object as a copy of \p other.
    image_sampler(const image_sampler &other)
        : m_sampler(other.m_sampler)
    {
        if(m_sampler){
            clRetainSampler(m_sampler);
        }
    }

    /// Copies the image sampler object from \p other to \c *this.
    image_sampler& operator=(const image_sampler &other)
    {
        if(this != &other){
            if(m_sampler){
                clReleaseSampler(m_sampler);
            }

            m_sampler = other.m_sampler;

            if(m_sampler){
                clRetainSampler(m_sampler);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    image_sampler(image_sampler&& other) BOOST_NOEXCEPT
        : m_sampler(other.m_sampler)
    {
        other.m_sampler = 0;
    }

    image_sampler& operator=(image_sampler&& other) BOOST_NOEXCEPT
    {
        if(m_sampler){
            clReleaseSampler(m_sampler);
        }

        m_sampler = other.m_sampler;
        other.m_sampler = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the image sampler object.
    ~image_sampler()
    {
        if(m_sampler){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseSampler(m_sampler)
            );
        }
    }

    /// Returns the underlying \c cl_sampler object.
    cl_sampler& get() const
    {
        return const_cast<cl_sampler &>(m_sampler);
    }

    /// Returns the context for the image sampler object.
    context get_context() const
    {
        return context(get_info<cl_context>(CL_SAMPLER_CONTEXT));
    }

    /// Returns information about the sampler.
    ///
    /// \see_opencl_ref{clGetSamplerInfo}
    template<class T>
    T get_info(cl_sampler_info info) const
    {
        return detail::get_object_info<T>(clGetSamplerInfo, m_sampler, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<image_sampler, Enum>::type
    get_info() const;

    /// Returns \c true if the sampler is the same at \p other.
    bool operator==(const image_sampler &other) const
    {
        return m_sampler == other.m_sampler;
    }

    /// Returns \c true if the sampler is different from \p other.
    bool operator!=(const image_sampler &other) const
    {
        return m_sampler != other.m_sampler;
    }

    operator cl_sampler() const
    {
        return m_sampler;
    }

private:
    cl_sampler m_sampler;
};

/// \internal_ define get_info() specializations for image_sampler
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(image_sampler,
    ((cl_uint, CL_SAMPLER_REFERENCE_COUNT))
    ((cl_context, CL_SAMPLER_CONTEXT))
    ((cl_addressing_mode, CL_SAMPLER_ADDRESSING_MODE))
    ((cl_filter_mode, CL_SAMPLER_FILTER_MODE))
    ((bool, CL_SAMPLER_NORMALIZED_COORDS))
)

namespace detail {

// set_kernel_arg specialization for image samplers
template<>
struct set_kernel_arg<image_sampler>
{
    void operator()(kernel &kernel_, size_t index, const image_sampler &sampler)
    {
        kernel_.set_arg(index, sampler.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::image_sampler, sampler_t)

#endif // BOOST_COMPUTE_IMAGE_IMAGE_SAMPLER_HPP

/* image_sampler.hpp
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
*/