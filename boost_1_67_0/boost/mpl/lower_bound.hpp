
#ifndef BOOST_MPL_LOWER_BOUND_HPP_INCLUDED
#define BOOST_MPL_LOWER_BOUND_HPP_INCLUDED

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
#   define BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL
#endif

#if !defined(BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL)
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
#   include <boost/mpl/not.hpp>
#   include <boost/mpl/find.hpp>
#   include <boost/mpl/bind.hpp>
#endif

#include <boost/config.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL)

// agurt 23/oct/02: has a wrong complexity etc., but at least it works
// feel free to contribute a better implementation!
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    , typename pred_ = typename lambda<Predicate>::type
    >
struct lower_bound
    : find_if< Sequence, bind1< not_<>, bind2<pred_,_,T> > >
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
struct lower_bound_step_impl;

template< 
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct lower_bound_step
{
    typedef typename eval_if<
          Distance
        , lower_bound_step_impl<Distance,Predicate,T,DeferredIterator>
        , DeferredIterator
        >::type type;
};
    
template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct lower_bound_step_impl
{
    typedef typename divides< Distance, long_<2> >::type offset_;
    typedef typename DeferredIterator::type iter_;
    typedef typename advance< iter_,offset_ >::type middle_;
    typedef typename apply2<
              Predicate
            , typename deref<middle_>::type
            , T
            >::type cond_;

    typedef typename prior< minus< Distance, offset_> >::type step_;
    typedef lower_bound_step< offset_,Predicate,T,DeferredIterator > step_forward_;
    typedef lower_bound_step< step_,Predicate,T,next<middle_> > step_backward_;
    typedef typename eval_if<
          cond_
        , step_backward_
        , step_forward_
        >::type type;
};


} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    >
struct lower_bound
{
 private:
    typedef typename lambda<Predicate>::type pred_;
    typedef typename size<Sequence>::type size_;

 public:
    typedef typename aux::lower_bound_step<
        size_,pred_,T,begin<Sequence>
        >::type type;
};

#endif // BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL

BOOST_MPL_AUX_NA_SPEC(2, lower_bound)

}}

#endif // BOOST_MPL_LOWER_BOUND_HPP_INCLUDED

/* lower_bound.hpp
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
*/