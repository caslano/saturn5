
#ifndef BOOST_MPL_RATIONAL_C_HPP_INCLUDED
#define BOOST_MPL_RATIONAL_C_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<
      typename IntegerType
    , IntegerType N
    , IntegerType D = 1
    >
struct rational_c
{
    BOOST_STATIC_CONSTANT(IntegerType, numerator = N);
    BOOST_STATIC_CONSTANT(IntegerType, denominator = D);
    
    typedef rational_c<IntegerType,N,D> type;
    rational_c() {}
};

}}

#endif // BOOST_MPL_RATIONAL_C_HPP_INCLUDED

/* rational_c.hpp
3NnI7yeP40mBP59/qH6HOU3v+YtIdX8wi7wW+fE942uY3Do2MsJxLDaUN4DDdjI1ciwES4Ehb53UywHmMKlgD7C4c55QdM1hu0K9iv19JRqU4z8OBC66btjBZv34r1kBL6Qo0XzXG12ihChPk6dPv4D7JC5Kosgvx1hM6nCwSmu/SOftSQtWyvQ0ZqBMJVE6DPk53V+wI9oz+67Jc/EGutzUwkSf9CcMohP1+1r0j81+1XSY1QY/rKEbIua5Cke0lwMT94TS+8bTKzHRkibVwWYzCP5kQsISPXkGEsK33L8NTERpovz1WSOyGsmQuVfgvYhYTR4WCB2FGMtO3OLzEuLOyh/a7xspbcSXoqYiqhEMaT+j+RP3BFSj5eLloufqzqxFmtL2nqLoogDe38Fn2v5xR+VCFdPagb0RbSq2INvjg72PkiRp2oEJ8g0EvEd6H/XnariDzl1295UJ3Cks2EWKePapgdOwg1cgA+XYVxxNUvKRdtBVnyvjQ/jD7VKMZcRQpEWBeWhWp4XJUs4oFqdAZfplGCCanDN4O//PtQ+Ekff920WONFiLxs+PEA+lRTCqMrmQDcZxERbhJRHWeMaHqV7UAhEessiD2AeDaP64D31vJZ3SMN8JqnYZHolflvCzeySLOH4Jj85DceQkws/DGG3qER9mKwgZ2m2jKl5jBXU/S8WJ9j/EYJbrtMIVL9j397UKs1ik1DQ/
*/