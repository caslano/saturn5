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
RTw5FIz2cIv2eRLtHpT4lJvUL7XBfJRETaQmXUu8lvQp8VOSeqJ6UldiVxJ3IndSaeKN3rHe5711WuqlX8em5Efk5+W/uznmuUnLGErmMA8npSWZJT7uhWvpLUmXZoyR3ZwaZcjMlazbSVKJtL2wXqve6V4FLe3StLHpfrk7iWJaFqW5Y3NrDofSIcxRWr6lKWOkNddDuRtPriW97H3jFPt88onLPTmtJ9xJJr1uTolvq98WvO1YlOllUS3t/4+1R+ubwHPdJElut0SpXtZnpbO3WB9ye+hLOGrN6jxh1Co3AetL8zGnJQn20vRG9Wr29vTy9po75Tyfy3aw8RiSFpNyYW5IGkwSTlTotVnSXRJyKniLeb7Q0mv5xsbTxtXGd/aNiLSP9GNmOeaEJN7e4V7RXnSvd+92r+kS7ZLhktiSzxL7kt2SqhPsbefeh72ivS97tXuxe1V1s0FDQbNBPywdlN2VwcreKGkg8+iTURZk0mriahJTIlNSVmJWkkwvaIlxCbAksxSwdH/JYEnUKX+vaS95j8MJV/c9iBQ0GrRw8m3KzUtSlpWDhYOZg7XwSSGLdeJo4miSeKJ4Uk0iuld2yXOJ1Qm7h97L38PVdZ18Pxk7GTiZPuk5IZwMn8xNuV84bEleSl9KXspeOvTXZCPgsDb37Ir15/5DNlKjKFei3LHUsRydBJ00nSSdLN1zOhk6KTq5FIkU6RRJ
*/