// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_hash_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_HASH_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_HASH_MAP_EN_16_12_2004

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_HASH
#include BOOST_PHOENIX_HASH_MAP_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_hash_map
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_hash_multimap
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_HASH

    template<class Kty,class Ty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_map< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_map<Kty,Ty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

    template<class Kty,class Ty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_multimap< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_multimap<Kty,Ty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

#endif

}

#endif

/* is_std_hash_map.hpp
vCUSENxp/TxIxuFHfFk8lJ9ru/7UYdCYu5KZOJgh0L9wqtdbaUb1vnYJ4OxTt81CXYWnX+QdRGPu3KUo5UucfEgZOBjg7LlADhfKUHeIFWByshdN0Xw27SoqMtWXb0ZFo+Ch6wIfs06XC0S2PNda71ZvmZeCvHAM/iVtFeYzhN27rPg3a9i517apn/kz/kz5BXqVjijBSttUblpPnQx/L37KPxhACzIw7RmZFkTT99oJYn1h8fa0xmDSZg3iUIrO8NYRDcQS85GspyBHnfOY+3/qPdfZ6y4pukk9ispOlx8UVb91MYudrrQn63mGclA2z0Fruh25SlSSX5Ef8mXADc8eVPv7cDbtI+xwm9Uwt2z/U8jBvvqPofN34BhdUOMzI56UysnhfOFxj7ZZS1Dc7rBKuJl36Zs/wuKRVohJFCPegqyhnJAdx0D7Oj74rHStlkGXaxhi+h7zk2ySzufV/DvGGbDkfMoGw8VS1mSUhv1pnUu8Hvt/WfL0v2KACIza8U4xcVe2eWsV65JkqtcXt0gl1Z5y9fctWN3Lmp8VHU4rFg39DOzdVrqQQg==
*/