// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2015 Akira Takahashi
// Copyright (c) 2011-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP


#include <cstddef>

#include <boost/core/enable_if.hpp>

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
#include <boost/type_traits/remove_reference.hpp>

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
    boost::mpl::bool_<
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
struct is_coordinate_size : boost::mpl::bool_<
            boost::fusion::result_of::size<Sequence>::value == 2 ||
            boost::fusion::result_of::size<Sequence>::value == 3> {};

template<typename Sequence>
struct is_fusion_sequence
    : boost::mpl::and_<boost::fusion::traits::is_sequence<Sequence>,
                fusion_adapt_detail::is_coordinate_size<Sequence>,
                fusion_adapt_detail::all_same<Sequence> >
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
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
    >
{
    typedef typename boost::mpl::front<Sequence>::type type;
};


template <typename Sequence>
struct dimension
    <
        Sequence,
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
    > : boost::mpl::size<Sequence>
{};


template <typename Sequence, std::size_t Dimension>
struct access
    <
        Sequence,
        Dimension,
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
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
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
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
                   typename boost::enable_if \
                       < \
                           fusion_adapt_detail::is_fusion_sequence<Sequence> \
                       >::type \
               > \
    { typedef CoordinateSystem type; }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP

/* boost_fusion.hpp
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
*/