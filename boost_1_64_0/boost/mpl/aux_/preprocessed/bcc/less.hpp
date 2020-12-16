
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less.hpp" header
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
cQX5RKxhivky/avB66/FZwuJS+q1nF++GD1Ad3ER/cX6UgE+m0ncIcuZVeQKxvdhkyz6T4P/Msb056FjctST4jdRDPLPIo6ygVPPiMfP4pAPWXJp/3QSMlHaK+FnPr4GjYn4w9nTsOVSbOIiRmmbjU2uSkDvYl5ro7/oA093MX4Mx792oONEfFnc5xP3jVOJ1ZXQi2ecUvqmo78c9AG9R3xcfyrwEcr0duIGGZ8uIPch33J00ubBn4Bl0P9C+HbPAxfeI8R9O0qUFXkoD2aRQ3zkSGhetxy6jfRBn8sc8J1MLqzABsBd1JnQWFhODOTAj7i/jg1mweefseG3HdArJU8sIkYz4B1bLanB38VvpXT0QJwEC7EhOvi9WGdKgQds/EfqR0sYV6wpTianiN848Pk9eP6GDzrN8AC9JxjrAvGbJp/xofEastVl4XOVxFwMdha/eavIszOIbSf+7OeaO5FxiogF4vwBxr6d4/PT6CN+q0NjDDQ2lNIH+f4C/iXEhXspcDvXlQp8u4n4xcdqJqqbDS+oYtwWbEv7d7FJ2TTyGjifIusa5J4Az+2Z6KkdevAWjENPwDaXY1f8qQeb756JTzHmzQp+DO8WcDKAz6FfL2P3zYfHecjO+VxozmOcX9UiwzLilrGnIcM/KJfMgYcV4FdyXkasgnPtdAq8/gR/eg+9vp9ITGcR6xnwPhu+6P8mY8yn72WU7yfg83Hg1aEb+j2P38Y3QBsdnuxjPOz3oyRsBA97l5Mb6H8Tsj4HfzWM+zX0B8TvaS+6oG4S973g6dFaxhBzM+gmUCYD6yEv2Th+FvnX19KWxxjY8iHGCHIcb8fW+NWx1Ivh5Wzozcgkl2UQF1PJZYyXSoyczvEAvPwGeLlY1xXrpqn4WSw8wf/4GFQK7Lut+EEBseQhvoqJGZHnGftFfG4XOJN96Jf6ghPIwcTIDymLOF/ug7ZYu6Qc34QfijlqHDnSjq4K0dF04qyGc3x1i7A3st03FZ4ZbyllssJ8iDYHvDqxU30MOQ3aqxuRcSljI+MR6OIGaI6jPaaNOp5xl+BDVVwniJVfRKALD/opI8fSdi7ld7S5G/Aj+H91JTCFsYiVT+CrOBVfn47MlALK1iJ8AFhUHfxBdwq6vB5dV/jxXWx7DWOWV2Mr8N6E5ruUwEx0NRvbUD8P/CLkWkefzVnwmkhfdJpZQ4x50BlFETkym1jNQD4vPt3E9Zp+jzLG6THoG/yzZuG7Yp1ZzLXpE2HFJtCYgZ56qR2L0DV8WPLgi1jaMx1eqM/Ex+4B9gPwLhJ7mLDzvfhMD+XKOvhyM6aLmKG9Gfsp6OApzr8C9y9RyEX9eQBfsxHD2fSNJf/noiP6/Rq7xIk5ML7xIX0/QN6pqeSxZHgA1kycpVvJF+LeDLn0l8hVbYOmmKvnQrcQ/VM3i9/bzcgNby5gn6QBF75dQmyLeVEe49Ri9xXkRg/yiPv18NtXho3Q6ynYwYZ+Sv2kFspnwH43FV/GP25l3IoI5PcRfw3oD54ubaIPugnA55fF5A7ovsG4v6DvmzX0w3ZN5eiP2PhtNH4krqPF9BdzVnF/SVz/48lr2dgG+Uuqoa9ga5FDqPuxczHjfK8OHVvhG17HO5ChhP7E+x76tqCDnEX4Kfb5FeMeW4BcC/Hxuchhw6+hW0H5lHFvo282fVfCd08EPGVwHYHOjZSlCjFHW30bMGKlI8A1ohwdiOsmuXM6OC9ayU/idx5lFbI0odsqaFZTfwgPP6wlF9vJRfhhw3ziD/0tdOEH4Dc3Y+syrtsnwC+83gneFWLdNYE8YUNX9L9O3OOC90z0dYJYJy9AdzX4eyy6KcWvxT166hvBi0Q3vSI=
*/