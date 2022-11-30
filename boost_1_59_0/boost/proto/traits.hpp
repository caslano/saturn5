///////////////////////////////////////////////////////////////////////////////
/// \file traits.hpp
/// Contains definitions for child\<\>, child_c\<\>, left\<\>,
/// right\<\>, tag_of\<\>, and the helper functions child(), child_c(),
/// value(), left() and right().
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/proto/detail/template_arity.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/transform/pass_through.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# if BOOST_WORKAROUND( BOOST_MSVC, >= 1400 )
#  pragma warning(disable: 4180) // warning C4180: qualifier applied to function type has no meaning; ignored
# endif
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T, typename Void = void>
        struct if_vararg
        {};

        template<typename T>
        struct if_vararg<T, typename T::proto_is_vararg_>
          : T
        {};

        template<typename T, typename Void = void>
        struct is_callable2_
          : mpl::false_
        {};

        template<typename T>
        struct is_callable2_<T, typename T::proto_is_callable_>
          : mpl::true_
        {};

        template<typename T BOOST_PROTO_TEMPLATE_ARITY_PARAM(long Arity = boost::proto::detail::template_arity<T>::value)>
        struct is_callable_
          : is_callable2_<T>
        {};

    }

    /// \brief Boolean metafunction which detects whether a type is
    /// a callable function object type or not.
    ///
    /// <tt>is_callable\<\></tt> is used by the <tt>when\<\></tt> transform
    /// to determine whether a function type <tt>R(A1,A2,...AN)</tt> is a
    /// callable transform or an object transform. (The former are evaluated
    /// using <tt>call\<\></tt> and the later with <tt>make\<\></tt>.) If
    /// <tt>is_callable\<R\>::value</tt> is \c true, the function type is
    /// a callable transform; otherwise, it is an object transform.
    ///
    /// Unless specialized for a type \c T, <tt>is_callable\<T\>::value</tt>
    /// is computed as follows:
    ///
    /// \li If \c T is a template type <tt>X\<Y0,Y1,...YN\></tt>, where all \c Yx
    /// are types for \c x in <tt>[0,N]</tt>, <tt>is_callable\<T\>::value</tt>
    /// is <tt>is_same\<YN, proto::callable\>::value</tt>.
    /// \li If \c T has a nested type \c proto_is_callable_ that is a typedef
    /// for \c void, <tt>is_callable\<T\>::value</tt> is \c true. (Note: this is
    /// the case for any type that derives from \c proto::callable.)
    /// \li Otherwise, <tt>is_callable\<T\>::value</tt> is \c false.
    template<typename T>
    struct is_callable
      : proto::detail::is_callable_<T>
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<proto::_>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<proto::callable>
      : mpl::false_
    {};

    /// INTERNAL ONLY
    ///
    template<typename PrimitiveTransform, typename X>
    struct is_callable<proto::transform<PrimitiveTransform, X> >
      : mpl::false_
    {};

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0)
    // work around GCC bug
    template<typename Tag, typename Args, long N>
    struct is_callable<proto::expr<Tag, Args, N> >
      : mpl::false_
    {};

    // work around GCC bug
    template<typename Tag, typename Args, long N>
    struct is_callable<proto::basic_expr<Tag, Args, N> >
      : mpl::false_
    {};
    #endif

    namespace detail
    {
        template<typename T, typename Void /*= void*/>
        struct is_transform_
          : mpl::false_
        {};

        template<typename T>
        struct is_transform_<T, typename T::proto_is_transform_>
          : mpl::true_
        {};
    }

    /// \brief Boolean metafunction which detects whether a type is
    /// a PrimitiveTransform type or not.
    ///
    /// <tt>is_transform\<\></tt> is used by the <tt>call\<\></tt> transform
    /// to determine whether the function types <tt>R()</tt>, <tt>R(A1)</tt>,
    /// and <tt>R(A1, A2)</tt> should be passed the expression, state and data
    /// parameters (as needed).
    ///
    /// Unless specialized for a type \c T, <tt>is_transform\<T\>::value</tt>
    /// is computed as follows:
    ///
    /// \li If \c T has a nested type \c proto_is_transform_ that is a typedef
    /// for \c void, <tt>is_transform\<T\>::value</tt> is \c true. (Note: this is
    /// the case for any type that derives from an instantiation of \c proto::transform.)
    /// \li Otherwise, <tt>is_transform\<T\>::value</tt> is \c false.
    template<typename T>
    struct is_transform
      : proto::detail::is_transform_<T>
    {};

    namespace detail
    {
        template<typename T, typename Void /*= void*/>
        struct is_aggregate_
          : is_pod<T>
        {};

        template<typename Tag, typename Args, long N>
        struct is_aggregate_<proto::expr<Tag, Args, N>, void>
          : mpl::true_
        {};

        template<typename Tag, typename Args, long N>
        struct is_aggregate_<proto::basic_expr<Tag, Args, N>, void>
          : mpl::true_
        {};

        template<typename T>
        struct is_aggregate_<T, typename T::proto_is_aggregate_>
          : mpl::true_
        {};
    }

    /// \brief A Boolean metafunction that indicates whether a type requires
    /// aggregate initialization.
    ///
    /// <tt>is_aggregate\<\></tt> is used by the <tt>make\<\></tt> transform
    /// to determine how to construct an object of some type \c T, given some
    /// initialization arguments <tt>a0,a1,...aN</tt>.
    /// If <tt>is_aggregate\<T\>::value</tt> is \c true, then an object of
    /// type T will be initialized as <tt>T t = {a0,a1,...aN};</tt>. Otherwise,
    /// it will be initialized as <tt>T t(a0,a1,...aN)</tt>.
    template<typename T>
    struct is_aggregate
      : proto::detail::is_aggregate_<T>
    {};

    /// \brief A Boolean metafunction that indicates whether a given
    /// type \c T is a Proto expression type.
    ///
    /// If \c T has a nested type \c proto_is_expr_ that is a typedef
    /// for \c void, <tt>is_expr\<T\>::value</tt> is \c true. (Note, this
    /// is the case for <tt>proto::expr\<\></tt>, any type that is derived
    /// from <tt>proto::extends\<\></tt> or that uses the
    /// <tt>BOOST_PROTO_BASIC_EXTENDS()</tt> macro.) Otherwise,
    /// <tt>is_expr\<T\>::value</tt> is \c false.
    template<typename T, typename Void /* = void*/>
    struct is_expr
      : mpl::false_
    {};

    /// \brief A Boolean metafunction that indicates whether a given
    /// type \c T is a Proto expression type.
    ///
    /// If \c T has a nested type \c proto_is_expr_ that is a typedef
    /// for \c void, <tt>is_expr\<T\>::value</tt> is \c true. (Note, this
    /// is the case for <tt>proto::expr\<\></tt>, any type that is derived
    /// from <tt>proto::extends\<\></tt> or that uses the
    /// <tt>BOOST_PROTO_BASIC_EXTENDS()</tt> macro.) Otherwise,
    /// <tt>is_expr\<T\>::value</tt> is \c false.
    template<typename T>
    struct is_expr<T, typename T::proto_is_expr_>
      : mpl::true_
    {};
            
    template<typename T>
    struct is_expr<T &, void>
      : is_expr<T>
    {};

    /// \brief A metafunction that returns the tag type of a
    /// Proto expression.
    template<typename Expr>
    struct tag_of
    {
        typedef typename Expr::proto_tag type;
    };

    template<typename Expr>
    struct tag_of<Expr &>
    {
        typedef typename Expr::proto_tag type;
    };

    /// \brief A metafunction that returns the arity of a
    /// Proto expression.
    template<typename Expr>
    struct arity_of
      : Expr::proto_arity
    {};

    template<typename Expr>
    struct arity_of<Expr &>
      : Expr::proto_arity
    {};

    namespace result_of
    {
        /// \brief A metafunction that computes the return type of the \c as_expr()
        /// function.
        template<typename T, typename Domain /*= default_domain*/>
        struct as_expr
        {
            typedef typename Domain::template as_expr<T>::result_type type;
        };

        /// \brief A metafunction that computes the return type of the \c as_child()
        /// function.
        template<typename T, typename Domain /*= default_domain*/>
        struct as_child
        {
            typedef typename Domain::template as_child<T>::result_type type;
        };

        /// \brief A metafunction that returns the type of the Nth child
        /// of a Proto expression, where N is an MPL Integral Constant.
        ///
        /// <tt>result_of::child\<Expr, N\></tt> is equivalent to
        /// <tt>result_of::child_c\<Expr, N::value\></tt>.
        template<typename Expr, typename N /* = mpl::long_<0>*/>
        struct child
          : child_c<Expr, N::value>
        {};

        /// \brief A metafunction that returns the type of the value
        /// of a terminal Proto expression.
        ///
        template<typename Expr>
        struct value
        {
            /// Verify that we are actually operating on a terminal
            BOOST_STATIC_ASSERT(0 == Expr::proto_arity_c);

            /// The raw type of the Nth child as it is stored within
            /// \c Expr. This may be a value or a reference
            typedef typename Expr::proto_child0 value_type;

            /// The "value" type of the child, suitable for storage by value,
            /// computed as follows:
            /// \li <tt>T const(&)[N]</tt> becomes <tt>T[N]</tt>
            /// \li <tt>T[N]</tt> becomes <tt>T[N]</tt>
            /// \li <tt>T(&)[N]</tt> becomes <tt>T[N]</tt>
            /// \li <tt>R(&)(A0,...)</tt> becomes <tt>R(&)(A0,...)</tt>
            /// \li <tt>T const &</tt> becomes <tt>T</tt>
            /// \li <tt>T &</tt> becomes <tt>T</tt>
            /// \li <tt>T</tt> becomes <tt>T</tt>
            typedef typename detail::term_traits<typename Expr::proto_child0>::value_type type;
        };

        template<typename Expr>
        struct value<Expr &>
        {
            /// Verify that we are actually operating on a terminal
            BOOST_STATIC_ASSERT(0 == Expr::proto_arity_c);

            /// The raw type of the Nth child as it is stored within
            /// \c Expr. This may be a value or a reference
            typedef typename Expr::proto_child0 value_type;

            /// The "reference" type of the child, suitable for storage by
            /// reference, computed as follows:
            /// \li <tt>T const(&)[N]</tt> becomes <tt>T const(&)[N]</tt>
            /// \li <tt>T[N]</tt> becomes <tt>T(&)[N]</tt>
            /// \li <tt>T(&)[N]</tt> becomes <tt>T(&)[N]</tt>
            /// \li <tt>R(&)(A0,...)</tt> becomes <tt>R(&)(A0,...)</tt>
            /// \li <tt>T const &</tt> becomes <tt>T const &</tt>
            /// \li <tt>T &</tt> becomes <tt>T &</tt>
            /// \li <tt>T</tt> becomes <tt>T &</tt>
            typedef typename detail::term_traits<typename Expr::proto_child0>::reference type;
        };

        template<typename Expr>
        struct value<Expr const &>
        {
            /// Verify that we are actually operating on a terminal
            BOOST_STATIC_ASSERT(0 == Expr::proto_arity_c);

            /// The raw type of the Nth child as it is stored within
            /// \c Expr. This may be a value or a reference
            typedef typename Expr::proto_child0 value_type;

            /// The "const reference" type of the child, suitable for storage by
            /// const reference, computed as follows:
            /// \li <tt>T const(&)[N]</tt> becomes <tt>T const(&)[N]</tt>
            /// \li <tt>T[N]</tt> becomes <tt>T const(&)[N]</tt>
            /// \li <tt>T(&)[N]</tt> becomes <tt>T(&)[N]</tt>
            /// \li <tt>R(&)(A0,...)</tt> becomes <tt>R(&)(A0,...)</tt>
            /// \li <tt>T const &</tt> becomes <tt>T const &</tt>
            /// \li <tt>T &</tt> becomes <tt>T &</tt>
            /// \li <tt>T</tt> becomes <tt>T const &</tt>
            typedef typename detail::term_traits<typename Expr::proto_child0>::const_reference type;
        };

        /// \brief A metafunction that returns the type of the left child
        /// of a binary Proto expression.
        ///
        /// <tt>result_of::left\<Expr\></tt> is equivalent to
        /// <tt>result_of::child_c\<Expr, 0\></tt>.
        template<typename Expr>
        struct left
          : child_c<Expr, 0>
        {};

        /// \brief A metafunction that returns the type of the right child
        /// of a binary Proto expression.
        ///
        /// <tt>result_of::right\<Expr\></tt> is equivalent to
        /// <tt>result_of::child_c\<Expr, 1\></tt>.
        template<typename Expr>
        struct right
          : child_c<Expr, 1>
        {};

    } // namespace result_of

    /// \brief A metafunction for generating terminal expression types,
    /// a grammar element for matching terminal expressions, and a
    /// PrimitiveTransform that returns the current expression unchanged.
    template<typename T>
    struct terminal
      : proto::transform<terminal<T>, int>
    {
        typedef proto::expr<proto::tag::terminal, term<T>, 0> type;
        typedef proto::basic_expr<proto::tag::terminal, term<T>, 0> proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param e The current expression
            /// \pre <tt>matches\<Expr, terminal\<T\> \>::value</tt> is \c true.
            /// \return \c e
            /// \throw nothrow
            BOOST_FORCEINLINE
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::expr_param)
            operator ()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return e;
            }
        };

        /// INTERNAL ONLY
        typedef proto::tag::terminal proto_tag;
        /// INTERNAL ONLY
        typedef T proto_child0;
    };

    /// \brief A metafunction for generating ternary conditional expression types,
    /// a grammar element for matching ternary conditional expressions, and a
    /// PrimitiveTransform that dispatches to the <tt>pass_through\<\></tt>
    /// transform.
    template<typename T, typename U, typename V>
    struct if_else_
      : proto::transform<if_else_<T, U, V>, int>
    {
        typedef proto::expr<proto::tag::if_else_, list3<T, U, V>, 3> type;
        typedef proto::basic_expr<proto::tag::if_else_, list3<T, U, V>, 3> proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::pass_through_impl<if_else_, deduce_domain, Expr, State, Data>
        {};

        /// INTERNAL ONLY
        typedef proto::tag::if_else_ proto_tag;
        /// INTERNAL ONLY
        typedef T proto_child0;
        /// INTERNAL ONLY
        typedef U proto_child1;
        /// INTERNAL ONLY
        typedef V proto_child2;
    };

    /// \brief A metafunction for generating nullary expression types with a
    /// specified tag type,
    /// a grammar element for matching nullary expressions, and a
    /// PrimitiveTransform that returns the current expression unchanged.
    ///
    /// Use <tt>nullary_expr\<_, _\></tt> as a grammar element to match any
    /// nullary expression.
    template<typename Tag, typename T>
    struct nullary_expr
      : proto::transform<nullary_expr<Tag, T>, int>
    {
        typedef proto::expr<Tag, term<T>, 0> type;
        typedef proto::basic_expr<Tag, term<T>, 0> proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param e The current expression
            /// \pre <tt>matches\<Expr, nullary_expr\<Tag, T\> \>::value</tt> is \c true.
            /// \return \c e
            /// \throw nothrow
            BOOST_FORCEINLINE
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::expr_param)
            operator ()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return e;
            }
        };

        /// INTERNAL ONLY
        typedef Tag proto_tag;
        /// INTERNAL ONLY
        typedef T proto_child0;
    };

    /// \brief A metafunction for generating unary expression types with a
    /// specified tag type,
    /// a grammar element for matching unary expressions, and a
    /// PrimitiveTransform that dispatches to the <tt>pass_through\<\></tt>
    /// transform.
    ///
    /// Use <tt>unary_expr\<_, _\></tt> as a grammar element to match any
    /// unary expression.
    template<typename Tag, typename T>
    struct unary_expr
      : proto::transform<unary_expr<Tag, T>, int>
    {
        typedef proto::expr<Tag, list1<T>, 1> type;
        typedef proto::basic_expr<Tag, list1<T>, 1> proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::pass_through_impl<unary_expr, deduce_domain, Expr, State, Data>
        {};

        /// INTERNAL ONLY
        typedef Tag proto_tag;
        /// INTERNAL ONLY
        typedef T proto_child0;
    };

    /// \brief A metafunction for generating binary expression types with a
    /// specified tag type,
    /// a grammar element for matching binary expressions, and a
    /// PrimitiveTransform that dispatches to the <tt>pass_through\<\></tt>
    /// transform.
    ///
    /// Use <tt>binary_expr\<_, _, _\></tt> as a grammar element to match any
    /// binary expression.
    template<typename Tag, typename T, typename U>
    struct binary_expr
      : proto::transform<binary_expr<Tag, T, U>, int>
    {
        typedef proto::expr<Tag, list2<T, U>, 2> type;
        typedef proto::basic_expr<Tag, list2<T, U>, 2> proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::pass_through_impl<binary_expr, deduce_domain, Expr, State, Data>
        {};

        /// INTERNAL ONLY
        typedef Tag proto_tag;
        /// INTERNAL ONLY
        typedef T proto_child0;
        /// INTERNAL ONLY
        typedef U proto_child1;
    };

#define BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(Op)                                               \
    template<typename T>                                                                        \
    struct Op                                                                                   \
      : proto::transform<Op<T>, int>                                                            \
    {                                                                                           \
        typedef proto::expr<proto::tag::Op, list1<T>, 1> type;                                  \
        typedef proto::basic_expr<proto::tag::Op, list1<T>, 1> proto_grammar;                   \
                                                                                                \
        template<typename Expr, typename State, typename Data>                                  \
        struct impl                                                                             \
          : detail::pass_through_impl<Op, deduce_domain, Expr, State, Data>                     \
        {};                                                                                     \
                                                                                                \
        typedef proto::tag::Op proto_tag;                                                       \
        typedef T proto_child0;                                                                 \
    };                                                                                          \
    /**/

#define BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(Op)                                              \
    template<typename T, typename U>                                                            \
    struct Op                                                                                   \
      : proto::transform<Op<T, U>, int>                                                         \
    {                                                                                           \
        typedef proto::expr<proto::tag::Op, list2<T, U>, 2> type;                               \
        typedef proto::basic_expr<proto::tag::Op, list2<T, U>, 2> proto_grammar;                \
                                                                                                \
        template<typename Expr, typename State, typename Data>                                  \
        struct impl                                                                             \
          : detail::pass_through_impl<Op, deduce_domain, Expr, State, Data>                     \
        {};                                                                                     \
                                                                                                \
        typedef proto::tag::Op proto_tag;                                                       \
        typedef T proto_child0;                                                                 \
        typedef U proto_child1;                                                                 \
    };                                                                                          \
    /**/

    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(unary_plus)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(negate)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(dereference)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(complement)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(address_of)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(logical_not)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(pre_inc)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(pre_dec)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(post_inc)
    BOOST_PROTO_DEFINE_UNARY_METAFUNCTION(post_dec)

    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(shift_left)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(shift_right)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(multiplies)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(divides)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(modulus)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(plus)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(minus)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(less)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(greater)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(less_equal)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(greater_equal)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(equal_to)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(not_equal_to)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(logical_or)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(logical_and)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(bitwise_or)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(bitwise_and)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(bitwise_xor)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(comma)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(mem_ptr)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(shift_left_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(shift_right_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(multiplies_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(divides_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(modulus_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(plus_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(minus_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(bitwise_or_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(bitwise_and_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(bitwise_xor_assign)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(subscript)
    BOOST_PROTO_DEFINE_BINARY_METAFUNCTION(member)

    #undef BOOST_PROTO_DEFINE_UNARY_METAFUNCTION
    #undef BOOST_PROTO_DEFINE_BINARY_METAFUNCTION

    #include <boost/proto/detail/traits.hpp>

    namespace functional
    {
        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c as_expr() function.
        template<typename Domain   /* = default_domain*/>
        struct as_expr
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename T>
            struct result<This(T)>
            {
                typedef typename Domain::template as_expr<T>::result_type type;
            };

            template<typename This, typename T>
            struct result<This(T &)>
            {
                typedef typename Domain::template as_expr<T>::result_type type;
            };

            /// \brief Wrap an object in a Proto terminal if it isn't a
            /// Proto expression already.
            /// \param t The object to wrap.
            /// \return <tt>proto::as_expr\<Domain\>(t)</tt>
            template<typename T>
            BOOST_FORCEINLINE
            typename add_const<typename result<as_expr(T &)>::type>::type
            operator ()(T &t) const
            {
                return typename Domain::template as_expr<T>()(t);
            }

            /// \overload
            ///
            template<typename T>
            BOOST_FORCEINLINE
            typename add_const<typename result<as_expr(T const &)>::type>::type
            operator ()(T const &t) const
            {
                return typename Domain::template as_expr<T const>()(t);
            }

            #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
            template<typename T, std::size_t N_>
            BOOST_FORCEINLINE
            typename add_const<typename result<as_expr(T (&)[N_])>::type>::type
            operator ()(T (&t)[N_]) const
            {
                return typename Domain::template as_expr<T[N_]>()(t);
            }

            template<typename T, std::size_t N_>
            BOOST_FORCEINLINE
            typename add_const<typename result<as_expr(T const (&)[N_])>::type>::type
            operator ()(T const (&t)[N_]) const
            {
                return typename Domain::template as_expr<T const[N_]>()(t);
            }
            #endif
        };

        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c as_child() function.
        template<typename Domain   /* = default_domain*/>
        struct as_child
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename T>
            struct result<This(T)>
            {
                typedef typename Domain::template as_child<T>::result_type type;
            };

            template<typename This, typename T>
            struct result<This(T &)>
            {
                typedef typename Domain::template as_child<T>::result_type type;
            };

            /// \brief Wrap an object in a Proto terminal if it isn't a
            /// Proto expression already.
            /// \param t The object to wrap.
            /// \return <tt>proto::as_child\<Domain\>(t)</tt>
            template<typename T>
            BOOST_FORCEINLINE
            typename add_const<typename result<as_child(T &)>::type>::type
            operator ()(T &t) const
            {
                return typename Domain::template as_child<T>()(t);
            }

            /// \overload
            ///
            template<typename T>
            BOOST_FORCEINLINE
            typename add_const<typename result<as_child(T const &)>::type>::type
            operator ()(T const &t) const
            {
                return typename Domain::template as_child<T const>()(t);
            }
        };

        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c child_c() function.
        template<long N>
        struct child_c
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef typename result_of::child_c<Expr, N>::type type;
            };

            /// \brief Return the Nth child of the given expression.
            /// \param expr The expression node.
            /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true
            /// \pre <tt>N \< Expr::proto_arity::value</tt>
            /// \return <tt>proto::child_c\<N\>(expr)</tt>
            /// \throw nothrow
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::child_c<Expr &, N>::type
            operator ()(Expr &e) const
            {
                return result_of::child_c<Expr &, N>::call(e);
            }

            /// \overload
            ///
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::child_c<Expr const &, N>::type
            operator ()(Expr const &e) const
            {
                return result_of::child_c<Expr const &, N>::call(e);
            }
        };

        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c child() function.
        ///
        /// A callable PolymorphicFunctionObject that is
        /// equivalent to the \c child() function. \c N is required
        /// to be an MPL Integral Constant.
        template<typename N /* = mpl::long_<0>*/>
        struct child
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef typename result_of::child<Expr, N>::type type;
            };

            /// \brief Return the Nth child of the given expression.
            /// \param expr The expression node.
            /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true
            /// \pre <tt>N::value \< Expr::proto_arity::value</tt>
            /// \return <tt>proto::child\<N\>(expr)</tt>
            /// \throw nothrow
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::child<Expr &, N>::type
            operator ()(Expr &e) const
            {
                return result_of::child<Expr &, N>::call(e);
            }

            /// \overload
            ///
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::child<Expr const &, N>::type
            operator ()(Expr const &e) const
            {
                return result_of::child<Expr const &, N>::call(e);
            }
        };

        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c value() function.
        struct value
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef typename result_of::value<Expr>::type type;
            };

            /// \brief Return the value of the given terminal expression.
            /// \param expr The terminal expression node.
            /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true
            /// \pre <tt>0 == Expr::proto_arity::value</tt>
            /// \return <tt>proto::value(expr)</tt>
            /// \throw nothrow
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::value<Expr &>::type
            operator ()(Expr &e) const
            {
                return e.proto_base().child0;
            }

            /// \overload
            ///
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::value<Expr const &>::type
            operator ()(Expr const &e) const
            {
                return e.proto_base().child0;
            }
        };

        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c left() function.
        struct left
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef typename result_of::left<Expr>::type type;
            };

            /// \brief Return the left child of the given binary expression.
            /// \param expr The expression node.
            /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true
            /// \pre <tt>2 == Expr::proto_arity::value</tt>
            /// \return <tt>proto::left(expr)</tt>
            /// \throw nothrow
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::left<Expr &>::type
            operator ()(Expr &e) const
            {
                return e.proto_base().child0;
            }

            /// \overload
            ///
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::left<Expr const &>::type
            operator ()(Expr const &e) const
            {
                return e.proto_base().child0;
            }
        };

        /// \brief A callable PolymorphicFunctionObject that is
        /// equivalent to the \c right() function.
        struct right
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef typename result_of::right<Expr>::type type;
            };

            /// \brief Return the right child of the given binary expression.
            /// \param expr The expression node.
            /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true
            /// \pre <tt>2 == Expr::proto_arity::value</tt>
            /// \return <tt>proto::right(expr)</tt>
            /// \throw nothrow
            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::right<Expr &>::type
            operator ()(Expr &e) const
            {
                return e.proto_base().child1;
            }

            template<typename Expr>
            BOOST_FORCEINLINE
            typename result_of::right<Expr const &>::type
            operator ()(Expr const &e) const
            {
                return e.proto_base().child1;
            }
        };

    }

    /// \brief A function that wraps non-Proto expression types in Proto
    /// terminals and leaves Proto expression types alone.
    ///
    /// The <tt>as_expr()</tt> function turns objects into Proto terminals if
    /// they are not Proto expression types already. Non-Proto types are
    /// held by value, if possible. Types which are already Proto types are
    /// left alone and returned by reference.
    ///
    /// This function can be called either with an explicitly specified
    /// \c Domain parameter (i.e., <tt>as_expr\<Domain\>(t)</tt>), or
    /// without (i.e., <tt>as_expr(t)</tt>). If no domain is
    /// specified, \c default_domain is assumed.
    ///
    /// If <tt>is_expr\<T\>::value</tt> is \c true, then the argument is
    /// returned unmodified, by reference. Otherwise, the argument is wrapped
    /// in a Proto terminal expression node according to the following rules.
    /// If \c T is a function type, let \c A be <tt>T &</tt>. Otherwise, let
    /// \c A be the type \c T stripped of cv-qualifiers. Then, \c as_expr()
    /// returns <tt>Domain()(terminal\<A\>::type::make(t))</tt>.
    ///
    /// \param t The object to wrap.
    template<typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_expr<T, default_domain>::type>::type
    as_expr(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T) BOOST_PROTO_DISABLE_IF_IS_FUNCTION(T))
    {
        return default_domain::as_expr<T>()(t);
    }

    /// \overload
    ///
    template<typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_expr<T const, default_domain>::type>::type
    as_expr(T const &t)
    {
        return default_domain::as_expr<T const>()(t);
    }

    /// \overload
    ///
    template<typename Domain, typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_expr<T, Domain>::type>::type
    as_expr(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T) BOOST_PROTO_DISABLE_IF_IS_FUNCTION(T))
    {
        return typename Domain::template as_expr<T>()(t);
    }

    /// \overload
    ///
    template<typename Domain, typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_expr<T const, Domain>::type>::type
    as_expr(T const &t)
    {
        return typename Domain::template as_expr<T const>()(t);
    }

    /// \brief A function that wraps non-Proto expression types in Proto
    /// terminals (by reference) and returns Proto expression types by
    /// reference
    ///
    /// The <tt>as_child()</tt> function turns objects into Proto terminals if
    /// they are not Proto expression types already. Non-Proto types are
    /// held by reference. Types which are already Proto types are simply
    /// returned as-is.
    ///
    /// This function can be called either with an explicitly specified
    /// \c Domain parameter (i.e., <tt>as_child\<Domain\>(t)</tt>), or
    /// without (i.e., <tt>as_child(t)</tt>). If no domain is
    /// specified, \c default_domain is assumed.
    ///
    /// If <tt>is_expr\<T\>::value</tt> is \c true, then the argument is
    /// returned as-is. Otherwise, \c as_child() returns
    /// <tt>Domain()(terminal\<T &\>::type::make(t))</tt>.
    ///
    /// \param t The object to wrap.
    template<typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_child<T, default_domain>::type>::type
    as_child(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T) BOOST_PROTO_DISABLE_IF_IS_FUNCTION(T))
    {
        return default_domain::as_child<T>()(t);
    }

    /// \overload
    ///
    template<typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_child<T const, default_domain>::type>::type
    as_child(T const &t)
    {
        return default_domain::as_child<T const>()(t);
    }

    /// \overload
    ///
    template<typename Domain, typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_child<T, Domain>::type>::type
    as_child(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T) BOOST_PROTO_DISABLE_IF_IS_FUNCTION(T))
    {
        return typename Domain::template as_child<T>()(t);
    }

    /// \overload
    ///
    template<typename Domain, typename T>
    BOOST_FORCEINLINE
    typename add_const<typename result_of::as_child<T const, Domain>::type>::type
    as_child(T const &t)
    {
        return typename Domain::template as_child<T const>()(t);
    }

    /// \brief Return the Nth child of the specified Proto expression.
    ///
    /// Return the Nth child of the specified Proto expression. If
    /// \c N is not specified, as in \c child(expr), then \c N is assumed
    /// to be <tt>mpl::long_\<0\></tt>. The child is returned by
    /// reference.
    ///
    /// \param expr The Proto expression.
    /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true.
    /// \pre \c N is an MPL Integral Constant.
    /// \pre <tt>N::value \< Expr::proto_arity::value</tt>
    /// \throw nothrow
    /// \return A reference to the Nth child
    template<typename N, typename Expr>
    BOOST_FORCEINLINE
    typename result_of::child<Expr &, N>::type
    child(Expr &e BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
    {
        return result_of::child<Expr &, N>::call(e);
    }

    /// \overload
    ///
    template<typename N, typename Expr>
    BOOST_FORCEINLINE
    typename result_of::child<Expr const &, N>::type
    child(Expr const &e)
    {
        return result_of::child<Expr const &, N>::call(e);
    }

    /// \overload
    ///
    template<typename Expr2>
    BOOST_FORCEINLINE
    typename detail::expr_traits<typename Expr2::proto_base_expr::proto_child0>::reference
    child(Expr2 &expr2 BOOST_PROTO_DISABLE_IF_IS_CONST(Expr2))
    {
        return expr2.proto_base().child0;
    }

    /// \overload
    ///
    template<typename Expr2>
    BOOST_FORCEINLINE
    typename detail::expr_traits<typename Expr2::proto_base_expr::proto_child0>::const_reference
    child(Expr2 const &expr2)
    {
        return expr2.proto_base().child0;
    }

    /// \brief Return the Nth child of the specified Proto expression.
    ///
    /// Return the Nth child of the specified Proto expression. The child
    /// is returned by reference.
    ///
    /// \param expr The Proto expression.
    /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true.
    /// \pre <tt>N \< Expr::proto_arity::value</tt>
    /// \throw nothrow
    /// \return A reference to the Nth child
    template<long N, typename Expr>
    BOOST_FORCEINLINE
    typename result_of::child_c<Expr &, N>::type
    child_c(Expr &e BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
    {
        return result_of::child_c<Expr &, N>::call(e);
    }

    /// \overload
    ///
    template<long N, typename Expr>
    BOOST_FORCEINLINE
    typename result_of::child_c<Expr const &, N>::type
    child_c(Expr const &e)
    {
        return result_of::child_c<Expr const &, N>::call(e);
    }

    /// \brief Return the value stored within the specified Proto
    /// terminal expression.
    ///
    /// Return the value stored within the specified Proto
    /// terminal expression. The value is returned by
    /// reference.
    ///
    /// \param expr The Proto terminal expression.
    /// \pre <tt>N::value == 0</tt>
    /// \throw nothrow
    /// \return A reference to the terminal's value
    template<typename Expr>
    BOOST_FORCEINLINE
    typename result_of::value<Expr &>::type
    value(Expr &e BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
    {
        return e.proto_base().child0;
    }

    /// \overload
    ///
    template<typename Expr>
    BOOST_FORCEINLINE
    typename result_of::value<Expr const &>::type
    value(Expr const &e)
    {
        return e.proto_base().child0;
    }

    /// \brief Return the left child of the specified binary Proto
    /// expression.
    ///
    /// Return the left child of the specified binary Proto expression. The
    /// child is returned by reference.
    ///
    /// \param expr The Proto expression.
    /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true.
    /// \pre <tt>2 == Expr::proto_arity::value</tt>
    /// \throw nothrow
    /// \return A reference to the left child
    template<typename Expr>
    BOOST_FORCEINLINE
    typename result_of::left<Expr &>::type
    left(Expr &e BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
    {
        return e.proto_base().child0;
    }

    /// \overload
    ///
    template<typename Expr>
    BOOST_FORCEINLINE
    typename result_of::left<Expr const &>::type
    left(Expr const &e)
    {
        return e.proto_base().child0;
    }

    /// \brief Return the right child of the specified binary Proto
    /// expression.
    ///
    /// Return the right child of the specified binary Proto expression. The
    /// child is returned by reference.
    ///
    /// \param expr The Proto expression.
    /// \pre <tt>is_expr\<Expr\>::value</tt> is \c true.
    /// \pre <tt>2 == Expr::proto_arity::value</tt>
    /// \throw nothrow
    /// \return A reference to the right child
    template<typename Expr>
    BOOST_FORCEINLINE
    typename result_of::right<Expr &>::type
    right(Expr &e BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
    {
        return e.proto_base().child1;
    }

    /// \overload
    ///
    template<typename Expr>
    BOOST_FORCEINLINE
    typename result_of::right<Expr const &>::type
    right(Expr const &e)
    {
        return e.proto_base().child1;
    }

    /// INTERNAL ONLY
    ///
    template<typename Domain>
    struct is_callable<functional::as_expr<Domain> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Domain>
    struct is_callable<functional::as_child<Domain> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<long N>
    struct is_callable<functional::child_c<N> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename N>
    struct is_callable<functional::child<N> >
      : mpl::true_
    {};

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* traits.hpp
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
*/