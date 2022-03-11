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