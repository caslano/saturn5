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