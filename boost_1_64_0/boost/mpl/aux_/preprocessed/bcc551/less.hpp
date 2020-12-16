
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
rM8x0k0VrvCO+Qia6g/EvzwW/FjAjDuQfHs9WmYfeNCIYGrwaFAIv7+HVe0jPeho1WCGHEG6SrVmkBMf4M4PXgu+CN4KD6AvrI+eeXofwZYXkrOo0wZy9+36Nnm/RQ5sJ8ec797CMxyPkzg5fEU4cR+Zvd3UT8H2F+G172+dybP/CFw/A2f6Mfskpxpk9oaT4Y5yf4ieONl7jiTQldTkg/HnyOK7fnOiI8oVqn2i54Dnu4deKMm4w9FJZqPRv208jGow1n7AMV3X9cm35aF+mCS3Lo3dCIqYHtyH1vZREAsHcmLs8sT9gsX7iK5TLMmfXO0cbRT99Es9y3iJ/uSQr3vaHGlP5vzNKG9D7Ml4Mwmk+8KZOBgr6MV9BPuG6oPq8/iA+1vZ1OORXsDpgMmw4BQ4bzn6SQWzozDxFZtamdjNcOmxfYQzbLJD9ySvF0yyLP4mT+c8/1H/M670hvDK6DpLozUcR0ppvHYh87YP/tSb+snGNOZ6jD1ykB3Q82vd1/BWT8PH/cL7bWxf9Ikz/IuD1DAtTA8zqJ+lyb1X0Uf6erZaBsbW6UFD9K/esFFq30oPOAos1uC86w7C915PxvVp2OVk9u8l4WNk3M9J/EL6Wh+ZgT3RcC5Dib3eamV/Hsfcf9D+FSq+h9p5c/xtEnJ7hcM5O/M94dl9ZJ/2pYYewbGZbRxlPskuNZ1H0LhXeXlk7L4XHxD4QS6IOx93piAYjdraHiZZSbLfRNceU6/Rfk7XNOmYj+vjjOn0mx3m4bih8+12Otjtzq+c/dA51+Na3gSe+4FfG3TjuRfgUzSLxhbt9wz1DfpgDjOlntzvFfoTrGkB/tH3zfHOr9yP8LaS2LyP4JAxdKgpzjS61CLnp87P2LFP0Xt/5FbCIla5z8Ekfu3u6/X3VDztk7yzQPoX491XeYvpOw/gbD/hNfJU9o1lSJqie3wddbinb/uHkeobTw7gHObMEBwVE9ZUzEypDO9mtV8MX+L+N8PGUuBhaiLB/tmU+HXi44i7tvVR2vjDQ2ubqz6DCr2R2dId1e1ATdPi9Pfx4MTzuL9l5EobOHmyj55OplLXx5LwO1u/UL+EOToXLnWTXkNK51F9jf668QfjQHS4Sk7Ba6DFyVYZp7iaeLop9kbn987+7hB3mHeoF/dOgV1f7y3wVkkmvNl7NfYGXe+o+Jkwp9XxZ8DfnTi6Pf2BaKMv4Atuxw0cQ8a5Orgn+DLIxDs6nFzkeeFM9vlP8S9ewiHcCZNdAY99NpqdndHzTlGng7QXq3czO1/kHj9UP1MP4e6u1GrAFCqTMzQuRQd/0UjAkRyY14FU7Q32YDLsx8aV5JOW571Jk/dKfOOtQ53GNmMHO0gxU8xkf8sQ7mGrV6oN6peOkp0hvKXF2eQoRRmiSS2N18V7cGbqK51wZVgfNoSjpFYzpC4szjA9oZ+JduNahVToD3F8rrU+tjLlPWnXkKi62Um60UfBsZSKDKkLF956H/hZI4V/r90EDgycS53F6E1vO9lujO54ByrKenD6fLIgZ8XzYN3L0NqUqgxFlXW6Qq1XN6vDyEO8oH1Gfs8zbzNfdId4Dd6hsZ+TKHgrWC1eZ/TfTzPvs+tIdr3sWN7h3tE8w80gIi92bawNL7l/eBrJjuZk16/LkOdwkGrDz+9Q65i0O1CZK/QlOB7zzRX40Rdbd4PC97YLmU+r4WAeM2dULI3pGpLn2yNQg2TdRT8nzm69nSvdw/BADDtw5ybAUUZZLn97IrnlIlzggXSzFO940i9B7Nfxq9AW9sUnX4FbNIx5HF3/DaSP3lVvpAe8rat0oceMs80ryWw5ZBJ3qZaFUicZgkF7kGEvRFHby7TMkzg=
*/