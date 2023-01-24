
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct vector1_c
    : vector1< integral_c< T,C0 > >
{
    typedef vector1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct vector2_c
    : vector2< integral_c< T,C0 >, integral_c< T,C1 > >
{
    typedef vector2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct vector3_c
    : vector3< integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 > >
{
    typedef vector3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct vector4_c
    : vector4<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >, integral_c<T
        , C3> 
 >
{
    typedef vector4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct vector5_c
    : vector5<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 > 
 >
{
    typedef vector5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct vector6_c
    : vector6<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 > 
 >
{
    typedef vector6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct vector7_c
    : vector7<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c<T
        , C6> 
 >
{
    typedef vector7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct vector8_c
    : vector8<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 > 
 >
{
    typedef vector8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct vector9_c
    : vector9<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 > 
 >
{
    typedef vector9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct vector10_c
    : vector10<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 >, integral_c< T,C9 > 
 >
{
    typedef vector10_c type;
    typedef T value_type;
};

}}

/* vector10_c.hpp
aNLFisQ2NafIFXhqZU9JsEwxL4zez/ZEqyLEykujXIHSeaz0fy5YoN61nQqVx2t/jVAx2g8hqIl8NL9GqJwkoXL7z0Yz4uxtG3QzQhUqSjuhEs/6PxQq7cyIroRKezOinguV4PskVNZ1KFTWXKUJldBV7efS7eeopwW6MUd9YdkvzFHnP93xHLUiPWmOSoPhLfnJFqvszOYu71Ttj/81NvfOk5b/YI7q4oxMW2P/l+aoK2/t2Lye8B+Y1zOgDg/GiP/XxvUafYa68Smcoa4w/bJx/azl/3CG2gFX/CfGtTpDvfjdbs1Q516p8cf0K7nPOeY57pe2icc+hFFq+glGaeAO8fQWcgU78X3tvnBmAy6sNNns5t51FqEIOSFNXe8uigeg3xYqkbjCFxWqL77tpQdfDA+VzIuhtuKxGeFLJPNv6NYaLpLMs+g2JzGgOC2cj6+HVN9kRYIK96u+CTdijw/n+qIse661KJ4wN6RB1SyeiGKNeiSNMT2XTEX7RKXcmnL2AQYDuH2GYIDaHWLshsIGOpJEOiHaSlmM827FUX0d0udcqzhvgl2M5TSJJR8u92L8KLRVwIIPkZRpsSHmyL6dbdGszGWJnyhLKYzNvMvtYE4A7BOAcPruFUs+WvYKVX/KdcyLSNEDsT16tGkh+f6S4vHUxfyeT2qL+d9hPJHKpVtZ2OcVVo0YvhQj11DwwHO/R3vmmjwhcg0e
*/