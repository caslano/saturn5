// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_EXPAND_SEGMENT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/expand.hpp>
#include <boost/geometry/strategies/geographic/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_segment
{
public:
    inline geographic_segment()
        : m_envelope_strategy()
    {}

    explicit inline geographic_segment(Spheroid const& spheroid)
        : m_envelope_strategy(spheroid)
    {}

    template <typename Box, typename Segment>
    inline void apply(Box& box, Segment const& segment) const
    {
        detail::segment_on_spheroid::apply(box, segment, m_envelope_strategy);
    }

private:
    strategy::envelope::geographic_segment
        <
            FormulaPolicy, Spheroid, CalculationType
        > m_envelope_strategy;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, geographic_tag, CalculationType>
{
    typedef geographic_segment
        <
            strategy::andoyer,
            geometry::srs::spheroid<double>,
            CalculationType
        > type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
3EPo4hFdOLszLSVNzu+EsE9srW9s7QZ8IzP+QePhebhG8twjyCtR8uTbR3m5c3KT3KmpxtUS7L1wN2d6+fJl/Ub6hLmyf+V8J6hEdLkCV1Nsbz6GLslXKl3kDol2BGuWJ5Q1fdnLlTlnipy7N39Ps7xHeVeLfMmLfrj91JviIPKTBk8YNmj8kBFJQ65OSLpyTLl5IWUh+7spSerbBr493yTfPqBPR6tt1BT/fXYqB46/qyTPRuFe1hI4PFBnjzecfDP3Ql40ZBJG9kKU3zTbN5s8ost26VO2mvdtfLr47ecC79xy16DLukP2N5HXX+RdhivS+vIRAfKwipChSQtjzftxYw2NgNYxdOvDxsMLENAIzoFPNUGukmmYl2cOXu5emvX+HneJ/ffOZN6YM8vw62lbi7WvbR8nP4rRLw2/jSPRB9a1jEH6WRBL35f8iD0PnyY9BaPM9Fi+U8JwyKcoQrCvar1PMocdKN9Z87VN1PkEqevWO+FbDNmcEbTWr1LR9SbRdb7UrwNKV32k0O+xJnF8It2dW255O91Jb3eVIb9eQ+sZw8RH7XaIG5IWz1VK/nS3MgqcNG0e7S2UtmY/0+IbL0tFZv0oHKwD9fM6FpnqvDt9M0WU5p4bzp77Esu3V5zWmeS+xmNG4NdkvrAN96zW3q4Opov8W7tNEsJYFeRMk3xzwBIVcSkb4pb/ph3Lnc6Zv7rqzquj/SlLuY5+3G7Dax3pih/jkC7A2KdtPISdnlB0Mut67BNGRAko0BxeBTdo86QAnTKnZ+vKhFPe/ncMJqlxRUw2+/bhZK/Lo77n1VPdE2HoT0qRvkWlx6n+WNJUo8hQ5n2pP/twg2ljRQkqTaqj0fvskNJULXryOMIb5xFC+v5NjKTPa7Utp/qn/i61x+54tlnSKc9lpE0P+H7uCknnbqlPO81zkeNUOrEG6vXvp0JIZ0C6rLaPiMn6rjX3SSPw86LDJunXi8f7dMiR3jyUuiNjla0/b20dl5z6eOczulabKnq/23GC0e/mXmT8HiK/8+X3ePkd+G2qI5LWWtIv15T8Lpyg0pozM8J+2OwjJj1lPLgWVxW3BrdRG/eVDOOaempOVpI3Rz/YkT09BJkxhkzJQ3X00nofVGQvwzWS8e/3yPYkKtm5bk9WSqreaso/M+0wx5EysezdWurTpKeNCBaLDvNwCwgfe43SQd2Im+UJva+v1Ng3Lx+hfk+zyK69xgj4gdTld3BzkV1ik62nPyLZ/ra4m0odlnsgvluhcjYpFq415lO8BOSx184ufKCth7XO37I6cK1PZ+O7xzPV+bi55ehcYL/3Ld/e8eiXyX1nfHx9stgVl7Rp4pLkvdj/vdCdmpaXQiMxwmf4va/FWM6R85Q+5Mg3PHz+GUlkhRlva6u8lEq2s0K5xOPOTpX8nGL6UxfnuNVLpupL8oz+2DNT4kn0xSP6yLfvqCfbyPdcLf3Xkc++vl7On3JleqZ+ZsJ2BiDjGSOzk2W8nQyLtfH2el95eVNyvfKVjxk508rvMx3HImvfqMbazbqfsTZhne8z5gTcgywVXWtIf3eBaQduitI1nzkgx3zc+pWoPO5lEzE3REO/c+R0pjvxWePBy6Ud9jHPgBZVtslVEiOY9/mndYfI7IOrI2vlK0hriVNa5+RkiuCQvgHh316nrJNzWkQaAzOhfndrqk+OJ41b4twdSs0I3Y640zex5c6M43fpPjfkVXok2qpf2no511VZznXJt6JLb1D6iUEJNPSG0p9Uix6bIvOm7DRb/1LWffvnm1htyySr/oKzlvlMZpzP8sg7of080yTrGUY9Hy4zdKvURvKho7TTw5IPl0gd/B2urXaHaJr+PN8=
*/