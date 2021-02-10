
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
nuLPdtLSHrGVc5Wfmqs9bSZabalfWvJHVeHYF2AoBNrGSUQbmORmu1W6GDG+Bg8WCdGbztLsdh71fOx89pQJ+fkLyRxI4FPoTo11Eez3+z4e1LbaYJ9Qum9ID4H/hK42muOhtK7Uy7dkSWL7myYtTxpRNeWi6daqNs7kZjNi9ArgzPXUIR32V8Yd9p1ka25Pk5OU2ojej8lTejt77LDrPMeKti/ERYd1/gAO3w/41Xt4fdK7lpCIs05knNSj5fk/8wtQSwMECgAAAAgALWdKUpYimEKhAQAAmAIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTYzVVQFAAG2SCRgbZJha6NAEIa/L/gfhh75Us6str0eFQmUXIjl0irG3tdju46JRB1Z19r8+5vE5NKDA8F919n3fXbG0GJntepwJsKyKYhfO9wPZPJuJpZxEi1SEWVZAstFJgqqKhoq0sqW1IhQXkpDOZ4WX2CN5h2N25U5itBgW+35c66s8mdHK+lPfbj1biD+KX4oiwFkPX4F7wFe6B1uPN8D/y64ewg8D5bPmRj9AjiQut1RyELtUMypsdhYd4XNxm4D+C5WJ7QANtRu+ZCUwzBM8UPVbYVTTdN+J0RDNT+MfIIK5YmS4edVebAc
*/