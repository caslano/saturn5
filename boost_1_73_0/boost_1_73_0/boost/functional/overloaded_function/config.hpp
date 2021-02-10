
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_

/** @file
@brief Change the compile-time configuration of this library.
*/

/**
@brief Specify the maximum number of arguments of the functions being
overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When specified by the user, this macro must be a non-negative integer number.

@See @RefSect{getting_started, Getting Started},
@RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 
#   define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 5
#endif

/**
@brief Specify the maximum number of functions that can be overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When defined by the user, this macro must be an integer number greater or
equal than 2 (because at least two distinct functions need to be specified in
order to define an overload).

@See @RefSect{getting_started, Getting Started},
@RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX
#   define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX 5
#endif
#if BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX < 2
#   error "maximum overload macro cannot be less than 2"
#endif

#endif // #include guard


/* config.hpp
S/DC+1YpbPkfNJX/rpAkz9B/UPEG7+9wNYYXredkH96l9Qx7WisZfJ2qdZK8w92NClL9jZXyTaKWuNNrDvpz3jy17LaQsDffh8nJySf4ANPDycyEc1IzWkIkab2h7a0Jp5ne+aUgj4+WoJ9NoBJIae0YjAsmQPBcPpCWAq5LltJa0AyIgIyKtGUbfGA1yIJCzkoK8yBcu/6vJjwULC0GO0+8A1HwrsygIPcUWppSdt+baUgrgedoAe1nTEi02UnGawvdU5C0rcRgRgVBSsGB3BNWkg26IxIKKRvx43icdm2JmYwznopxuoXCKmT1VVZrjKYiT8AbCZJDJ6gJSt6EimcsV3eECDebblMyUZgvYaHDOhvzFgQty8EcqjIq+hQoRANappKEBqNnUt0Er4Xy9lDwakcQYR0M5V1bozuEBeUyjsCb0NUZbbW8BmLrZUBZQ/5GyV5iz4DXGBWM7AjcaAQbIpgw4dqNF8Eqhmt7ubT9eA3BBdj+erB36frnyA2GXlugj01LBUbRAquaktFsx/k37XTDihcwXy29IIyTKFokiyCKk3B15rnz5NJZJ1fnH+EIRpMT+K2rFc1/GMGoZBvFA5hZRzPrEDfUU0KJeEoElari+ENyCbQfLcC3rxzjLSc3HyAtaHonukrh
*/