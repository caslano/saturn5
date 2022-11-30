
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

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610))
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