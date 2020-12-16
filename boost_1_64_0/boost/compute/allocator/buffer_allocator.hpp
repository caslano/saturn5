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
m35F9friU9kfPb/xR/Y3g275Bh1omfuJn1lHG+dl8EAM3agZzo2Dt6PEsyJ+/zv77BGuu6NrLqD3POh+p/P3qfDVavGOn7Wcbp0FvN+sf7X4J30F+OOqYrjzRTpxC5zgevn4bd149atYddfOCcE4jAx5ifVm+nKm7pAnh/P/q+lO4mHqVfJNxzh6uHWW5+PNcGtdAt4fFXxOHwZXwM1VK8R39cxFQ+BM+GqV9TKV79Ehl1nP97Q+2Wq607nw9k7r+X7Uj7JPPH1P/epc61Qq+MHC6OC5H+YPv/Bndtf2B7wkTs58it2060Anty5mfpS6G7zXYJysW82G1/PvCO7flIjPvcq++O3UMZ6rq7yQTOc3/onWr826Fm+/n45kvJIbgusMOg4eD/taP/M8z+jbt2645Qs6SCn9Ap8uLqNXZdFr9H3kTJane7L7j/CxI+hgrZFwW3RwvTh+F8Ge6CcZz8CB+cF1VrTJD2v0RYX9c7/oh/xRP8AkdjXCe8+DC+5TBz/XdeH4ojfcdwD98Dvx5BzjyY5iLqajZ0QH85Inr4+JDf5+GxyQJB5uDt67IUkf7p/sDK9vWo+XLHPfn+kh+hzbwv7wMeLXt3jFbvXN5+k+5+Ot7djXUM9/AdzWPyF4D7ipP100ZiC+ONZ7XYSP4XeFqQnB+y2K0KdCz6vDAx6hCz6MbyaKO1voHGfLz56jbjcc+Jn4LO83bqDXzINnNqqLV6tn7KOPHSHfwW2rOsNjxnP7UH//AL2OHZTcZJ0VPazyJv7SQ7zryG9Pxfei8YoVnn9+JD3FeqbX4OIF1uHx82p1hP4Xw+dfxVp3o19Wf8fsn+kfC/Ct8/VR/Juf86PI7foK9AvOOlIcmijPfs3O9es2rYmgU+FLl9PNSuA1fadJz/KTfezugL4HeCJSn0Th/epP8GPrAe+jv33WO36fqa9hI73Ndcqt32/cjL9Hi3vW3bU1ss+n8L9r6Xg92HFZPBzGzzxn5g7z0Yf+MFde7hRDN4KDhqkzLPQJ35S7X8W04HpFU9QpO8E3V4brBvDqG7xnrP7QGnXsEjisQPyE5yvY4bgN6reD2Wce3fzgaH0srqO+t/YyOHykfttp4tsf+r5n8bfz5ONqvKtnQvD93/jtlxGeI+yTSAju+zS/tB59FXss3Mb+X4SfZ/BX/QK5j/GLQn1Xp+IFq+GdQ/lxJr2gu36fterCcGHFT8F16jbinfJOyiHs/XPzTY8vuFH8PRwP7Gwdw2feaywcEPZXwl3JLfYvOEY9+QJ9Ja/Rr45T/67B65LFz836JegHs8fTJ8WP7J3w/0B/l6N/oBM7+sD8yh+pW+DpS+PoRdbtbW0XXO8MvBbeyzla/8av+mPW09H0D62kxxbPUL/8QFy4hD+qu5QNgztS1J2/tw/LE+LFHHyir7pbJJ3wWHrocrger8kYire0gyPp1AVw0Ghxu9K+A5H4bMN9nvdveCUVr22Fn6Ya1+F0oGesV7tGvY3fxxTobzvT+54Fx02li/eBF1vwmPti6Y10ne5hP79604uuj+fXDEoI4n3YpwOnZcvDmceLy0fArw+qG8wWFz6Wp+z3kv22PNpFfDrc/ict+kqb1Jk76i+NVG9opXePoueK77n47Koh+v30Bxe24aG/+t5gfgAPFp6tH4FOMnIh3aUi+HlVT/he/XP2MLrdJPWci/lFjvE9VHzuwE4SxY1urldA9xFXV90R9qnRUwYZz2HwQ0f+Zp3I2gX62RKj8EJ2UobXfGJfpmvpeu/LNz/F0+/oSx/DYTXiaddo/ex4Aj9K6yv/6Stqe5hf0xeSjqPvXUL/3aPuMcxzve3vv8aLtqgjb7IuIC8e/jdPJfI=
*/