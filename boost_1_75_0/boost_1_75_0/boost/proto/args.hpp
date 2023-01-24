///////////////////////////////////////////////////////////////////////////////
/// \file args.hpp
/// Contains definition of \c term\<\>, \c list1\<\>, \c list2\<\>, ...
/// class templates.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARGS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARGS_HPP_EAN_04_01_2005

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/is_noncopyable.hpp>

#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_abstract.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        /// INTERNAL ONLY
        template<typename Expr>
        struct expr_traits
        {
            typedef Expr value_type;
            typedef Expr &reference;
            typedef Expr const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename Expr>
        struct expr_traits<Expr &>
        {
            typedef Expr value_type;
            typedef Expr &reference;
            typedef Expr &const_reference;
        };

        /// INTERNAL ONLY
        template<typename Expr>
        struct expr_traits<Expr const &>
        {
            typedef Expr value_type;
            typedef Expr const &reference;
            typedef Expr const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T>
        struct term_traits
        {
            typedef T value_type;
            typedef T &reference;
            typedef T const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T>
        struct term_traits<T &>
        {
            typedef typename mpl::if_c<is_noncopyable<T>::value, T &, T>::type value_type;
            typedef T &reference;
            typedef T &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T>
        struct term_traits<T const &>
        {
            typedef T value_type;
            typedef T const &reference;
            typedef T const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T (&)[N]>
        {
            typedef T value_type[N];
            typedef T (&reference)[N];
            typedef T (&const_reference)[N];
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T const (&)[N]>
        {
            typedef T value_type[N];
            typedef T const (&reference)[N];
            typedef T const (&const_reference)[N];
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T[N]>
        {
            typedef T value_type[N];
            typedef T (&reference)[N];
            typedef T const (&const_reference)[N];
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T const[N]>
        {
            typedef T value_type[N];
            typedef T const (&reference)[N];
            typedef T const (&const_reference)[N];
        };
    }

    namespace argsns_
    {
        // This is where term and all the different listN templates are defined
        #include <boost/proto/detail/args.hpp>
    }

}}

#endif


/* args.hpp
3poX0Mlbk8U3cLEXC4Nmzydcwq5BfvaosmwEI3Lv0EZRLQ7BUZucnCmaX/kozex5DpewPlcGXm551zbhXeUvycDXHhPli7bCdxv39uBz1NDkyswE7Kca204pM17xZ3Ae2V1JawM+SDmFZHdoc0KBZrNJfIMOnNNwi9i3NBnVCT+diYg7N6EACiz10/iQPos+MOsWL3IJUmYC6yTElM5xBAvCngWwNM/XwhLYLnmbcrx35QXMFKkkQcw+euueNqAi1yboTaecuGQvSkD4kqfTbDvs9CZKe3GX7bBrhi1/mGua2FxQ7QB0dgA+271aKd/isuw0NV+oBrEw6MdLEe6zIDuaIVO2VvQKbU7v8Fy/zWtpk3CI6EIlQ67FAxe9tTaUSw84vSsUp3zBJn9LbGAhXSi37aOrjUs6leVBMhyybYIe19yV0EObTTb5FmDt7unyriiXvCv8QMb32eR3nHJZJ5BnCOmwQT9PFM0vD3MEW5svNjeZfcW/9ZxP983rNpcekXQnRI8/6P5A8i7pgNR/a7mEOGH24OU+9EP1XexgRxqGnXNGYsR3L2k439N1DtUmNUxMM+9dmFRY1uFeBaQGRr6sGyhNPGY9OCoy6+00Aku6kcWUChX3aCDinXbPgWQAWGkcR0nxLU08RRXld4AkJDCSMJdIAvAFP5Hkf7fb/kaL1VgY25Z/EyKj0bNj0A/KxOGoUEsN+WkhOOy7
*/