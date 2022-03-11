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