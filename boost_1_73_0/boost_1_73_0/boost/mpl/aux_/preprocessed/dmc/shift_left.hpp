
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
oaf0y4nCLUv2rdF6zQuURISkosUYz43hpLMX0uu9EbZV/KxUHqZTPG0DKunUmbDCuYoatmGco3RNjXaX2R/EfsYJS1YGXj81rJQr6ETThEQJntCtEDW1dvVxapZLqTMwlad9Emiz6T6kL6XTsskw6O6LhOhfzR6S63nU9waYz+4T4QplBS1XoPDqAJ+9HaA//3kuSrOAf0JIbai73rQbsJganXXR35Bo+M3UXs2taK2cj1irfA2tZWXusAZCbh0HhbTEHjUEtjAuYPFLW0sQVW2cSU05YZcXCbxntDV7j10Z6yJ4x6DHftAT8dMFDUKeaupS9B8v7h+uZ3e9jSsj+CA+9Fivu+IN4/8KH4s9m9hbFzrvkmztbfSUWzv67KZo+Kpqr/4ftUOv9k40sf/l/AZQSwMECgAAAAgALWdKUpUI4vSWAQAACgMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMDE0VVQFAAG2SCRgzVJfT9swEH+3lO9wYqqQ0DI3oy+NskioQxRt0IoGXqfMuVKL1I7sS7sI8d05N6Ud4gvwZJ/v/PtnZ4SeVOkxF5k2S8vLE3Zb6yqfi2lRzEUcb50mjG1LIpPHZib7+S+wQLdBF3tdocgcNnXH3aqkEoxVK1RP
*/