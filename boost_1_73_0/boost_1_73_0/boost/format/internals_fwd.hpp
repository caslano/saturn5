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
6zvYNztYXAXaCklDuKxFoz5BSQlWwnjHcz8I40lsObywfmI8q9qcwokO2Ymw/GIZ9Eyg/XkmQz0D2yXKo0KVvJ6FbX2/E2QlaWBbbVLbOjZJnXrxOJqEySTwrZBgjUi/UItJoVphw9FdSYzua72qEJ26Xuy0n0FxGiYklr0/k6gp/C4J49VaRxF8RbGV8IziuVGlMPIlK8Fy4JTmjN9qg+aUWFkrFer/9Wh0RZs1xF4yC7FD/N1SqboeQGrUWkZ0AWGJCD3YS5QFRRytetnqsOQZmGU9R8sFnlwuVNeWMM2/KK0NIfrQaIhG4BEEUuDx02GV2Y6mpROU05N/5s6mieXPplNjCKMgCcbBNDbsGZP3h3sZTj0jmk4CphqfvxEI40wNsZ6sGGrjFvyDMnihH2141A0ONgwaJWtsgfSe4LGkTiaWowECveltVBd5v8+8OOmsxoSW1FD3boz/V+4gSsKRexUetxyZl+o4w97BVaqL9/njz4eHO3g76jJusLbfkoK9E4u67Bh5mk5WUcLbejP1r+UUzHDtXrmTqft1Mp0kc8vN8+4ddeB82HV2zYIINxf5cOVOZ54VUYWdV5oNeWlwAaxrsl2FtdhlW+tUaW73i2b+hR9c+2lgDpx2QBHZ2BetHmSWpMFZeuld
*/