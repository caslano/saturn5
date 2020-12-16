
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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
NJX2aiL7k6uzP7Gm3Sm+vcpjf9TPD8dI/MDr0uavkNyoY+0cax2jDanWepagvRnXMaf499OlspH4pIkR8arnWFI/a7uyj9KuhfXNlvp2lzbtSnKvz3+sbWruwpMYvColpuTtqTfGk6+b5tmelJV73LYsikotSV8vqqwMeY77QiWOA27Ayex/zvu2ZSUkRYUx+JypLJ9ijkP4h5rjIP0i2bew3zxDmw9SHQOpm7bPmOZP6oyVZdqen8QiyPzU5EnTre+klGUJfuaYAn/adAz79p3yuTisGitP1psi8wUyL3Ef1rw7yKs8S+hxRPUZlHU5X5jWG886WaQlzC+X9ZT65ct6UQlT/Fxku+pt51UyP28dd9Qm1kHyMOqipi61K5vL7PNBYV1yLfWmUdTrBrJuEuv8cKxw3TOWbbsUjtH3o9S3Ep9BZf6Vo7bzY4/Zznf7sHBe/Vw6W55Lb6bsmqJHfY7v27b9iZelTI1INdiM5edfgvE+F7xXOJ5nwbv242p+VLjMOibnK4XLulmWzStc1tVF+u2g9wr7rTwHV8fPyDlEFWej6r8SnyP9V3XeUcXcSGCQ6nhJn5Y+LHE5tmMtqvqa3mdisqbfTpI4nnw5j1lPoLLeMfX7U6UvaM/Zl2QdZUSrxsznmMqS86b1lGzu83PpX5k01HHl+Vy2+nNl38fukf9fWfrQn9n6fegwf+iVaZf0oW3Sh0J26/ch9biJgcWcm97ff+uOcUExx/hwMcc4VxOjlq055pdUx1zOeVJeiqkP5Nn1AcfH/LzqmKv7V5zEcR0rog8cphE3VjP3gXb71GOL2vcBj322feDEPv0+0FaCIP8m48buQ6UPBL2p6QNp1GWinEbke4x3MX3grYN/nT5wvpR9IF9zzM+oPs/az67Svs++pd++V2vKM0RT+6K078Ftuu0rH7GSjM1rPk+H7io8T+/cYR2b2HpOXlO4zHpOnla4zDo+8wOFy/wt52n3Xbfu+OVpjt81zfE7ozl+VzXHr0Bz/E6pPsPa46k9furjH0dSjuemnTbHU9775SjeqPRj5+nHD5U+rks/bqn08UD6cWClj1sqbVyXgzinUo+9qB/P5DhurFNHZfmD+7OiA3Ys7PRjzqGZG1Z3W1J+cW+O4sys8QZyjVlN3suljhvoJHEDvlgF/dA65p3ki9Z5X9h+iXs5gPXwIHbE97EHHsZQPILh+AFOxA/RXC+5dsWmOvU6IfU6jU1QxswgzkauJ/F1yVcHV0m+lap3HnviGmyFa/EuXI/98Bm8D5/FYMzE8fgCGnAjRuMWNOLrOB234jJ8A9fgTtyEu/AV3C31HOjCJPvXXepZGS3fZWq5sn9YG+tiHWyOddEX66HpehQvYICLXCtiI9meG1qu26rK9qrJ9qpjA6wh+b1c5fpPrguV/BHm7ZumwTJG0hB0x2HohcOxE47AXjgSh+D9OAHHYyxOwDR8EGdhGM7DCFyHkZiFUbgfo/E6xmJ1JU4LG2AceuIUbIvJ6I9p2BunYhSmYyzOwCk4E6fhIzgDH8WlOAu34mzcj3PwIM7Hw7gAj+NCPI2P41e4GC/hMvTm87gCffEJDMSV2AdX4xB8GhNxHT6E6/FR3ICL8AVciRtxLb6Iz+JLuB1fxm/wVfwFt+Al3IrKB2MbNsTt2BT3YEfciwNxHw7BAxiPb+IUPIjT8W18FN/BuXgIV+O7uBvfw0P4Ph7Go3gST2IefoLX8VN0o+N9hi3xFLbFzzEIT2N/PINh+CU+gV/hU3gOt+J3uAPz8RP8Hk/jD/gD/oiV6KfnsRr+hI3xErbAf2JbvIzt8Qr2xt8wCf/Ah/EazsTruBAr8nlYjm64HivhBqwsn5M=
*/