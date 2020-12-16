///////////////////////////////////////////////////////////////////////////////
/// \file extends.hpp
/// Macros and a base class for defining end-user expression types
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <cstddef> // for offsetof
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/expr.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/generate.hpp>
#include <boost/proto/detail/remove_typename.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    #ifdef __GNUC__
    /// INTERNAL ONLY
    ///
    # define BOOST_PROTO_ADDROF(x) ((char const volatile*)boost::addressof(x))
    /// INTERNAL ONLY
    ///
    # define BOOST_PROTO_OFFSETOF(s,m) (BOOST_PROTO_ADDROF((((s *)this)->m)) - BOOST_PROTO_ADDROF(*((s *)this)))
    #else
    /// INTERNAL ONLY
    ///
    # define BOOST_PROTO_OFFSETOF offsetof
    #endif

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_CONST() const

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TYPENAME() typename

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TEMPLATE_YES_(Z, N) template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename A)>

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TEMPLATE_NO_(Z, N)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_IMPL_(Z, N, DATA, Const)                                      \
        BOOST_PP_IF(N, BOOST_PROTO_TEMPLATE_YES_, BOOST_PROTO_TEMPLATE_NO_)(Z, N)                   \
        BOOST_PROTO_DISABLE_MSVC_C4180                                                              \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        typename BOOST_PROTO_RESULT_OF<                                                             \
            proto_generator(                                                                        \
                typename boost::proto::result_of::BOOST_PP_CAT(funop, N)<                           \
                    proto_derived_expr Const()                                                      \
                  , proto_domain                                                                    \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, const A)                                  \
                >::type                                                                             \
            )                                                                                       \
        >::type const                                                                               \
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, const &a)) Const()                       \
        {                                                                                           \
            typedef boost::proto::result_of::BOOST_PP_CAT(funop, N)<                                \
                proto_derived_expr Const()                                                          \
              , proto_domain                                                                        \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, const A)                                      \
            > funop;                                                                                \
            return proto_generator()(                                                               \
                funop::call(                                                                        \
                    *static_cast<proto_derived_expr Const() *>(this)                                \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, a)                                        \
                )                                                                                   \
            );                                                                                      \
        }                                                                                           \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(Const)                                         \
        template<typename... A>                                                                     \
        BOOST_PROTO_DISABLE_MSVC_C4180                                                              \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        typename BOOST_PROTO_RESULT_OF<                                                             \
            proto_generator(                                                                        \
                typename boost::proto::result_of::funop<                                            \
                    proto_derived_expr Const()(A const &...)                                        \
                  , proto_derived_expr                                                              \
                  , proto_domain                                                                    \
                >::type                                                                             \
            )                                                                                       \
        >::type const                                                                               \
        operator ()(A const &...a) Const()                                                          \
        {                                                                                           \
            typedef boost::proto::result_of::funop<                                                 \
                proto_derived_expr Const()(A const &...)                                            \
              , proto_derived_expr                                                                  \
              , proto_domain                                                                        \
            > funop;                                                                                \
            return proto_generator()(                                                               \
                funop::call(                                                                        \
                    *static_cast<proto_derived_expr Const() *>(this)                                \
                  , a...                                                                            \
                )                                                                                   \
            );                                                                                      \
        }                                                                                           \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_CONST(Z, N, DATA)                                             \
        BOOST_PROTO_DEFINE_FUN_OP_IMPL_(Z, N, DATA, BOOST_PROTO_CONST)                              \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_NON_CONST(Z, N, DATA)                                         \
        BOOST_PROTO_DEFINE_FUN_OP_IMPL_(Z, N, DATA, BOOST_PP_EMPTY)                                 \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP(Z, N, DATA)                                                   \
        BOOST_PROTO_DEFINE_FUN_OP_CONST(Z, N, DATA)                                                 \
        BOOST_PROTO_DEFINE_FUN_OP_NON_CONST(Z, N, DATA)                                             \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_EXTENDS_CHILD(Z, N, DATA)                                                   \
        typedef                                                                                     \
            typename proto_base_expr::BOOST_PP_CAT(proto_child, N)                                  \
        BOOST_PP_CAT(proto_child, N);                                                               \
        /**/

    #define BOOST_PROTO_BASIC_EXTENDS_(Expr, Derived, Domain)                                       \
        Expr proto_expr_;                                                                           \
                                                                                                    \
        typedef Expr proto_base_expr_; /**< INTERNAL ONLY */                                        \
        typedef typename proto_base_expr_::proto_base_expr proto_base_expr;                         \
        typedef BOOST_PROTO_REMOVE_TYPENAME(Domain) proto_domain;                                   \
        typedef Derived proto_derived_expr;                                                         \
        typedef Domain::proto_generator proto_generator;                                            \
        typedef typename proto_base_expr::proto_tag proto_tag;                                      \
        typedef typename proto_base_expr::proto_args proto_args;                                    \
        typedef typename proto_base_expr::proto_arity proto_arity;                                  \
        typedef typename proto_base_expr::proto_grammar proto_grammar;                              \
        typedef typename proto_base_expr::address_of_hack_type_ proto_address_of_hack_type_;        \
        typedef void proto_is_expr_; /**< INTERNAL ONLY */                                          \
        static const long proto_arity_c = proto_base_expr::proto_arity_c;                           \
        typedef boost::proto::tag::proto_expr<proto_tag, proto_domain> fusion_tag;                  \
        BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_EXTENDS_CHILD, ~)                        \
                                                                                                    \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        static proto_derived_expr const make(Expr const &e)                                         \
        {                                                                                           \
            proto_derived_expr that = {e};                                                          \
            return that;                                                                            \
        }                                                                                           \
                                                                                                    \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        proto_base_expr &proto_base()                                                               \
        {                                                                                           \
            return this->proto_expr_.proto_base();                                                  \
        }                                                                                           \
                                                                                                    \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        proto_base_expr const &proto_base() const                                                   \
        {                                                                                           \
            return this->proto_expr_.proto_base();                                                  \
        }                                                                                           \
                                                                                                    \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        operator proto_address_of_hack_type_() const                                                \
        {                                                                                           \
            return boost::addressof(this->proto_base().child0);                                     \
        }                                                                                           \
        /**/

    #define BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)                                        \
        BOOST_PROTO_BASIC_EXTENDS_(Expr, Derived, Domain)                                           \
        typedef void proto_is_aggregate_;                                                           \
        /**< INTERNAL ONLY */

    #define BOOST_PROTO_EXTENDS_COPY_ASSIGN_IMPL_(This, Const, Typename)                            \
        BOOST_PROTO_DISABLE_MSVC_C4522                                                              \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        Typename() BOOST_PROTO_RESULT_OF<                                                           \
            Typename() This::proto_generator(                                                       \
                Typename() boost::proto::base_expr<                                                 \
                    Typename() This::proto_domain                                                   \
                  , boost::proto::tag::assign                                                       \
                  , boost::proto::list2<                                                            \
                        This &                                                                      \
                      , This Const() &                                                              \
                    >                                                                               \
                >::type                                                                             \
            )                                                                                       \
        >::type const                                                                               \
        operator =(This Const() &a)                                                                 \
        {                                                                                           \
            typedef                                                                                 \
                Typename() boost::proto::base_expr<                                                 \
                    Typename() This::proto_domain                                                   \
                  , boost::proto::tag::assign                                                       \
                  , boost::proto::list2<                                                            \
                        This &                                                                      \
                      , This Const() &                                                              \
                    >                                                                               \
                >::type                                                                             \
            that_type;                                                                              \
            that_type const that = {                                                                \
                *this                                                                               \
              , a                                                                                   \
            };                                                                                      \
            return Typename() This::proto_generator()(that);                                        \
        }                                                                                           \
        /**/

        // MSVC 8.0 and higher seem to need copy-assignment operator to be overloaded on *both*
        // const and non-const rhs arguments.
    #if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600)) && (BOOST_MSVC > 1310)
        #define BOOST_PROTO_EXTENDS_COPY_ASSIGN_(This, Typename)                                    \
            BOOST_PROTO_EXTENDS_COPY_ASSIGN_IMPL_(This, BOOST_PP_EMPTY, Typename)                   \
            BOOST_PROTO_EXTENDS_COPY_ASSIGN_IMPL_(This, BOOST_PROTO_CONST, Typename)                \
            /**/
    #else
        #define BOOST_PROTO_EXTENDS_COPY_ASSIGN_(This, Typename)                                    \
            BOOST_PROTO_EXTENDS_COPY_ASSIGN_IMPL_(This, BOOST_PROTO_CONST, Typename)                \
            /**/
    #endif

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(ThisConst, ThatConst)                                  \
        template<typename A>                                                                        \
        BOOST_PROTO_DISABLE_MSVC_C4180                                                              \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        typename BOOST_PROTO_RESULT_OF<                                                             \
            proto_generator(                                                                        \
                typename boost::proto::base_expr<                                                   \
                    proto_domain                                                                    \
                  , boost::proto::tag::assign                                                       \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr ThisConst() &                                            \
                      , typename boost::proto::result_of::as_child<A ThatConst(), proto_domain>::type \
                    >                                                                               \
                >::type                                                                             \
            )                                                                                       \
        >::type const                                                                               \
        operator =(A ThatConst() &a) ThisConst()                                                    \
        {                                                                                           \
            typedef                                                                                 \
                typename boost::proto::base_expr<                                                   \
                    proto_domain                                                                    \
                  , boost::proto::tag::assign                                                       \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr ThisConst() &                                            \
                      , typename boost::proto::result_of::as_child<A ThatConst(), proto_domain>::type \
                    >                                                                               \
                >::type                                                                             \
            that_type;                                                                              \
            that_type const that = {                                                                \
                *static_cast<proto_derived_expr ThisConst() *>(this)                                \
              , boost::proto::as_child<proto_domain>(a)                                             \
            };                                                                                      \
            return proto_generator()(that);                                                         \
        }                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN_CONST_()                                                     \
        BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(BOOST_PROTO_CONST, BOOST_PP_EMPTY)                         \
        BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(BOOST_PROTO_CONST, BOOST_PROTO_CONST)                      \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN_NON_CONST_()                                                 \
        BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(BOOST_PP_EMPTY, BOOST_PP_EMPTY)                            \
        BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(BOOST_PP_EMPTY, BOOST_PROTO_CONST)                         \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN_()                                                           \
        BOOST_PROTO_EXTENDS_ASSIGN_CONST_()                                                         \
        BOOST_PROTO_EXTENDS_ASSIGN_NON_CONST_()                                                     \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN_CONST()                                                      \
        BOOST_PROTO_EXTENDS_COPY_ASSIGN_(proto_derived_expr, BOOST_PROTO_TYPENAME)                  \
        BOOST_PROTO_EXTENDS_ASSIGN_CONST_()                                                         \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN_NON_CONST()                                                  \
        BOOST_PROTO_EXTENDS_COPY_ASSIGN_(proto_derived_expr, BOOST_PROTO_TYPENAME)                  \
        BOOST_PROTO_EXTENDS_ASSIGN_NON_CONST_()                                                     \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN()                                                            \
        BOOST_PROTO_EXTENDS_COPY_ASSIGN_(proto_derived_expr, BOOST_PROTO_TYPENAME)                  \
        BOOST_PROTO_EXTENDS_ASSIGN_()                                                               \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(ThisConst, ThatConst)                               \
        template<typename A>                                                                        \
        BOOST_PROTO_DISABLE_MSVC_C4180                                                              \
        BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                            \
        typename BOOST_PROTO_RESULT_OF<                                                             \
            proto_generator(                                                                        \
                typename boost::proto::base_expr<                                                   \
                    proto_domain                                                                    \
                  , boost::proto::tag::subscript                                                    \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr ThisConst() &                                            \
                      , typename boost::proto::result_of::as_child<A ThatConst(), proto_domain>::type \
                    >                                                                               \
                >::type                                                                             \
            )                                                                                       \
        >::type const                                                                               \
        operator [](A ThatConst() &a) ThisConst()                                                   \
        {                                                                                           \
            typedef                                                                                 \
                typename boost::proto::base_expr<                                                   \
                    proto_domain                                                                    \
                  , boost::proto::tag::subscript                                                    \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr ThisConst() &                                            \
                      , typename boost::proto::result_of::as_child<A ThatConst(), proto_domain>::type \
                    >                                                                               \
                >::type                                                                             \
            that_type;                                                                              \
            that_type const that = {                                                                \
                *static_cast<proto_derived_expr ThisConst() *>(this)                                \
              , boost::proto::as_child<proto_domain>(a)                                             \
            };                                                                                      \
            return proto_generator()(that);                                                         \
        }                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT_CONST()                                                   \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(BOOST_PROTO_CONST, BOOST_PP_EMPTY)                      \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(BOOST_PROTO_CONST, BOOST_PROTO_CONST)                   \
        /**/

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT_NON_CONST()                                               \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(BOOST_PP_EMPTY, BOOST_PP_EMPTY)                         \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(BOOST_PP_EMPTY, BOOST_PROTO_CONST)                      \
        /**/

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT()                                                         \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_CONST()                                                       \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_NON_CONST()                                                   \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
        template<typename Sig>                                                                      \
        struct result                                                                               \
        {                                                                                           \
            typedef                                                                                 \
                typename BOOST_PROTO_RESULT_OF<                                                     \
                    proto_generator(                                                                \
                        typename boost::proto::result_of::funop<                                    \
                            Sig                                                                     \
                          , proto_derived_expr                                                      \
                          , proto_domain                                                            \
                        >::type                                                                     \
                    )                                                                               \
                >::type const                                                                       \
            type;                                                                                   \
        };                                                                                          \
        /**/

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        #define BOOST_PROTO_EXTENDS_FUNCTION_CONST()                                                \
            BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
            BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PROTO_CONST)                             \
            /**/

        #define BOOST_PROTO_EXTENDS_FUNCTION_NON_CONST()                                            \
            BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
            BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PP_EMPTY)                                \
            /**/

        #define BOOST_PROTO_EXTENDS_FUNCTION()                                                      \
            BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
            BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PP_EMPTY)                                \
            BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PROTO_CONST)                             \
            /**/
    #else
        #define BOOST_PROTO_EXTENDS_FUNCTION_CONST()                                                \
            BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
            BOOST_PP_REPEAT_FROM_TO(                                                                \
                0                                                                                   \
              , BOOST_PROTO_MAX_FUNCTION_CALL_ARITY                                                 \
              , BOOST_PROTO_DEFINE_FUN_OP_CONST                                                     \
              , ~                                                                                   \
            )                                                                                       \
            /**/

        #define BOOST_PROTO_EXTENDS_FUNCTION_NON_CONST()                                            \
            BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
            BOOST_PP_REPEAT_FROM_TO(                                                                \
                0                                                                                   \
              , BOOST_PROTO_MAX_FUNCTION_CALL_ARITY                                                 \
              , BOOST_PROTO_DEFINE_FUN_OP_NON_CONST                                                 \
              , ~                                                                                   \
            )                                                                                       \
            /**/

        #define BOOST_PROTO_EXTENDS_FUNCTION()                                                      \
            BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
            BOOST_PP_REPEAT_FROM_TO(                                                                \
                0                                                                                   \
              , BOOST_PROTO_MAX_FUNCTION_CALL_ARITY                                                 \
              , BOOST_PROTO_DEFINE_FUN_OP                                                           \
              , ~                                                                                   \
            )                                                                                       \
            /**/
    #endif

    #define BOOST_PROTO_EXTENDS(Expr, Derived, Domain)                                              \
        BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)                                            \
        BOOST_PROTO_EXTENDS_ASSIGN()                                                                \
        BOOST_PROTO_EXTENDS_SUBSCRIPT()                                                             \
        BOOST_PROTO_EXTENDS_FUNCTION()                                                              \
        /**/

    #define BOOST_PROTO_EXTENDS_USING_ASSIGN(Derived)                                               \
        typedef typename Derived::proto_extends proto_extends;                                      \
        using proto_extends::operator =;                                                            \
        BOOST_PROTO_EXTENDS_COPY_ASSIGN_(Derived, BOOST_PROTO_TYPENAME)                             \
        /**/

    #define BOOST_PROTO_EXTENDS_USING_ASSIGN_NON_DEPENDENT(Derived)                                 \
        typedef Derived::proto_extends proto_extends;                                               \
        using proto_extends::operator =;                                                            \
        BOOST_PROTO_EXTENDS_COPY_ASSIGN_(Derived, BOOST_PP_EMPTY)                                   \
        /**/

    namespace exprns_
    {
        /// \brief Empty type to be used as a dummy template parameter of
        ///     POD expression wrappers. It allows argument-dependent lookup
        ///     to find Proto's operator overloads.
        ///
        /// \c proto::is_proto_expr allows argument-dependent lookup
        ///     to find Proto's operator overloads. For example:
        ///
        /// \code
        /// template<typename T, typename Dummy = proto::is_proto_expr>
        /// struct my_terminal
        /// {
        ///     BOOST_PROTO_BASIC_EXTENDS(
        ///         typename proto::terminal<T>::type
        ///       , my_terminal<T>
        ///       , default_domain
        ///     )
        /// };
        ///
        /// // ...
        /// my_terminal<int> _1, _2;
        /// _1 + _2; // OK, uses proto::operator+
        /// \endcode
        ///
        /// Without the second \c Dummy template parameter, Proto's operator
        /// overloads would not be considered by name lookup.
        struct is_proto_expr
        {};

        /// \brief extends\<\> class template for adding behaviors to a Proto expression template
        ///
        template<
            typename Expr
          , typename Derived
          , typename Domain     // = proto::default_domain
          , long Arity          // = Expr::proto_arity_c
        >
        struct extends
        {
            BOOST_FORCEINLINE
            extends()
              : proto_expr_()
            {}

            BOOST_FORCEINLINE
            extends(extends const &that)
              : proto_expr_(that.proto_expr_)
            {}

            BOOST_FORCEINLINE
            extends(Expr const &expr_)
              : proto_expr_(expr_)
            {}

            typedef extends proto_extends;
            BOOST_PROTO_BASIC_EXTENDS_(Expr, Derived, typename Domain)
            BOOST_PROTO_EXTENDS_ASSIGN_CONST_()
            BOOST_PROTO_EXTENDS_SUBSCRIPT_CONST()

            // Instead of using BOOST_PROTO_EXTENDS_FUNCTION, which uses
            // nested preprocessor loops, use file iteration here to generate
            // the operator() overloads, which is more efficient.
            #include <boost/proto/detail/extends_funop_const.hpp>
        };

        /// \brief extends\<\> class template for adding behaviors to a Proto expression template
        ///
        template<typename Expr, typename Derived, typename Domain>
        struct extends<Expr, Derived, Domain, 0>
        {
            BOOST_FORCEINLINE
            extends()
              : proto_expr_()
            {}

            BOOST_FORCEINLINE
            extends(extends const &that)
              : proto_expr_(that.proto_expr_)
            {}

            BOOST_FORCEINLINE
            extends(Expr const &expr_)
              : proto_expr_(expr_)
            {}

            typedef extends proto_extends;
            BOOST_PROTO_BASIC_EXTENDS_(Expr, Derived, typename Domain)
            BOOST_PROTO_EXTENDS_ASSIGN_()
            BOOST_PROTO_EXTENDS_SUBSCRIPT()

            // Instead of using BOOST_PROTO_EXTENDS_FUNCTION, which uses
            // nested preprocessor loops, use file iteration here to generate
            // the operator() overloads, which is more efficient.
            #include <boost/proto/detail/extends_funop.hpp>
        };

        /// INTERNAL ONLY
        ///
        template<typename This, typename Fun, typename Domain>
        struct virtual_member
        {
            typedef Domain proto_domain;
            typedef typename Domain::proto_generator proto_generator;
            typedef virtual_member<This, Fun, Domain> proto_derived_expr;
            typedef tag::member proto_tag;
            typedef list2<This &, expr<tag::terminal, term<Fun> > const &> proto_args;
            typedef mpl::long_<2> proto_arity;
            typedef detail::not_a_valid_type proto_address_of_hack_type_;
            typedef void proto_is_expr_; /**< INTERNAL ONLY */
            static const long proto_arity_c = 2;
            typedef boost::proto::tag::proto_expr<proto_tag, Domain> fusion_tag;
            typedef This &proto_child0;
            typedef expr<tag::terminal, term<Fun> > const &proto_child1;
            typedef expr<proto_tag, proto_args, proto_arity_c> proto_base_expr;
            typedef basic_expr<proto_tag, proto_args, proto_arity_c> proto_grammar;
            typedef void proto_is_aggregate_; /**< INTERNAL ONLY */

            BOOST_PROTO_EXTENDS_ASSIGN_()
            BOOST_PROTO_EXTENDS_SUBSCRIPT()

            // Instead of using BOOST_PROTO_EXTENDS_FUNCTION, which uses
            // nested preprocessor loops, use file iteration here to generate
            // the operator() overloads, which is more efficient.
            #define BOOST_PROTO_NO_WAVE_OUTPUT
            #include <boost/proto/detail/extends_funop.hpp>
            #undef BOOST_PROTO_NO_WAVE_OUTPUT

            BOOST_FORCEINLINE
            proto_base_expr const proto_base() const
            {
                proto_base_expr that = {this->child0(), this->child1()};
                return that;
            }

            BOOST_FORCEINLINE
            proto_child0 child0() const
            {
                using std::size_t;
                return *(This *)((char *)this - BOOST_PROTO_OFFSETOF(This, proto_member_union_start_));
            }

            BOOST_FORCEINLINE
            proto_child1 child1() const
            {
                static expr<tag::terminal, term<Fun>, 0> const that = {Fun()};
                return that;
            }
        };

        /// INTERNAL ONLY
        ///
        #define BOOST_PROTO_EXTENDS_MEMBER_(R, DOMAIN, ELEM)                                            \
            boost::proto::exprns_::virtual_member<                                                      \
                proto_derived_expr                                                                      \
              , BOOST_PP_TUPLE_ELEM(2, 0, ELEM)                                                         \
              , DOMAIN                                                                                  \
            > BOOST_PP_TUPLE_ELEM(2, 1, ELEM);                                                          \
            /**/

        /// \brief For declaring virtual data members in an extension class.
        ///
        #define BOOST_PROTO_EXTENDS_MEMBERS_WITH_DOMAIN(SEQ, DOMAIN)                                    \
            union                                                                                       \
            {                                                                                           \
                char proto_member_union_start_;                                                         \
                BOOST_PP_SEQ_FOR_EACH(BOOST_PROTO_EXTENDS_MEMBER_, DOMAIN, SEQ)                         \
            };                                                                                          \
            /**/

        /// \brief For declaring virtual data members in an extension class.
        ///
        #define BOOST_PROTO_EXTENDS_MEMBERS(SEQ)                                                        \
            BOOST_PROTO_EXTENDS_MEMBERS_WITH_DOMAIN(SEQ, proto_domain)                                  \
            /**/

    }

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* extends.hpp
FdTzKnI4uBvvZPzJOa9+QzJLUDWV6Q74HPWFMY6D3WHIWGT9NTmu+awNZJVFLdQQGyqp/9L6han3Rl4POzrMm7oJM6VfHFHV+sOjHveT6pImz9vOKBmTVZkv0/xgHpMQXqJwX1V7Bjztv20arE1rB7iDPwdRHcRlNjGIFu3cwH/zYV5bIpFCji6qJrlI/zE6zsh/bEx3uF+5kbH1+qZe8vn4Ksq0L0rD/UvwXfudLFr/EHzT75AtxOqr/a79TrrynrggZN+1n0nT4uotXmB4rqq/PzBewGtk9rt+A0NrGgzP1c33eGFpkX2/hv5Ol4+c7jX1dxkvBVEGe7j+fi39XSkVQcfrXLsvw0oLFh7Cv1/H1MnTRf79ump8lnA/Wk+xcbte/z3HGZ9Y2Es0DvXV4bh+/53kZkjMDMeN++9LLcd7k/5bstDW7tvN9HzA3mFx3oK+6ZRDvL23Vt8xgvSGnPv+1yv131tMUbPE7ky2rohx1/4FZLXEJ3ffc2WU6fW0esbdN1RXsd/tfYNZ09nBlO/3W0OrD9J2YGeC4GAf5yXTUq1MMTJe0O9NFmav39r3V02SLiuyvCODzkUgxA9Or/kecHGeV7V5m2DHik69VYVthr/ME4yba4TwAAxU85DO8J8pzz4fi7LqsrAtdZMGZ/7ATnoJrxuBbzfIWljVlTZaal5h1GL1MNOabRXLq34NPwd7iQOprpVd6tzAznIfr71gtEGeZ0ERicWRJuR6nUu0nyHhd0l/a9RdEmCXN52bSGRz7Jx3b1wheRGJyVY+vwErgwLllV1e6V0Pnj1xWj8LxfL2PB+yu6WplpvRfT67PSm7I5USEnQsLuZtY3WyL21Pyu8cECBjg/N7uwTLS3XCqlGvTzUG508m4WBFOUlt1MM3NTa6y68mYSmTxrLNbbY9LLfDsGra9Yfdo2HoFntr99IpQ+sfk7goBYwtf+Cu1WH5CNjyDVWO6fPLzdp/8G0GvsCyTWVdZyJSvda5B7Z23ZvHB6HRCby6JWS5gBKSWxlqrN/+xtZzi1AjMTieObgby2qZ5UlQQ44fbLw9GN0gXh7x3uxrPRwwbEo0o4oDL18IVgphYYMwkXPjox6eVED8DsKkjY/CQ4t7GPv0Ta9+LeI4Laq47Fh9Fa59VDM0z/+bPn81b3/wEu1XyAN/u77Zr4Ptqv1+cPjQ+5HAqw8R9g7lnVF+JV2+sNQtdwvtUhwtgTb9SOeKe2qSfHWuqWCjpapN7eOZms71GJ227lxFXX7DYTsYxHVRfmOU02LcXV8+u7u51vsM3ULXiZYcNcJ1mwlculj36U4X7JMbAKJxd05Df6f2SPiRYPPY9hDdGb+PbCQV3fkL0tWN1HTvbenqgdB9u59PY+KN0pjNAW8A1b0syo4h3tfNWF1LlckIL78MyWC0EA0fdrLAlS9HZZw9O3vte7/NbY4lrOlNlPV3JzsTby2+/BY8tq2E7a4puxyy8INgy9FbQVdUxse93TEkfbLo6VscdzZO/ZrbiUuZygBSg9BWPz/e5Ku3GNhiujYP6MWGSEFbg+MJ4k99nJ2WyJUZkd+J/WuAKw+6pCxqKIujfa3mMnxaStHyC/o0FkyOuu0tB/kcUhhhMSIiARbz/jB4v8FzW1kx+WeztzlzG9ELv+vreyEMILDIxoI1wt2M6AQdEYWmD96U4e2aCzGfsqlj5Dyh3g34/bs9mrloqjSXWdD6NKnigByLiXnwLQdv7ce1DEIYvguYyMwjYDhN7eoAjzM4TJsPOI7ZuGoKnFpkpcE8mNgDQ+9xHr1KdE2J++euYPQ4qfvNMizWL+Dn3jtIXRznVReKM4eXOh3Y+gUAlttdyiDt8lAmYuk=
*/