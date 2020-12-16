#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/poly_function_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_NORMALIZE_ARG(Z, N, DATA)                                                   \
        static_cast<typename normalize_arg<BOOST_PP_CAT(A, N) const &>                              \
            ::reference>(BOOST_PP_CAT(a, N))                                                        \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/poly_function_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_funop.hpp
    // Contains overloads of poly_function\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/poly_function_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_NORMALIZE_ARG

#else

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
      : Derived::template impl<
            BOOST_PP_ENUM_BINARY_PARAMS(
                N
              , typename normalize_arg<A
              , >::type BOOST_PP_INTERCEPT
            )
        >
    {
        typedef typename result::result_type type;
    };

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    typename result<
        Derived const(
            BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT)
        )
    >::type
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
    {
        result<
            Derived const(
                BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT)
            )
        > impl;

        return impl(BOOST_PP_ENUM(N, BOOST_PROTO_NORMALIZE_ARG, ~));
    }

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* poly_function_funop.hpp
ZsM94nPgzY/p6P4GSUpCcC97bB9HSkPy23lcH+dLdGdsk8cD3c971/ehriyJvsNq2Q5U2r+PkBFmSuv5CxXTvE5xl+9ehXSgdOlyS7/D3x3IM6T7W0Pp01CWD2/gd9+1NM2ft5DmlX5wLH3iaeH74XXb09NrpG43fVageYMkui5sB5pvUuJn4tcjoLnlEWYbGZu/uQLfwRk9KMbNJlOvHxjK8rhxS4d0XreS7hfPAVqL98EdCe0L+0jDcHYkzwOg4QvSAF+qAv2Hz23prnJBRRymS6CfnQLd61FjsWjebAb09rNbHo+G10jefz0ONDf7rzohyMA9ZXf01Rd0dBggXgG168+nvjDQF+p84UVAA6V4bH+y1r3Y057vVUH9ykLo33wJ0r1PDH8gJev6S1u6U1Yauhb1gj+a97teBnQffhBHGtJe8fKOhiVD2j9eCbTp8HmYivB8zWuQhqnIvvr6ljaatxIkDGX98xsi2gz0mCjfL78R6RhmsZtnf3gT0lqzCbBDjdLuvhXp0PqOAaG94G1z2vEhtlAo06/fHmjdTkPSbr2jo/sdi+x772ppMzCuahE+aoXbs2GudWWv3g048IYC37EI3Rx8yHuAfjz2eo5kbuJ3OAoQ/JvfO/8OQ4Z8/+v7/Hc/VMje/n74DrvLwF0inMb0tQO3IhA92kmrN7SRGOlL6PftfyH9hoeB7ll7QKDfnNCBAl0A6YP/rjvG7+ZaJIWQabrsbe0CTBMQLbfHYpTbEXkm5aU447Y2qUnBl/t46i/u0ziihOeHgY44ypaiMmmW6jozeZkx7+xz/3h7F9N6Nxud5Hw/+F+IylKzUmuQGTcMdNGczhqJ7eHLAi0E1xaQ2BE54uPuRPhIyxqheGnzlIXWuODLEHxdwDPt4Sx4kNWzXRoL8EXID31TF5kuUt1E7d125H9ocOKz66Pt3W/aRjyg3z/hfXxd3ZlOtq8bzeB8HvTtzsMZeWFIdWf4Z19/OWZKMG+7AcHQoUd0JG95e6LbB54WQFN0U22CSQV9Zzr1zOu1OF03dsPp6alNsaEbd8dyJ9XLToetlh3PFcoTrFpinnvBb+EdCG6r2oTV0K0RuIgE3K/7uO29sVMVCrh747s4zRfy9PN4EPSobhfT8cBIZ/X9cJ70eWFAZqI39uU7xBjQkI8cLpF2/toSLDVuCDZ9fVw7rFBJG959ujK+r1/G6e7xDJZPJwMOOrk9DLk6dPbxt1uCmR4dYn+0cbxJXb69BE/yHiDfvy3FjabQjoNxe/GEq0fg++fbn4yHmOqI27rDIo74IAv93SzD7U+vdiejlVnwz7QkbyjggbvN+z5YmWGbrizjC5YhhN9Pl9Udrv+HyM7Z0uDb0BIsamyvENysX0Zsy6ORG007nU3vYvn2oBrdabTj+YEeTxBujK5OZmM/fic4t77Qx/m9c4b0G96xR/e2VrPg86CfHlYsnMgi6dY33PP6dRhP58Oxa+NHIE+CAa9RjtlBG+EHbLnwLWCB30GLbW0psQ59DFwt5/Jd0O1dQxzmS3EY2oMMcFqff/TSePsON2hI/q+4wyKGrDuj8H65iMM5jVYYE8T+8XYLWD+3QdvXnzMmWMav3f4E7NWuHb98EsasjLAev1hSPhCJDPdakcp+mCNLcbtD5xgJ4d3+c/uTsdvjw13XSmEdecMClq4jxIf4svxhkPmWQZOYHeT7iP+M73ziLcfBHISaHc0OYRb6EY/t+s1laY68PSKW9xPLMIej0VG86YyD/4Pbn4DHG5j3uTLGOXzTZfyv7IQyfnQJP++Voivji5Zhtr1BBZgDDw/aXhgHO/3/hG/dpYZ+C2Ph23c4Oc18MATsu5byx2UHxGw=
*/