
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
vWPXdo+S8pf8/8qb8h1YxnF0lSi5SDcFcv486pEy0ROesceTjeCU3tuC90m+mi9n7aH++nXSczHhySepY7X5tkms80ldPqnP/Pgfs3n/VjJv8iLh9zbl9+bjvgVw+SLKPMR9K8PnqyjzOj24CaNvo8xjmxnvocwHuG9jOH2CMp8qgZ97SSYPh+zIJvF61iX7oV8pjNz6ZL6cMpQ0Kvo6o4eSlleGOy5vHB2tzLtJg0/pAT4sPaAPFOkDIZ2gjHqu4o/VccSbqOc2/liMI96BkfXoEwMc8TGsLMEfm+KI+zCzvHJ5Ieq5TN+v0i/qdIwmvbRN74/p/h16Ro+uMUBDj3HHEvzwKTzNxx0L8MOLaOgQt3uIVp7Ayc7gDL9gDZuZbgx7mJ/hCQxiSg/yX+fgEHm87lBp14rOFdTBZhMfrE1fj23+t6f7Zqr08ToqoQ1riJn3HXhDD+YwgDuM4WeJTnxoj/2+4FXAmw/WAnBWBGPh0wiUVUBYDXQ1wHHrDtD197G1Xe61I79qdDF35VYF0rb40XKr0LhypeEm0rrvL+9ETomNPGr3Ca5VpFvdqvjSdXO6ArV7iGuV4EJPYS4+HlWAC11E4YalMp2+ii91qIRrR+nWPpgaonEnoOoMRP0q+eApYGIWQVT4KmIKVDQFGvCdFoznkE3TV1ypLr5zn5k6tLhKh6BZ/ASzCAIxOMpynY43IiZiIlXwk2tSOK2ojcKJ0Tgdo3GEqEvFzZS6FXqK8/hZjh640Zj5nsCO7K1LUjraC8tFPpaLzFZIahIXWVshZuLHgvcBLN0niu5iRm2HI6bUPc2osdzeE2EJx1duEXudGTxFFlE1tjoNfKNWRmwZZNVSYGvdzMIrWMTU4lTKOJOEMNDVWIavTBPLvJXisRzb/bX4maIveAMCPDlvNW30pox3oPmEj9VMN6M+Fbxqhhl1X9j6qLz5zVsRQIvFijmnejqHEjCynsHdChvbc7XgciKtmEdfUdVddHWfLcqQPelk2YRKhZloFjUZMJOO0QXrOF1m9DCfViJoxvkVTpq3nEmNjVMpHao2YOqg4O1nwFSWiZWX82YySdHCDUMHcojZXmrHQR5BO0x0sFIJbDK17yCbgCb+03NnjTpKja00c4d95NXZY7YZSh7sLnK8FGjKrZhO12eZdAZCJw3PSzmDqD80h1Yyv8w4WzanyAzcyP+TDpLDSjJIWxUcbLMvkXd8LCQpHSBnZiQ0KSEAlkwaKG/zQKFJBMlr/SBM7duUQB8MaYsoP/tcODKbxLzdJYZmm7jV7ZrsF5QSkl/2peCdPVjuZ8i90L7xwJxQtSdTh1cbB3M6N6d9I+fu5bgyp7aaUtswwLvA4fopl3aGMcE2aqoVqNO59ZY5x6uz6ngWC3cg9uVdGOyNlfPxqKKXkw/ouXLlypUrV65cuXLlypUrV65cuXLlypUrV65cuXLlKmX9BlBLAwQUAAAACABWrrxKgBOhujTqFgAAEG0AFAAAAGJpbi9saWJjcnlwdG9NRGQucGRi7F1leANFEA3u7u4OpS3FNSQpBNqkJMELR5pcy0GMXIK7u7u7u7u7u7u7u8/OzMpJ8B/Ad/tRIO+9nd2d1bvbvRt0Ss26Wx9tzZ1YMrHYYnMP5vvnXraru3uKSWdN5mMQpo7FxoX/PDZhLHbgAjEMj04Yi0IUohCFKEQhClGIQhSiEIUoRCEK/6Fw64+/RCEKUYhCFKIQhShEIQpRiEIUohCF/3lYbrzY/zT8/EsUohCFKEQhClGIQhSiEIUoRCEKUaAw2f094yyH+/zxD4PAx8f/jqd++/+7c2y8acedQfBD9W3s5rqu3Rxq2q5da8U+E/g4Gs/UW5I=
*/