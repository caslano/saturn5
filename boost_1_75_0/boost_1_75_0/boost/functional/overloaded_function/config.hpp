
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
EU9mvC72T67Kbhr2TwHsH9NYYhNnmfROlPobK9pSCcvJbrd6FTy3ypWr+P6vRHLwSaVBf2ngD7+N9eYPjdqRva+RdiRJ044kpbwBE3JNgXWZocad17GKqkfuKnzjGdwibzumKGjDe7fKMT7xmkGRYaAhVSoN+fe+QBxj3wpBShMqcJ7dKgLP86curfLBza/68sFl/xUf/M6rbaGMlwWcVU65mNXg8gA8faRhLsfgzt6wZpe/6mfNFuGajXR4hrSgW/EGtlGXXtWFp1ki1MQJ/PqK32XR9Es4gfG5gSbw0jKLliczQr1T55FEQ7NsWoJJTKNICFcvMkxOYN1jhskOjLMA6VY6TQeQg6PdmDwQtsyW9IQkuzk67JjZkpWQdoz9OdgC3ycYhx8gQ+R7Y7QwXxZ/0te2rw24FCF0igB/d+dWcenDl31xaRbiUg7g0iiHJ2rIAojxP/9lK133cMg/+HJbUKdxtO7iNVcP+W5fC9Sxfu29BmLsW6ytjv3wwkBjvxfGPsZekYZM3075+Daw/dZt548WtmX0VwYc/ZivVP/vr3A7n1qu4b9hDpFWb/w3zOGKhYFZGJrLLY7iy5ApPPFSW8Y8ZVSgMX/0ZSA4j49pFc5PvXQuONs5nOfWesH51jaN+buRgcZ84gsB50NfIJyfqwgA5zejW4Xz2gXngrOdg7lsQVuGHBNwyOlf6GyJeVRiGKBJN0BBS3i+
*/