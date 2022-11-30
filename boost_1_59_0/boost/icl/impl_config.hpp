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
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
*/