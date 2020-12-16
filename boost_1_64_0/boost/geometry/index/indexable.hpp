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
w0tgLsyEM+Ev0YQXNkfWeaneJy1tNOkSOC+9AftxcCFsChfDOfAWuAoug2vgcvggLIIPqXxS5nF6FzNM1nS3x//71P+xhCMVToD14STYGE6BmTAHtoA3wp7wCpgDp8FZ8Eo4T+XrVL4JzoB3w5nwfnW3CeZD2d8Ln4OF8HV4LXwHzocfwxvgv+BC+DNcAsMtwmHSTe/zhZuCpFtfO1/gAJgFB8LZcDDMh8M1nCPgnXAkvAuOUv8Jo96Fix+abnaZ3qz+n4jyzW9PwUbwNMyEv8DO8Fc4CP4GZ8PfYQH0kC/XQy9cDsPgEzAcPgkj4X4YBd+D0fAsjIW/wjh4DjaGdn42gfVhU9gQNjP5rvfDwulB8v2FSN88cC9sZuvDlvBlOBT+Aw6Hx2AOPAAL4CvwWvgqvAe+BtfC12ExLIH74fvwfXgYnoAfQDv/PoRJ8CNYBR6BteAnsD58E/aBb8Fs+DYcBwmHzgf0vlLYP8h84GuN1/ewLfwBdoQ/wnHwBBwPa5IfM+FPyNfBU3ARPA1XwDNwJfwFPgx/hVvgbxrP83A3tPBnH3TDr2AV+ANMgydhOPwVRsHfYSy00yEORsHKsCpMgi1hCuwEa6r7heZuTblDVOJrtwMF2m5epOWvGewJW8HxsDWcAtvCv8J28B7YEW6CnWAx7Azfg13gx7AvPA/7Qa/d78N4OBCmwKGwPRwHu8Eptjs4DX4Jp8NEN/UeZsBZsB4sgA3h1XA0LIRXwGvhDDgfXgUXwMXwOrgcXg/vgjfA1XAhXAOL4CNwMdwBb4QvwpvgIXgz/BTeAr+CU+EP8HJ4Ag6H6aTnrbA2XAY7wuWwB1wBR8A7oY4T9a5EuWOy3DixCuWhCawPh8EGcDJsBK+ATbTeNINPwhZwJ2wJP4St4FHYGn4J28BvYFsYY5F/MAG2h6mwE2wHL4XdYGfYF3aFg2APOAP2hLfAXvBe2B8+DwfAPTAb/goHQ4t4DYNt4HDYDY6APeEo2B/2hnmwD7wajoU3wXFwFfwLfAKOhy/DiXA/vBxqOur9dORJkHTMxV4ynANbw6u1HboGjoTPaXrOgzPgfLgALoAPwevgI2pvCyyCh+Ai+BZcrOFYAn+BN8I/4FJol/e/wsZwJWwLb4Od4e2wP7wTLoWr4ePwHrgDroHPwvvgC/B+uB8+Bt+AG+An8HH4GdwMf4RPaLo/CSPhKtgEboW94FNwINwGx0DipesEekeazEXKrxPcHaXrKLA5vBf2gPfB0fB+OA0+AKfDR+CtcB18Cq6He+Gj8E34GHwbboSHYTE8DtfCWEtkXQfX+8rgjSjCFbAO/lG0b73mCGwHP4Wj4VF4JfwMzoGfwwL4FZwHv4Q3qHwSklZ61xhlQdtFe/3jHJT3iboOthW2g9ugbb4ddoPPwHEwhnH7JDgS5sJRcDocDZdA2hTpn1+Cz8OD8EP4BjwKS+BXKv8ID8Mwi/jBavAcbAR/hy2hC3+zoRcOh2FwNIyAU2AkvBJGwVkwGubDGLgSxsJVsBLcAivDrTAJ7oHJ8F2YAj+GqfBTmAa/hVWhXd7SYQKsCRvDWvASmAH7w4vgYNgUjobN4F9ga3g9zII3wzbwFtgO3gHbw7WwA9yu8g7YEe6F3eBbsDv8F+wBz8A+kLDKPKo+7AubwX6wJRwEh8FsOAUOhnlwOJT5p7kvir5c25W6vnm4/D0dpe9RYRu4Cw6FL8IFcA9cBPfCm+A+uAy+DNfC1+AGeEj7z4/g6/CI9psfwy/hJ/CfcL/WhwPa378KK8HXYG14CDaFr8OusARmwzeh2009gBHwe5gIbf2L4DuwBXwXjoBfwInwGJwJv4R3wq/gvfC49offwHfgt/A=
*/