
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "times.hpp" header
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
GgNtDXsyjRu3L7xIqOYJ19KpDO9/FIaLK5i3gHZ4tdrhLagd3BtVzv/RQuSp2Z3i9aV0xuxaXest0ELSYA8ywKmr2ZMML90D8Swk1DQwCk9WP1Qg09hdJaBWtEYixQzhx3R8oDnvf2NjnD+yEnRVaIL2RSRIsbwfr6sFFAC1JjFfikxLWZKSq1sPngxEyjTKc6gqUSLFDP53EbgcjokFVTWmV5/TVksqaFwWn+Bsb26JpzsZ8we+jGEMSVAcQlsGhZ4BLfQM6GTPgBR7BoDYMwCUngEW94RMS1kSkqc0p832gOOmyzRkCRCiQJKGZQTJAzmRimcpQLHZOMm/1sIxPikCEGc1CcSuFOKxEx9MMjA1qdmVrPKUBIRPR6DUqQigIFaYJ0DzOSIJCAudRG3K5KHisL4Kwv4K2Au/UFBVVz5nqCCW5oFFUlVEj/gnSSov6gMRRh8LtLcgE3g1TOClmcBLM4GXZgLFadQpg4P/wwTeAkzgKSbwXTqeBQAky3AcF0YS4QwUD2RTx7XI0wEgeGNfBosxmeYiAQqWBO3bhZdAd8Vpzw8NIYmt8NiGqXjGH5BIgAIWk/HQVxF/eyWiGBExEMcIEYEiI/xNZxmmSuOocMKDFA62nCqm5uSXjqof+1aZuGeLyzU4LBRZ/mN+te3wcQXAUaeIeWhN7Tq9mo3yUhrlpTYK1heV4591iSHlKzE1ODhqqcHB12ESHKx5fPYIFYJPFrKehPuDWIK4VwISHybJMHxHgnwXSYGqBlbx6odjZO3RVyISBxYVTlPBi/7YpQr7y0UZ5/dxZEH88o3KEG+5J/m4WZbwUdyjzCc9T8qOqzUCwV/6SGZCH6UxohctFcAPoiloqcj1SH5CKAnCEHmZVsQBDL7mgijBS0dnDAKgqgNUVUfqR99lRApnojLQ2SghOPhEWgI7lGx+F0pQ/0C2R4Dq5frqlfrq0+qrV+rDlruIyx/VVWSuem9HYEsdACQ1FsjfYVIZ8lDqUx5gYe+UMHgiHQZBmZa6Dc7XzyMLh3zvFCExgvCVlwSpcUFZdqkctTq+9FLhyPVTOfDiFJXQVbWKwB4psGI99TUklYUgUQvGelvi8Au2NRlYAfWUkKyZQZEqhll1sadyVMN76Yb3ahreq2V4r6bhvXTDe7UM79U2vJdueK+m4b1ahvf+l+G9GobHtwlwXpcazNEfApFBTEITedVxs1REshCms8HoU9AKyqc6DqvznIcL/2lq1pr3PDlmekrM9NJipqfETG/BMRPs6qJaRYQFitTRoGQjYeHPhSRE8tu0MR12pUyLAiWHqIXzQp34cgvfZPhUvKMQj1OkQ5JwLdcX3jmMoOQ5H8gw6AckblrioxBYtfbINKY+uBk+ilFfk4OX3kVez4BI44sTMoAfGZIA9FWSxlchBLpPqqQk8Uu9MR1/R00B4MA5AcSHXji9WYNoENBomkijJTIAOTIkAmiaQKNpAt0nVYKmiXSvQItNA6A2DT0kNAW02Lc1OaBFHnQTaLRXBmAAGRIBGECgYQCB7pMqgQFEulegRQMASDVA3LfdvbEtkIRyY0ZFBBQJk3Ed3UVcLW7oHl3fkCC9yCw94ddT4tGjgrBHKoqfVDwFhb1UELoqILQWwciJVVDVi7tvKq6iql4AoZeqgqJX5GcqqOrFvSoVV1FVL4DQS1UhoZdXGZ1QCFToGZyGAE7xkv1Z/NcwQiCqf7qofuSI0VU0BweEaJ5GYxIEaklSY2MCFfJ0Lp9MjxQIX7oEoAoZQT0KNFZA5BpHopUS4I+sJCJXrdYjC03KTKbnxqIwrwd/xw5E4mly+NckASYuV0vg0BwsV0oDwSIRW5h81pcaE4F2nIQ=
*/