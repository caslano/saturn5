
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