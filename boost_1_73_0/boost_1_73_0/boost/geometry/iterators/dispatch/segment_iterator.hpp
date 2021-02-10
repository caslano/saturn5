// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for segments_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_begin
    : not_implemented<Geometry>
{};



// dispatch for segments_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
b1tDRy/EPTuB4Xp8ZSEVsMQcsFlmUH9Fy3V6A9hSUU4B8wS3u5Eyx3IhLLI1eBRmqXBGhQSStNWVH1eE6ntPOR754dVH0O5b0fWDtIfbfmtaDqNYI80aA8fVoGbcUmthVKUxPP2/ggr/fUjhXqDwJEBQxwOi1+tpKLidsi0myPU3QqitMKcM0xRsK1RTtVQ4GenYDETgdSvMd1cGrqoRh6PhWW2P4IEiTYJo8Vgs3OrDNovQUnp6d2y7PzWf3Tf+SQCN21kHyKuuu7kXiLbIG6NtQNKBylXeXxZrUHaAP9tUUaAX67NDt3Zy4V0uCyxsqAKJIGRpwIfPBb7gJanJh6EtS516xtBYZCVNqlAg5OwngD4zS5sn5Pid1dUD7TgSpG0xHVOdRPUuHWOiP1diPKiCHNZmZQG/49KHtRrQYCTd6gV5soRMt2hdFNgpRmF1sGs0D3U/WItWOPmkBct0t4tJ9obNMk5kq1WrQN/Y5FX1uVkeASv6+XNrEy2tIuzH62SOict0EpAyNbdMNqN9UZt95nXA9mnUPh+N89lNDJrBTliGlsg9KhFG5TpMzOrcNLLfqsd2WWIYW1oRnkNi/0UbELa6ekKfZdvTSBXOQaL6+KciB8l1U90imEpIgHmWr5MQYz8ib1DCSlLE
*/