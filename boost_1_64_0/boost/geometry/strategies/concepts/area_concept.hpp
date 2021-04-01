// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for area
    \ingroup area
*/
template <typename Geometry, typename Strategy>
class AreaStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state template,
    typedef typename Strategy::template state<Geometry> state_type;

    // 2) must define result_type template,
    typedef typename Strategy::template result_type<Geometry>::type return_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy const* str = 0;
            state_type *st = 0;

            // 3) must implement a method apply with the following signature
            typename geometry::point_type<Geometry>::type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 4) must implement a static method result with the following signature
            return_type r = str->result(*st);

            boost::ignore_unused(r, str);
        }
    };

public :
    BOOST_CONCEPT_USAGE(AreaStrategy)
    {
        check_methods::apply();
    }

#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP

/* area_concept.hpp
KyNf1n67MVolAhGA814DWtgyjd3yauYjSOYgxz2fezFGFrkdGqYtrH1+WnByp3/FS8hJ91dMARwjtpv2Yla1MtkFJGykt6bATLKVGHs4eBuTx1WCcKtoY5uD7l0GpnlIAgXUOKZNrRwCHcdfFwnmJtN8atItVbaCiucH33OS/d9wy6RWDT4ATPpD3543XjrnJ5QcH391LHNHGlhHaJUq++NGQJYqfTaw0W4awrEZaCB/5YULnEKKnbwlYqS3Y2IDx/twH6aMh00feZnUbjCPyF+PxjlmqkJCD9IwN2mR0F2AJRsv/zR3FSqWPGn5JHuqWanXDlasUIx5M/zyY8r+SdGhLg2OyF28T7PsOI8hW6MnxIJYOMlfzOL6Fp0nkVSTOCltgGlOxP1l6/UFmoFr2/QnLQsFsu0FyDCRnmHLIJqfAiOtCDGt8RPVvKHFCMouwKYCyxvn5euMPZcezZEtCvc5xdFMMWqXQSmGzPEj+/62y70WMeLiwk7lJ6zoBaZDqFZv8r/R/ORFkeyEzDqBm7LPS26RD44rmc1inorQyiULod1YF0z+hEOVWg==
*/