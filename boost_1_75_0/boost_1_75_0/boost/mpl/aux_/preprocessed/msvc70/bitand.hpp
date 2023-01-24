
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitand_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitand_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitand_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitand_impl<
              typename bitand_tag<N1>::type
            , typename bitand_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitand_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitand_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 & n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitand_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitand.hpp
OF7xd6BgsnAHlVjaiKGRRKDfeCbjx+eirEKNN98Ss1UdPG4a+uTcHHir4u1Vc6n7Yx0CVutLTekEK01oAlXLvFis2VUF0jz1PqZsFEirNyiCjlTf32in0txbWwq62Aew11Ejo3KsDQBm7oKSklnCZcJrKoeqCvVvvoisMQ96cPyJXO8MwSTmhTzS1bgilJOO+twsmkDzwf+OqqjnQ0NTGd8yPYwUhbh2fZx24BH0Ii5zlI1Hpibawjl8CJBP5bbh/lzsUZxiX6T80BQh4/Aj35eRqLcUWCFg0MP0vB9YT9YR5NV8T09NwLmyEGDGj8lf2I7+931PCTLa5C0l9fTepwe/aPB5LbdxaPCJckjA3z9W8VO4DuKW9ZoPsF9SuwlrZ5Wo08cr+o7huNC6DlKT5A1rFccWr30ZwstzE1NUP7CdrjqQ0+X95BVOuF7AQ039k4e3e8AtlOi+WmxBuNvdzd7JjZN6aILx0G0AaSrEQw0B8cS1yf/Ijz5GxJhf/46zo/JDocJJ9y5q+2d8mWTCUzO/FbOhQwKliaeNX/SttgdI6MqcHeF2BZ2nZC5RooiUwZ6asss6bizMti99fXPVU5Ynp8ck549p645GFmZegWdfySiBu3Z9F1C6IIxMddeUUOgvNv1IzFtFWYTLwvVZtyAaF4R5ucR4NZ7414qCLfOZqcji1tBzvrkzxCHC4+7OX35l/jnl4oezs2v2
*/