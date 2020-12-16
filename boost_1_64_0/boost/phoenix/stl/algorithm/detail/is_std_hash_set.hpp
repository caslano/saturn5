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
D4lXpMWr+b0IKTb9wcjB1v3resQtMcZ1HxxNU051prLd6VtMdVpbDXH/8KQs0ycY6hOzzBCzV3xOnlNZQxJUbkmQaQ2oRlypY8uxe8O2gywD5+X/JYprm2oM9RJKnqn8pmcMeaH6HOEc5bcyTfrlo3CItS4vU5aPGP10xaNyvNXLOmT50M+3yKHuH14jddifoUEYf002xOKQXXxizpLMpPiU5Bodm3kzhDwYRZCuf+D+bb6qrOMom+syioda75lqSJ4xhjx1t0t5cR7S2rbkZbH8GSH1MpShURjfm+KxBT7PkVyzugnS1Q27KCnJst7Q1Y/ra/W3zeS3yY507behlb/la+W3Vddn+DDrM5v9lDammz7jdX7VX3en2OzHZ1axDMlyYFgGNkl+k2R+T2BoTH7OKWp+vt1jZNd3MdNdf/pIrF4Sq9wQS44PSsjqrSc8x9wpMYdKzMEM/sQMn2oXMzsxkx11r/vonPRqn6tQ8/IbIe8nlbz6MgQo9W7KKy87u7IyvM0LDfe/SMwh0hYHMjQlZqmHmDyrgutSvDsva7euvOghbkCsbVz2sxIzlai+LOP6uLkjrf17M+ImaHFrfj+bxDVcF3reJm5z4hZocf+6e9ns9hnyR7l/GMBQV/IIJn6xfXweTuLIyvPi+HiK7jzFo4zT7n6OLte6C7aTe36vxFkhtDVjDmzXsZ3uxflTuz4vTT6fl+NX6r7yBe24S2JOlu64xLeMY25aliHffddazzuH8JfzBjVf3+79s8032fjMDL/Rputu5Fh9sTF2ii/7DPppfFTizJHlcAZDmLL8m+LwFoicVEdytZc9iWW4FnduXoqhD5T311Sum+R4mL7dho+xLjctyC86zpBfWmZKlk/X+khfbVz/2cTMp50maDF9u+fSbl0UMNb9w2FS/4Nl273AGEvZRZGbNdh296LvlZiV2yN8zjblsF1yiJMcYmX7rtxDDrKR53MOfW1yGDTOvh3GTLfkII3Rt/NTvrbHgeryMs56n3tL8iwz5ilnlat3nYMxR9M1Qde5f3iVxOvCcCxEqSB9PMM1Hz7FG662BQ/xog3xanaNid1y0GC86biE9HcFWtya3Xdsd57YaROzFfOyyBgzm/WCT3G089/j7c9/F5viOBLZmUl1JPrap6vTlT/BtDxLvFJTvJRk39axlevQXMP6M1tb58r61NS2KiZYj4+0pr4jZ6p51fweb7u2lTzRHFeuP9Di1uz+bruYFyfa72M4DTHl+uH/wz6G2hYLJrlHNk3axhSGNuRVas3LfVDMhz42SHL6kmP3cnjVUDfnJYd0ySFV5kfkLA85xCtj8X4f2BAzRo7L1pZzqNhWmW5TTB7ypztWVZ17oO3XL05Zv+iflcfMkONPxv3ws9p+uOXYlrZ8MT7O5bjfM3WB+qtgejbxeeJs8tctd7K/bzmulTDZvn+NmWOcfulZvWuHpv6uzCZWuzBy0GL5/lyDRnbHP6dY+9f2xHNq8Wr2TAO7adw/xb5PKdJi+v48A7t4Habar0NKtHi+P8vA9hiJOZ7sL5bZxlNuVUn3fhvAtN1dT15A0lRiBsq2R4UlJkcCfDx+3VtipceatuNk3R8Qb4i12Nd1f291mq63XxdHm+L8v9fFxyWv9+R6zNcYOjL9JZV5pSbmKGe0k1I5tW25hu2ifZ43kSfPNBnoyiOYiJ7WV435zLj06ys+K7cMSB9K+XzddNTjcwc5n61vM1HTzMcPZVsnwTAdPMc1mcmoWZspnma5DodY/JWoxeLiueTcdC/uj7LbJ/e7wUNfrY/jXj16dS2p3TV6xRJr4WVME2ZgJ6WvrozFs0Cq0zbrB+6bRxk5L+fp2nb99aw=
*/