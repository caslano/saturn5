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
NEPU9P3vOefet8yC+P3+/p9P9ph377vLueeee865Z7HNT+/MpSs7REjtpMF8cjrZBeEwJ6Ub0tH6XmTjXj0e6bVXGbREooSEXOM+9TJc3LXKYLiIu7WB8UkGr7vjt3JzvkK0MHCkS1ghKa84NcRc+gPoc0ZEsGP+b/PM9IR80Be54ULdE9oTr0UZFVjRx0QWPkySiLJVxJnkwswYUyrjGx6/D6y98xs7pubETYrpncPIeVoEXotcCdqcBmkTexHv8HSupk3+wiNIH0ItomnV3znPId0D6XxXwBop4IQJrlZ/Ng5mtX8Z4127i//aFSCyNkBYXTa5CHPpfahpvSuCOl89MdpExw1brv6ZkhP9spOAM+i9yVxugdQmEfbetYJiVLr+ZOK/Bdd10S1IM/ohuZleAK5YtY9Acy16ulEjfzkxGv20dj4CT49KPyDaNGNc8yg4q4GCFMKuL8ddX0q7fhjseq5fAf4jr3+hjoTUyIMnao3r2yr+nnUw1H9zamAGVf+y2c71L4S539rF9naqBONzuyG//Ct2g8ZGsqPGBoHeGJfujyjYjaabkeGE6jhyvQknZAbBcIzJo+iA+mEckonN4/S5pQ253vd+06qceDbtXLnei3iu981pbRELB4cFyvU+a6RP/utM99R4Q067JG2wDoZmx3xiRwxJ07MgKdJpVmtGUV4GT/e+jI6f/zBe6lnBUs60s/MUT400
*/