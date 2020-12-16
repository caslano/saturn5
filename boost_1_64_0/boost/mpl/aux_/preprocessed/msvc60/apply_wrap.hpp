
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename F>
struct msvc_apply0
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P  = int > struct apply
        {
            typedef int type;
        };
    };

    template< typename T  = int > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply<>
    {
    };

};

template<
      typename F
    >
struct apply_wrap0
{
    typedef typename msvc_apply0<F>::template result_<
         
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};

template< typename F>
struct msvc_apply1
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1 > struct apply
        {
            typedef int type;
        };
    };

    template< typename T1 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply<T1>
    {
    };
};

template<
      typename F, typename T1
    >
struct apply_wrap1
{
    typedef typename msvc_apply1<F>::template result_<
          T1
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap1< int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply2
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2 > struct apply
        {
            typedef int type;
        };
    };

    template< typename T1, typename T2 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2 >
    {
    };
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
{
    typedef typename msvc_apply2<F>::template result_<
          T1, T2
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap2< int,int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply3
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2, typename P3 > struct apply
        {
            typedef int type;
        };
    };

    template< typename T1, typename T2, typename T3 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
{
    typedef typename msvc_apply3<F>::template result_<
          T1, T2, T3
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap3< int,int,int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply4
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            >
        struct apply
        {
            typedef int type;
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
{
    typedef typename msvc_apply4<F>::template result_<
          T1, T2, T3, T4
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap4< int,int,int,int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply5
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            , typename P5
            >
        struct apply
        {
            typedef int type;
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4,T5 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
{
    typedef typename msvc_apply5<F>::template result_<
          T1, T2, T3, T4, T5
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply_wrap.hpp
pu7ay7Ya3n/Z02vf+/yAu/uSA0FpMfdsLvz/taN5G9rRdroNLn1tZMLLCafa2eiWHgv4Z9vRiizkd1V+b0vIbeW4qqSR0t7kh21xFHaSdqOu6I99pd0oHMdjFE7COAzBZTgZ78Ypct1CKK7BqTLGYxq+hmG4C8NxL0bi+6jD86jHrzFa2p1i0AZnoi3GoSPGY0dMQi+8BQdiMsr9beU30LAOlLvi/W2/k/vb/oDNsRj74c8yVqUEpR1SfnOoM3kfdTtkR6m/69EOu6IjdsPu2B37oBuOwR44QdoNdeiOC7A3LkZPuf6jL67EG/Bh9JLrQPrjZhyAz+Mg3CPthQfQGw/jELkuyQc/wqFYgMOkXDYN5HdCfj+Ucg3mbys5n1gk5Vos+8US2R+W4gBchhNxOYbinTgL78L5eDc+hOm4Fu/FHXK9zG65XiYbV+Pb+Kis71r8BtfhD3IdzC+4Qa6XegLt8Em0x43ohJtwAD6Fg3ELTsRnMAm34ix8Dufh87hbrpPJwe14Al+W66VewTNy3cw53IGNqJud2BR34fX4BvrgbhyBe3AMHsCJeBDj8S1MwUO4Eg/jA3gUn8R3cCvm4kE8hm/jcTyBH+AvmI+/4UfYlu12Em/Aj9ELP0Vv/Awn4Gm8Gb/ECDyH8/E8PoiFuAa/xmWWNWuPLd1BGyHZigN8HG2y6eRK1wcFGK8R8kWlvTZ8R9XXCqVfpO3WDYeQi5X3QHU7buqO6ttyC/nbbhxlIadJu+46zMQMNG/fPSNtvFa03QZjZyxr6/UfX317b4ZZm28BlpCravsdJO2/oZhK3sT67yBX1R6cy3wvzGB+LjmUv4tR3T4s1z5JGzHvJ+3EZ8nWwcb2YtedzEO34L9uN/YP5vW5lrQf877BvB/Z2I6MweVtyduDWV9yEX+H8N7WPnxecMW25WCz66zidpa3MS/bWd7ObHdTeVuzH5a1N6/C7eQ8srHtGXldMdPWk6QNupprtDZkWFbZFp2uLEPOJReSq2ubdg4pb58OIS+Wduoss7bqvJDy9upS/naYXLndupB18mR+Pn+H4gLyamnH3o655BL+dvvaysKXHE5e8HXN2rXrJ/6PSEypo/g/izUdajYmvwU2tSBL/J91wU4d/4f5BAV4hAUOCx4eHBYUPGFUwEiJYTqjpDqPYS+lDaDI7Dr8kxLT8Zoa96sbPlemCyuOK5B6Y90kJu4j9dYLH3BhvoVZrF+55mrUltL1qqpjP51SkZdWj7VoCzCrR6m3XlKP6nqL+Yt6k/EJWjymxWMWt3Q3bHcnx+/TYw/8mvjYw2u29p38LxjXYDjOyfHPPJ5oJefdrdEOHeX8uy12RCfsgu3RCzvgSHTGCdgRo9EFE2R8wwqJT+7BLvgkuuJm7IYZ2B13oRuewB4y5r4nnkV3LMLeEpf1waboKfEEXw85DvF/Uq42/J0n5Rog5Roo5fKWcg1BN/RBH4lP/HAETpP4VId+OBdH4UIcg2slLn0CA3AjjsNncLzEGRMwB4Pk2oaJeF7iVwsZx9BArgVoLOMZWmEousl4hl44TZmu4fnxX50T+5LNxi9c9nnwlXwOXPnct2bnvdWf89b8fLc257o1Oc81nuNe2vmt8dy2duMr/olz2pqczxZyDuvwTc3OY7WkJS1pSUu1S/US/yelpNTF+H97ngGwmhPSMy8pzwCYp09O1KeUPQdgr6pdIF3aBVzIluSO5IeYcP/RrqrrAsaNGRbkETaOZwrUoG+7yvsBSpw6fGzFcfPxftx4QBXLKv18Mot55ePmU/z1CWCINUdIGTwlRp8gfbIBuIYyhF+kDGHx0VEeUg5XlFRlnH5nid1F73NY23LZK+WSeco=
*/