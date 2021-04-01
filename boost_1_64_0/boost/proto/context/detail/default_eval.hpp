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
UjbDjDhcy0WgoG2R8Krr+BzkJsrwBSl3bgxNlSQtuEIZbvP88dthCC+ni5omv7s95JdNXEgCBZxD8QfjKCA4a9ErdPAqwwJC6FZLrASwfB72C7H5Iy0OpIHXTg/90hXMR8NHMYVRPoQ8a8FWpFXrl8OZWhLD9ovNZw4sE7tnXy6DppkVH3y9/5YMXUE4MFmytKMQACw7VYnrZco4L5c4GmDKRUfC6VujM6Wz6KqoU5B+awZibpkwUyZVl/aSm7gyjRmi+81qqq//JaS9FFActUgEVFH+cZQxHaZgw1iMQTbiJjaE9CdXMBoNrnEBHC4/J9ZLkCUg6FdQmHqrjpVSpSFYkmr13wzECZcQRJPeTMzGDBgvKYLQ9bV+Zaai0UWawbM/IsZXi0DIFqTHovVSEIOXoj1AWIu/P8Hv085Z7OeSkp/zvyk+NEo7e/+L/6JsZsWBeVWhOduLpNNitq4TZFYdm+jy2+5dEYsdyuP7kEffC7gy2ZiC2ta8XuzBHb2PqCJ9G3LKstKg4X0RHMKRSKcZ0Bd7LYgwTraA2TVK4SSOqW7hZjlFD4vu8w==
*/