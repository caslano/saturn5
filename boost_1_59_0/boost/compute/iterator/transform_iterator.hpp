//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_TRANSFORM_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_TRANSFORM_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/iterator/detail/get_base_iterator_buffer.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {

// forward declaration for transform_iterator
template<class InputIterator, class UnaryFunction>
class transform_iterator;

namespace detail {

// meta-function returning the value_type for a transform_iterator
template<class InputIterator, class UnaryFunction>
struct make_transform_iterator_value_type
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    typedef typename boost::compute::result_of<UnaryFunction(value_type)>::type type;
};

// helper class which defines the iterator_adaptor super-class
// type for transform_iterator
template<class InputIterator, class UnaryFunction>
class transform_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        ::boost::compute::transform_iterator<InputIterator, UnaryFunction>,
        InputIterator,
        typename make_transform_iterator_value_type<InputIterator, UnaryFunction>::type,
        typename std::iterator_traits<InputIterator>::iterator_category,
        typename make_transform_iterator_value_type<InputIterator, UnaryFunction>::type
    > type;
};

template<class InputIterator, class UnaryFunction, class IndexExpr>
struct transform_iterator_index_expr
{
    typedef typename
        make_transform_iterator_value_type<
            InputIterator,
            UnaryFunction
        >::type result_type;

    transform_iterator_index_expr(const InputIterator &input_iter,
                                  const UnaryFunction &transform_expr,
                                  const IndexExpr &index_expr)
        : m_input_iter(input_iter),
          m_transform_expr(transform_expr),
          m_index_expr(index_expr)
    {
    }

    const InputIterator m_input_iter;
    const UnaryFunction m_transform_expr;
    const IndexExpr m_index_expr;
};

template<class InputIterator, class UnaryFunction, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const transform_iterator_index_expr<InputIterator,
                                                                   UnaryFunction,
                                                                   IndexExpr> &expr)
{
    return kernel << expr.m_transform_expr(expr.m_input_iter[expr.m_index_expr]);
}

} // end detail namespace

/// \class transform_iterator
/// \brief A transform iterator adaptor.
///
/// The transform_iterator adaptor applies a unary function to each element
/// produced from the underlying iterator when dereferenced.
///
/// For example, to copy from an input range to an output range while taking
/// the absolute value of each element:
///
/// \snippet test/test_transform_iterator.cpp copy_abs
///
/// \see buffer_iterator, make_transform_iterator()
template<class InputIterator, class UnaryFunction>
class transform_iterator :
    public detail::transform_iterator_base<InputIterator, UnaryFunction>::type
{
public:
    typedef typename
        detail::transform_iterator_base<InputIterator,
                                        UnaryFunction>::type super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;
    typedef UnaryFunction unary_function;

    transform_iterator(InputIterator iterator, UnaryFunction transform)
        : super_type(iterator),
          m_transform(transform)
    {
    }

    transform_iterator(const transform_iterator<InputIterator,
                                                UnaryFunction> &other)
        : super_type(other.base()),
          m_transform(other.m_transform)
    {
    }

    transform_iterator<InputIterator, UnaryFunction>&
    operator=(const transform_iterator<InputIterator,
                                       UnaryFunction> &other)
    {
        if(this != &other){
            super_type::operator=(other);

            m_transform = other.m_transform;
        }

        return *this;
    }

    ~transform_iterator()
    {
    }

    size_t get_index() const
    {
        return super_type::base().get_index();
    }

    const buffer& get_buffer() const
    {
        return detail::get_base_iterator_buffer(*this);
    }

    template<class IndexExpression>
    detail::transform_iterator_index_expr<InputIterator, UnaryFunction, IndexExpression>
    operator[](const IndexExpression &expr) const
    {
        return detail::transform_iterator_index_expr<InputIterator,
                                                     UnaryFunction,
                                                     IndexExpression>(super_type::base(),
                                                                      m_transform,
                                                                      expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        const context &context = super_type::base().get_buffer().get_context();
        command_queue queue(context, context.get_device());

        detail::meta_kernel k("read");
        size_t output_arg = k.add_arg<value_type *>(memory_object::global_memory, "output");
        k << "*output = " << m_transform(super_type::base()[k.lit(0)]) << ";";

        kernel kernel = k.compile(context);

        buffer output_buffer(context, sizeof(value_type));

        kernel.set_arg(output_arg, output_buffer);

        queue.enqueue_task(kernel);

        return detail::read_single_value<value_type>(output_buffer, queue);
    }

private:
    UnaryFunction m_transform;
};

/// Returns a transform_iterator for \p iterator with \p transform.
///
/// \param iterator the underlying iterator
/// \param transform the unary transform function
///
/// \return a \c transform_iterator for \p iterator with \p transform
///
/// For example, to create an iterator which returns the square-root of each
/// value in a \c vector<int>:
/// \code
/// auto sqrt_iterator = make_transform_iterator(vec.begin(), sqrt<int>());
/// \endcode
template<class InputIterator, class UnaryFunction>
inline transform_iterator<InputIterator, UnaryFunction>
make_transform_iterator(InputIterator iterator, UnaryFunction transform)
{
    return transform_iterator<InputIterator,
                              UnaryFunction>(iterator, transform);
}

/// \internal_ (is_device_iterator specialization for transform_iterator)
template<class InputIterator, class UnaryFunction>
struct is_device_iterator<
    transform_iterator<InputIterator, UnaryFunction> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_TRANSFORM_ITERATOR_HPP

/* transform_iterator.hpp
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
*/