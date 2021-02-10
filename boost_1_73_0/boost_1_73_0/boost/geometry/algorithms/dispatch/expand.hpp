// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_EXPAND_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_EXPAND_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename GeometryOut, typename Geometry,
    typename TagOut = typename tag<GeometryOut>::type,
    typename Tag = typename tag<Geometry>::type
>
struct expand : not_implemented<TagOut, Tag>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_EXPAND_HPP

/* expand.hpp
dyL+Aazf4buJySEpUL5bCmlG+U5aHMWSXI7xt2U1MfodZcM/h4j5u4U/4QygIeYoWjzF/v0sJa2RQrTBoE/2ia7qapuc0tBnAZmkLLRZfN8mxy4/888ZfXw8SNhJm7CU0OBAkprO/IQkkZc+0JgR+B34DgsT5hKaEJclTuzbcOCHJJ0x4vkBI6Prm0/jq/M2eZj5zgyJPEVLksyiZeCSGf3KSMwc5n8VNBY0TknkAToQd/0kBYLL1I/CA+DNSMrieYI0kD0NkojQr9QPqA2MaEpmabpI3hweOss4AOkP3chJDp1M/YNZOs81+QRCzOkTiRYpSSOyTFibIGSbzCPX9/AbDAInF0s78JNZu5AGWIXuYRSThAUB0gI8nyVCbEYm0jxtBCMLkNhP8SuJwgRZPcyieQUQ7IhUvGUcAiOwAwC5EZi5TZahy2IOzDXPWEibcgPXuqaQ1yVRCMKQV8MJGU9eEZsmftImH8fTi+u7Kfk4vL0dXk0/kev3ZHj1CYn9a3x1Cq73gVlM2OMiZgkwj4k/XwQ+cyXPH/c53Nn5yQ+dYOky8gq9ZyUsXS4OZq/wggdW8Mjo7vbSOh1Phu8uz6zR7aeb6bU1vJtelFCPEVV4f3ayRnLudpHgytnZnDrV02DAMACFM+7I/G5y
*/