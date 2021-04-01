
#ifndef BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>

#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct is_class_helper
{
    typedef int (T::* type)();
};

// MSVC 6.x-specific lightweight 'is_class' implementation; 
// Distinguishing feature: does not instantiate the type being tested.
template< typename T >
struct msvc_is_class_impl
{
    template< typename U>
    static yes_tag  test(type_wrapper<U>*, /*typename*/ is_class_helper<U>::type = 0);
    static no_tag   test(void const volatile*, ...);

    enum { value = sizeof(test((type_wrapper<T>*)0)) == sizeof(yes_tag) };
    typedef bool_<value> type;
};

// agurt, 17/sep/04: have to check for 'is_reference' upfront to avoid ICEs in
// complex metaprograms
template< typename T >
struct msvc_is_class
    : if_<
          is_reference<T>
        , false_
        , msvc_is_class_impl<T>
        >::type
{
};

}}}

#endif // BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

/* msvc_is_class.hpp
El0rkHbD6OpeaVygCH3d5SqdjPNK3Dw2MutHat2+KTlYWBxTSnwQbiA/p9c9AIcarkk/bD3wGNl4o06ORiRRiJHsgYY4cx0014Kob8k+Za2NCO93IHdyEnwlkDl5kwAcPJWpZ/bf8MvaFt4SWwUcmGYK/37P9lKsea5keFq1eymVq6aUubwUdZ8zYrowaSOb+c/aRMNVWqAdtQqNUQgcyAe25/s3JSL4UxyiqlhAsUQmfRARpNCOU9kgTNxDuNwl11eZOK8I6XDM+0poZq7rA6hKuS6fErAiH46/cpM01XNAKB03YCQmttmtK0Q4t+GvkIGTozuclf9xT63oSy70bCo3+6gwFFBWyQYDDjUYvZLpmeLqpFVWDe3cd43jfJ1o1bYS4++gZsN2hHlt2Iupu9vJOtxNwsUrsGVLqPTunaOSunVlKCki+QdzoX4L8lHAvvi8w3gWBnsi13xuzLsmb9iGG0n85Vd5RDZMvCvON7aU7dPA8Zc66abQiBsUio7SmzQimTJ3L+pMqxCf+HAqnkvSRXVvOfMGYHLiAn9Oe8sEbF8/Smo+BQM/zQ==
*/