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