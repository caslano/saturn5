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
t2etfq9kjF5rFQ3VXGb5cLJu755lzQH3CH6Z/4V2cnz13g5sqgbbR8Lw3cAK8d/4nJxPMtbxolX/FjAORs0rSxKXcO1+XSgvPtPdquPLdHxGtu8TL9t7+h128K05CqUTj/EJRPpQ/G9HM0yU9U5PBg/6aEBp61oyRsO1dmCDyIE1+T2ktQ36wxqtLWv2nc/fzaeOy2jt6vR2QgHzjBf0sffpOAIS0ad1PPaN7tP31caDt8xT8b0xgOtO+dd/p94vcQ77Ud4lo903Tnw5tVC96+LU3NC7Ddb9sx/juE67tiJcqcfOc8GJrjxdssOl2CztPB21w0W7ws4SObRkTMs50JfWPbX/GOecszubrJcV8SXxXqW3EQevcMp2tIwJ1CNwf4XPtdsy1436XM255CryTMWxP23ASwbzPQzCFxaiB/GelN3+DByuxle15cSYwNkqGycrr8bJ7E+rz3cGaP10qs+kjy7TZ59r/LTBPn3n8mJZTld0WUBM0Jrv3v2Ww236kxF7tyRh3Mj24827xPrZKvcZjfYmXrUvSMdanczckPFQ33rGB+eraiOePe0Gx1x0XP/5SqJl35cjrfNYy1g00fZdAfUEGtr31Zi+xjL21SHAWwdL+zrdrd9LGHV5YIXsNSIWjqFs59PWvXYk4/A0b2N5KarOA908KIpayDMd1yZO9fQ9Py2q79Ed1Uef2HZP536p06kR0VlzPHcUXaePMdrTu7aPj3fsWJ65ePM4MUgnsFo/p0i5bbKfMySd0Y+Q51lj5PNt2w3gXKUgeWa43WGzE7sMtz2/dZ7Ok/JwA9d5edaYCTuXipQs89LBZNXf+fn7g9lK5hc5PLTTKrpLJI/y0Xl++yY+c0un+O/Gyb9xeLjDAOZfCA9TsyOpZtu9nxLrPr2CcerLwk46DNdUDgjfFA5OeTbrSq1NMJa7WuCWlDfmZhG4a3VtAEf1m8JSMq23v87hrdu/jrtB8tOHE7y62eHVLgPw127t0IFNEbDC+ddTYtj2faz8u1PyokRjoO4zFS5wl+0PvnYwUfN/9+ZwSyoq9V436L7Yj6dnFUv72/pq/w/o/C9BAPp9oyAOD9+jzelhDb+6pVW21u+9KbnJkfVnAV2cmpc3pyelTK3t/iJxvna5M2rgZ+IvRoXQauj7ndcj24z42xqL1Ay35fXPGnyRXeh24zmPpqfEwUbwS4keDvp0G/4idI05aypLP42GDwjgAz7gpWD7gN68Aj61OpZxV+nKSPDsLXCPwbN9oJvp7JH3gG0zhO/k0mBfOHSLNNh/HNgRGiw0VsJ6NViRA9tBgw1yYKM02ObAyhl3dw02xKGLabCxDuxEDTYe2JaDsK0abMJYudcXaLCJTtsNGmyyA9soYAXZhLluoBHQmZjVL00ZK/VhrnjgY1kEx0iUWVkXPA9E3nY6pO7R7GTvy3c/5gcejZilqEBRhspy8iwvhXt7bTc/XRsG2Kuf7m7icn3ouXixnyajt581Vu5xy1w9mjnQsJ+tNMM1Xyh6xxUC4+6zI+9XBzBGITLLktmTxpgyS1llNm+skwfxJgrv3DQqavQE+po85lvoSFFJ+WLeOhdYaGCWoOl/bJ/NF9t2W/1QmTtmM0ExU9ZrLxUerrvVXY/g7SJn3wwZgGycPbLYgQ0UsML4nUmtTljme7A1x6sdq8VajfVLqpyJiTksHyvP/Y4t4rzHmVe7A7tRg61xYFcKWEFz5ZMnHGKGjz/Cnr+N1euZaLm2jiYfjqdiQOt+MTtWOyNt9scAZ/KpHSNzAq38eM9YHy7LEbG3j9d5uGRHBwfTuk1pcnHMg+kIrnYmeGOWHtdFXBrwPC+o7psAV9dEOScIrBOcXKc=
*/