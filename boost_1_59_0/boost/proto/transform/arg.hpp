///////////////////////////////////////////////////////////////////////////////
/// \file arg.hpp
/// Contains definition of the argN transforms.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_11_01_2007
#define BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_11_01_2007

#include <boost/mpl/if.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/proto/transform/env.hpp>

namespace boost { namespace proto
{

    /// \brief A PrimitiveTransform that returns the current expression
    /// unmodified
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// proto::terminal<int>::type & j = proto::_expr()(i);
    /// assert( boost::addressof(i) == boost::addressof(j) );
    /// \endcode
    struct _expr : transform<_expr>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// Returns the current expression.
            /// \param e The current expression.
            /// \return \c e
            /// \throw nothrow
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::expr_param)
            operator()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return e;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns the current state
    /// unmodified
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// char ch = proto::_state()(i, 'a');
    /// assert( ch == 'a' );
    /// \endcode
    struct _state : transform<_state>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef State result_type;

            /// Returns the current state.
            /// \param s The current state.
            /// \return \c s
            /// \throw nothrow
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::state_param)
            operator ()(
                typename impl::expr_param
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return s;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns the current data
    /// unmodified
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// std::string str("hello");
    /// std::string & data = proto::_data()(i, 'a', str);
    /// assert( &str == &data );
    /// \endcode
    struct _data : transform<_data>
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : mpl::if_c<
                is_env<Data>::value
              , _env_var<data_type>
              , _env
            >::type::template impl<Expr, State, Data>
        {};
    };

    /// \brief A PrimitiveTransform that returns N-th child of the current
    /// expression.
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// proto::terminal<int>::type & j = proto::_child_c<0>()(-i);
    /// assert( boost::addressof(i) == boost::addressof(j) );
    /// \endcode
    template<int N>
    struct _child_c : transform<_child_c<N> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef
                typename result_of::child_c<Expr, N>::type
            result_type;

            /// Returns the N-th child of \c e
            /// \pre <tt>arity_of\<Expr\>::value \> N</tt> 
            /// \param e The current expression.
            /// \return <tt>proto::child_c\<N\>(e)</tt>
            /// \throw nothrow
            #ifdef BOOST_PROTO_STRICT_RESULT_OF
            result_type
            #else
            typename result_of::child_c<typename impl::expr_param, N>::type
            #endif
            operator ()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return proto::child_c<N>(e);
            }
        };
    };

    /// \brief A PrimitiveTransform that returns the value of the
    /// current terminal expression.
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// int j = proto::_value()(i);
    /// assert( 42 == j );
    /// \endcode
    struct _value : transform<_value>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef
                typename result_of::value<Expr>::type
            result_type;

            /// Returns the value of the specified terminal expression.
            /// \pre <tt>arity_of\<Expr\>::value == 0</tt>.
            /// \param e The current expression.
            /// \return <tt>proto::value(e)</tt>
            /// \throw nothrow
            #ifdef BOOST_PROTO_STRICT_RESULT_OF
            typename mpl::if_c<is_array<result_type>::value, result_type &, result_type>::type
            #else
            typename result_of::value<typename impl::expr_param>::type
            #endif
            operator ()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return proto::value(e);
            }
        };
    };

    /// \brief A PrimitiveTransform that does nothing
    /// and returns void.
    struct _void : transform<_void>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef void result_type;

            /// Does nothing and returns void
            void operator ()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {}
        };
    };

    /// \brief A unary CallableTransform that wraps its argument
    /// in a \c boost::reference_wrapper\<\>.
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// boost::reference_wrapper<proto::terminal<int>::type> j
    ///     = proto::when<_, proto::_byref(_)>()(i);
    /// assert( boost::addressof(i) == boost::addressof(j.get()) );
    /// \endcode
    struct _byref : callable
    {
        template<typename Sig>
        struct result;

        template<typename This, typename T>
        struct result<This(T)>
        {
            typedef boost::reference_wrapper<T const> const type;
        };

        template<typename This, typename T>
        struct result<This(T &)>
        {
            typedef boost::reference_wrapper<T> const type;
        };

        /// Wrap the parameter \c t in a \c boost::reference_wrapper\<\>
        /// \param t The object to wrap
        /// \return <tt>boost::ref(t)</tt>
        /// \throw nothrow
        template<typename T>
        boost::reference_wrapper<T> const operator ()(T &t) const
        {
            return boost::reference_wrapper<T>(t);
        }

        /// \overload
        ///
        template<typename T>
        boost::reference_wrapper<T const> const operator ()(T const &t) const
        {
            return boost::reference_wrapper<T const>(t);
        }
    };

    /// \brief A unary CallableTransform that strips references
    /// and \c boost::reference_wrapper\<\> from its argument.
    ///
    /// Example:
    ///
    /// \code
    /// proto::terminal<int>::type i = {42};
    /// int j = 67;
    /// int k = proto::when<_, proto::_byval(proto::_state)>()(i, boost::ref(j));
    /// assert( 67 == k );
    /// \endcode
    struct _byval : callable
    {
        template<typename Sig>
        struct result;

        template<typename This, typename T>
        struct result<This(T)>
        {
            typedef T type;
        };

        template<typename This, typename T>
        struct result<This(T &)>
          : result<This(T)>
        {};

        template<typename This, typename T>
        struct result<This(boost::reference_wrapper<T>)>
          : result<This(T)>
        {};

        /// \param t The object to unref
        /// \return <tt>t</tt>
        /// \throw nothrow
        template<typename T>
        T operator ()(T const &t) const
        {
            return t;
        }

        /// \overload
        ///
        template<typename T>
        T operator ()(boost::reference_wrapper<T> const &t) const
        {
            return t;
        }
    };

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_expr>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_state>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_data>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<int N>
    struct is_callable<_child_c<N> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_value>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_byref>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_byval>
      : mpl::true_
    {};

}}

#endif

/* arg.hpp
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
*/