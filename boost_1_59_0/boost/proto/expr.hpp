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

        #if defined(__GNUC__) && __GNUC__ >= 9 || defined(__clang__) && __clang_major__ >= 10
            #pragma GCC diagnostic push
            // The warning cannot be fixed for aggregates
            // Sadly, GCC currently emits the warning at the use location:
            // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94492
            #pragma GCC diagnostic ignored "-Wdeprecated-copy"
        #endif

        // This is where the expr specialization are
        // actually defined:
        #include <boost/proto/detail/expr.hpp>

        #if defined(__GNUC__) && __GNUC__ >= 9 || defined(__clang__) && __clang_major__ >= 10
            #pragma GCC diagnostic pop
        #endif
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