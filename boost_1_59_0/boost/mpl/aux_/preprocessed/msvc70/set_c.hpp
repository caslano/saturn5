
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