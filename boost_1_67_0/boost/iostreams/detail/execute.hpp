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
                  !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
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