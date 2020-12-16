
#ifndef BOOST_MPL_ACCUMULATE_HPP_INCLUDED
#define BOOST_MPL_ACCUMULATE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct accumulate
    : fold<Sequence,State,ForwardOp>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,accumulate,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, accumulate)

}}

#endif // BOOST_MPL_ACCUMULATE_HPP_INCLUDED

/* accumulate.hpp
XiRowxMIB1gnewC1SzBKaNlcOSDVTd15TUxoWeY8vxVaVor77dCyE6WeM1DPp9fZoWWPPu/bE1o2Jt5qaKBezhytL5QbOlMcjrVoOFbeycYhxzzCSeQUvsfzTHuMH1ve+GXxY09s3Kf4sf3lq+gVaDNkqeYMJ3uBtEbPuuvnaIHHxwWGeaU1er5dJrna/dQn4WS1dLxecgkYod++QthYaT8LjfjxYikGePOV+xYv1jz/0qD903Q82CxnPNgsHQ8W7LTkcnyXfdOyHqs8OeTtjAfr72o8WLlP7Fi0R+acp6rtyFodzviwdMMX3bhSX9lKapjH4Wjy9PAe7eTnwYEG1G1y5lIKJ5V00EPQwH2ZbnXdXB13aG/Deux1/NnJ5AfsnOTdepJPmR0v/iwf9nRM8nnj9nf82efqaT44MbCM5VK+6tYYE38234o/e0C2GKVPYVgdf7ZgbqLQp4UMJpL/zivkCNFplIQZ4lqSfh3VXzX0aUz82WOkInEOLzCryuNE0TIOo6TE8Wdz4safTRxfNituPNnE8WfzYt6NmPfcuPFqE8e7pe+Iif9UR+Pn1+O3qjF+vNrsYD+7R65tjD9oxwYPswftnSk6kq8MGo6i0LgNn/6Vxs0RP1UCXya8//4G+p4zUanErJsTo6GM1A2aJQ166Bd2yNpy5Olr8afsQ8jaLsSbzdrHeLL+PeTnfcV4tDo/dx/j4XrN/K7G8xX5PZlclWJvmGpOcq6flQvnSMZhtaxq8X+bvvexDVfiSvA6vTg2tHHVwIztI4Q/Y6+VP7NeOeAipwnmXk46kVCC2FUuPUH3S0ZwEH0SO5lBqxl04GintSVISY7LQHHEQm7IMehua9rd1ZtTxQA0oBxlX71b+PLBJb4ZpG8Y0BRcMfmYvohKI3oyZ9+emINeUqccTe4gOYe6/DgyqF4qt3c6+CYe8epuk+k6mY7e/tRGdjuQGaYZCudnfnCBaYmacbijitJkC+DaW2wd93wxGxhyTVWrhtFVnSVNEZ8oaan6C6fJTcMa4wqdRHtIi8nAb19V5ao6OhgKbAMPN1fQNlGa2nq1HX0i+1ynlgxDQLskwYB1qtbQ2igCizwjAuf35PlboFXv/Q/xD85uxt7DmpkCqotrv8xF/Ds6FGpdDNjcST+EQ3NOpuacTHBOdoB5j/ob4S0up96ecBV6mw+GjktycfVQvEaGtMWJ4rGxE0noRHpo4oej6MHlpofswPsWsglAdoiNrBcho1rh5tZ5pePCrexAxCr1c5R6s8oqtYO3/kLngyXVJPwfUePxv1J1o0xGb6dPg7jwEQWx0BDWP5sK81lVYVpWwitAyLAZHTtKU+WRiNk68Wb9frD5zUg++yy9LcpCBq5x7ZBFTTRBltko+Ehsro2CvpQ5BMm+3VE8bAattWpqEjPcgCrbDHcztgHb1u1KGlzmm0Ej1rbu06T6Sra12nKix7U2a4+TFTplcuACIBRmbadt35G2iBgUB05b5BoccAbgMvXlfFZ7vRX4ugJGgMv5/jnTPBu2vaZ6O3U8Av4BJg/3jpzBYXyiikfkEbfWyiMTuOJHaVaeeR9LDrdEbN6n7DUWddgCO9JnWdSnKnQJ2UmqfmwLqqMbTKmuLjxTG+VJtd6mVettYlXbVl/WzFcOVvsDRW5NsUmg2BOutEVU4Ie2kXLeDFs2zZZnbiD5Wn3Lg+V8DT9duD+t9rZI/PvTMn9iGc/kHfKP9NNztKZh3WjKcSojphqS2AX20MBNDnk4kYb2nMu1BWwcyyJ1rlO58Hl0FFz12ZlOveFD9ihIleD/8IKgybDdvltOjKJiTJG11SNFtqPLI1w4y5lbONveLFqo7xyceKYWN4s=
*/