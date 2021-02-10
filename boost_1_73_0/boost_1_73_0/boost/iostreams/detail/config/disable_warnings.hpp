// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/config.hpp>             // BOOST_MSVC.
#include <boost/detail/workaround.hpp>  // BOOST_WORKAROUND.

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4127)    // Conditional expression is constant.
# pragma warning(disable:4130)    // Logical operation on address of string constant.
# pragma warning(disable:4224)    // Parameter previously defined as type.
# pragma warning(disable:4244)    // Conversion: possible loss of data.
# pragma warning(disable:4512)    // Assignment operator could not be generated.
# pragma warning(disable:4706)    // Assignment within conditional expression.
# if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#  pragma warning(disable:6334)   // sizeof applied to an expression with an operator.
# endif
#else
# if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
#  pragma warn -8008     // Condition always true/false.
#  pragma warn -8066     // Unreachable code.
#  pragma warn -8071     // Conversion may lose significant digits.
#  pragma warn -8072     // Suspicious pointer arithmetic.
#  pragma warn -8080     // identifier declared but never used.
# endif
#endif

/* disable_warnings.hpp
SczDGz1knnEXsaFgBh3yeYZIYrEa+tjQHPrxtmFvOGRnETey++r54bMm8HEb26x5G9K2h1mbm5X0zbT0DE7YvOeSO7BiSNH++c08tQuk3h1ABMgOei3dffrpJ4ZwJLJeAwZe7TSOVKuwU6HozgFt6NhCeFhD/B9B61JVQobHIVyjcPPBTaS68s9kWx2OCHI2crEDlN3iBspksJ2zFg+3kevvgKYu81GbZ905QLONg2936F/jDu/f4cnLXznblZaye4OKnahILNOyw8QaSxi67Gn7G/PweWS7CPWYp9ZYoSFs2gzfLFPZOkdrSSZAuL55tjdhd91nMG1gasFkWrL/e6OzcEShrUxLdbeh2a11yxt9vuXWaJPS2H5Ek1+O379//gxdltn7G8b58+12bttnZaPtFgfO9bBu5TyHNCq6VUPd27PBgfOA7rfpth2U1DvdrF/vPPa5dHty+gxzCLyvO3M519u/SSWt4R+hWAsVGxRtyZd9pyVdLmwWQ6kF6bHEm0qa/Fea+K85VVbWsg0Tnz1yBaSN2r5h0qK1gf8DUEsDBAoAAAAIAC1nSlKqfUUQrgIAALIFAAAfAAkAY3VybC1tYXN0ZXIvc2NyaXB0cy9jb3ZlcmFnZS5zaFVUBQABtkgkYK1TXU/bMBR9
*/