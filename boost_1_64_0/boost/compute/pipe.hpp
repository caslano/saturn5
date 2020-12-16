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
SU9t6r+PsPotxO8w4zd9VsfQ/OvwGjpWVj9z24Ta58sZK6clm0+WCxxto9XPFvychR++gl5KT01xQnEN1vudgD09oi3/sro3Nu6u9vHVLXFTdx3rLjtIW9/76ui2fpdPW/+YT1u/x6fNfdmnrd/r09Z/6COzWhq9V7G084Ux48ZdNi6tqxq2xIb16lR2lJs+ex1jDr8yet/irTH2EVdF26+LsW+Lse+z9ui15nXtvIJejKmLuQgzCT8zF0ofo2KyIzhJYmQiWVn129TqCt0s9jFOFdufhN+JdXJthPYtobCNI/oR/Q7WdvxGue61DyXWf4P482R0nLdVrhfFyOrp+uFB5K7zo+XqVI9L65T24QVRsgHR4/fOfCX57aOcf82v30c5/5rffh/l93zSdwV+C/3SVzqp9ED7KBfGpG/4v7gPcmT6dp4Un76rTV30Td/UKSWJ00eYRPs4a72LSf/gX1G+cfs4++zZvB8ucxPtD5xon+Ffv19xov2EWyw37vs6TPzw++POGH7fiR89PXTkhqRfv7+u/z7AifbRTbQPc6J9m3+7/YT99zdOvG/zN7gX6dM1c0jlsLfu8fuy7AnHM434e1jE391qeP4nY/ro3wHu31P/rsHfvfTvtvz9d1jiqP6s6v1yjbpHvBhH9/RtaPzpXsBFsJnaO6q9BxwL+6r7ufBsOBWOgyZOKqXuyad6j6pryrWoPflK8Zdj8qB7dU7RvTrL4HA4FY6A0yLi26vxZfvE1wt/hr1hMuwLM00adE/bPrCmsWt8hVYfjzqm8VXGDND4qicRn5SlF19NmGruneTFVwvmwRxYD9aG9WEebKh2c5/BVg9N9OzkPkdiehkH8zf+msBjoOiKwbNgG2ieU0+42PiHO0z+4D0mP/BB83zh3+BJ8At4MvzWlAv8CXaAh3OvU0z64GnweNgZ9odd4VBYAIthP1gGR8AZcBScBUfDBbAYXgXHwCWwBK6F4+AGOB7eAifAbXAivB1OgjvhufBeOBnugmXwITgVPg6nwY/gQPgVHAS/g2dCJ0B5mnzAIVq+LUM6JKpvU67Ps7GW72PsrZgLn4R14FOwLXwW5sPn4Onw+aBXv38OeuX/IhwLX4Jnw1fgTPg+TDdrzPAw+BmsC7+EneFXcDX8Gv4Ffgsfhd/BD+D38HPXi+/v8A34g9p/UXtygLzAJvAt2Bx+DnvBL2BBwLtPKdwPywJeupbAD+Ad8EP4APwRPgx/gi/Bn0N7UgZUvlll4ct178ws3RsAFYKZlCNaQV45XQC7wOlwNJwBi+E+WAYvhovgTHgdnAWXw9m6F/McuBbOgzvhpfBeuADuhpfBPfAK+CK8Er4Hr4YfwWvgp3BRwKt318GVcAm82fXcn1P319T9Dbgs4JX7KvgJvBGeQh7Xwk5wHSyC6+F4eBMshTfDOXAzvAI+BPHDiq5Xno/DJ+Hz0AlST2ASfAXmwFfhCfA1eDJ8A54K34IFcC8cAN+Gf4DvwEK4zZQr3A7PgffA6fBeeDm8Hy6Gu0w5wB1wBbwd3gPvhLvgX+Bf4QPwWfgB/AZ+DH+An0AnifoLU+DnsA78wqQT8ly1nqgcocqBxtaTbwJe+/cz7AB/gT3NhSD5MfUGypgEzjbO8DJIWUl9SQ569SM16NWPNHgzTId3warwHngY3AUz4DswU+txM/gjnASTSWQprAwnwyx4Pqzjeuk4FtaCx8McOBDmwqGwNhwJ68DRsB4cB+vDy2EDuBA2gdfBpvCPrnf/TbA53AqPg4/B1vBl2Cbo1cPu8EPYA6aaPW9hVdgb5sA+sB0sgB1gf9gFDoB94UA4AA7S9/1MeD4cAmfAofAiOAzOgiPg1ZA6JfU=
*/