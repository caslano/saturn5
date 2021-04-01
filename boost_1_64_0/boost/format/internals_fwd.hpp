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
ct6lh5Nrvc8Og0mQTHoohOP8qiORR+gk7l2kR2MUeRpdS+mpW8FoEms0MUOXYEhzex7CL5rhgkudX2RWdqyqo53RuksgoPWyuFw9HQfacD9V8TWyUVDGK6gPQ0llwIrfJkfc5V1sX0Qt51t/U/woHSjCRkCpa34IerDUz38h5/1fWbTR+FEl7QvzzVYUOxcjNMVshbaF77eJg5M3H1a/fSctGqndgr8D1SAzUZ+08q05RBAJkR0h3HTw+R4IH5cxfphLk+sOiAZEW53HIvcBGqJP39M2JC7vyL4pgz9Wna9Hi/hyLw8xFbsuvgP1gHxwYvVTh7jhAc4r1Sl2HZbhoT7a5pZx3Wh0Fgix9SO8o8yDTNo/hKA1Uc6ulDdOkVNnY4C0JO9VlVjRuFdHbzUfkcqwucxmplo26Wee8p4qZcZj10yq/5e8p4w09XOX8hSRM0nm8/G5R54syIrdIZbAZNaF2mBbg0//GBProgn7QT0vx3ngVK9FKdakm7xHoxTIm67TM5L5w8Eo5O4Rkm3vpESJ786gq5Yvco/qLB0S9E/qLAfAPIfS7LguSw==
*/