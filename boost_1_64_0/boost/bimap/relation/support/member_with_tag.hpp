// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/member_with_tag.hpp
/// \brief member_with_tag<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

/** \struct boost::bimaps::relation::support::member_with_tag

\brief Metafunction to convert user tags to the member_at idiom.

\code

template< class Tag, class Relation >
struct member_with_tag
{
    typedef member_at::{side} type;
};

\endcode

We have to allow that all the metafunctions that works with tags
and retrieves data from a Relation will work with member_at idiom
even if the type was tagged. This will be great for the user,
because he can choose to tag a member after he is using the
relation and the code will still work.

If we perform this check in every metafunction it will be very
tedious and error prone, so instead of that all metafunctions
that works with relations first call this metafunction that
convert the tag to a member_at tag.

See also member_at, is_tag_of_member_at_left, is_tag_of_member_at_right.
\ingroup relation_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct member_with_tag
{
    BOOST_BIMAP_STATIC_ERROR( MEMBER_WITH_TAG_FAILURE, (Relation,Tag) );
};

template< class Relation >
struct member_with_tag
<
    member_at::left, Relation, void
>
{
    typedef member_at::left type;
};

template< class Relation >
struct member_with_tag
<
    member_at::right, Relation, void
>
{
    typedef member_at::right type;
};

template< class Relation >
struct member_with_tag
<
    member_at::info, Relation, void
>
{
    typedef member_at::info type;
};


template< class Tag, class Relation >
struct member_with_tag
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::left> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::left_tag
            >
        >

    >::type
>
{
    typedef member_at::left type;
};

template< class Tag, class Relation >
struct member_with_tag
<
    Tag,
    Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::right> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::right_tag
            >
        >

    >::type
>
{
    typedef member_at::right type;
};

template< class Tag, class Relation >
struct member_with_tag
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::info> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::info_tag
            >
        >

    >::type
>
{
    typedef member_at::info type;
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP



/* member_with_tag.hpp
X+LUvD1Xy+YBX95GvkMElk0N45XN98Q91Fc2icVXNn8nx3toPmt4WzbVf4Oy+RvxMyCcl4Q5FWWT80aVTU1Lg/xbn2lke1Lz7x7kAPEWPO7Pv7N8dTu4fM6XMNebK73yqfF01/Xso96V9bhn7zhP3DczVjYlVh235fJS8Xe7WeeVS42rU2huYs3L6tymjR2ILpvefAKkO6K+Fx2nvh9tb2R7T/P0Dc3TQU9E5Glgfc/W/Jwl/p+T+v6AzVONR+s8aYuu89ZPd5Ot+Tpd3N+SOr8ruN7b8f0Xif/vSb1/2stjjbdr2M6UvD3xfM62+fzR2oDCDka2PZrf2zW/S3dH5rfXBgSX4XUS5lOmxua3xmPLcNS3hR73yvC14t5krrZlWMM0KMNXi787zSe8/CWuU1mGvXahKHa7YL8dBmUb2abqu8dEE1LgFn3Zy9Oob5rgtlXDFUi5myjH/cGs/Zb6C/dfHfddZXLQdefqdU+Ufb5zNfx2O83ItlSvsxxp6767+q4z6hspoPxMdjQcsQ00GUE2auqnfVOv8bj31tqNNWiH0nOMbOF4hyNuYSx40rs2+10VfO/U/4jG1ltQP63lXTmDPN2GXCB90H2MjF3R/XvD+1M7pqSlJ+U25z25YZuREXt9A9suvJET3b9wLf43+q/f/x0XnAcaJt1Xn71g2g7gp3l9DFHXY+ukjTvifu7tqJOjaFkdjawijm3+67HfWUFlVP0TS2+9ngniR4Opv/bG89ftJJTVcBs/QfbpuRp8467ONbKF27iB+t1mnrLXZ+thxBdc8Deuhh0k32v15F9BrnyvURbSTvd/r33UPozBmva31Riv1sEvXAI/wG+BTbtVjwQ+7xeL36lOZ/5OQ/QaNI4+Eu5QtA5Ej/fSvm5jysR9odPFJJoipEHfun2/fVH8vRndj662tnfJ8TYo1loG95erne3F4neA059cKUXayH5mK9oTWiMlVl95AZwn4WYH9pUXuSHEz/jj9pV3kXO1PmFdRKM2vDp2YM0eOxeVuOU67ViC4Laa+xe1ho4dX+M9m3WfzYuI9VHWdom9bkve001ftyXv6ZO3bkvY5ntW1+h0vYffgoh0VS2vEnVBKG1PRKdN/WdL27RAjrv+F61YtsBX5hukf3Yz0v+ETb83xmmB7LPnicjvvG6x16Mpfbrp69GI3+D1aDh+atejOQp3nsT1U2LbWzd/HqoA++YA++nm2223XOfuv3nqRa8Pa9N73Jd/cUXHLW9d2T3I7jzIDrv581w11/6+sXVVio1s8t50BE7UNVbyHLvGiv1dpX4ScK/S3z9EPu/zc4vu7+54a7KIDYHaIRxpsKbKWbpmyWCYBYfAHHW/D1cb1cOrjcARfeeq1PArnZBN+Wo4Fl4NS+E1cCm8Dq6EH4cPEP4T8DF4PXzcCfn/GlwPvwE/DX8Ib4Bqe6w6Relb4/yRtsenq417b3iaunPVhn2A2rCPVxv2S2A+rIL94fVwgLWRVt0eSI+RT+/qeX4NW6htdRo87LfRbiT8yxr+Oxr+FQ1/wBc+r5Hwv9fwRzT8exr+fbs2DaLhkzS833Z6n4b/JkyE39Jw5UiBhuur4fxjCA5puB/CZPi6nvdHsKPaRHeFv1Sb5Z/CXuo+XW2h+4jbS2ddI+lsoTbeqTARtnS8cBs1XHKMcN/XdB6ESfBV/1r8jZyvk56vs56vi+98OzVcYoxwX9PzvQgT4Nd9a+fUa7gpGs6/ds4HGu6Pmo8far37O+ygNvMT1V0Ij8HJ6tb6oDoC7lGM+nCabw2iPJjrG4sxTsdiTIA9NN5ucDrMg3N0v5ZH7Vsn7hjl8Sb8dYcb4TD4eTgSbrLp1L5keGuMdBY=
*/