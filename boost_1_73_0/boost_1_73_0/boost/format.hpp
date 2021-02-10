// ----------------------------------------------------------------------------
// format.hpp :  primary header
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_HPP
#define BOOST_FORMAT_HPP

#include <vector>
#include <string>
#include <boost/detail/workaround.hpp>
#include <boost/config.hpp>

#ifndef BOOST_NO_STD_LOCALE
#include <locale>
#endif

// ***   Compatibility framework
#include <boost/format/detail/compat_workarounds.hpp>

#ifdef BOOST_NO_LOCALE_ISIDIGIT
#include <cctype>  // we'll use the non-locale  <cctype>'s std::isdigit(int)
#endif

// ****  Forward declarations ----------------------------------
#include <boost/format/format_fwd.hpp>     // basic_format<Ch,Tr>, and other frontends
#include <boost/format/internals_fwd.hpp>  // misc forward declarations for internal use

// ****  Auxiliary structs (stream_format_state<Ch,Tr> , and format_item<Ch,Tr> )
#include <boost/format/internals.hpp>    

// ****  Format  class  interface --------------------------------
#include <boost/format/format_class.hpp>

// **** Exceptions -----------------------------------------------
#include <boost/format/exceptions.hpp>

// **** Implementation -------------------------------------------
#include <boost/format/format_implementation.hpp>   // member functions
#include <boost/format/group.hpp>                   // class for grouping arguments
#include <boost/format/feed_args.hpp>               // argument-feeding functions
#include <boost/format/parsing.hpp>                 // format-string parsing (member-)functions

// **** Implementation of the free functions ----------------------
#include <boost/format/free_funcs.hpp>


// *** Undefine 'local' macros :
#include <boost/format/detail/unset_macros.hpp>

#endif // BOOST_FORMAT_HPP

/* format.hpp
QS+WQZGbBvBx8LoY/NULn6YkWTMXiFWEH/hwzZ/XhyO7GLY6BBjerLKgAbaBzHRovm9wM9EKZ03da7pg9fH1oiP6/dfUNGzRAqxxhOs6QOubgAkQxudn5Mlf+Ul6wN+lKXkQOoD907o+HhtgWglChE8pdMYTo2e+F2ayIGFg6jtz+MuLI7R87J8bH5zBqIOd6x24a8xm1qhnAz3DN7BzNlOE+NYUzAXh+kn0FcJ6VW/U1FXh6mSU1SAnIWAu/TofKm0yYOlTiHd6zWDhg8UjjWkWl3S9jiPqLts1iTWuOALBzmjYM8+mE8OxOhNzbNdERCFsVm0bYRr3e9GXJu9vnU98JIRbPB7kw7Fu9x1r2gNUC0qv/FB1N3I6F/q54WDT8j1wIHMyGl4YQ1s9B3AIOUHH3OIBeQp6aSvZrPkCl9Er8GATUwQMcuHbGOEJBH0Ky/F3heTxkXKrYVIrexHexe6YC4u9A/Plwnpdz+kA4r3AqJIwl+UfiNZquZx4NaIJ8tFy4pAkjKe2cwnri/7HwBBe1eEknms1MazpYKdV1lVPB+rv7mq1bDDBsSfwGBIa513ftA1rrHcM2VQMbgUjwgi3bN2eQrSI3t9kI+I/RdxxnDLnLxsAcUCegzoKmViycREp2dGJykZ5Rnkb
*/