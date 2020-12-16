
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
N3wP7oGH4BvwY/gmPAH3wjrc52/B+vC3MAa+DTvBfbAn3A+HwAMwG74LZ8GDsBy+D5fBD+BaeAg+AA/Dx+Ef4Mvwj7AS/gkegkfgEfhneBL+BZ6CVbBtGH5n2BEehZfAT+Cl8FOYCI/BbPgZnAU/hzfCL+DN8Ev4LPwK7odfwy9hNfwafgO/h9/CuvTr72A4/F7xf1VnePxfNh//1zDxf6XA1nCk6u+bZJ5ujKTLkHST3OmQGtL1k3SXSrohip8/TdJdjth8/Pzd5f7sARNgTzgY9oLJsDccA/tAmccg78/YBLH5zGNoIXq0hO1hFOwGW8FE2BpOhOfDAhgNl8E28H7YFlbAdvC3MAZ+CNvDr2AHeBJ2VPxR1Vd6/Ftr65j63+SdF138XJcw2Tc/Y/9bmi4/4+tsSn5765j71VYp+RldF/Mz96v1Ft+aQWwlvrX/nl8Nnxq+tf89v9ovwacWk8i1IZ9ayKcWpE+t91H24UbsyFpkJ3IUCfsEvxoyGilA1iA7kcOfhPxmoSN0hI7QETpCR+j4ZR3nyP9fkJ9dO/7/hS0s7hjimDr6+M6+Wrx1sscfOSJlYgYx6KzvGriPbWCMsm65lDVFviveW4fy4Ep4EWVVJPv4g3HqEWAW5DrL4c1bjyQfPs/mz9Jc7k4ffK+R+rhHNS7ZtYbqI2joXOFZi+HlvPgCv3afd8bvt+V8lJx3huuOLyvMxrBS9wrFn6muoVyUn6tbf7mprOV8AXllFTjnNGxTfOmq7XrXEyMjTZAlyMWa7Ub62M5ejPn8x3r72kKN7b5Gq1tZ9mxrjl18opwTOyhroStrS3vWTvbYxROTfaF2nbLefj/X3BOpU4rUKQkZQJ1mjPKKx84ptAXuexZfrpdvNxv67jOgzg9IlowLRY980aPSWw9n9R3qnB19XG29W/4c+lHm5JyCg9AnbbRHH1tWCRMEykoKLP7X99fug/1jPfdBa35vdf52ZCN7cjjuofud5wuthZle81a0TkBp7j7yQxSJ84q1jiN9RM7Ziktc5/gp57LseXIuGtrDOFdaiuqevmTjnDM7sY2cs8nvb+V3dtlM5/r88luK45pBzR9x2Ifv3K2cv68Z4/37qM/vyLGe3y7f6PFQLOX/TCxlRjPtfNMDjVfM7PzR0JMv99/aqnBMXu3FWK5z+DRvSUivPjHwtR3WQymvXXgsa/cvK8Yy1iLPenkHiPeJCZH1Oln/T57T8vzWrusga5BaxMdwPuwLO8D+sDe8GPaFA+AAOBCmwEHwKjgYFsNLoR1eBu+EQ+E9cBh8FibCF2ASfBWOgH+EyfAvMAX+E46EP8IxsDN6joVdYSpMhJfD4XACHA3TYCa8AmbBdDgTToKL4GR4M5wCV8KpUNatlGcv7S12U9etjBbfTAxsCdvDdrAD7AQ7wgQYC4fBTjAJxsE02BlOhl3hTNgNLoHd3b4heU7CFClf9Q3lSfmzYSycA7vBAtgLFkp5RZLfDKRS8iuU/BrCDESN0ZwOu8BMxVd+IcyCo2E2HA9zYDrMhfnQKuVY6spzTJ5vlEObM+bKe+h8KacctoaLYUe4BMbDZaL39XAUvAGmwpvgdLgC5sKVUu6tcAG8Hd4O75B+9Sv4EFwFt8A74StwNdwN74JvwDXwbXgvPAnXwlNwHayDzuthA7hB8Tl3hI/Cy+BjcAp8Ak6HT0n/ehrOgc/CufA5eCOsgHfAzXADfAE+Dl+ET8MtcDPcCnfA7fA9uAMehi/Dj+Cr8Ee4C4aJL7k+fA12grthD7gH9oJvwiT4FhwH98EcuB9a4QG4GP4e3gUPwqfh+3AL/ADug4fg+/Aw/BL+AX4P/whPwSMaw86OL2zt67U=
*/