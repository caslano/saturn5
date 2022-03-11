//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_PIPE_HPP
#define BOOST_COMPUTE_PIPE_HPP

#include <boost/compute/cl.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/memory_object.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/detail/get_object_info.hpp>

// pipe objects require opencl 2.0
#if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)

namespace boost {
namespace compute {

/// \class pipe
/// \brief A FIFO data pipe
///
/// \opencl_version_warning{2,0}
///
/// \see memory_object
class pipe : public memory_object
{
public:
    /// Creates a null pipe object.
    pipe()
        : memory_object()
    {
    }

    /// Creates a pipe object for \p mem. If \p retain is \c true, the
    /// reference count for \p mem will be incremented.
    explicit pipe(cl_mem mem, bool retain = true)
        : memory_object(mem, retain)
    {
    }

    /// Creates a new pipe in \p context.
    pipe(const context &context,
         uint_ pipe_packet_size,
         uint_ pipe_max_packets,
         cl_mem_flags flags = read_write,
         const cl_pipe_properties *properties = 0)
    {
        cl_int error = 0;
        m_mem = clCreatePipe(context,
                             flags,
                             pipe_packet_size,
                             pipe_max_packets,
                             properties,
                             &error);
        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new pipe object as a copy of \p other.
    pipe(const pipe &other)
        : memory_object(other)
    {
    }

    /// Copies the pipe object from \p other to \c *this.
    pipe& operator=(const pipe &other)
    {
        if(this != &other){
            memory_object::operator=(other);
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new pipe object from \p other.
    pipe(pipe&& other) BOOST_NOEXCEPT
        : memory_object(std::move(other))
    {
    }

    /// Move-assigns the pipe from \p other to \c *this.
    pipe& operator=(pipe&& other) BOOST_NOEXCEPT
    {
        memory_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the pipe object.
    ~pipe()
    {
    }

    /// Returns the packet size.
    uint_ packet_size() const
    {
        return get_info<uint_>(CL_PIPE_PACKET_SIZE);
    }

    /// Returns the max number of packets.
    uint_ max_packets() const
    {
        return get_info<uint_>(CL_PIPE_MAX_PACKETS);
    }

    /// Returns information about the pipe.
    ///
    /// \see_opencl2_ref{clGetPipeInfo}
    template<class T>
    T get_info(cl_pipe_info info) const
    {
        return detail::get_object_info<T>(clGetPipeInfo, m_mem, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<pipe, Enum>::type get_info() const;
};

/// \internal_ define get_info() specializations for pipe
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(pipe,
    ((cl_uint, CL_PIPE_PACKET_SIZE))
    ((cl_uint, CL_PIPE_MAX_PACKETS))
)

namespace detail {

// set_kernel_arg specialization for pipe
template<>
struct set_kernel_arg<pipe>
{
    void operator()(kernel &kernel_, size_t index, const pipe &pipe_)
    {
        kernel_.set_arg(index, pipe_.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CL_VERSION_2_0

#endif // BOOST_COMPUTE_PIPE_HPP

/* pipe.hpp
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
*/