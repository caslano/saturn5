
#ifndef BOOST_MPL_AT_HPP_INCLUDED
#define BOOST_MPL_AT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/aux_/at_impl.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct at
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,N >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,at,(Sequence,N))
};

template<
      typename Sequence
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct at_c
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,mpl::long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, at)

}}

#endif // BOOST_MPL_AT_HPP_INCLUDED

/* at.hpp
FSVZ7AQyS59cvi+n3NXH08eeVllPyCW6VpWwcx0isZeIsnvEg3VqIQHgtQSkTw+PYDa4RyyssoPdeDlE685G9FcyeTdnknYUURqrKCGmI+2fWHzS3BfnbNL65316PrKQj3g1TUCZq6yefIiGay6Gwckqm7SpjPKmMs2ezXaXZJONANrwegXuK9T+usySzc0y1LlLc5CtC47jFpWBaXPAh+H7OKh1TjYiBlbza+IjA1dTD97mYg6y/A5R6m3u+jTd6XwgUKxe7JC59FvyciStT1Am70C+VFdxBnR+u4o+9w6JzoQYbmDZU1znP+7xeqnO25+Q/3+lP6+j52b6103//k7/dryNf8b+IEgv6WAG8tE3M+0HC7SkRSOJso/PqpNdLqnOKcUXqwGtV/d/ukMZFJ/mACTUThADn96zb6WXLoo/hHRYDb9DWod6RS1t4DIsvjRu4fBTeP4+R/IL1EtZytKAQUBr/IJUFRphFlyE/OY27AJqqeOoyVASLdQA5IAHfgo9V+GpeBnyhOXPzZ9Hnt4SpyJD3y/VGusZ02xLKo6jc0dp2U+j4nFLoVDdeNjMIAagPgYZcKr0GeVWqk1G7WRZph2XOe38WmppYqUaQ6+isQJjVJS3Vl+pVB01L7zFZR19VcruCqQcyOWqg9rRidJrzbF34Dhs0zIb3yK/LGM9+PW7VHtdrEWM90Jg8aH19oYKw5op85K2VoUkMbZ5MBCPg5bGy9hxQbHhuAPr1zGyZlCjsd6SsunBjdULxoIj/diAWf9fOoz6995nrf/vpaj/yxz1f5Kt/tMGltqq+D7ApYp/Ya/iX0kV//V2qeIL7VWc9yVLFZ8dft5sVSphiyRE7Y+//02rfXxvBet/quPLPk46etzDaljji65vHb4vGmxdHKWCR3nS6/apoemM8G576V6QTGbfrjd9uGlxYq17s9l24uXb3cSqtVDrEHN/sWB8n8WTDFK8OPm7WX7FuuU2xfr3HMnjpzmizKp1rG5eNRjMUwxuNBh8Q0yT1PCimOtbqW8qA3XpBeH9SKsG0O2lYB1Ojs7SaYrjwEeVN5p6k77YJaPmDTdZRs17sU7I5U86hNPcViFXixDjAPRT/7FP88t5KHp90xJl70odf2NEn7yzywzg2OvRIC3GMec/QZ1aBorbqK5o1bBufCuvKAYW0nOZG8/t3A1mcbw8l/FzAT3HXHhew89+eq6X50J+ziJV8lfejsjzQcpTvpb26TlqkXpPlW5kVGNS2ox2xXFs/4cN5nh5eZWumVdvtG5t5QAYp+Vk+fBrM2/WT9B9EiaA6dwiVFYu/Bd71wIfZXHEc5cEAl7MIYcGCBIBEQsogiIQQIIEEQkmaBQtWB9gP89HRRJ8ERADyhHSYouKrbZYH/UBikotKFpQFLTYhhYttlGj0vrFQ00x1WiD6cx/dr7HXQJB7bvHD/i+/XZnZ2d3Z2dmZ2dLfRvAGCzDbgPQAxbF/f41z1DvaU8+eLO7NxUCf79dU5qS+fgR0RQVEezS2YbhlbaDvpl+oFh5xtNxd7c83qLBaJpj+1qaoqpPgr/GB4tBf9oyvsDjeNkkjpeyAjDasUKcbeRvWBs8p0Yb/aEAeklN+9cP1+Wg/xd7/IHthPgF+G+X4xvTBYgOucmnjfSyzhWegK31N4TFPDtXmVZcrGjB0lFQzjuUaysHRlN4RQPI9Ctl4CHL6xCzwm50gjPVEHcM9O/7z1cQh/NqhzIX3+KRBrlMrpZhs2JtqEc4fii9BvBaT6+wMs7ldYDnqGOOHBN1DcBvqNf/e44I2TDFqg70CCNrl8XGN3d+et3jKebQ1zir3b3dw2wqsJYRcHTI7pvdjDHKiDNNaWo=
*/