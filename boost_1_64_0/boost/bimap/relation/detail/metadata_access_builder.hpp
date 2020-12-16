// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/metadata_access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_DETAIL_METADATA_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_DETAIL_METADATA_ACCESS_BUILDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/is_tag_of_member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>



/******************************************************************************
              BIMAP SYMMETRIC METADATA ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SymmetricType >
struct NAME
{
    typedef -unspecified- type;
};

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER(                        \
                                                                              \
        NAME,                                                                 \
        METADATA_BY_LEFT,                                                     \
        METADATA_BY_RIGHT                                                     \
    )                                                                         \
                                                                              \
    template                                                                  \
    <                                                                         \
        class Tag,                                                            \
        class SymmetricType,                                                  \
        class Enable = void                                                   \
    >                                                                         \
    struct NAME                                                               \
    {                                                                         \
        BOOST_BIMAP_STATIC_ERROR(                                             \
            BOOST_PP_CAT(NAME,_FAILURE),                                      \
            (SymmetricType,Tag)                                               \
        );                                                                    \
    };                                                                        \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    <                                                                         \
        Tag, SymmetricType,                                                   \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_left      \
            <                                                                 \
                Tag,                                                          \
                SymmetricType                                                 \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME SymmetricType::METADATA_BY_LEFT type;  \
    };                                                                        \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    <                                                                         \
        Tag, SymmetricType,                                                   \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_right     \
            <                                                                 \
                Tag,                                                          \
                SymmetricType                                                 \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME SymmetricType::METADATA_BY_RIGHT type; \
    };
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_DETAIL_METADATA_ACCES_BUILDER_HPP



/* metadata_access_builder.hpp
/Jzmcqu+zvev7+N8/yh+Fl9QXHutRahzp9QHVJIb6lkVMUl9RH2T0umJcF+T/4+tehlPGkllzHXufirPGCVZOOSeDKtOuNa/NBYBcix3McWTq5Uh3SgKa6zb6epIdTnSRHjI93/hlM9EnhHW+x2gvGUgDw+76rtNL+cRqFr6OOJkCpen9ESpNFJuEhH8vK9Q2fVTbxV29qunYRF9KC8uvwqX83m1Cfwb0kmldPidLaawA5V6iC9LiZDP7UcK21mNh5z8ynuxozw78z3LOiLPBR2PsMfp3pZbeU8LjzGwxXBXdg5CMZ+DIOc6n6ow17mC+/RJT3f5SX0udIuT7vm9zeRYUVNdJseKEnSZHN+6SZfJ8a1IXZbuljl0mRzz+ukLKZNjXud0WYqcM33CLcuU8Q3TZTK+vrpMxtdJl8n4WktZhhxDS9VlWfJ+dZksl2hdJsul33E5b1zG11WX6WNyukzG11yXyfhSdZks5yRdJss5VpfJcgnTZbJcjn/mPdf9qC6T5VLOMuN46E5dJu9jmy6T97FOl8n7WK7L5H08pMv4PsLDy3yMN+7zMd54UI4V8u8sy4+ajEMek+OQ8jeS4j7pYxzyrMnc8fN1KLycs17fMDbpepezw5+nMsdvTKzLXX5CuuXY5Szlxo0h/kTyyx/udDw+497Ft7x/cVjR4ETcbFcaWzy9IG5Z413jL9977pmXZz9T+4/wrzjlxQfH3X/hbL03Dz3UrkbyZ1mvY08XGktd+/Sq9vdZtCttC5o/N/7T5sOuf4xyDY2ZftVs2IzxBSfmd/z51taTqlfDD9wTFH/HHgUxn+V9mxxQXOPYzMxLSPcOys/ZtrfWuLP+wgWvRecsDDh2BYN48xo75TE7pi24XDfv1QemdNl4/59eKMd6NJLf/qd7ngk7ErW6y+yTt429lPe0+VhwC/L/zj2H3vz5wqJv7/5N7eovLhhsc42NLlb4m4K/G4+CTWHnGM6KzAVrgd3BJuAsMBV8BEwDXwPbgZfADFBB2AFgHJjFY23Z4KtgS/ANMAfcC7YCG6qu8M3B9mALsAN4M9gRvIXHALqAnXgMszPYG+wDFoF9wQfBAWCx5tLl3wVmgLPA4eBcsIDHCmaDK8DR4A6wEOxkwdcN2A+cAOaBxeBQcCI4CpwEFoEl4FiwFJwIzgDngzPBdeBscKnVNfa0DFwAPg0uBMNQ9ovAeuDDYGdwKTgDfBTspqAOoVB2wZ6GrYFBk56ws2A3wx6DHQq5x15BsGEYb4iDzYAdCzsLdinsBtgyWNpPCOMQU2Dnwa6B3Qa7D/YYbNWmuA7bF3YEbCnsPh6vqIFximTYHNghsGN57OIw7GnYy7DBqQgP2xd2GuwC2F2wh2GPw34La0lDOrClsHNgV8BugN0FexhWpOM6bALsNB4HOQh7DPZbWEcG8gA7FnYxj42EZeK+YVNgh8IWw86CXQw7zz8+4jfXYH6d/n+zjBu1/9+xGCHXW2OMkgyaAJEI3gR2xe958Sd2Ifv/SFvXAJjqADhMaznvbj2531ZixTtynt09f3PKbhK+9AJdZRwt5bzZdeT+u+Ldj+f1FDJMrjIU8xljuN9wkGTlCPcwpNXEOdB3Px96AxlHinCvPV5B7kuKrzmsPXB9D11/SXkXIQy6AIrHPfe02O1G6T6O/undyli671K6b+p7y7Xdq8jfBcXY5+e4DOu7zfv6Rr+zPPvc8iy7TeTnQ+UIfL2Gc/Er9LflGXm1jjn9fY3r78hzDL6ksFWVDPG8z3mya+j6R8Yz+PQ57xSfTV+nS3UgmueEY14jXT+N678TL0Iu90zkPnqUYc/ETPIrlDhRJuUW2CEkP4834W3kmcpe1gE=
*/