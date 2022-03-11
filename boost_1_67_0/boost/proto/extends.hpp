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
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
*/