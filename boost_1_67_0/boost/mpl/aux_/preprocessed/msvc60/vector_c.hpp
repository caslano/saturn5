
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
jGbYAP0p6BMH8txu//MVecLGXJ5BPgc7eG0R6IdJvicuMRC59FMkpX7XaTp1/NVS9pfiZwP5L0igYovFaUa2yENR/6th2xFsJ8/nE2Fc64Dld195ba/5r1y7UywmtzgSfe5OK7rQt2oRy7LyyWRdmeLCpsE3bDsPdOQbkf9T7NhYt6bew7guBA49NsRf8TwaBigmHq0C9hrLla66wvelIRcZtX5d+JpCCn6yW4xlroP26nU+u1+Jn2AfyC6hJu0Svtz7WQxp2OFNW/xafMhG8vjnADGLgWl14xtJpnbsAZHSRJayRASLNu2cw9aKtR62LMe4x5y4q3Sryfx1NmODGRpCgvKSf7M0GfkD9mLljsjRqWXe/cVM8POt9e5X043MIKwkK4/989r2Hh+jrNQ0eSQAYUQBB81+eFXbSz7gRCaKR4uwXa57vh9Epq1lZLng9ftAz0pukEf510HkHVoCnLAHc+rN3v0gLXvA2Bpj2pen4xqxpnrqNes/b8sTTrEoCXPxExQ6hl0/htoaSzppJMreU1/lDcRfmwUHoaUSsb/Mdov2sTBp4fH2jyOm1NUa6PUCTA0kl/mQTmaXIwSau5FSp+DsWE781gQ/c/znOjke32dOH4Fdl1fdq5tCc4K29b2rm7aegAbwfvuLJXFgaGXAMEj4TBPOk1m/6CPb1/PSnJeEaue3oLviLbpqry2xiczCf0mQXQKDLpn28/HiGRh/JJdvnUHT4ET50022WzBwZYEwE1HCcUIFtZI+GEAGMsSmzKctTDLGC0ajBASY05dq4K7ZpIWQbrCqHMtnV5m9cGh8lSZe0dsPzHLpUQyRPYnRk+p6bUzMaU/HJUbf2+K3QYa/qQxtSfBNv+BG8oqD+Rk9CXz/g4fnaMbwzYDnKFSfKVMRKWVidiwNtgFc9NlWDhSbW5mkq/w50XGwAPAp7S/NeTbVVwzU8+XHK/1xeDb39WyZXMNzZ0XBrPgMaomxzIfXZfH7M3suVZitCJ+quVi2G/CKxULJ/B/nc9ld5euMAevzyXUYCpmYd+Ihr4/YjpBjJEl+yV95MH2Cs7mb4lt/a2rZnOboJ4RNzhtdoyQ0N1A3yqBmwcPVZes2scadW/c93wt4L+6Z4xV7/RrcFPAk8nzsEmLfExKkTB/AFa1xJ4JNu2TMWR7MZME6F3i1dCQ+P3TipR0QILRHg3Po/m6tmScVQGcVyFqM5L9Q99V4d+hFKtQ+yxWLiLFp6mt0IYy+Cor6xO7C5rS0eaYPfhdHP5QL+ZrDePjsn7Gi6A9BEJor+VCkggX5B/x4B0BdMAsD1h4+jp1z/xPiuz9NEIID5bHF9Ql33hP9s9oPE0D4XNv9eWhIcmjKCyU0RAEBlEAQjK/KKk/gJuQoJyZPOLpkgKCFsIUZ0EmifwV17iRtAVrjR0L147rYlNd2KqYL2if9c5H4se8krq6RnInz/9XGwjYRT4jkewM4A4VSM0DdrW+nOyxMwS7R9Z4kGIIHpa9Wb0gD8f4Kg4GZd4WOsGX0hAFDLza6GN3cxbnVVI1TCt+dG2cCQ3+7vynJhJFMj6LKbfGbiOjqAlK/l/8uCo9dm8AiKnOEjgcz9bTwgVRwJ18RGMzpzoc7S4RuRJBNOfC7ODGPo8ZxizVzoMYivmbP48Khbj8tohUptGqMs0V2bsemoYFRWYthtzh3TeVoPI2Tp94T1hdAWjP7QXhnlxlszCLPv8ME44XsNQczb/sycapL4gVa15G5j55vzyIAPxRJgSWTMz/0h5Que07Y6QgMOZdZHCHuPFKjWWXLIcAbx9t988jm0KHfvFNnUsfjAZBb99ss1UY0y3Aihu7GbMNu0hYQWlwVLCXGCa7M1Wj+tiHS5dLotfEZ1bORpHMcZ+kk3GsXVYSu/9ghPZi2YyhNZOozn3yqnvD8wMzGOxaQs3Fbar1u5+yKhfiCbHCAvVRLbfWBXv/R6o89Hmq3d6tz/MbFcg6ZXC3WOj8d/NfcjctzbYJtE8ubSg0n3vT39FUAjAd6OilIm+9VyJyzI0owJACSITZgFBAsAx2vJFJ+/HHtsaSgeNktW2kpFp0xZKtj9Fc8Nr41m2/fLWETw5mYOJ6dK/Jeqvxe6vDwXip6+Q/sQB36VcAqkQs/hGaKMkFu4O9MVj0mFQt2DDu7eXq7za2j2525xR4Hh/i3sKVqnVTq5j2q5Wh5DRkC5OvfTZUG7crMFQ5j7fBp0Vstt/3R0HiysRpFdvvm4LfANqV780QkKhDsXXVQoLkujW9wDEonDsIX2J129WjeQunMnsrhx/oaVKA01YuQhh9Ks7fOsv4vXxMoLjjG2IMIPSzx1LCsfkz5h3diJ0Wo13FdsY9LAU/fGIA85Cia0vY63hDRQbVrMnthZ1xgOtHHyog1bHUF+4zmrOj1GpOyCf3ltkSUbx8qvt2y9hZZfT3c1CtLb8DAvvgd+BoQ4qkfKzpAOGvAHj5qybjc60yjlBW5y/wDey16Y0cEvPiCCRQmcX6nxetFHfwKdefBWzxvDLr7dRAdPU/WrxcjCa4Kxjn6I8B0LthwRvvA07SY46N4wJHyjdC27Lk4+RnTbam3Vtv34owr8jSUIQ0V/eGQb5GkcWsvqBjH6FWjWevW1FX+pUOGJBd28cvi8Y07+++DmP+P4mfVwB8lBg7XIogumDK2FRxOGihlsDNMu9eYOLcBmmQDa/3sZI8Kan8z1B5YcUk9h8JfSvsiPwOzGa7xw9JiStMoCMcBwlBMe/Gva+SEP+fWFWN6DYyLNm7CxIn18m2TrrI5LaZZYxU5WfwHevppQ3vZ7qjaNcOXIZOFt1A2ZbOtAtb/GkjWc0YizEUpsn0RwJBcEbSyT9EjDbCwRIEgb4TsW2486UJix15gLhrhwD6yxn4+0KmOwX7K7FtCBvZhGmrPRTsqH2JIT2/p7o6awleH4wTj2BqJTebqF0lIHJzXuhqYTt+IyOdWWBeIrDtCB2ZPBQret+O+b6kBnZtXbA+jQIxsgU9HXoQeRtPGIEelazgOWrK5Rblnuv1XS7DFGh5PiWw66nkr9LMldrwbcMJ2+fHnnMQy9bJ0g7UeXtZaIkn0pr+hykg2PVKMmlxZtjtjq2OQKwjL9b2bH6aW0KF7ww82K+72i7YGAQYX5pmQY49XTGdmzLQEbT7qgZKKLk44/yC7zpRoNfNsKPI6UbLmdNT+DCM6aR2VAhC/ZH9Ttj/9MjIHsy1bM9trajaK3Zxr97ZPvErGU+W7hfTHPIvwlr+P48T6KlJ+pta6APCcdQl7Nhi8SsZy7Q/auE9BwoHY5vpXs68dGVBrldMyK385bLAVVYrvDi6TUajMPf9otYK+kBInXLqkBGieg5CBfV0eFYd3X/izfssoVyzWBK9BEQj8MBdPr7+S747v8eD4he6Q1zKfzHlbDjKGnuvFNY2dCw/lFPWP4dzjyg/FpOM4/CONP4qHOKsV1i+vGNI2HU0rqfHfefjwtwQWxeiWSvnkmB8onaRgInwv3ry3OsuQRgiqBMLWgAl6n70F+sibshdPj8rgae/ycOeBuE/4ZqkeNPT6DM+r15Dhs7o4OBwhItNM973cZylLi90X1tJ+BzKsP8ItrjZofxU7UGvwOb0PM1UHiD0GhmnO4v0ch3e02/c5UqNlCOREINZn7ZhRFEFSbS4AXcN7A527NkQEkDHOC94WTQX7Z/kbkwRVoQD1GjOTza0s7UEO9OXTzm756q7QSOV6Il5fpBFpDs7wqauEjSC+eGjvbc4jvDNIr19/AGDkcCXufq/IORVRKWcSgP5BHhCUXUnrJTcyQ3kX1ywupPbuZykZFAizDgRf63FOoul2YDPSTaAPyXiIuQ3qVU1n/lL/euWRN+xAj/UMnd45YAfynysK5FwXEi7GvF4PBBhDP+3lYgEqQywkUNw4JZkuNn15zOD/xILlMhEOn6ca5UOtSd0pJ/R5ws+GPlRwLX3hvP0NTA44MhS/ssI8SfiPbld4UXvyjvmXTdzyLCKH0yaFuBm3qhvnwejII6qfY7fW3711ZOOYf74Fq03Eq4B8JlWa1r49jwRYk3tzHE2IfJiKT11Xxjot4/nTz4SV9rVpA7BGJyQbyCyyQekQAuTUeGm5FKNuKEnpOzM4ZPyRXQri39fpcRdhsgr6syIqdj3n4dh1LTWTWewUhmDiWZCjbs1dRzhxBEdOkfLBh5TcOjZiqSfPrM0r9FUtHFR7i0b1PP1z+4HWrrf8e8YGyoyhQ6UrWg8aZEBfvvZbG+C2lLVgyS4aHSJYW3Rc7dsLYQfIhe+ampwRe+NFi+lJkPYd8dgxxK0We5AVmuB2k2goD916Y6w9WuvSYmfp170Ser9c4vrlmr6ndC37MmKzJ47NS+FJmn1WH4H5ebxGPtHF2CZfNsVSCWVjBjbwljFS3xsJeGuf9CUfOhUYKQK0gKjh+xMrTOYBrwtHUXnFS+rhzP4ihqh43D0b0TbxgUInJQadbrf0TNxdebmIU1HMDG3kkfkHytFlwfVRouIzcXJwjA81I2VfEbkuZyv0JyXAvMEafwdytQedpdnebdgoyoOxoi3n9U/fQzefeF+473SLVLuhoK4j/Jw3mh9VX9zj7YoPKJjhUchHHVCaPV8wKSwHfRBWm/YcmcNhOLNdutmxkZjZzaDd51MdaieoCq1IomW/MfWsvFkbe5bUZsXqJ7lTheotvIxYhF3znOzvSkRHucLGww1CnpLLlUBxPYrQfhjmeP/H+U6qEdChE/D2TiiKynFRrVnw535DBhJSl+EdNTRwmBJasStgAjXgiNP6D4nhS1ixHGfgWoYGdeVRBc+iMGiavszEyImgf8C63aFRS5cn7K7B50N/Mq+YxGB2yBKmpHXBktVQN47jPOm5wjz3Xve3+wDFvutTHLZscOZrKd3TqIosFxxcrxO62h3XT9DVySdAODNbweZtetuFKJposIlvGboHi5WPwG8+xNEy9e9urnbZDXu9LtULrex6+7SM1fiLV+bkRIMjuajP3u8vVcxNS8vk6bcA5sNkCR7CkofCfj9fuL2B+AK6lCQ3ZbaWmZZUf2S/x0FPk1Q/A8j7UtkwwgCyT7tgm4j82S9lTAkhX36tt8GDy1kXv1m5qD6l8vnkc9bfAqnrcyc0T1uIT8Np/zlrzxFxaeqgFFWS6PR1pscf/qPkBc6yCX5kQn5RDiiq3KlTu4im8ql1je6BteN0sNqE5MARYelTIun/OiJe4A3yME4WB1L89Wc1JOWSxhloxdafMHICf6cN16RB4oZv8Gd/sXANaigj/pEItvcBbsQwoAkXA5shTaIf2lxhCJm/OCj5owVcDoKp/kC6KpiOqFLzi56udDOrfqsu5UHXZqxkjdwmdEpgbxWu+R2aLduwYDBTgzRz1rE6SJYS+zXfgWNknOcg/s+edynhwsfh2XnKxwgIYSF5KdM95uF0jfZ6EoY7dUAtyFQxPdrPkOte5eFVVQiO9Esn5cSYfECw1M6ZRkDBiGjg/NC4UwEGx+jYptKujsg1Ru5tvMJRMV328qt4KoR6s/Lpuio2DSA6pGyxRXES4qPHhgXFLjxAxwhMlkrTL9rnS1vgHheIrrwYgaxBxy7GX+43sFcw1m0cWQqson1eSye91mY1mHpC6+HC3mEWK9BU1Lqqkbh/rgj/b0PKiDurcgwWS+qypwPWQjvzZ+C5uZbs3xe41KGAtw+TnYAHbp1IRZ4wcRek3/a6thTtBVCBD7IbeMGKHHj8146kwOIhNqL3NPdyWTOa+wbxvW4aMemNKDSXxJt+8VDkk1P+BFhQP0IVrFa/XuHxMHy/RuulWVUUYKFm+lJX6lyZIh4LATVRnvpA6KtHfFb3pyWH8vgwjUCgM1zYbwrVgBZjJInMX9BId4Xg2NPugX97hrNU3teNC6UVeBTq3g45Dv4xWYc/OwSpgsvxH68+LkLna2Y/5IMLvNhfgaZBhf6Gynn1GsT6T+tcMv4xREUCVE+/j5AHldbpdSaWCYz7oeLX7KyVyZnZI/ByIFNG9zNpq1wLIoFymCtdDkpAP8/mdNA5bjF/LYYioWlq+SeTanIO9B2HNn/uyJL80/KsIHCs+sQxwDrZWvBdpnFOCTTN8MB5Qn+WHUHh3/jIER/IjOnKj/8EKOjfk1G8rZdbqMcRV8ixqnOZoxuVRThltsfrGDmh1QtPm/xE6HnyjmjJHTHFq6bwAUVdfDKnxqm9pg0MQmoQpfMYhGbELLwD1GBheX/d+ZVXUP6HRzCJ39P3O8v8tiDNZPkhn0k7/5WQkfXi0Vr4Cuwglmn6dXMWPi4rrlcOJoD4jtnuxz9mJhqXatbMq8VsVtOHTEjxD6ItxCOpVfCXiphscozBnNCro/0PQR3JJ6ReG0el5lWD4JpWemJkrBQyKBVN0miGcLz0/Tpnl0b0sJ+OG4XPo6EmrJk3dOFgXpLnfoG0a+N0COr+DhpdCdmVSUqTyOwTOPDd/2mNtPaKh1F9fjWiOCHe64+AUv/7ghj8j9sd1HY8ejNYu1pKIg9+7ih7/NgPaVpcr4xCz2AsLSk/brookopQBVdqZnjGlsucMgM/mLDl6I7aAx4DYeTW9HuRGukhCqFkw7QDaooMzu3UKZ7OZYi2UqaLLv9BmuTYBqQikWQ6LOCjgVlrWt+yb6Jw7gwnoAHPoxXEQU9/A6SnfpY4G6rW/UkrPDZLhQT897x+21/+dOZSK7l9NUJAPZXqzhfO+UfoPa6aPcWSCQDlhpRRrDXZzoQaeaeTQZ3StdGssFgBdCRM2i/g1Gw0/vpp2P7p2C16ijMQvfdjioQGG0P3CdMhcPc6/ag4Al8qX5/6Zcna6Gdq/G3/+oPAq9YVe+EmCxZD0uDBMmz4m7Fkwk1ydqIqkzWpSICrrmLiW4UC5mAr1MN/KDFAdEuK90BAgp/+2dQrLHhZ2SBI1giGv5caLnQl3F/G6AvhDoTG/Yp6RCyIiKB0b3HWrob3UgbRBTcDKUr7B9jasHbxo5N3iJ53qClk0WnOO5TXNWQ1k/5v5sRr6hyBtqM/sdleh7yF0WHT56PovSBEWGQbZMivS8ZLTB6/MaB3upNdviBJ49RhvUfr2BScBq7R889GF15eEeJ77IVkdvMlcDd6/FJYQFKlBZNlqhpN1y+kmqoBmzMfawD51Cugu+VZscVy1MXFysxF8F9YE7AZy8G44aGGvT7QeT+94PGzcqwehPj2nEsa8MuWMgBzH7tV5l+6xT9JEZH2XNfKKKwNefiMw7Nyhl0U/2Eh/SlewK9/SgqjgeQJdfnvDEWiFKePkhW605gG8NQPTqa38i6ydSKybAtJh+LbeeIhOQ2GPtLKX/6BzRIxdk5IZNrCLY0TB44z6kcgbu3hsaiBXDx7TCv/An01szhLhR86mvA/2uQWnkJO4oqUgLPShzOnLzeQ4lc2b6BYDB7kJyoeHME4JoFCrrRF0t2MXDd09wDDJonFIKAOGNIPRE8svMdEl0/DCA6DKrZVnYINkHAO0gE2PONDVcjG145EvyvnnW1QYKDxDwDVW172IuAd5YJ6iMhq7N1yAVrEU7vQov7GKFkyHZEbdv7xPzzJYBc58C+QrTxwP7nm9gOtz5WXu+z31KVF5LBQC94nAYuWuVFC8kImgZ5/XLVI7tXg/G8af0yuxnpIfcGzAHm3OSjiaf7epciUTp2sRgSRv4j/dXxfHTj2JPj4uI/E8DJQIh72qO5rvvAgBManEeshxD7xwv5Z2tYAoS0T3fotE59V5iH6OAh0SnNButC+KOvHJosR/ONq4Dlu+yW175L3a4X7M4EHMypJtApDTqse23TWYHW/bf2sZhMhbIG1SrB1/X7EbaJKalgZjyD15hZ48XKvhvDnmj3hwYLkPWcUKSx9YnxF6ACPHT4/MsP7uGzH0gAhnRzjfL6sOH7Pxv7jznO2OMdHxEEOkelaNOrZ07kjXDc+PL0GrPd5DfzTdrY9/uPjJk+OAapabDjPzfeIlWxmpLVzv5GUP2snK6QHPD9RfinJZqutoweGUSiBoWuzz8OOfvRVYHoXUvVMqYoTfsyljIz+kTFBSAR5td77JafJTY4h9ylP26d6cL5OotUt3X66Rai8yrZpvsqZgegdqqWWIXTlpxIL56aVLIkuvrxSK5opZAUkMkZRkHUe+aBguAqyew0ii2t9UCxzlSaL1ClAsdazriVHx4Xb0dHCRKqhX5bLEqeyuTW3k1N/fhqIv4/MXZNkQzbtvoKQ9Q/zmSz/7+tDi76tEaZ42okzbr3YckVBJImxOLQyZ5+F8AbrIU4UvyOJqBeV8M8fcMzgqeroJOAUesIjqcpEXCiiwrBaaFhKGVCRcnoQMIgZ3RJDRgN1rAnVRcY//ikEqq/sqOv7I32tC0nn97n3qcbfqK6Uz/GUvoV0PrrEPqL1PLpAJytDTBov6yiNu747XgozQmBeOyRLMnKcSsXNDpe5/ToYJGV9FNh6R7R1lffOpfR+zqJx7KG4VZDe1ZMmUpMhOOpcJQeeCpR7nSfkG78GN3LhVK81+NGlu8589PJwaVb8xeapQb60IgxYcOlQr8IQmjsRSvvDjdvPc8ada4rY3gOZixI1aasGCne6fK8z7IkWWO7PoWvhuZCHkIBmIdIj7yfuXzVwU1N06uI8y3G/bXrpqn3xOY28rp3E2tpScbgdsivszXQ8Dne43VXPwCd1BnYjf6R2xFrslnE8MjbUgV823z58Xf7rXxTk94IcUIFJY9ntC5aL6weYkYJ2490yUm7Aim3J50DajH7x3dKpzOmf594t1aeucqq2XcyaGswmxbKaQ4qEVpnVhIevxZBHG2N+G/xGnAo1a34kjLCL7N9hSBO/kzfCXMY4Q+x87oBAfscY4tkiHyfyz0Rki88fWzww9iRPiKFEAeNEikKUlTRPRun1A4u7sKAIzwr/otxnfs/Jfch7o1L/gj3IbFi7YXVv/NkX/QzKttuNWJPPsfzkTU+PEMbmw8OfjchkATqUsbfHSKtvHryWsfWOYpH30Dq12IRQLfLVvwGcXEGuSSe7mhTzlt1K/Ay6zIKOqb3+N+InHG0BGPljeoZ4S1oU3tdB9rL28AP8YJeNMu9EC9goKO5H7wY1zAiEDy9xG5zMuz/2GWDn9jThT2v1DebRKfok+s6Vfh8+W3vWbw4Ev2p7Mn9xrlm8CPQR8MI5VWs=
*/