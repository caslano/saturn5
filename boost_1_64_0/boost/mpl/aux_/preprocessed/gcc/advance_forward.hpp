
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
gmVB/sWsiiv3PY9L/23iys7nspf/d8/pku8ApnO7Ksv9m991udznHC/69/8z87ySnvdvrpe+r752c77M++jV/nn65r9fc7+kT136033PAYtuEGyJR9KRTcgR5AxSjUQ2DLYMRRYgxcgB5BRyAQlhIk4ckojYkZKg+n7y+l/9r/5X/6v/1f/qf/W/+t93//uWvv/nZ9xa9+//yhz/IfSfWx1z/JV1cZi1mGzNLrA75/jbyUyR9m8Fzjn+/TRjBrIaGOfhDCXN2Ofc3wJmTbhRmeE/IDnVbg/ke90v2CCj6veIN7AoSejWLuoh39kHiA/9keH4kODNB1kfKpBvM+KLz/WhnF+S3TEGPmxFP/IKe0aBpBMpx1kzcnX+nzfxfwT+l/jyn1mbdfFf1o26Iv6XBRn9H4X/lb78txcFtFaf+K/OQ8RpR12Q72N1yofr+95QeaVsJ/lQjosnH6HlhnxohsAEngdHfZa1jkinwLM+N5Zv4EVIc/F1LH7E+fRDuUD9/97m3ReJmaGv42qMC46h2NzfxmKDHft086bzl+ny4+z8kzk9zYX50dQPfX5kvrstP3uZshAnH4b9ignijCla/TxpSYyQHP6tjXs3m21t3LshbGvj3vVStwfryke+R6rfqpdq5pUr20Uea/rlLdV/yy+WfEdKfYpAxivt0gv6fMsKfkp1Drgu+VozL1K+o8+UejRVYmjY9PbddUipQn58Nw3TzM/HB0XL6/x7qUO6ctkkfsVIuUQjE9io0vvlGKskgwwCLhdtOXRpbBwXNVG5rl80sScDgwIZ17Ek2mFTPz6KdLTtUoGyjwFenmMddjc2jq+ZhG/xet9qPUZKykNX/pFNjPVyilIvTWwqlTKQdnpJdM31skzsR4v9dsg07NtM7au36zr54GUtR51fk5oa/ZqBX6U+/OI2XGu/5B5co1/HxS/tWrgJ+FXpxS9n+JnAz5m2ze5isqbejdisNtrUtx9+3A+1easWO6eljXoNmRWjZNqHHbER7kfepP6r7VM8VklHjfuhPBvY5DqtZlv7jCltuxoPRb0PBqPjbCr18Z5CzNs1y0seeanF2CnyYThHb4eY14s4vT2P8Y65fs3R91U3Epob26zZMez3tFuHsVDYNbRbFc2N+U3Eborebq3GWprlc4TM528u9pohc7FX7GGvoBbXQJgmfpGi4TnGK/Ya58HXyDNTM3gTtks0tu15yS4fHPYw6DN22l0vo+uInebfmDzXc+BNlE2OJl6Wsy7a0XFeH04ddzy0apPngPXt0MnWXy+lkscOUr7tkXs5rho/yWP2wHTec9UsMkraj3L19nz0T+U6t7nHcJVewTFc5mO1vI3t+s+P1Qp0TJb52K7//rFaf4hW9h+a23B4q3tujp9zeMHtnc70OuB9rFbiNcr+FpUhmzI7vz/qkxcHH2udMznL+1gt87F4gY/h8jZGzDkmRPpS5Lm1ymNMyF8080TbwQuwI/wYdoZ/g650EiSdASbpfCXpfA27yfznvgpgf9gQutIp8ZHOJ5LORUnnM9gX/gv2h5c0/lT6SOdq7AXBxrAbbCr+NBN/QqBzrJO8n8N2ko52rNPPxJ/XYSQ8LfazFF3RKxI9Wf9Tt27iizAcHodR8GU4GFbA4fAEHAV/AufDV+Ct8CS0w1fV+ejyvivvv9jTzUefLfYSxd4csXcT7AWT4M3wZpgK58NMuBDeDpPhWpgK74eL4H6YActgJjwFF8PX4VL4LsyBn8A8+CnMh80lfnNbuAxGw+VQylveX7kedeWtn7f8EYyAf9KM4bGJ3kzR047hWSf53wA7wI0mcTyGwzvhWLgFToZb4VR4lzZug9iJMalXE8W/SbA=
*/