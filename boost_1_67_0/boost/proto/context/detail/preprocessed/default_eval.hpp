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
MX+nHGWdD5KwAvzCPv+UEaN1WSW++SGGnnqUETIEkVDUH1qHFrHiXPleEZWoVryx0ETKmSJgSNlYuD0VWObhu08hyJQJVUwEEZdeZdGLl+obGYN5+5Sx4mdBatxcJ2H5JVVlhMeJTCK6KMsuj8PYtxTCSxtZlmehV55/eAZVNlkfWW8YFsvdBUUp6hA94HRtLBru2jgrM0YIqGgw3TlPbLNm02odfDdLXmkWU/IPo3rY4VNpq5+D6rveeLuJzyHOJZQ/TKKY8dH1wDFU0zniUCAOxUMA5uzuCz5iTJzOoFO/ZjRhodDU+su+JMw75RGJ2tvzDxeUu9UM8RsuAgfAQsdt1dSQG640wf73iYU06JWWBpdF3EZ3Yn4+/Xn3K6KWewlW0qK+eo7LCc8/nkaWLMDNEKA5nb/tRaDaHtrLqh2Uo13cPYXJ2CPivL9AnC74rCLICrvlQjyxyWHJ30nMm6cRZ3m7lOuCUAmfTq8NVUhV3hSx6m8OCFDFoY38q3nZgkFspkdEpcyA7nTWFBpCvSc8a4ERnjXXHRBZvlOsaNVo7q2FuWWVX/3c7vZDvd3IWrQOGvdHpHLC5Nd6ed+JjdN9B9gH8rmTcOrYHi5ZwB/qy39hJ7yOMdR7oUi9S8mm7mUiTlv9bMOfbUa/wLCIv13EG9pgiZTgf4mSumjLcauDgrS4CGfQqqGGD+eGr3xWan9nFbJmnafX9esGMX4FcwGhcfU3YA6ViDmH+goJq0f0oqVwavvurZhAJ01tRRWB7yb5SOC7uCpogm8wDr4CAZGdHK7Swi+OFJQfIS6/2egol8hn3zd8lCN6LjxlnFtOEHFAK29DS39AmwI1u8DbqQS4rebGcQO85XZKrBePQ/hiIbREKWPksHKxtAi7WbKIZ+u7xFk/ZKTihlWtGE8PxK0jGwiCgFiAAwS1U2ymXTfoZ0e8YhLQl0EY5RoMoXJOyE4bhbj1B3COCgxmC6XOx0ZlyQWOop1BGVb5WyoxiH/0fsQPJVERu0D3tfDkzrxy4ORe86icXL28DUfPrYytd4lf3ImgrAeUDJi3mp0sqO5UMuWJoKcoVx3EHxbAfxxLDBdQfXtPGtSKKqxsIVe2XrRABOv6KRkn4TlmJJdeB9OHTGLTIG6RZ5dUArHd2ANMP0nAVRoRfIfFP2djA8Tsqo6AObsBObuM1AFdjJdwAEjz5CwTJ3qxi3eZGAYRvRMnU3ILkjk4IjAHm/YLRHfpP33Ey/iJ6DQDfuzMDzjLAhLV5ledaCQMQGnCyxSLmuba2KgVK2JivLFlZzQVDdNby0yRZ9mAxiXoIW4L6izlOgmnbT4LIuPt+NtkPUI/HYVfm0w2y6zCb8G3kpVGs/Z5DKMjOqdvduXSHBy6DtO9fSZmLS2FbNTY0AZhtq9H7C8lcnNVAz2Jsggozx69Sxwv6TP45NCkM8/M9HR/Ji2Raev/IdM9pZhst8wHFe4XEllXxLPGhXBnZL0MOhArkM/MvXolFuyAN7BBp/3uOKU/8S8xKV5iYrseWGKb/8wSYYmHL98Uw5QmOSdRsMb6eMbn/NxosZ+TJbV4QKpqM9WfzVTf04rAt1qxxmyF8q1WDMyZwzlptzdYD5Im2wEpcra+4laQpD6HVpI9sOTnzZLP+t/713iLbPmxItny+CI06281k61BslWbAQE54fg0vlP03RAQz/Sj/kyzE5l+8X/IdOUtEDa5LYQunrjMhCAUAQhamChlZryUMyAoXkrnrD7GNCtk1ngZbGGM7/Yic1S+p7+vcH63zB/P/IqZuclrZv6eyn/6PZWvN/M/Es//PZVf/l2Vv2FmvrG/ckIaYK+kr+WHxrKv5a9GxU0SCWG5wWY5y4KS+P75NOkJG0F1iIua9gxBjqvuKXqa9izfwqR52nN0q8yZ9jx+pk1bh59Lpr2An1HTXsQPyIsqudfD13XsHnkPSI6Vy3v2VlJqLDFDonOwUVusUCou5h8uY+I1wX8dhG+gsrLKu0yp4sHYSJkPSzy2Q94DnPk4KlkN/mi4JtOiZlauIawnTp11yohrchVl6rMywULLQBihzMrmq0a6xbUrWOHK0KrbYYomlt5MQ7seFIaRNeF5tjD1NDH9NEWr7jPdKa8Gj12Umb/T0+T69VbPXgLM3jxMkMNoIZqCgAGGLSIDo+o9IsauYHkLxNBHXE80MHU+mFA+b1qIb2+o7QikMvF5+INV0mkPq6Jv/bo0NTno0np06ZLkLuXos3IGdEmgS/dGBnbp5Zv+r7uUk9yl8f9Ll26O/H/oEja1zJtAgVfpJXZx/+kk37D41nNj4ht8pJqC4p+BCvQ8nBDS5Iwhzn4DdP7jpwL7FmVYwlt4D5ynXq+vwCZobFjLWyFhxtzEsSFTHjdcAvz5UvyrQ6aX90ZWz0vUk1UwdWT7rxckdQyuHxuvaPqcBmPFw8lqzDClivP9F+T28/2VcBxa/xpa/5+fQXXQrUXYPMebTbyeL1eLtPBTjl+LttIdLQZ9j/bmdhzPj/6CqNHyPtlZMWYC+zpFo8QHz/Qa78CBajAaaaOkZdrTcMvCSmza0zMhrDz/HginnfK7X3sbP0S2QkHi7Xa6T3sgQ/eO01ZgwGJp2tP41Tj2aMFTaIg6uCmC37kYxjdxJ/65BJpMKzDorBH4j/EEIvypzC9er6Te/Zq70BBdBQ+dd2vW6BZYFdytpQNOV8D7CjUJTGlq6iKqrkjRuTTt6anUZM0tn3C+VpUj75sKc9n5tkzmnxpPkamVjJP3ocJ5Wsl4eV/7bq7FYRnkn1TnyyT2UL5bMMkwlhniGRAEhU59FZc03REvf2ajd4i74CnMiZITov7gjhVaguL0Eii03EODHd6eWfAUZkqZabyJX3Mi3n4Bqnvyfvq6XuLW83ferTnCDSmhpX6h/QxqTTRW/zXbzQm1EqcJp64IhiSUQgx2H1vTu1ZC6BqNQKfaX3ngnBHu6BZMbMjalN5MCKBpBea2h+7KCp5GXiW9ckogyx1LrSyhH0L9VIyncelsnYsgsuDXzfQ7u/JRSQZGGh5KFbMuopGIf/8NFshsYjVKcyINVZ/K95pcDJFmvsciiUOIvkM8W8W6hKHs+pOA6heXSFeLbeFNZp8yUimdjv7mHy+4f6IyVg/zWrx/ok5tmD2TsMwO11NbPXsIhLZdSG0JI23BoqnK1caiqWCVX6SRNDMRB+SA/ohROjeRT2kG40oLEpLth5/tTZTgdNXtB7QscuYbdxdc66r7uxUhKN5SMyxRpSglIF417+YV3x2+1jJP/ZSwJHylPYXN5FvGU+fn9MGJD5tcfnxBvKHhu45wGBWqxbUC4Y9FeLxpYHLd071GII6PZlBdeqs8RpqRfIy0++y+hNevFwPIt+R5nHAJfXp39FZLyuzS6ExLih9s4N4AUMYR3dcZvaMipUxzNgli9y1613ecTqlUbHh7NpfrqrsJrAXKPvv7yn4QZfuOwD08DaU2c68dpi/b3YYXQoGo8mCKGEuQT3wisPzPR2KLKG+T06I7iIRoJ6Bxm1g1/7i+lWanLo8gpkBtXzzamHRCjKEWGcoJu8ikmyJaCGr7A58FRdrZ8aGcl79zekFJ9mKbTsSqLNhdSiCSmYSrXXUHQdCGTXhalKMOKlg0wVWXT4MsBl1kWmn9fU0cCkynhZRQerkxFuXAw+etz0H60o7ErL1b9/te+EwM1/RZa4Yai7tRiH8tvyM2bTdtXCED7x7CvBd109q4Xp/T7rm+e9k1d4enXn+Hai3UdW5xQdR+vb/UCE4d0OjzmAqHG0mW4Lz/B8INQ6RepfYMV2N2ySiomqCMKKjpVkcYiyagynue5e/0SpmBJlceITwQDLAOCcGrWPqrPsPTtPSi+App511rIm/etDz2uurW9WFLke8d8li8S8ymJtA0cabonK7Z0O1AgvFAOw/2xcf4LdiQREomKamDfF2x9Nq7ugzqyluW3DPffoS3FkvKwLeGceot+O0c+PZLmdZ9ZtovjxdOQhx4X5cjZg/f1XWCUrnPyEuZ37IsP7PEZVyi9cy0p+mt9cy0OH4unJTC9aRwPdRGx5mpTqDEwjPfvoO8t1qVQbW+LovFbjHr6TUKXsdeyWXmcpkf6b+X89Gl28oM/zgMa04vbZvlD8YJhXCnM5mL6xaB6yGIcYOFY6rk9XP7DMnLVVqWpy6n2ckkyBN8PNwnVq/tZZIsa9zLkFj0DeTvQFTrvsyKyE5lIxVmP9cac+fvu96zTUknXOHZpqZow3RfH3Bm8VO9XL2rYACPR80rYwk04CBIC0dqz8otUy/N1W/IKcxrse2bnX84ap9Oe/47C5jGMLI6cdy3hZPt0bw9EKM+8hksMuzizyOIDeESC+ba9TGQISnnGovsCRFaprmP00q1m7jT2C/O9xA2k7skNGgyZSNOTJ9ksSD8oLYoO5YWEFdMORVPpY4nOvZHJwmMZXMl/Xe/nfccJ6/NX2+NPmSNjQlvwc5pkdSjki7uhp1CqngY0pQe3dsdXpBtYUG3SUGErGjufqg6xM87BvHDXIi99oiP/oOwCIpdb4rZQilzcdLfGHLXj+ui3VFbBPWl/OP5h4u08iMFG9FUV+RtjMb8XFfdEiCxmeeZ24flSVr47zBSSY/6ukqDMCGDLVHVfYjDTHBxhOCCYBSMvmeHOjL5rSUXb6ltV9Pb6JxOCUFaeScvcoDROYT1Uc2gp2Glgbs1uaDxOyVAcWFMCqsivKMrIN77DTWn2jEv3EC91NLFMKDMpg42ZH2EZ6OQZ0P6BOH+vEg3QjnXVNyY+Nteg7ZujgYQwIuxhKURMHUMOFTiK3C8uw+aKOqRQOVCmEfF/WxRaqJV0sWl/0N4Mz1kiKNjsVK6YJGkXMWF7fs9F2YWo8eLuevbxUwU//kdNsGuOM1QTKXKLhCQ6z6HmPwUNjqH+OtPpY29IWpRn9rV8RUhj9D4+h9hMjf/RLJWxQVb5DyessUBDdPQBgGMH9YyrkeHYjHuERWdgClPr3IFZrQTM9pp+KuIQjtLL8rVXWXYiQ21LWiULqWN2Bx/4pf8Dt3bFp0j4rMo5Cyi6D8xkhHYKZZh16P9uwqHCX20jy3ifWzl7/i1X+5j4V0gBDrFq+dgBDv1qm7a52kPe4j2sGIJ4WWleknuDaU0GCLjx6AKhPk+6nyI3o43Fo0TX91HH3iJG0tyxN14uiUnf194+7i7tVunp7Csl8FIOusmDPAxgXP+YepHx2iYLa6Ig0wKfDw5U+JDB/3HyvuIPtXKW9DLYejk5xg/b0t0zoHZWvkB7vx9eL+b3x/AcLdiuMfh5V/4ZWt0zu7Z0Tnts2mQd3MOGFFHICgUH59j0glPPdFrYiPeAqv7dOI0vO3mKMsFgLVyNaFxOXwm5V6YCxXDrhJ/UIh7YTrTJe68F9gvk26jS4tT4ouoHQUPLI+mexlSUf1RQF55Z/hhJjse5Ok69Ft+V5ZMdqSMocm6qVuf00UzdSPN1HSz1TmDKIFzRKm+N68kh1r13sm8rWhUGTXGVt5VJnaHvt0qzIJJDZjdKcnVC3OiM0tOe3oePJvGDgMqRw9h13nk6iaC4vt28vT8BmLoYib7JT/l7yMgKOlLfoUXpwEM5prbD2yCirgVXjmndNMib0xvXdu/MQyTghMTxvCk7Rbicex77BncyNr+PDgcZRB/uZYgXdhluhbRkEhHu0uzTDf87vCUy1QnMWScZAgvjSN364Xd5j5RvfvuvOLuu7XpU/h9STc16e48+vkNPt+t3XhNtKRLZFHr4dd8CHohvc+n0K2opWFvrH1oEmGJ6x4YbNyfGUoV9cvih9zSbAJa1a6VYVSGGBQ1S0OGZ4ljaUbUfo5fnD5GzJVPX+Lgp65j2MMderE976j+wdZPUvSjs7U57q3/SYlmTpxtqG7brqh9pV9siFIzGre2p/gpqW0HDBPz58GE2RHenqPvoA/EROu32PXhWiYxo/ab1C9NQZnwj2Y3NT1EU+o3IKpseqlQXMSR9Msy/pUky5jn6pdlhHLqdeDBz+4xWT79wan5hOHbtWrhOaGOD+WIrqGUXPO2I6pxk5LBjoD+RdQOjmZZhNJFH9n6HuokB//JehkOGA95O2M/CmWKV1EAZR2tVdm1KrdW5dSqHE0Wbm4P4fqYTas+YjxYyJHD9mrVnVDEe+sr7NJU4KtUoDYldg5NUbJq7V2dlvpzXsQZF7WZ6GWvQ3twKg7kCT41h9h8j8T6zvp6dO99SDKO6kXZ+YdPtMzIN+oalVBBzRS1kPrnRvOgayXQw72wzS8Upw73d7DMWDyTvhdNEcosmstZU4LiLG6UVjEJRp3SYeweAQsISGFnTRHf0PjAGtohddSpph/SQLwwJFFTOWpKF0/8wcFqNlQl1ySr+cHqdIteNKWgyrEsVTw4CkIOuzYFupK0aVdM0qq7xEyw+r6uMox7kOZKzKfK4YpuJjXkOjAqs6bAI5qxeJIIUCX6rKnQhy+j0RWT0DhfJzXg2TLYa1KaJq+D1+dodKFokqiu7FcoMw/FjsLIy1icGUoTf1wKBir7RMtLVjUdr6yxWO3DDqgLEMH7wki4uRK1p2UjxBc0lPoUfQ/RU5fWG8ssFkI4Q2v3gv4PitQHaJwL/eLU/X0GvbNYluN483K8vaQSBYpP74fiyi7x48WQ1okf9pnF/vawOcTUXl4ICY1cNyhehNsLygZbxcmHsU863kGBBCODaWSpoaeyuKEwEIESLRW+gurlJt5d4O1T3dDsprdPQKnG1x07y7XR26c3135sWW4YWz92Z9AtmBbN170JLY/sUkcR5Q+9L1SbGntEc+Q3dNwJcVlBdZ8r8jSwvbfHHxCfP9jHOivmiHbcBrxc7EDhdLfM4+tRLog0yq/pHVMNNpHfI2Zx56fq5T1B8dsPCQSz6WVpL49I/uEZZUFM94+e4umGZymATJmYifgwRDXBl80F1OcyVhlePAkb+vhennDd29PB2OzkJtR/fq+rroDlx1P0QkeJp8f1yCUGVx3XpKdB/RzhR1iD/uWIUbXOU+WoXgsdmL3hqStTXHUnT3N+vNbweupKzt6DGEgjUERQ/OkQ44pUKiWWSt0/v5EYDY5FniUtHzrmSI+wB1me2qOzcwEzArabhxrrvVtjr1K3J85qWFOfwDNI8MlDmCJOPMRz3YmxqnZg4AFnj/yU4OxOgFNQFKM72ZHDyvkMAfoeT+uDjjKxEEmu9Ys7forlScCA58vY97MbwHEIU7JH7D7JkxAUlkP9YKmnB9h3t+l5J5RZvx/I6OGFQEYAUNk6u5j3UF9CjwTy8nyoBxwmwpJIoQjUUOVE6NWC5mKxCV07zTUdIkKxU8yX+nAXY2HvoomeOoLaMd0R9Rueb5aM8PQu/dzTU90BYyF7fbjHqmzC3PQuPYj52cfzUw/H1s8AXZU7ZGh1OQmP3Sq9GePkSEIrvH4SpiLwgbYa4fDqTk8v1bl6OC/Rhh4ei5CVwbH1f0zs4+CWOsSbiPXhgyn6LnbL4aq7BfBtxQAwKhKMilahFO8RvcJNI4npNgdTq3DrTaLthxJB+TqJOO8POlNWJn5ya4Zlt24N6K8tR4PZmTaUM6SyKGKc0VOK3tWv4pfkzy0NPSi2T7PC6Ub6NIwGLear2Tn78RXIbC/blEolKqMK5tvV4eFljodgTsVGKKzUJlOlKDdRMZ5GNZdSDFfPgqOHMIdWs7qe2Dq9NJ46Nm5aGv2oY+THFDWTUtJCjn/Xnob+nyzTugmktepB+1hNMo3KPlsZKxubPc2On2HcZgVVo3Gp0EEMpcSLQ1b+fjGRURdMexa3WdPW4WfotBTZ51T6UbPDL7C/1JiLtkAqxvVEg7YCb7BqbmzvM26P677N1FetxZjuRERUYnJuJfT3WbyJD4ybNoh+lozpP9+jfK6gX+psygDEbyGEFtZH0vbeqNfCmi1yhioqz5fuhZ8iZahfjDqXlZKOsjUcteWE1LZbBXXLIGKaKnffoPGTZ++S2/UVsPolOqS0LP9wwRRlsnxhTJqSkAEMk6+oCXgJuYZ8MUPv3fpZSnhqukV919iANyIzjWjgF3BrmXf7/LgKXjCUqtE+zopFfukaGGjeVfdzC6tbIypjICj+aTVV+soJ9cEqpEkpC/rFGIMNvUpCXUGp8Mp+JUZdQHmzp1kQNPnSkCVo7A/PmpsSOw9hlLPVs48XzU1RsqiccP0BtEblUJT7w3fPPRVKCfa3QV1Zcfv8xIk8qFj4AFGHhhzCO+WU0VQ0/tHdUOvJfRk7s+IYAsGZVpRbO2sC2DvoGSY5SIOhOQ39GOgamytsqBmkhedNtelFS/VVAOrwSSuUhDHjj1JbYhnhkylqmsbx+ZIMD6Ed44i+xpz3HjHlaptUmKT7zybbkhOypnOukk40Cwvl1/CRt2o71+uAExe2a6lkZLUasbv6c0L75v7cSvibZ5Gb4yXp9Y3gqraF0ieO1NG5oL4F7zwfKYXhF3CH6A9DiY8v4/BxLJoLcxKLeo72NG5o78iE62pKZqNkVnYRboWvkn4dIFlTBJZrzUKfdorPQss7tjpOJWxrwlvWolTCWCtwg/5wxIwqKLOd7pPGR1HWTe9fEo6whkCMVq22nd4jRUfGivTEV6pwXLgnTRkb7klXzgr3OJSscI9dcbNuwZoXGVgR7b1fJboik0c1TecjPlNdGLP9hJxt4jrr5YcVEBVh/sP1eGNhvFDRCG3W+nFjR5hHxGgibTuucE+KMhhNSRW/c/YZBbVAbUqe3nKjMvxGJTX8XzsNJ78MpcScTXyHaabhtEokxm3k9wPwd9iwUsFGChVciIIZofKhuJc+qSPQdihnGBsAeASOsXMYJlvhvpuBUSIp6GCYKsMA1/wGGRIzbiRb280V8w91iEFKFuKPudG51I6tGUQTvIYSxR2BhPNoGtPzLiSSrciur+QolrMc+kooEWpDodrDt3qRXVuPjyZ3Fn7ITjsNNu1hGisc4vYGSow0jfQACXNHKdWXnKDUoa1GgvAP7JZGduV9BQRo95sCNL/4cI0j6Zj7dqkVoBfChfUTBASmYFVjtcwKfesA0wR/H5EqDJjhKZYKQvoWQGe5ced9CdhJfFaGy6/G7EXmdkHgsqeiw0llmLR6DgO8tAG4pywYsr3zIxvUHGn8pQOQA0DCYxx8lKoORm/wzdhvZBW+IPU=
*/