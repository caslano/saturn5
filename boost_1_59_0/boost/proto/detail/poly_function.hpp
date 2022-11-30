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

        BOOST_DELETED_FUNCTION(arg &operator =(arg const &))
    private:
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

        BOOST_DELETED_FUNCTION(arg &operator =(arg const &))
    private:
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
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
*/