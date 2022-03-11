///////////////////////////////////////////////////////////////////////////////
/// \file expr.hpp
/// Contains definition of expr\<\> class template.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXPR_HPP_EAN_04_01_2005
#define BOOST_PROTO_EXPR_HPP_EAN_04_01_2005

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/selection/max.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/traits.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4510) // default constructor could not be generated
# pragma warning(disable : 4512) // assignment operator could not be generated
# pragma warning(disable : 4610) // user defined constructor required
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{

    namespace detail
    {
        struct not_a_valid_type
        {
        private:
            not_a_valid_type()
            {}
        };
        
        template<typename Tag, typename Arg>
        struct address_of_hack
        {
            typedef not_a_valid_type type;
        };

        template<typename Expr>
        struct address_of_hack<proto::tag::address_of, Expr &>
        {
            typedef Expr *type;
        };

        template<typename T, typename Expr, typename Arg0>
        BOOST_FORCEINLINE
        Expr make_terminal(T &t, Expr *, proto::term<Arg0> *)
        {
            Expr that = {t};
            return that;
        }

        template<typename T, typename Expr, typename Arg0, std::size_t N>
        BOOST_FORCEINLINE
        Expr make_terminal(T (&t)[N], Expr *, proto::term<Arg0[N]> *)
        {
            Expr that;
            for(std::size_t i = 0; i < N; ++i)
            {
                that.child0[i] = t[i];
            }
            return that;
        }

        template<typename T, typename Expr, typename Arg0, std::size_t N>
        BOOST_FORCEINLINE
        Expr make_terminal(T const(&t)[N], Expr *, proto::term<Arg0[N]> *)
        {
            Expr that;
            for(std::size_t i = 0; i < N; ++i)
            {
                that.child0[i] = t[i];
            }
            return that;
        }

        // Work-around for:
        // https://connect.microsoft.com/VisualStudio/feedback/details/765449/codegen-stack-corruption-using-runtime-checks-when-aggregate-initializing-struct
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        template<typename T, typename Expr, typename C, typename U>
        BOOST_FORCEINLINE
        Expr make_terminal(T &t, Expr *, proto::term<U C::*> *)
        {
            Expr that;
            that.child0 = t;
            return that;
        }
    #endif

        template<typename T, typename U>
        struct same_cv
        {
            typedef U type;
        };

        template<typename T, typename U>
        struct same_cv<T const, U>
        {
            typedef U const type;
        };
    }

    namespace result_of
    {
        /// \brief A helper metafunction for computing the
        /// return type of \c proto::expr\<\>::operator().
        template<typename Sig, typename This, typename Domain>
        struct funop;

        #include <boost/proto/detail/funop.hpp>
    }

    namespace exprns_
    {
        // This is where the basic_expr specializations are
        // actually defined:
        #include <boost/proto/detail/basic_expr.hpp>

        // This is where the expr specialization are
        // actually defined:
        #include <boost/proto/detail/expr.hpp>
    }

    /// \brief Lets you inherit the interface of an expression
    /// while hiding from Proto the fact that the type is a Proto
    /// expression.
    template<typename Expr>
    struct unexpr
      : Expr
    {
        BOOST_PROTO_UNEXPR()

        BOOST_FORCEINLINE
        explicit unexpr(Expr const &e)
          : Expr(e)
        {}
        
        using Expr::operator =;
    };

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_PROTO_EXPR_HPP_EAN_04_01_2005

/* expr.hpp
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
*/