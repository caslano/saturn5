
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
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
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

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
/VTH7lgDb8GaeB/WwofQBzOxjuX9f3KvI/dA8TZjHH8l+fOQ5M+vsR8ewYF4FGPwGE6RsZMfwxP4dxkjejV+hzt00n8bT+NXMlb0L3hO+gv+aBnTWe5XcKaD61dfjr+BHL+fHH8jvB+bYBL643RsikrfYEM9+i4RjIQcQh6hgFBE8PFlvFpCBMFIyCHkEQoIRQSf+iwnRBCMhBxCXn0X6uhV9fNK3XwB20q9vNTFa9fD66T+faVNPfsOwqgkL6lj59/qunXCafZhW5ceRVDXn/dV1pd68iNnPHVLberH1XXjtvXiUh9OXbiqDlyj/ttc351XRv22kTAq0Uupy+biUndNCCMYCYsIWwhHCLqGLCOEEYyERYQthCMEnR/LCGEEI2ERYQvhCEHXiGWEMEIiIYewmXCQcKWRu07cPbmnP2uqgPb/EycpNf83aby/g98qda8TJ0m7eMt87xMyX9qdm+eHynwelljNT5X50nbfVHe7XDUuYKxG+/yA1pbnwiUbO/m83BzvVo14Dap45eBcipexNhzX6VjFy0lwMb2JGvFGqOPlpDsbr7n9sl6jrX9ogCle4ix9Iu5MncSNPCuhzbZV2k5qtPU3tChJm1yfCnmOU1Y7f2/SWSjt/NNaONduPFejnX9oSzk29VPFCujD4Ew7/yBJewjPVBy1edeZ84zliWH584uzzwvV57RTVcf9D4rM55TvR0WeUyVvKO0drkn/g6qtyuh/IOsGcgzDmT+/lftdZX/kc9C/Whv/Zabnkfuvnl+p2/bO7rf6na3r5xN58c9v4x/QWrvtfFNp890E9fK5ZDtCObcLLed2EeXYLlQJlFlabfzV202Vz9Pk85tW8cjfJDysEU9N2W63fN4rn7+0Pf6W2m381fFkqbYLIegCtNvmt5DjaIntpa1+F2ytSn+R7PfcddK/UD4/KZ/PKJ+ljb9/Y8ZAIYQ3dq6Nf2xjF54f/J+08Xe372fbxvrrtvHPZp01hO2EQsI1gl8TnvcQRhGMTdzPM9zT/85UAeP/R8t7zuOnRcdMYG2aUSkPBG7seYDye31FPcbMM7f9lN/VXvLboIq5fWxzy+9U0iHNrK3Scv3fCtz3WvaTrbGfIuv9EG/59lNseu7u+v31zapH17iv1Ly/+0cnZf57M9LPrH1q7MBW59KG/pw9or7r98Ua95Wa9/W7TfetQateyx769KyfjjRpOWLph/NGu37/K/c/kk84vYQAm/sfxtrMUD6vwSq4Fs3bFZWx3XrZ7nXZbgNSZ6Z575HluM7iptRXaNRVOFVPcaN1E9r1EmXUScjf3ewm1CO4/6a6J/fkntyTe3JP7sk9uSf3dFOmP+H3f7eb8f4/5ff/Kid+/+eX/fvf6X571/v9X2D3+798+/lf+/3v+He767//tX7ne0cq85NT7tatO3pH2hcNlkQuPnboiOu/87WeU5h/x+erfsfrbX7HvyO/47fI7/h30bxdQRnbbZXt3pPt3nf//nf59/9Jfvt7+7t//7sn9+Se3JN7ck/uyT25J/d0M6YKaP/P7+Ebr+83j70We0hpt2/+KT8zJdo4wcjrtS3LF1uWM7KQg+W7Lcv5ia5aLu8XoCGdOv5k2suXLgs+rIrbZln8YVW8NsuWWsXJYwHVsgKrZXFW23l+bZWWSeplIbJM4rRalmi7rFvpslzbZSGlyw5YL0tNUcWpP6I6dptj6KteZnMMRvUym2NYqV5mcwwH1ctsjsH7qGqZzTGEqpfZHEPqUdU1sjmGNeplNsdwRL3M5hh8jqmW2RzDAPUym2NIVy+zOYb16mU2x1B4TH2NJsdMUy3zPa46dptlYcdVcdosm3tcHWd66nTVsjz1djY=
*/