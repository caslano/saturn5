///////////////////////////////////////////////////////////////////////////////
/// \file poly_function.hpp
/// A wrapper that makes a tr1-style function object that handles const
/// and non-const refs and reference_wrapper arguments, too, and forwards
/// the arguments on to the specified implementation.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_POLY_FUNCTION_EAN_2008_05_02
#define BOOST_PROTO_DETAIL_POLY_FUNCTION_EAN_2008_05_02

#include <boost/ref.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/is_noncopyable.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4181) // const applied to reference type
#endif

namespace boost { namespace proto { namespace detail
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct normalize_arg
    {
        typedef typename mpl::if_c<is_noncopyable<T>::value, T &, T>::type type;
        typedef T &reference;
    };

    template<typename T>
    struct normalize_arg<T const>
    {
        typedef typename mpl::if_c<is_noncopyable<T>::value, T const &, T>::type type;
        typedef T const &reference;
    };

    template<typename T>
    struct normalize_arg<T &>
    {
        typedef typename mpl::if_c<is_noncopyable<T>::value, T &, T>::type type;
        typedef T &reference;
    };

    template<typename T>
    struct normalize_arg<T const &>
    {
        typedef typename mpl::if_c<is_noncopyable<T>::value, T const &, T>::type type;
        typedef T const &reference;
    };

    template<typename T>
    struct normalize_arg<boost::reference_wrapper<T> >
    {
        typedef T &type;
        typedef T &reference;
    };

    template<typename T>
    struct normalize_arg<boost::reference_wrapper<T> const>
    {
        typedef T &type;
        typedef T &reference;
    };

    template<typename T>
    struct normalize_arg<boost::reference_wrapper<T> &>
    {
        typedef T &type;
        typedef T &reference;
    };

    template<typename T>
    struct normalize_arg<boost::reference_wrapper<T> const &>
    {
        typedef T &type;
        typedef T &reference;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct arg
    {
        typedef T const &type;

        arg(type t)
          : value(t)
        {}

        operator type() const
        {
            return this->value;
        }

        type operator()() const
        {
            return this->value;
        }

    private:
        arg &operator =(arg const &);
        type value;
    };

    template<typename T>
    struct arg<T &>
    {
        typedef T &type;

        arg(type t)
          : value(t)
        {}

        operator type() const
        {
            return this->value;
        }

        type operator()() const
        {
            return this->value;
        }

    private:
        arg &operator =(arg const &);
        type value;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Void = void>
    struct is_poly_function
      : mpl::false_
    {};

    template<typename T>
    struct is_poly_function<T, typename T::is_poly_function_base_>
      : mpl::true_
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    #define BOOST_PROTO_POLY_FUNCTION()                                                             \
        typedef void is_poly_function_base_;                                                        \
        /**/

    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct poly_function_base
    {
        /// INTERNAL ONLY
        BOOST_PROTO_POLY_FUNCTION()
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Derived, typename NullaryResult = void>
    struct poly_function
      : poly_function_base
    {
        template<typename Sig>
        struct result;

        template<typename This>
        struct result<This()>
          : Derived::template impl<>
        {
            typedef typename result::result_type type;
        };

        NullaryResult operator()() const
        {
            result<Derived const()> impl;
            return impl();
        }

        #include <boost/proto/detail/poly_function_funop.hpp>
    };

    template<typename T>
    struct wrap_t;

    typedef char poly_function_t;
    typedef char (&mono_function_t)[2];
    typedef char (&unknown_function_t)[3];

    template<typename T> poly_function_t test_poly_function(T *, wrap_t<typename T::is_poly_function_base_> * = 0);
    template<typename T> mono_function_t test_poly_function(T *, wrap_t<typename T::result_type> * = 0);
    template<typename T> unknown_function_t test_poly_function(T *, ...);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Fun, typename Sig, typename Switch = mpl::size_t<sizeof(test_poly_function<Fun>(0,0))> >
    struct poly_function_traits
    {
        typedef typename Fun::template result<Sig>::type result_type;
        typedef Fun function_type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Fun, typename Sig>
    struct poly_function_traits<Fun, Sig, mpl::size_t<sizeof(mono_function_t)> >
    {
        typedef typename Fun::result_type result_type;
        typedef Fun function_type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFunSig, bool IsPolyFunction>
    struct as_mono_function_impl;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFunSig>
    struct as_mono_function;

    #include <boost/proto/detail/poly_function_traits.hpp>

}}} // namespace boost::proto::detail

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif


/* poly_function.hpp
7X+Jnvm/nbe/8v37j/0/We+u88dF2KmJ+dREqzmkrjeuiar+9a9K3bHm6Jf4+7zKCBPBxDpZciaQ/NJs4kK140O1ieg3DRzcIhPmbw7pjZtsXDxFAd9r0V4nipgnNVpYkM5em5OsxktYzIUmizxhyf5lbUvo3rLpl7HsBOXdg8mk28V41lKa0+H4OHTywmlL53EUDql+pPgYfK4mATWVL+Njj2MkzItUEu8GZ0yYOq2sgMLkmV4+VBpsElZ4OFMfOgHxdFDZ0FMDxno/bj9ty6m3/FWNBlnPOOpLjvALVYgMZHFU9qcO/07Cto5VjCM/bFHjcUHToqke/mJm7ODlu1FORNl12LSMPS46qvwuc17SgeTVsdi9QvTuX6SMI8mixGSkixNA8qvBADM6I1z/Cu40WxxfZ2m7NU9o8Xa0evY7JhkjHaNuBVMmMH5nouO1W2PnjtV9Dva4FqLyzu71lvkp2GhI6fMZ2OPZAwnjX87Fgt0AjHiua16n8mHvt0SjV2dnvGidTvU/7Wa+KD4uNdc8bO4BIFtHujP34qDzSqm617AbuAPKhDeiBX8FYqmAcNyaQNT11PWcFfbHQXLBwopAYXAb82VDZs1Y2gVSByTy6udf9CSuX4bPkfI9qUGpgakBNZ896FikOwMLoTWoHT0VvVY9mgE1b8AYOmh68t42+AsBNSggbD2Magxe/6UK4EY4YBtnm+5S6pLu
*/