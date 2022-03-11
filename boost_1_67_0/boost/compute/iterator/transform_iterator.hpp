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