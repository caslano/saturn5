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
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
*/