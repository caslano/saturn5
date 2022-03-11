
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