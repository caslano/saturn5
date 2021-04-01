// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace envelope { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::envelope::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP


/* envelope.hpp
6Fcr50D/b9jVwma+t9NeJ4KTpJc0rHoIvZj+Ln9OdTemDY96oF2oZO67JNYAXnwWXPTNMYbYoz+aEQWW2q2LR1vo+B4T02wxtk7YXg0rnVRSEcLYM6j1vLNEVAny/o7q24o6+4dMUPn9e0MpTKY6NaLkXBLT5UP6VHJ5MUV+QPz/1VH2mGrOFrYHg+3tmVgRVimkZgSncvrn513SzhhIFIgi7+cnHwg9YtR79V/LBQOABnKKMweoHg9VrZj+2+JiBwCgYo0r9F2Kvp7V1UFIc9irBsPrjKX6usOzaKomCgPUgJuW5RPtgm+VuYiV+erKLBKzQg17KoGW5Vd3AwX/EWC1+NPV47qWZCFaJvMS+pCqDDmVQ2rxBvcDa6zF42q2yp2sHWpylL2sXaag9IsZM7W0jPvIQV4wdwMqlEISPtzTImZe8MnqOAogMZ9hie/a7MHpjQEfVFu8ri7Y/LT6h/6Zng3TfD34LeohKjBGvBA1eY0ZBTHWg88ATVkBJjYK2ikY9dv+sizUJ4M/17b2FPfMJxunfTdmtrHDo3N9+/GgTX2m+nVzQr4KWQ==
*/