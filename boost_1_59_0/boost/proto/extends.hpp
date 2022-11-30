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
        BOOST_PROTO_PUSH_WARNINGS                                                                   \
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
        BOOST_PROTO_POP_WARNINGS                                                                    \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(Const)                                         \
        template<typename... A>                                                                     \
        BOOST_PROTO_PUSH_WARNINGS                                                                   \
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
        BOOST_PROTO_POP_WARNINGS                                                                    \
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
        BOOST_PROTO_PUSH_WARNINGS                                                                   \
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
                                                                                                    \
        BOOST_PROTO_POP_WARNINGS                                                                    \
        /**/

    #define BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)                                        \
        BOOST_PROTO_BASIC_EXTENDS_(Expr, Derived, Domain)                                           \
        typedef void proto_is_aggregate_;                                                           \
        /**< INTERNAL ONLY */

    #define BOOST_PROTO_EXTENDS_COPY_ASSIGN_IMPL_(This, Const, Typename)                            \
        BOOST_PROTO_PUSH_WARNINGS                                                                   \
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
        BOOST_PROTO_POP_WARNINGS                                                                    \
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
        BOOST_PROTO_PUSH_WARNINGS                                                                   \
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
        BOOST_PROTO_POP_WARNINGS                                                                    \
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
        BOOST_PROTO_PUSH_WARNINGS                                                                   \
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
        BOOST_PROTO_POP_WARNINGS                                                                    \
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
hcd3mYw62J8AzYGYQuPYc78l3ycoY9PZwK5fUBYOpRUaxhP15wl/KPFcbWcvwBuwJZg2Rlyw8lDWPMmOIa4pxtJek4Pcjc3TCKZT7WRZ9CtJbWQ3UZgIWmW9BlARPWwzkHXBQgH+nkOGzuV3o0eRSMxj50ZhPA7FiHDu2rMpKknP1nCqnrOMVvaXcWMrHgADv0xIMyAc6V45qWelIcs47snQZqgnL6kSm6yzRR5pL5HkFM7orWUhlLv2coDkrzm2Pre1s74Zr9C1gWBS2vp4C9/GGykYdD/R8Hxm97VIwzn7lgfZSVCQ+okuwlOSFuQFUR7QvXf1aHwgQlOwsE3w/uFc1ggN5J+ASvZuja5ESoK3ZWu0kZ0+z6SkHM+5Nj8g1RN3RplQVvh0E0oOGSNQXjB4pOui7OD3QsvQbCaVqIvQDF7+FpnBc4QZfLkQ30IFuMi49/K58pGcHNXXwdhXetNzPrukuhqnOFBZgnGlvA8oycKnM+4kZ/9wJiiP+mvGcUeXFGcvQKf3E0O7NXu+Wb5I/RClHHiwBB5Iv8nJIY/tSFNz84I78Q11oOOQNMi+IE2ycOKOGxlvCI3wTvXksev3YqiPlKgOxFScoP+MugB23esdv0hD7YvSpEF4FE+16geriwqi44ZTz02whhKftPC8+dS440yLm5/vaMlp4jrKhZ4R6bVExUFo702l3GRbV/Bc9+gbPqiATy6GGL/0WLR57Jy1EYZ/AcWE1Dr/EdgxnS3ktqt+AfqdH2UX5D3E8oThUHEyqZ9/N09VMcLDnXyPoveVq4W30s16EnjQj+psiaTt1Uku/jH9EBOnMOM40B1O2ljPuRzgfGm8CiirNEWMhMMDLljUo0VHbePJsTgFwi5IF/zncyDdDBB8G4VsNR7zP8BrxSA4+DvjpVj/ZTDxgVN4fmxWjd5Bmnt0yJrH/pFE5wDqILc2b+wiMu8sSeqOOE4vjm4H1iwNPb8hPqMy0gh4n/wP4jDWDyuIlP7vvYiyh7CE/EhUTn7rc4gPLDjxP++I4sR9xlbnx/8rTowLkR9jwcJXT/KlfO7KP5cB/e4OXP4bydk1gplGRwl7KJIEQ/SQF6MDM9B6Hi7cz9zs+B0Yv0/qr+LqRBRpD57tZ5xEOH4ziKVlfyYRzFyI1j42AriB2r5gQeCUlOonBckgDcG02693a5fCRcpk+GOTknEDd3Xi6m9tFzXJ70OhOxynpfl+ksgN8twwEoGR67IUWneYGd6iSBFs3qQ7hPsv+t3OT1OXpeV5O/JgeS4nCz5nlzna5yIgGx1vo+w/sOAigDUnF6LHHnTOcVC6Qz3EDv6F/AazPXk5ocmOXmmmh3fxhmQ6vT0oXWbfTjrPKPt20iCG0iLJy9MeSlPoDl8qMP2ubhbTjqdQji753YizMezwRkwBk+WnCTRIU3T/hus9UXvB/IViL7gwh28Gpa+fdzNYWADPArdHOwJQoACaVS7JQ7kGllMcmzyoW2Pf30nyCkYColwydbk4mwXNdCeKRBueTjYU4pkkiw91UWiki+TQbkeNFMeqgbCZ65noM8HLT0bOBGNC0eYIfNr9Wjf6PrGnTuIplXcAxftesLWbABA+The2G3JMQQeZX1nhSYQSSPM39/pr+uepR5TMNPanF3nIV9jsguH7hHAnjqWf/jkqfh8e47MoQICyjj6PbQIezsweP9UntIOqNUbKOc6u1tin2ivPrtYoHqRHV0v4hHxLIhEjWcgniULE0CEDzl3LoClNt5OVQbrRTpYH9JPnWqv12X0KpSoOXWin1SYN4w9kazV5wlN6jcQeRLNMQ+WAOIDkyOasQKewU/Px1D0qXWcnG/kahth0npuuE1fuSAzz1T4D6llMNN83NC9mPupX3fQ883wOCXayk5REi5PqeyQ8nIZxKUmTbB4PN1Mtixz310anolTJ/OeBD9zgL0oDMRkBxmabSn9FREfJVvprDP5vLv0VrQ/y0ByvoTBBON9zYSQWCggUFe6OZQ2Uk1HWnChP0RPIXi/8sj73CKeEi7lPgvHP5/VJwBm8LVKvPNVPs2aQbhD1rPNw70J1htnfmSZd7e8cvewCf+dly/r5O8cuH+Q1hmLo9LiAJ6B4C30w0y4Pg6PApJfT9P+Q8amdZp0G3/rs/uxs3AWej/Ac8cFRHsEdESq86N9wR0/rZE3g6ukUKkw6nKJuIcUIOH8U0QEXuJbfRl/bHTSn9DKKQy+fwcPv88jBBX323FxzRmV6vTR4ljzS7aYE2RZWf0LTQgPdbq+RX3/SjgG7ZP11VxxDxlRYnkwHH84KjPBsD/rqSZZq50BmaOzN/6ELT7x2sHEXIerCjgzgPIdQbTu1rEez724ge/sXZMLYQWmA0JMeD6Ltu1fx1Kjr18OwxPrpjOVQLB1oK84GNZY/uNzZFLrP/lgxyOvr1yL9EMgbOfuf/iK9xuhqJJsMd5GnN/izRqOThcZF3Yn1k0J8yOisx7rD941Q1lmPXvzOtnRqRbqzhZ6sAAZBntosncqmE2ga1u2OwLSF+vPf7aQ8VfBm4DG84txMOu0k9ChzVXiNrPE0/PKjCVSl43jMZBAD+j+dK4AU7s/idjS86fGCvruj2rnHsAqtwNvZnCrcH1fY4NboVeiOsh2ZTWgk/+D6SL/dHgKh42cFM4rSq9ERuV+WfK3ftccYGqfGwv8x54xVY2jwWSOI43SIHXqlW3vdYJiKFnzXHnTKVp02f7NJcW6Tsu2UZVC6BbonTjuMmns84dxVbtniNW7B4Iawezsqz7GavAf6lR10VWbjaMEHy3BSJ2yH0hk4TqoxD+qw70YBT7pOlRvhXjrU6NwBg17jZv8y9mr28SX97b7tUhzQFHJx9Do4DNuGQqX6fqc++jt8qroJj8UauBu/7B8nBt1h920DTZN3yaKqaNd2HIG52Bd0bc3W3kELNx4rwkqpUHxbFd829oQSa2hNxXMsKHqxKDpCTI199+h49HEN+tEKpDj3hMbAPIrJhrtoI7LvToG/cnzQj8YjeAd7ZbPvRquuZA6+gwaiUGq4zDtoOLLv7jBSmXda6CskDM1WXXswnG2GJwMYZdB5wM3yDmBc23bY8qghYZQceLNQM5CNBAHsZNBomqFL7P1vYad37Qll2ktM0qxwPcBhLJGasGHhmvpWQzkPsKKlWNFhaoP2Z6yzQpM3I2WMVV078Bz7Z1uXxp56MoIC2AeCCpU2Su7oQcML6h5CgwvKbSDsdWBIjK7+vfw71LOSDN6pFdZ3Ef9SIXZFUErOOsfpaBf4MEjSGwndWh5yrO/iCCcEyIT8xPmyFW8qzhqY/M9YybddPD+fKxXZG3ADnu0q5eEejdZoI9vxIa3MYRwdv56Y4VwNqk5Rp5pCU87n2SggIRvVrA4KUwvmNhMQ5A4oi244zjY1nwEbSs9vRlMxj/R/SOXHtflNjsaVsYqziTvGElPsjPU1BY6XWCK3Yjt1u654D1mE2hib3xSb34AJD/SXifs2+n0NhpI50XdCU/vUT0dTsV3n/4ia3wBtilEbIxUEU2egaicP8g7N8XC/ZiClZa+inFODQ9RoRtWyUZUJKvImZZGJfTFQR0Xcwf5gIrBI7xqe3sZQMQkn+MEnEJlDWDbiM447qqQ59vlp0i0gDE+VZrAjzV0cQujlEV2aOjDHgxBC6BRyzBZvIJvH9L/Gc5vIAGHzuKI/3OCAQgsGkoPFt0/wb15X8QJ+s2s1oYFIvOomNmOE8DlpivicxLxAENpBVw3b/YwIHJnBCzSzwSPCOQmHoS9IDR0d/eZ58gVxqM5m9AXJcLNX9yYb/My0QBqtR46Mqp5J3qChZPgRS+dB8IMYf6xSICHFFT6EdQJnVPIbWf/nSeRJsuc3ohdEDrJZ9ILAQ132ztdd3Gnm8eE6KuOt4fbEss+fi6AyHmEr/wk6Rykv0c7cw/XQl9RwCRPbwktcJUJfLsM3r10dhbF4w9MCY1F5grT2J0hrT+e1MnYmRfeRaR+q1xrH5vJaRwsfmVQ3e/IDHJcBC6T+WdayNzBeRY5X/oiGIfb1V108mufNFB2zsSZcVzyLpbqsZT+Q/NFG4R/HuV8i1Amas7/XzENgrOVVKJD29reuex8buforQUi5vGKzu3BzuOIE9pdnqZErgNlgI3/rZt/vSTZAdf3l4RhMAiP4YisIV/Phx7++1LRWNCn7e/vJMx1VxJTGWHeChuf4BS3fVcCUhsaCmrh3HjdrV0lf6moihqaAeAbVXPI91GfOgV/pX2kiByB18k8DusSDwV/xJKGFRUN1mmhgp57pCacHfWKV8H0uzAq/Uc8a+BvxKAbNLBbBRq4BYSjL6QPCAJc3DAijWo4bEM6WddEAdFeqwfPoX9f26vk0Bwyg1fRsGXdXqhiG7kr0l5h+qc+CwdnyFai8WW/tAb5XORwU/kz0yiTvVB6jieQeShBbDlrbQWl+H9flPf7wcW7LcI5riWFkoDAfcPXo/rTZd/VobBA0oQqUvWmSMq1ImVaslNL5dCmdOpfSCXQpnShT5vcq7/yKL/ED99MHYKvYyI4aBLqkcyPuiE88T1i0KH77Z+nxcxuZyQgfq/BH42hSjTpaK68+rMS/dgNCfPDWs3xN4654a4SvUWYRyF3AVOIxTVemRAp+xJmHeaMLp51V2LqzBoooc4qiS/l3kXuU3E/NtShP6Z+ZVixgtP/DOzRc6PZEI0bvRzwFT2XOT0FnODO6UK3l1inSQYpXCCtHFTdMeI3Q7CFTOTWSSWIXgQd5Y9h2+FGlTkNfm4Q4FDJxrpFokCKqQHbYhH5c+P+qcKiqjkn+uwuwxv8DPui14opEAIBDS6W9D1yUVfY/PsAAo07OaJi0YqLZ5oa1tlhJaEE6SH+gwdEZ3ETdVommdtOcUWzFPztgPj6NW23r2mez7L9t/9xKpa0MwhVNKy0rCksqqktDNSUBAvr8zgAHLPjT+9znYWaINvf769ULn7nP/XPuufc595xzzx8fiTc5nP0YboC/46LTAtXSIAwf3B/WrJJy4hzEtOsc4UsMdCb4r/WGtUukhLbV7Mst8xHl0i4RWwOsjLrQG88zEVIbPQhxxuTjcK/JGy/lUUNobvkTTQI5ds7KiFGcyICi4GUQb96ufudxiZyjDCAzUiV860YLPaOjDsy+76o13aawybTkiiilVF0+Nzgd3TAjvdfj0mZYaQ++LG5/p+cn3m3RM8Lbdb3QxRdF7ZlWOoljTFwe6YnolJ5piNEpwU1/dCHb+kPViPg7w8XV03u09pwFcfShJs1jP+IG3h3zcub2KtxM1NJ3kVs0FxiNz0XjMWKw0Xi4ZBl6+DokEtpz4tx5UR4Ej6J5jpk3DnwvvvPCi3GdbAPTnuAG7Lwip7iE3rjVTvHwEppq/TwjNNVl+RxNJ5n+0XbwJtWjMiLFtFFyH/xSHsOzSWTKEefqe3WvWEkdRzsDif0nqMYZiAt3d7mMtVaex8pA3XdJTfJIoUN8eQ3CT0+u2uebJOMO8aG5Ed+Ss+ptmnPWDLcc3EOQKLoSBuCxcca2bdu2bXvO2LZt2zbP2LZt22/uW3ybLFPV6f4rqRxLwMPOpqRUCm2uR9U3uZS6A97ueOLHh5bMH9DdO3UfDsZ0GbK+jMo/jO8+Iaf1kiNWiIXsfVnlyD6+RGx6ejZJD4sMZk4Saa/kMVduTpbOIbe6NVWJbSS/QFL1hQxE9zaOBo7WdyUeyvIIRXWF1CN+eNQgGKmQ4oUkLFC0fGJs0zIT1N+55OWYMo9Whr/bwkGqnrCEAyaatMslGajfIQo24ttKR9gvpIL0EMwmQVhqucOLNbIAMTroT/VVOCZKhi7JlhzG4O6Q179bnuetnssspiR3NhmAfwZBvL/gGx6yewCh8JDGleParBoIF0OascoW99OqzpQti8dQTI1HvuSWdFS3ZLsL2XBBKwkKCz+AzSc2HzS3KRdgAUs5fClIVqLnroXtIZgEe1jpAAWna5qVpRP0Kjd/hIo7stK2wT5GiXJKYXePrw6VGmQCe7reJIMkNx9lTe4eI7CTvtW6Oj7N4jjB8XQL4jrJhOFYvsAjYrUTVe7XQaPEHiV2u6TzQ3eZr+QaACsaMYXT84QLyb4z6XLkm7guxBA4lGZsySAkxrLDbwrZhymsL4x9XtNMpRe4ODZwWc4Rq3ZVNkarbXQ8JZVNycYyF6EaftYTI6YDdYZb+BdY9t44wqftbvTKMe6VSJ84w/umGgvefat+qzk0MYZ+wnwxS5c3G3R6Q6Aik2fVgkJFXtnOOUHP42s4h0DqtVdSG+kXbJ35s7qpc+i1+aPkz3z5u1FwBA1XgIZahCMOZWfT29hBHc6coC3FwsgUJYKwK3dKXOKLK1l4UFhq26s+wUylV5C2wzRBfDCrHsImFUFyBJRVRMNxdvr6iWGx2mCInZD1hTLuenrL284OQPOWkTR2hpcfZEqkO994VRlM2LxjVjCaphZqTGn5KzfUnhgBVkNsqstmvpK8JbLezTvG9oTzDJOiapAAqcYLXhucE1cWrdlBXi5pShJDcs4OuWeK7C0irZ8iriOESmiDFPUW9kBcUotVzkzVnYOvJctPtEquq92wT0Jd/mjx08trJZB79yZo5lsZr18ghBHYo+GxuciCxAnwnePAmoM9j9Iwfo/iPhqeotC/piBsk+Xo/6302Cnmz7+hrsVQI8vp5W8E4UzZlckKDWzcV0wTFCTiKbq8UWzuk7hwvIm35c//uxgQ2NU20zpCe52B3N5mOYaw+sRMP7VNF+D6PFs70COQ9aQky1hZsJRaAGvVBmtwP/8F/CoybSP6ufTGvN1zgCmgEHOjNXqjNZVJB0cde+usGiTaZ3JK03tj8BEHJMzSQp6Fme3B30e9xShcqi4pIGda+EoOP4KvumLncFF5kVI5UYTTGVmuFKg5K3Rh7BweY2uPYpA9PRuPDXlq7FZcEGybDjQAuzfXVLZrMafGqlQQaHoWPx1L9TAe/gBQaQFbdZ/eZ79MseBtGABYVQlfBiBt49e3t/IngAKzTVe24aWjlJwVcYV9ik/1ofQFSaDD6IUecVIUL5/O/aUtIReGubsRbqkDU4EmuqK6PTTd8gtvbHA88wPB7+8UUQKJCo1stbmpytS98N0MXgdGwTmNRXe4UZsEdvWpoQcF18VoujkjwmZj1TeIc4qIw3El1DiwmqxxSDq7chr2EgLvxfn5n7Z56wTfytaCg/OtTW/sSFX0LUG+80XNd744XAQEye+T0h+CGhNj4naN082vFwaZSjmP8w+FZ3MkUw4A/cLG9nXYhOQ6p7RynrtdrZP1g89CoNI7YN57xglxQ7xQlYsed3i8PDT4fXhfBFCbrQxrlBu55Or9iQwIJI+2jtCXgnfdmmsuZJRC7c0mZspedKm/7wVFoyLKNP0aPEzj82IFtQSUXiW+NddBP/m2sk5baSKRr3dWXDGP+IOWpaucycI9sCyPUjCTgY8r5SHBRwW40VvPhdxSBVg04czjZzaP04M/26eMGBryLQM0MhJ2CzKiSlY/MkglATKiXN3Nj/BRFP41MW7VLhU7d/WjTB5NjzsHvTWnGweop++n0c6EaU2nKfTA26bM1L0B/qi5ZgWayIMMzaanzbpLVl8gyBh8Afu8
*/