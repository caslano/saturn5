// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_HPP

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/geographic/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/expand_segment.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{


template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
    : public spherical<CalculationType>
{
public:
    typedef geographic_tag cs_tag;

    typedef Spheroid model_type;

    inline geographic()
        : m_spheroid()
    {}

    explicit inline geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    typedef geographic_segment
        <
            FormulaPolicy, Spheroid, CalculationType
        > element_envelope_strategy_type;
    inline element_envelope_strategy_type get_element_envelope_strategy() const
    {
        return element_envelope_strategy_type(m_spheroid);
    }

    typedef expand::geographic_segment
        <
            FormulaPolicy, Spheroid, CalculationType
        > element_expand_strategy_type;
    inline element_expand_strategy_type get_element_expand_strategy() const
    {
        return element_expand_strategy_type(m_spheroid);
    }

    template <typename Point1, typename Point2, typename Box>
    inline void apply(Point1 const& point1, Point2 const& point2, Box& box) const
    {
        geographic_segment
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            >(m_spheroid).apply(point1, point2, box);
    }

private:
    Spheroid m_spheroid;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename Tag, typename CalculationType>
struct default_strategy<Tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::geographic
        <
            strategy::andoyer,
            geometry::srs::spheroid<double>,
            CalculationType
        > type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_HPP

/* envelope.hpp
Xyf9baLctypq4K+b3INL0tp4+XbfyrwHk2q3YVYcTV40NOVFbr9M5UcF7JeZ85m0NEPAV6LnF7hhlNkpq57U+fL1czwbY+1DpEyDt6WzaXZbZcPRJ7aRqU9kdspEp7DslCnbrm4jwlelbb0k7dujdArf3lbA+ZiwbG2Z43nVdOc6ndzYopfc69IrdcRn8pS9I5H5ipTPi7iRWj+jZFbMtldAHQrbrpdZjzprHjI2XSjuPcqspIlFT/2rNBUZk8y700RjPesw3W6b4yotn5T8yO1n2XSx286ynH8YkWHXhbGaTsLUpeJ2swJ0stnMstwdybDbYLoafeKUPpHZX2rrCt/+UnezjWcaET6Ni8E9LvcnCqw6paeFMB/W3p+bNlPvz+XcJ9OjdLrvIumwnY1QdSx2RqDNKJw2B2xm6lxxe1FO43+NILZf1syw2y4Yhz4lFn30aZB2eSokO7nByjbfdwfLetd5pr2uT2iiefh0qMj5hMD8cEFXkPzYNtNue+MarZ4rXSK3neVULpWD2M5LzLLrMRE9PEqP82vfyaab3b6T6gs+yrLbd6qMbsVKt/BsO4V6D1uto86y15frtPryO1N+5DadbP20zZ6TVZeTDrpM1uqL0iVyW07BdIkJUi6e7IC2LP1hstIlMhtObV3l23Ay2/JZ0SFGxu+GMoYXKR0is99kywubnRZrO16YE2hLSuYSfnpEekbAWYd57ryA8WmAxwj8heTHMSmPUj8dwj03EMp45Junyxog7IMu2hDe92JkBx+nrGddPfb1gqlahrYw9Y/c9pU9L612r2xnfWcH2L2S8oxTukRm86rsMtVjseRJpVy7DZlirY0pPSpu60r1xRWwdaXuO+U6t0dXrE/fSPaiQ26HeUbgb2Qc+xKXpPWPVvlqfzq0uZqtLTja2Ip1uIu8jPyYhE4v8Ds11roeftZYq0lXZ1xVnHn08r418vWE87dTsTfWeb24htc+hqeQ9uSWZtorZsNL1RNnG17WvV6v89hQpHSJzH4XOgSz32Vd68r32TKpi7sMl0pelCr54dnuCqUexljtdkn+Bsx/8wPzRfqVS0y9wrfbVXbe6HFY579z7GOVmx8ePx0qsv/vMP+Fzu9Up+Y4j1mFfrqEu38e+piVq8asnuhxEpeh9RmXlD9mmfqvvtFQ4J+SxjOmjYNWPv2lrwt7303T6ww6LUPGAPzbty5/P83bWvUNFj1dcwPstImep1qbeoZuo62cu+WW8WuNyP1F+qR/yrpYcRtTbuS22QL0KNcum5kXtefJHWnZh6kt+7On2po6yRmUCO9rqrvjIudikfM7c/+unZJzY0qmVzt6kZ6Ta9ydC6Wdqb7IYX//b/OczxLE+cvM9oYsw+lcxNb5cgeRCJvD9tCLjAQ/GUyK3PynsOu8udf8B1f5e83HSWsRuozR0tm+/LaRL8+kq/36esY5jwX2/d6W1NEDxvNJrLQy0enRrWy7TrE+mzAOa7SAuVPAHXGRXyTyh4v8wbJGG99Bl6+b8pGV44jWQ/S1WZF1ZKHYmolCFpwEtTpZJLK0JTVvbgrMSc3zaJ2/h3dqt35VPLTyrBZ9qCNxybpWYPlebDnLqMVqCnSnOdwxVvOi6U30+pArz/jvZ6h+um20GaevHmTo4XLzPFJn1pDXhxca9ydzDT3VOdt5hi1F2mOWW+YzlrzbtshI6N1STndIe07uFJh33iw9WW79SpyWdxHdh71Y8sIxryQ9paRlK3pN1dq5oYeUvzV/2lvyx5621YsNRX4vaVsnaYvtHJi2ub3i+s7pEZC88542KT+5c6Jt5Rjp3UFaV6Hrlfy3xZ2t47Q9fb427rnJUOZrXHPccdzMJlo=
*/