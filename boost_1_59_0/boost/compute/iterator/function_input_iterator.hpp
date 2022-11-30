//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_FUNCTION_INPUT_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_FUNCTION_INPUT_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {

// forward declaration for function_input_iterator<Function>
template<class Function> class function_input_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for function_input_iterator<Function>
template<class Function>
class function_input_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::function_input_iterator<Function>,
        typename ::boost::compute::result_of<Function()>::type,
        ::std::random_access_iterator_tag,
        typename ::boost::compute::result_of<Function()>::type
    > type;
};

template<class Function>
struct function_input_iterator_expr
{
    typedef typename ::boost::compute::result_of<Function()>::type result_type;

    function_input_iterator_expr(const Function &function)
        : m_function(function)
    {
    }

    const Function m_function;
};

template<class Function>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const function_input_iterator_expr<Function> &expr)
{
    return kernel << expr.m_function();
}

} // end detail namespace

/// \class function_input_iterator
/// \brief Iterator which returns the result of a function when dereferenced
///
/// For example:
///
/// \snippet test/test_function_input_iterator.cpp generate_42
///
/// \see make_function_input_iterator()
template<class Function>
class function_input_iterator :
    public detail::function_input_iterator_base<Function>::type
{
public:
    typedef typename detail::function_input_iterator_base<Function>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;
    typedef Function function;

    function_input_iterator(const Function &function, size_t index = 0)
        : m_function(function),
          m_index(index)
    {
    }

    function_input_iterator(const function_input_iterator<Function> &other)
        : m_function(other.m_function),
          m_index(other.m_index)
    {
    }

    function_input_iterator<Function>&
    operator=(const function_input_iterator<Function> &other)
    {
        if(this != &other){
            m_function = other.m_function;
            m_index = other.m_index;
        }

        return *this;
    }

    ~function_input_iterator()
    {
    }

    size_t get_index() const
    {
        return m_index;
    }

    template<class Expr>
    detail::function_input_iterator_expr<Function>
    operator[](const Expr &expr) const
    {
        (void) expr;

        return detail::function_input_iterator_expr<Function>(m_function);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

    bool equal(const function_input_iterator<Function> &other) const
    {
        return m_function == other.m_function && m_index == other.m_index;
    }

    void increment()
    {
        m_index++;
    }

    void decrement()
    {
        m_index--;
    }

    void advance(difference_type n)
    {
        m_index = static_cast<size_t>(static_cast<difference_type>(m_index) + n);
    }

    difference_type
    distance_to(const function_input_iterator<Function> &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    Function m_function;
    size_t m_index;
};

/// Returns a function_input_iterator with \p function.
///
/// \param function function to execute when dereferenced
/// \param index index of the iterator
///
/// \return a \c function_input_iterator with \p function
template<class Function>
inline function_input_iterator<Function>
make_function_input_iterator(const Function &function, size_t index = 0)
{
    return function_input_iterator<Function>(function, index);
}

/// \internal_ (is_device_iterator specialization for function_input_iterator)
template<class Function>
struct is_device_iterator<function_input_iterator<Function> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_FUNCTION_INPUT_ITERATOR_HPP

/* function_input_iterator.hpp
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
*/