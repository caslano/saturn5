
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct not_equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          not_equal_to_impl<
              typename not_equal_to_tag<N1>::type
            , typename not_equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
YR+0efIibcBrKcvzz93SanPM/utX3XCiSoPv9hzmt7/lHa258dpvl03acuuqjjfv8A+rUerq3a2rfk5cvdP1vP8T5++SPe/PxNN32J72c+K8PxNX7+Y9rz+5w/IufMOFaeFfd9rfat3lPQ/Nz32Uq3O5j7J817S/+9a666cDrQvebR2yY8zAa/fu/6KlvbSUjUiZSTghlH9nKQuknmMtPIOBeBab4DlshaXYHz/FoXgeb8bPMQW/wAV4AbPxX7gXy/Fx/AZfx0v4GX6LF/Ay/oA/oT9xuYIh+DOG4S/YD5X6kJFYBROxKmagD65EX7wbr8MdWA2fxup4EmtgCd6AZ7AmnsfayDqGOtgS/bE11sO+GIjhWB9HYgO8FRtiKgbhQmyCi7AZbsTmmIMt8X5sjXnYBguxLVrKrKRe5imDlLNI+Uu4sm/lu4KgTE9J/hRiID6LrfEI9sXncDAexSn4Ak7HFzERj+FKPI5r8WXMwyJ8Hl/Bt/FV/BJfk/w5iV/hG5JPxfgLvoUNiOfb2ATfw/Z4Crvj+9gDP0RLvU2DlKNI+YpyfrUxU85viPS7MwwDcQTeiCNxKI7CkTgWZ+B4TMKJuAwjcBtOwh0YiQ/jzXgQb8ECnIEXMaiKlIlIWQnxsfTlU1M+Dwskve/EergEO+NS7IErcDSuxFhchQm4DhdiFq7Ge/BBXI/7cAM+jRvxDbwX38X78Wd8QD4Hm7ARbsaWuBXb4TYcgjsxCnPxTnwIV+Ju3ImP4KO4Bx/H/XgMH8U3MA/fxgN4Ch/HDzFf8uuMQcpLcKKkTyPlGUfyK0jyqyk2wWYYis2xF7bC0dgaJ2BbjMFgNGJ7XIshuAs74CPYCQ/gTfgmdsaL2AUvYSh+h93xFwxDJb16YhPshS2xD/bGvjgAB+BoHIhjcZD9OpByEik/0V8HqXKe8zAQ0+R807ELmnEkLpDzXIQpuBhXYyauxyV4Py7lv/24DB/HlfgcrsI38C4swTV4Dtfi17gOlTjdjXVxMw4nrltwJG7F6bgNo3EHmnAn3oG5uAR34WZ8ELfiw5iLe/Ag7sUncZ+t3rePlKdIOYuSPrNUba1el/R5W9KnRNLnHeyA72IovocD8X0chh9gNH6Is/AjXIwf40Y8g5uxFA/hp3gSP5P0+Rw/wq/xR7wo/VN9g43wewzBH3Ag/ojT8Ce8DX9BM/6Ki9Gg1L9HX1yLfvhXvA5zsBrmYnV8GWvgB3g9foI3SL9AtbAp1sZW6I9hWBcnYADOwno4F+vjAmyAWdgQt2IQ7sJGmI+N8Qg2wRexKX6AzfE7bIk/YRs0kDedsBF2wVAMxaHYFUdjN4zF7jgLe2AC9sRk7I2rsQ9mYT/Mwf74KA7AYzgQizAc/4GD8WMcgp/icFT6tRqBzXAktsYx2BfHYjiOwyE4HkfhBIzCiXg7TsJZOBkX4xS8DyNxF07FR/BmfAJn4N8wCs/ibXgJb8dqXMfR2BpjMARjMRxn4hCMx2E4C8eiCW/GOZiEc3E+JuJfMAlXYwrei6m4E+fhg5gm99Vwg5RNYR/5HvTDMIIyxUjdxlhsijOxG8ZhL4xH2Q/lSq73M1v2kyD7Mcl+5sh+5sp+9hqkTAi/lv0E4DbZz0H5fB/CQHwK2+DTOAIL8RY8jLH4DMbhs7gAj2AGPof3499wLz6P+/FFzMPj+AS+hCfxZfwSX8EL+Kq9vz0p75Fn3N66/vZC7etJGQ3W/831pAxFnsePGrTrZTjW42Rlf7+5HqHQEb+9uvVuVq0X/hvrxTrWo1xA4lfJeqlu7i/bdh6VrJdfyXolfJ7o16fSPoNa0i9M4viqmvq3x5c56uC25cZ4SpknqOvjJi6n3is=
*/