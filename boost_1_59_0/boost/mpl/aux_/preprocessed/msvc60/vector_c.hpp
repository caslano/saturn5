
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct vector_c_chooser;

}

namespace aux {

template<>
struct vector_c_chooser<0>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector0_c<
              T
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<1>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector1_c<
              T, T(C0)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<2>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector2_c<
              T, T(C0), T(C1)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<3>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector3_c<
              T, T(C0), T(C1), T(C2)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<4>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector4_c<
              T, T(C0), T(C1), T(C2), T(C3)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<5>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector5_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<6>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector6_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<7>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector7_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<8>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector8_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<9>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector9_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<10>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector10_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<11>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector11_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<12>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector12_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<13>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector13_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<14>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector14_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<15>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector15_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<16>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector16_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<17>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector17_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<18>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector18_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<19>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector19_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct vector_c_chooser<20>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename vector20_c<
              T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18), T(C19)
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< long C >
struct is_vector_c_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_vector_c_arg<LONG_MAX>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      long C1, long C2, long C3, long C4, long C5, long C6, long C7, long C8
    , long C9, long C10, long C11, long C12, long C13, long C14, long C15
    , long C16, long C17, long C18, long C19, long C20
    >
struct vector_c_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_vector_c_arg<C1>::value + is_vector_c_arg<C2>::value 
        + is_vector_c_arg<C3>::value + is_vector_c_arg<C4>::value 
        + is_vector_c_arg<C5>::value + is_vector_c_arg<C6>::value 
        + is_vector_c_arg<C7>::value + is_vector_c_arg<C8>::value 
        + is_vector_c_arg<C9>::value + is_vector_c_arg<C10>::value 
        + is_vector_c_arg<C11>::value + is_vector_c_arg<C12>::value 
        + is_vector_c_arg<C13>::value + is_vector_c_arg<C14>::value 
        + is_vector_c_arg<C15>::value + is_vector_c_arg<C16>::value 
        + is_vector_c_arg<C17>::value + is_vector_c_arg<C18>::value 
        + is_vector_c_arg<C19>::value + is_vector_c_arg<C20>::value
        );

};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct vector_c_impl
{
    typedef aux::vector_c_count_args<
          C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        > arg_num_;

    typedef typename aux::vector_c_chooser< arg_num_::value >
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
struct vector_c
    : aux::vector_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type
{
    typedef typename aux::vector_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type type;
};

}}


/* vector_c.hpp
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
*/