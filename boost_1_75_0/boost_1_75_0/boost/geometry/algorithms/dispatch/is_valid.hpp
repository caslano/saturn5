// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP

#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type,
    // for multi-geometries: determines if empty multi-geometries are allowed
    bool AllowEmptyMultiGeometries = true
>
struct is_valid
    : not_implemented<Geometry>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP

/* is_valid.hpp
cdMoC2BVkv5JUzoYcmQfbVY4nmroVasc/unA4VXU9rIUmzINEZRpVGDsXAsuSOMcbN/Tt5dgMSqmToa6SZjVGIdDhsib6KQrLMuvLCS6+GjVm+Z/9cCsmcfEjE2TNdL03PRypcrgadASse6k63ltruPpWhrpkP07/q2VJtbXsULFiLdqU+p9l89+7hz7rDzBC4LbW7i8pesTb3x5RHJcvcbkYojkI3S9Q+SejnZyKloLzwcoHpgv4j+wp+N16GQD2vnoOTkhU9UviVHty6xOOJVfqRGPePgK+T6+28sMe85Lp6HBfvb6Gm5LwlDl+jtFnApox1qbU0FCIOifjhtKPeqsUdeqpIrD6N9VFfDw8tFuHTpazwBriMi8+EoE7/KGDa4El6Se0mXwIq3nVa7+CPgjPefg1NeRFUsd5bjmj0VFozXNYgKYGPIjHgjLTEOAl6o1zEvBxMvRvf8iZ0mvkf7ZvJ7e6FlEgq9er2SvyM0GfSTCUPBCTZPMf4CE6ZAryY6MkrEv7jcWr8IL3hexush9hypOvXr8iyU+Cho6LTCyiYSGv3dVuEtJQBmEFr3V/LKpcMsiG98uUZgHxVEvnFoK8iixxP2Wa4xETaSvghMH7T/33HNueF5R6RTDVg2yKNtj4mQaeXVaidbd7LgoFM8O4IYJf6M79qLKuHO4oZ0DFVZrfW4jxbbZ4sszOFluvJNCJ3i/+cXvnRRQ
*/