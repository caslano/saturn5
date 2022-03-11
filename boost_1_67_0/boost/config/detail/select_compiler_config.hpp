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

#elif defined __clang__ && !defined(__ibmxl__)
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