
#ifndef BOOST_MPL_UNIQUE_HPP_INCLUDED
#define BOOST_MPL_UNIQUE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename Operation >
struct unique_op
{
    template< typename Pair, typename T > struct apply
    {
        typedef typename Pair::first seq_;
        typedef typename Pair::second prior_;
        typedef typename eval_if<
              and_< is_not_na<prior_>, apply2<Predicate,prior_,T> >
            , identity<seq_>
            , apply2<Operation,seq_,T>
            >::type new_seq_;

        typedef pair<new_seq_,T> type;
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct unique_impl
    : first< typename fold<
          Sequence
        , pair< typename Inserter::state,na >
        , protect< aux::unique_op<Predicate,typename Inserter::operation> >
        >::type >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_unique_impl
    : first< typename reverse_fold<
          Sequence
        , pair< typename Inserter::state,na >
        , protect< aux::unique_op<Predicate,typename Inserter::operation> >
        >::type >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, unique)

}}

#endif // BOOST_MPL_UNIQUE_HPP_INCLUDED

/* unique.hpp
7bI9tLoeJqASjh2XH+yvn4E02dT3ISGw77P9+bPB01howQscMS/JIkmPNyx3UoXFiE2DYMEmjw+z+SJ4GX/3X/y72yeHeeYJ4plNFDsDH9UWlVEkITJPYZ6WdBxyzSGTIkbxNmyXWLSbtGbnsgNdy4b5V/aZa3QhiDcXYA3gm9yCbXUs6DiuM3AtC27vA9Ykd6GiaxS1YUb8DdlEZhozbQRljtXxXpuxXqdH/wyzlY5dsNhMCq4TmblgdgbdK8uybEb8K4YHovZf3Gwq/P+4nXiYB+VI0EmaVKhGUFEbBGgKjFisdU7wd/MMdJwUoJBwBciMTIQQXzcriJDrjULYxYmIgaep3IGWUKCuQTpZU/4DiEbq+zNWBzKhylxLKnI6ZF7G19joBMeVgF2iY9A7CbmSW+KriguisiK1gWchVCQTQVXMJtrTUqYjliav1STI3djUpVyvKaDpzjXN8+ncD+4W7nlVbzF/COrRmZXSPE/qJ0Ufo+j1IBPp8YQqiUqoN5BHGlXTLYVAzAt4RcygXcRSt5m3rbGVulol+Yg9PxJlY7yiXO7lJ/b8zyQrx1gIzOszGkET41HvWoqqkdsvAXxkCu/L1WJTWWgXPnTXYuONjqVKfh82dblcOsb0fjwx/OnY7l3BRGFIRBKe
*/