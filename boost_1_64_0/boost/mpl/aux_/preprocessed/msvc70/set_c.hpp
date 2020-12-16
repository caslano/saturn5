
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
R4Zlz/uHel65N9lnsOm9yNlDTKfDhppOLx1meg/DXeqmrTxjv4b8lMQV+IrSzjrCet30YUM3aSzPfeei7fVx62fmva7p2fe6Hllnc1s/51mon2kW6mc91hNdyFj2k3z/Q/2UeTcwbyqfFfJXvwND6qfZvKmFjPXi5QCr9cI4XoIff5dyUKbd/E2n7/tb7pfgIQ368+W4MyfzuBOUY9vm6JfQ6Qkfd26pt6H6+Ko6nuYcQ8F0uz5Qb1fZ7vMtbNdDFrZrEcpiCZdJhraIYAvbSuarzTxxROUY4BCc92MAMWt9thRaJRbgHmL92BXPunRFjOvrI/PJvcoc60uxtD6pMw2DzY4HIWb9v0aZTq8dbfn4kCL3/VfI8WFZ5vEh3GId+lscH6zWrTzUo9hcHh+6k4H4osZ9vsCY7O16Q73PyzZpEGm631YZYzp9Z4zl+8zHpV9CS34bnsEmyDkQNxdybgPpT5LjHKhIHsre0n1m9TmOf2b+pWwXWCirDPX5kJRVKuWUXMx4XytOSbuq/JVtHCllpc57qtxjr1jQmHcHfJX12UfnzLv0O3nsvEudUfXFkOOPKq9x6rxKvlLI06HixnyNi5Z8qcogOCRnPkupyjM0IruO+EdbrgMBJeTdKHJfqRNxMWlJnGShHOibkpf74Op8l7DyHCtlpfQtMfl9SZM0ORFtlPURlyjb5iULaRobSGfRqFy9x9t8+6jLIV36Arxmy3y4EJcyn1uOdZr2XXF43N+znP1Vcp5TyDFlmYW6cYkFpZDmX6i37pNN33NVw7g8V8jZp0DqQ79plutDpNzb7yH1wZMYz/p1MyyUAzt0XurDzMfoe5Ik9+udmbcCOmA0yxlhTA8J8RkZ7BsVbLjMk7S45rG/Ww2WOTAku+9JFMv30PvSmcL62O2SVpPf2nB2uMzfiSksY7Aue/wfvbFfgPTTlvnZgR3lN/91k21sOo4QV7GGba5X+jw8w/cK4CzVuYX5/i/fGy/bW12eGbKH3JT+8J/jONYdNye7PMMYFu9JluejyistF+W1wkJ5XTIrr2TK6pa9sbxOxjxeeS0hk0pYZWcsr1hczbqnz88qL34dpLikvFrksrwy+/CtNCufElKGHqgun/6y798lT3tJ3Uhlv4iVfKnOI7wlH5nzpjNvMJ8tkHlVec4xb4nSxuXWWJA9b6qV5bYobVxurGrea1aWGyDLrbYwe97jVpYbJ8udp5o33XS5/1PjFvTvrHwe61drwHPlQ/u+eCm+7TWfToMeb9wCysPYhiVtW0ny+/lAKmGcDeMC4GtYC1dhT1yNA3EthmACTsU3cA6uw7W4AbfjRtyFm/AwbsbLuAVv4lZ8gNvwIW5HW9KzAyvhTqyNb2FD3IOtcC8OxH3oi2/jKPwAI/EIjsejGIfJmIgf4SE8ju/hCVTKo7yNtIdJO1kSjiCWsMl6ByflQV3DsrgAG+BCbIWvYheMxwH4OobgChyDK3EersZluBZ3YAIewPX4AW5GBxKxDWviDmyEO7EdJqIH7kJv3I2BuAdn4V5chftwI76N+3G/sh58B9/HA3gBD+JVPIQ38UO8j8fwIR7HygUpJ6yFJ7E+nsImeBo98Az2xrM4CM/hdvwMD+EFPI9peBsv4u/4OdpSxl9gSbyEpfFLZb34FVbHdGyEl7EXXsFBeBV98BoG4rc4Ca/jLLyB8/EWfok/4Y+YgYWVfjvojLexPt7BZngX2+Mv2AmfLUT9x9Loj2UwFB1Qj+XxGD6HF7AS3sLKeB+roD3HgapYG52wEVbDJuiM7bEmdsHnsSfWwVCsi+OxHs7H+rgEG+AqbIw/4gv4JzbHYtTjFlgdW2JrbIU9sDX2xTYYgm0=
*/