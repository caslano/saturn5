//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Martin Wille 2003.
//  (C) Copyright Guillaume Melquiond 2003.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for most recent version.

// locate which compiler we are using and define
// BOOST_COMPILER_CONFIG as needed: 

#if defined __CUDACC__
//  NVIDIA CUDA C++ compiler for GPU
#   include "boost/config/compiler/nvcc.hpp"

#endif

#if defined(__GCCXML__)
// GCC-XML emulates other compilers, it has to appear first here!
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/gcc_xml.hpp"

#elif defined(_CRAYC)
// EDG based Cray compiler:
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/cray.hpp"

#elif defined __COMO__
//  Comeau C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/comeau.hpp"

#elif defined(__PATHSCALE__) && (__PATHCC__ >= 4)
// PathScale EKOPath compiler (has to come before clang and gcc)
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/pathscale.hpp"

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
//  Intel
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/intel.hpp"

#elif defined __clang__ && !defined(__ibmxl__) && !defined(__CODEGEARC__)
//  Clang C++ emulates GCC, so it has to appear early.
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/clang.hpp"

#elif defined __DMC__
//  Digital Mars C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/digitalmars.hpp"

#elif defined __DCC__
//  Wind River Diab C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/diab.hpp"

#elif defined(__PGI)
//  Portland Group Inc.
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/pgi.hpp"

# elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/gcc.hpp"

#elif defined __KCC
//  Kai C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/kai.hpp"

#elif defined __sgi
//  SGI MIPSpro C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/sgi_mipspro.hpp"

#elif defined __DECCXX
//  Compaq Tru64 Unix cxx
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/compaq_cxx.hpp"

#elif defined __ghs
//  Greenhills C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/greenhills.hpp"

#elif defined __CODEGEARC__
//  CodeGear - must be checked for before Borland
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/codegear.hpp"

#elif defined __BORLANDC__
//  Borland
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/borland.hpp"

#elif defined  __MWERKS__
//  Metrowerks CodeWarrior
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/metrowerks.hpp"

#elif defined  __SUNPRO_CC
//  Sun Workshop Compiler C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/sunpro_cc.hpp"

#elif defined __HP_aCC
//  HP aCC
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/hp_acc.hpp"

#elif defined(__MRC__) || defined(__SC__)
//  MPW MrCpp or SCpp
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/mpw.hpp"

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__)
//  IBM z/OS XL C/C++
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/xlcpp_zos.hpp"

#elif defined(__ibmxl__)
//  IBM XL C/C++ for Linux (Little Endian)
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/xlcpp.hpp"

#elif defined(__IBMCPP__)
//  IBM Visual Age or IBM XL C/C++ for Linux (Big Endian)
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/vacpp.hpp"

#elif defined _MSC_VER
//  Microsoft Visual C++
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER
#   define BOOST_COMPILER_CONFIG "boost/config/compiler/visualc.hpp"

#elif defined (BOOST_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the compiler:
#  error "Unknown compiler - please configure (http://www.boost.org/libs/config/config.htm#configuring) and report the results to the main boost mailing list (http://www.boost.org/more/mailing_lists.htm#main)"

#endif

#if 0
//
// This section allows dependency scanners to find all the headers we *might* include:
//
#include <boost/config/compiler/gcc_xml.hpp>
#include <boost/config/compiler/cray.hpp>
#include <boost/config/compiler/comeau.hpp>
#include <boost/config/compiler/pathscale.hpp>
#include <boost/config/compiler/intel.hpp>
#include <boost/config/compiler/clang.hpp>
#include <boost/config/compiler/digitalmars.hpp>
#include <boost/config/compiler/gcc.hpp>
#include <boost/config/compiler/kai.hpp>
#include <boost/config/compiler/sgi_mipspro.hpp>
#include <boost/config/compiler/compaq_cxx.hpp>
#include <boost/config/compiler/greenhills.hpp>
#include <boost/config/compiler/codegear.hpp>
#include <boost/config/compiler/borland.hpp>
#include <boost/config/compiler/metrowerks.hpp>
#include <boost/config/compiler/sunpro_cc.hpp>
#include <boost/config/compiler/hp_acc.hpp>
#include <boost/config/compiler/mpw.hpp>
#include <boost/config/compiler/xlcpp_zos.hpp>
#include <boost/config/compiler/xlcpp.hpp>
#include <boost/config/compiler/vacpp.hpp>
#include <boost/config/compiler/pgi.hpp>
#include <boost/config/compiler/visualc.hpp>

#endif


/* select_compiler_config.hpp
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
*/