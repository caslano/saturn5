// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP

#include <boost/geometry/core/cs.hpp>
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
    typename Tag = typename tag<Geometry>::type
>
struct envelope : not_implemented<Tag>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP

/* envelope.hpp
8sgB02U3+UjgT+XxiMYrPV4vuvtpH6WC18VVXhrdxM9hCdIfGbmqc3r6jrROlqywf4AWwDcnFiYYnCVORSWxsY3DNaOAcViKgcl7VIZ29CRa46AM7/hJvGa7BO+gXoI39cowGqUYTyl20HwSrVSxg1YBT0Nryu3vqZDhmxymyW9luloabwlapqS1rKOEL9POKignEUrUslKtUsh2CWm7SHS/DLRE6rKotsukLgZ1Bp+XuiyOnSLRstB1SqRulPnRKRO7UXRnhpCXu1HmSXcF2aITJWyZ5GW+dEslL7o0Q1DRL2udeGtc7CFsIt4LV2+TqT/6EG+Xkqv+e/FHH3x76cq/54FWb2l/YUk8T+Lq6kEjPyQovkApYFEIM8Z3/rI2C3coEIrLnDaX2+I0i+i93DZXRdBXyn8D5T185c9IocWWqGTc1l6tTdUt+XMm1P2/UEsDBAoAAAAIAC1nSlI7hLF1dRQAANFFAAAVAAkAY3VybC1tYXN0ZXIvbGliL21kNS5jVVQFAAG2SCRgzTz9c5vGtr/7r9ibzrjCkW1ACEmx47mK7Nia69geS26aafOYBRaLGwS6gGI7Te/f/s7ZXb4kYeQ36ZuqrSXgfH/tOQv0cO/HfXbIHmn8WPw/Cz7wzTFu4ujfzEk3Q1vW
*/