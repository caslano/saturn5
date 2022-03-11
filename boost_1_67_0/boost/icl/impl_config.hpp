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