
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