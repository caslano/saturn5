// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP
#define BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

#include <boost/geometry/core/radius.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Spheroid>
inline ResultType unit_spheroid_b(Spheroid const& spheroid)
{
    return ResultType(get_radius<2>(spheroid))
         / ResultType(get_radius<0>(spheroid));
}

template <typename ResultSpheroid, typename Spheroid>
inline ResultSpheroid unit_spheroid(Spheroid const& spheroid)
{
    typedef typename radius_type<ResultSpheroid>::type radius_t;
    return ResultSpheroid(radius_t(1),
                          unit_spheroid_b<radius_t>(spheroid));
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

/* unit_spheroid.hpp
nUWuu0RscjeLXZ6rxPuezXglaBiFuUnXxdgPv023GxGCDll8l20j+S0IDsBq7xysur8rbg3MD2LOaqaZ398bQ3OjF4j/E8EJnirxA/9DCFvNQ+sqloeR4loRMff8ApWly8JXWb2wokqe+ovg2+jX+dhOeb5r7iW+EtDzKsNYw9EvRNKVSwrN5E0I6vPNXHKr+jCa6sPXkV9/dZWIOciveuTXN5FfvwoMI/14HVsP2PLm4GUUdw/tMtEB/UUiz/FVuNMRbjpsROmFLqKIb3xadLo6Qa//oRid7nd86LzWZ4nfEE7l+pBLsl8W3RF3iPyU/IygG+c3rPH7KH5OAsc/B2E0UBpuoXKfE9FGnHJe7fII1U6gTGQbQ78pJIN2hfx0z8MkNwb1bpFzp/Ne6K3SXV9Ruojfn+Q0f4bKIU2TK2UrUT+yYtL+ittaBuZeQh3Nh9nmuH0dgvY1w7MLNmdnI8OS9LY6IyaeDR4VB+vLcUh9zfrpIPkq0n+i0a6PxD2Y+zx7PPdoJKvaAfXeJ+fveySbjbQ62c+axwN9ZnsOQdIa6eO1/v1Jun11xGrXWHFIpJK/in8MSuYyb7w24h6S0zS4ab/u3g4uPnsNuiF/BfItnfo3XvssgwZGG7SewnBpbNMsM5hkeL5IMsJyPnAPyXTSEsT7IsEoiyVGOXyR9MiPUw77vb/15guUQ0z7ksplzXYN3u1+k6ccKpt7I8uovU012t8l5PYZY5l5envM/CpNDjpDeER+tB8HJP+WIu853Rx0+4POHkG3m9aSaMwmgd8OZP7t4P+75E+osYyP+JwI8+Th8OVyestwW0CuYSXIuyGuYOz+D+fhap8+DkmNsLX1sJ+7tNg9IV5HI5kckkk10jWEysqqy1Gly6qVbdKlnNrevqI7uVV5/cWdKYY41joSxacdXcQ38ArnTteYGN1SWbd6CuNNpKiF370026gEkSy6Rel4dqR+FsO5ehBO3XiDHl8wO5fPD49hnjVYrGsET9C7+m+BJE+2s1vgisCEQK/AFZ5eTl+gtyfZ6YBPb08i8NWe3k4v0pnoQVDOVG4PzfY8qr52p7YtE6MYD/Sl+hrTttF5VNZlN3RZJvVdexP07Zys7MCZGmkHJ8BXTzqvvy/oTgx6rw66Zf60Zl+u0RjTS5mk9Xuj7UvZ7ODRKtwNjwTdwWBwaGyYVn3nqTD9G/ZCjxi7nQy3rEuj02Ar8oxnso7vAFwHQg5wH8AKwJ0W/GEy4k3R4Ra4bw6d/53MENZan0mkdc2edYsqatQbsKnw/3VH3b+suioseM+3JmrPt5H3Yq13SZsMPxqvk9+GyHc2o2Qx7mW/GmN+EiY+9uP7qtT3xPJFzGPoHSz6lXj1feBpwDWZgM62b17zPCb+2YUHSW6BZ5PwmnN38uvBPNjZSqf3qz1esdRjM79hmUHGeeInyJ3rjZ7fqH2KFqKv8KzkeAuNMPKYR8X7RY43dn4zw5DpZ4w3Pkvu/t448xjqFzrLsQTxPKE5kLPD0EIs0UIUZ2f4einOQ55u4hsxc5fe3G45u0ie1W6f+ApmAEUiT5srmrWfO2pdt4pjrifEtZyPN1FY13oCYpx2i3a5WKn1Ea9oDu1Hjmqxw3mvGOFKE/Nd9wif+9fib+400cmTJa7m/DxKOn4Hs7UnxLPQ/BjGB9O1l0XIMVfc7nhP3OFM1na7XNp+960iy/OUMb/oS3G+6egqnnCoe/ePZVG/SPOLrXJtg8Ie7bWdX3B/9zmSw/jJ4KsCI27MVNdXF1WFF8LKIs4OZGTSWMTo/46Ru0vcMX0z8Aekx088xx0Pi3mulZYxUo0cXZM2an59XRdeJyO3tZymaDx+U3KGbQw=
*/