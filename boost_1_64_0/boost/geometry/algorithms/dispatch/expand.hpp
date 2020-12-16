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
qMUcfrcsq2sRNVV5lqTxLvN+lau+4xDgmgZdkmrjKEw9XhSsObJX7p62IkIvk77Y2kO6e8f2oAkYdu8fEFRVX6i7NwtR3S0yn5RFxu/a3GVmWufAa3O3C0ll/Vyn3ziqQYE78qDLvOouQcZFOpDj+eqgGb5Lx8OSRJCo2PNDxLVgWDcd9iab6/N0cvM0JKw4NK+JxfM6l13hVcvj3Azi48zRX2OKhZrzUSITKA/KdIdKHcDI5dpCcaD8viUIjk4QsvnRQZmt9D0wVBLxvi6nVKMo0mUd1ctzRv0Y44fEXgUFLTLr8NU9aC2AH0O5xmLuHNAnWClijdnSJcMQDuLU9eUTu0xmr8asXKY0pvA9fBujFja56oN6O7PYmZY2I5VOEkgVhxHKljKlORKWsHWMs4qoUkImptsSMhmfaU/mET3e1h3FSOEI/XnXDd1XXufcqLysXkiPaKMOJJP2ZPMxvGAoYteGLRsRrpeFYQdkxknbu/V+D3u3fa+l6g6z7t/ClgH3bQq427h2apkP8+d7AQEM36DKYDXK4s2eguDhY2p2N5C5CwJYPylmky92A2IFgCZFMVe/RQiG69YPfFuKsdc7Uow4pFXlndalvF4Z5fU9ifKkmKf3Zxazbn96MYPehZAPyNqXT3oG/IoAIBlTPMmbqHVgdzqGO4Abo8vp+6x4A07YCf/RgK+6TWj7SlTlh+yFJ1x8EL0brnjDVzthP8cRpzuO32nPYVlAMwbAC6nVcvSrotnuQDK/+Qd74TA2+4ufxM1BNCtkrO3Ihym1+moncvvrqxwyISlB3A9M5n3w98Hfv/6P/AeyHiy2w1SyHe59s5NsB0zGZeDJa5+S0Ebn3RUNUtCrJPkHnmg2+QeRgpQhXy9+oAC5SrsOPMBJXcqp2D47EFv+qNuRyT8oUYYo1nZ02vyDpqwU66AXbt9WDLTsIX7/VuEf3JUt/IMyGKQn/6AEp4vu+AeIQCLNPyhDOj0dlVlrUBnWoBKsQcpoWhnWoBKrueYFbJDmH2zJsvkHAGQaCnK3MhHNaBGaXYjXxn+i18ZWEjnO6JQUTg4xJjIBKPDFxkgxzVgw1cRO/sE6l0O3VH7VxI53hx3Miq2m0WZjo4glGQvVVUnktKDxR3UMPi7H4HPY6jfZ6geV8iqKIDaNh7qcfNE969zSrp9JQrj/HZ9lHR9uPy5NA0OYzQgZW9Thd7ygLm2XWYZd5iecTINNSjoAlfUlTIr9JVOZC3hzSUDcTxOO2MqIi3i5Wu4Svionw2pJX7HZFxsg7Wm2F8AsNsZpIeT0k8BTR2++WT5S2UOTpL5KgfehY5n98LNj6f2Q1X353OuWuU6wzveQ8m/axuJhHqMrbS/cl9rOnEuH9cNQl6ZfX+xsvJxIw77a/gj3o+o0Ou79HujYnVb5GFb+E5zchYadgDBDtdf3iD8/1rgQNvV8t9Rqeym7djP7TXNYS3NV6zHTUdhc9eeSoSXe5qod2dmj6pqrnnO7XD2aq9pKvNnZzVWvjKpzu5qrTNdAJtmtkuxFkkHSrR8/mtatI3215+Ldl1/ValTt9eVXt0E+xtcnlA9BOGJ6pLbUAjOmbmxn+S1/3NWJtoWy1RUyahostt1dMlHFG10acYnJlQBDXP3OJ26k75dDuA84QjtiTR5r63p/JwmgVKM60hXVZiaq+Riw4g1UQgK/F/w0w8as2oI36i04nYdTXwmtKrMND/Z7U21Ri1B3bKVHzY23O05URb4xs6diNxVWRqYZ/iEg3ciVY6itHfn0GAd+00bQtiOZI2jNkfQRNPCkRlBzjI3iH8N1Iw6CO2XPZzccyRxHVx9JH0eDTqIWsFeWqM5sIXebXBEqpiI=
*/