
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