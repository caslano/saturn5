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
DZdb3CnD7jZsQ3LEkK5+yG+XGIL+7BD0D4eMG5wYFB8YNddf+qHecanvd8rwh1V4/B2V4V0fN6PdMt4wjL7WM5wjOa/XH5aikdq/3/6KIcaodlG2sbloY9P73ZPhtawaf/NHynKidJjdA3tlhr2Qac5FmsFapB3pGzLfmub0cdUWGZ9Mg8zvZH2aOi+zv4y+cpPs12ajX+uUfea4TY4XuxxopzIxbrSjDs8QgxLy3c+n3rfHR1ruvZMQHDuMLRh59vWsgvc8i99zITh2wu9I43T7egPnWfYZyXffXA4H52+ML4sq892Mp3n3zmZruFsg/OA8c0x0x3npayj3GM5jxmYxz/D+03c0Hj6P60Vvw5KAKRql5tTlW6QivoqAHXXiJ3BWez6TWyuvfim5tVK94uOPOTm41y91qTcajnQc7Xs/WdUoS9pv87jFpXCwh42lwvpsWk7as2nrrWGuhfCdUeb53jgq/XzH240N9r73dO2zxtHwnxgDw8FxtqG/xWBTc5YwtXKvkUu/m0H1ufqrcXR2chxtHy3nS/E3YLS8z3+FjEAXr94YfD7K7vr+YnBzPsZ+I/p8V0LVaM4fXQrLHpgDMF7rNxauTj7jI6U7zY811utPnagHJzP4UsLWf8sWoUb1X64W9661m8czM01OUzPt72caoqT0sdGplZ0PXpKfIhyzx6g2XJuMZtfTzsnuqzwT8m0ZBYGiA/k7
*/