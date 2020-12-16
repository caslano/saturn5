
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_impl<
              typename greater_tag<N1>::type
            , typename greater_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
17EOcZ7Cenga++MZHIjv4xA8i6H4IRYeF+Q7G44zOC7cLu3/DrwF/aTcHbAedsSm2AlboT92xM7S7rpgP+yKIdgNw7A7jsEe6nu5RBbPD+KpmR+klcTRGqthG3lfEMlX3tdA3ueB3eR9veV9AVgT/yRxB6I39lHlHyTr8TLIv5GspzHWxSbqufTlfQ0N3tdM3tcc66MvyhgJ+R5CW5L31cEtmnuyDEAvDMaWGIKtcRAG4J8xEAfjALxT9u8hOAWHYhSGYjoOk3Y3ArdhGO7AcNyFo3APjlb3XUYV95nmavpqQ1XLZcpy3qUslxVVvJ1zS+j7zbZZn/3l8lTry6pcQh+xtRwlL8cTybfE5UilLBfo4Hwzv1u/r2tOmVLnlKno+WToR7Yzpwwpx8F5ZcrQv1yRc8vQ5+zQ/DJ/5Nwy9EmXaX6Zhmc9pJ+6YuaXySR//7MernlmDOaZGUy9xJM2knJI50juHzJfPymYFE/aSMoh5ZPcP6IeSaGkDFIWKZd0jnTtI1fft+vhevy/Pf7N3rmAR1FdAXiBBALyCBAwQIAQXuGlAVEeIiSQ8IwQSRAQJeSxkEAeS7LhIQFBUcFXEVERUVFR8R0UKiBKqqBYoaJFoS22saKgoqaillZr+8/u2d27OzPZXQhU253vO9/PDnPvPffcO3cmc+659xz5/20lRbXj/5+v+P+3yN/gEfI3VBiM0/xJqaoPmk3w0zNQIL/ItXZ9tB9/Q4vxPr5W3/2pxR9SDMXX6u0HFL9fZ3TBF+f2ix4kDU4mQz/hCX5r5RfI72p+i0/L7Zs38qk1Ft93w3BsAMNhV8rdMN7bDz9hfHqKGMFhgwQ/Nrgn3b8NWsbXbIOjbl+w3fH7gBorL3XsFs9v8fGfMPAnH+GcRbtG9q2vEn8y/mrjtctVO0o7OH3AMsdB8cdqvw+a2HVNPb0/rTF/XFZneOyqOWrFiw9KAvalaf8udeTZuHkP6jawMIyyc7ScMu3ZBV56xIYZ6xE5SdGjpCDT6dPX1Ajcj+jSoy169ESPNIcekhOK+M5veMZYF94d9f69M7VLL/SJcOrjsouXv2K0vK5cLr7GMcgFWh2cuuQWZ9qzsgus/Sif3hTIfguqDp4+3ps87aWeeQJlzr0+3H2vTPqeV+yw6Pad2OkkkkA+FZOUtQHoO/jruSOD8/363oNa381S7kGz/QhS6xv7PauvPDt+z331jf2ekZPPrt/T5Y9MbGAc75ww+ezFO+9uYBzvnDb53MU7944w9lPaJteOn9J1/22KMPYXrpp89v2Fwfp7jP1SZv6/4P12wcbmGvufzPxwwfv/gvXbGfsdzfyywftBjf215n41Y3+tuf/P2N9p7nc09oOa+yNnOvyRB7OPlH23776//77J66sHX79nhbmf2Nhvbe6fpusSmyTvrfI+a0Pi+HeMvONOke/T02AUvBq2g9fATnA67AlnwCSYBUfCbDgZ5sD5MBeWQyu8Ec6E6+Es+DDMg1vgbPg2nAMPwAL4PSyEjdGpCEbBYtgN2uBoWAovh3Y4AZbBuXA+nAcXwHK4EN4Fr4Xb4SL4B1gO/wEXwx/gdRLLuwyGwevle3B1XXnHlXdf7IVtmIMEOdx7tt4k9loh9loJ4+AtsAe8FSbA2+AAeDscCu+AKfBXcDy8E+bA1TAP3gUXwrvhQ/AeuBHeC5+Ca8WO98G34Dr4O3g/PArXw8/gA/An+CBsRmUegm3gI/AC+Ci8CG6Eg+BjcCx8HM6GT8BiuAkuh0/ClfBpuBo+AzfB5+Br8Hm4G24We2+FX8Ffw5PwJdgIG26DzeB22AXugD3gyzAd7oSz4SuwAL4Kr4e74C2wEm6Av4GPwdfgc3A=
*/