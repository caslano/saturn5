
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
FhfGTPX9ooS0eGs7RDejXOumGKzvTvdpZFkuRcaDzLu2rc3ndZa2iSGxKbSGpv1kamSExBGqardYk88n5DN5hkgs8r576asflzhmXErslEjV9lSPA5Aln8eS6vF5rzrvsFSyj1LaY09mlrXdKBcftOWnj0BauGkdmbKfMi+vHTkbeKLkq8w7qsyTOC3fS5f3ZbCDhljuQW1XvdtC+bxT4hkn8WZb8jKYy7lB2rrTPjgyOSw1MVnm50oMpj1Bxt6sKe1AH2d5y9FhmX89Lz5zlSl/rzN/pcxXvm/ejiFJkckhpu+o24n+6mzOy7K+M7JcamJqWBwrtXz3sMyPD5tkHUPhcin26bLkzU64om9ee/pd8l3ugqRI+1Pr9yM4Br7Ax/rn9Ye4IGM6UHemI8CS51VZD/OteV4lv1DW0YR1/K5ax2apX74r5TXXe4asOynJHIc6lu2s50FW8NCQvNhjZLuxFyVERpvnHZB5EbHRsWizjgusoyfzTgzNO/+tttSrfFf9zhJ/aTv+GuWojK9iM+I+OkJ9DtCeeszng1n3OB9cD8l/PohunP98oL53ejVv/zF9XqB598st6zGSbD6O5LO6ji/IOiiv7Zgdsm2ydY5pabus3k/kXTLW4yhEfe/0uswPD0thcTk2NcdhTdneesfVbfk9sB4/so4z8u4abhNGJsuxk37XY0fOUzrHnWn/ZH9wZht7KWOLjs7bJzIt5yv53lHlvhXfm8vna6rvnZDvjVPtO5b1+vH9zsx3Cc37fpZsD/mtKdC7ZfTvLRXfvUP9e5b27ynq38ss/Lgk+vca7bdN1r+nWPg273/2vUb9e4f2731eNt1TbLJwTuX21ZuPjw3KvnT0bO+phb9necN0j0r+jsW2cg+pLFI809RX7vH1x+o4AD1xIHrhINW9wmxZz0c69wqHyHqCZD3D0QVHYmsche1xNHbGEIzFMEzGCFyKkbgeo3AvxuCbGIsXkeNP2mDK35yYKfGo22B6STyt0BnbYG1siw3QG9ugD3bA9jgYO2AQdsJQ7Ixj0Q9T8TGcgV1xIfrjcuyGOzAA/4bd8Rj2xBPYS/VO/dye6u1h+079HaWIG19EL9yJN/B6Ofk7U/7+ZDnTduC8YprmSnmfkPLOw4dxPjbEhWjERdgOl2AnXIrdcBn2wQwcjE/iCFyOYbgSY/ApTMTVOAGfwem4DufjelyBz+HLuAH34fNSH5tlO27DXNyOpSjLC1gXd2Aj3Ilu+DJ64CvYHnehH+7GbrgX++M+HI2vYQTux5l4AOfi33AJvoFn8RhewlP4HZ7Bn/FdLMV56D2sgeewMZ7HLngBu+NF7ImXcQB+iMPwIxyNn2A0/gPn4Kf4HH6Gb+DneAWv4z/wK7yJ32AldogcdMNvsRneRC/8Jw7G2zgff8YGHP+/YHv8FXvgHXwK/8BNqLSZ31YGcB+WwmNYGk9iWcxCB7yIFfAqVsSfsBLeQSd8gBPIg+iAVfBBrIY1sDoa0RnbYG30x4cxDOtgNNbFOKyPqeiGU7ExzkV3zMAmuB6b4g5sgQfRE4+gN76DvngVO+KX2AlLcWx0Rhf0w7rYBd0wAD2wO7bBnjgIe+Eo7I2x2AfHY19Mx364CfvjNhyIu3AQvorD8AgOxzM4An/AkfgbBqNLec6H2AJHYysMxcEYhmEYjvEYgWkYiRkYhVsxGl/EWNyPY/FNHIdnMA7fx3j8EidieQeeLWFlnIzuOAWb4zRsjzPRD2fhKJyNsfg4rsA5uBnn4k58AnfjPHwd5+NhXIBHcCGewUX4JS7GHFyKD1TgvIPlcDU2xmfQE9fgCFyLIbgOw/BZnIfrcTFuxLW4CTPxeXwXN+NPuAU=
*/