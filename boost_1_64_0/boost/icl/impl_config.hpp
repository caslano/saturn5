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
Bg7ZxpnpGzKy5xpF2U1f23b8KKyXz3Nvpoyx7ZZbOhJZ3Ew2p1XZnIUp7sABuVEHdUwc8bqtW7/sBoExd3WGvVfE+PbS/Hd8rfEhc6epCqtoYX7rniRQp8pPXOURSYnK1ehPl1rc6CnnpWIeAlNH4Uk9pJy4qBBbE6zc1addW5zHriNoaNRCl5/ZVr6rk2CLxxuqXwgan2DCJ26bOEJIC1u5pKdfIDIbIehp7+CcRuu7SiRasGdcuK8vvUuYUpDL2hKf5nnCw45BSpfhNzU1uwzPZqE9IGtiqpVotpbVfR8SxjkMYVNP3qxo+Be7sCx11MVaW9iNAgWX4KQyMmtZrF9V4CCowBbL+A9C0JpD7U6c1ntbV1Hje60qmgn1y30JIXoeNAY39Ap2gPoCWjCj1FerzNa+jUOYhyaSjqMq96X+wx/g2DvLyK9gDzl7rTZuLWpMmS/Y+C1nHC8Z2li2qsfGlwiSXNu78znKnQy8lTlb+JVeqOIOMSgmIK3rZ9YGqy6v8b4LGuDGjagmN9VTh3qkMxINzHUMN5T1FqUF66S+wMyp0NLYaBZ1NA==
*/