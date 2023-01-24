
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "inherit.hpp" header
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

          typename T1, typename T2, typename T3, typename T4, typename T5

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
3P1iswP0xE8RCJvCPYczcnJQEVnuLki1VFwuJoYreyJTVj3bFqq7VGPml25XQin6InzXSw7nElhmfBnUUT+j8PaRFxDrYNagLFe/fUsRFNdHbMLtkp52c4y4aRdTYlEql8HYQ5ceksFfac7IABOxZraig1yn3AO6NQEsp86VB+wcFxmGLfeHmeBitz3hc4Bn4BxLkxmhheLmZsMuPqviBLnc6hhj+ixY/+HgtyBLoy+WwJ7WY/wDyVqEEG54NoSF5jv/EgbNld8O79/ymndof504Oz99dPsAk3RYgilRi+PeRgxftbUljOLPWScEcvi5EIlV6Ie9wPtYiG6gbZvxos1C8KGnt6OLirfua00jSwgvD8BK/yVggEYme2BdGMHQ1PWOpdXkmdUO+AamQht9rw1AtI59n1tvZGmcb77JOy3WhG9fzM3cO+Og9qZ/xwV0IZzxvz+Jb2Oev25Fvke6R75/tR50hsQBR0NC8Xm7+uo3oZ2KCNYiStcf9Y60d0j+wcA+eqlNfZwdv7c2SMgSb23+kJIgmMVqRooI+rKjUYAtgEWJ9+xALyM8+8oD2fSvbrRXRuHdtqJlnp4QmMDlHy5YAjg5SKrIon3JfUxT/uQr3BL57OJhp4I7tjsiLpKTWxTpgx995JAofIh9cORZZxG+i6XBWDtIujtcH3EM5p6VSgkOKjzXKOV1RrWkf34lapmSsXuADmUQKTA0
*/