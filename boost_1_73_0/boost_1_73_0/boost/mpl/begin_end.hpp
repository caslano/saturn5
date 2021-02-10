
#ifndef BOOST_MPL_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/aux_/begin_end_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// agurt, 13/sep/02: switched from inheritance to typedef; MSVC is more
// happy this way (less ETI-related errors), and it doesn't affect 
// anything else
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct begin
{
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename begin_impl< tag_ >
        ::template apply< Sequence >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,begin,(Sequence))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct end
{
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename end_impl< tag_ >
        ::template apply< Sequence >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,end,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, begin)
BOOST_MPL_AUX_NA_SPEC(1, end)

}}

#endif // BOOST_MPL_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
+QJn62KZ+fSUIHNHP7ztGhp57jyB9XRVYllkzFAluyDhD+BhUk4SeH6dl8HiiYN9do3m4l9hjeJ7mGNeo9Dv0ISlRxvp6Yb9AlBLAwQKAAAACAAtZ0pSWKjhxsUAAABLAQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MjFVVAUAAbZIJGBdUM1OxEAIvvMUZPdsmjXxRubiKxivG7ZD7cTpjBnomr69tFVrPMH3A3yBTNR6VglAqQzVy7ssn7VFDdDPLV+FdbmqWP0woO4Qqdv9cIYzPuckxR40RQHqN+AOlXaXFqDU4nT3A8lqzQFyul2eHi8u7BiQCk8e5MUjIeeM/+8jl/iHfBNbI6ArqRb1+W5fgNTXaXJzgLnMKtFv/DLefufbkr9KS8OCkY2RB5OGNgquX8GRFW8iBU86VjsB3TfvuuLojv99AVBLAwQKAAAACAAtZ0pS2eNEes0BAADOAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MjJVVAUAAbZIJGBtUk1v2zAMvetXcC56m+ePptkiuAGypFmzpbEROzvsUig2HRuxJcNS0nq/fpKdppcJAiSKj4/kowKFUqVM4pQEJc+FPo7YvYo2k1My323Xq80y
*/