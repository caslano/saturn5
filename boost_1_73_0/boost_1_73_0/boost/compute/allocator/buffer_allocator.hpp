//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALLOCATOR_BUFFER_ALLOCATOR_HPP
#define BOOST_COMPUTE_ALLOCATOR_BUFFER_ALLOCATOR_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/detail/device_ptr.hpp>

namespace boost {
namespace compute {

/// \class buffer_allocator
/// \brief The buffer_allocator class allocates memory with \ref buffer objects
///
/// \see buffer
template<class T>
class buffer_allocator
{
public:
    typedef T value_type;
    typedef detail::device_ptr<T> pointer;
    typedef const detail::device_ptr<T> const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    explicit buffer_allocator(const context &context)
        : m_context(context),
          m_mem_flags(buffer::read_write)
    {
    }

    buffer_allocator(const buffer_allocator<T> &other)
        : m_context(other.m_context),
          m_mem_flags(other.m_mem_flags)
    {
    }

    buffer_allocator<T>& operator=(const buffer_allocator<T> &other)
    {
        if(this != &other){
            m_context = other.m_context;
            m_mem_flags = other.m_mem_flags;
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    buffer_allocator(buffer_allocator<T>&& other) BOOST_NOEXCEPT
        : m_context(std::move(other.m_context)),
          m_mem_flags(other.m_mem_flags)
    {
    }

    buffer_allocator<T>& operator=(buffer_allocator<T>&& other) BOOST_NOEXCEPT
    {
        m_context = std::move(other.m_context);
        m_mem_flags = other.m_mem_flags;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    ~buffer_allocator()
    {
    }

    pointer allocate(size_type n)
    {
        buffer buf(m_context, n * sizeof(T), m_mem_flags);
        clRetainMemObject(buf.get());
        return detail::device_ptr<T>(buf);
    }

    void deallocate(pointer p, size_type n)
    {
        BOOST_ASSERT(p.get_buffer().get_context() == m_context);

        (void) n;

        clReleaseMemObject(p.get_buffer().get());
    }

    size_type max_size() const
    {
        return m_context.get_device().max_memory_alloc_size() / sizeof(T);
    }

    context get_context() const
    {
        return m_context;
    }

protected:
    void set_mem_flags(cl_mem_flags flags)
    {
        m_mem_flags = flags;
    }

private:
    context m_context;
    cl_mem_flags m_mem_flags;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALLOCATOR_BUFFER_ALLOCATOR_HPP

/* buffer_allocator.hpp
ew/IroLfOqF4EzqWE8cN1gynjR44WYwm/U8fb8f9YO4lHHBc1cbSEnFPpVaF5WBE/iFWi9hZsBI2zlTx4CuAznO9xlNQVtpquynlj0HwpFVCuY4fFy2Vw4TeZEiRnJOPMXMXEmEF8Z/9QxHHHHT+o+vZvUHWVqVlvFq1mYw1FtVDvZIFAEOOGiQcasSjQjIidxz/NkrWorAuJ1lKiKB5lIGpkTWWSdieWOT5UsSPXCOgAHIpTWXFvJnEoS1FnB2wD4MAynhlWZ1EpqqQjR6NKQzMoRrdbfChtgBATmvm05jJjJDLrFPrBldTERZrpCabv/PnbTSYXffmPe/2A1ffjv8SZ9fFn3b3K6/uefQAwuMu9BJ90WVknCUreJTYo4HzqC5yFP1CeucBTp8l7JZiQ1at5Jc8+o09Ed30ZoOjTjCljFWqXMC5QGnj1hnRtFE4yQdM6Cs++lnAZ9K1NDay6RRPIq/lfrNeSngN2sx2ZcBVgAUruuhPJp+Gg6Cv9aOSXuxa5flOHkK40sYDIIXZkPeqQYr4wOD2s19Hw2Cs7TanuCFp3C40J4NVT8L11H1WfzdoqU68ewbX0LXsGNcS7V1pJEOGBN/QctOIbpBncL0VH4ejwcnlaVsX5bNAz5LhMbOvURT78Du0xlfK
*/