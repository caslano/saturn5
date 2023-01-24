
#ifndef BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct contains_impl
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > >
    {
#else
    {
        typedef not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > > type;

        BOOST_STATIC_CONSTANT(bool, value = 
              (not_< is_same<
                  typename find<Sequence,T>::type
                , typename end<Sequence>::type
                > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,contains_impl)

}}

#endif // BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
YJdM5wCrqw4uaKk8wvLz9am/64C5Rh5CT2+CbKc9YWV1kV0zcKVtUVdVf/G1GUT7kxvUBMJur8uH+Zudjxt64q4aA/iKy9aDoNX56kFD65tk58w34dnf5hK4VtzO1/sc65ibp2Mu/S5fMPDG+0BbTM192Jci/kh/mPB+NOjdkHk8fzfiPIb9YiI+2v9RJM5/SSWlctf21iZpjObip7ZojN/OzVk7+ZYxyB6SRHz9Bm0egiQyCBn8E3jFNqpxTg6TpD1Jy+pRwYpFxP+Jw5MD7OZB9DnjKjX7n8iLdjqfeCHCz8desf9Bf4sOD+Zs6KS3D7yQEXmFOHO6Uj9iM5yj8Ae3Y9+Gtr/EBLcjyNFcL7woBkW3SPEfQtm/TSG08B+iTdBdyx6Zo/yGyN+fb+iDW0v3aoJeFFzKLhIDBK3ohtVnbaWMBQ7dh6U83NkFzIu59T9H62dwDmyY3Mv7Zk40Wi+RTH8HLTWdot4Tdn6/h2n8g/7ODsBOKD859bgPuEfzSy5JSRRLlZ2YSk2meSVQLbzCDFAnej4Eq7+bDR8qT1sABK5vu2CKddyImA5OaAp5LKh/Y3Jjpmf7/EV0eVjRHlO0ZlqLsu0iPfbsRWefbAf1BfcL+nrIab5wIqU7euNAAPp1Sj3tCewiwhrxLCP+9RARLKx7JcwqP0t5rBJ4H9rj/TJ8AfaCTzxAX175ofCnzotuOARx21YHvn+t
*/