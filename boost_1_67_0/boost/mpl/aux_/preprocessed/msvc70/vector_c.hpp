
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