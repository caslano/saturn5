
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
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
*/