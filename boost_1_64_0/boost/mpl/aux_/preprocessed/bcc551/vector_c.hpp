
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T, long C0 = LONG_MAX, long C1 = LONG_MAX, long C2 = LONG_MAX
    , long C3 = LONG_MAX, long C4 = LONG_MAX, long C5 = LONG_MAX
    , long C6 = LONG_MAX, long C7 = LONG_MAX, long C8 = LONG_MAX
    , long C9 = LONG_MAX, long C10 = LONG_MAX, long C11 = LONG_MAX
    , long C12 = LONG_MAX, long C13 = LONG_MAX, long C14 = LONG_MAX
    , long C15 = LONG_MAX, long C16 = LONG_MAX, long C17 = LONG_MAX
    , long C18 = LONG_MAX, long C19 = LONG_MAX
    >
struct vector_c;

template<
      typename T
    >
struct vector_c<
          T, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector0_c<T>
{
    typedef typename vector0_c<T>::type type;
};

template<
      typename T, long C0
    >
struct vector_c<
          T, C0, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector1_c< T, T(C0) >
{
    typedef typename vector1_c< T, T(C0) >::type type;
};

template<
      typename T, long C0, long C1
    >
struct vector_c<
          T, C0, C1, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector2_c< T, T(C0), T(C1) >
{
    typedef typename vector2_c< T, T(C0), T(C1) >::type type;
};

template<
      typename T, long C0, long C1, long C2
    >
struct vector_c<
          T, C0, C1, C2, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector3_c< T, T(C0), T(C1), T(C2) >
{
    typedef typename vector3_c< T, T(C0), T(C1), T(C2) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3
    >
struct vector_c<
          T, C0, C1, C2, C3, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector4_c< T, T(C0), T(C1), T(C2), T(C3) >
{
    typedef typename vector4_c< T, T(C0), T(C1), T(C2), T(C3) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector5_c< T, T(C0), T(C1), T(C2), T(C3), T(C4) >
{
    typedef typename vector5_c< T, T(C0), T(C1), T(C2), T(C3), T(C4) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector6_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5) >
{
    typedef typename vector6_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector7_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6) >
{
    typedef typename vector7_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX
        >
    : vector8_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7) >
{
    typedef typename vector8_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : vector9_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8) >
{
    typedef typename vector9_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : vector10_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9) >
{
    typedef typename vector10_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector11_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10) >
{
    typedef typename vector11_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector12_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11) >
{
    typedef typename vector12_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector13_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12) >
{
    typedef typename vector13_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector14_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13) >
{
    typedef typename vector14_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector15_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14) >
{
    typedef typename vector15_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector16_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15) >
{
    typedef typename vector16_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector17_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16) >
{
    typedef typename vector17_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, LONG_MAX, LONG_MAX
        >
    : vector18_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17) >
{
    typedef typename vector18_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, LONG_MAX
        >
    : vector19_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18) >
{
    typedef typename vector19_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18) >::type type;
};

/// primary template (not a specialization!)

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct vector_c
    : vector20_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18), T(C19) >
{
    typedef typename vector20_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18), T(C19) >::type type;
};

}}


/* vector_c.hpp
4arvx/n0cmHo23GYe4ge9Pn4ulcI9+b77im69LPA9hIW9bFeGTL944qiy/n1KvFF/TC3d3jCQ5UK/DUJThUL/LUpPiHPn9cluZTH6yOO/gH6G29I85ku9qKl5CJf9k55TQWjMTXy8T3fGPlcRaK830d41I+bFbI8nfd9kS/O+9lJj+T9vkkueT8n4n7e75fkkvf7R9zP+7kR7533B0TedN6/KfL5eX+gcHp26HnjBwnjMKEfLDrbob8ZOi2OUedwHaJ1dQ7XoVYfmVcK+1z9mlWnJotxI7dXeIJRRBDugOZSB3gugGI0fQZ6Seumflr/fK3nsj/hAuj02Xpu34iZl0/6QqcbpY8gxWlI6+5twek5LMlkXs+ikNODi9niiMkZtEtChlU6WdZ2a6uGe3jsOapLY64aIIcxkvTId9zDU5yu57o8GnFZilbMa26hjZeTvtZM1qYj++heY6GH5uNTXlN+LYu4rDFfnmLqTM0jQk7L9nVEOZ4rYl+UZyuTHsmzI5Ncrj8q5p22SufRmstZURS/YzSLz6Uiz7G9PWawiD2VtAfnUXE83qI9/KvOGPeh66tJZlp0o5q7PQEiDz2xidUiRi2a8qeeZkUu0bVZxGUv5YmYmYrGcZ5MM5Q+xu6THpxhhXQ1Io98Vz8uYu5NRHx1kst3+6k0b3Qy/r43neTusxx5mmkPZj2ypxV7ZDkT3mkzSU+4uwzG8gOvXkfZ1ox2m6407LM714xCZL2jdV6jxGP4oZ7YW2uN9lCVUybE6QTtCfYqXptgev+hdUnemqrj+hM112e44d4nBdyUi3vnvzXB+NY4mzzBueSyzIZ/svYEe/e+PWBh2t4Rc6QN55ZrTtWW9XdpnZoVx+XdkU7zdIi9J2IyR+e9MSvRCjpce0rMR821xN4XMaq8xN4fs1XT1RqxU0M2S+L6gYhJXD8YMT+uH4q5iSvOH49ZZyrHMcV1WaP1kdBHFYrrxEcjpl8J7PlY2oNXAtbzJz149uGZ8AnfE80ApI+HqCuf9LxGR358SuvB3l2nJRhXT4zJa069YnonEftMxOR9c3rE6J1C7LMRo4pNefK5iMXvjM8nPf4ZHmckPRQ/4l9IcLw3eL1+kvvnvJ+Z9uABw54vJT3+XvBnpT2yZj/JXUGS52ztiTe+4/O7kx5Z1//V3rz4SkKeryU9WPuPOvv1tEdOm2yZ/0U/8Rvr86pvM+fEPtMH4DidG7M8rA/nJT1SH85PcqkP30zwsD58K+EJ68MFCU9YH76d9Eh9uDDBw/rwnYQnrA/fTXqkPnyvJ5f6cFHCE9aHi5OedH24JO2V+gDf931fI8/NaKvX7cC53tqnfr9cFuoV81ZS+038QHOXbdhTIMnkLLbLNecJOezK+fofRdx1FolfEXN0FDnPf+zxnPbPCfeSuVJ7/C4kj/sHXL97fxoxefde5bPo3Xt1xOXde03E0u/ea0MffbDg+1+XZPRThcr7es3VnnA3hDqXF++Prpn6pnqj1uk+HNZNWnezepn9XDPXDLBPeoLpvubNmkfNg/PwlvV49J7jv7S+cladUt+XbtX6kPh/ZXU3+oOzv63ujd4w+w0YfolO6rXDtymGgV/Sb9d6Xca77nB6llfoxK3xmn3f35lg1IssTnqZxfly1/o8vFc+3ee3ka82bdndAaNjW8DuSTDzD7F7E2wurrsvYqamgt0fsqw2btkDIZuUeD4YspZc97uITTj2kGLuUFTUzYcjhgNTce3vQ75Wfos+4rED+qjswB6NmKTjsYhJfv8hYpLff4yY5PfjEZP8/lPAdH4/ETCd308GTOf3nyMm+f1UwHR+/yVgYX4/rbmpv7o9PBOxuD08G3nS7eE=
*/