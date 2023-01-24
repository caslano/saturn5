
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
MEra4D7BINfSK26b9ddhmWG0sjD+EDMOzrt+UAKyIvXDV3ddOn/BBUCZVGx3ZScJf8xC2ca75yafXOLvMwWSCe5DL/w9JvYmi8IIlp04jBVw34JyxQC8E9D+klRWFxMy8XWdrlWP7cmn0n76fPeQep8yjTFJAH37qrlYc5gxftlPquYZvzbHl+/eMIQv354jEzaC7r4HSlJ3LZHHxbGURq/7yz6f+iy+/mVhbap1SDnzAwfYeJ/Uzi5myJNa6VJRhr5QePCSBS8QZIZhr9gS6Q4ZnqbJ7AG8aL02M4hr0DOoRYxfHQ+wWXvY5RS06CA5ND0G/W/Ht2o0AxYrjKTUgKK8zTpNiztF2gQPlJfnmPwWC6L5DSs799daobSS3SYjfd+cLYUbeLPXgZATg/kh/HUIvrGdkhl3jj0BOSY4b4G1qsVVUpB97XHQ7j4053ftR9R4saieTc7fz088LnaVGMZQ3r5oTczeVqkGUmsQqpSgC3IPOh77sFxBjKxpZOubWjwD6gJloP+Ec4/Oogmnv2ENBGf/MB54K1EzJvuhwxeA7Wy+2UaiplBZMWJIs5Kc10K0T3bbrT1bo/7Yn1u4B+fWfcUtoMiyimYY7bDCcmxkQ1Lpijkk/j3pU+pIl9UDg9JeYOp06n7I5/rQp6Sx3JcPHoiCEZT6BEo3MajkvZIDtKLRHzG3CM30uV2Btbsbt0t2Sa5/cQySMtoQ
*/