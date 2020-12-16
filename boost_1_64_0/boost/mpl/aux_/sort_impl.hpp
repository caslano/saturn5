
#ifndef BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/partition.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Seq, typename Pred >
struct quick_sort;

// agurt, 10/nov/04: for the sake of deficeint compilers 
template< typename Pred, typename Pivot >
struct quick_sort_pred
{
    template< typename T > struct apply
    {
        typedef typename apply2<Pred,T,Pivot>::type type;
    };
};

template< 
      typename Seq
    , typename Pred
    >
struct quick_sort_impl
{
    typedef typename begin<Seq>::type pivot;
    typedef typename partition<
          iterator_range< 
              typename next<pivot>::type
            , typename end<Seq>::type
            >
        , protect< aux::quick_sort_pred< Pred, typename deref<pivot>::type > >
        , back_inserter< vector<> >
        , back_inserter< vector<> >
        >::type partitioned;

    typedef typename quick_sort< typename partitioned::first, Pred >::type part1;
    typedef typename quick_sort< typename partitioned::second, Pred >::type part2;

    typedef joint_view< 
              joint_view< part1, single_view< typename deref<pivot>::type > >
            , part2
            > type;
};

template< 
      typename Seq
    , typename Pred
    >
struct quick_sort
    : eval_if<
          empty<Seq>
        , identity<Seq>
        , quick_sort_impl<Seq,Pred>
        >
{
};


template <
      typename Sequence
    , typename Pred
    , typename In
    >
struct sort_impl
{
    typedef typename quick_sort< 
          Sequence
        , typename if_na<Pred,less<> >::type
        >::type result_;
        
    typedef typename copy<result_,In>::type type;
};

template <
      typename Sequence
    , typename Pred
    , typename In
    >
struct reverse_sort_impl
{
    typedef typename quick_sort< 
          Sequence
        , typename if_na<Pred,less<> >::type
        >::type result_;
        
    typedef typename reverse_copy<result_,In>::type type;
};

}}}

#endif // BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED

/* sort_impl.hpp
Lnu6P4Za/QEGV7ZAYPA7YW3piq+b+rDF8pEY57mBrVZ2RmhHO3n7eCU3XzBHcUEaP+wvkgqbL8MnLVN0V+7Fs4umw3BmJAN7DWOnw1uplr5TvPmogb4+p5j4N5mTdj+SQX80MdHmqyj50JED7p+m29QqZnd+Q8/sO9TaPV98PWLGpQvtsfxdM7z/XIooJz9O9o7jGMdm7BTah4uebeeZisXyRH0CnH6tkYlvurOkmalIfjQTAeWq7LbWD35twsX5wW/pkZMh45utgvW0IuhFpVH9rr+ccfgi5qpcF23Ds+BSfZBtvkzA7DA/pgQ/g/nmuzj+Ngi9Nq2VLjlDsaSykCMU91M36TXXf9uD7CeGUv/nYsT9nomD4/N53icN420yUDe5NyJiHiPr7nHx07ga7Z3q5c4aA9510GKsTgA25hwWqVMX8/TJvvKFSOaqoarYVn4byw+YyKX1R6F22YYHrGsYPT0WMD7JHpGzMdZZBfNaLZeuPhFssK7gP6VdeLZ+ntT0/YI5Q0xFZ+MEXN5nwXTexrPfFtJseT38O9nKBIVyLB2twXEfg1lbYiz1S2ZhZcQvLkhfzOsb2iCk4CJcjILEqX2PuC4nj0kLw2C+L0KON++PdUZprH/iztRvrdFq6Fqo9TqN/6pjuPfaA9zd6MBPW9+xZ+Bp5noaImChGeUJBfF6/wU+22YqS89v52OHYezep5FjnhmJwvyFsD3ljND+xnizolJqdv/Bd/fuyCrVChQXx8mTh1/jpX6suPf4BD1Xxwrl+Zn0NZ+Ky0cPoqByghwYd4VXDg2Vr5MvMnbPaXwZfAutdqoIl7jRVHmdgFdZKtjSYxAXjvOh+RcH2d/2NCZct2Cmw2FUtumCbz5xeJtUxqhVa3jiYK1Q730Kga4rZZLaVKgeLpHRRi2gtuI4J8z9y9PLa6CU7c9/rKFVQCFe334u/U+o8m0rN1w3uIjVilvFR40dfDp2Cwb5rWO661BEzF2KCYYVVDrky7TxXRFv/xDDd3xGVc8FWBn9GK6HNqDvslfSZ1UKp56nrDVN5+u+KdIk1oB2CuTK19d4tWu5VHGYwwnds2Vn1QjW+Usuu+9GxUfKomTwISzb3k8sMLjNiKFZ8sqINlym+1HktFTmha2W8nV5MgNGVor3n9PZ91qR/JHZgOvtpotNcwTKtp6GYmk2rTZMRuILJ0YnZQurUGDsIn2RMjcKLzZO4bH+Q3FEtZtYX2OAr/fPMnL9Tercug6XixY4Eb6ejB/K7v1V5fP50zA79KXspXWfsxVbYMWAHH7zXADTkYPgc7m90Pu+BgdFCQ/HX8Wf9puF+aBAWpY0corhZRjP3cjK6be5LWiD6NQhk3ojmuod3hepDW2k5u4eqB6bxtXLR6Dqepqw/5nA6wa/GGZ3maeV+zHsuQf2lK1FRE40ix6HCpULxTjd257UvAC/suMip8yZ41te4c0xs2h48iD2aQTQpC5ddhy7Df12XZX/8lswZ3WI0E35wBiPTEQ2JsIopAsiD01EeNYyuf9IC1btfYT/Dm2nw8Es2WpsIv4ejWf1tGFUHzWcOqXO+HapLR/lFUKtX73sObkSIZ49RPpqwMd3jdjS8i9Dg46LJWN2Y4b2O1a9K2fesyAZG7CQGf6foedZCavWJtyybSNS3ljJM4evoqLsnax9NQ6Xlf3EjFgTrAroiNjFs2hQ7SZjQp5jBRNlv7vPsE/HRjQkBSJ6QQy7GL3igc77MCginv03XMJd60/0DSrkqZAKPvPLxqcaTfwzakWfRUPYKS+K6dvS2KWZgojYNId/VY+K8eYa2LdMFeevm9PkohmXTxjG7A5BjHhjz7JOB7mj80X+iXmIr3o=
*/