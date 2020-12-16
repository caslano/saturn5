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
uChL1jo/lDwe629GLMbcqnmSVKbA9sET6xKXnAc7rowbeBfstXOV5MpKXvX5+G5G98RniGOM1otyZF/9Z8qzYmmhEqPyuOK024NefNRXKeM6q5pMVqSv8I5HNBtjHve8b8wjN9bm3PZ82eMSHfeywbULeaBvs1LVSeTDOx+309dfjoLPtMs+Qi2oYrbtgfx2KT+RM5WmueI1uXuNvNuGzteaW/GiHCJ+b474pUw1SWKVVR2/zevGh4dtmYJJQdAGQ3fpXX99gfIzYIYptA22y+uNf8AOMoeD4FOfprsoal6WSWlY27g16Ha7Y4q0oXkPgg8pmu5s3tRa1mXOto6Ou7gBwYcUxa7XpWyteNLh3pIYA7+L+t4wzU2uVZOzDQgGDj2D7/7zSl1zVYrHgMC5e8P70bqZzPJUNQ1Ljt3jxVGnqLiN5bwtxZ+17W5XKC8d6uuw3JViK5aWha4KJZhpDLhsBwdqC74HHkHTiIxxldQ6FznL3VMrXb28rwj4FX1F4OUjGkNbET/JhCyLCnzlKnia/e/MtsEBCLlDvyDiB7GpyoQXiWC6+Z+YEV8uLMTxul8cBzKxltemvV26jjvt/rQppgXumxQvDdO6qNPKKLbVWkzMQLg3BI+aV45dDf270LQNRnmM/vGe+GQ8d0W8alZYnmZNlbHh1HVp5H3kjA98P19T4C+oYbulCU6ANfx1cpgH4b52f3rm5TZLtDWNkwPO7U4Q95AIl9VVyrlhz/cweNvBcUFxF01elSYtFRsegn+Fzp/BHo7TCxR/XtTgykdrhuKpaD9iEVaVtamFCl5545i5OWLRt3iqE2lV3tqa7Ez8TjSBtz/4NZiXGGzvZ2N6vJNYnSV1U5C7ExHy9Y9A/tqHBVtlXXzk11C+52QhrU5zzpxkcIKmcMOwp0Z1kMwYW9nMJmwh6xSGTf+McCX4to74lEzkhcpMLZfygaKfxJP4ofh2y3MArxh77Mzo/HDn/JW1i8PL28MrZy84HOi5f/IUvCdc0mDDbOtmC9L575AWvjuPBTp92srcbvtT7vsXWvvs4zE+V0Ms/U+775tP29xSNUT0clj37bsu/v5TtHHh9VNt5EAmW0n7/UsOq01zCWyLhd2Q7ROD+w7nilqZS04DTBlChDTX3d6dyxrrClMlTaPaNLeHPE7Bd7Bo7vL9fvuNlsZ//5H73mDGhPd33PdLVbKRqfaQnqkNX55fQHmsO7xHBfK0bzlaasWlzR4NbASeC2ulyJMNeONz//7GqbYdpH0K2Bal7i6wqZ+uMImvx08cZv8yXKKdci68+7lvv3LfYkU0quQ2uHIwb7evOhxoWsUl8WX5maMJ6z+gPcI3wR5o3jP+GNvZ5N70hkADHQoiSiX2vj+8EdDdUoFvZ4TvF26MNHhnB+lfZ0N96mZIG0/hpRnz+/LN8Tt5zlrpbIg/ccsl9EFno5zfmtLj5zDM42+3oRhUf+rq9NfbIh31IDuavD3SWmkm6GYEvg+5I9Jm++1jjrsyUvoN7wJ00OiByYvv213dHnfXZfRBSP+Ae0R0dyQbHdGy/e7eSJ9NQA8Taf78CLTt3cnhseuqI6/rgOnuD7Q4uA6lbz3Y04+Ojg9ng+BIK/TzQx4CdBiDXs1w+zKMV5/2fQ9rabMXLH2eRxzES6e4RU2BeyPukYBD/Ziw5gT6hUcBvdXkbeMVQUh52g57j/b0Q1B3ArMD2rerlDY+oOlWTlOaW/cJ7RctzSvUDtr3oo7WrLW0oxG+DJP5cdMzQGvDmTm946O9aCytA825UPUMB88ftvtS4Pu+c0BvWSLjYCe/cx5oJGxYlSebeesBIWB2LyzFwP9CGVYvIoaEHyNz8R89ups=
*/