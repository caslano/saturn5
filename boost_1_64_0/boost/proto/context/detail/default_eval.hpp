#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/default_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFAULT_EVAL_SHIFTED(Z, M, DATA)                                            \
        BOOST_PROTO_DEFAULT_EVAL(Z, BOOST_PP_ADD(M, 2), DATA)                                       \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/default_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file default_eval.hpp
    /// Contains specializations of the default_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (3, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/default_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFAULT_EVAL_SHIFTED

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, N>
    {
        typedef
            typename proto::detail::result_of_fixup<
                BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 0, Expr)
            >::type
        function_type;

        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFAULT_EVAL_TYPE, Expr))
            >::type
        result_type;

        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }

    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)(
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFAULT_EVAL, expr)
            );
        }

        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, expr))) ->*
                BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)
            )(BOOST_PP_ENUM(BOOST_PP_SUB(N, 2), BOOST_PROTO_DEFAULT_EVAL_SHIFTED, expr));
        }
    };

    #undef N

#endif

/* default_eval.hpp
9/YroX0bV6Z8d+FbNh/QVxF89199VSoHsWdtk9xnfN3vujqlk12Oa3egef01xjywPLs9R+mW5pfXpPQzuxdyH3jidT1KNw3lX+Wmzt//BiEfNlLLRsykWRTG6u438mUMRMFZ7Nw758HDjtWNQ34cTmfO+9pf+eZUZsZswGFgBGyC21A5buIy5+s5fjueR1YoDqIgtPXpd+BlZvOvfifKt9YSzj6Kfbu9Qzzftdc2k7Xl2XeOy+3ZT8XresphW8bm2bBzfuyfdmSSby+fnMfpo64MzQezFnYZHsLeXVw+jX8I2ObXNOP1rhO8rLU/Y30/dPc4f3uL/m8slTmf193Dl+MLwOf/4Z4+n4dg8nP1fQL5dv/AF/Z0Q0bpZgaF5RLa9ybF86erCu1zup1jtAchwCDsizYCJMuV3B4+nOFn35B3A1SYnag2EZieG1Te1t1jefljeV02bZ51Amhr7god7hmrH45l6yInE9XGcydUNgr+i3ckj9c2xTf+2BsiDOm2o9eHTNA3dRUeq909n9eXtUKVTdeluo7q85qRlZ2d85CTWBMEi5f7yg/H7+Bdr7WUAh9y4j+LcpEfT64rDXWViRM+uio/6nBsMe3reFdcR9EXSaEzga0nlhnex8sN9H4qkzarTRWbWzF3bMlu7D7H6Y7idgiJtpBi+xGndj2um3a6tGjsMtxv86TrmtRUMjTZIo50CUdtCvR9zFfpgu9esHJ2Y0+w7zb3EV53lyRFUmW52FpZ2/b6L++7grLRO0da5XWmZ+vuEzUQNYsnce2IthAl5Oth6DW3oY5tWuL73/DGeI5mSV5mfaGEcSayHDiaYGzfcPx5UcyfpCBZnOxdDZpcZGt1iLdVZmLA/SSvFKwrzm6OMWwwS+nCi3DaF6JOxkW2dP8h/xt/7+TtvguFndClTijWEJ3h8fy5PspG7wGkD6HSJWkZqLyrPe7bavQNa6hzVNV24tyJI3f2WMqpu/ehLB9HKNg6SNJ2HSR6sQJS64l7HQXpZLrOtT6eBm9nVlC8/DbXCcVoI4FtzSoD4ORN17mtC+zv62Z1PyzC9XhK1B7ctWUPFX+Be5LxKzjow3Iez4941AS2Iqu2yoVci3jMTq9g53jtvdH+L1nUdzYwP8Z8O3d2jh974j6219iNkHXK2Thf2tgNI3V5FzKvtzW9Ykg33Vi2ThOg9bF5QxnbTFcolLnuDJ/VtSmfG8/wcYVY7NZzsY00mNFRd97ZYT7jk7CNdmeRgUV6hPv24i0xJvhQF20psYkn8fiaXXwT+Oku0jkmwfru+N28b8RmdBfUqez7bpDO9I4riXcdzQ8343uZSrqqb0EzDggjAU3qbOEmcz6r8jRXfTYTLwmjxu3peFs/xXloUdMzZY679Oktiu2FoWKzyuP0cppB1GmGtV/1wu0gMdXcWup0JG+OdRFDnqVJX/j2kpIX7fUrit4Ip/Ezfhn1ORdV3aQU7HzsIuxadrjij711aLfXR9g/UvRDq4ay+vfMY8zMAT+DOffH6zn5JhZvHJ7enwkjj/ALx+U34rD59EuO6aU6Ke/TDXQvs+mXMriJyf18msOnpMMnpF3GYUqycpcd0+i8CmmXM9iW2DJD2lVMufuklXbtQR6l0X2w0vze9lvEBr/aHF8yyHNn11En2/mehxhSH5xgLGVFK7uicbKQkWRJeQCHW7OZSgVkcgAJ4shVHbdlvfSH4n15GJoibXsl+rN7/w4zzuv1Z2I5o6/bFhJnSX49Jp7VFLp3089HvChFsuGXOK95BXGlrftagBwrwcqG3l/7QxOdV1JVlaoK34e4Xv9O4NacjOgTkTVNNwwZzXuzRZD7g5NImb5uKaKrRZtUw4A=
*/