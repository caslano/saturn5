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
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
*/