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
zKkrraln+/mgywc7/lW6730vVrcwCe8qruaFmhz5tkdzyMihSdF0w/cZaf7No5k3bHjSw3fKQMf2vljdpPjV1XxImi95NfOSE77SNOsum/5Vj2ZuNHQD1XTz6AZp/s6riS+Dbr/Y9v9glUFuW42x6aYzxax8H+w7h9t+WCfNVzyaps20rLSqstz0nDLGizE5Seo/zchR/Wb1NR7ffYCAv+W6Yb1Sus82103iOI390rz4TmkyxlYfBZKityBX41C2ePTqKy8P+h3Hrb+fk94er54GhNAGj2gEXj7Y8Z95ju353rAlKoP2qx3/Kb3yGD06fQPOJ3b85xDH9vbvuXrjpheULFzeEK5Pit4t0uu0xatH737A4WnHv2uzv7vd8CyeOM2svhgZBe4M+h83d36w2nb8u7SzNyXSDlbXLXszhylOff1MgkrSmHRXf630H/bVd8WDb3O7cZ4xXHHuG+4FU8x7a8D5yZb/0t7S3O9JmEPjprMD0vybV3Pc7Om5znKKSZvvUDVCbXBf3WDbFa5fX5bmvuaaJpCDn8vi+nX+SLX9fXWD1XT9uluaH94mzRnF9K7NLiqpXxJpxTQGXQe5ulPO1Fo4m+J0aTIG/w3Wfv+Sbr/bfXQrKhcFPS7fLa/yR2lsiZ8uTVY6rEsWNdaUBe1vN23dI/21d/jpB/ut0w3rAaPVP/+9eM3axvrAxxO5ZfMm6S7Y6KO7tDYp/cZuOPfUom4DbvfVTormWmke8MnDNY3Bvl/a+u8s9Z36xC3fkNGtqkpWGK+U9qj4siPw79e2/pPmV33yT2UN/YsBv1e7urVna8x4fDgnJR27uvukm+mnW1lTHrSu7f8aq7l/PnFb3hhs/nHT8h5p7m6maQYllDgSyfJvUb7miTUP5/LKpMXtTml2a1Y+0lUdpk8qcF3XryPHqU+qeTjTVG8KeK6jW+9udzXvbKZZNMUZ68N3pshgu2S9Gw4dr7mzt8frR1bSrgwvCzy8Xe1t0n73jnht6oUS2s/VQY/zUlyzbpnmG8T7O2ll9C3SrIjXTEoZ7aaxngUqP3zS2OIkpjHX3+ukvzDe30mpI9z0lTlR60jE+xs/swNYSWnd4oC1XT+vlvZOP222TQ2671W6vLBoDEbzsC4onEWGTlocN0k3y083HHx97KbtA9LtacOZ+fB4tL52KTnKGbq2sLS+sixgffv+P1n9W3H6ZthYoJr2/V+aveM1y5Y21gT+bjpcuhVTNNc1Rnd24fTJRRMjKxCY0E7yvNO9eoZRMc+gdReSMH7Mjn8p1LtinG5hQTL6wu34F+kOjdEdP2524YSIeFLKT7efuuAcx/Y62x4af05JfU1e0PPH7fgP6c3y6iGWV1+TFL0+UzXX7y6PXlXw/rPjP6Q3z6NnXlYic/Mry/niUFJatTjYbw52/IcWvy/210Y4+DmV9v1f2qmbPdoL68OldWUVJUnSTJ+mb9qetGSGXibhO4sd/yjNSW5enT5hxvRJzuIL4TI+9wY8ftj1637pZrjvS9MKhtnP9wGPmbbfP6c7tlt7Nfl8H3T/pKu3W3p7XD1nuGPS9PJn6L3IzS9Tpo2bEPnAG3C7zfZ/Sq9HjN7cWr7SB16+u5rZxRor7NU0kUglHrCmG67rpZkVozmpsqa0KlA9148ZMx3bbWP0NJMkYD/a/r+Zst1cM5njH6Q5y+2nmVRYPDsyVjNJegtm6buXW75OnFfMB4pSxp8lRW+39N5upsfYs6To5c/W98Rmeoz/SoreNunta66Xlxz/Zc3RHgUbY/Vyk5Qn1knvs3d49cLhcqYSBv1uZsc/zdU4C69mXdnQkorq0rKS6vJhAeu6YbtCuhnNdJNVju+X3sk=
*/