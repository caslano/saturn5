// Boost.Geometry Index
//
// Copyright (c) 2011-2016 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_EQUAL_TO_HPP
#define BOOST_GEOMETRY_INDEX_EQUAL_TO_HPP

#include <boost/geometry/algorithms/detail/equals/interface.hpp>
#include <boost/geometry/index/indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail
{

template <typename Geometry,
          typename Tag = typename geometry::tag<Geometry>::type>
struct equals
{
    template <typename Strategy>
    inline static bool apply(Geometry const& g1, Geometry const& g2, Strategy const&)
    {
        return geometry::equals(g1, g2);
    }
};

template <typename Geometry>
struct equals<Geometry, point_tag>
{
    inline static bool apply(Geometry const& g1, Geometry const& g2, default_strategy const&)
    {
        return geometry::equals(g1, g2);
    }

    template <typename Strategy>
    inline static bool apply(Geometry const& g1, Geometry const& g2, Strategy const& s)
    {
        return geometry::equals(g1, g2, s);
    }
};

template <typename Geometry>
struct equals<Geometry, box_tag>
{
    inline static bool apply(Geometry const& g1, Geometry const& g2, default_strategy const&)
    {
        return geometry::equals(g1, g2);
    }

    template <typename Strategy>
    inline static bool apply(Geometry const& g1, Geometry const& g2, Strategy const& s)
    {
        return geometry::equals(g1, g2, s);
    }
};

template <typename Geometry>
struct equals<Geometry, segment_tag>
{
    inline static bool apply(Geometry const& g1, Geometry const& g2, default_strategy const&)
    {
        return geometry::equals(g1, g2);
    }

    template <typename Strategy>
    inline static bool apply(Geometry const& g1, Geometry const& g2, Strategy const& s)
    {
        return geometry::equals(g1, g2, s);
    }
};


template <typename Geometry, typename Tag>
struct equals<Geometry *, Tag>
{
    template <typename Strategy>
    inline static bool apply(const Geometry * g1, const Geometry * g2, Strategy const&)
    {
        return g1 == g2;
    }
};

template <typename T>
struct equals<T, void>
{
    template <typename Strategy>
    inline static bool apply(T const& v1, T const& v2, Strategy const&)
    {
        return v1 == v2;
    }
};

template <typename T>
struct equals<T *, void>
{
    template <typename Strategy>
    inline static bool apply(const T * v1, const T * v2, Strategy const&)
    {
        return v1 == v2;
    }
};

template <typename Tuple, size_t I, size_t N>
struct tuple_equals
{
    template <typename Strategy>
    inline static bool apply(Tuple const& t1, Tuple const& t2, Strategy const& strategy)
    {
        typedef typename boost::tuples::element<I, Tuple>::type T;

        return equals<T>::apply(boost::get<I>(t1), boost::get<I>(t2), strategy)
            && tuple_equals<Tuple, I + 1, N>::apply(t1, t2, strategy);
    }
};

template <typename Tuple, size_t I>
struct tuple_equals<Tuple, I, I>
{
    template <typename Strategy>
    inline static bool apply(Tuple const&, Tuple const&, Strategy const&)
    {
        return true;
    }
};

// TODO: Consider this: Since equal_to<> is using geometry::equals() it's possible that
//       two compared Indexables are not exactly the same! They will be spatially equal
//       but not strictly equal. Consider 2 Segments with reversed order of points.
//       Therefore it's possible that during the Value removal different value will be
//       removed than the one that was passed.

/*!
\brief The function object comparing Values.

It compares Geometries using geometry::equals() function. Other types are compared using operator==.
The default version handles Values which are Indexables.
This template is also specialized for std::pair<T1, T2> and boost::tuple<...>.

\tparam Value       The type of objects which are compared by this function object.
\tparam IsIndexable If true, Values are compared using boost::geometry::equals() functions.
*/
template <typename Value,
          bool IsIndexable = is_indexable<Value>::value>
struct equal_to
{
    /*! \brief The type of result returned by function object. */
    typedef bool result_type;
    
    /*!
    \brief Compare values. If Value is a Geometry geometry::equals() function is used.
    
    \param l First value.
    \param r Second value.
    \return true if values are equal.
    */
    template <typename Strategy>
    inline bool operator()(Value const& l, Value const& r, Strategy const& strategy) const
    {
        return detail::equals<Value>::apply(l, r, strategy);
    }
};

/*!
\brief The function object comparing Values.

This specialization compares values of type std::pair<T1, T2>.
It compares pairs' first values, then second values.

\tparam T1       The first type.
\tparam T2       The second type.
*/
template <typename T1, typename T2>
struct equal_to<std::pair<T1, T2>, false>
{
    /*! \brief The type of result returned by function object. */
    typedef bool result_type;

    /*!
    \brief Compare values. If pair<> Value member is a Geometry geometry::equals() function is used.
    
    \param l First value.
    \param r Second value.
    \return true if values are equal.
    */
    template <typename Strategy>
    inline bool operator()(std::pair<T1, T2> const& l, std::pair<T1, T2> const& r,
                           Strategy const& strategy) const
    {
        return detail::equals<T1>::apply(l.first, r.first, strategy)
            && detail::equals<T2>::apply(l.second, r.second, strategy);
    }
};

/*!
\brief The function object comparing Values.

This specialization compares values of type boost::tuple<...>.
It compares all members of the tuple from the first one to the last one.
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
struct equal_to<boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, false>
{
    typedef boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> value_type;

    /*! \brief The type of result returned by function object. */
    typedef bool result_type;

    /*!
    \brief Compare values. If tuple<> Value member is a Geometry geometry::equals() function is used.
    
    \param l First value.
    \param r Second value.
    \return true if values are equal.
    */
    template <typename Strategy>
    inline bool operator()(value_type const& l, value_type const& r,
                           Strategy const& strategy) const
    {
        return detail::tuple_equals<
            value_type, 0, boost::tuples::length<value_type>::value
        >::apply(l, r, strategy);
    }
};

}}}} // namespace boost::geometry::index::detail

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <tuple>

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Tuple, size_t I, size_t N>
struct std_tuple_equals
{
    template <typename Strategy>
    inline static bool apply(Tuple const& t1, Tuple const& t2, Strategy const& strategy)
    {
        typedef typename std::tuple_element<I, Tuple>::type T;

        return equals<T>::apply(std::get<I>(t1), std::get<I>(t2), strategy)
            && std_tuple_equals<Tuple, I + 1, N>::apply(t1, t2, strategy);
    }
};

template <typename Tuple, size_t I>
struct std_tuple_equals<Tuple, I, I>
{
    template <typename Strategy>
    inline static bool apply(Tuple const&, Tuple const&, Strategy const&)
    {
        return true;
    }
};

/*!
\brief The function object comparing Values.

This specialization compares values of type std::tuple<Args...>.
It's defined if the compiler supports tuples and variadic templates.
It compares all members of the tuple from the first one to the last one.
*/
template <typename ...Args>
struct equal_to<std::tuple<Args...>, false>
{
    typedef std::tuple<Args...> value_type;

    /*! \brief The type of result returned by function object. */
    typedef bool result_type;

    /*!
    \brief Compare values. If tuple<> Value member is a Geometry geometry::equals() function is used.
    
    \param l First value.
    \param r Second value.
    \return true if values are equal.
    */
    template <typename Strategy>
    bool operator()(value_type const& l, value_type const& r, Strategy const& strategy) const
    {
        return detail::std_tuple_equals<
            value_type, 0, std::tuple_size<value_type>::value
        >::apply(l, r, strategy);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

namespace boost { namespace geometry { namespace index {

/*!
\brief The function object comparing Values.

The default version handles Values which are Indexables, std::pair<T1, T2>, boost::tuple<...>
and std::tuple<...> if STD tuples and variadic templates are supported.
All members are compared from left to right, Geometries using boost::geometry::equals() function,
other types using operator==.

\tparam Value       The type of objects which are compared by this function object.
*/
template <typename Value>
struct equal_to
    : detail::equal_to<Value>
{
    /*! \brief The type of result returned by function object. */
    typedef typename detail::equal_to<Value>::result_type result_type;
    
    /*!
    \brief Compare Values.
    
    \param l First value.
    \param r Second value.
    \return true if Values are equal.
    */
    inline bool operator()(Value const& l, Value const& r) const
    {
        return detail::equal_to<Value>::operator()(l, r, default_strategy());
    }

    template <typename Strategy>
    inline bool operator()(Value const& l, Value const& r, Strategy const& strategy) const
    {
        return detail::equal_to<Value>::operator()(l, r, strategy);
    }
};

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_EQUAL_TO_HPP

/* equal_to.hpp
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
*/