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
WHvR/6YHf/T5aumif+469Xeer4bnDl8rzl70n7tWXLHQH3veStfsu/9mL35k707joyzuAI4/uwkQIGg4BOQMh4IcIUFERKrhkENAAwIKRJPNZkkCyWbZ3QQiSKP1xKMIeNQz3tYTVLyQCt5WbYMnigdgrdYTtFYrHv3t5jmGf3aHJ0jbN/BxTXa/+8zMM8/MPDPzzPMkeT7svd/6flv35ys3/daGdqFp56xW7f5/+5/T7n+z/7o+wxlNSMP+Hrec34S492X/7eOepE18IPmxJ8xff/wT9F3V+OPp2dpuz3aZuElv09vlhraw6XOlzdv/98r/3s5JWe2bdk6a1b7p5yW354SLfmU+6M4J8vw0DCdswo2HFY9/HfGTPuKw55kIg7DN/bXCJe2kYY90sh+kw0zPneb5hzitPhRpd1cW3v2VeaDbf/Kb7+yRFsKR8dnbx9PTskM8DLPPIPqFZn+BOElLPD7SQvqUeT3SznHhs4z4WIP9dNIztEPD/i/pQPo1fftnOuy/87XuXL2LeHpzaSuf1wpem3h9w6tXR8OYzKua19283uTVnLVDR/Mq5XU9L7aJf/YKr+95Wdsd0ZnweRF2PIyLOjeE86YZ1hOdG8IhPsIhfjPezzvzO2uJTjt039J18aGx8PZt203mtl+b8R/RRaYDt/fR3tYMb9/iPKNLLMy9x3Fpl18XzwaX8Xxhx7P37yb6Xu+uSb7b1X245yjffYzfv+WV1S2+jVq+7LJXghGvWs7ssremm50Xdln7iM8OZoXWGF7kXbwsLuH3V7Bb+bmDV+cehnEyryt7NIT9Ej89Pfcs76N6uivvFXzv5p7acs9nyfdvS8+k+xfflzaZ9v4k2F+5j7q4mpaPVrivaMIbl7nvYS7OTB7u/b8i3GT2WaZ+X9Zoytm8kfnFxfnV/mhlZXkk3x+O8nsk6gtHq0L5kbA/v7wsuKAyFI3kRwJ8WlKd5Q+FjOKR+ZWhQDBSWRX2Bxp+jZQPzsnKycqel18RyfeFQrHtsvyGf2R+KFxZEvZVZM4rKw9EMvsvHjH8iPxFZcHiykWRzAVlhJyTnV8W9JdXFQf4NSs7K+eo7OFHZmXnV8VSE4kWl1Vmlf76gPyV4QA/Cxbt9xDjARb4K4Pzykr2R7iRaLgsuF9CslJYEajwh2oKIvsa5rAjj4mFGSn1hQPFse8GwuHKMKHpCoIZhv1xPhvtnwQU+SiMkeKmxh9a4I8c3dSNFh+VfUxTt6kq29f9TFJgzfKgTQR1LtKQWn/TUltEbWjiDvrDNaHofqlD0bKKwP4Ix86sXxPgnqWMbPeVl5UEm5o5sWNQUD2vpqnblZf6IqVZbo5ybM8iWU0MvtIfCTV1m9iuVB/5K7OzqiL2vWC0qZH7IsGcfY16j6IRrQntc5FQA6rwlZdX+pu6GxHfvAAnVP+CfU2Cko2RoVF/qCz0K0MyyzehlYWKA/OaukOc6Jq8TXRxtKC46Femu6EgxRr/LDe1hO8eObSgLFgW3dd+iBMv2/oDkUi0NBzwFUd8oTJXKagOhCNllcEsv7vvls2rcfXVaCSriU18dK+tRTzgSDjU1JAj4b02Kg1Bhxb4/Flu9i4SCgSKXX0zSr3iYOxrqUrYUfJF3TXBkYrYeaaJmeXfaxvYEDYlraBsr3kgQ+e1f7IiuH+7x4sIce9djIY9L4i6yFbzq5FK/4JA1O2XA2Fq2K9vCPheLN6hLnfHX14WCLpNo7/I1RfDEV9VtNztV919L7DQ5fdifRR3X/UF91qCzc6M20MeWhCocbvnse+GfBxl1992+UV/ZERWEytmbKMcdyWmYYjiNiU5Q9191ReJLHJ3MCpD7gprw2fuDgUdz70=
*/