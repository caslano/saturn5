// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POINT_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POINT_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/metafunctions.hpp>

#include <boost/geometry/core/mutable_range.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief MultiPoint concept
\ingroup concepts
\par Formal definition:
The multi point concept is defined as following:
- there must be a specialization of traits::tag defining multi_point_tag as type
- it must behave like a Boost.Range
- its range value must fulfil the Point concept

*/
template <typename Geometry>
class MultiPoint
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(MultiPoint)
    {
        Geometry* mp = 0;
        traits::clear<Geometry>::apply(*mp);
        traits::resize<Geometry>::apply(*mp, 0);
        point_type* point = 0;
        traits::push_back<Geometry>::apply(*mp, *point);
    }
#endif
};


/*!
\brief concept for multi-point (const version)
\ingroup const_concepts
*/
template <typename Geometry>
class ConstMultiPoint
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(ConstMultiPoint)
    {
    }
#endif
};

}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POINT_CONCEPT_HPP

/* multi_point_concept.hpp
V2s+tDHbhebDHu0/98Le8DnYDz6vz2cvwJHwRc2HlzX9v4GF8BVYDF/V57YDmu7X4Wp4EF4D34APwKPwKfhn7Wc/hi/CT/T57RB8F74DDYP7D2wH34U94WHYG/4JToTvwRL4PlwKCcd+DpN5KZAT4Dlsod6vy2EYXAwjYDWMhItgK1ihz02VsKvap8MqOEX1FaGN76E1lsIoRqy9r1bzt+59xb5XTftbNe1v9a/b36ppb6t//d5WO54gT5BaxP0kbpEcpApZg+xCDiPup8hTZA5yGbIV2Y98gXTaQ9ki5cg6ZBdyFIl+2tH0a/o1/Zp+Tb//gd+/7vt/81t8cwOAH/f9v/l9/+Zo773b6SgoqVqYX3luHpeoYHF1fmm1p9Jhu5nn54bla+rC2gPg4wSHrh+Q92nyGxnCXIhQv3PvKu+yzcj3ySuonj+fJRq6kCfg+oFnxb075CJHC33PbYUx0GctbAmrPgolHvq+W91kSjiL8LNH9JYh1zic4m+zfou8eEBmAe8LZA1bqq5hmxQvawrI5Lo1bLd2kzXjss65N2tMURzrzb3kSbNzVniIM8nlcXWCCSw0jQsLd7tD+4cnuSN5JrHXDp4a45XrozHT9UCsa6jIX5Bnf+uciNkRietHxgJHM4nPjWZ8xJ1D19+ipptuXjXOkDXa1nohMpT/rfVkn0o4fzTm8798I6Hx3k68a4m3u9nK73zN99aZf2Ka6xoUew3EUOQV4j6s8fUQI7F2RFHa6bIOwGiwTijR7/t/u+zEPBVuFndaNvX2Tzig30TfF0otV5r1qrx7Xb3y2UDBr04la526StyuC03g/3FI31B7LwANp22QPRTUnpgma726RPSbQlvT8ichA0JD63+HYa/RG9QTt8y4pjKrb33H2L0XZsxmlRtd7O8zbuwt6yW5Bm7464Eepl7gvIS3q0txeTRksdSfarlGdaWnSOqP+mdM2dN/T4LmorsNJ2Ydvd/VYW5d53yulOMTHh/351WWnOdxiP+F+J8l13/OGYL/qc5WPm4LSssKzzUdi9sy3K4Tt1c5w3Ab7UzxcVtYXUFTr0KJ1XVSrSVe1/EepAf+MUNzSX5EhcQzo/WgkeOflxXLHcn6vdwVku8/D21F7ZiAZIaG+FxL2lTZ/Pl1beoWiddFzmhnLGFa7iTb7PXA50h8NodkhHTRdUJW3i9yPuzICHE6Z/vEZ5nf/gTvSrxLmZ+IbLB+bwL2L4r9hQ7zO7xZTp5DsP/UbGsRFw50uVxjXJ3DQ50Jrt70HgkY22EYPmHcL/E7U3Urr2Ik3d0TpOwqF+QVF1X47FuyTfzMVd3yE2+tpZe47OU6n5lxCb+wLdfn+DVdS6/26RFe+/Awd8SqENc43EThJfB1tb9cLnUrVr/D1nzk7YPbkcFj9uUhZvjTHLOlTX1E+3wPMfuYXGQGMg2Z7qPfi5RHe+UvyCP69/PIR+rX2ouEvqbRtarl9dZkLQuwF8lfe9dbm6prtOiS5ZfgBTlJ3Urh+hl1/Q8r4pbVW50aaE2++knwuxdovdX+JqgbvzXv6qbR8pgpblqc9Bov37462t4/xI6fmCf5mxMn/3W8hzWv1uoFrkF6Er9yn7wKtJK3hV33ZY8gzS/Ln9P+5qpS9KvtdBv10j3B9rP2hOm2vu/huqRHrmunnbAxs8L2T+NO3W8hUgOLQG6iPmT0qZfGxdWeag9rJkvKuDMtlzR2kPLkPqfxJSj1F9no2EbdnHSauI73ftrg+zINu16aVru8gVQjccoNVPRs3zQVL8wzS30hXxPxh4dmo2MVq47W7RUwW/zNtsqRcPz3JNkhOiY63niSMO7ScZKKfgfQeFozINfX+ujfbrM=
*/