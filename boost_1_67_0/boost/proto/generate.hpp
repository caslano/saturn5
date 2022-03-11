///////////////////////////////////////////////////////////////////////////////
/// \file generate.hpp
/// Contains definition of generate\<\> class template, which end users can
/// specialize for generating domain-specific expression wrappers.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007
#define BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007

#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{

    namespace detail
    {
        template<typename Expr>
        struct by_value_generator_;

        template<typename Tag, typename Arg>
        struct by_value_generator_<proto::expr<Tag, term<Arg>, 0> >
        {
            typedef
                proto::expr<
                    Tag
                  , term<typename detail::term_traits<Arg>::value_type>
                  , 0
                >
            type;

            BOOST_FORCEINLINE
            static type const call(proto::expr<Tag, term<Arg>, 0> const &e)
            {
                type that = {e.child0};
                return that;
            }
        };

        template<typename Tag, typename Arg>
        struct by_value_generator_<proto::basic_expr<Tag, term<Arg>, 0> >
        {
            typedef
                proto::basic_expr<
                    Tag
                  , term<typename detail::term_traits<Arg>::value_type>
                  , 0
                >
            type;

            BOOST_FORCEINLINE
            static type const call(proto::basic_expr<Tag, term<Arg>, 0> const &e)
            {
                type that = {e.child0};
                return that;
            }
        };

        // Include the other specializations of by_value_generator_
        #include <boost/proto/detail/generate_by_value.hpp>
    }

    /// \brief Annotate a generator to indicate that it would
    /// prefer to be passed instances of \c proto::basic_expr\<\> rather
    /// than \c proto::expr\<\>. <tt>use_basic_expr\<Generator\></tt> is
    /// itself a generator.
    ///
    template<typename Generator>
    struct use_basic_expr
      : Generator
    {
        BOOST_PROTO_USE_BASIC_EXPR()
    };

    /// \brief A simple generator that passes an expression
    /// through unchanged.
    ///
    /// Generators are intended for use as the first template parameter
    /// to the \c domain\<\> class template and control if and how
    /// expressions within that domain are to be customized.
    /// The \c default_generator makes no modifications to the expressions
    /// passed to it.
    struct default_generator
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Expr>
        struct result<This(Expr)>
        {
            typedef Expr type;
        };

        /// \param expr A Proto expression
        /// \return expr
        template<typename Expr>
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(Expr, Expr const &)
        operator ()(Expr const &e) const
        {
            return e;
        }
    };

    /// \brief A simple generator that passes an expression
    /// through unchanged and specifies a preference for
    /// \c proto::basic_expr\<\> over \c proto::expr\<\>.
    ///
    /// Generators are intended for use as the first template parameter
    /// to the \c domain\<\> class template and control if and how
    /// expressions within that domain are to be customized.
    /// The \c default_generator makes no modifications to the expressions
    /// passed to it.
    struct basic_default_generator
      : proto::use_basic_expr<default_generator>
    {};
    
    /// \brief A generator that wraps expressions passed
    /// to it in the specified extension wrapper.
    ///
    /// Generators are intended for use as the first template parameter
    /// to the \c domain\<\> class template and control if and how
    /// expressions within that domain are to be customized.
    /// \c generator\<\> wraps each expression passed to it in
    /// the \c Extends\<\> wrapper.
    template<template<typename> class Extends>
    struct generator
    {
        BOOST_PROTO_CALLABLE()
        BOOST_PROTO_USE_BASIC_EXPR()

        template<typename Sig>
        struct result;

        template<typename This, typename Expr>
        struct result<This(Expr)>
        {
            typedef Extends<Expr> type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr &)>
        {
            typedef Extends<Expr> type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr const &)>
        {
            typedef Extends<Expr> type;
        };

        /// \param expr A Proto expression
        /// \return Extends<Expr>(expr)
        template<typename Expr>
        BOOST_FORCEINLINE
        Extends<Expr> operator ()(Expr const &e) const
        {
            return Extends<Expr>(e);
        }
    };

    /// \brief A generator that wraps expressions passed
    /// to it in the specified extension wrapper and uses
    /// aggregate initialization for the wrapper.
    ///
    /// Generators are intended for use as the first template parameter
    /// to the \c domain\<\> class template and control if and how
    /// expressions within that domain are to be customized.
    /// \c pod_generator\<\> wraps each expression passed to it in
    /// the \c Extends\<\> wrapper, and uses aggregate initialzation
    /// for the wrapped object.
    template<template<typename> class Extends>
    struct pod_generator
    {
        BOOST_PROTO_CALLABLE()
        BOOST_PROTO_USE_BASIC_EXPR()

        template<typename Sig>
        struct result;

        template<typename This, typename Expr>
        struct result<This(Expr)>
        {
            typedef Extends<Expr> type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr &)>
        {
            typedef Extends<Expr> type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr const &)>
        {
            typedef Extends<Expr> type;
        };

        /// \param expr The expression to wrap
        /// \return <tt>Extends\<Expr\> that = {expr}; return that;</tt>
        template<typename Expr>
        BOOST_FORCEINLINE
        Extends<Expr> operator ()(Expr const &e) const
        {
            Extends<Expr> that = {e};
            return that;
        }

        // Work-around for:
        // https://connect.microsoft.com/VisualStudio/feedback/details/765449/codegen-stack-corruption-using-runtime-checks-when-aggregate-initializing-struct
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        template<typename Class, typename Member>
        BOOST_FORCEINLINE
        Extends<expr<tag::terminal, proto::term<Member Class::*> > > operator ()(expr<tag::terminal, proto::term<Member Class::*> > const &e) const
        {
            Extends<expr<tag::terminal, proto::term<Member Class::*> > > that;
            proto::value(that.proto_expr_) = proto::value(e);
            return that;
        }

        template<typename Class, typename Member>
        BOOST_FORCEINLINE
        Extends<basic_expr<tag::terminal, proto::term<Member Class::*> > > operator ()(basic_expr<tag::terminal, proto::term<Member Class::*> > const &e) const
        {
            Extends<basic_expr<tag::terminal, proto::term<Member Class::*> > > that;
            proto::value(that.proto_expr_) = proto::value(e);
            return that;
        }
    #endif
    };

    /// \brief A generator that replaces child nodes held by
    /// reference with ones held by value. Use with
    /// \c compose_generators to forward that result to another
    /// generator.
    ///
    /// Generators are intended for use as the first template parameter
    /// to the \c domain\<\> class template and control if and how
    /// expressions within that domain are to be customized.
    /// \c by_value_generator ensures all child nodes are
    /// held by value. This generator is typically composed with a
    /// second generator for further processing, as
    /// <tt>compose_generators\<by_value_generator, MyGenerator\></tt>.
    struct by_value_generator
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Expr>
        struct result<This(Expr)>
        {
            typedef
                typename detail::by_value_generator_<Expr>::type
            type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr &)>
        {
            typedef
                typename detail::by_value_generator_<Expr>::type
            type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr const &)>
        {
            typedef
                typename detail::by_value_generator_<Expr>::type
            type;
        };

        /// \param expr The expression to modify.
        /// \return <tt>deep_copy(expr)</tt>
        template<typename Expr>
        BOOST_FORCEINLINE
        typename result<by_value_generator(Expr)>::type operator ()(Expr const &e) const
        {
            return detail::by_value_generator_<Expr>::call(e);
        }
    };

    /// \brief A composite generator that first applies one
    /// transform to an expression and then forwards the result
    /// on to another generator for further transformation.
    ///
    /// Generators are intended for use as the first template parameter
    /// to the \c domain\<\> class template and control if and how
    /// expressions within that domain are to be customized.
    /// \c compose_generators\<\> is a composite generator that first
    /// applies one transform to an expression and then forwards the
    /// result on to another generator for further transformation.
    template<typename First, typename Second>
    struct compose_generators
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Expr>
        struct result<This(Expr)>
        {
            typedef
                typename Second::template result<
                    Second(typename First::template result<First(Expr)>::type)
                >::type
            type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr &)>
        {
            typedef
                typename Second::template result<
                    Second(typename First::template result<First(Expr)>::type)
                >::type
            type;
        };

        template<typename This, typename Expr>
        struct result<This(Expr const &)>
        {
            typedef
                typename Second::template result<
                    Second(typename First::template result<First(Expr)>::type)
                >::type
            type;
        };

        /// \param expr The expression to modify.
        /// \return Second()(First()(expr))
        template<typename Expr>
        BOOST_FORCEINLINE
        typename result<compose_generators(Expr)>::type operator ()(Expr const &e) const
        {
            return Second()(First()(e));
        }
    };

    /// \brief Tests a generator to see whether it would prefer
    /// to be passed instances of \c proto::basic_expr\<\> rather than
    /// \c proto::expr\<\>.
    ///
    template<typename Generator, typename Void>
    struct wants_basic_expr
      : mpl::false_
    {};

    template<typename Generator>
    struct wants_basic_expr<Generator, typename Generator::proto_use_basic_expr_>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    template<>
    struct is_callable<default_generator>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    template<template<typename> class Extends>
    struct is_callable<generator<Extends> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    template<template<typename> class Extends>
    struct is_callable<pod_generator<Extends> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    template<>
    struct is_callable<by_value_generator>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    template<typename First, typename Second>
    struct is_callable<compose_generators<First, Second> >
      : mpl::true_
    {};

}}

// Specializations of boost::result_of and boost::tr1_result_of to eliminate
// some unnecessary template instantiations
namespace boost
{
    template<typename Expr>
    struct result_of<proto::default_domain(Expr)>
    {
        typedef Expr type;
    };

    template<typename Expr>
    struct result_of<proto::basic_default_domain(Expr)>
    {
        typedef Expr type;
    };

    template<typename Expr>
    struct result_of<proto::default_generator(Expr)>
    {
        typedef Expr type;
    };

    template<typename Expr>
    struct result_of<proto::basic_default_generator(Expr)>
    {
        typedef Expr type;
    };

    #if BOOST_VERSION >= 104400
    template<typename Expr>
    struct tr1_result_of<proto::default_domain(Expr)>
    {
        typedef Expr type;
    };

    template<typename Expr>
    struct tr1_result_of<proto::basic_default_domain(Expr)>
    {
        typedef Expr type;
    };

    template<typename Expr>
    struct tr1_result_of<proto::default_generator(Expr)>
    {
        typedef Expr type;
    };

    template<typename Expr>
    struct tr1_result_of<proto::basic_default_generator(Expr)>
    {
        typedef Expr type;
    };
    #endif
}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007

/* generate.hpp
SAas2GMsHDLmsSGyMSYmxXVpOIkhR7bXCa1X57FSz2oNtks1w2Dgu/VRrWntbg0ebZll+6B2DN4X1GjAaTDMggfbpZWf2y6ZHkeDPvzUjDsCmX6Dm2/bjbYaTn+SOKEYuRk36+iooj0qvOOQ+y5Mul4kRWVf5mkBgBPYMiRGaEBNmYQDHjqXjNPNU99QFDUSTzcfzT3c9DddGRQNkOLXOPm7F9OB9EXRo32lXnaYASpXpoRmaWUHut6CckL6aNCgpRhDDCppS83aCCMiOyxhRxYdi3boww5yzgZZoSAlsw3SAphE8QDt6j8D5nBkQ0uOYQmx8784qie9oaXZHiTRCavDZnvUWHM7W2qJjLPVGmpGMWiOsUHsyyK8wHtwYoOGLdPDDL/HZsRamnM5ovXEIJ1UoX5zQwMCtDkNAPqCXMNDy7G2TrU2O565bTY9cQkabptlNIU+Qxx7h1iVKMoE8nB3r9RgerxJg07ejcK3UkGlUZrv1yvLjfz8LpoVt0AKkQq/GX3zHLqEfnUCQ8Oa2U1YEjqIwyXjCd1vERc/8psA+Ue2MzsPNuLI0DI/5Xbz7ZfSNf4kUfh/i8KVZbh7BAlszVK6gq2n2b1pJ0B2qQEny2vEqU0qC+nr3U6uuwDTOssI0+rBeYP+HCCtJnpVg1alQYdqAD0YZUs9lBYfM/6ToWQnT5Oj+osh+ze0OUmwIHOhJhSW2AwvDGlFb0GlofYewKiwpLPY/eaCmSf1ARNO0bSnNIGxiDUiYgafGjCDT2lm2CoNK/fieenA1FBVDEXiIPFckHhU7EfdR5yqGgKZ/ZpYnxKPRtEajeNZspManYBhb0YacNDJCwCzRMYKE5OR5FCmWo8S3nikGGG8R7JKrVdwQUBAP0IQ+oWBTvoBf2gAykaI6AxQGbSEuj2GuaTxO+fCg1xCrgL5CZTacLu8VRYJGgP7+W9RfYbGWo2Kmo8fuwBV41nzEYBbRRyLonOT6cjIhHmPQTVO9AikDNxkHFU6+Ras5QZNTHOTgET/fhmRaEzX47B4IesI6K4fD9bwvMtqh//FcJ3Sdn8jwokDGzpKRUTYEMJDXuG4K9iSDeCyl8a+OTgdsTNIVsowfJBGxms38sdQm3E9vmog3QY6EpvpywM5LpyMb4gsBEJ4AV9jaQI2ZRg+IEs5HauhLMqJ3cXw542n4Avu/CS7lRNKerA5K9iiX3MJU6zkAAsxIQW50aCSsSSZT9+OwqWoPZnT3StjETxCU97EAnH2bhY1HMXnESz8/casZKxGxVZKivhMEPF9JWtNGD96laOJFBm1RVGs7uA2RUkoAPOQ/HLbcai5kM5DjtsLwFSSom42o7OgwnDKHMAS6OSrVM/HfqYhMxP/UORCalbQFSOl+aQOengFKhnowBLaAvAqqA6dG3Q7/amQhp+O6MjFqsMCDJzsyAImWHbMZfYsdDxRO4e18NdShIM5Q8Od2I5oMhF6xLrSUGsjD6UQpHmx6v0rSDyLQMFevpteAsNZ6Vx5mjZYuyBJOiKv1OojB3w/WKA1812/VQ2VS/Wy3cB/dQ73VOtOQRuDW3EheyxebOA/VxB/RWdZs/hjkIk5oMAsKlAvr8xCG9NlCjGn3Pdb5MqAl3ixO8ZLBDtxAwhInos5ZqLlKtCywFSv2G8SG21YzQ0/Qjo7V2fvJd9ZWDaariBh9GThcR3pnSpM9+ktadhifqILmLx98dl5XR+3iMGJibmYQecesZnIqkbb6Gw672CEZ/I+CCVthpL4rOTE43S/VvoMD/7xm4FOtzx85DEUj4CKWbvxjP0RqKpYnmGG5zq877JAMgTuAdZSCVh41ilUkCMfPA3+6D0epY3dl8M/xJV8XzY/SX+z+GH6a+H76O9Ejk7mvPzRo/BWrReb3lG6tBIG8kEQd74lTORMTm6/0aSZZ3sMRdWl9wXfErLrPYitHzTg/I9w8utuxBOQaBnJbUBn5s1TdmAy/oyWDvDiseQMwJEkT/B1amQV4M0Z5kpAnImLxshKzHiJ+Cq8zbMm5rZVR37R+jtujTmZ6nPaCogvOw8FlV6VewSq1Ii7YOSY1lijk6H4GrMtWgOyO9OxxedRJ85/i6LsPFtLrQHiqs/n1hiZlTnOQ45aSEdEI8sWlSwhB0hCr96UeD53DNvPh6BmpQRvTzV6Q3qHk9+8jRQgRIdI2CLvTj9MUgEIq0y+WYnJWoB1eyYrytpGiexUDvJ52IUWPlLXR3jFmWFUvrOTLN1bt2+FetT3a19X0C8IcK/ORcE7NYFvMF1oWjErPh/SF8t26OlSb5mXG/+erglNmzVvHlqj15iXzkDzXb6JjnCzdF1JrxP16KE5Wi3bL48k0Ijcxmy2+8/XZEEHJ+1RO5gS0s9ykueHyIhgOu6KDFM/8Sk39euzseFBXDQ/gqnmow7DktWCiLj0Ip6d6HTungsLKBie4sGDFKecaDfbSQoBVARP4x+3weNiA+6+ZW4AoRizeNAdATvEP7kshFVab1tuxMq5qgX/9mRsQVfB3PPSLkj5US7Wyh8R19ei7rEIEvBGLS1DWGK4FccfhbpAoibzXyOuoGYgI+hxhm/EL12sdJptP3Au6tkzgHadXDmNS2/jRz4d0uCh5ev6DrjRAWTlhFw5mTkmxV8mxemQql388+s0/0A0N6tsyVCn2PotjIz2K04ht/MfKOnAkbdPQgC3oGbPGDdDWNOZZRhgXgp45dVDhDccM+UZBvo1ClVFiLQYwDT2+YLQk0Y65U5U/oqP5A9CruM94mAB/2cBYMwQvqJqQ+tVzyaryflkVXDmeyBdsPYBDR5MpBT8zjRa4g9QMf/1e2h+rVMjWVXvsZ09uDOhOYNuDl6nMoaokREdnqvuBZZTdjjRWn1PsHaORiqIZbyAGVMwY6XIOFyN5K1DqcY5kdSwYw5uyWHGQJA5nIA2g7U+jVTJqGehELY+t+lwlB3KbQ3WLtZKqb4AAGQk2eeDPy5lGybjP/kSh77iRtRDYY7gXrOTf1vU4sMzBxORb+gbnWDtQxrpNt+CJtSL4yh4nXz3EHSzNZrKEAMzfqg4Iu54CIsgHB2zK/jOybiix8Om7noRjZyV48PQPsupHOeH34G0eE5AXmyQFxv5vL9AI3e9o6gKoZGANuXiYjqTMRsTzeR/Re3TL94RxkWVMBE/O0XK97hfQhdqcggHhcp7ywDenEoGecdsmwAYNNGVMzGYaeqxzxuE5V+iMgNSnGQ6j+Kcif5Lf44Src6LXt/z0RlVQXJ7eaZZKkTrveTT+DgVbXuTz+DjzSh/JJ/Fx3Hsfr31SARtc3XNBWapJNhkKMgAfuhu20Xpo8g05tVHcqE4LSy4Ir3NoZeuYUUGm8MgDWdFRpvDKA1l90DWYL5GygjuMbChwH0fYncDH7O3v7bE5UJHWujTiVo4Sx/RgUSO+aKhxfrIzSwFPTXphY4iYYRgADIAplNJWSEB32sI3qVIh6mKnVgFypfBFQZNYCi0jMZL3xxs0ruUzIYXUSFmaPjBIcCL3+4FYexcyKHHKlEHlqeeuiWOf7yyLDtU0sknHYDZTRlf04vGZGbiJiD2G0hugP+HIpr7V2Vo7ngmpuISbjEv8G8iiElGOYUcQQ3hVQrCQAT9ePBzl1HqIEfyl99SViUnFWpWJ7h+oMKHo3VDkQELw87jx4qOX1AtyIzXo9LSxM4pJ0DGdUyCPxZ0wXHCP1x25MGfFNkxRTnBpj9O6WRHvoibqJyokh05lYSJ2dSVaMToT2MXlON+ozzLAH+S5FlG5XihX/fiBuS04Unz4kbiuVej6nrq6hfgt90/1w1pv+mWZ2Upx91+jTwrW8lc+zLJgFQ24sSnsMun8HruidyBLZ9e/TKqUFah5viET4N/Zcc0aFmS7CicKzugJ5YqudIpV85EtXezD90/NzAkaMUgiLMm2jludDr5Ew5ARRsgrpn/8DXaGiVnDzdeB7WQQwWWYkWn2QOcPSQJZw83qVjBn+9b3TSYp4cf7aIdvkjOICmEm4e5lMLi9QpHD15+tAOQzf2CPjqvVxLcPPw4M6ZHdcGCzcI+AI+c7RRes7LZBXa/waNaBNE5LQnP+qbyX7YnWJqViLPU5dkyroNMoLNvjCMctuYfGvSmY5KX63EVZAsQQm/1Rvwx+LW+IWiin7kV5XCeFFOzImCB/Ao9Gas6XSWTfD16lUnQLpB7SZDgjHXKCuTdbrXVnl8pGLJrchIZshH8R6gBAZbE6+EvvKoyJXFkFhPV40DeFxFzmS9sKuTaiQW12ZJJWZbH7c+jpQ+e3ZyE/MChwFjhVJCn/kC4t4P+J7jbEWn63vC0Z6I3ntp8aJA6Ey7VfA2kIrRfwg1j0hh/3u3I0gJDuMzi13PvMJRcJnlZ7eTcqO2DpUnskteJ12/wy9coirZ2krYGXc/mfmBaux/VjUdYc8+yHHYp92LwwahGrulVyEIVhxoakK8FucMevYn0rSmoZ1n+QW5F1LT2JyhY1ERNdetIZ1lQa5BmFdQiUnXkIOPYvkyH1zM78lANqZYYVUvE4nToqncoFrhMb7u05DSkDBnz5dLJkVGQlmWEHJOFTfOyHACwsjkslToEaKNfn24WfaIO4aXUzXF9DowTDgsOBaBlz2RbG3BmUHJB7p6n/doyp+IFpmtypBgPxUFFbJRbGm7bE5iKaUbn7nGWKe5pkRshJoNiUIyEWH+S4p6DEdqQZ3IZtQ76BK2bDyhqUkwtSdperN0bm5WmNJgVzySArxAwe4C8ci/qwlg1DI9UDZ23tZnWPQ1DWafUjvaW5ba6nPyT0QCQNCzQPShdTmOlObmH0JMzTBNg8nIDuvk9vEQnlxh0eE0GNcxLY9x7k91AY5yOILLMQNdqRJe8izPimARyrayLTAbJjXoX7mmnMcH5mUyFuPvGHnsHWZg9WuDIWYp+Wg0dyM2xtNxSZFVtrRSp6xgFkXHrUdIXkRNTMQRJfPdQAsxCm2PysmQ+H0mNY9L6EkO9QYHSEyTaK7MGRVbUg1Pma0VmlPJwV0Yu1gcdkwxURpwPGVjG3bEykkQZ735JZSyiuzIMkD/pq9ugDFHz60X+X4j81AbIrR+QO3FJ7hVZWenkkFNrO7wsLbepEPVnh0QR6/FmmXrtlaOQWMbqhDJgzpcNy22C4cBSZLUhqJ6VM4DBk4v6hmPwwqwJhSXFCkuiG0djo6KhcdEOHBcXkgMjasdCdhPIWOEU1MLxFJj61TUmZelQ03a7SaBQNOMFlI8nwBou41FJPHJ6XSwb6UMOXRbZluxTE9+PiRU18dIU0w67IfKHEN5rdIh78V5kuzEYVZY8j2oaiDqKu5SIk4YCdE5HPcCyIJqU8zKQdlR9T41ZI9R5u9GKKmBBt1XfhF76sE3w/A72uMLIDtneX2pw87tRqX6Ph9+B0YfWXMJUGP9rjL/Zh20TU38oeEnBD5g/kuFXOFok+TVuKPL2L4X9WtwEWYhxn7+gKB5++x51p/BnEShlWXZkOJqYo+9G8qMSsNAxQemfHv5RBLkvccREw/+KyVsiXaLEhHusemMzUtcdmIXXWEMLUmFgYPAa5BQ1ohuatChY01C4dKJph9QAEvIujN58gewlzfjaMnPqLg2/D+V14cGP3L1cPJCuiSNU/hL6BFo0MaYqjtMj09rfaQQxMq1Fc9ABa6cZN/lKJwG+zW3ysku2ADUsytP2JUmoFQYO2cV9ln5UKbAIoPAuqCZGmBAbIXUih5zOaZAu9wM6yHzNFXRCS3QCSUQlngQMbiJYtjnypM+RWLid/NIIks20JGPHkQVBHPQDYQ7VKnwncEcRYJj+cIkEb2jRx5cS3ci7yFEwjMcve/vgtTeA8NobSadvB/nLSXR6JEa9kVPAzYQ83IYoMZh2RE07HAaQ+2Yj59fK7finhDyS46lFsXno1zfsRk6yqitdqIOImaydqAmYYD0nSUP4iAtiRqBCP96nVmpBrynBMcBYJp1LJ/PGTixhbKwE/tkLyHuWWvjvAWGT01gg1HR8ueyXEJGKds3skOLMwkTEGkojqWmq6uTGMfhmDJaaFbk0q/swCInXtZp27+s5OWZf8MO2YFOhWy4tBNkS/uS58URh5TS5Ml++lrb4Zsq0xZctVxpYql+HFc0BaTR4BthpY8Nq3EZrrTEAuy9X5kV0cmkOq80pqMyTJgmy5Hb7dZAjeAb3E6UMPDryi43IcAFZq8xGKxtB9FVmIpDEmpB2tfAvPk3XxETZYKel3+oxCF4x5k0+JVtR3F6Pklm9GW38WXvI3ol7nZ+8l64h16HzA+XvpaKiyeV6L3uikrlSrNzCRSxlkc3eKd2xiDmS4OkT6WvwhHGfSRPgyQBP56XR8DQUnrolEzwZ4SkaP5QXW3Vr98XF+5hJ6Rd4p7hR9ZO+BNjnRFpn2pESjOoCNwejQwPXB6Np0gjCOSgsorPFRTBYEbyfYC32SDd3EUh4wAA7vopGmHR9NEIfoxG0z5XVQ+uKSARRiDjtQ3f5IJsuFh6hkjsmpwlnQzf+BSDwmX+lk9/GLpAQg9EkkAdKDOS9jf8VIcpu6ECTJ+uRe2x7pO/z2b8k3Z2RGzIVZbemHRYomjz2PkdWlLd66NvKkfQ2AW2D0SR7moUgel6w0QwSXCpfmQXv4Q40O8fKjA9CZT4VfJu6eAV8jqyDFr2nxVMzaJxcDuyvWZ3Wh6gbK1bxxufVtqy0xNpCBq0Pi8bki8Z8mklvN8ca8/qI/o35FPkjVFOix7GOBxVaU6JNx66Jt2lfv1T/uExvoRIz34Jp8GKFLuEEzonFS4Z5uHgazZBVTuGPJ2YGoNfAkKN9jXGPsK8pw3lwdAImuGA9VVBhMK1FQzAoFfd0QaJb07TlHKxOA25A73+OOm3mj2FFs4xxx3cnhoPQuNg8T5Y6aR+p8ryU/UZKF8jFvPJZ0rMNwzsUO/n7OBtSJ5tl8CRjuU48KsF7zuDZ5z4X9Tv+iaqz6ywkmqLLtTBhG+wR3zWSdFARQ8NbE0EetTbyWzqpRwBT1diXWZEYVvvwF+guZTJ0lGdQy0uN/J3hBFeKsByHGIB4Pgm56hb+d8iZyCySQyi1APvIvv2WZRsSDnoaGoYa4fthaLLfzMfTp1a5pDPmwzlN7VMFbjLgDpW9y+c04L0vIHqOO51OF76QtfkTUER/i/Yu3MpC5fgoarUZlpfzPEtnj5zHRGVOD2rdVcNz/nQb9QwNzLOhI3GTezSUAUQuPw2fzXIGcIh9tkWd0/o5awa8ZwmV7HU5w/a9kzQobM8VZnEzQ/Z2J2I3JXMhak9SAKWt1DF7JyANhwEw2Cp4OY/Iw6HH+/3grQtvdnIYAZPhtyjaE5T0Whut7xRW8p17xWEFoWCZjtobds5/a9hBF9koJ/y3yevwgLByIkQumLzyOtzZVTIXoJ7H13O91mxVvF4l04k5x84RZwqHeUPrMLXT689TjobWbYBnOV/evRH+FpCDJuk6r9PrSzJDUUcLduP3gBkybaRMvuEUD++bxftQM7ryadWiU9ZXtOLApnKU0We5Vl8lr9ukRd8UYqTXdKKdaaKzP9yF9YXqcHsYSUXzCSAVD65FG7NFsn01hB+/8IA0ygzkg7U2dZj9hvqSZyvx0eC3hCkbzoFMThLkbcgz15c8V29/XslEpRnlqS/ZRBnq7b+qL3kBaEXr6g+1Kt1d8+Grv51Tvqbpt78tL5dn150utLWs/ADvSMCSnXgyza9XX2AkN6A6TKU01zTj9OhpetALwKnQbjTOlJ/Pht+CcQGDl0/4J7Rp3JqWiRhzbcDg4RkYc218mwIE0dA9l4NRy/KHlIl1707SmlmRJfJdVpQV+TYrmhSpYEWTI3NZUXbEzYpyIqWsKC9yLyuaGJnJiqZE7mZF+ZE7WdEDkamsyBfJY0UPRXJZ0eLIDawoEBnPiqoj2WwNWWlbhF01Kn1XRlLLxOAghG94HSrdCuEghGcgPA7htxA2QXgJwk4ITer3n0L4Lwjfg/BDCI9B+DGEfRBqICyFUI2dwL5VKNfPxhkgto+tMSeJg82odhpNWKWk19X/SChuKPYpzddYKEcgK7gTnYdpJFM8F6VsxqsjgbkO/QG9paEFgcknr0ITOOA/0Mw4JX6khhs6NJrpWk0KHiBZmhLWnCcDQ6eS579JyZyjDoWK0ehGxWS+6kmQdCxfDMeLQM0n+s7z3+Pr+oQiLx2n/ZuIb2aE3iPi/ZRvw8f0fkq87/e1f0Dv++FdXIqlcg5edF09BWA78OALE+EPnXEgBbM8Hd9fmDQgEt9fmDwgEt9fyIYfD5uKDvrgm86pHH8hR6TDZ5lqqayKm/Kh5NEY0IHEC6jqIYBpZE4uXJ9obSlcQ2GS+BFeZ7/ZQpcxvhdw5HJEjjWdOMUDlvZudODpiV3mlzmH9sSIu3LH7h5c8lG6ZlFwl/0TeFswLzBaPZeBHz1O/rdPBesIA6neFwiR78Qjt8dK0W0S9ry0NFe9hUygf07DM0jq/nIWSR2s6ZJNfPoNwsIjtA6d5Tkxas8ktJewNoIsptoWrf05EIHpu/DohX0r9PoV5QQr2WptDF4wmZ5rLA6e+TLYmKxrlZ84oEX26ICuNbSOfOY9cSxW6A+g0MEyuxNyt8Vyy0+0474bZLt9kmrOAM//gPngj58lGuW2nvIWPI2e9AL3FjyNCCZQFNqJaIWl2pqlO2ARZBGOkTLQSps2SFdeI1QMXt+cPWjy7PZN8uDZtS50u5NaiUxzldDes3OhJzahMvKU17Y/MLRgnj6QzLNuhCY9gaPEh9EjehHkSfSIjgN5zw34iP3mnfSITCj/kB7R+yA/jv6jDvLT5K2eG2GaCp7n2IXhbB2q6oF1gkUvUxxb16nFGDYWYTgwFK/y+DVGwRck3KjypDii4sFfP0t/dmOnNYFhSmYUr8X8Nb0ict3pBIDnOYC1d+a/DE9/XZWk4WNf0Gr4/Y/CU+6KJCzRyK+DB5Age+APbwskoQJkTGqSpqPtsjYRHQRSyAk/gm2p962srFF4GRa/eISwwkiPlw87iqYNyhb0AsmDQUC0JjrHL5w3OSCCDD4s/Q4ovMFaQFYFNBaJEon3ZTcjhef5zyH44ZFC66l5sjowgXt9mmY0Mz3h64LpVLZjtLwOERlEnU6Iioqo1oQofZKGPNMa4G8kS34ec8nPR+kXv8nP45c=
*/