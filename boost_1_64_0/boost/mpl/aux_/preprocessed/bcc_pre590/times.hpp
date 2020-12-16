
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
h0NhAzgeRsM8GAMnwUbwdtgY3gFjYRFsAh+ATeEjsDl8Ap4O18E4+AY8y9Afnm3oD1vCg/AP8Cd4jp53+GLUOhRx9Vwx5vm9VA8T9TzNhjEwFzaHefAsmA+N+JPgYDgZpsLr9bydAvPgDfA2OBUWwmlwPpwOi+CNcBm8CT4F/wy3wQL4OpwB98Kb4RF4C6yJjjNhC/gX2AHeqnKfBYfB2XACnAMd8DY4C94O74Nz4Qp4B1wJ74Sb4Dz4NSyE++B8+D1cAP8NF8H6lFURPB3eC8+Ai+HuWrSf5pxFQTDb827/UTa90Neu99BPLtveYdzjICwklBB2EvYR4kuw8dsQ3Idk3xKv3W/Lm62+JFNKfhsb4PyS/3074Kr6lJxdEr498CruKSkJ3b9kWUno9sHlJV4b4UMlQeyE13tthc9df3T2wgnrj43fyZHrq+Z7Mmu914545vqj90FZtD40e+I16/83bYp3rjfZFcdEBrQt3re+6vbFEadzng+hLyGLUEhYR9hJOEiIaREZ0Z4wklBAWEXYTqggxJzB3wgjCQWEIsJGQjkhIo50CQMJaYTphKWEEsIOwkFCzJncTxhFKCCsJmwlVBBizoqM6EwYRZhJWE3YTthPiDsbfQkpZ1fbRlf/qn/Vv+pf9a/6V/2r/v03/o7T+X9jHTlZecfy/L/pXZ0+AHonDevXp19P/PclDhnYr2e/3mY/AC1kn7/GGdcZ4cp+g/sMcdvet1BaFc6/o2Hm2BvS0selTsrK588u+/4OsZRRN+/9lw/vPtCZRmramPwxWR4fAIk+cSxyFGehM87wob2TBg8Z1q9nb9+/73T+3fW3pN599GeXb8NXTecYNpftvNk2dxh6FhQ690v5F0qYfgKSYv1tc4sC+AmICyQzTF8BhV0D2+YesvEVMBwdVwSSHYa/gI6SkWHjL2AEMkpdMjyVEnzPs7Usm5l8BbSTrJ0BfAWk+MiiIILKUfmxOB7Yxr29jY+AkcY+Sl95lFoo9tTmtFfY+AcoNQTd5Uzb2+mC7hO1lttmG/8AMbXsyy2+0EdWmHbhO7oGLjuHjX+AKw07G9/8VcEefF+A/DiUH78BJ4T0DZ8mPdCvvXMsYX9mOpZIWcbNVrvPUTb2/ckxNKO7fGRXoe5G2/jH2BHAtj/BN69VqL8p3QL7x2hvY9d/lbGX3DefYdahp/3X8S/HUcZY7ErfM9iHe5bsugY27b+ufRkmFlplhXuG7MZulbT/uv7lN9oYe33yV5WzY5vLFn+H7PHKCMnGmOtK27m521VByYOH9Oqd7DTQOwq7vGeNPb05aenBbAf7okNaqtVWt9jGb8AY4pXNR1f5MfB7DoVhK50Shm28u24utbHXT481PrZ7dPKM7aG0B7cuY6ugy1YbXTJIJ96ri3esDEOXcWHo4u7zI0/y12WC0ectuqjfh6lPZhj6uMtmt40+2aRT6NXH04/COYc4Kwxd3O04w8be3mH0uQVum/Oja8dJscFt/nfb6JBr2Px7dKhau20WE1x2io3NfT6y4xa6ZVetnW4Owd9AuY3sychO9MiuerscHULeR53qL38K8gs88qvWDtc1CO5nIE62+E9qrH+MMNXok7d7/Qyk52LZnhV8fA/of13tj0TCssV3/pvJLoa6xKY/e1yOj/14kUrjz5GuPEyD05FX7Cq/7Jz8zLHpPr57zg2UD9mrnF7EvSZ7lRpFHnuVSn35TEKa33MstUNO7nhXvnZ67VU8dsZGG7lukvU8X6PuSEo2LFablkM+9kAtqcNhCDP2B+69Gz1N9kVG38vOTR8XoTJzx18YRVxjf+Aiq78g8oDcPOf9u633+9kHpcluf5vazouEmwy7/Xs=
*/