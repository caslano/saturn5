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
rPqOv5nqb4sg/l5q+cLTWduDLlrPesIasBtsCHvApqpvyqf62zhI+Vyu6bBC4/03GAtXwTh4G6wKb9f24U54sZo79axY/e8YpJ49rv5vVP82abv+lKbvE7Aa3KL+PqnldivsoPa0XFK5fc8ZFKRc/kOfs1+fc0CfU6LPeVWf8xpsCg/CTvCQlts34EC1f1LrWp4+r6E+L1zjKG/69HlXwXBYoOVkLkxTuYHKTv9RrP6FBek/Gqt/TaAXNlV3Wajd6m6CuvOKPX3/oe3sKtgMroa94RroxKPLy6YdZ7wUGI/D+twPoBt+qOn3kcbniKbbx37hyfPzb5oVGJ7RET73Y2ASHAurqOyEZ626byfuA8PTX8OTDTPhYG0Xh8GW2t9nqXwSrkWdUP+SLJ9/CVJOfX/jPL5wTIZVVK6h8nyYCxfDK+FSOB3eBWfA1XA23AgL4A54NdwF58P9cAo8CHPgD7AQ/gGvheGW2DP5n73fF86aEu/A/B+v8Z6q/cR0jd9Z1EJ1d1jdVYffqTu325feYbAVjIBtYSPYQeUuMBp2V/3eKveHcXCQ6g9VeRSMh2NVf4LKOTAJ5sNkWKjmC1QuUvlGmAr/CtPhctW/TeW7YA24WfWLVd4OG8Idqn8SbkCtPOCL/1KNfyK8T+OfiT2bLeFFsDWsDyfABjALNlG5KewAW6rcCl4K26ncHnaFnVXuAgfBoSoPgyPhaJXHwPFwnMonYRdbveILbx0Nbxhs5dRXza+7YRJcC1PgQ7AmvEf9OY7KU3+ytVynS330/T2h/UgxrA6fgp3hDzpe+hEOgWf9xksFcD+8GR6Ad8NX4aPwIHwevgHfg2/Dr+Gn8BT8Gf6i/p2Hf4eRlm9cFg1t/Xi4DdaC22Fd1b8Y7oAd4LOwJ/wZ9lVzO74rURmv+eJ7m6ZbZbjEGQdgLxEWwbpwhY7b/wYv1XawJ7wX9tVxdDZcAqfBmzT+N8MFcCm8Xu0tgQ/Am1VepvJJrXNHNVw7NVxp8KCGa6rm5zR4CVyu5etKmKVyRzgTdlW5J8yDfVUeCPPhUJVHwqvhOJUnwmvhVJVz4QI4S+U58AZ4jcrz4SK4UOUl8EZ4C1wGb1X9k/AE8Sk56IvfErcvfna7cQzKO1rtDxbANjoe66Djse467uoDK2u5W4w8Wcdn03U8lg9vgoVq7zpIGkt6L4e36fhjjY4/HoYr4Xq1v1HHH8/AO+DfdRyyV80PwLuRP4H3Q7s8roMp8FFYG9r2GsDH7PDDx2EPuBH2h5vgYLU3Am5BHg+3whlwJyyCz8Jb4HNwhdq/Az6PvBrugmvhC/ARNd8An0Z+Am6D2+F2+JyavwgPIL8OX4HvwVfhR2p+FL6B/AP8FP4EXeiftQB0kW9u6IGVYSSMhVVhHOwEK8HOYq7tlO1HiS/fN2v7Us9upzTfU3V+VBVmwhowC9aEneA1sJuOY3ur3B82gTkwE+aq/izYEl4NW8H5qr8QdoVrYC+4GV4Gt6v5c7A/3AsHwAOqfwgOhT/AYfAMHAV/U3M7UiO0fbL1SQPRT4STYAacAlvAHNhWzTvCKyFhkecOggPgMDUfDefCsSo746GMt3zpGBlkfFZb+/U6UPp7GAFJa3GfgcpU96m+dll+J6v7Pp5Se9kVtJdXQXsrL2DvMj97xRW0V+Jn72gZe/384nuigvbi366YvcwL2JvkZy+7gvbyKmhvZQXsxZv7qul7tJ7VsssIlHu7on3jvZOwDjwFm8PTsC08C/vBP+AQeB6Oha4YX7vvhguhB94II+CtMBLeA6PhAzAOboSV4B6YAN+CifAoTIafwyrwR5gGf4fp8DysCe16lAGrwdqwBqwPW8EGsB1sCEc=
*/