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
zXb9kx3HWNxPIr/lnqDOWGcjv003mrSCjCJCaovxg/AfZ80VZSLMxGht7vLzpmyGRU1ke6KCMmb79UlCwe9+M/zpXKNuZ5IUN5DwdNbgeU7WQnPm5IQrW5b7Y4QLLP4dwNdxQUiFE90wVxPOiBtZf/+mS5++C7R8vN58Rla3mmrscGy/Jznsk5PvEjT1JFL0H9J+sI8Bv2Fe+fMoL3dw76LvoClfeK72Id8+T4WGSuwuDRr25QDndkss1uYsQdmiXTs45bSlxhxjF00yKYIWYSqvkhevYId56SE1w+Q9Q21Q/5tkEJv71itDSJQNj6C60derZcfS3R8qvM+Xg9Wf4Ku8wyv6fBeOVEvt7EVEzU1cyfI7I7NgewHjgngIYJZMuzb9A7zm5e4/foGKMGCuwf8COtZ4dnYjhfDJyW9TsI3DSOGvyjTFiKzPopGN/Or9cUb4bf/DKM2th7RZcsfr+IPD0CrbvlV/QWqR59pRgrbVoEDMMLgh1W1BWKwsJ8EITk3qgt3g5zmU7thlTohyoEHDjRwlwQWcmmUCs3/ty7OiU4x7hPioa/1cmA==
*/