
#ifndef BOOST_MPL_PROTECT_HPP_INCLUDED
#define BOOST_MPL_PROTECT_HPP_INCLUDED

// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    , int not_le_ = 0
    >
struct protect : T
{
#if BOOST_WORKAROUND(__EDG_VERSION__, == 238)
    typedef mpl::protect type;
#else
    typedef protect type;
#endif
};

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
namespace aux { 
template< BOOST_MPL_AUX_NTTP_DECL(int, N), typename T >
struct arity< protect<T>, N > 
    : arity<T,N>
{ 
};
} // namespace aux
#endif

BOOST_MPL_AUX_NA_SPEC_MAIN(1, protect)
#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(1, 1, protect)
#endif

}}

#endif // BOOST_MPL_PROTECT_HPP_INCLUDED

/* protect.hpp
EQvLOlf02ePxTemsjdg0SVbDiwcs5Fd7yG0o+wQb1K+o3bbMkIUam+pI7iw1qc3m/mcffM+HzVtpZFHWuxt2dQSeB8sf7FtqUEDS4R14j/CiXsnhe+Dfi/tHQSHPi4TZOgL6dt12WPA83SObp2RYqKzMS8xOFP8LfO/qHk+UQPjemTJWtcHauHOsd6YQ8HCxJMcGe/q74YU5VIxVJbY3pNRqsZpkgXL/f2E2+BREs6nKlthgFJgCoWt2Os0QNP7uSASFWxnykEXs5CTEB2PITwMl1pj6oTbtnOWwiM6EiBXGNJdcsueYmk5jaz3D7l1NENbpAU8ygktfpKOA6khKwHIokNtICKU6HNI6szzB+Wi63CSzlRj1kNVynXD/Kw3DdXt/X+6S0P+f2mUhUcu8PyGNVkZJVUXseZKATT6P1WFT1RoB/9Rw2JY6c+Md0QTITld89HOy3syWLw6LpcSGzLf81ul3tUZpSlUL2Fp9dwM/cDdoDGlsCWYdfaFgTByH/R0hII4XcRw/7eN4HdtnNrwd5pCsqwbanu16Pvk15Au6E3UGeVpWNG8BT1rt6RQ0ZUM7h1orLVVGQ/UfiPFhHfLLdPj1Uv4BUEsDBAoAAAAIAC1nSlL+t3PwzQEAAFUDAAAeAAkAY3VybC1t
*/