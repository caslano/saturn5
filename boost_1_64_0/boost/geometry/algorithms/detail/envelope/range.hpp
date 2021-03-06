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
jjgp1SGVoeWieSBehJhRigaVwWESFZ81JVK2qzAB18B9j9L26ullH/j7P+/1yde2WEkYGPODV0jnMD25Ldq80j1fKyIHYQIuxEQ1dzMNCJGoI00GTDZ0itiG7Pgew5roXzaCKasrRhyXgXo/C3EuLYU9ZERaEG/hnUgAV4J56HSBY3pWYDzOqv/N3aBCVw9osmPD+bKtNjuYs/7JYmnHAQRTGgMotv9Wsw9NjduomM3e4zXffglGOwfkrF/EfKzAcKcgFRbmgdQb77NwjN8IZHv9E63rsVLlSZzcwikJkU/g28cbpAKh1OzB7yLSgvB71R+2f9ppsvpthQy4XSNTshqTETEEP6++e7m6yZgRkZTGUIe9Plzw7YXxqEFEZXUsHS2a5uE3BM9HW47ZDe1GeKMZvkUaAYQMnMx4eZiMmv2MRkn9nNhAv2MDGFdw8+/37FrXf14Z6EWASnDOVbOhqbCJPC+vDCggdrn9vEFJKHI2QrViL+0Zq5qhAD1y/LL+t5j5R4Zg/Gq+48GErBd9+0iN56ZaSdHJPYivBYhVf0bxIPo0VrLMfgXkPw==
*/