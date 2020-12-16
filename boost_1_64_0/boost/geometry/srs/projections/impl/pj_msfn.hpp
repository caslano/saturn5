// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_MSFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_MSFN_HPP


namespace boost { namespace geometry { namespace projections {

namespace detail {


/* determine constant small m */
template <typename T>
inline T pj_msfn(T const& sinphi, T const& cosphi, T const& es)
{
    return (cosphi / sqrt (1. - es * sinphi * sinphi));
}


} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_msfn.hpp
Yhp78xf8dsNi5eGRVh7aSCMLl6WRhUd2E3PHrgdzm4K55RJz3cRN+QYw19YWXRJpji2KxM396K6YYIKcL60QOFwRwOHxYjx12i8tVk4QOFwhcHhSAIcnd/H9Svt9IC2t3j3RjvMpFmO/CpaZBmMrBMZOGyrzubanTVsZwNgqW/fpDmMiv8DYGouxhULv/prfaQflEx9vpzq8BTLYOcwZabB3ajexd2YX2Cu3evg3Env/JH72EvjZK4Cfc8RY6bSz7fifK/Cj492bwQH8nNfF9+fb7wNpQncH09LLsdV2fC+wcuxCi7E1tl79rf4fnCcFyw7iby+Bv0uHynyu72nTzg/g7zLbvssd/mz+bsypL+K3mFiaOcjF3ZiDaGxeorEpPtZ4vCINHi/pJh6v3ID+vUrisZtz4q7uLp9ut2Lxw9gs+l6AhA9cpfOBO585p2H1Jp9ok71ozr8f6nca31ghMeFzH6SSu73ph/Ojb5fGj67X6XuAvmvS+s11PfIT4TXvOkPX95H/COVqnrxW8OR1Q5N++euHuvUjtyb6B9MvIyEq6tOUyn2Nbi/aDYIGGeu2NV8XIloZTDLtk+0YJNpxYzfaMc+24ybRju3UsPS1pVsK7F5W+0aB3Jszv66JndbJ9zBbZRjsLTTh4db3fotoX580mO6pJaSqNONzmx2fUWltA7egarjIhex62h1iDnWHGPO7AnL4biGHdb47rRy+x7bTluVk3n1DRT4l81G2mK/saMt7ICBDdVqOSJNl2HlO+u9kGzdiDuToIuZAgYTgHMjVIeXw23YOdDvxer5zL39dEXYOdP+6clQ9SJx5u1RvyLFxD8l8e6t14rYXcXNjXAQZ88MPE26OmrvHXbgtuiiSjOuvHknMuZKNM/OrR+X8Crn9WBdyW2OtD3L7cZuuMThoPVib2j1Z1S3+11h9UmD1KYv/+g2uk0qZHZD7rp5k2tP+mmlqC6jzILsH+BnBowN+xLVnLd8yMt2dz25vZI9M/y7I5sSVM3Xl7nzXn+y4uRQ71iV2v81zcr3nB2B+eGob9tdTcncHDvW2lOjj8cn6npf1/QA/Q0LuZFKO3CfzIuG0d05txH4SjZmXLWYS9bwSqOdVwgPdPjiK4RE5c8Kc789Tm8ApvTzd99eH+icY2zpIxoJiU11TO4c6eYpKL8xNqm2MtmUbcyt7pP9X7gONAbzdROH7+Jvnuk7P23fYemrL26+4oMifJw6351/foH1dF+efYw2xr/hNMV6hje2RIXW3Wrb2zo2gndmo6NuWMf+NbraA/3vICHLSVZ7HP+Vo+/YGaHuKpe1fuk3btJVuHJm7bLmPizUbQf9FeqgjHf9W+Eb2T8XvXzdA4zZL43e7TWPbqx8EYdO6tbduBA27GNF/JRUr14cBSdv3NkDbFZa273ebtl30tjvUXX+r156zETRPGeF/Na19TDiafthNeftRt2ma0pvu0tLxkXn7uKfcCxzeanuVfB9ChgcQbk55ozAW4fLgplr5PiFxtXPjrfJ+yQwd16pcuKcOt8VrZZ5eJk+0rbEu+c7Nprr8pmbj4ZR5+5h6FwfiaTvx7e3JejJ1WNTbT9fR3jlffjOAuCaRZ6DOI8oYRDheH9WtdXGDiWtZ2OzeDvvEzOtjELjdtX2YzhOb3yTfbhxu4zA2/Hc0+G6E/51756GfXqP268SZxp3t9p2HzwQe8hL3TBdVVIu9RDNErNtkM9zaKHl23/98/3XMBPdE2hub6vXacbPmH7tv/+9pMNrlt5ZDup8/9ez7y/5e4PqmNn9fh40zZyuiRNmwthG5WiO5t/RLQY9BKtLSHFvc1BEx/iV7jCEQ1+WZd0u18sTOpOrx/kQ=
*/