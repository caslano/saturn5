
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/deque.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct deque_chooser;

}

namespace aux {

template<>
struct deque_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef vector0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_deque_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_deque_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct deque_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_deque_arg<T1>::value + is_deque_arg<T2>::value 
        + is_deque_arg<T3>::value + is_deque_arg<T4>::value 
        + is_deque_arg<T5>::value + is_deque_arg<T6>::value 
        + is_deque_arg<T7>::value + is_deque_arg<T8>::value 
        + is_deque_arg<T9>::value + is_deque_arg<T10>::value 
        + is_deque_arg<T11>::value + is_deque_arg<T12>::value 
        + is_deque_arg<T13>::value + is_deque_arg<T14>::value 
        + is_deque_arg<T15>::value + is_deque_arg<T16>::value 
        + is_deque_arg<T17>::value + is_deque_arg<T18>::value 
        + is_deque_arg<T19>::value + is_deque_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct deque_impl
{
    typedef aux::deque_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::deque_chooser< arg_num_::value >
        ::template result_< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

} // namespace aux

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct deque
    : aux::deque_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::deque_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* deque.hpp
3eWJfeVHQFSUUz+nDjENuNrQJ6aBUnGfifAwXjy9g7L20RYfoBU8mkBmwaPi+1jmBNRE/cRFevDEeKLZYsCDUuXXUCFad1q7meUsmSly/pnwg9ihPa2wGDUEx1dtdFA1g72YyS4R0bIX3u3LueZHoXQxELcyrpKcwER+6yGc1I3GtD34Ees7IEnWeNzKN1ZSI8DlsBD9nQZY3U+033plr73PN5teYXgitOzKbpBKMEA4ZIlFUDJPPpfOr2LzFzBkCnD5CmBMSRB9uq1F/i6jWDVKqhKkz9pLKpLWkOgeEysS8JW1KukPG1Po77kqyYtfnRQ06P6YUb1EAhI8mfCn0sbqZBVL9oXeZQkA+zR6Pr0oJxdTyeiw9tYVGmBFAcTnBIrPc//ZimbusDg7QPnCpxOb/4QylegY21hY5X/7dEXVRPzS8Qrg3SeaZoJiUZ8cLiQRlMEdCfvH/Pbt1CbdgDK4YNg5kcIb9O2bZnvZwLiXtaWGLyQXh5m0uFWfVG/NtpM5TRepmkKO+D08R7wEX1W1Qg9IYJwqnAdS3kJVhBYSFDs4v2AwgvicsIf5bRvySGbZ+/MqD9j1m7w8ABbTTmQC7Z7/QANqa/sxX4L4EtaJSuQFgoHfqgqjZnofsQy6aZLYzSjJdjd9k9+j5/dcArgMWibTEVLMW+F9Cfzdrs9OxJQlBZBakJMKKUsYSGVyUhl/iPW3s3ZHEkiNw4wSTRmLu+Z6wcR0pxwG0WHmxfV5x4z7n5RHu2OgAXuNqkCDe/3eEuIzo2jMt1bQ2tCZnpL8JzxZKIZ5BBgBmsSCTk+1Wz3TVt7AKwqd5saG+g5CUWWvFdTtEBO09TDBV9k8FhAkgU1Na+Vn6VbMtBUjtFIdu+oF6KYn3VYttOVJbwEWY5NZ8hr6T8w+Ml+ba5+zIW2GhdWrHtahVWe66gTupwEOuqFps4du40kGpNi6auovdIEy/vljKCfEguEtlrTlR1SR1ljmx4bQXW+0B3374RqOvhsZkgvXgTQRwQ2Z+bHzNwDVBIlpjWWh0noF9WBbrNVCd78fvPxYCojWhimewKbSY4MmtMDAQG5550Mqt8BCVyUXkFKaLUb+D0B71VULlC96j8XUv8ZiugtpJQgu5BYOkoyV4grqVte4wUnqzY+SW9llGxYC/ZZYYj1FUtPlGRPKM3UW0/2FxDQTEE9hl22MIordkllzEaBMxo0v58Mwil9GVDEKgzCdZAmqlaWRPhDq3GT02EDfadArUTBlQTAtkCOxm9pwc89XlIWBiej3Esd8oNyNqggHmkolpPJb8TQf+JTZQ06HPjAOz0B92Ju0BSXDS4FU0z9QfOxlBEPoQyNzkDkousYk00tW1xgUIhcAIx1i7eH1MhKcStb6tmQioHHshS8/R0bxq+NGsvB34vWAbVBsBGs+SMITXgMguHVUYn9PF1tNrSiMKY/twAWMhIs4xqxdIKohbKol04IapsOprM9k0+OtUVhnADRHQvSaeHEZImpaKVbPl2s1FdzfxXpE71js/LYTP9cpP3qcerBuNtzUO1On810Iz75Z2pW6YQMQnOGZ8IZ56L7iMsmAXkE0il4O35IEusrQ75zwJXH+DlhBnfeNIEBv0QB6IRp3BAM9/C+Ckukpai7tGqy8MoS9noiKDqNkoKkAczTYcCggxnrHyAxrmDK0XwBDC0mmgOb4uUYytAEI/r1GWY+tC6PIDW5kuoGMMB320yCATsB8iK4kXgA08k+2S+tTV3qNfKvXAOp5UxPOH79nDr/HzLcAFizp077zBqW9p3Hz7lDoQ/NWI7+nGojmKiCj72QSnZBSDURzVUFOKqRUAxldBWT0HcZrmMxgQO7E6RWS3p/BmIgPmKnC1A/CosbZqQcyWpxLRul+nlvbz5N+yB4tUoZ+goFIuGUASNyaWQzIhItyeCZdf4IhTUtAXOuWTD+uqVW++VP4YgYCFUGRwKVg3Pifq5Go0flvAhxxR4OeSCiqRIPx96I90XfjQ7HznYDqygM/Ube2vEbKNK0JIpipl2+Vmom+/QrGkYQlBsye3/7HAsSRBpZ0WOkeCYosovCC+jLa97FUvhik0ZQ1CpgIfS234xuDRxq7pfKb8QXEUSjfJZUvom8ugN8R617RsYsB4eCY9SPyDvEWk/hE/6X9th7/+1xgnN8RkgxvcVQEGIWVoSVQdcQxgnpEVQEurU7oCBF2Y8KX0SzR8DXR8Rxx7BKFl3HLbgzFCexJAlbkE0FpHYjUV54IHIRn5oDo2FZ5ZTt1J9iG92j6QD0oAOXRYSTLOOJ7zv4xrK8DxNdmPWB9R3R1kz7SzbdCQjfu2ZqlhdsJ8KoDt4rex0XHa6LrUdHVxm+9FHemw0xQ8qSYoOh6UhSesKVIu+gbFH2K6IuhnZPvsOiLiD7qJQctGG7xnyzgt22Ep74PRVdw4qhkcoquZ7T4JXP5Pe1MgrSTfYcUfxfH7+nWo8/DUdJ+SKEvMeIYOfQh2cfvOah3DRJ3Ej7QC72Z/Eh24QFamBZVUo4g8H8BRIDXAsENN9CW9MKY2hQtncz+1KC243iNfp0A0oJrXRgkrif1IDMJA4wQ0wMtECKMcFiPamcvE4b6GO8TKUcbL+LFdqArtoMTJ4AO+vZTzdSAL0hBhMTECTIa+hN3ntdA/036fcW6JsgYwy8wCQj4o8T1uOiFGW2DHi8g3u4q0ftoYHwDColSlZ6c/Oh5qFmq+x1LvI/iVC5hrQJING2S6aGNR1KOl4ljG3F18gEZWDYDCS+I+NYGb6vpiXdHev+mSeU3qMUgoyxjI32lkzzHA7pIibYdEg0OF0R7VL6DznubLaXISEvTjHQNcM01x5ot64CProNn9BBd2l+G2zrrokr8vXgPYF3qoi17d+hi91jW4Z7Hke2AostR/1kBCs8K4Lh18Ftn7UYx2xg5AQl3Yi0gNFTSU8E1lg3qTic8rQN5M3ochH54XitDm4ioLnNfgkpWsDRLjIyAlodkAupYhSi/wrJC7QA2fjs07m+2VOpJt/cG6DO6ti+3hnAPhps4KsJLusJKvlWVG9UqaX0Y1eAOQLft76taVinMXpNlEVljKSGHQC2BEtYuqKQO24aGncPooLlEMj0tGX5hCz5KcG9uUejPRjT9IEetx4gdVFRgtFDV/e/B5yWS4WFgs+lipORVyA+p+UOQX0eaLauoYMic9rihlbXKQgQnFXKt5ZY7YDhrMb8GCGeXx6nMhVxZFahiW6ivfSB9MDlrFadEIwHdAUMvt5Tzrd0q8wVhxSmVPMIHytRdokqc0Up/ApB4M65xmByQFEE/ojvKAMC+00xXBlQmNN6uBBrPhDe/S1UijJkDpTYWLvP3nF5CupoYqUIfCLZ8UcTRlGHUh0o6IE+18h3skiasQy4l/9CfOu+RwHjLfFLL0glbYSlHeQWNGxblfLAK/pzwUZX38KT+B+t988jLdNPWeO1vdbXA7t0evFUbO/+Fl/AiTJOlTnqShgQAsJikZksJOpePHoc3i3raSAMw9cC/C2UthI8iq+ELZIx50COr0QvgpQn+muGvTsYgCHuhonvkwnko7r4nq4EIIAPrL48PQcKT6upeoVgw4gPwrWLqITsWogGHeqSXaagEEKRXQbfWQcnSWCkHP5V4tFr4gooRTq2TxZbq6hrlaBxvu5nwEKmTra6BbxeSXowLoZQOYDgjqkGYIsAuERoaWkFrMo0/AE9adejzG95WOTEQBcDIMgmjO6Ez92iQmBx6OfytoDBbQ+G0TR3bfFh82rjvgdcmeNVG3ax8KT5t1POyR70OGirFHV111AuyR70oZ9SDMo7anDXqO+moFyq3HkNmb5pcD3g/I9u/wJoz+JcQ8LqnUzl6Dch842Hh5XXlT+tEb5vopX6iva9JjpdBNrfva7qYPMiRvhrlma+hGS3uYhChTbniJpQDX5MF3MCPt8y3HbS/zW/bX4CeqHipE68vCm1yeQEnwV8ktMTfbpZBV33Nvq/5HeozDy+gU0EgqhBHm7oT6EKJUtBUVFsKdfefYI0dvPQI/h7htz2Ev4d46QH4lcuLromtKTJSJZYnX4ekfoGTXd0yWxTZH2sq4iIdkb2gibki0f2xFUVmSJqHJg/xHiDbrt50wA0BCmj3/WGx1/eqotQkTZ0hWnWA0VfJQmRq1vBWFKxBGh6eLYNUMDjcIfpG+0HWRdCAONKmbu4v4QNL0OjhuGTaJBdWAsIwB6MKcxDAh4pJbPhCNZW4YiDt7VdtHuw+jpca8bP9sWDM2x15NzK2uH6El76Pt+PrFV76Ft6d8Q0iILhIT8xSBA/zYncWcfG98GSGhPiH8RPRgXQylIGSTWy0A5heJ3pp4KlDboN9AzSFbk5RR+n1P2DUAW+MRTuxK5FxEELb5YL4m/AcOzYg9yPMHBT4dxYZIXEw3hMNwb8fQ+1GoAr1T0R7iOMJuR7kkyfF2cTxjAgimvCceCtHHIPiLSAW7BZvNYq3mABMACN6JBH1CzHzUhV6ALo03La8j0TZpcgR0BAN9AGRHJpNCSO3+LvMsGhgPWx7E4QAOYormZo1yCC1tmmr2t6VY5E9ze02VhpDs4jh3XJkeBc89cN7BFuUI6o5I30+mvWORzGR6S7SVPy7I9vZQV1e/DuBYRaEEaetv1qsH5kaWQU9fDjF+tGc8At0ZwIQEy2MnlPdvysjxbj1ZBDrkzQXs7rxUnP9oFivKG8XU38fetv44vpRfnsxXYE2IJLDbPQ4rK+P+G3bcc5dRvt6mP+H9PROOkhDdTM5yTBTnYBH0CYkdhunWgi5YtXqk3c5zJN/xBxbxsl6ENqB/hnjH/YLuyZtdEBRRsMUSXguI92krVMETvnC5ynqI0Wz0ObRDTy5lY3VLeaYA2prDSoRTLfurZKXcMS1P/IuNHzUMSrr063unwwtAZonbdXRndMqtumuVp4vxlahSdxtqPCHzXbvKL/t+GlcMehv+ya0eVlcP4heJgckVzdAMm3xdESbB8A8tIQZANI46eFVXXWL64P4IdBOnKC0Hc3kh5344Wv0w3wmNHQ15iyszP7WuisenzRJ2zUt4lJbJuKSrR8jFlJiDnwU/urgD6NyrBCftASpmICERuXaGCiK8nBgXMAcgWfZP8pY8EI1UoveqexaiJTWcg/IUpWS4X65eK/EAnkBVreKg59meRUeqa4AoXU0wwQLNcg32zsy9W3Q06B+yqpPrk8VZdTD04WKZws95gQ+DdkLlVu20EPHEtoo7rLdAw3jAJQzNPiB7W8YAO7bnaG+f/oU9SFgKaBpr7Q6KUPPD+SyM9X5xlaYysmKQfpcBZO5Bv7Wwt+d8HcH8Zq6ttC51avBWxbS4C0lOdRDbR3PvoGFgSByh6yFQ6pTwhMoXGC4oWp0YAIgqKExRr58KoWxCwdUVaCZfEWloPOwD1DrDGfqHaCnYbVpzYlKZXr1TRYg29TlmW+HU6WXC2JZ9pYD2Ys798oTpZmK05aqBnU8NwhRFQtUHAlqtejaJfpGcgMbuQwZ8ghqfUTV5JXWz6HjomS/MEK8I6RLdu3eKQsWa3ukpw84usE/YpRdFqCGjvmyazAWjAylzRQNsutluvJUWcDSAwxBeNnWHxvyd4K+CbR3QWwvVBU7BWQ2GP+jLOyOtkcG5frHY/9HFooj78XfRtUx+lb8RLwzug9kZ+rlLP6hKrSi1Sfae9on+O0jVJDapdkmoardBe1rr6pxKCQOz9bOt6BRyJZeN+HZ5e+p+eNTqhGkakZ6D/0X7T+VEwfR+M+kkwMmag6qGRn24J6THECvZrGPo/vjPd5VcmC+VgJ7FRsCjt+v0uey6N606WiJHCdCpxxD22phd7wzPgxi1vsxr4WS6KF+oTPLQrNn6AgQe5Wly0eRFMN/lKVKr+NpKJDvrM4DZcru+KKDOB5qqUk7FuuRhS3R49DzfWhHuU0WHofnvfDsei7WDYDfF+2MvBXXbLzj71JzzXhItd7QqzFJsHGlbxMQFteTse89B7WA1LijLpVuCTlK7JcUDD2xbz2u7N6EYRc1GcU7W6NXwXgo5hjUehWCksLLAIt0qevlKEIogLUi41RBQ4MbI3B48Y/AhTIA2qOjABKejAlad1xPTvYl/h724mq1F31Te9GOi/aM/fiifBT7EaEz9eT0bjRkdWP4BjnSLyyA1R1vzxiUPFADfFvoxO9Bqcqd2b3pGF2orQic5ApqaFJdW6N86SKgE4KhDE1S6xfYQZTdthw9S6VAeI7agAPjSkizUl+s6fNEiEiOIKBrjkmqhtWLfQPITiP04nSanQrGLEwX0pj+5oX0Fj6VDlHKX/xDtuVroGhYO+ieQL8ocEw/Bv5YyvGt76DZZ2sXc4hx9VYzHcxSY41TafVZdRWgett/yDa/kzGdjVHTWexjWIid2XR2gJrORs5oOptjL4r3TQsHXnpal4mIrgE6wz/wvFKVaNCpDHRuDx71d84/03n+udSnx/ru+oT6PmN5hMoKAqeuL5UEIt+nwufzeGPE3WzVZdh/WTOVBlAAaEoLAGeVXxTrOcobHzyYI28cfPDs8gYvvZhxnKU8n/vtz9Lf5nZVOUNXbzrXrpY8mAWZax/MQIZ2lXZzqugxXZzpvu7vJ3qs+HN+0ePlv/y3ix4ZfzFuj63/DTMA1Tb+KF7e0jnxjmLTMYrAc/1dQK/Chs2n0aHl+mONDbbg6vqOxgbSsVq11wJkKJw8fG5bd2+BTvn9RutZfE6LgYHtf02RKPmLLJi0myEZMs5vKWVQRdGMC/mAnUFGkCG+/JYraALG0VFuQjZfUoqbrTBa/xvFMAqd+LoC1fOBXu16ZYgeuEumIHNQen0EssKBGPxLj/deH4SnzSdLn9TpWkrSJdkzH+Dj9Rv6NTCKLd9B2SSh1kEkbBTGQx6bB52QApiYPmIHclfB7STdhKZaw6FEAdoK7Jz4mAoyTkIBUuskR0iXcht1tIxt+DuLq9XrbYQOKTNEvfcLoDdiYyokf4xN1tRmmuvD0y9asoAPdKBaqTb/qUwUMJLhpJVCN4MuHZie6lqP8vwPrbp0DnGzfGsvg6ZDzMGau3W1St/9kCvR/lSwkFwNsFeNCdQT0ZpqpyRthWzlf/81nvJQR50VbL5CT2Chh6BQLQ3plr/QLixUD4W0m0cvMaC+Sjsw+e4C6fdt8Cvu6MV/A4fpvxH84DUDyogmYI8BbAUgj4BV+1VN3qmh8VG2IjjToJw0uoD6/a9jXbqm60gAq5Z2tNHldFhbTnnvBr0eoZ9cQCT8JPvOlzoIHKPSdDqeUgdOHSZ/i75uVV+B/uPrlEBQ+d0jP7ZeNWtD01nTUATKq9azpqH9SbwVqN4vIJUsKeXole1KDzlJevnWPqn4Z+gBjz6afia68EA9ENxQJ7GSTvOyIQoJ0TEGXNI2Hgi2zAeh4VHiYZmvEoeB7tdL7EtOyfRijfKQ16pjfoiLwB/mUg7OGyHCmLU+ca1gSDmSG1+fpEOqvf0oGqx5oMENPpBSJPY06ba+Hfq4oNrpVl69Br1Yfx3qwjP2lgWE3a5ZlEkPpEgte2XCftI3W0u69cpepC+m7UuYoL27+RDWVv51DLFj0s4jq1i0NGMrxaqk9y94GwAIHAudEt3JjQ83Nkxl
*/