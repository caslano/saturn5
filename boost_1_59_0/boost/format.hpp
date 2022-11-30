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

#ifdef BOOST_NO_LOCALE_ISDIGIT
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
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
*/