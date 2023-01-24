/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09272006_0724)
#define BOOST_FUSION_SIZE_IMPL_09272006_0724

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply : mpl::int_<tuples::length<Sequence>::value> {};
        };
    }
}}

#endif

/* size_impl.hpp
o8dD9PDq5e06Kn5tOaq3xXr2k9/h5GeyMZEINpIxiADskCrawGsgyryXvrVa+KZzHNtzDfveyl2Qr+tqhUC27TwMvNbcDSa9DKliPhu9Fbsp9V8shqxjZMLc7Qi7BOxuLZN1I548vC9yDcpgQz6XLbkABn26BVjSN65es838ysrWb/bvkBQmdsf81M9CF/kf3IMQzXCxDzIJbWSFQFqOAyqa7e51AHpfmIWjXD92L/twXRsefEfh4Ipr3NOPlbLu2n5MfLTh0Uw+SkZWt7hPMe613VY6s0HHx9AUD+3GCygMHAWB3IwWNdRS6Nsy/PZ6llKpB5hAOVv5FMbslGQgKQGz4qBhgWjaWb6ZVlzLrrNwX4nv4YSbwuQJy9E7Okb2xa0/BCXk7sad9DeHYCc92ip7z9wBP31xL2D0RRCNxsouX1wJaze4Xc9BVey4n7+FFDXX9MPrMNAmnf2D1ZLlyY9htYteR9KnzoGtWHyrLijJnisP5EjP5w173yDoK5jFWtbQVeoFC8iVw1cn4vB2czt7lqt7YeRcvahVU52LcPh8eIIGwLsnkG9RhzNG9hboepyk5e05i9VwjlX23BhjARDNF6249Nspe16EowjWu3zLoU57S6J9yhIW7Em3FN3rSbffO4RxdmZaxD2sUqNjrlZiq672xm7G355BVRaHVpWZHnHX/uZxKTt999lRTZq1uBIbLntjL8bfnkHh
*/