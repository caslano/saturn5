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
// is_std_hash_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_HASH_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_HASH_SET_EN_16_12_2004

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_HASH
#include BOOST_PHOENIX_HASH_SET_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_hash_set
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_hash_multiset
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_HASH

    template<class Kty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_set< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_set<Kty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

    template<class Kty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_multiset< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_multiset<Kty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

#endif

}

#endif

/* is_std_hash_set.hpp
LWWs2QoCg7a5XLD5bBBA5XF2cXoaJgfjzDfOfePCN37xjY++8ck3PvtGzzMuHOkJXGr1gJJkyweX+rGQ5da1be3U81l6Pkuv6xs+Zc+j7Ppb6/pb61a7OcLf9XfZPfexPtZiDgkdxNfX8YRdRePRHMKwQwfhct9ZC21smPhL7hVm4A4syTB5CLNWIGSSlymyVFBzW6WpRZqE/+HbYDkbs3m8nA1GbBjNdg7lcIVROShYUYu5hqZW0MiTDBoOmpGwsmBKJhhmjfexqup41fW+i9HJ4cNlNOnPbv+njkTJtbh/o8HH2e/8KE59SREK5Zyq231oMqe7ujM/fKuLekdfAe7RMrcs+QaJf1MoidLW7m6N3P8J3cGkfz1iN6MWBfI0ZbjFpLROQXPv5kJ2MPprMF4OR+xqFl+z/nj8FqQS4BfBzuGdOMAUC6S7SSbuUF0ELRjwsZ2r5drJdpXI6i527m8U7Lv8NYvj6LJmoZNm+/BCK7o97b9Dgzq901k8Hc0WEZUoSZ2STDYcXUWTaBHFkzk0ljRbjOaLeaMVkOTXNLeC71BLAwQKAAAACAAtZ0pSFgFe73sEAABDCwAAIgAJAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvTWFrZWZpbGUuYW1VVAUAAbZIJGDl
*/