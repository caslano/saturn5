// -*- C++ -*-
// ----------------------------------------------------------------------------
// config_macros.hpp : configuration macros for the format library
// only BOOST_IO_STD is absolutely needed (it should be 'std::' in general)
// others are compiler-specific workaround macros used in #ifdef switches
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_CONFIG_MACROS_HPP
#define BOOST_FORMAT_CONFIG_MACROS_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// make sure our local macros wont override something :
#if defined(BOOST_NO_LOCALE_ISDIGIT) || defined(BOOST_OVERLOAD_FOR_NON_CONST) \
  || defined(BOOST_IO_STD) || defined( BOOST_IO_NEEDS_USING_DECLARATION ) \
    || defined(BOOST_NO_TEMPLATE_STD_STREAM) \
    || defined(BOOST_FORMAT_STREAMBUF_DEFINED) || defined(BOOST_FORMAT_OSTREAM_DEFINED)
#error "boost::format uses a local macro that is already defined."
#endif

// specific workarounds. each header can define BOOS_IO_STD if it 
// needs. (e.g. because of IO_NEEDS_USING_DECLARATION)
#include <boost/format/detail/workarounds_gcc-2_95.hpp>
#include <boost/format/detail/workarounds_stlport.hpp>

#ifndef BOOST_IO_STD
#  define BOOST_IO_STD ::std::
#endif

#if defined(BOOST_NO_STD_LOCALE) || \
 ( BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x564) \
   || BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT( 0x570 ) )  )
// some future BOOST_BORLANDC >0x564  versions might not need this
// 0x570 is Borland's kylix branch
#define BOOST_NO_LOCALE_ISDIGIT
#endif

#if  BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x570) ) || BOOST_WORKAROUND( BOOST_MSVC, BOOST_TESTED_AT(1300))
#define BOOST_NO_OVERLOAD_FOR_NON_CONST
#endif

// **** Workaround for io streams, stlport and msvc.
#ifdef BOOST_IO_NEEDS_USING_DECLARATION
namespace boost {
  using std::char_traits;
  using std::basic_ostream;
  namespace io {
    using std::basic_ostream;
    namespace detail {
      using std::basic_ios;
      using std::basic_ostream;
    }
  }
#if ! defined(BOOST_NO_STD_LOCALE)
    using std::locale;
    namespace io {
        using std::locale;
        namespace detail {
            using std::locale;
        }
    }
#endif // locale
}
  // -end N.S. boost
#endif // needs_using_declaration

#if ! defined(BOOST_NO_STD_LOCALE)
#include <locale>
#endif


// ***  hide std::locale if it doesnt exist. 
// this typedef is either std::locale or int, avoids placing ifdefs everywhere
namespace boost { namespace io { namespace detail {
#if ! defined(BOOST_NO_STD_LOCALE)
    typedef BOOST_IO_STD locale locale_t;
#else 
    typedef int          locale_t;
#endif
} } }


// ----------------------------------------------------------------------------

#endif // BOOST_FORMAT_MACROS_DEFAULT_HPP

/* config_macros.hpp
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
*/