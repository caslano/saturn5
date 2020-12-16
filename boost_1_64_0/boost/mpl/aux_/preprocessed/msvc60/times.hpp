
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct times_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : aux::msvc_eti_base< typename apply_wrap2<
          times_impl<
              typename times_tag<N1>::type
            , typename times_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* times.hpp
TuZkTuZkTuZkTv/m6Vg9/58XnXVUnv8/SfX8/y655v6FXHPZS5yiXM8aYTvfb7/CK+f7fQ/zGm8ENSrXWWmGXON1vu7bXue6r7/Odd9Aneu+QTrXfXtprvvar/v3b7juK88oa67v2vpmtVyL3yB9s444lb6JOVXVNwXKJT5K8qBvHNe5pc46++m0uz1Ku23P3g/gNZvn/KwFFodr1eY1FfOaiufXVAKilfebrdz025s3xzxxyym/BvXu22/fsbmmUmmR4w5+Iecw2+AqwiLnOlthe2yPnbAL+mMUdsYJ2AXzMRAvwK54FXbH1RiE92IPfAB74i7sha9iCH6Aofgx9sG92Nf2rKIcA+TY4PisYn9pZwSG42AcgkMwHqMwEU/GGTgcc/AULMURWIGn4iqMxTU4Eu/AOFyHo7HUzXO4h6o5V0d4P9r4+dxei+zndNOqj+553cLq/8a53bWsRzWhd463pvrIz/P23nz0z/W2/K7hfG/yZvee/cvZbD/nW7rZft73vWU+Hp37Xb3Z9fnfDfx8HFZu8PrHnAfet9m9c8EH6Au/5eY5XXMyJ3Myp//jdOy+/2cele//A1Tf/3Pk+/9oohURq4Ryv98pqu+4mVluf/+33u/XnzL4DurR/d3K91nluYTM6TmkP7Hnafu2De/lZhSa9wma32n/ZO9O4KKo4gCOrxyFisYlKJqhIqGgridoioCKWpZ4lSkK6KKiXHKYmSmalXdoVpZmVFaWVpRYlFZWVlZWdF9WdFtZmlnZ3W+W/y4ze8AuIV0zn15fd3z73ps3s+vOu6Y+97TJscp+n3f2Z3u+Ouahh+bc/3TSA1e/0Dj3tLEG+SzhMLlX9MJogrL5yb1iIHbAIEzAEOzj4r1dlj4+p173cP+q8Tn62ByX7seM+r2YvumbvumbvumbvjXC1ljz/3O4WW6o+f99VG0AI6QNYD3Bk1BCOEeZX9pPPe8wJ+Mi8i9wY86frAGtaQPIzTIpqWj6/yVl8719d1nr/Fcp00XSLlFAOJf0qqrLRAuBMgvR9XmfUbzgTTX97bwpr3ruoZRF9snggWDVuvF5lkEGhpo+9tGUhX54zfrsXjKHvkrKfJAwhnjFMeYyy2Eqk1ary93ahXLLPHSX69Dy/AHleLmqOGLtmvR5sanKEVqPQ+ZlmuMcqolDzbBPMzaCHKReDtfEs9SMph62ST2YpB7SCOOoh9JY23ooqPP8WcZMtOH9yhv4o8t1oX1+gbaMy+Q24SMP7rXxNTRf8/01ZeTyrT5XxY7LeBll5HM3wJxPsMGDPL39rzhLScPA4zrr/1lQ9lWQpvW4pe43sM8ytkY9zmUz+3f5sz+GFGRfOfsm8P50mfmulGWHqj5Ceb1VxpAo3y+m9ML0VJ6GYMmrTN5PitUpSLqlkgblsl4nq1XlYqc5rz3sywlmLmR69bMalklevKY1r/p9xfJ8APZZn9+wUdLKn1ddjhJV2nLBmeNtsx6zzN2Wc3tCzq2/fJ+dRriA49g70HxuC+ak2kzfzinKrn1dgDDNZ7InaRXMkfUXJM/lMke/leQZSLiQeFXO8szLzUudkZ+R4Ua+bSRfyxxqb14rSSiPbuWlpg58T7Uvz2TiGwY5Kc+89KyiDNfLInUg6/3LuCvTfHMZBkgZsk61XyshJYKUNGWIUf5l4RRkZblyDlSfYdpn7c9zGukbbdLn9NaZruW4pspxqY8jxce+LqcRL1mbj/WUunIclvwm2JzTFQH257SflOMtB+Uw8f4823IUFcyqTxks59L8mSrM1+Q9vql93jN4X4lN3spl5M41PdXZdSTt/PubOGvPd9b+76zd21k7vLP2dmf9As7ayZ31C7jffu4=
*/