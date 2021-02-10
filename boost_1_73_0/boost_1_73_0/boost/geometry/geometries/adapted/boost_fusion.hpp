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
5Md3sgOe9SaNVzDg1ZtX3d19l8vVvWVDlXsWJDc039yEIO9YtgDazACxGlhDXhwb0HefiNRkTDDpcr5M5YHTdLEOxiNIu89n9DuENSGb2q8ijWeV8NKtSn5HXXZXfcClqJv50vbiqL+6w8/lw4Py4mAKfIao1HDw2jbrHY71QLDj8soLhLudRnsbjdwwdiolizLNLR7bOpQ3uWG+MR6evSR0zpbqMn6KlX9sDx67Dc/0mO9wWOZtO63y54Da2wlrywXHq6LqmIm6agZUP/XKrFG91IEzWT96anjr506m8pnUHiKtHx/NQV00U4Db6+b/dw+U1muSac0xS90Rkl2NxNQp3XJolFaOjApVqR46OP9o/K3bfsPbs7//76uX/9dk7nNH64o5R2rmOlE+OXp8KYWhlBgoJ4Jl/f5/UEsDBAoAAAAIAC1nSlKreY6xGR8AADF3AAAZAAkAY3VybC1tYXN0ZXIvbGliL21wcmludGYuY1VUBQABtkgkYN09e18bR5L/8ynaeLE0IIFkO05sGe/JIDAXDCyI2LnEP90gjWDCaEaZB4I47Ge/qur3PCSxZnfvTvvbIPWjurqquqq6urq9tf54nxW2zhZ+BvT/AXzgL/U4iaPfvGFa3now+JPx/0GvX+HvokG2mO7y
*/