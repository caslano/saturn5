// ----------------------------------------------------------------------------
// workarounds_stlport.hpp : workaround STLport issues
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_MACROS_STLPORT_HPP
#define BOOST_MACROS_STLPORT_HPP

// *** This should go to "boost/config/stdlib/stlport.hpp".

// If the streams are not native and there are problems with using templates
// accross namespaces, we define some macros to enable a workaround for this.

// STLport 4.5
#if !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif

// STLport 4.0
#if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_OWN_NAMESPACE) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif


// ----------------------------------------------------------------------------

#endif // BOOST_MACROS_STLPORT_HPP

/* workarounds_stlport.hpp
0iKcQnOS2dDTlnjkW9EUiMluW4h/7ePbG/vOPTbr+profIM+c6s+M9Kg+hzPs8SOyHj24Zw+3PuWyfRa8p5KLY/6Tammrzf/VR9r5DpNHzISdSxxd4cn/yEJoszK6+9T/sOtn8zFNw/e4ZNX/WSCd/jnVdvneF7ut/KTZ1i3br9mBOVtR9+aei2YE2pOp6ZFMAwTQ80iof388rCVg+8QfxKMf39F1y6LnQY/c+O2rYN57laU
*/