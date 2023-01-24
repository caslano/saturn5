
#ifndef BOOST_MPL_INSERT_RANGE_HPP_INCLUDED
#define BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

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

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_range_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos)
    , typename BOOST_MPL_AUX_NA_PARAM(Range)
    >
struct insert_range
    : insert_range_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos,Range >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert_range,(Sequence,Pos,Range))
};

BOOST_MPL_AUX_NA_SPEC(3, insert_range)

}}

#endif // BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

/* insert_range.hpp
2hpvJHDq6ScMiR/VSUxLnEME+4NkyFJcW8ZVGVhKVlY82EFOXPkh2xd7JmFJ9WjlrY3YjuUAUxR9FMGA5s+pTM04ODY1sTQ6cSexP5FZlOuA+QALsUSUEvEzNtxFTpm7mHAmEZvxZxT2H7nkOhwlIqJwJRKtA35zJ3LHdqdyR+eN8kV1J0sm6hriZSA5TqUqkBWPfh//nmnUhcr20SPOujvClyaZoouUag7OE5opL840qhHHKd+ifnD+09JWVqIcr2JeLktfqFpRgDmPWkxIojKC//gsjEFnglgup6kpbkNKtmA7Ln/W4XWRZKrBPbHX9LD6twjBwBsIDqdt/JCBi/PaSSuHHO2k8TeQerfDoP7gKM2nm6hkXXwNAK5jh5V65NB88m3R+CAjc56CC2kqtdl8tU0vb3peH7q1dwyWriZfMfVJVBpveSoW5FhmkGaI66Pi24nOfLL2PUt9OsO51NeXd6s1lO53qDE2ib8vNPGRBnyJVl+gkumksv42uP+rf/inn9ReaYLjB+Pm/UGB/qYzdXl6gwZHFtoP09qOlpj2fzhI+pT59aywONE2jfe+0M7YITHJ6lsXJbzka+SUWiXxFKG8vHi5PR4MneCovKx0bgjr7HF7EMdF3X6FKVsk60P5clNJOMnCZ+N4ViY2TmWHqVnHKarvAqUfD1Akg+8eQXM01IZeKikt4a3c02TdXxO25Ln1I9EA878a
*/