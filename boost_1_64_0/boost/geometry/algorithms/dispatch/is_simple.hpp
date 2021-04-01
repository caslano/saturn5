// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP

#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_simple
    : not_implemented<Geometry>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP

/* is_simple.hpp
wjCUYpeZ8emICIx/eMgFWYQPwZxZweNEj9P8hXquFCMKQI5U/NuIC9IijYCQJFA0ToHcDtzGwZH2cpYfPaXezUJCvNJIHM+dwX5XqJIxQ5jLbvVBDA33d60gL5flCOYGQEx1RSwLzgSX+8tMELLbAu1RrzmMflzPQkELXRWiL6xDcO9eRX/aCK41POy40u2gTIykxVpWL3mFQ15VZlHbw1cOy1tGZoZTakWPtvSOBs8+wYjQ+MabNDZb1B6khYHesS32UorPjp35LUgupDTj2gt7k4UefQXSfy/DeNOTPqhLtLagowXR31fkMtXbOCGEQlHRhaPAZWWDrnxCzfGgmL0ZU3d/76bJcrAJSt865woH3JMwx17rpWo9FOrh/uO6bCfIJel4+7gDK9C+b7AkMAWbsJ5pXNjpZ+b5cT2LuxRHwJz0hag8RHjFYBOMKCLv4+zubbi4K0pVnLkZT3vrgQeeDCWlcUv6dilDS9U5XMg+MKVyO208ypCv4q9RAWDW06dyVkySXZ7eudGzGRS1UrRoIlmXZu5NTIPfmtNDyplIaddutMh9GWcq+g==
*/