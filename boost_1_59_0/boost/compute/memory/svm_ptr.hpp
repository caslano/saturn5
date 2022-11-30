//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_MEMORY_SVM_PTR_HPP
#define BOOST_COMPUTE_MEMORY_SVM_PTR_HPP

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for svm_ptr<T>
template<class T>
class svm_ptr;

// svm functions require OpenCL 2.0
#if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
namespace detail {

template<class T, class IndexExpr>
struct svm_ptr_index_expr
{
    typedef T result_type;

    svm_ptr_index_expr(const svm_ptr<T> &svm_ptr,
                       const IndexExpr &expr)
        : m_svm_ptr(svm_ptr),
          m_expr(expr)
    {
    }

    operator T() const
    {
        BOOST_STATIC_ASSERT_MSG(boost::is_integral<IndexExpr>::value,
                                "Index expression must be integral");

        BOOST_ASSERT(m_svm_ptr.get());

        const context &context = m_svm_ptr.get_context();
        const device &device = context.get_device();
        command_queue queue(context, device);

        T value;
        T* ptr =
            static_cast<T*>(m_svm_ptr.get()) + static_cast<std::ptrdiff_t>(m_expr);
        queue.enqueue_svm_map(static_cast<void*>(ptr), sizeof(T), CL_MAP_READ);
        value = *(ptr);
        queue.enqueue_svm_unmap(static_cast<void*>(ptr)).wait();

        return value;
    }

    const svm_ptr<T> &m_svm_ptr;
    IndexExpr m_expr;
};

} // end detail namespace
#endif

template<class T>
class svm_ptr
{
public:
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;

    svm_ptr()
        : m_ptr(0)
    {
    }

    svm_ptr(void *ptr, const context &context)
        : m_ptr(static_cast<T*>(ptr)),
          m_context(context)
    {
    }

    svm_ptr(const svm_ptr<T> &other)
        : m_ptr(other.m_ptr),
          m_context(other.m_context)
    {
    }

    svm_ptr<T>& operator=(const svm_ptr<T> &other)
    {
        m_ptr = other.m_ptr;
        m_context = other.m_context;
        return *this;
    }

    ~svm_ptr()
    {
    }

    void* get() const
    {
        return m_ptr;
    }

    svm_ptr<T> operator+(difference_type n)
    {
        return svm_ptr<T>(m_ptr + n, m_context);
    }

    difference_type operator-(svm_ptr<T> other)
    {
        BOOST_ASSERT(other.m_context == m_context);
        return m_ptr - other.m_ptr;
    }

    const context& get_context() const
    {
        return m_context;
    }

    bool operator==(const svm_ptr<T>& other) const
    {
        return (other.m_context == m_context) && (m_ptr == other.m_ptr);
    }

    bool operator!=(const svm_ptr<T>& other) const
    {
        return (other.m_context != m_context) || (m_ptr != other.m_ptr);
    }

    // svm functions require OpenCL 2.0
    #if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// \internal_
    template<class Expr>
    detail::svm_ptr_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        BOOST_ASSERT(m_ptr);

        return detail::svm_ptr_index_expr<T, Expr>(*this,
                                                   expr);
    }
    #endif

private:
    T *m_ptr;
    context m_context;
};

namespace detail {

/// \internal_
template<class T>
struct set_kernel_arg<svm_ptr<T> >
{
    void operator()(kernel &kernel_, size_t index, const svm_ptr<T> &ptr)
    {
        kernel_.set_arg_svm_ptr(index, ptr.get());
    }
};

} // end detail namespace

/// \internal_ (is_device_iterator specialization for svm_ptr)
template<class T>
struct is_device_iterator<svm_ptr<T> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_MEMORY_SVM_PTR_HPP

/* svm_ptr.hpp
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
*/