
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
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
*/