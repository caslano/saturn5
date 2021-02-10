
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
    : v_item<
          integral_c< T,C0 >
        , vector0_c<T>
        >
{
    typedef vector1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct vector2_c
    : v_item<
          integral_c< T,C1 >
        , vector1_c< T,C0 >
        >
{
    typedef vector2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct vector3_c
    : v_item<
          integral_c< T,C2 >
        , vector2_c< T,C0,C1 >
        >
{
    typedef vector3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct vector4_c
    : v_item<
          integral_c< T,C3 >
        , vector3_c< T,C0,C1,C2 >
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
    : v_item<
          integral_c< T,C4 >
        , vector4_c< T,C0,C1,C2,C3 >
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
    : v_item<
          integral_c< T,C5 >
        , vector5_c< T,C0,C1,C2,C3,C4 >
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
    : v_item<
          integral_c< T,C6 >
        , vector6_c< T,C0,C1,C2,C3,C4,C5 >
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
    : v_item<
          integral_c< T,C7 >
        , vector7_c< T,C0,C1,C2,C3,C4,C5,C6 >
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
    : v_item<
          integral_c< T,C8 >
        , vector8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
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
    : v_item<
          integral_c< T,C9 >
        , vector9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef vector10_c type;
    typedef T value_type;
};

}}

/* vector10_c.hpp
gBIOqPBkHCyEUzZXYlmhx74IhzF8rdUnCLswzRyEnU4EYRBHURyEcP+YeqypFsPNWmQlEnjUDoZw+azVj49wOUfpj4XjE6U3FK+M/GZtxcP2gEhM16gXiwnvtIftHszGM97dn/bYRFjnPxqpcoXyLwyCQdwJ4jBqGNylooihJZbXfeFfd/p+lA+HvUEetTx2k2W4PspmY1juSHLvpOYEdeHKGLre7wIfE+GKD/rnrXS3ph21EgXyQuUe89hSSFK+0ZaUT0uEpZE7sKXZVBKWCKrQpkbZbhwghbLX/zb8axsaC47iJvzY82TIbaX2R5qnkB0CSrAHrUasdG5N6e8hJFqssHEH6sMTA1cLbXOsYatcCY783ZamQsgVLaKqUZDb0mx1ZYRESRi8AYEkM6uV0LIpE3N+MZ4u0odZfLHHn03nKd8K7fgwBP8WBn0icjpBv0eudIcXrFVOReiGIHJHXPY09qMDSmGpx1BDixrOtVjydsglgHVtnMlMNWI0PeBU6b3xPDY21sXwByeP/ar850Hf99gzCeTfFMQnhmxTV/zi5W6+eJg+vfsak0NXjQ/nuhSc2PDzoPsJUEsDBAoAAAAIAC1nSlJ6V/QCwgEAAAYDAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0
*/