// ----------------------------------------------------------------------------
// internals_fwd.hpp :  forward declarations, for internal headers
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_INTERNAL_FWD_HPP
#define BOOST_FORMAT_INTERNAL_FWD_HPP

#include <boost/format/format_fwd.hpp>
#include <boost/config.hpp>


namespace boost {
namespace io {

namespace detail {
  template<class Ch, class Tr> struct stream_format_state;
    template<class Ch, class Tr, class Alloc> struct format_item;


  // these functions were intended as methods, 
  // but MSVC have problems with template member functions :
  // defined in format_implementation.hpp :
    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    modify_item_body (basic_format<Ch, Tr, Alloc>& self, 
                      int itemN, T manipulator);

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    bind_arg_body (basic_format<Ch, Tr, Alloc>& self,
                   int argN, const T& val);

    // in internals.hpp :
    template<class Ch, class Tr, class T> 
    void apply_manip_body (stream_format_state<Ch, Tr>& self,
                           T manipulator);

    // argument feeding (defined in feed_args.hpp ) :
    template<class Ch, class Tr, class Alloc, class T> 
    void distribute (basic_format<Ch,Tr, Alloc>& self, T x);

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>& 
    feed (basic_format<Ch,Tr, Alloc>& self, T x);

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>& 
    feed_impl (basic_format<Ch,Tr, Alloc>& self, T x);
 
} // namespace detail

} // namespace io
} // namespace boost


#endif //  BOOST_FORMAT_INTERNAL_FWD_HPP

/* internals_fwd.hpp
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
*/