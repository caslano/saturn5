
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