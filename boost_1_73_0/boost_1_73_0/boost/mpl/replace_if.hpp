
#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >
    {
#else
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
#endif
    };
};


template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct replace_if_impl
    : transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct reverse_replace_if_impl
    : reverse_transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace_if)

}}

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED

/* replace_if.hpp
QjBNaaiDk/ZaFHkSmzpSkJSG/P2O7TQp9LaFXmyNZ+a9N29k4dF5JR2mTNR6bej1gseDsaVL2XS5nHcPuM2WTPBLRvC+mF3DAu0r2tDVJTJhcdccKV1KL/t+Hv2MIB5GkN+DO7iV2WuFbGaU9LXRCfDo9x82Mdqj9uEM9cZXCcSM5fdE0sN0aNE7uF/DYQvXtmlUPY5qjMMPQNGIsbHye9mA6lMnVILrcVWF6uVzUv9TVy/kxE/RyTuydNLUbXFvqeoCcsF1Rqes8n5H5W8hCC23mJ73BIfaV2DR7bcIUpd0LGtLcuC7NyBhJzcIvpIeSoNOf/On2h+ExHsoEMpst9TbkyWcD6b5Ynk3TwYtyzwvlq0XEE5gNIRwRmrODXQ8CaZBntDW6yO0c4Jce7RETOR05aCSDlaIGq5cZfwVE69dLQHsrPFGmSZl7TQd0ZvDAZsa5xP4ICdghdQbTGB1JPS/o2EYsEdyKBxvSAttYW8bPnjKisVd/hDQlVC4o883/CZgwZfxCH6Z7RriGGoHk8dilj0X44fb7DkrirxgAq01VpmSNhHH1PQuFvxsE7/8uf8AUEsDBAoAAAAIAC1nSlKVRo+6/QAAAKUBAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0
*/