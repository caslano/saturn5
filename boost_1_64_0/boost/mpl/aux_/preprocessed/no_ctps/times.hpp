
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
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

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
4ABsjQOxGw7CUTgYJR9pJ8K21clnmJQnSMozXMozApthMHbFUTgSR2MohuJ0DJPyJJFyJZ9Jkk8ljJB8hkp5hqETBqEbDsemOBLbYjD2w1E4CENwBIZiGIbhBAy3lk/acuB0nfI9JOWrLeV7WMpXR7ZXPeyC9XEEuuJobIhT8RGU40faYZCnzvETKeO+xGJ1HIu1ME7KGY8emIBGTMSumIQ9cTwOwWQcjqkYjGlo+T3ZJfl31vk98ZP6fUz2ly6yv/hjTeyGjTEAO2J3a/1JGwqYrFN/G2W9m2S7PS/l2SLbbZtst+2y3XbIdtuJE/FlVT4bJJ+pOvn8LPn8Ivn8ik3wN2yOf6APGtgegVAKg7AMTsayKPlIewLqTiefLyWf65LPV1Keb6Q830p5vpPy5Ep5bmAK3rSWR57vY4pOPm6y3zVGJ3THJtgEm2Mz9EEPKU9zKY8njkejtTzynB5jdfJpJfm0lnzaoBu2w6bog22xPfbDDjgIO2I0drLmI8/cIV4nn56STy/Jp7fk00fy6Sf59Jd8Bkg+g3AcDkbr8XqXfCIkn0jJJ0ryiZZ8YiWfsZLPOMknXvJJUJ3/Xf3s//07SfaDyeiAU9AyLqVRlkvUGZdyFeuvjGuxDq7DZrhe8t8o+W8wyHNgPCfrqYorZT2PyPnCDatjY2yG7uiFTbEjNsMh6IHD0ROT0IgTsCUuRS9cjm1wHbbD3eiNp9AHT6MvnsWOaP0desz+8b9U6mkZOmEGuuFybIorsS2uwn74NA7CZ3AirkXzOJ3yfBaP64zT+a7kc1byeQ+b4PtoxPPoixdwGF7EkXgZZ+GHOBevSPmv4n78GA9hNh7Ff6jjsTyv1Ilnj8SzV+LZJ+Xej83xIPrg6zgQD8t2OoJT8A2cgcfwKTyOL+MJfBVPSnynrNuB5G//OJ8u8cyQeGZKPLNlO8yR7TBXtsMTsh3mYzQuQOvvtOSzRed3Oln27zR0wQnYCidiO5yMA3EKjsGpOAOn4eM4A+fiTNyIBC3HlTyHxBCd42qxHPfp6IRLsTVm4Ch8EuW6Q57xcS7Tue7oKten/lgHA7AeBmFzHIntMBit49DK+hroxHVd4voKHfFrrILfYH3MQeu7wmU9W2U96neFH5N6PY418E2sg29hMzyJbTATO+Db2BFPYw88I/X+Lg7G93A8ZuEsfB8X4TlMxw9wBX6Iz+FHuAmvYI8CvsNbGfPLdb/D/+yYXsU1ntd/ylhef/U4XtoxvA6cdTBcIzm852BoRPIjBZMmkTaQMkk5pCpZvGOJFEyaS9pJukC6TXJ938HgT5pEWkfKJOWQHM45GDxIgaRppM2kM6RbpDrnef81KYm0knSAlE26Q3K9wLhipCBSKimDtJN0jeTygYOhDymOtJJ0gHSVZLjIOknepCTSZtJlkuES5SL5kUJJ6ZdKxicrmUqmkqlkKplKppKpZPpPnMqQxv654/+NU/pTmEcAvL8xABsaHBn3h/tn3IAoZZAYQpQcIidLpw3Td1bwkPBCY+WeVkRkVBgjPai/QwzKWII+zoa8PkrSzuk2qbI8zz1mVPoGSXtZ/x4hliakrKYAbUdpK4pKv+PEtFRDNVXbZj7TNVvaBlv6Y6SFK+u19tHYw7zIMcxR95Ujnt7+ATbv3k+JHGPzTic+s25zO+ja9czX21HSf7ajfH5D0ycmppTckyVZ7gGe4DtZ9dT9sqUvtNJauBBtdo+zHqlymzFdbkueNSVPZ9Ipo/KgQSdPOrypKr9Q/WIt+av7xb7FvKQx42zaEN+WMfnGSTyxpPf4nqu9eJQm+EWMw7IvZCpxyHos+8LbyrwoZqbEWPeFd0zx0iFY1V/ntDIvhTg=
*/