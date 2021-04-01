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
z4xxca46GooMUfVGo5Ar6gb5jom4HPo5BpgIrMRrHpCgp5NTe2QgHQUcBBtOUC8EdpxCE8yXfDrMG+kZkYAyr7pM4GtSGaNyFGYBJSxJF+cNevf6+B/fCd+q5/6ZWNfNwbRqs/HQIb2mz8NhDCGOYp9YLIQ0OxduddLCJT+IP8cNg80jwo+JiSFK6H0zcrpuQrFVzzO1EbsR3gv/oBbPvz15ri+4rytDSUNxRRaIK1EGh5At03ge5PgAGRkR3DDZvv1Wyrq6cWIzq1BkoZ2uRRkKgqyvx7z26xo5WhAJuoJP8r2TYKJuZVWEYJXl7H3dGTErntH01ykvVfzPBv32OaQKyjhO/4nL6FvUjM2j4COAhdYCp6mf9G/EFUenVxEsLiHCh1Yg8z3SsOc5lk75XLPlu3StdhHmFGa6lH6dxsN9C8LTKMneSbjNHi5OpEU8l5F9tDiu9ScowiNFZfxDD2nwvLSH6HqB/Je3BJ+IBP7s7fK+hvaKN9+BrSbIPtbMjCJooF7BSnNKYBsEVjgCJKP9SCdMllROHzOmZom8cA6TgMIMIjc2oLE2PA==
*/