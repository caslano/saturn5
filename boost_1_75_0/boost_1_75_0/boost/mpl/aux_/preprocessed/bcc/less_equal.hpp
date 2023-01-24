
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
3RenG70R8tJpwa7Rz3PpiCfB5J0eVMdLCrqZnj4vYo0Lv0xlWykm6YVb0HxV9p4/H9EQm5R2vvt+wwSkeLTKJMbPeb97CX0ntJGSuUGKSIqcib6eLfaA44E3wMnwqzfszIAlyRyx8aArzc389PGskR1/1V4GwTUfE8iy5eYn09PKc3nD8TLJ8tiFYjfLwiukV2JZ1JfBW2jsoMY/Emuv0MojbgQsh7a+KsQTDHzqTyz64ajQYm3768LylXMO4/uyPdGI3k9ss24jc9LFTXYIhdnhqqmq0ZVJABE0gn0qNL9lSiFFVyqmZdq5YePME/2sAGLzzHzJvxFW9z0D8v4GTkA1EO0RNFQ1rlXWvyoJAhyS3tLc5tf+MAuFKaYMxG6EMznc0p1WJBqzLv70jv0LMaCkgqjmtzdHriuTcfkPHaYRrOgEQUaWpZ92Su6Bsmy5I2Kzk47MxuVbQQr1dPFBmPPr71p+MS9rNg0YJVcUu6vmeFjr8fXh1EnNBW8YZnHtRz7RY6oKp6Ja8wFFkKAsBcZj7/Wi6UNx7olICuNLu8vHiKyHDur9LS5C5mmtKjKY2OTLM1hr3nH//GtnqXedshCidW2GmkveCWUgJzo0Lzy9/hIXs9oAt+mjgWCa0ImUfR9q3Jf6x9/YrezyP7OSwLNKGfQUsWgMlAYU0rHmKZEkCOrEUZZ1Shzv339hqiFZLHJm6uJyoFv6y+4i
*/