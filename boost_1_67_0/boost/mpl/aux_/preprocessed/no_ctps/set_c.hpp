
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct set_c_chooser;

}

namespace aux {

template<>
struct set_c_chooser<0>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set0_c<
              T
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<1>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set1_c<
              T, C0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<2>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set2_c<
              T, C0, C1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<3>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set3_c<
              T, C0, C1, C2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<4>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set4_c<
              T, C0, C1, C2, C3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<5>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set5_c<
              T, C0, C1, C2, C3, C4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<6>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set6_c<
              T, C0, C1, C2, C3, C4, C5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<7>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set7_c<
              T, C0, C1, C2, C3, C4, C5, C6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<8>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set8_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<9>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set9_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<10>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set10_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<11>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set11_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<12>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set12_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<13>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set13_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<14>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set14_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<15>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set15_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<16>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set16_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<17>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set17_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<18>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set18_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<19>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set19_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_c_chooser<20>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename set20_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< long C >
struct is_set_c_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_set_c_arg<LONG_MAX>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      long C1, long C2, long C3, long C4, long C5, long C6, long C7, long C8
    , long C9, long C10, long C11, long C12, long C13, long C14, long C15
    , long C16, long C17, long C18, long C19, long C20
    >
struct set_c_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_set_c_arg<C1>::value + is_set_c_arg<C2>::value 
        + is_set_c_arg<C3>::value + is_set_c_arg<C4>::value 
        + is_set_c_arg<C5>::value + is_set_c_arg<C6>::value 
        + is_set_c_arg<C7>::value + is_set_c_arg<C8>::value 
        + is_set_c_arg<C9>::value + is_set_c_arg<C10>::value 
        + is_set_c_arg<C11>::value + is_set_c_arg<C12>::value 
        + is_set_c_arg<C13>::value + is_set_c_arg<C14>::value 
        + is_set_c_arg<C15>::value + is_set_c_arg<C16>::value 
        + is_set_c_arg<C17>::value + is_set_c_arg<C18>::value 
        + is_set_c_arg<C19>::value + is_set_c_arg<C20>::value
        );

};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct set_c_impl
{
    typedef aux::set_c_count_args<
          C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        > arg_num_;

    typedef typename aux::set_c_chooser< arg_num_::value >
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
struct set_c
    : aux::set_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type
{
    typedef typename aux::set_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type type;
};

}}


/* set_c.hpp
+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
*/