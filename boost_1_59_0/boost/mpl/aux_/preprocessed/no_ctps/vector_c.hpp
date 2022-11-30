
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