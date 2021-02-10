
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
qnkT3Iiy9Yb6IQPJabRpl/xws+FAowgyLkHVmaxrVfqENlX/TNHgdWJ1RKxxzZ5nCa5pfq+dQG+iX4EFVCqu26ES9suXz3+xq7lwzJlBoQm7o59Y8yBUgJ9YaED7uSuQUB9BdQowEWu9E5Jcb2WM4K1CqTSoMGYcUg4+12gAdnHLg2Z0q5VK9fOCoXfKgOffZOBxKj99bJhH09H85nJ+TUiHmMfHd9cMOhe+3yPseZUsbrp+dsnI4blokKVPMjOcVEaoNyGT1EWtHun57ivSS8ls4s5Jr0cmZv5qQmbmR9cni9S9JZ0GoRN8X1yT34kbkf6CDH13S/roRUqUWV8SNyH9EVlM3NDMPeIKo/e3+vnTbh/jOeSxr4Mm1BsmRn2eQSa2Z3l97LEAIcEXQFOaPdnFqsAb47UPqtomCcY5x3fJj+FL0UoebZWnvomf2s2ZiD208F6cdrBHYcwxNRQatMMYVlJsciUWhejUIeS1ByGvVSrGmdhXQCXHtEELqFrEOqLxx8pwFDIplFhpezCYOc/LlS9P8/cwbNQMhrtVBWKFTlOd57hBFVF5u0Xy4t4ZJrQsH7Gs7QkFWYGtv7PKF7DK95r/6pr//5fQrmxazr47P4VOThW7pl3wBgoULHRuBVonKL6ftlacImFx
*/