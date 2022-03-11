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