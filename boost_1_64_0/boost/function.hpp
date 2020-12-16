// Boost.Function library

//  Copyright Douglas Gregor 2001-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/function

// William Kempf, Jesse Jones and Karl Nelson were all very helpful in the
// design of this library.

#ifndef BOOST_FUNCTION_MAX_ARGS
#  define BOOST_FUNCTION_MAX_ARGS 10
#endif // BOOST_FUNCTION_MAX_ARGS

#if !defined(BOOST_FUNCTION_MAX_ARGS_DEFINED) || (BOOST_FUNCTION_MAX_ARGS_DEFINED != BOOST_FUNCTION_MAX_ARGS)

#if !defined(BOOST_FUNCTION_MAX_ARGS_DEFINED)
#define BOOST_FUNCTION_MAX_ARGS_DEFINED 0
#endif

#include <functional> // unary_function, binary_function

#include <boost/preprocessor/iterate.hpp>
#include <boost/config/workaround.hpp>

// Include the prologue here so that the use of file-level iteration
// in anything that may be included by function_template.hpp doesn't break
#include <boost/function/detail/prologue.hpp>

// Older Visual Age C++ version do not handle the file iteration well
#if BOOST_WORKAROUND(__IBMCPP__, >= 500) && BOOST_WORKAROUND(__IBMCPP__, < 800)
#  if BOOST_FUNCTION_MAX_ARGS >= 0
#    include <boost/function/function0.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 1
#    include <boost/function/function1.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 2
#    include <boost/function/function2.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 3
#    include <boost/function/function3.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 4
#    include <boost/function/function4.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 5
#    include <boost/function/function5.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 6
#    include <boost/function/function6.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 7
#    include <boost/function/function7.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 8
#    include <boost/function/function8.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 9
#    include <boost/function/function9.hpp>
#  endif
#  if BOOST_FUNCTION_MAX_ARGS >= 10
#    include <boost/function/function10.hpp>
#  endif
#else
// What is the '3' for?
#  define BOOST_PP_ITERATION_PARAMS_1 (3,(0,BOOST_FUNCTION_MAX_ARGS,<boost/function/detail/function_iterate.hpp>))
#  include BOOST_PP_ITERATE()
#  undef BOOST_PP_ITERATION_PARAMS_1
#endif

#endif // !defined(BOOST_FUNCTION_MAX_ARGS_DEFINED) || (BOOST_FUNCTION_MAX_ARGS_DEFINED != BOOST_FUNCTION_MAX_ARGS)

/* function.hpp
SBdCBVJsmcgYUQF9OUpuhqjM51F5LRCCKW78wI/DebEMeY5WeXYWec6mzCrTtP9KrQ/gQSqyUC8nA32rrXLYKvBsx/M+npV43sJTgjhbdna23eF0ZmfgxZHNP4TxLzPr1f+yP2X/d46UNC2NfBsLnVBZA07Pc3XCyuUC/ATc3kZj0b0078wdTFp37sYNcxZijQdSYvZmj3JknOe6cbZStv0c64dQRY58mzfrxIT9Jk/uYl/WypV9mdAVyQuf3319yfrZYNayHm+pyKcQWVIX7quM3UNt4iVmIqzl63/Tv9Zd7iVbXAF32Y4dtaVo1iaaW+jE2wadqn325ikJjp2JMdJsrlvxOhb8XOBuD9qhPhUBjDscmxHpqaXohxcvEHiYBzw8haKiCsArvOxieTH1AlKwm64TKi+l7nuwggBhlZq0Vfw/yip5ij3rC2Ypqvrz6qlbsEyEBlvuFDzJVqzZEVgVn57PAUdjbqnJw0Iu1wv3ud9wMrYh55fJ9Pr9tFy9h/otmSnqB74JNA2Vtnr4JC8EXajAKRh3LbI52ygdLfq6V6rlbUD1uAWjs+MeAdEhFcKrO+nuPo8sS2/1uQ7BgZ8txvrZA7bD3Qrf0R5sosK0rPHRDNPO5obGrqadzUnofsHTWWW8NxlLXYORGwWj9XlpPPSorT8F0nCRFjrY9TjyrNeqhw42XgmB/pKBbKcHw8HxKRqVOCHpCoWGNktuJfADYjcFLVQAWqgbaKH9a448j6U44O4oG2VaDQIj2aefWE7N+aUYLm1H9pxQB94MCeqmZ51J3aAbuEPTD/dHZZV2LC0NZRRtbMbx7WIgXoXSjX9cZfgX8iHknSYqscho3GHarO1YDg2ToCTmQ9fwtstcWh5fvmNpRugsGFr+1WN5NgA5sEs+9ZjYJalPNuNlqh4N8MjrdNIqH0w1jRBIcjwOV8fLnfkawGEMZfQ7Mppnr2xhlLBXoa/oA6q26381bvULlAnDt/ahSPhChZzos+4Swb+XU2ejLk1Di7sovGxETx1e0Mp0q8bRNm1l8hRAJQ9kwd8CY5y6cERTNsgJEqMj/EJidAdWr2OYBUDR+ufniHV72UvA+ZNGSErgZKTBIDhCRwPgvjmiewAzBDCsolOBZQFMktI/seoGSOXXklXyK3MFSCU6xfjLdtYGI/if4gZb6T9MS9B/GLAb/YeE+G637kb+Nc3kn9DVRMOLin+TCzZwqj8Bf90e+TGMt7f+JsOnNf+vh+D/TVXLxgYU2lztL+D4oVzjizLJtOnG+5YIEFf/ybT5WwLTpuJyxbTpQeMyo0r5tm/CVDB0W9UfE+pRlFKXxP+eGu+vBdhAWsEPfSUFfusUAV/t3yiSfAqliNb+v6bE87s8Ob87X0jJb76Z3w6R5CHmZ8FvSa3v+IT8M5Lzv+HlFPjeZv7viSRn7S3/zIT8Hz83uf6p/fHmTSr/7SLJuxcn9cdCxqv8zk/Ob0tqfSvN/L4USW5Pzm98Qn4Zyfldupv2m/l9KtufnF9HxFvjX56U3+cvpo5/WOX3jhz/McnjL+OB4288r+bW5r578mfyx+dT22+mb3ePmf5UfU/pH2X6hG/thdT2h+PteyOY3P+p8Jlm+/4qkhyS3L6toXh+Fcn5zU3tr4UhlV+zSPIy5Iat8T9k9tflZnuf7bOn9mqp/TXcTN+u0Ewfi+4p/Q1LWvdX7eLW348uScn/68nx9t4zKKm9tan9t3yyau/HIslrFyJJuvrPn2y2P2Ox2f7TkWaP678J3+6NPyt4dzQNfO+E+r9xTlL9j97N/Dfr/5Uc/wuTx//GhPEX+aXHv4U3qvw+k+N/QfL4J+TXKzk/+5LU9c/M7wOR5Lo=
*/