#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/deep_copy.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFINE_DEEP_COPY_TYPE(Z, N, DATA)                                           \
        typename deep_copy_impl<                                                                    \
            typename remove_reference<                                                              \
                typename Expr::BOOST_PP_CAT(proto_child, N)                                         \
            >::type::proto_derived_expr                                                             \
        >::result_type                                                                              \
        /**/

    #define BOOST_PROTO_DEFINE_DEEP_COPY_FUN(Z, N, DATA)                                            \
        proto::deep_copy(e.proto_base().BOOST_PP_CAT(child, N))                                     \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/deep_copy.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file deep_copy.hpp
    /// Replace all nodes stored by reference by nodes stored by value.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/deep_copy.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_DEEP_COPY_FUN
    #undef BOOST_PROTO_DEFINE_DEEP_COPY_TYPE

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr>
    struct deep_copy_impl<Expr, N>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , BOOST_PP_CAT(list, N)<
                    BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY_TYPE, ~)
                >
            >::type
        expr_type;

        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;

        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY_FUN, ~)
            };

            return proto_generator()(that);
        }
    };

    #undef N

#endif

/* deep_copy.hpp
n4v+aCbAEDQYEWPE76cInHFOcFSTUUp+Bt0nOo67vK/g5YG3dsa7wNzOzHBwLOpntcP+FOK0FbJIW9DiTIq6s9zWozFOfPlohCIhlv3hKZ1asrrlwujYSYpXjuwJ4r6qwBUM4gKGtuoRd8mgnuQ1UuBaFpSoQtNg84HCv1mqQyzXz1I6wjMVDJdNcDimEXf5or0GWjXIPX8o2uNYC3ECjQ/n7B28EnKL1lBf+f6Rvb/0VTBOURkxkaSh+biGP7dLU/rr4Pp9cEGzYcFIyC/WsRcu1d8ivsazViB+lq98J5RuWHnILunVijKo/y5oBCaDFVXlPXtKtea0a6A7h0f5HXn/cJHaE/L5UtCSrFEQdVNI5hLyk2mWwaEtRzmPdIFvmKtaq6Wp5mM8JSRUjHce2cRFu/3PjNqgQ+OUbAkJfLTy3Thm81cpLq+ZccFUtp/l3Fl29axGc7Ct+CMuyEvUh/OXRRsgt4sOvOodzgsHlu38XVDld/4PlG8TulNe91IinXgUxc4kStNCNZeWID3rrvlAObZ9cNJ3KtJaW/NrMMvQy/W5nm03srror1Kul75oU8WE60RTtS1dL0gFJMYp5pIk5HJuQ0orgArEeFEJMDGfHY1PAjUSZvcjeC8r8dpKNa42XcRzkTVdxMs6VYrnWLBVJbh1EW9txrkts0nP+ZKK8RNMxG3SS97NkF94tDVPwbcRu5wrhi4i/mcLfMUE5IUSmk2mceYS7m5c0zvbgH3lMOPfF9fC4wo/jN6IoLRn16QwIsO73TeLehwzXOvWOcPkKLj02fGgJYyc4dg34TcFnZbNnNhbX2c6p5O08pDIaC+tfLC8B7TspK37kPARK1kKZAupYdwznXuP6HSqamwT0FWD3KkQthqSQm4XTGXOsU/pXLahbmxt2xgnv93YiEZPkast9U49heeSqQjPve3/fcVADE6Y9PCPtI4LWgrOlUqJ7j/3YXX2HlGMxweK8YCASMJ6WXHGY2KObTink4USrMgddOci92vO30XprPbBGAN+PcGvb+R8oAb5taL9nIF+3vdB/XdjcXKF8rI/H81nsMG2vQrFnXU+g3DF4fr6EKGjatbZIOOoSpbnMzICF+P2iOd8xI1xcVPq0Rj9AFOGThjxH9lAeii3hKrvrUEeGxcpNI1ul8Maz7IC3zAOHplettnPLkr0SGW+3bfHe+5NBQ0JOcGcgvfFDbQbjHhIg/i6ZZ33XQofkRCCaWwckSPypqDwPPvQaH+GlnMVbMwhGQ1KIv30yH0aFw/UuL1f7M/hzv/iqM3SV1o10tM202lE/BwnguJ75prGmC508anpADpZ8grkPvtp2f6IWGtp2zxdeMXicNFZo3T+VtBxLDTa+2DFIiFwxwRqYPkw3GUG/eo+XPJRVlexSYEjndj/k2vJwkbulfRtAvbIv8r21v5JG0r3mBPqV9meOh4MYEML37INtG4cRBqOd/kKwuf8UM47LhN8zgUF2pVYsJmyc2LZTYcycMPWItJKbcJcnIgCuov0/eb4fT22odp40pqcp5AB3cUc5hYUF4sJ7Vvm8rbSbsC7FcWLhZJ3sWbs+5C/E1J+9prrjVyGOTw31p60Hkdyo5VrpL7bIp52Me2nm3/HvJ2grd2QT90Y4O84jAsU5PG9E8LrgcadM6x2tI93mX1/cgVTOvQBc3/C4GEzsSzlAMXxwlIcm3vN6fVa6I2YrycCeUFw753obsQpWd+sGknbcl9sd1xi9Pv9cttTAfbz/vOcoxvt8O3B8zyuQj41f3toGler3UDzYfANNV+E5jUJVlRPW8+wFxIsDIZcI7AX0/e4Jge6D0/fcMwy7CPSd0vX7uo8Tncl5Br6sfw=
*/