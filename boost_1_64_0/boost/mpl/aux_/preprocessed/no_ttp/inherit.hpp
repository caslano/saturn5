
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
HsJX8Xdcj3/iRixMnjY52/YVct7nUAbJby3+HYZyT0QbAEdb+ZpYHOtjSWyDpbArlsZoLIMjsRxOwQqYgaH4MFbELKyEr2I1fBtr4H4Mx9NYC4PIQ20shXWwMl6PzfAGbI31sCvWx+HYAEdjQxyHN+PdGIGPYlNchc3wZbwFt2Bz/ARb4jfYCn/C1vgztnH2rVVYvufL93/WF/1b6/kjMT85Tm7Fqtgca2ErrIutsTO2wZ7YDvtie4zFDjgJO+I92AnnYmd8Arvi83gb7sBu+BH2wC+xJ/6Et2MO9sJg8tgbi2IU1sQ+WBf7YxccgD1xIJrxTkzEIWjHoZiBw3AuDsc1OAI3ohE/wWg8iDH4PcbiUYzDU2jCEO27LoZhPF6PI/FmTMDmOBojcQymYDKmYgrOxrtwJVrxJbThZrTjNkzFD3As7sFxeADH4884AUPZfmlYBSdhE5yMkTgFB2E6xuBUHI3T0IbTcTzOwIU4E5/Ee/BZnIVrMEPOgycNcq+CHeU40/aPw3JeMMp5IRqrYiw2QBNGoBm7YTxG4igcjAloxNFoxzE4GxPxQUzGJzEFV6EFt+Bd+Dra8B2040FMxdM4Fs/iBLyAE7EIeZ6E1+FkrI9TsAmm819rnIptcZqcXzILyT2N3Oto5W6ifWdGLc2W4+UBDMUHsSo+hLVwLt6M87AHzscofBgH4kK8Gx/BqbgIl+JifAofxfW4FF/DZXgIH8Oj+LgcH5lYEp/EqvgUhuNyvAVXYGt8GgfiShyOq9GKz+B4fBbn43O4Gp/HLHwR38S1uBNfws9wHR7Cl/EnfBVzcD0Ga32cYQhuxPK4CTvgZozELTgIX8cYfAOT8E2cgFtxNm7HJ/EdXI87cBO+K/tnhkHuy6Csvn/Ke3hk/9wl22k3huFHaMe9OBE/xUX4Oa7DL3Aj7seP8QB+igfxAH6Fp/FrLFaIRcv6d/YBRBnlfol9X86zXGc4b0t+5Hh5H0PxQ6yCH2M47sHW+Bl2wi9wMO5HIx7AifglTsVszMBDuA8P41f4LR7B7/BH/B5/wR/wGvJ0HOvhj9gIf8KeeBqj8QyOxF/Qgr9iGubgdDyH8/A3fBR/x0y8gE/jn7gWDVofVoUAd2Bh3INB+DkGYzYWwaNYFE/hNXgBi8n+VByLYgksiyWxJpbCG7EM1sMQbITlsDWWx7ZYAbthKPbCitgPK+EwvBbjsTKOxyo4EavidAzDhzAc52ItXII34NNYF1/AerKf3oRvYn3ciQ1wLzbEg3gzfo+N8GdsgmcwAqUNp9znsY/J91rPNpwzZT+ahRUwA+vjvRiB9+NtOBuj8AGMxQdxFD6E6TgHZ+A8XIDz8Tl8BF/HRfg2Poqf41I8iMswTDseBxfX2vvl2ybwDHGEaetMc7QDbEYYhtCGCxcR64jdhLPtH+3+PNv8SVs/73Z+xz3a+kk7P79t/PYSdViWoV3utn3jicM9aJu3tJjexm8HEdqT6QlnG78ufNa3nd9sYjmxThvH3z3b9oV5tO8zSRu/i7XvCyMszMPZlm8QMYNIY5ypp7sd317iJOFsy/ccHUnOYRp/7fgyiSyvdnz5t99bL234nG33spj3XuIkETKUdnVEd8JEpBOLiPXEASKHCB1W3NCY6E/Yh6lnsf9L6ar8/j82yeb49f/Sfv/Xft+fE6pdozjfq/qp/1z91JWuh+K7dMDXJLkWXdJ1KNBrUB7XH7nuuK43F7vWXPJ1xvsak+e15YpdU1RSSSWVVFJJJZVUUkmlfz4FE8lX+v5fJr9cdQDzVB2AqgNQdQCqDkAllVRSSSWVVFJJJZVUKlC6Kr//JybEXo57f639f6r2LvThevt/c3yM9i4=
*/