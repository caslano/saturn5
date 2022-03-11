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