// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_INDEXABLE_HPP

#include <boost/mpl/assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/index/detail/is_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
struct remove_cr
    : boost::remove_const
        <
            typename boost::remove_reference<T>::type
        >
{};

template <typename From, typename To>
struct is_referencable
    : boost::is_same
        <
            typename remove_cr<From>::type,
            typename remove_cr<To>::type
        >
{};

template <typename Indexable, typename V>
inline Indexable const& indexable_prevent_any_type(V const& )
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        UNEXPECTED_TYPE,
        (V)
    );
    return Indexable();
}

/*!
\brief The function object extracting Indexable from Value.

It translates Value object to Indexable object. The default version handles Values which are Indexables.
This template is also specialized for std::pair<Indexable, T2>, boost::tuple<Indexable, ...>
and std::tuple<Indexable, ...>.

\tparam Value       The Value type which may be translated directly to the Indexable.
\tparam IsIndexable If true, the const reference to Value is returned.
*/
template <typename Value, bool IsIndexable = is_indexable<Value>::value>
struct indexable
{
    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Value>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Value)
    );

    /*! \brief The type of result returned by function object. */
    typedef Value const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(Value const& v) const
    {
        return v;
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Value>(v);
    }
};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from std::pair<Indexable, T2>.

\tparam Indexable       The Indexable type.
\tparam Second          The second type.
*/
template <typename Indexable, typename Second>
struct indexable<std::pair<Indexable, Second>, false>
{
    typedef std::pair<Indexable, Second> value_type;

    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Indexable>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Indexable)
    );

    /*! \brief The type of result returned by function object. */
    typedef Indexable const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(value_type const& v) const
    {
        return v.first;
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename S>
    inline result_type operator()(std::pair<I, S> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (std::pair<I, S>)
        );
        return v.first;
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Indexable>(v);
    }
};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from boost::tuple<Indexable, ...>
  or boost::tuples::cons<Indexable, ...>.

\tparam Value       The Value type.
\tparam Indexable   The Indexable type.
*/
template <typename Value, typename Indexable>
struct indexable_boost_tuple
{
    typedef Value value_type;

    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Indexable>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Indexable)
        );

    /*! \brief The type of result returned by function object. */
    typedef Indexable const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(value_type const& v) const
    {
        return boost::get<0>(v);
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename U1, typename U2, typename U3, typename U4,
              typename U5, typename U6, typename U7, typename U8, typename U9>
    inline result_type operator()(boost::tuple<I, U1, U2, U3, U4, U5, U6, U7, U8, U9> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (boost::tuple<I, U1, U2, U3, U4, U5, U6, U7, U8, U9>)
        );
        return boost::get<0>(v);
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename T>
    inline result_type operator()(boost::tuples::cons<I, T> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (boost::tuples::cons<I, T>)
        );
        return boost::get<0>(v);
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Indexable>(v);
    }
};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from boost::tuple<Indexable, ...>.

\tparam Indexable   The Indexable type.
*/
template <typename Indexable, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
struct indexable<boost::tuple<Indexable, T1, T2, T3, T4, T5, T6, T7, T8, T9>, false>
    : indexable_boost_tuple
        <
            boost::tuple<Indexable, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
            Indexable
        >
{};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from boost::tuples::cons<Indexable, ...>.

\tparam Indexable   The Indexable type.
*/
template <typename Indexable, typename Tail>
struct indexable<boost::tuples::cons<Indexable, Tail>, false>
    : indexable_boost_tuple
        <
            boost::tuples::cons<Indexable, Tail>,
            Indexable
        >
{};

}}}} // namespace boost::geometry::index::detail

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <tuple>

namespace boost { namespace geometry { namespace index { namespace detail {

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from std::tuple<Indexable, Args...>.
It's defined if the compiler supports tuples and variadic templates.

\tparam Indexable   The Indexable type.
*/
template <typename Indexable, typename ...Args>
struct indexable<std::tuple<Indexable, Args...>, false>
{
    typedef std::tuple<Indexable, Args...> value_type;

    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Indexable>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Indexable)
        );

    /*! \brief The type of result returned by function object. */
    typedef Indexable const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    result_type operator()(value_type const& v) const
    {
        return std::get<0>(v);
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename ...A>
    inline result_type operator()(std::tuple<I, A...> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (std::tuple<I, A...>)
        );
        return std::get<0>(v);
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Indexable>(v);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

namespace boost { namespace geometry { namespace index {

/*!
\brief The function object extracting Indexable from Value.

It translates Value object to Indexable object. By default, it can handle Values which are Indexables,
std::pair<Indexable, T2>, boost::tuple<Indexable, ...> and std::tuple<Indexable, ...> if STD tuples
and variadic templates are supported.

\tparam Value       The Value type which may be translated directly to the Indexable.
*/
template <typename Value>
struct indexable
    : detail::indexable<Value>
{
    /*! \brief The type of result returned by function object. It should be const Indexable reference. */
    typedef typename detail::indexable<Value>::result_type result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(Value const& v) const
    {
        return detail::indexable<Value>::operator()(v);
    }

    /*!
    \brief Return indexable extracted from the value. Overload for types
           compatible with Value but different yet holding referencable
           Indexable, e.g. tuple containing a reference.

    \param v The value.
    \return The indexable.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return detail::indexable<Value>::operator()(v);
    }
};

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_INDEXABLE_HPP

/* indexable.hpp
9dlO4CR9tQn1LwjAGzhBE+bWJXEXq84d+6g4CrKhV7IftSkP56y1vALFF3DIVLKveIU7OQqyub8635+mtvJGEDGQ0Qrnq/rRRrxyoPXSWKaHiX+CBHB75ZiHE5AH8V6END2QM4jII1kshMuw21TdOvX8fUTom41ywIeYt33VRIYRlgNMPig4kfal1lPaBTbit1RAThHKeh8PANxO0Cx4hYM+YYvfLZKq/uZZI6mX9fhhkMw26rhvv4PNORbfISTh64mgqn30320+psTAkzmV4hrBMRXL6WLitSw6C+IrY3jGQ8E6FBhHqNwTJuRKnLfkvPNBT06sFlPuR8g0Xy75OUrtzbR0NWib9l1s5W3VB+YFMaBkKvV6b/hsGWQwUwkhQPa2+ocZYoqPpCb5GIrmz27uPQ4jBbE/RHLCV2c3qgEOCBOp4aIUV7o+3b7gTnIA5KpEV+CvomzJ0gls2idY3ZAvpRG1+f+T7kMEWA7yJ4sfc5Nf1IFRWpIx7bx8qf/rdCerobIgODiXuDqYx1isw/vR30Xm8/WTNln6qAmnGUwl11KR5eN1c7Z0aQ==
*/