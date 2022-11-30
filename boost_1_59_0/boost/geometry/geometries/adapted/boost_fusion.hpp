// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2015 Akira Takahashi
// Copyright (c) 2011-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP


#include <cstddef>
#include <type_traits>

#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/tag_of.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/mpl.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/size.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace fusion_adapt_detail
{

template <class Sequence>
struct all_same :
    std::integral_constant
        <
            bool,
            boost::mpl::count_if<
                Sequence,
                boost::is_same<
                    typename boost::mpl::front<Sequence>::type,
                    boost::mpl::_
                >
            >::value == boost::mpl::size<Sequence>::value
        >
{};

template <class Sequence>
struct is_coordinate_size
    : std::integral_constant
        <
            bool,
            (boost::fusion::result_of::size<Sequence>::value == 2
          || boost::fusion::result_of::size<Sequence>::value == 3)
        >
{};

template
<
    typename Sequence,
    bool IsSequence = boost::fusion::traits::is_sequence<Sequence>::value
>
struct is_fusion_sequence
    : std::integral_constant
        <
            bool,
            (fusion_adapt_detail::is_coordinate_size<Sequence>::value
          && fusion_adapt_detail::all_same<Sequence>::value)
        >
{};

template<typename Sequence>
struct is_fusion_sequence<Sequence, false>
    : std::false_type
{};


} // namespace fusion_adapt_detail


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

// Boost Fusion Sequence, 2D or 3D
template <typename Sequence>
struct coordinate_type
    <
        Sequence,
        std::enable_if_t
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>::value
            >
    >
{
    typedef typename boost::mpl::front<Sequence>::type type;
};


template <typename Sequence>
struct dimension
    <
        Sequence,
        std::enable_if_t
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>::value
            >
    > : boost::mpl::size<Sequence>
{};


template <typename Sequence, std::size_t Dimension>
struct access
    <
        Sequence,
        Dimension,
        std::enable_if_t
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>::value
            >
    >
{
    typedef typename coordinate_type<Sequence>::type ctype;

    static inline ctype get(Sequence const& point)
    {
        return boost::fusion::at_c<Dimension>(point);
    }

    template <class CoordinateType>
    static inline void set(Sequence& point, CoordinateType const& value)
    {
        boost::fusion::at_c<Dimension>(point) = value;
    }
};


template <typename Sequence>
struct tag
    <
        Sequence,
        std::enable_if_t
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>::value
            >
    >
{
    typedef point_tag type;
};


} // namespace traits

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


// Convenience registration macro to bind a Fusion sequence to a CS
#define BOOST_GEOMETRY_REGISTER_BOOST_FUSION_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <typename Sequence> \
    struct coordinate_system \
               < \
                   Sequence, \
                   std::enable_if_t \
                       < \
                           fusion_adapt_detail::is_fusion_sequence<Sequence>::value \
                       > \
               > \
    { typedef CoordinateSystem type; }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP

/* boost_fusion.hpp
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
*/