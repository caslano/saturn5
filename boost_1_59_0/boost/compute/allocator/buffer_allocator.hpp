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
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
*/