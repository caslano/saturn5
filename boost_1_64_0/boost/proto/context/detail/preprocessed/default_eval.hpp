    ///////////////////////////////////////////////////////////////////////////////
    /// \file default_eval.hpp
    /// Contains specializations of the default_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 3>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 4>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 5>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 4>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 6>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 4>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 5>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 7>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 4>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 5>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 6>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 8>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 4>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 5>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 6>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 7>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context) , proto::eval(proto::child_c< 7>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context) , proto::eval(proto::child_c< 7>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 9>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 4>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 5>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 6>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 7>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 8>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context) , proto::eval(proto::child_c< 7>( expr), context) , proto::eval(proto::child_c< 8>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context) , proto::eval(proto::child_c< 7>( expr), context) , proto::eval(proto::child_c< 8>( expr), context));
        }
    };
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, 10>
    {
        typedef
            typename proto::detail::result_of_fixup<
                typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 0>::type >::type , Context >::type
            >::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 1>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 2>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 3>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 4>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 5>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 6>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 7>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 8>::type >::type , Context >::type , typename proto::result_of::eval< typename remove_reference< typename proto::result_of::child_c< Expr, 9>::type >::type , Context >::type)
            >::type
        result_type;
        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context) , proto::eval(proto::child_c< 7>( expr), context) , proto::eval(proto::child_c< 8>( expr), context) , proto::eval(proto::child_c< 9>( expr), context)
            );
        }
        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (proto::eval(proto::child_c< 1>( expr), context))) ->*
                proto::eval(proto::child_c< 0>( expr), context)
            )(proto::eval(proto::child_c< 2>( expr), context) , proto::eval(proto::child_c< 3>( expr), context) , proto::eval(proto::child_c< 4>( expr), context) , proto::eval(proto::child_c< 5>( expr), context) , proto::eval(proto::child_c< 6>( expr), context) , proto::eval(proto::child_c< 7>( expr), context) , proto::eval(proto::child_c< 8>( expr), context) , proto::eval(proto::child_c< 9>( expr), context));
        }
    };

/* default_eval.hpp
tf+RD7yw4ajAj5M8/v2lQX9MnmW2KRuKbTp+ZQmPzXM097/O6VqB4XKVaQyRBRLmw/k9TnPS5E3ZWspgzDPy8n3iR0AT7b1tqbusMZGufnMblYp4Gvg1O5yTfxuMf4O5mCsYf7jDu8XSD7e/7kaDOB6yjObkFwfxvCrd5lWCa3gb2nR+hJsVergOIjuhuoHrYYqIj8JEu2mikhzPFbiOelUk9woiPSLns/nFwRglpc1NmYt2TO9eVZgmkhxsTw5itr+A8zGilGUF27gSYObj1ZfBBybYtL42qh+D6hZJnetSwEtft4CvQauDDo3iFrA86p+O2wDzQyaVMXi7ntKGkI/h9w8f6JOKruhaU/sYbZT3JI4/ARJU/J6uE1OmOvdkXT0Zz+2yLw3626Y5/NtMvh9Nn5R8LinOS8qxLs4myhzIi08G+HYLFNc44pMIlTcq7cr6v3yTWn8Me5OiO/9zOM+TWeXCQMAkP78zkdvgJdGYKNHVddelhVjbGOG2tA/iapQVwucPj+gwkUaedGWRsP47+YrtYE5P4nw9huv8yxG/Fvi1Es7XbBgfj7HzOuGhrPZTzqsRBUaoqE0i8DqycWYfvN7jun/P8XUNZ0uXpJkqxYO39/sXoxU0+wmnMog0tPHA/YHbIN37y/H3NI3ssrqrQYBDbNi1Ym/BMMdOTPjhP4Lz0ka0oEuvmioTDzyHYsHj49b55qzvOvnjcbxdH+C8VCO0KtNaJaVYAjeU9Z7PY1zYgRX4crhswV13E2URGLLoveDXES/UARutmiQT2faue+4JtHuO/eMgwQ4wcswFk4UOf4XzSkVXJKVB+6PyrOsh9Qi+9wn47yiyJP6Ob/T+YDm/EzavQT9ZJ2L5fLCf2vLvZhFup2UqTWsBd+WCx/Xx4zjufJo1stVZIUhxNREbaJPjn7RZXhTov+bzmvAY+3tfiecr7N9Fm/b+hXEN9/VxG4Emsp1Ky7aWOhcYdJotEnIS397yS27T2+VEfcp103Rdply1vKGEf3nUp8aYooSWOnw+wD4eXoRf26zNW1s6fD/IfI5yfNli7oXamrzq45QcdQ4J2+OzZMQCBvT7CrISFckf0bxCu39ry7TF2GYW5en1fmLRdNrehLRezulgHm4NUfyUa301ltebLsu62mhB2wG8DJDB9uQKD/vMfMQHYxOVtlRdKcw2e8qAbu70LYRLU2/2uL+D+wN7w3kY5zWfw8doClsLFkGnF/MzQ3EY90iWPge0UUx5qUEOtCDTrm/srnmTSKA7DUxKmjdbKenuI/pSZLVq2rauxSDMhN9vWQyriuYe56Fa0SUJSIjG9pfPyRsUlPDbkWDf+jsRLytqk9kMxFTGiy2DISsoFuHt5dDX+JyVZWFA4MzdTYoGMqO3zq/F41CnOumSJhH3d5F+mMeuu9ug176svW7BUPufG8slhc6yrG46r6fA858FtO9fu4a2OuE8e+7g7aIobC6BcWyLfSBHHkv1aGTrq4XtYNV3pcX3PhfzdDLQLDHmc38p4oP24ZW1NZw/ZZ+ti9kgrQ7VMzCQXG6+OLA/rrq8bfO69fNv04VZhy72yh3msC5mVjKSYSI+SpgErT2ygvh4V+ApnMRM4PP1aB40wKfJVNY1xGc0tNVHTwsWrwJtiW56mN6Q2RNyn1f8wg3gLfMTBEP5Cex4et/la43Lx89mY7ufmx8mu3TQmufa9JpH4ONg1yaYs0nqy8luHPRxAArlZDtukcAiwfX78huOy9NkSRYe90bEo1ALMwz3pq68U3rRl91iXIaGOKGuW2IZ6gXhB6e/lbOHv39ahbLbjstQsgZ4X3a7cVl7/2apfEDS3F8vLyjD+3JH4g9q1sU=
*/