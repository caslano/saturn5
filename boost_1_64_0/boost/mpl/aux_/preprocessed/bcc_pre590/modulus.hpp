
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
r4Y94TVwd3gtPADOkpzrYAa83pZ/pfQf55L/Bcp/uvK/SPlfrPwvgQeaPJTvpfAQeBm03mdkLwWTXd5n9tL9Owh2hXvDbnCwfi/2kZz9JCdNcobCY+EweBwcDktguk1upeT6XOQeIrljJHes5GZJ7jjJPUz1l636OxzmwiPgRHgULILHSO55pBq1172Suyk8WXKfVX2+oPvuRd0X1Srfmyrf23ACfEflfA+eAN+Hp8EP4GVwKbwJfghvM7LhHPiJrX3r9JwOd2nfXaVPL5gCe8PucDe4I9wdDoB94b6wv57TPYL9k2ySNLNL/5SgfqCV+pvEBNveXrquV6TxlvKf3yHy+94ytePnMOAXA9VvY4/T76NLv/2QrnsMmn7hcbgFfFL18JTyuYNUJT1nK58O+u03R4nqr1T3zWS4EyyDplzlcDCsUL82Be4Pp8LD4AnwGHiS2vsUWAxPhVPhaWrv0+F0eAa8HJ4Jr4JnQ6PLOcFyWzY1eKJLuUepHTLUD4+Gh8BMOAUeonpf6JGNzFDvp8lm7lT59FE+u8NOsJ/69/7Kdw84DO4JM+AAWAYHwrPgXvAcOAhWwr3hTXAwvAXuA1+G+8IauB9cDtPgD3AI/AkOgz/D4XA1TIcboe8BMAWODN5vlr1Mc97zPfb7Tb+3Oq9K53Vu4rzqKM+rs8mtDDlvkX3vvO2UXxPn9dkucn632s7LDObX6HmljZz3lL3+gnIbPa8qyvOqo5RbF+V5Sds3fd6qVprj1py3ua/NOLi2ld7ndF/nw63gsdDkPRHuCwt1Px8Hj4ZF8GRYrPvaBy+HJXAWnAwfgGVwAfTD12A5rIYV8HM4BX4Jj9f9PRX+Dk+A7VH2ZNgbngZz4DToh2fAk+CZ8BJ4FrwUng2vhefA2+G58FF4AVwML4RL4XS4Al4E18CLYbdW/K7DbWAl3BleCgfCy+BwOANmwCtgMbwSngyvgjfDmbBjIu8hsDu8Fu4Er4d7whtMfvAmeAC8GY6Et8FseDs8As6BhXAunATvhSfCKiMPPgAvhA/Ci+Aj8Ho4D86Gj8P7oGn/h+HT8EX4LPwUPge/hgtg69b8LsNN4YuwG1xoyg9fNuWGr0AvfBWeDV+DM2A1XADfhG/DxbAOvg2T2vA7DrvDd2F/uASmwQ/gMXCpKQ/8GN4Aa+D98FP4GvwM1sBlJl/4OfwRfgFbcR9/CTvB5TAZfg23gt/AXrC24feU1FPPicvv6XCPxn0ejftse0Nm6rpJLu/T7+u6DzR/shRurD1Yk7UH67bag3WQ9mAdq71XC+EyuFh7Q27Py9Dg6qb3Wxgxz1r3v+TR6PZdiO+50Lx7LrT0fgtZ1Wu358LU6uj3XVgz77+398KM6ubbf+H/tvfC+t53YW417UaqJSW9Qf2TsknTSHeQqkmrSClvIo+URzqLNJs0n7SM1P4t2pI0nnQW6RbSIlIdqctiykzKJk0jzSUtIZkBZg9SJulk0kxSFWkJqY7U/h3+TxpOOoo0jXQHaRGplpT0LuUmZZNOJs0mLSDVkpKW8D/SUaTyJfH9JJrraKn1/2U+s/x/3WL/mfX8NyZ5GtY4Fek22B1qvsHzuPGPaMs7hbUe5tB+3vTsLMQX+sqj8DNps/nwdlwbsn5ecUsa/CHk292wdr671s4Dl9gmQV/WUzsG977rIN8Re8wQ+X1o3U15wx52tfX709X7deqcEq3Nr5GvCNewzV3QTzSxdeA7b/1eessUL0XOP4H1gJtsYL1/PZFsfR6gz0/q82n6/JQ+v63PT+vzru2sz/P1+cR2zvyu0Odnkp3rtwYmhq99ec6sEdrQte28x5ZG7xN+Kw3A+RHbqzzK9jLtPqGwxMs=
*/