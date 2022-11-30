//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_ZIP_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_ZIP_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/mpl_vector_to_tuple.hpp>
#include <boost/compute/types/tuple.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {

// forward declaration for zip_iterator
template<class IteratorTuple>
class zip_iterator;

namespace detail {

namespace mpl = boost::mpl;

// meta-function returning the value_type for an iterator
template<class Iterator>
struct make_iterator_value_type
{
    typedef typename std::iterator_traits<Iterator>::value_type type;
};

// meta-function returning the value_type for a zip_iterator
template<class IteratorTuple>
struct make_zip_iterator_value_type
{
    typedef typename
        detail::mpl_vector_to_tuple<
            typename mpl::transform<
                IteratorTuple,
                make_iterator_value_type<mpl::_1>,
                mpl::back_inserter<mpl::vector<> >
            >::type
        >::type type;
};

// helper class which defines the iterator_facade super-class
// type for zip_iterator
template<class IteratorTuple>
class zip_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::zip_iterator<IteratorTuple>,
        typename make_zip_iterator_value_type<IteratorTuple>::type,
        ::std::random_access_iterator_tag,
        typename make_zip_iterator_value_type<IteratorTuple>::type
    > type;
};

template<class IteratorTuple, class IndexExpr>
struct zip_iterator_index_expr
{
    typedef typename
        make_zip_iterator_value_type<IteratorTuple>::type
        result_type;

    zip_iterator_index_expr(const IteratorTuple &iterators,
                            const IndexExpr &index_expr)
        : m_iterators(iterators),
          m_index_expr(index_expr)
    {
    }

    const IteratorTuple m_iterators;
    const IndexExpr m_index_expr;
};

/// \internal_
#define BOOST_COMPUTE_PRINT_ELEM(z, n, unused)                                 \
        BOOST_PP_EXPR_IF(n, << ", ")                                           \
        << boost::get<n>(expr.m_iterators)[expr.m_index_expr]

/// \internal_
#define BOOST_COMPUTE_PRINT_ZIP_IDX(z, n, unused)                              \
template<BOOST_PP_ENUM_PARAMS(n, class Iterator), class IndexExpr>             \
inline meta_kernel& operator<<(                                                \
        meta_kernel &kernel,                                                   \
        const zip_iterator_index_expr<                                         \
                  boost::tuple<BOOST_PP_ENUM_PARAMS(n, Iterator)>,             \
                  IndexExpr                                                    \
              > &expr)                                                         \
{                                                                              \
    typedef typename                                                           \
        boost::tuple<BOOST_PP_ENUM_PARAMS(n, Iterator)>                        \
        tuple_type;                                                            \
    typedef typename                                                           \
        make_zip_iterator_value_type<tuple_type>::type                         \
        value_type;                                                            \
    kernel.inject_type<value_type>();                                          \
    return kernel                                                              \
        << "(" << type_name<value_type>() << ")"                               \
        << "{ "                                                                \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_PRINT_ELEM, ~)                        \
        << "}";                                                                \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_PRINT_ZIP_IDX, ~)

#undef BOOST_COMPUTE_PRINT_ZIP_IDX
#undef BOOST_COMPUTE_PRINT_ELEM

struct iterator_advancer
{
    iterator_advancer(size_t n)
        : m_distance(n)
    {
    }

    template<class Iterator>
    void operator()(Iterator &i) const
    {
        std::advance(i, m_distance);
    }

    size_t m_distance;
};

template<class Iterator>
void increment_iterator(Iterator &i)
{
    i++;
}

template<class Iterator>
void decrement_iterator(Iterator &i)
{
    i--;
}

} // end detail namespace

/// \class zip_iterator
/// \brief A zip iterator adaptor.
///
/// The zip_iterator class combines values from multiple input iterators. When
/// dereferenced it returns a tuple containing each value at the current
/// position in each input range.
///
/// \see make_zip_iterator()
template<class IteratorTuple>
class zip_iterator : public detail::zip_iterator_base<IteratorTuple>::type
{
public:
    typedef typename
        detail::zip_iterator_base<IteratorTuple>::type
        super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;
    typedef IteratorTuple iterator_tuple;

    zip_iterator(IteratorTuple iterators)
        : m_iterators(iterators)
    {
    }

    zip_iterator(const zip_iterator<IteratorTuple> &other)
        : m_iterators(other.m_iterators)
    {
    }

    zip_iterator<IteratorTuple>&
    operator=(const zip_iterator<IteratorTuple> &other)
    {
        if(this != &other){
            super_type::operator=(other);

            m_iterators = other.m_iterators;
        }

        return *this;
    }

    ~zip_iterator()
    {
    }

    const IteratorTuple& get_iterator_tuple() const
    {
        return m_iterators;
    }

    template<class IndexExpression>
    detail::zip_iterator_index_expr<IteratorTuple, IndexExpression>
    operator[](const IndexExpression &expr) const
    {
        return detail::zip_iterator_index_expr<IteratorTuple,
                                               IndexExpression>(m_iterators,
                                                                expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

    bool equal(const zip_iterator<IteratorTuple> &other) const
    {
        return m_iterators == other.m_iterators;
    }

    void increment()
    {
        boost::fusion::for_each(m_iterators, detail::increment_iterator);
    }

    void decrement()
    {
        boost::fusion::for_each(m_iterators, detail::decrement_iterator);
    }

    void advance(difference_type n)
    {
        boost::fusion::for_each(m_iterators, detail::iterator_advancer(n));
    }

    difference_type distance_to(const zip_iterator<IteratorTuple> &other) const
    {
        return std::distance(boost::get<0>(m_iterators),
                             boost::get<0>(other.m_iterators));
    }

private:
    IteratorTuple m_iterators;
};

/// Creates a zip_iterator for \p iterators.
///
/// \param iterators a tuple of input iterators to zip together
///
/// \return a \c zip_iterator for \p iterators
///
/// For example, to zip together iterators from three vectors (\c a, \c b, and
/// \p c):
/// \code
/// auto zipped = boost::compute::make_zip_iterator(
///     boost::make_tuple(a.begin(), b.begin(), c.begin())
/// );
/// \endcode
template<class IteratorTuple>
inline zip_iterator<IteratorTuple>
make_zip_iterator(IteratorTuple iterators)
{
    return zip_iterator<IteratorTuple>(iterators);
}

/// \internal_ (is_device_iterator specialization for zip_iterator)
template<class IteratorTuple>
struct is_device_iterator<zip_iterator<IteratorTuple> > : boost::true_type {};

namespace detail {

// get<N>() specialization for zip_iterator
/// \internal_
#define BOOST_COMPUTE_ZIP_GET_N(z, n, unused)                                  \
template<size_t N, class IteratorTuple, class IndexExpr,                       \
    BOOST_PP_ENUM_PARAMS(n, class T)>                                          \
inline meta_kernel&                                                            \
operator<<(meta_kernel &kernel,                                                \
           const invoked_get<                                                  \
               N,                                                              \
               zip_iterator_index_expr<IteratorTuple, IndexExpr>,              \
               boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)>                        \
            > &expr)                                                           \
{                                                                              \
    typedef typename boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> Tuple;           \
    typedef typename boost::tuples::element<N, Tuple>::type T;                 \
    BOOST_STATIC_ASSERT(N < size_t(boost::tuples::length<Tuple>::value));      \
    kernel.inject_type<T>();                                                   \
    return kernel                                                              \
        << boost::get<N>(expr.m_arg.m_iterators)[expr.m_arg.m_index_expr];     \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_ZIP_GET_N, ~)

#undef BOOST_COMPUTE_ZIP_GET_N

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_ZIP_ITERATOR_HPP

/* zip_iterator.hpp
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
*/