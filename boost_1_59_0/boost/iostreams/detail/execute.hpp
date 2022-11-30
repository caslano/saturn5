/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com

 * Defines the overloaded function template 
 * boost::iostreams::detail::execute_all() and the function template 
 * boost::iostreams::detail::execute_foreach().
 *
 * execute_all() invokes a primary operation and performs a sequence of cleanup 
 * operations, returning the result of the primary operation if no exceptions
 * are thrown. If one of the operations throws an exception, performs the
 * remaining operations and rethrows the initial exception.
 *
 * execute_foreach() is a variant of std::foreach which invokes a function 
 * object for each item in a sequence, catching all execptions and rethrowing
 * the first caught exception after the function object has been invoked on each
 * item.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_EXECUTE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_EXECUTE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/limits.hpp>   // MAX_EXECUTE_ARITY
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace iostreams { namespace detail {

// Helper for class template execute_traits.
template<typename Result>
struct execute_traits_impl {
    typedef Result result_type;
    template<typename Op>
    static Result execute(Op op) { return op(); }
};

// Specialization for void return. For simplicity, execute() returns int 
// for operations returning void. This could be avoided with additional work.
template<>
struct execute_traits_impl<void> {
    typedef int result_type;
    template<typename Op>
    static int execute(Op op) { op(); return 0; }
};

// Deduces the result type of Op and allows uniform treatment of operations 
// returning void and non-void.
template< typename Op, 
          typename Result = // VC6.5 workaround.
              #if !defined(BOOST_NO_RESULT_OF) && \
                  !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))
                  typename boost::result_of<Op()>::type
              #else
                  BOOST_DEDUCED_TYPENAME Op::result_type
              #endif
          >
struct execute_traits 
    : execute_traits_impl<Result>
    { };

// Implementation with no cleanup operations.
template<typename Op>
typename execute_traits<Op>::result_type 
execute_all(Op op) 
{ 
    return execute_traits<Op>::execute(op);
}

// Implementation with one or more cleanup operations
#define BOOST_PP_LOCAL_MACRO(n) \
   template<typename Op, BOOST_PP_ENUM_PARAMS(n, typename C)> \
   typename execute_traits<Op>::result_type \
   execute_all(Op op, BOOST_PP_ENUM_BINARY_PARAMS(n, C, c)) \
   { \
       typename execute_traits<Op>::result_type r; \
       try { \
           r = boost::iostreams::detail::execute_all( \
                   op BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
                   BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(n), c) \
               ); \
       } catch (...) { \
           try { \
               BOOST_PP_CAT(c, BOOST_PP_DEC(n))(); \
           } catch (...) { } \
           throw; \
       } \
       BOOST_PP_CAT(c, BOOST_PP_DEC(n))(); \
       return r; \
   } \
   /**/

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_IOSTREAMS_MAX_EXECUTE_ARITY)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO

template<class InIt, class Op>
Op execute_foreach(InIt first, InIt last, Op op)
{
    if (first == last)
        return op;
    try {
        op(*first);
    } catch (...) {
        try {
            ++first;
            boost::iostreams::detail::execute_foreach(first, last, op);
        } catch (...) { }
        throw;
    }
    ++first;
    return boost::iostreams::detail::execute_foreach(first, last, op);
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_EXECUTE_HPP_INCLUDED

/* execute.hpp
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
*/