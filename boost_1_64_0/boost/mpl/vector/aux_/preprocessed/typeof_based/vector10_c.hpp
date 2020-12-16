
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
M90gcO+9uO5nDdxXH7hf3/Petese+u695cLr6Lb1aztLhQkx+zc5pMWYpU11GBDV1hEdYtpfpExCu/tU3DsffpA50vYqwUXFxTLbHFGmx4y4NbnKstg3OaBAkyGxa/r8gk0OKFLQT5sJiS351V/7wfIijo2t/9z3PyAklgSrZFj77/37x2TFFnNOiSVjKbPl/C772ihQp09YW5scUKJFUxs72qjQYcKKtibE1szPf+8rHop3R99tRiSct63OIYvWxYr5mtze9yN0ybH0CPtvc95g17F72t6jSWJXn6Qp0eL0lud1j74Yba9Rsj1kYDv0SPvIsEOTBEX6TP57j/4auxxRZu3G/rZI2WZM9L/36W+wzzF9QnvmmXtewnxxTsw1TuY6rn22ruv9huhjnE9N3Q5jUl6nnyxeWoyIH4iVkmM5Y28qN8gyJPJYc8s6u+SosPRE9Yg+RU7Z5IA8dU6ZUdB2nY5zRkQepz6bpCnRYkQ05RhbZDihzZjY442HTQ4p0WJE9AnOY5M0J7QZExPjaN97mLGmbBfuaQzKOlH39i9Tl9e1fXkm5XWRNfV3GKk3d3b+U61pNo1lwgo96v5Iu7hvfM453hOT7antddspCv+9v37umc5VHlBjwqJ9a+yQpkidLmMiz5J7VtnmkAJ1uoyJpNVhlW0OKVB3HfSYMPcc42Tzv/fTr7FHn3378tQZELIvT41Qxvr0fXmZDlPmFs09WxxSpMmA8A2tTdbYI0uZLhNiN3Ium4z9nBDf8zMPKY5pMCTqZ6AltjmiTJdOy89KRL/oZ3Y2SXNCmwlR1/epe/1n5J//n3vvdzk982LxZ83pS4z7FdYB8VeSN58MKb9KbBSOz36OPXdQo8/CJV1n7FOgSZ/gUucO5llmi0OKNBjQvYrrknjCe/GCa5MSbSZEr6dtNtgjS5kOY2LX9z78AuuDEi2GRI5cD+yQo8aA8AvlmC3SlGgzZV4Oqmdfq5wfyMUB3dfLFeGXmq+z4yTt3+CYGlMWs+aNA4q0mDAnl8tskaFEi6T21tknT40luY7IbV1uQy8TP5scUqLJiFhOf2yRoc6Q2MvNE3sUaDEhYR7XiZ/NN3tUOSVkrGXHukzZEkOGnby4aLAopm0ytIm+WqxscUSVAdHX2M8WR1ToETp2DbLBPgMir1WXbY6ockrwOvFyIoYOU07PcmXfPgWaDP/v+QGbpCkTL8gBW6QpUqdnXvffYM6o0yf0Rn2xxh5ZSrQYEX2TsbPJIXnqDAgVjYkN9ilQp0/wZvPLBvsc02BA7C3GzRZpTmgzY/6t5octDjmmQZ+gJB4xn8M6c95rxncP+R2yuWPK3Nu0Texj9n1U338QFw1GVfk6u4/8i3JOhqNf6Nex8J/kgVV2SP3FWMmV5Z7we+SBEzrM2HuvOqT/Kse0GDP3N+udHTKU6VL67z31FXEsfEK8n/zP/dodMUwJ/VK/rP5K3Mz/Wv8k3VdYIzSWE9bdK3hAiRZjamLtE56ay++L+VSfIzn7jXyxxRE1En5XtSWODEMKHzBvDIh8UP7Ypv0lcRH/sny27WeHHA1G1H6ufbF3xB36rZhZZZccVaIflTu2yVJlwpI52uSAZEPcpCjQYETk03LJLqdn90Z3tEuNAUFXfz3HyVKly4zEf+8V3qdImxmJ79nPPkXaTJmXt33yVDkldGp8bJKhSvgH9nFPDijSZkrih9omxTENBhyY56xcRj8nF2yTpUafyOeNjWP6hNzPvsEBBZqMiLWsX3bJUmPAibVcmIrd35BUrZ0eM0Ij7VDhnmNrhiZD2tb5mMU/20+TETHraKqt+U+cx3OrzQ3r7JGjSo8Z833xsPFL/qrdDzv/I9Y=
*/