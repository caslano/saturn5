
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
zxi1HrRpzs6Jy9udrec4HCCtx3lAMuOZP7iZnZZHtDjfXeMYQwJqy4C87TuieM2fBPO+u0osJ1GKN2oepDn5bRriuDrFKQgwJbrsmEpt4KuyGvGAG/dyZTG4HdZFLbMLF7f+wViQnJgqhBs/CMwLnAeykJDYys9GZ9w08EUEfgXeDBYPAm1RwCDRJ+REQMANzM3J+bKxsUHgzIEcccNIM8TdCpJxeTHk8jPNAjhfANJV3qd+3NsdUvWmOzk8OD2cH5dWE3ge2Flb1pmHcx8b7nhScLGSYMajsrY3uja9uAhpKKrNyzvMIx2iE12fu1+b7AqWEMXzIrsyJ1xntr8Jq7q5WbHac9GaS3Kf6u/OTgM4OKNhJ5RlUM5wUuy9TuMZyjsxG8wfkWS3nS3PBqxSNuS33bcJmQ8MWWRwpY3Ngg3+uJgA5v2MeAV1uwYO8S0VvrpLUvkFdX+jzF1zK2sezPWYjLI6xsO5HKiU19ar9Gqmh3Ufd0OsF/zEcxyc1T8TnENfYd94Cf2WeK3buLE/n+BAHr+o/3IH50yknMBiXBiEdE9QQrQi2OM7oz6UrY8lTuQv80QzzL+Mo/5x3dFJ1dpJtUXd+9x9O+1VKjj/N0/0txCVbJ2bwe1AVbqcGYHMw3YLjpnt7TsM3cDFvfYFhwn+2scNuSrNq7KKZEt3BTto0TuLCPaVloiifJlEimIgzgaeER1vhbWUIMLZ
*/