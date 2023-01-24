// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for points_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_begin
    : not_implemented<Geometry>
{};



// dispatch for points_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

/* point_iterator.hpp
8CCKeWh0EZZk3T00NDp2T3cnYf4S85slFjYVZBScLpeSe/AB5c+TOTSCEMGmIaTsuIl/XLgLDGhQHooN0e9Schwf55TkQRuWQqiFxLCZQ6M2O/kUBpltcJaDFhSW/zkoJOId3sRP/w1BYfLezKBimh2litgR5QgisrpchX3/hLk+RfnT9Nwq/KSGwxzyg7t+ievdLDPGT3VZ6OtiOapJCs6SZHTbnlXqy4XEnu2OQvlw/gI7KurAur6891MNwlT45/DPGM83xNPt1C7gJzvhYfPAEaAqoCx1XSGlg3UVc50nc9xFdLhh7RSzAlpdx6wj40HhdX2MKX+CY6MpWkXdYZHNn98qBowNrxD7fFCCPCSyqbzkg8517Z4uTMNzib7fN4RbzGc9HKqba9tMw97ZNeNTIw4EF7beyc1+OPh92FlD6l24M4zyS3ef3TpDwCG0knoSDtxS9Svld3Xt3PgqRtTOtdLd++dcp559lsCbls0czviuwd/slc3xUYfzWWg23/wcso9JsiyRuaNDLWldwiotM7Cf75/FSK7+b3maV9Oy3qv9vG8FJ2b1swV7ZIysG6fb5G8b3tLzM44N/fiWDzZ3Vhirct5/L8WaynWdNfED+VNzpDAviVFH2+pe3kdrKosetHZen9Cm0+l0AsNZZZQU8iEn7r3jPPCxZGWrB5CmXG3GAJVD/aIv4U3PV3d4mw+ym7vIvmygse0g
*/