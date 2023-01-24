// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/envelope.hpp>

#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template <typename Geometry>
struct envelope
{
    template <typename Box, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        dispatch::envelope<Geometry>::apply(geometry, box, strategy);
    }

    template <typename Box>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             default_strategy)
    {
        typedef typename strategy::envelope::services::default_strategy
            <
                typename tag<Geometry>::type,
                typename cs_tag<Geometry>::type,
                typename select_most_precise
                    <
                        typename coordinate_type<Geometry>::type,
                        typename coordinate_type<Box>::type
                    >::type
            >::type strategy_type;

        dispatch::envelope<Geometry>::apply(geometry, box, strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_variant
{

template <typename Geometry>
struct envelope
{
    template <typename Box, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        concepts::check<Box>();

        resolve_strategy::envelope<Geometry>::apply(geometry, box, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct envelope<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Box, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Box& m_box;
        Strategy const& m_strategy;

        visitor(Box& box, Strategy const& strategy)
            : m_box(box)
            , m_strategy(strategy)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            envelope<Geometry>::apply(geometry, m_box, m_strategy);
        }
    };

    template <typename Box, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Box& box,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Box, Strategy>(box, strategy), geometry);
    }
};

} // namespace resolve_variant

/*!
\brief \brief_calc{envelope (with strategy)}
\ingroup envelope
\details \details_calc{envelope,\det_envelope}.
\tparam Geometry \tparam_geometry
\tparam Box \tparam_box
\tparam Strategy \tparam_strategy{Envelope}
\param geometry \param_geometry
\param mbr \param_box \param_set{envelope}
\param strategy \param_strategy{envelope}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[envelope] [envelope_output]
}
*/
template<typename Geometry, typename Box, typename Strategy>
inline void envelope(Geometry const& geometry, Box& mbr, Strategy const& strategy)
{
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, strategy);
}

/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{envelope,\det_envelope}.
\tparam Geometry \tparam_geometry
\tparam Box \tparam_box
\param geometry \param_geometry
\param mbr \param_box \param_set{envelope}

\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[envelope] [envelope_output]
}
*/
template<typename Geometry, typename Box>
inline void envelope(Geometry const& geometry, Box& mbr)
{
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, default_strategy());
}


/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{return_envelope,\det_envelope}. \details_return{envelope}
\tparam Box \tparam_box
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Envelope}
\param geometry \param_geometry
\param strategy \param_strategy{envelope}
\return \return_calc{envelope}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[return_envelope] [return_envelope_output]
}
*/
template<typename Box, typename Geometry, typename Strategy>
inline Box return_envelope(Geometry const& geometry, Strategy const& strategy)
{
    Box mbr;
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, strategy);
    return mbr;
}

/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{return_envelope,\det_envelope}. \details_return{envelope}
\tparam Box \tparam_box
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{envelope}

\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[return_envelope] [return_envelope_output]
}
*/
template<typename Box, typename Geometry>
inline Box return_envelope(Geometry const& geometry)
{
    Box mbr;
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, default_strategy());
    return mbr;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP

/* interface.hpp
iTjvOwJ4Xy/wvk4L7xsZyWXP2yBSAuHHI4k+SH0OchMjPOaUkdZ162Sy2oGxX3hSgJZZTpH+BtItrB6ZaZyB3AqJfxvJ9/9G0v2Lx0YmVKy36/sX9DDkDbIbuJIehvR8W0E+4NV8VQ7ky0tDvs0JjSXzfwQ0CHZ1+ApEVvhhclc0ZEf1+ZehADn25XBxk8u3yaWIXKaRSwO53EMua8llJ7l0kct/kMspcvmIXK6Ty9BfwyVILuPJJU4u/0Au88ilg1y2kMs/kcuz5HICLtmUYZQb0FYhbzbwS/kMS62XDvIRyHL9Y3DBL/V7Lva4n4+RtyByBsJVP+HbaR+Kxgiow3m/VVgfh+VnhVponCLipKW//pIxytRfnjkEYwBuSE/j2kH8TFWZ35kFiXtGsTEzd5R1zKRhqQtXcT9Xfek8aKazDxL/zukc6EVnAYYcLRuQzlkznSNtAXSJlOEwf6P/MrgzTO+MJokM9u2xGdZve8i3F7Lzvf3gwNWb6dwNiV9zOgt60Zluk17B7xDo2X7PFV8/GhjwXGzVPv5fGPiJtqHI06AiT14q8rQybRid/8z5uAKJIQGWjxtGPorHQJeYa5PGEbOfKG42dKVWGTMvYF4TIPFjTmtKwEprBhZ3EsaV9C067ofBuHeQs7c9+j5oe4DLUesh8iCEgwGyD0Nlmo2UjemkWL0PGaSpinGcpMLI7xHeIT4uRS9rxwHw
*/