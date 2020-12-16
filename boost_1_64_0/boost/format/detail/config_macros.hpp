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
FLAKThRYTuz2lL3uqHgXFoagkmoAcac8lR9rEgKZL+ER+OAQ7qxlNe2ivUTLjz2vVQ4JL620PpmLT6aLtlHEFzjQGla+v6SgAliEf1fd0hJXRHF7Ct47t6Rdthj+wNtvLfCNdy8TRO21vQcxiNJe20F4InaE7SPxpHYzqOgwltxrNVsC4ovjThyPNgGW1mQZaYbId2UkFHysDqzNS78sr+5RNeQPu7bUTgzCs6HoZtn93F0rm1J32ek+4D7qr2JohhZpEWa5oBdmpXB/OUV/WVKov0alUH+92Rz76Lnmso+eaC77aHvzyn30FMShXBD2azO8Pn0ZtHzFF4BnGDcfQ//UfhU4D7Y1UQ1ziYYhjlp7A3m1sUXgRGjdghq2tAU17Idm2LAPm8mGvQ1PZuk9drZDyGftfI+Lo2vPJvdJ5LSH1ic4MNi2QTljFzwO7yh+wy4IxUAQDpiS85tjHB6R9bLi12EnnwUFs3CX7V9sRTP9+337AdxUB3Rh5ucXZ/Kc4/sq9JtAbjYz1uB+f/Fp/IMtRpbfKnkk1hMtkM14H96tSBllbCY19I0z4/VJpO5wqXhxRqzpQjj3IfAfOyMk/tmhHCcj6pYFk7hpgjYD/fYZAdS195qApuWqpuWFbpqHhpGIPWzaZ9OBZLbAvxUX0ED/enoY5u7t30abSrERnlPHPcWvwELjhRgWxXdBh1zFB7W/vSW+tzDgdQ+EB4/ScLc0d7MYoXWxxUHGkEDVTgtNdsRv38e+Jd7eJzNiVdpNH5brcLw93Ljy1h2wVadJQ9oQhfAkWengzdDvhAGf7FRV/A4XXZexozOFJIxPkvGR8EXStpkUtJcmoRMMXyx5xFgGWZSnjR7WFG97jC52xZLF71mXizd0iQEbejEbAs+PxGjg4714wXy8SuMhJMPWzrt8rMmBaGE1ktT2YtIwjMFuQYS4WYbuUr2CZLco0YIioJ3+zklCkDEWkcHyjLkay/MEQKBlqp/zDah7tOYnSIMZoWVpteBkwzopinTh7yUuFVZeYaD0mCf+2csMnENvHb8LjALrM2bo21c7h2MglubXFhDSIlWgxW8r1311tK5f4zu1Lkr7HZgpq7qJTKpo7/jKdaLJCs7dJVxf76+Nuetrc87K91rajZBWNQguf932cp2QDMoUmt8ORcCs1DHq4ra4IJkLUoz6BlBAqw2kMa06whUWHO/Z3CZpog1pEDbDkvAbDJWxl/u4DNiVtE5Q3ldb63yIcLBpXeCdEa+qP2/5AVpYK8TOL6e78Jyxx9Yc911t+LOQ/7PvjN3aQLtJvccAyCUvlevnn64If/gIqCEvfrttR3IMUYvPmCvQiKFUPvAmiCezN7rURneFyqH60d+zBr+6NZ2K7QcQWsskpjo776p4mBlJmRhd2x99J+4rizx7y5B/or29ExoesFg51VOqekoDrtVXTZFGycL0057i46TO/8MjKotLPXnUUzYU2yOKuQKK7bG9BvFm6qC8MTeFMdrn/wWconIl2pHrhWYZizeu/FU3DNxgv4lb3kv8Okmc3f5LoOofFrpc2KxIaQlNWSw+XjssBPi3GvqOK8T80u76VtyqqI8+tVMBIlg0x20+7jG833xHFbNoBXx1EgbMoNsgLxSNQxhpiBVgBK67cWdsAbObn/6+U33JVfYfjF/c6cth0ly1u9zQeL2gHfOD3kmkq62xfiewvloev8VbfO/k60jkEtLZCOne4CJOLuKURZxhrJ9VnrcA31ys5a5XjCIknQVGLq0NVO673NdI7dhO0tAD3NpgqZ8TwlxxVH0MthC/HLSkpEhnu/SQHVoyVXmpRLLS70jSiX/MXgf+sXh74p8Ib29fJvUk13k=
*/