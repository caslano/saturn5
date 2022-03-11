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