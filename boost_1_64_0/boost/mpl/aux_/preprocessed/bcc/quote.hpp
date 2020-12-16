
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl

{
    typedef typename T::type type;
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

    {
        typedef typename quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >::type type;
    };
};

}}


/* quote.hpp
pHGUcbRxjHGscZxxvHGCcaJxknGycYpxqnGacbpxhnGmcZZxtnGOca5xnnG+cYFxoXGRcbFxiXGpcZlxuXGFcaVxlXG1cY1xrXGdcb1xg3GjcZNxs3GLcatxm3G7cYdxp3GXcbdxj3GvcZ9xv/GA8aDxkPGw8YjxqPGY8bjxhPGk8ZTxtPGM8azxnPG88YLxovGS8bLxivGq8ZrxuvGG8abxlvG28Y7xrvGe8b7xgfGh8ZHxsfGJ8anxmfG58YXxpfGV8bXxjfGt8Z3xvfGD8aPxk/Gz8Yvxq/Gb8bvxh/Gn8Zfxt/GP8S82/AuZC5uLmIuamqmbhmmalmmbjklMajLTNRczFzeXMJc0lzKXNpcxlzWXM5c3VzBXNFcyVzZXMVc1VzP/Y65urmGuaa5lrm2uY65rrmeub25gbmhuZG5sbmKOMOvNBnOkOcocbY4xNzXHmpuZm5tbmFuaW5lbm9uY25qN5jizyWw2W8zx5gRzotlqbmdOMiebU8w2s92cam5vdpidZpc5zZxu7mDOMGeaO5o7mTubu5i7mhlzNzNrdps9Zs7Mm71mn9lvFszdzVlm0RwwB82SOWTuYZZNz6yYw+Zsc44515xnzjf3NPcy9zb3Mfc19zP3Nw8wDzQPMg82DzEPNQ8zDzePMI80jzKPNo8xjzWPM483TzBPNE8yTzZPMU81TzNPN88wzzTPMs82zzHPNc8zzzcvMC80LzIvNi8xLzUvMy83rzCvNK8yrzavMa81rzOvN28wbzRvMm82bzFvNW8zbzfvMO807zLvNu8x7zXvM+83HzAfNB8yHzYfMR81HzMfN58wnzSfMp82nzGfNZ8znzdfMF80XzJfNl8xXzVfM1833zDfNN8y3zbfMd813zPfNz8wPzQ/Mj82PzE/NT8zPze/ML80vzK/Nr8xvzW/M783fzB/NH8yfzZ/MX81fzN/N/8w/zT/Mv82/zH/xXHPQtbC1iLWopZm6ZZhmZZl2ZZjEYtazHKtxazFrSWsJa2lrKWtZaxlreWs5a0VrBWtlayVrVWsVa3VrP9Yq1trWGtaa1lrW+tY61rrWetbG1gbWhtZG1ubWCOseqvBGmmNskZbY6xNrbHWZtbm1hbWltZW1tbWNta2VqM1zmqymq0Wa7w1wZpotVrbWZOsydYUq81qt6Za21sdVqfVZU2zpls7WDOsmdaO1k7WztYu1q5WxtrNylrdVo+Vs/JWr9Vn9VsFa3drllW0BqxBq2QNWXtYZcuzKtawNduaY8215lnzrT2tvay9rX2sfa39rP2tA6wDrYOsg61DrEOtw6zDrSOsI62jrKOtY6xjreOs460TrBOtk6yTrVOsU63TrNOtM6wzrbOss61zrHOt86zzrQusC62LrIutS6xLrcusy60rrCutq6yrrWusa63rrOutG6wbrZusm61brFut26zbrTusO627rLute6x7rfus+60HrAeth6yHrUesR63HrMetJ6wnraesp61nrGet56znrResF62XrJetV6xXrdes1603rDett6y3rXesd633rPetD6wPrY+sj61PrE+tz6zPrS+sL62vrK+tb6xvre+s760frB+tn6yfrV+sX63frN+tP6w/rb+sv61/rH9x2LeQvbC9iL2ordm6bdimbdm27djEpjazXXsxe3F7CXtJeyl7aXsZe1l7OXt5ewV7RXsle2V7FXtVezX7P/bq9hr2mvZa9tr2Ova69nr2+vYG9ob2RvbG9ib2CLvebrBH2qPs0fYYe1N7rL2Zvbm9hb2lvZW9tb2Nva3daI+zm+xmu8Ueb0+wJ9qt9nb2JHuyPcVus9vtqfb2dofdaXfZ0+zp9g72DHumvaM=
*/