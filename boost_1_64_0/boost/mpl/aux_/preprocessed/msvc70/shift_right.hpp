
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_right_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_right_impl<
              typename shift_right_tag<N1>::type
            , typename shift_right_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
0lMH8cEigbPZwB5MFM2TQoUJnKOotQRXUL73yfgXFfPA6t6PkpRc8+uJsA/Eo5sZvUmzsa+YRzPxjuW7Hhtw5iCeZmP0B38dI4NhTVrEs6CXEh0xgM7kwM106nLatjDI4yn6NIojoUyp/LgyChYfZprrD42SSgf9U0kX5Cua827Umsz7GNSkZq4xdzk+XPzk7zgsm2agMlFVhWcLZ5aoI5oQ0B8f6ddBbMZ/Qcp+KiA0h8nRh7Jt5JfnH43rEI0itYY1m2aeJzHX2fMl+jyYsYqBoH5lKCcQErP5NnR1rgf+zhgj4Lizm391bZcww6DKYqPL2tfEcRKaV5mPlhsBWhwElSalFLMYxCXUjPoIa9DR66cJvR5pgXqnuJtsOyOF5rFgzVmyeTv2pgpuftktZbFQup0T/ATDXZvca4RQ4ECxkGYtweoAZDkjDh1td8WKJ+tgz7UZcE7iexQQyLV9J+WfFbaNUE7ZLSRkBWNtAV/ZnsLakf1LOCnZvF/32SChIg/b0jKKk86zRs94198MP8KXfNw3bTIk4Abaz/3/fFYsJ/LoaFUQHRdWhQ==
*/