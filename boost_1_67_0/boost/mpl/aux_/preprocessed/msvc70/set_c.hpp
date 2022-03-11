
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