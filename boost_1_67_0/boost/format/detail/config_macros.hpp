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
 ( BOOST_WORKAROUND(__BORLANDC__, <= 0x564) \
   || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT( 0x570 ) )  )
// some future __BORLANDC__ >0x564  versions might not need this
// 0x570 is Borland's kylix branch
#define BOOST_NO_LOCALE_ISDIGIT
#endif

#if  BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570) ) || BOOST_WORKAROUND( BOOST_MSVC, BOOST_TESTED_AT(1300))
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