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
// is_std_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <map>

namespace boost
{
    template<class T>
    struct is_std_map
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_map< ::std::map<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multimap
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_multimap< ::std::multimap<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_map.hpp
5i39mNfnpJScnDnuxCNh1PJLn3Nas1zrAwx5bpI8CyTP5ZJnxXI1T++f62V7f7NpfRSe5y74hrStY3IMquhGNW7Nn+kleVzymV5qXRTmmd9NIte2rFBzqtk1GNo2QZ752LmcM6mMszgxLVe5/CAlK9t9n5cv060/P5qwyP7ceqk+ZmZutWPYXSfQZbH7h99KW/qKoZAYZboYbOQ4anlxfZl5WT0S4Pk8bDLT2IwcBvHdnJWXXiaekN9M1c7D+rvXi4ut9zJzPJKFxDUdrsezyNFRn44PuI5DSqzSfOv1eUpbiJFYymGk3OxEzErKcSqdrJN9T4d623A13hvKOyJXMS45pmO3bJyVZVQZpxrOkez5mrxY6muujOsLPuuft1DB55aB7nHpt22up0x2jtM1n3ZSvy8w3dOUuiA3/TM/PmpGWVp+usNdT/q62rnEPWGLpH1lq33qKnNd5aa7JsThunXKVVfe3Fejr5sL9nXjmo4jTMN2cprkGoPuekRTnVw01Il1unKXupPYLNO1XqarYLV5uvL7RQ5Y1Mc0aZc8D203XRW20yX3Csm9CnKOyTWtdzGdTvIcyuejMq1yvth22nrLtEUtcyfyikzbSwxxyjbmTTJtXLO3yN2cq7H+rh94+iZrW57G+JJzcrU+wpVPdpJ2TqYo1P0cnzTdOfCNjJCgTJtpHivpJBv7g7Jl1vVCWCDTsEadBqcjOyONPadFXp2XaGZ6/maIrh6Ddcd88zKVE+fxyqaRoW6PLXePtFjq9i7JK1rLizMvaUm53vS3vuQkdWq5Lz1XvbdE2tB71OMRcu7J541rjPely/yQ/tp6vYF+fpTe6E58gvSZY3EGbSBgrWu6XY/TYBrkYTmXfsZPkEz7m0xcsjLxur7M9ayMZN52KrmquWXqprOAkXAH9CKn/poKXV38yR+eQ8NvMhLzpS6OUw8vMB1JfD7lyrvy2UHyDlbLdEeucCcdI+1wIsNMprtknXG6uU+oWs/isU63sX3dJfHyJd4ihtnEC79Zi+d1LP3zQ/TTtm+l/Fjm6QqMJ1apxDK837Ya7dlm2nx6x62hbcu8K6Zeisn3Rz43LdT3hdb2UmFqLxcM7cU6j2NWuScivj71gDMxUZnH66UebJ4rFlGNetDq/f/4bDFl+t9jemUbTavLE7pnPH5t2r74Qmv/xn4kTRmn1P+DK4lNPX1MxQdsqqz/CsN6S5ZF07q4nM9XK5+5RU3aoDbO8YxzHd+13lK5PJ6VfLMdSdq8Gqj2Q6us+8dzwxh3kWtepady+UflY4B5RFSVx6nDDf3wVkaanlrLEC96tfU9qKnEK7KNp1y+Wv14SYwnNSWz8rmbfE5KkeeYS/z9q63T2y6Utmkbnzkez8Z+Rk61c5BpNsSMusk6zWHELLONme1ghedY5EM9q9NdGkL7RX0OR2xyWBbMPrI7B3ZRJ42YGhM/ZdTUmLEj451ZTi/ndWt5dlyw5NCOQMoYUvIyk8z9ZPga67ZImrLu26bmMnVErDLvqf/09EvnoO/vC9dY5+8Cxh1uGDfz1Yt2FSLTpo9TYRMngzjRhjjUoxdxWtrESV1rnW9ZxEkwxsnLSfU+jtpelO0WZ262IW65TdyFxC0wxOW6kjxHteNKPVrvndftR8xaZ63XHOIWV8adEhsTHzNlUuyoEbEsL8o/rx07fpSX7fUqyUXfNx23id01hOVJje2+FG5szJhRU1xPXvRi3q4KtsYbdLM1XjfildvFUybPi3iGa5QkXvHN1uUuIoS/brHG0xa/asTUT1NAoXWabgrme7sYLIY1rcOiQms77cE0RdrFUxYTL+JRh4b2mhMgy4l+etdb468lzxi7+Mri4kU=
*/