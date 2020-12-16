
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {
template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl< aux::has_type< F<U1> >::value >
            ::template result_< F<U1> >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl< aux::has_type< F< U1,U2 > >::value >
            ::template result_< F< U1,U2 > >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3 > >::value >
            ::template result_< F< U1,U2,U3 > >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3,U4 > >::value >
            ::template result_< F< U1,U2,U3,U4 > >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3,U4,U5 > >::value >
            ::template result_< F< U1,U2,U3,U4,U5 > >

    {
    };
};

}}


/* quote.hpp
AatgLN6NaVgVM7CaY8xZfouCt6xPP+a8XsZ6N2BVfNdeTw/5TSi/FXkfxyr1RC3ek3puRS/chr64A/1xFzbHj7A97sHuuFfq9zE+ifvxefwUF+EBXIGHcC0exg14BA/i53gcj+EZPI4X8Qu8jcp+idXxBPrg1+iPp7A7nsYMPIOD8DscjedwHObgIvwel+F5XI8/4Q68hIfwMp7Hn+XzdgXL4G8YgL9jD2QDDumNhTAJC+N4LIKL8VZcjp64Gm/HLCyK6/EO3IfF8BwWxwt4J5Zjx5XGelgGG2FZ7ITlMBnLowUr4EtYEZdgJVyGVXADVscP8B48hTXwDNbEb7EWnsPa+Aveh4U4Lu7H29EPy6I/Vsb6WAsbYENsiAH4ALbFRtgBH0SON+4FIb9p8RM5TkvjdDlOW/C64tgKy2AgVsRH0RtbYy0MQn9sg40wGJthCHbBthiO7TERO+BzGIovYEd8HcNwE3bGXfg47sEuUt8gD/kNKb8ttfq21v5OoBbdpb490AsjsRKasSPGYRLGoxX74jOYiHMwCRdhKr6JaZiF/fBjtOAhtOI3mIEXsT8WoVID0AsH4j2Yib44CAPxCWyDgzEcn8ZeOAQzcSgOxhH4I45E7fgehRVxNFbF57EZvoDdcCz2whcxGSfiQJyEY/AVnIOTMRun4CacLsf3DCzK8fUqlsTZ6IdzMBjnYgecj/1wAT6Pr+OLuBjn4xu4EZfgVlyGp3E5FtG+z7EorsSa+BYG4mqMxDUYi2sxDrPxGVyPM3EDzsbNmI1b8AC+hwdxO97KcfE+lsYP8G7cibXxQ6yLuzC2gPcoUTk0lUMrSA7Nfwv3IGFJY5nAksVyYIvKo6lQoUKFChUqVKiwxz+a/+9jS/+76fp/Xy+TI9dTQ/reiYVycz3xuNmP/xgs+X9WnZ6QnJZktk2kn2E1k86QeQBqSfud5XpqDL021/ODloNKzdCff0++Ofc5Uj2O3Gb+3ImXzCGuVYj/NMzl6HM9+pzhwHw5GqovOX7jHGWO5NLs83yfvXougGH+R3vupMztzXtohuSi5DmeyJNfOynbPFzy311YtG0eOixPfq2Pfou7kv+2beN0c8w125jnXNvGTe6cLXmFON255AFO81Ou53fclU8xzuO4Phe48Vzdrp9DbZyHcp63Ms7rOc/TGef7nOeVjtryR+cGZ8zsPHVbWK2Sh5YcefPwFmf5Jvfl+4zzibl5q2O3yPcMJOaOM5FDom2on9u4MXphE6yOTdEXm6E/BmAzbIGtsCV2wFbYCwMxGVvjk/gYDsMgnIFtcA62xRXYHrdgB7yIHWUu8k5YBjtjBeyK92M4tsZuGIIRmIw9cRT2whcwChdiDO7AWDyBZjyF8XgG++Idkm+qiUlYB/tha7RgFKZjAlpxKGbgCByAc3Agvo2ZuA7/YO9O4Gu49gCO31qDSC1BqpZQjSDkii0hSInY9yAIWWQlmyz2tdQapJZWUUVtVW0pivIUVdJSTVG0vDav1VbbtE3xWm21fb+5939v5k7mkkTat2U+77xv77gz53/OLDczc86Zafg+TsccnIFl5PlTOXwcnXAO1sS5WBfnYSNciEZchG1xMXbBdOyHSzACl2I0LlOPIyHnEeqK7Wy/Lb4zuqMnNsFW6IFDsTmGFvC+3//qu4kn/Un3//6Txln+K95RrDfecupbDoZ1b5Xc8yuZSqaSqWQqmQo2/SXX/+MizMP/FcP1fzNV///Wci36JX+T1cIPMcZIu4Kplr7MPUJ6+weEBPmEtPWSa9AglOnu79XiHsDY6Zp3AUp7cy73865NSXL5b/OerREo16V8h8+qtrMu1razCVGJcj1fx/Q9mcd31W0=
*/