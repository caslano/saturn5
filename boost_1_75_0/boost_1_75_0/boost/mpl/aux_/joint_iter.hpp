
#ifndef BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter
{
    typedef Iterator1 base;
    typedef forward_iterator_tag category;
};

template<
      typename LastIterator1
    , typename Iterator2
    >
struct joint_iter<LastIterator1,LastIterator1,Iterator2>
{
    typedef Iterator2 base;
    typedef forward_iterator_tag category;
};


template< typename I1, typename L1, typename I2 >
struct deref< joint_iter<I1,L1,I2> >
{
    typedef typename joint_iter<I1,L1,I2>::base base_;
    typedef typename deref<base_>::type type;
};

template< typename I1, typename L1, typename I2 >
struct next< joint_iter<I1,L1,I2> >
{
    typedef joint_iter< typename mpl::next<I1>::type,L1,I2 > type;
};

template< typename L1, typename I2 >
struct next< joint_iter<L1,L1,I2> >
{
    typedef joint_iter< L1,L1,typename mpl::next<I2>::type > type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter;

template< bool > struct joint_iter_impl
{
    template< typename I1, typename L1, typename I2 > struct result_
    {
        typedef I1 base;
        typedef forward_iterator_tag category;
        typedef joint_iter< typename mpl::next<I1>::type,L1,I2 > next;
        typedef typename deref<I1>::type type;
    };
};

template<> struct joint_iter_impl<true>
{
    template< typename I1, typename L1, typename I2 > struct result_
    {
        typedef I2 base;
        typedef forward_iterator_tag category;
        typedef joint_iter< L1,L1,typename mpl::next<I2>::type > next;
        typedef typename deref<I2>::type type;
    };
};

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter
    : joint_iter_impl< is_same<Iterator1,LastIterator1>::value >
        ::template result_<Iterator1,LastIterator1,Iterator2>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, joint_iter)

}}

#endif // BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED

/* joint_iter.hpp
QEn4unLg6kyUQZsg2EPnaEnH2dBwg4YXbADVnLnQf09BhZ/hoUfQYRdz2vAnzd+18+5yvnyO89udid7t17vU8n2n3IAp4fVQp7BPE8GUyNu7jQOAIVLr9lHM/6brzOH6IwjGcKUZVm4h549UbTVYxukrvn5gcb4cSUYIGqXND2xeyiqjBNRDEW8cfYHbc8k5ygGIxRotGGDyonvDsZrjrYiXx+2TNLwik7OhowRqil73uZj7zVr7dgW+wjwuRvETHRYnn8ut6bEP2s6YtMbTXm2joCcQe5oUr3hyV1XIcEGNJ9L0UABETNvqlQ/YBbffg4pESv6YCbFhoY8IP+h8sc76eEhyujJiKrwe8LGRhTxUuZrd9vZW21ifrre5RrJUR7+h7pZw+FnhF9CnRva/nhWmkzEQkQ/Hy36IzPOyCpRdA8I+a0+ccuLwmbwD6737Olbt8xA2NAq0HxXuSdV2tCFYynXcX3A2k3rM+4enL8gf3chVQg10vy97HAtKLcAB/Mxx9aGqd8pxfvSsBTGryv4uj+AozjinB6GcCkxR3gcgT5wrUW8r/xs5l8En911dbCjgpOWkVBgWewVlajHk2orlqUxv2D7WLhihEWRwGBX3/BCtW2fbVV8oizC4Nt56FLO6nyEbtQ1m/DZ/Ydtot1d+QwPrcFno3lZCTlqVszu2H1XckLXZeSzJB6y+Ojme/VDd7nfuPKVtU1ld
*/