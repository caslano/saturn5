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