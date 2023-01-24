
#ifndef BOOST_MPL_UPPER_BOUND_HPP_INCLUDED
#define BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
#   define BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL
#endif

#if !defined(BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL)
#   include <boost/mpl/minus.hpp>
#   include <boost/mpl/divides.hpp>
#   include <boost/mpl/size.hpp>
#   include <boost/mpl/advance.hpp>
#   include <boost/mpl/begin_end.hpp>
#   include <boost/mpl/long.hpp>
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/prior.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#else
#   include <boost/mpl/find.hpp>
#   include <boost/mpl/bind.hpp>
#endif

#include <boost/config.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL)

// agurt 23/oct/02: has a wrong complexity etc., but at least it works;
// feel free to contribute a better implementation!
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    , typename pred_ = typename lambda<Predicate>::type
    >
struct upper_bound
    : find_if< Sequence, bind2<pred_,T,_> >
{
};

#else

namespace aux {

template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step_impl;

template< 
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step
{
    typedef typename eval_if<
          Distance
        , upper_bound_step_impl<Distance,Predicate,T,DeferredIterator>
        , DeferredIterator
        >::type type;
};
    
template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step_impl
{
    typedef typename divides< Distance, long_<2> >::type offset_;
    typedef typename DeferredIterator::type iter_;
    typedef typename advance< iter_,offset_ >::type middle_;
    typedef typename apply2<
              Predicate
            , T
            , typename deref<middle_>::type
            >::type cond_;

    typedef typename prior< minus< Distance, offset_ > >::type step_;
    typedef upper_bound_step< offset_,Predicate,T,DeferredIterator > step_forward_;
    typedef upper_bound_step< step_,Predicate,T,next<middle_> > step_backward_;
    typedef typename eval_if<
          cond_
        , step_forward_
        , step_backward_
        >::type type;
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    >
struct upper_bound
{
 private:
    typedef typename lambda<Predicate>::type pred_;
    typedef typename size<Sequence>::type size_;

 public:
    typedef typename aux::upper_bound_step<
        size_,pred_,T,begin<Sequence>
        >::type type;
};

#endif // BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL

BOOST_MPL_AUX_NA_SPEC(2, upper_bound)

}}

#endif // BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

/* upper_bound.hpp
RStY/QG3TJN+ZcAxFPmxXY7j5H693MgAwQqnYsC7VqJdgf01B0XsdusTpsxTymjtl1/iOUv5U6dS4qk/KrZ1X3m2SU+toNPSl9Wj7KPxpS364SLObIJU2mQNk77asWPdqt8Ys8mJ/gAP+sAG7yftnuTLPsoLKNB9i4mmjy5ZvjPiN/R8asgALfjujJO1+k+UdI4+aDaEtvLtvtQb07mV3L8rE6pHkd8Y8Eue91t/kNsYqaW8MSRbA0E28yU3us7xTzbP3fMujjHeu4l55Ki+TqG55Tz8VPXwBqG6VR8iJPC221BkGt+sOIjSKdyw1LM2rfAnfigcN4zAmwQ5jVG7ASYenFHONOgJ+ITm0iiErEMr3zydf2JyFEc+TExemGkZf5m5MaxmP8gIoq1NtBhd+wBSmLnK2rZvW5Mvjpeds2Q8vmVYiAmuAkAzNVjti0yZZu+PZxwe3uIVzNvnOqKttsbCkTv/OoTOjoWrj2LY5QDzqy4i3ge+bHv6I8W8TY54dSK005n1YB18zdTZ90INa8QD513GqVAe7+k6nl1VD0UOLfU/v+y6N4l+bfO79qx/zkhfYbA0DVNrWaZPFGEQafEt9S0lhrz8rqZVWcla+ZbccT/xmvLxD0/sN4ujM1y0PhE2c1q1MgZ0vJH7nlV4DTve4834qYClEWLAt/tKHG0jeNwmjgTsPvOb6npof5tFyyM12dvsxjX5MnbJ
*/