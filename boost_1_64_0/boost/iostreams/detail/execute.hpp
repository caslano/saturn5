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
eyx5PKx5zJxwOvkkj6Y955u0HhWdxt5zWMqZ1mC952v/1fU41flP1+E4Drnws1bka7ykLT9Uv+c48350PpE/EN5/k2AH0Z/qL7Se8Hmklfg8+6xnHaDr3T+1TBaJ/999nazdPo/+acInmfD5M2aew7iv10t06SdGXK+5pGFmZ2CluebgXjLB0fmlXce6nm9ElcQvWfM2RPyuYg58J0b/xe4+38VyjQt95Dpd/NnWi77Q2qT8iY5bNVm/cow5rCuDafGXxjEnXdKiY9tD4j+U8AlWI6SDFfCZud/i18FfYN2GW3C91FZxe9230xewUnDb53K73tpiO+6ua3V2z9deImmradriWAmXZOaQpYp/AzOHPlPKoTcuCVZ7hDzJnN+rxP1Smdd9iPNsiecU/yJ7tF167UJTVrVgnujUZwT2mf5+q+NG+0rSfCyT83j/Y3x9c+WhkzueFaLzla+9tcMXKsNvxK2hL8FK0LT+2Q7NuQ+WDWWi1xjkpJ1yStK8rBL/b33fkp+q5po5Vppe7+MzHP/xViXKrR6uPajbNC2/N8RvsBVPnmrhm46fq61IukNlnRFMo6TjANcdI+e93O1CyitF9XPEv5W/NjOpqtBBJR6TnziL9Mtc6wI5r+u/xT7FdsWV4a73JyWdSWae/cVazj2ti32P+Kqb38m/SNlMohw+t2rouojVovu1z1WvYfUxSPyTSZFPwhwlzBniluHKW4Fph8mwp/gPEv3D6C+R85pu/XR3+ruLP+1P140NkPPhflf/lrJr5Orf108IXiORUbgJko5WCv6p6r9ayuQ5YvVJ36+rff/GYDhWsHTlm/12GVe6nW9bTjt/TfzC2nhnd1lM0v7k17IoIcxscWvmTms6CI03cnwWHP/sBOsjq4n9aFh6dojfm3Y8s74utu416XHqvqbkgXovjbuTloOJu5Ok+SU7mbV3H9KKm9p3S/ypGv9XEv96uzrxr2cXtBSN/3j4WCO/SZkx3J/4A+W/P0nBLdG4mbE97Hdtms6RHW7z7R0OhkccO+qTwn/XcudL2MjfNdOWLhH9PlI/eGv4092/bbh5PkuZcWvIZMe/0PO3zh32UJrMN164ICfXjAOPi//1cv0Eo7/CxKFuEfejs9Mt12/zjeI/nnbW2a1jxttkeJfodLDidMxx6vNlcXvfHcb05brwCvEvYgxtb1U1bapI1q7UCt0vSt6rSV9KUre1Eu63xLsmtE5KjiWim8K/0va4TXRHWKm0KPeamN+Ke+VQ25fjdnFbiWsW8xXrSjy1tI7eEb/JjDzNJJ6kUHt23NWttro9KG5+cUtWt3vELS5szeVm41ba/34tbgHT75zxKkXy9Wsr4jfd1PFKCXOKqYv9cp5EWQbMmLdB3JZE/a1OkmtUMm1uhehXM2PsKjlvb3v8Tor+QfGvQQw+k66JEmdj82z8dy2X0BzxjXI+3LTNo3L+hLu9dHbf/9wm/lXsAO0l4nfM5OP3mu4UTdfPJoWex9ewujZg7gHvFfdvKP23Td98VNy+NvdS18t5y9I80y8L55Ze6zXxT3CnN8NdLzvEvyq9gnVlNShTEtSVjFfy+5c1Z0l8XKBaJeDzV/MDf6VqGQ78wTXxGmazK0x8tWbV2qFSKd4SnWaqs9foJASWvuNEXLlatWrNHc1qjl4r1Tuuegm+pU9X61GtBQqVKyX4q2mUZi1+4g8cd827Fde4eygNNx2T3OPrZO2gL+oz4QuI3ZrrnRk+vuYtiD6+1oX1RH+31/MNcZ38fUuy+D/nOa5q2JjfefgDZb/zCO11cemLxG+v/0XXHYOP7Phdv7FL/vTxq1O7R5sjX/455t5z83+6PS3Ku7bAe45/+Bw=
*/