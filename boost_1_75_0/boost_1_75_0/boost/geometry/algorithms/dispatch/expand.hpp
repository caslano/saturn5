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
e//z5y8JT+aq2VylNoVuZqrzVM+UeaXB3I27aa8nKvOamAnBKKXU8EtE1naJOo/boxbut3+dx/0RhdlI+7afaju0nB5msTW8uhZMcyGZOScknZYErh4MYUOb+oDzeuyTtsrsk3VQk5va9oiFCH9JjwD4T/liy6PpoCI6zNZwSVZDi/KbJ4K1TM1aPJOYg9xJVltVysY8uWp9J0msBBt7xKUZpiUc9ScJcig5JRzsfRA9jh3Y5Q4yyNjPQhbB9iJPo5VcoDaSW0ZMmcr24vpkegdKcOK9jedMj52h38DpnspoRuG59eAR5Hn8eLEe2zG41Bj17PELg8dPvupRw1xpNGqN3PEO+XiFVlm7qcqz1Q91fQxv/viViPUNsDXo2EtNezQZfsWD7wxS23ll6ltVfsc7581MMcpvpqdKLW1IgPSntDSi5xyTzQx5Q7XKfxTb8V4bvO0Gbx4vMzI1YmudoDY99aXa4W68DA71OFuJECm3cJdiiZla6eeVPFHU2Amo7Olx1ajWKUhJTxKM7sz+BtBWIkQ6jj9WvJRmvuhwwq7H4Vq2+lsniEdsi3RS5dqoCUfbm6XaDw3S8WxpFihJa3qUYVq/fbORw+j5tys2cPhK5RUV98mFbqYzaY3YP8XDgrY3CwaFDF6OCabpvTHs9tFIV37TKfCjZx2JuJP8RTlbHt+zzFoicz9QQtjObzsT3UqooG/uLBxnq+SY
*/