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
Lrvuf6Dte/u9ofz3PfI03L+sEh4pXAj34xZicAXOrmsB+iw/DI6ltWAtr4GeJd/D3wq+gnOnV8Ffh/khNbNpDzThsZlw7yd7YVrhAnj4ww1w91aAjEqA/20AuGn1Mej9wWG45u1aMJX9CFcWfQtJD63HNvyX2jGQ8vsffwEmbfkJJnxcDdPnlYF/xzEYjvmHVQHcvhFgwHqAG1YeBe+yerj6rf2gf20vXJ45Ce57+mXehgeeng0Pf7YPpu8GeLRoEUx/ZyXkbpXyh2Awbq36YTnXfXwUHO/WQ8852+GmYbm8DZNnvQJP7NoPM/c0gn/55/DYq2Uw6fNGeLAaVDBpJ676O4CXfddmgFuKN8KM5wth6gtzYdbXB2D290ewjGMw7bW3OTxSshimziuHya+UwgOzS2DSrHkwEds8/vEX4b7HnoN7pz0NY6Y+CdMKiqDguzqY9+OhcBn3bVO3XwmUR9n/j82ZD6/+WMf3W01lNMLdVUfg4ZdehcnPvQJ5T82G+/NnwX3Tn22Rf0bha1Dwybbwni1UxqMvl5B+WtyT1TxgeV4qozlEkvdsCOiqxxAwnLRYexliZGAEcehsaHvgPpLxNFBcEAMF4wHGj+f5uLer3D9eoNo/XqjaMV6k2iNezM7k/vDiGDVdEVBH7z2q8E5jumzYUBFQ7A8v3rt379G4pv3Phg3rMEHT/qhZPOP5lfvD6cpo3B/OUETz
*/