
#ifndef BOOST_MPL_FOR_EACH_HPP_INCLUDED
#define BOOST_MPL_FOR_EACH_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>
#include <boost/mpl/aux_/unwrap.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/utility/value_init.hpp>

namespace boost { namespace mpl {

namespace aux {

template< bool done = true >
struct for_each_impl
{
    template<
          typename Iterator
        , typename LastIterator
        , typename TransformFunc
        , typename F
        >
    BOOST_MPL_CFG_GPU_ENABLED
    static void execute(
          Iterator*
        , LastIterator*
        , TransformFunc*
        , F
        )
    {
    }
};

template<>
struct for_each_impl<false>
{
    template<
          typename Iterator
        , typename LastIterator
        , typename TransformFunc
        , typename F
        >
    BOOST_MPL_CFG_GPU_ENABLED
    static void execute(
          Iterator*
        , LastIterator*
        , TransformFunc* 
        , F f
        )
    {
        typedef typename deref<Iterator>::type item;
        typedef typename apply1<TransformFunc,item>::type arg;
    
        // dwa 2002/9/10 -- make sure not to invoke undefined behavior
        // when we pass arg.
        value_initialized<arg> x;
        aux::unwrap(f, 0)(boost::get(x));
        
        typedef typename mpl::next<Iterator>::type iter;
        for_each_impl<boost::is_same<iter,LastIterator>::value>
            ::execute( static_cast<iter*>(0), static_cast<LastIterator*>(0), static_cast<TransformFunc*>(0), f);
    }
};

} // namespace aux

// agurt, 17/mar/02: pointer default parameters are necessary to workaround 
// MSVC 6.5 function template signature's mangling bug
template<
      typename Sequence
    , typename TransformOp
    , typename F
    >
BOOST_MPL_CFG_GPU_ENABLED
inline
void for_each(F f, Sequence* = 0, TransformOp* = 0)
{
    BOOST_MPL_ASSERT(( is_sequence<Sequence> ));

    typedef typename begin<Sequence>::type first;
    typedef typename end<Sequence>::type last;

    aux::for_each_impl< boost::is_same<first,last>::value >
        ::execute(static_cast<first*>(0), static_cast<last*>(0), static_cast<TransformOp*>(0), f);
}

template<
      typename Sequence
    , typename F
    >
BOOST_MPL_CFG_GPU_ENABLED
inline
void for_each(F f, Sequence* = 0)
{
  // jfalcou: fully qualifying this call so it doesnt clash with phoenix::for_each
  // ons ome compilers -- done on 02/28/2011
  boost::mpl::for_each<Sequence, identity<> >(f);
}

}}

#endif // BOOST_MPL_FOR_EACH_HPP_INCLUDED

/* for_each.hpp
4tI7lPvQFy2qSU6RNSUNuZqHEZ/8akSZDalI/IIjPXg0HhISF5IWvREpzUzJr7vz1ZvO6f6vUAbvOP1DIL6j3CIaK7+el0/LoNt5bsBGxCXmg+fD/T0loCXoYRMOT4oSubtDjOs+XLnUO44m4+2EGXnVhR81uG42eY6SCltmyi8tJjOJWNGjn5eVlWGOwouf0BRkW51s7UjeGArrS150lLxJpXiH/n0DZYe74a8hXirhHjHgxxl7QGhbcgtXvRN9Uh3SigT3t4O7bAFb7FLy0CVj28+eNMf6TlH2OGvWfg6HLdTpeKSYJHWFRFqr9L+hZzQr800Bp3Gm3pyceMvv7UhsthprLU3l/BQfxBsC1tLE19pcCspLW1srfww2o7QNFC8TNc4XgDBdnn8Ci0bjhmoy99Cfvo19W7bQ+8OEKv1w9yPefRQx8o7buOiqYj+rKaE+1ahDm6gns3zRBSX+Wy7J0JCrvVrV5GpnXWtrqaeRvaIiSwoe5/t34JDCHL7wheaKg6O83Xb1Fa/KMvAQ56LJu9XxG0k+wramwBG39RR8/tSdu4h7iry4JxR5FjOhRSBrFv6WM72SbCumtwObokN7Xz2SXHAke2/lXqX4hOe5dLUcznxR2Zq1gFQZiBFj8t7hl8HD+060ovKzZoQ/3oRyT3nf5VXojm9dTp+B6sOLTYeo2TCGcNsD4IAEpJK6FbqBbR0TZn/sh+nL
*/