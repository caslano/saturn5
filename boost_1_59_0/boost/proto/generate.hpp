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
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
*/