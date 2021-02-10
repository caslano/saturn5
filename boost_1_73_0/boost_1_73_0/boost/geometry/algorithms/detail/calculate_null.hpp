// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct calculate_null
{
    template<typename ReturnType, typename Geometry, typename Strategy>
    static inline ReturnType apply(Geometry const& , Strategy const&)
    {
        return ReturnType();
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

/* calculate_null.hpp
y3TPhdJ9JEMuzjkYZZTXX1L/kzzKEF+jau+m3CGjMDyfqM/Sd0JUe7lk+UVlWGReWc7Th+wS6v42Pee3rZpKObVZEGv4sAo/Z7ywKDH52qNTDlKXgOqXPMqcvIMF4m6jQQ4UGuM6sQQ9S07EcLVrr5gYDM7FsJzFiJebnpTd2MbFnLUZ2ofNS4I4iIZYdXLfPmX0955TaWuNP2ezuvNSx+r4XE3vULAhYqGZRXzBNVYMKZZVv+VozJd7M4keWGmLUqERhxhnSNKMxPX3IaZwraJtubchyKejGCQCfKR4OOGZivJQonIFHEcpklcrfIJP4dYclphOhZ6idfz6rHdx2R/88erkqMI8V/Krqr8jrOapxAJ6FIDS+HboMEqGntofzXbgPM8sCZFMkLyGNL5Np2mpmDYJy4ibgz91L3sn52eDZ1aVUl07xljuCzUhAzFz7xmr/LefkWeWG+vn+67Q8ga8qngkdLhc5uRxITXVmtfVLe0Odu2mYPFG607Mi3kTiTLFnzCaMSlIuSCvs6uNCFb0dgc/0mmXsRwN8WC5LqUiMKJZqZ6h6h9dYM2C5EaT2bNXFDAbEMQlPbw5iYPQ2Q0uLk/OLwc/nZ2/Pe0ev+pKtd368lXOPF9axsrZe0X3LjvG9uiuRUlKD8fw
*/