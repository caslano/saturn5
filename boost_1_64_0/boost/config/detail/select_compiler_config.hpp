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
yGL4Z+a+IDb99sr6fQbar2/mtlVHM+1MrGYh0YQ+goWosuj6o037PpdFF/ozr8xfYaB9em+UE4KmPLt5soiPN9zSpEIUWcQW6HTuiQ4OL0++LGugQV1DrxSkaeacitXMN3r9QYWo48ViUxZLFVkE9Nhs46cHmy0LeJ0t23hhUCmkF8/VtUu57Y3r9D/97o1vNFrr12N2vgZp5r4V1LIAoeIaLgoqRLI7nwdnF9zuxCn0pbf++1MG6tNv55bGQXw7uEmyGMkYb8o3VBZUiGU/c62uvZLrBZqZg3/3fM1AvXp5hvFTd0tzZZGDwLoNlwUVIunFlTqdRS3HnSvXXr4u8+hP8/VIubV58wg+WFxo7IxKRSg6sUnXClwOl+Ne3s3p7xqoW79ZN34aszfPzmKVrDReDhWLHA5s1rXH+PyBjpKXvXTGLw3UpXeLfZuW5skhvafQ+HGCClFlcXSrrq3mssDz/eu/8sc9BurUN083fiq0Nm/+GI03erefSjDHB6+u3cfnjZXw+88+cBcP1e/QV0zj648mnnmM8qfwGywGKkSxrfp07QNcH67ApdnSR6MGulV/0sb1wd482yrTk2r0WElFyHI4BXL4LJcDOiCs2Dnba6Bb9FNcDmf15ukEVLLRYyUVocwZ/Tr5VcA4Qf4m4ESsn+F9I9bSvPMfMPxuTDd2J4+KUNblYZ18v9awO7tPDBroZn0ZPxfdD/owt1lyKJXSL2msGKgE2suMmLrwAkUXrtaP8XlzWWvzdKGwPl4YaexqnIpQ1uIDphy6FTls0jd28J2rac2Ww56eJkgCC1FtqWt17UN87sQLMF+995DXQK/Se+fwc9G2psqihL831oZQS6HzwBFzjMCLCpkt6T8ghi977EefAcSa2T82Nn6wlMuguTOl0z0K3MuMf3bxr42WXqn38pZ3tjTPhoA4qZlyqbEaQWXIchgFHzS+3mJxGeate47R0g16mbf8RBP3ZsqNVwcqQjkDu0HXPszlsB7vYy769+sMdL3+mG7alJc2TQ6lwo2ZBssBi7DI4XBW127n/QL9PGP3Fh8z0F79+CbjpxZwsrmoWXKAvzEmcGMlQYWosniLrt3JffDROfbHthXzDXSd/hjvJQdmNVEnsJrpXBNkgYWosjh7j073XjairXnNpncaaI/eMZuPE63NOxdl1RwtNtayokIsPjUfMmVxlSKLtfrxudwPs73JfSSX3tt4WWAhFll8CnzquSxweIgfWfErA+3WV+BmP46loB/PaaYsCsXGnhFTIZb1+FdNWeBZ8UOLl91toC/QV4i5tKV5fhSsmqVkE2SBhVhk8aBO9zw2axrd84DIHfoJn/HTSTgrntlMWYBfWONlgYVY9id+oNNdGbzklEyt5z7sq/WWDk44rXk+eKyalXJjjwKpEMt5+U9Mvdii6MUq/SQ/Iz4CfaSjSbKYiCeyu/ON3byTyyB7E4zKlVwOW3G0fOVy7st/hR6aJfa0m7e/PxEfAcfqSmMdEqkQi23xC11LcFngBZ5vj6/6koGu1Odz23u4ibb3BAvb12BJUBHSmHla13q4HJx4Dtwf5mvS5+tP87sup5vos4yVhEA1DReEKIPuMv4W3EW4HPC+v37t7/OIYXT0MzO4HJraN7L5Bp90UBHKvtUfdLpniD6J3/zV6KMGerm+jPeLg03tFw1fm1MRSr/4o7mX6VH2Mpfr51q5ZjRxf38CLqE0Wh2wBKVPPG7Om15l3nyeftv/4IxjovH7E1SEsk/zhKkLPkUXlunn7Pyuj72ZctiTaKwhZZaA//0bI3Tgv/Af/U7/PVdfxaVxQG/SPLEvl9yFLxkbP8ZzlWwDxVGvMG0Ksln6P5dNIV8=
*/