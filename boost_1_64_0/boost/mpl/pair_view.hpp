
#ifndef BOOST_MPL_PAIR_VIEW_HPP_INCLUDED
#define BOOST_MPL_PAIR_VIEW_HPP_INCLUDED

// Copyright David Abrahams 2003-2004
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_category.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

namespace aux {
struct pair_iter_tag;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Iter1, typename Iter2, typename Category >
struct pair_iter;

template< typename Category > struct prior_pair_iter
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        typedef typename mpl::prior<Iter1>::type i1_;
        typedef typename mpl::prior<Iter2>::type i2_;
        typedef pair_iter<i1_,i2_,Category> type;
    };
};

template<> struct prior_pair_iter<forward_iterator_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        typedef pair_iter<Iter1,Iter2,forward_iterator_tag> type;
    };
};

#endif
}

template< 
      typename Iter1
    , typename Iter2
    , typename Category
    >
struct pair_iter
{
    typedef aux::pair_iter_tag tag;
    typedef Category category;
    typedef Iter1 first;
    typedef Iter2 second;
    
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef pair< 
          typename deref<Iter1>::type
        , typename deref<Iter2>::type
        > type;

    typedef typename mpl::next<Iter1>::type i1_;
    typedef typename mpl::next<Iter2>::type i2_;
    typedef pair_iter<i1_,i2_,Category> next;
    
    typedef apply_wrap2< aux::prior_pair_iter<Category>,Iter1,Iter2 >::type prior;
#endif
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Iter1, typename Iter2, typename C >
struct deref< pair_iter<Iter1,Iter2,C> >
{
    typedef pair< 
          typename deref<Iter1>::type
        , typename deref<Iter2>::type
        > type;
};

template< typename Iter1, typename Iter2, typename C >
struct next< pair_iter<Iter1,Iter2,C> >
{
    typedef typename mpl::next<Iter1>::type i1_;
    typedef typename mpl::next<Iter2>::type i2_;
    typedef pair_iter<i1_,i2_,C> type;
};

template< typename Iter1, typename Iter2, typename C >
struct prior< pair_iter<Iter1,Iter2,C> >
{
    typedef typename mpl::prior<Iter1>::type i1_;
    typedef typename mpl::prior<Iter2>::type i2_;
    typedef pair_iter<i1_,i2_,C> type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


template<> struct advance_impl<aux::pair_iter_tag>
{
    template< typename Iter, typename D > struct apply
    {
        typedef typename mpl::advance< typename Iter::first,D >::type i1_;
        typedef typename mpl::advance< typename Iter::second,D >::type i2_;
        typedef pair_iter<i1_,i2_,typename Iter::category> type;
    };
};

template<> struct distance_impl<aux::pair_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        // agurt, 10/nov/04: MSVC 6.5 ICE-s on forwarding
        typedef typename mpl::distance<
              typename first<Iter1>::type
            , typename first<Iter2>::type
            >::type type;
    };
};


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2)
    >
struct pair_view
{
    typedef nested_begin_end_tag tag;

    typedef typename begin<Sequence1>::type iter1_;
    typedef typename begin<Sequence2>::type iter2_;
    typedef typename min<
          typename iterator_category<iter1_>::type
        , typename iterator_category<iter2_>::type
        >::type category_;
    
    typedef pair_iter<iter1_,iter2_,category_> begin;
    
    typedef pair_iter<
          typename end<Sequence1>::type
        , typename end<Sequence2>::type
        , category_
        > end;
};

BOOST_MPL_AUX_NA_SPEC(2, pair_view)

}}

#endif // BOOST_MPL_PAIR_VIEW_HPP_INCLUDED

/* pair_view.hpp
v/Fv9q4GTqqqiu/MLDjsDu5AAwy4yMiuurIo6KKCiwrIGggTC7JKCamFOg0fJswiJovisrjrMioFhqkpSmlGpUW0mRVLBqhoUFSUVIuRvmW2fltOOejqds7/vHvfm51ZPoJgrRl/uO/dj3PPPfee886999xzllZhepLeQEVwLpjQVhO0fg/IRrde7ATad+KT78Zh4fQophTaHA5FL9zDePtua5U0vdw4iHMYqUIa1sTn8Kounlwir4rti+VVbSHnq8LY/zJ62goXlhsffscqXESbrPJqboYZTXiVwpNpy3++VbiclHR5DT2mqIFqE6YaX38A2Ie+qjJwKPLgA7EjuLBznH803ljo5NKskC3NOr6sigSv9JoTfEjwiUSpg7p4SH10jAdF0sDP7wg/oMClL+/tWN7XER//YfCpvrSFLmGzodQc+kY/xS/r+H+o1Pl9surG4VON6POp98nQPyQl3X8jZZaEuWudWvOl3xHS5edx+QkY/fAMw/9sh+tykyRnbDhMotdYq8535srZ/LYxIxwM5LOPmGaQ02EGOT2rclh4mr3mt6Vm+GokQkSfE0VTBGyQgw+LPm+zpMQeUCGFSCdzA3qlTTOshS8Ua5N5at0yIDxTGjkLjUxca78O0cZCZaonlmvsXmCC9gA7DwGCGRQdib8ryhu3QU3C2IC2lMI32cH+Q44VYvNgNsDseCbjBYgjEW1/OBbFJA6GPWAtli+jAhArdKJ2Luer6vntO4E+tXObtHMl2rnPbKcbFY6JB/H77ztuC8Cj/PH5YbvawfjranNT6fG1ehqmlleLgO5gnNOxpVVEr2CbPOyQDqXZz0wDW7TrUc5vaiiG80klw3jrblwhqvmVwNu/ztoJ8tZNKALr+SHwhpJdieRCOfTRWuFIVqzp8c9X+OfJISgQ9grCYwVhtaaYamvUw4smIKzkdwlypTveunGBo0RJ4eNNxscn+CQRUOm9jU8k4ePV+ODj8xRyNT4+IaDaSaxBrpDXRwHcjxJbhe9TWp7hXa//mUWM/fd2fmCN8tgpzw161CZ9+v1vUpZR0g0nd234bOdRivBXoP2X0g+w9xM11tGAx9zSZ9uPCUwicCZqyuVF1DxSm38lf0cWlHkO6Y+ip+CrlRaHUlq+Bl7ymvcariR56ySN5RvJGsuOiKmxxJXGEje1XsfSHil6TFniCDDvKP9JnQ4PCTWxHBppPL3OLv8jk8N8fiEbgd8eIYH4h6EsHAWS6a1e2LA9TRvb00B8nRsuQTFI+stl4MMXURJ2nteJJv/wFyHw/iPpRvjjk1AULgBU0+R49wppqhCJUGcaJQktpI5fEdL1O+a8Pd8vCfo90OG9sMN7fof3ER3efR3ewS0p+kra7zveszu8D+3wPryjPhB9lMbXq8Z35JNJ4zuWxgf8UBjuY1GsfV1ng9rfGtRwjVA6Xw3qkzKoLz34Hw2q4A9cipTwSc//pGpQa4KHh65greugsYxXCD0lCJUohGKDwxOQZ5rkP7McNdFsW537SDk/BV8lLDvLDxwmv/Aw+fmHyR9xmHzfYfK9h8n3HCbffZj87MPkDz1M/vBO832lZZ6l/cO9Q74Ajfj88Bwa7vH3q+G+hD5ldJRU1T/cTwp8AQUKdIH+Sb55Xh8G+XaEXz6r/QHhQgE/L3wrz/+o9uxyAaFfTPtj5r2uhdKAtfXtdtHGL2/8Xa1ywP2d6mOXhKZTO6F7+BNxr0zua3RrqfQJj7OVr5HyZx2q/FRb+RVS/l8rD1H+Klv55VJ+6yHKK8p2+p5/D5QH/T4T6/8v2/1ZbStryOLUbQt5F2rjtrL1vNlfXbWR9wemYFFCK+ufrDEXP89UVz3D90wvhMs=
*/