///////////////////////////////////////////////////////////////////////////////
/// \file call.hpp
/// Contains definition of the call<> transform.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_CALL_HPP_EAN_11_02_2007
#define BOOST_PROTO_TRANSFORM_CALL_HPP_EAN_11_02_2007

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable: 4714) // function 'xxx' marked as __forceinline not inlined
#endif

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/ref.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/detail/as_lvalue.hpp>
#include <boost/proto/detail/poly_function.hpp>
#include <boost/proto/transform/detail/pack.hpp>

namespace boost { namespace proto
{
    /// \brief Wrap \c PrimitiveTransform so that <tt>when\<\></tt> knows
    /// it is callable. Requires that the parameter is actually a
    /// PrimitiveTransform.
    ///
    /// This form of <tt>call\<\></tt> is useful for annotating an
    /// arbitrary PrimitiveTransform as callable when using it with
    /// <tt>when\<\></tt>. Consider the following transform, which
    /// is parameterized with another transform.
    ///
    /// \code
    /// template<typename Grammar>
    /// struct Foo
    ///   : when<
    ///         unary_plus<Grammar>
    ///       , Grammar(_child)   // May or may not work.
    ///     >
    /// {};
    /// \endcode
    ///
    /// The problem with the above is that <tt>when\<\></tt> may or
    /// may not recognize \c Grammar as callable, depending on how
    /// \c Grammar is implemented. (See <tt>is_callable\<\></tt> for
    /// a discussion of this issue.) You can guard against
    /// the issue by wrapping \c Grammar in <tt>call\<\></tt>, such
    /// as:
    ///
    /// \code
    /// template<typename Grammar>
    /// struct Foo
    ///   : when<
    ///         unary_plus<Grammar>
    ///       , call<Grammar>(_child)   // OK, this works
    ///     >
    /// {};
    /// \endcode
    ///
    /// The above could also have been written as:
    ///
    /// \code
    /// template<typename Grammar>
    /// struct Foo
    ///   : when<
    ///         unary_plus<Grammar>
    ///       , call<Grammar(_child)>   // OK, this works, too
    ///     >
    /// {};
    /// \endcode
    template<typename PrimitiveTransform>
    struct call
      : PrimitiveTransform
    {};

    /// \brief A specialization that treats function pointer Transforms as
    /// if they were function type Transforms.
    ///
    /// This specialization requires that \c Fun is actually a function type.
    ///
    /// This specialization is required for nested transforms such as
    /// <tt>call\<T0(T1(_))\></tt>. In C++, functions that are used as
    /// parameters to other functions automatically decay to funtion
    /// pointer types. In other words, the type <tt>T0(T1(_))</tt> is
    /// indistinguishable from <tt>T0(T1(*)(_))</tt>. This specialization
    /// is required to handle these nested function pointer type transforms
    /// properly.
    template<typename Fun>
    struct call<Fun *>
      : call<Fun>
    {};

    /// INTERNAL ONLY
    template<typename Fun>
    struct call<detail::msvc_fun_workaround<Fun> >
      : call<Fun>
    {};

    /// \brief Either call the PolymorphicFunctionObject with 0
    /// arguments, or invoke the PrimitiveTransform with 3
    /// arguments.
    template<typename Fun>
    struct call<Fun()> : transform<call<Fun()> >
    {
        /// INTERNAL ONLY
        template<typename Expr, typename State, typename Data, bool B>
        struct impl2
          : transform_impl<Expr, State, Data>
        {
            typedef typename BOOST_PROTO_RESULT_OF<Fun()>::type result_type;

            BOOST_FORCEINLINE
            result_type operator()(
                typename impl2::expr_param
              , typename impl2::state_param
              , typename impl2::data_param
            ) const
            {
                return Fun()();
            }
        };

        /// INTERNAL ONLY
        template<typename Expr, typename State, typename Data>
        struct impl2<Expr, State, Data, true>
          : Fun::template impl<Expr, State, Data>
        {};

        /// Either call the PolymorphicFunctionObject \c Fun with 0 arguments; or
        /// invoke the PrimitiveTransform \c Fun with 3 arguments: the current
        /// expression, state, and data.
        ///
        /// If \c Fun is a nullary PolymorphicFunctionObject, return <tt>Fun()()</tt>.
        /// Otherwise, return <tt>Fun()(e, s, d)</tt>.
        ///
        /// \param e The current expression
        /// \param s The current state
        /// \param d An arbitrary data

        /// If \c Fun is a nullary PolymorphicFunctionObject, \c type is a typedef
        /// for <tt>boost::result_of\<Fun()\>::type</tt>. Otherwise, it is
        /// a typedef for <tt>boost::result_of\<Fun(Expr, State, Data)\>::type</tt>.
        template<typename Expr, typename State, typename Data>
        struct impl
          : impl2<Expr, State, Data, detail::is_transform_<Fun>::value>
        {};
    };

    /// \brief Either call the PolymorphicFunctionObject with 1
    /// argument, or invoke the PrimitiveTransform with 3
    /// arguments.
    template<typename Fun, typename A0>
    struct call<Fun(A0)> : transform<call<Fun(A0)> >
    {
        template<typename Expr, typename State, typename Data, bool B>
        struct impl2
          : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data>::result_type a0;
            typedef typename detail::poly_function_traits<Fun, Fun(a0)>::result_type result_type;
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl2::expr_param   e
              , typename impl2::state_param  s
              , typename impl2::data_param   d
            ) const
            {
                return typename detail::poly_function_traits<Fun, Fun(a0)>::function_type()(
                    detail::as_lvalue(typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d))
                );
            }
        };

        template<typename Expr, typename State, typename Data>
        struct impl2<Expr, State, Data, true>
          : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data>::result_type a0;
            typedef typename Fun::template impl<a0, State, Data>::result_type result_type;
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl2::expr_param   e
              , typename impl2::state_param  s
              , typename impl2::data_param   d
            ) const
            {
                return typename Fun::template impl<a0, State, Data>()(
                    typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d)
                  , s
                  , d
                );
            }
        };
        /// Let \c x be <tt>when\<_, A0\>()(e, s, d)</tt> and \c X
        /// be the type of \c x.
        /// If \c Fun is a unary PolymorphicFunctionObject that accepts \c x,
        /// then \c type is a typedef for <tt>boost::result_of\<Fun(X)\>::type</tt>.
        /// Otherwise, it is a typedef for <tt>boost::result_of\<Fun(X, State, Data)\>::type</tt>.

        /// Either call the PolymorphicFunctionObject with 1 argument:
        /// the result of applying the \c A0 transform; or
        /// invoke the PrimitiveTransform with 3 arguments:
        /// result of applying the \c A0 transform, the state, and the
        /// data.
        ///
        /// Let \c x be <tt>when\<_, A0\>()(e, s, d)</tt>.
        /// If \c Fun is a unary PolymorphicFunctionObject that accepts \c x,
        /// then return <tt>Fun()(x)</tt>. Otherwise, return
        /// <tt>Fun()(x, s, d)</tt>.
        ///
        /// \param e The current expression
        /// \param s The current state
        /// \param d An arbitrary data
        template<typename Expr, typename State, typename Data>
        struct impl
          : impl2<Expr, State, Data, detail::is_transform_<Fun>::value>
        {};
    };

    /// \brief Either call the PolymorphicFunctionObject with 2
    /// arguments, or invoke the PrimitiveTransform with 3
    /// arguments.
    template<typename Fun, typename A0, typename A1>
    struct call<Fun(A0, A1)> : transform<call<Fun(A0, A1)> >
    {
        template<typename Expr, typename State, typename Data, bool B>
        struct impl2
          : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data>::result_type a0;
            typedef typename when<_, A1>::template impl<Expr, State, Data>::result_type a1;
            typedef typename detail::poly_function_traits<Fun, Fun(a0, a1)>::result_type result_type;
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl2::expr_param   e
              , typename impl2::state_param  s
              , typename impl2::data_param   d
            ) const
            {
                return typename detail::poly_function_traits<Fun, Fun(a0, a1)>::function_type()(
                    detail::as_lvalue(typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d))
                  , detail::as_lvalue(typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d))
                );
            }
        };

        template<typename Expr, typename State, typename Data>
        struct impl2<Expr, State, Data, true>
          : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data>::result_type a0;
            typedef typename when<_, A1>::template impl<Expr, State, Data>::result_type a1;
            typedef typename Fun::template impl<a0, a1, Data>::result_type result_type;
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl2::expr_param   e
              , typename impl2::state_param  s
              , typename impl2::data_param   d
            ) const
            {
                return typename Fun::template impl<a0, a1, Data>()(
                    typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d)
                  , typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d)
                  , d
                );
            }
        };

            /// Let \c x be <tt>when\<_, A0\>()(e, s, d)</tt> and \c X
            /// be the type of \c x.
            /// Let \c y be <tt>when\<_, A1\>()(e, s, d)</tt> and \c Y
            /// be the type of \c y.
            /// If \c Fun is a binary PolymorphicFunction object that accepts \c x
            /// and \c y, then \c type is a typedef for
            /// <tt>boost::result_of\<Fun(X, Y)\>::type</tt>. Otherwise, it is
            /// a typedef for <tt>boost::result_of\<Fun(X, Y, Data)\>::type</tt>.

        /// Either call the PolymorphicFunctionObject with 2 arguments:
        /// the result of applying the \c A0 transform, and the
        /// result of applying the \c A1 transform; or invoke the
        /// PrimitiveTransform with 3 arguments: the result of applying
        /// the \c A0 transform, the result of applying the \c A1
        /// transform, and the data.
        ///
        /// Let \c x be <tt>when\<_, A0\>()(e, s, d)</tt>.
        /// Let \c y be <tt>when\<_, A1\>()(e, s, d)</tt>.
        /// If \c Fun is a binary PolymorphicFunction object that accepts \c x
        /// and \c y, return <tt>Fun()(x, y)</tt>. Otherwise, return
        /// <tt>Fun()(x, y, d)</tt>.
        ///
        /// \param e The current expression
        /// \param s The current state
        /// \param d An arbitrary data
        template<typename Expr, typename State, typename Data>
        struct impl
          : impl2<Expr, State, Data, detail::is_transform_<Fun>::value>
        {};
    };

    /// \brief Call the PolymorphicFunctionObject or the
    /// PrimitiveTransform with the current expression, state
    /// and data, transformed according to \c A0, \c A1, and
    /// \c A2, respectively.
    template<typename Fun, typename A0, typename A1, typename A2>
    struct call<Fun(A0, A1, A2)> : transform<call<Fun(A0, A1, A2)> >
    {
        template<typename Expr, typename State, typename Data, bool B>
        struct impl2
          : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data>::result_type a0;
            typedef typename when<_, A1>::template impl<Expr, State, Data>::result_type a1;
            typedef typename when<_, A2>::template impl<Expr, State, Data>::result_type a2;
            typedef typename detail::poly_function_traits<Fun, Fun(a0, a1, a2)>::result_type result_type;
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl2::expr_param   e
              , typename impl2::state_param  s
              , typename impl2::data_param   d
            ) const
            {
                return typename detail::poly_function_traits<Fun, Fun(a0, a1, a2)>::function_type()(
                    detail::as_lvalue(typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d))
                  , detail::as_lvalue(typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d))
                  , detail::as_lvalue(typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d))
                );
            }
        };

        template<typename Expr, typename State, typename Data>
        struct impl2<Expr, State, Data, true>
          : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data>::result_type a0;
            typedef typename when<_, A1>::template impl<Expr, State, Data>::result_type a1;
            typedef typename when<_, A2>::template impl<Expr, State, Data>::result_type a2;
            typedef typename Fun::template impl<a0, a1, a2>::result_type result_type;
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl2::expr_param   e
              , typename impl2::state_param  s
              , typename impl2::data_param   d
            ) const
            {
                return typename Fun::template impl<a0, a1, a2>()(
                    typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d)
                  , typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d)
                  , typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d)
                );
            }
        };

        /// Let \c x be <tt>when\<_, A0\>()(e, s, d)</tt>.
        /// Let \c y be <tt>when\<_, A1\>()(e, s, d)</tt>.
        /// Let \c z be <tt>when\<_, A2\>()(e, s, d)</tt>.
        /// Return <tt>Fun()(x, y, z)</tt>.
        ///
        /// \param e The current expression
        /// \param s The current state
        /// \param d An arbitrary data

        template<typename Expr, typename State, typename Data>
        struct impl
          : impl2<Expr, State, Data, detail::is_transform_<Fun>::value>
        {};
    };

    #include <boost/proto/transform/detail/call.hpp>

    /// INTERNAL ONLY
    ///
    template<typename Fun>
    struct is_callable<call<Fun> >
      : mpl::true_
    {};

}} // namespace boost::proto

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* call.hpp
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
*/