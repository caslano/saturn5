/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_IMPL_CONFIG_HPP_JOFA_091225
#define  BOOST_ICL_IMPL_CONFIG_HPP_JOFA_091225

#include <boost/icl/detail/boost_config.hpp>

/*-----------------------------------------------------------------------------+
| You can choose an implementation for the basic set and map classes.          |
| Select at most ONE of the following defines to change the default            |
+-----------------------------------------------------------------------------*/

//#define ICL_USE_STD_IMPLEMENTATION                // Default
//#define ICL_USE_BOOST_MOVE_IMPLEMENTATION         // Boost.Container
//        ICL_USE_BOOST_INTERPROCESS_IMPLEMENTATION // No longer available

/*-----------------------------------------------------------------------------+
| NO define or ICL_USE_STD_IMPLEMENTATION: Choose std::set and std::map from   |
|     your local std implementation as implementing containers (DEFAULT).      |
|     Whether move semantics is available depends on the version of your local |
|     STL.                                                                     |
|                                                                              |
| ICL_USE_BOOST_MOVE_IMPLEMENTATION:                                           |
|     Use move aware containers from boost::container.                         |
|                                                                              |
| NOTE: ICL_USE_BOOST_INTERPROCESS_IMPLEMENTATION: This define has been        |
|     available until boost version 1.48.0 and is no longer supported.         |
+-----------------------------------------------------------------------------*/

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   define ICL_IMPL_SPACE boost::container
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   define ICL_IMPL_SPACE std
#else
#   define ICL_IMPL_SPACE std
#endif

/*-----------------------------------------------------------------------------+
| MEMO 2012-12-30: Due to problems with new c++11 compilers and their          | 
| implementation of rvalue references, ICL's move implementation will be       |
| disabled for some new compilers for version 1.53.                            |
+-----------------------------------------------------------------------------*/
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#   define BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//#elif defined(__clang__)
//#   define BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//#elif (defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))
//#   define BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
#endif

#include <boost/move/move.hpp>

#endif // BOOST_ICL_IMPL_CONFIG_HPP_JOFA_091225



/* impl_config.hpp
cmqOTMMy7fFkZlosukNmzjLlcWnybX0XvBsrAc6syc10YILwSyfzU/a65ZSz6EU0kXOwLoSBncSLz2C96ykIKF48vL55PxoONh/U5g7ZQqnwHHoPrWeHsbcCffr4VJ8v7smfNpNl6tXnT7sQJVkrG9og1t4qyE4+PayTdhryAcl0UGqqivB+ToGK9EbttRBp6K6TfNoWYoXGupAiuWTYtRyDC3cqHYVvOw51Vo4XdH0RZ8ejTBkYG38NsYUT0t80vtOzl26qKgKVa9nXPP4sxJCnn/L9mXfbJSnG09qAt9tkJt8QFIVJLa0oY/X5qzRVKUHrM1Wr0jA5K6VJJru0ns82g4p+pxPZJnCjCSzJW20A8wfdjlSloVKW3IWZ72Lz9muWNMfszlNlYwdhowFLGwlgxbxl1A7+W2N/J9FL7zvL1N3cziAPyqfy7fm811MW6W3L5puC6NVzP8/aup5c0G8mY9UbsZ3y1f9rkOZmFBaEgivfuc1VB3SQTOvhluwJqo644RhMFnyEllwQuOGj1U664kgoYktLvONPCHcP3RKf53942D0hbHKt2k8f6sr+hK9jS6ZCAnoJXsmBfa1ovfLhpyudJgXpLZtsST9s8715A708Jmz+GeazGmrtuJX4YIjL0XWjb9TlrzBt
*/