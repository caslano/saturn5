// Boost.Geometry Index
//
// Copyright (c) 2011-2016 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
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
    inline static bool apply(Geometry const& g1, Geometry const& g2, Strategy const&)
    {
        return geometry::equals(g1, g2, typename Strategy::within_point_point_strategy_type());
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
    inline static bool apply(Geometry const& g1, Geometry const& g2, Strategy const&)
    {
        // NOTE: there is no strategy for equals(box, box) so pass dummy variable
        // TODO: there should be a strategy even if it is the same for all CSes in case undefined_cs was used
        return geometry::equals(g1, g2, 0);
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
        return geometry::equals(g1, g2, s.get_relate_segment_segment_strategy());
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