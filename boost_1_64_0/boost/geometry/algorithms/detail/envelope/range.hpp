// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP

#include <iterator>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>
#include <boost/geometry/algorithms/detail/expand/box.hpp>
#include <boost/geometry/algorithms/detail/expand/point.hpp>
#include <boost/geometry/algorithms/detail/expand/segment.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


// implementation for simple ranges
struct envelope_range
{
    template <typename Iterator, typename Box, typename Strategy>
    static inline void apply(Iterator it,
                             Iterator last,
                             Box& mbr,
                             Strategy const& strategy)
    {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;

        // initialize MBR
        initialize<Box, 0, dimension<Box>::value>::apply(mbr);

        if (it != last)
        {
            // initialize box with first element in range
            dispatch::envelope
                <
                    value_type
                >::apply(*it, mbr, strategy.get_element_envelope_strategy());

            // consider now the remaining elements in the range (if any)
            for (++it; it != last; ++it)
            {
                dispatch::expand
                    <
                        Box, value_type
                    >::apply(mbr, *it, strategy.get_element_expand_strategy());
            }
        }
    }

    template <typename Range, typename Box, typename Strategy>
    static inline void apply(Range const& range, Box& mbr, Strategy const& strategy)
    {
        return apply(Strategy::begin(range), Strategy::end(range), mbr, strategy);
    }
};


// implementation for multi-ranges
template <typename EnvelopePolicy>
struct envelope_multi_range
{
    template <typename MultiRange, typename Box, typename Strategy>
    static inline void apply(MultiRange const& multirange,
                             Box& mbr,
                             Strategy const& strategy)
    {
        apply(boost::begin(multirange), boost::end(multirange), mbr, strategy);
    }

    template <typename Iter, typename Box, typename Strategy>
    static inline void apply(Iter it,
                             Iter last,
                             Box& mbr,
                             Strategy const& strategy)
    {
        typename Strategy::template multi_state<Box> state;
        for (; it != last; ++it)
        {
            if (! geometry::is_empty(*it))
            {
                Box helper_mbr;
                EnvelopePolicy::apply(*it, helper_mbr, strategy);
                state.apply(helper_mbr);
            }
        }
        state.result(mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP

/* range.hpp
ZdVVtRXy+/a7yJvVuzjfsuM5UlJ1gncCNPK4QVoo3x14H535/fsf+PHqLa99zDchp+v18ZEVz3S1eu6GIE1GpePt7jmEndZ4N84nATxhDr7Svl7scmAgNe/PTFq59j7m0t0lZqP8yxdBPDaw3/FoF//JL/S36M5t1hrVV7nxZOW8NVYya8aeXN+lnsEF15JZ/aHbY85ceJmHbubskjluf7Nnzgn1g65kxqy5/aGbOWOPkv7QMdN+jTuneNas/tDNLd6zxP3eHS6WbbkNtcQQvtaBDXFgSzTYNg5sigbbzoHtJmAF+RceHTNs+EPW3GsYY7AGnknLfdGEBe6/GzlcwVm3oh+h4GwNdNWA+99HM94ch4pu2hdjjZa4el6y6X7PsqoDazgxEUsb4x7AeIVzn/r02u0gcY1NpeVLnMGsuOD36U7UcVzG0Meb5MNx8cKR6w8nSD/wTYhYqyCb3xJPWZ9XWm+1+dMnOPrZFU9jIKRy6nf+JR6zKDGujSrxwSlDEWNyt6H/z//JuVruFPxDzbMgfSaMMPT5JWu8NFfOnQb9fFYw1z8pstH/q36eWu+81XpX3oRc5zly/QS6tQWtj29fYfxPHfpJ06oq9pL0ye50LB5o2ida9ZzoinV0t8Q3Qb1JsubuREeLQzytJ1Myo3gPD7duzqxpmfZoOt4yLXfn0MXLGUzq1zzh05YD3HVX1NWHaxsbqyNLG3nZYH09Hm4J0IrGush+VbUzSzSKpkUN4dKKRg1SWxepWFFbWlNVzkseF1bVhjVcfVU5f0lwI+/x22fVZOamT86bXQs33wPr3eSCV3GFcdWqeFcbt4wz04ojxasmq8ELGS7k8qKf44IUQ+03c9K0tS24sRmTpi3MiI9KfnsnTetKUphNaoxoXNHosTL3/0juBcaltRWRGv4BtBruVVTl/hkpz31PZvnShnCOu+F6XoDIqzNB8UrG8rqKsCDy/llT0TJpWh2/FRXhsqULBc75x8rEpGkxqQ8t8Z5VzuyXla9q4kH/zKqaRv5ZPGt68YzpJbMFprSpuqYy9L6zH8pdJS2gB9Vicvleq+rTyTaC1EmVVLczk3ZeN3fOLqv2I3xOrs1MWsLblFbxapjK5Y0VS1bNmj5nerHbelV35+T+9lA8w2vFJGZML549Y87M6TNWdcfS2X50Im36IOwPZ91YnDexPm/x+za/7/B7F7z4F//PM9ismXuKwaSO9GO4Prv5n5btdMGrP3LrbmLfLTfizDcc2/ruKN12z5e2G2Oo/PwCCevkniVwVQd9aXsdLvO9qflxMuLlEE5/R0P5BJOOhI3aOPO1jk/YEOPunR2XSfBFE3Et/wiDr6mriISX1xPg8GJSTvDrV0QqG+pqePUqO6My5NFW2Wmb6hxKPb9aAi3rIV5iwqyJi39r9Pyq2oInbvHdm6oxaHD3B8XT2GPGyUfTmen3PQjXr5XY4pWvrL61zsfPEiGQAmOOtphZV/lGjWXqGg2UTtV748t0kvCQWD8PjkCWa2dcDIq16zWpBuji3bGORIuKgZuAJWAhE1TtC8rX2lpLOi18pL0R06u6z8LKEnGir+4U7zdBg6fTJalkB3f97O2YqBf/rpzgg4u2IW9/BHAEXt54q0xcn20Ret624Hxt5/vxMFWNe4CB63tcCkN5xwWXazvZPi5nKB18VdAa6m5KVw7IS0NXnL3nWwPFpLxrAEdj8Pnbyv2dtz3VETrQ7UhUoxG6UAJet30x8Cif7AM+FK8r9ngYD+BK1pX077mWLv5z3g5k5gcTrPrcJsdidtHeSFw9Y5aQcGpzHC5xal1bWunhVru4VK8swmn9deZw8mZwZ3RdyALPJjVf0+XBzVo=
*/