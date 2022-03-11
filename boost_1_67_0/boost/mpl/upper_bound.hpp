
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
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
*/