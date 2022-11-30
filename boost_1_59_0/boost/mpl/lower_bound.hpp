
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

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610))
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