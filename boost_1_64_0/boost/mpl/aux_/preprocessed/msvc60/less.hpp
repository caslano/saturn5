
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          less_impl<
              typename less_tag<N1>::type
            , typename less_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
hYGYgkGYhsGYhf0wD0PwDuyPB3EAHseBeJHk/skYhjk4CBfi+XgjhmMlDsYGMqadhEMxFYfhVTgcl+MIvA1H4nochU/jaNyCY/EQXoDHcZxT34Kf6ltQoUKFChUqVKhQoULFacr/6+v8fy+uq/eYnryusBE5KduMMcbFpxpM/QKH7OYFKJV8czO2xBIs5nEZx9tJv4Dj+fsda9Ef8HAdzt/X1nnKfeJTjFnOc6cnOp+zL8sHZfkyp/MDEuzPJ2hEPVLsc3aWdY45+mxTjl68cVPjfN+f9jX77fvru/2uTbRcaZozQdpB2keLzpRj8qKDJUcPxXMxDLvi+eiP4RiEg3EgDsEhOBTHYAROwuGYjCNwPo7GZTgGb8KxuBEvwLdwHJbheNyNkbgfJ+NPOAUbUt9peDZGoR6nYxjOwGl4Ic7GaIzFSzANZ+JSnIUlOFvOVR8b1tiaJ8eqPFmFChUqVKhQoUKFChX/4Tgt+b8hIb6+zv//1e7afxmWcWUP8nxsi5u0660ds+b5PLNl9L/21/5zM/Yv11iTvoAsyfNdj90z1m6f58t1/5zy9JWmPP3bR/s8/M5Rz/dGLLqzR/m5q36RsXSdvA55fYTDnGlnS57eES/FTjgXO+NO7IKfow/uw654CLthUxk798LuOA974FLsid+hH2rt2ctpLDlX5cgqVKhQoUKFChUqVKhQ8a+M05L/J8TX2/x/R+3y/1S5hnzZmeT/YgmJbWCFNf/nmS35f22O/W9hvhb/zzzebrlUltvqGrdZWWn6t37CpH5BOlmXY1sXaFkXY10XHGZZN9q2LtSyLtC2bqBlXQfbugGWdb//ZF3X37Jun21diGXdD99Z1wVb1n1oW2et8wu2ddY6r7OuC7LWOd+2zlrnXNs6a50TbeusdY60reuvq0X/iqtzK7T7eNr1ubRyOKeC+7Lc0UUfjO18hzQ5dsJuXgS7eRNy0jOt15A/LOt4TKBl3UHLOioYKOuq7NYFybq9tu1ZH3vMtj3u5niNiSUyJ0KG9F2l4lN6/nHI+t5NNNT6fUu7oq/d3JMt7I5ZsZ9LMidY5pVwMY9EtrSjw1yVgY7zTqRQ7OeESJXlMjk2JSPIce7LnH6Ox77kyO3HLPcPdGyXQuleCpZ26Svt0vqIpV3q8vdcc7tY6xnsen6Nw07tUuXULmU1tEu5U7tUOLXLQXft4nTezcumvkLd0RXGVhM39/EsKHon1Sf3HZlrw0M+8+QzUIthFE8P23UaWmJbbIftsRN64TzsgO+iN+7Gs/EwnoNT2ei5uAE74pPYCV/AzvgWdsE96IMHsCseRV+MpQ7dMB31uBO74wfYAz/Hnvg+n+V+uAd74T70xyrsjQ1pkwBsh33QF/viMjwP78BAPITBGM37qB8+gyH4AvZHba7PAZiJA3EBhuJdGIY/4yD0YI7H83EmhuPlOBgX4BC8EYfifRiBuma0OcbhcLwUR+AcHImZOApzcTR+iGNwH47FoWdwLBROwnE4G8djBk7AxTgR5zVnDkq8CiPxWpyCFTgVJ7L/ozATp+OtOAN5n/D+kc8XyJD3RhdKI+lHXybvkxuxM96E/ngz9sNbcCSuxEi8FaMxH2PwdkzCO9GIBbgY78YCvAdfxkJ5n92LTXjuVdgJ78MLcDXOxvvxenwQC3ANPohrcS0+hC9hEZbhOvwRH8EmvL712AkfRV98HMfgRkzFJ1COiZPPF+1z58Rj4i6SdomRdomVdomTdomXdkmQdkmUdkmSdrlU2iUF5+PluAZTsQTn4GeYhj9iuhzjloH+eAVGYSYa0IgZmI0LcC5ehfPwLrwS1+N8fB4X4DuYi1/gQtyP1/Bfc17vYuyLS9A=
*/