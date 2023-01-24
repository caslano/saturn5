
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct list_c_chooser;

}

namespace aux {

template<>
struct list_c_chooser<0>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list0_c<
              T
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<1>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list1_c<
              T, C0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<2>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list2_c<
              T, C0, C1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<3>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list3_c<
              T, C0, C1, C2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<4>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list4_c<
              T, C0, C1, C2, C3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<5>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list5_c<
              T, C0, C1, C2, C3, C4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<6>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list6_c<
              T, C0, C1, C2, C3, C4, C5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<7>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list7_c<
              T, C0, C1, C2, C3, C4, C5, C6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<8>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list8_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<9>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list9_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<10>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list10_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<11>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list11_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<12>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list12_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<13>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list13_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<14>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list14_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<15>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list15_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<16>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list16_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<17>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list17_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<18>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list18_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<19>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list19_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<20>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list20_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< long C >
struct is_list_c_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_list_c_arg<LONG_MAX>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      long C1, long C2, long C3, long C4, long C5, long C6, long C7, long C8
    , long C9, long C10, long C11, long C12, long C13, long C14, long C15
    , long C16, long C17, long C18, long C19, long C20
    >
struct list_c_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_list_c_arg<C1>::value + is_list_c_arg<C2>::value 
        + is_list_c_arg<C3>::value + is_list_c_arg<C4>::value 
        + is_list_c_arg<C5>::value + is_list_c_arg<C6>::value 
        + is_list_c_arg<C7>::value + is_list_c_arg<C8>::value 
        + is_list_c_arg<C9>::value + is_list_c_arg<C10>::value 
        + is_list_c_arg<C11>::value + is_list_c_arg<C12>::value 
        + is_list_c_arg<C13>::value + is_list_c_arg<C14>::value 
        + is_list_c_arg<C15>::value + is_list_c_arg<C16>::value 
        + is_list_c_arg<C17>::value + is_list_c_arg<C18>::value 
        + is_list_c_arg<C19>::value + is_list_c_arg<C20>::value
        );

};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct list_c_impl
{
    typedef aux::list_c_count_args<
          C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        > arg_num_;

    typedef typename aux::list_c_chooser< arg_num_::value >
        ::template result_< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18,C19 >::type type;
};

} // namespace aux

template<
      typename T, long C0 = LONG_MAX, long C1 = LONG_MAX, long C2 = LONG_MAX
    , long C3 = LONG_MAX, long C4 = LONG_MAX, long C5 = LONG_MAX
    , long C6 = LONG_MAX, long C7 = LONG_MAX, long C8 = LONG_MAX
    , long C9 = LONG_MAX, long C10 = LONG_MAX, long C11 = LONG_MAX
    , long C12 = LONG_MAX, long C13 = LONG_MAX, long C14 = LONG_MAX
    , long C15 = LONG_MAX, long C16 = LONG_MAX, long C17 = LONG_MAX
    , long C18 = LONG_MAX, long C19 = LONG_MAX
    >
struct list_c
    : aux::list_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type
{
    typedef typename aux::list_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type type;
};

}}


/* list_c.hpp
AdM9HU0qBLIuTSfsE7/89fXz6JknzSHFl0EXx3frMxE82Wkfv/z1Ne2eJbavok96Xnkv9f52TdmIhuWARDveWnQ9oSPCaE3wiKTUDzS2Jk1H0lUsgP2FACiH2aVEtpsYTZQJd9uu6DRO+qSEW1JeFqmaim7Uw5IL0/pLQTC2CMmXfFv4LiIz/xSHh7DKe1qs0dQgCyFsnq9h4zDP+nUZY+3qTHuTkuqQ5XpiO/wHFlL0+m075s1ZvnUp0z5gwniwxQipgMDrtaOOzz0AosVkt/Fyqeu2m1EX6SvVmfBKHsk/zhzcHuqHNqR/8uMjKEsYxbmsIzeqa0qW6poJUX7LsJVtL79M8bYB2Q5ZdzK90dyOtyuvxtizUfYbnaLqX6cs5dZshj6R1FmEM3jq8Pc24B83+HkQ0hsFgY/Q/4DcJjsyGS086/U80HWH1UrXRt7l5E0Zx6zV2AnmjOI1ptnlpQqrEloozvdcIVBde2OxOwOgNDiQwOQo6B67/NZfC8wPDDJT9aRM75bI9UrThYYyoy/egS3JarE9ChiCu+Zm7uffEaSG4ugl16FVzkNa963M7rLK8Dz+lDjIQg+JT4HrY/uAwlH+TP4zRSqUVSyTyeR1K3ttK9cSLQv63a7m/p5FnUDqLSyyVPZ5lSi6NY0TixqGyFkbD2ZbY2gmuu/OSPa64FQURYm0I80I3qZ9zztr4bZzRY3x1vrQ6lBT
*/