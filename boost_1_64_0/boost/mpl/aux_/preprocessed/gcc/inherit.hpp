
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
OEB+SizlKizIyE82Xs1e5b6ZKJWpBiv5YuFz3cNifJ6Xk66PrXXer6b//vYV8ZZZ8ua+c0SV/qutc+1jOrYKtLa1vDnqM76CY705zsMt5DN6v6e8jNCgnIVpzmR3XvUej6r2GZq3jfLESTWDaL3HVYT189zUuZRL7/CgDkzHZo3G/dlOSeS9E/mdTV7N7974VzvPsn3dfc581spb132879wo9y7X2/u+Ct0/5O3znaG4v2ZZ8z58SPV2jfbhpYSDLBP2mbfe6Gd1ZrjO73npx92HjTzVVvldBTftr0MijbrzxOTpR42wvJv/PeXj70bejGPJlw9nvt4BElGFfdT83ua0uene58I2Mb3vI1LHmEPzLfBLFsrUc16PUEc7yd8U5g8b+VGZylXPjIDLSDZ2dpXJvF8O12COWB2HAwnfkbfSz1Uudht2y7yF7moJ6hk5USqjX32a0i1TukWqT6e+86K/8KZb6LB+7x532wbznadtzX7u/ozDzrGwQt4W17HP2w5z3izfxz9f3o6qr/0xjdUpQeN7OuWAKW/W7+kg9smajR//MkrjVII7j/5S39u+OlJeVEttNa6Iz835cf9R6R/S3z350h9d65brb+a82dX/gXo6j2vfWKTfCqu/8qv/U7Lfnu7vLZu6tJT3UH1lVOVdou/pmH+Zyqvv6RMd4/Fzltf/ezrgPmU5/ydReJc6T04lHCb/Zd56yMzPyDj+udFXdv/7eXcpjW6q6y6EIyyXUO5JY1aGMyZZu7cquwrnHo2hsaQZ19C9YD2Vq47SXG1NkwHOvj06mO8AvzRN3+nblWaB0pxH+IE011vTdG3iqrxzyu47lVlLeWMauVfsrTruofLGfG2T9knWsecYWt/Ifrs6rGmyS1b9nGGXXkSE/zb9kfRKLOn5fvhXZXva7bfOCP93iB01vi/N6SXrWrwKvyMs7w7Tki2URhThGGmUW9LIKHIVKIi4zeXJR8s+k15kqc+Uxv71+RPrRRw0pa1zvutcVYX07Y6PXY39x/n/m/SiTelVpR4r23ZxLGBMfbRv9lTZYixp6XDQifREjwdPmo8FSNNhlyYn9JNJ07MNOzX1q1MqlGPCkqZG+zoXOqoyZt8uvduUXjOlZ8xWI70dnvS0/VzJuu6wyD9uek1Mv6vda1u3ZUSkfZplNmmyozIUPSM/mP3HJl1LWZfZp8vgIJt0jSbBkyjrSKUZ3sw/zeqkGW2Xpr7UvVfYeSeevqfMRX7pI+nH2aVvjAQ+iTJ7f3sGSDPFLk1j1O0pSNMZ5V64ldI8k1CTNIsrpllwcvux5zfgJs4Disayb4c1t89HiV8+Tn7fNudFUVnqZHmAvJT55eXk9ndzPhSN5Rg4u4V/PmqRj4hDFfNx6o6BtsrTg+TJP0rrvlNik786xjHil7+TO0Y89XQ/eVI0lnz0P9M+Hw6/fJzccWPOh6KxXEOsUj4aKR8NCHXJx3pvPrjvMIh91vxboX5L9x92K75S4zPje8Ycp8oXzHeop1z0oahcvmcSbXTVr1Nj//WM5VbulTtpfG403stypd960mcvScsoKFDakcdph1h+OGA7hOXeIWb9npXkaW80ru8KnMYbZHX/0HdGnOQv2j1/veYbav75Cn9POGz9+13M6++Wc1JxK/97KxpF8/kRT9kLTuh3b8VtEFZxm7fW2Fel25LQmHRX+9I9pb+FXW2SaoNMzZ9lycsq5aWJ8hJBaGrsf768nNRvVR1TAetiZxv3ysXsdy1wHjYj/TJL+rqUVPox5n7NKrSpB7pXy/ifUnAtU+pp31b77GrqqIh8fs784O/JF3ray6PIK/dLzczId7eX77V81tsoqzeODcTxfhhp/UA=
*/