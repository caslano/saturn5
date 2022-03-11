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
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
*/