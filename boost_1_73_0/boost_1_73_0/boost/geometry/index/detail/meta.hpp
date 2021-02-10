// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_META_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
struct is_range
    : ::boost::mpl::aux::has_type< ::boost::range_iterator<T> >
{};

//template <typename T, typename V, bool IsRange>
//struct is_range_of_convertible_values_impl
//    : ::boost::is_convertible<typename ::boost::range_value<T>::type, V>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values_impl<T, V, false>
//    : ::boost::mpl::bool_<false>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values
//    : is_range_of_convertible_values_impl<T, V, is_range<T>::value>
//{};

// Implemented this way in order to prevent instantiation of all type traits at
// once because some of them are causing problems with gcc 4.6 namely
// is_convertible<bg::model::segment<>, std::pair<bg::model::segment<>, T> >
// because segment<> is derived from pair<> and pair<> has copy ctor taking
// other pair<> of any types the compiler tries to instantiate ctor of
// pair<segment, T> taking pair<point, point> which results in instantiation of
// segment's ctor taking a point which results in compilation error.
// This is probably compiler's bug.
template <typename T, typename Value, typename Indexable, typename ResultType, int Ver>
struct convertible_type_impl
{
    typedef ResultType type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 0>
{
    typedef typename boost::mpl::if_c
        <
            boost::is_convertible<T, Indexable>::value,
            Indexable,
            void
        >::type result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 1
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 1>
{
    typedef typename boost::mpl::if_c
        <
            boost::is_convertible<T, Value>::value,
            Value,
            void
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type
{
    typedef typename boost::mpl::if_c
        <
            boost::is_same<T, Value>::value,
            Value,
            typename boost::mpl::if_c
                <
                    boost::is_same<T, Indexable>::value,
                    Indexable,
                    void
                >::type
        >::type result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 0
        >::type type;
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

/* meta.hpp
isCHljQVdnt9wwMjFefZtoJqC+dri4EqZgU+PzGc607wUhKfyap2bGBKzBqHTaHLDye7hvGnWM/5HNlfn5WM1uC4Z3ht+WbPMXcO0ewf+UoRPPyAAb/N2QVtR3bQAKEx1hq92d0/eH88jE1oDU5HXxr2eWl3UfHsvOKA/AljAy1wQC2OBRiRQj0l+o/8oWA4DeHHj7gHgiZXGEbDg94ND/ewsxcvXZhFGkSaoX/pY4rGe4w9UCgkZutLObdEOq1s5RoeVLF3UISbjNvxqjo5Em5OHTMNpb9h6z5hRREV0kE2pbReOKqIE/IJ7ntLI29RNwnpsM+IwpsqqViyFBO8gkj7NSnS7pfOLlkVXOenjCqygEjdy9BPmrv2gq1yMC6hH12acRT5fULekceSjvfJlS91N8/+04tjs7QicQUjJEnAeoxLemxTFLkkPRojRVTaZMsxOVC0FllbUkcqGA2fjial2GJ8wgvmPVKpDGPqqnEmFjp0gek5GfUw1XqQLKqrbqW4j9qcrS3RliZvJDe82nyJSYIB1f/2IvlpOHyH5/TzjtTPRKRfqkLmgS+G1xrk1Si+0uWhz1frCdcqUJgyFUxcMn7GZ2s65290BHfGD10ESMdbzXAWpMpohNSM8tppDYg/gg1Yo4pDxdEh
*/