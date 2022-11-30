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
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
*/