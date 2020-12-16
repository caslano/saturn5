
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct sizeof_
    : mpl::size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, sizeof_)

}}

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED

/* sizeof.hpp
CewvPPRt7fastR+np1c0UzggbnWakzvB1/Q4sGyl9GBFwwrxfShCtRBkCok7axoNxlBxyZ2Ix7LWTEdKC+7nCIk4j24KB1Q81XzyEVjXU93p4qKJ5oAD7uDFGGVzXV9gojwjjyYcCJS8FLOBOiRc4isuNy9lIIQN9TQ5ihDtiPwyqjNGsWkPme413eVUPXGr08J+N2FYNMn01i5P00e6CKn4gt+3oh39bb7bOlA45qWTt8wL44q7r+PnunHF5EkD/6/dTAmTTNBBa3qpSYQj44mgK0zqCh3asRnj1bywulV0XFV+dLP/0Ec1O64ZBaIZa3hA3d6bdtM3yyFMYOwQyGqlJr65HC8BN9GK7hvrKtq9L5S2L9wmWlZX2g4nVdqGV7TT+Lz7NdWWPokaObm4+xuETHrF7rofFJP/JhDeHcnlhi+uaK8rtz7j0hE3NRhCoZtaGtvEWUOjm2jmoYk6JE+rjbZagVJvgRIjTnhtZ7zqyoqb1sWPEtq8cDtaVKFbNAktalXDVl7cfaOGojyhRIvQysWT2uvGW581LakhIvyFc9qaYp4jQ/YZf0WcHCF4GUbV2NueIo/6/6+D+3b2ZsH/QPNrNbHbohm3DNf8sshFFCto3ZM+qU3Ruie9oo1oPZLNn9cXFy9QYRqFWVnBnGL6Wzz7kJeLxZgKP/o0dspiTmb+HEwI7iCCTODa4egFMlHGcASFyhd0WH45l5f6wpMJn/DE7GLiJpLGLO89EfzHPbuEOI9oNC8JtO5IZhM5iMLogCW10OxYa7IHeItrdh9iBjTrwY/MOmqliRjrJsU9/4WYnB4xOeGicVousEZwhCMDxdppqP1+oGgIPomMlVtNHQxwf26q2bcfjT9Qkdc7XMrYadP/xP5rb3VT9ok+BCRrxZrVNmsoOZWR9QqsENHggh7oCPDvNnC1VqIMKhB5C254vakgHSbBCBE4fJaDAqn5sOh4VGO7xd3Pg2Da4EMejgjqJOtfQbhwIrzIPPdrU5j6rmATYGVS2VtQXysHIb01izLDgTBCn83JNKZlCIJbhQQdjyI3cLax/AqEsrmEIkNM32PCFbG3Ck+EMuN0mf0wmdT9X5pJ/nWXcq0e85Ys9Jn9PvL55hl/hKEoJkhr0E2tE06TAZSB699JLPlR5nLKtKHYBQP9o/eaHD7DjfAZFAxjsAAhLrh410QAoWssEHs+VSB6UH+LYpNTHLnO4p9lNLWrEWwzFpzRW9QHd8Zgd7gz8vXEZvsm4EQYIsKwtz/f7PJTgmFhWfGpmaInsah/pEPY/7qi/SG26ttE09rVk0nfxI2igo4RyfGZDA7PV7uZUsit1VH1PRp+VuKH631QSW6hJKtoZCJlc1K2SWRNkC+yhZEtbGUTDlKR/kazahHFHLyUiGxXK4isaQjVaRpv0lADs5pVwI+cmXfqAt1QYJ0s8CX1r7w3CJdqIq7a8+tNeb0j6m22LhjFhZyCF+IhhCLwMd4mI2ogszf8gACLPFNtmfLl9QS1Lqh48ddJ5sl3y0iXPcmnQ+QN01/hjSCQp4t03jHb1fXo7boZ49CMPV9yM0ZQfaLvvLW4cwkV8G2p96srS6kb38QNsQIdXKyxqAXNDON7OfDhhDuyJJ67v4G9P256HUGW/jH5mlU+D5TO+FvuIqcOyhfxb8BnJo5W2YXcGSDOX29H7ZRPp1ol1td2p6fh3tX14n+KtT4uRLlwl6TJSLSgb9FQmo3GVuoT0WHAjHKlMS609LwnqsmPnNohAO9qqghfBSCaQkazACSIB1gySMw0JwAVhEvftL4Sw/TDBYkvCr4SVD4EwFC7AuRiGXVNH+uGy/GRYSD2w9AG5LHAYq2IfGnq3P4=
*/