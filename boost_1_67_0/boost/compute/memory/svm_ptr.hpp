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