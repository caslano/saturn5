
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP
#define BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

struct forced_unwind {};

inline
void * unwind_coroutine( void * data) {
    throw forced_unwind{};
    return data;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

/* forced_unwind.hpp
orDeyoiVxv6ywtyFbBOtFE1svNWV+ZJSip5Z7TmMiDpQammMExkrOE6kh/iwFSHX1oFChuhBCbfW5pZ5YjOeCP8G9kOzzZW8PyCJf6rQhsPe4R7YzWqhCwqlEJ5OnIQLw83GJ47jzTC7sU6s9mguZrwq3E4AEVzUa0SNxmnAvSb9QCuxzMh3s2a/smyt1Z7zwERXzdyW6wQbeEFcF4VeIxmLDYV4tkexBYo2XjTGNWvp8wJLu7OfhZS+2g8ojqWIAPphxvi1B9ZxlLSb/kWdgFrWOQeJlDK5RaTMiGAagHhAJevS6DuZ0tDHRDlZ4C5bHx4sbCNClHYPA74J2w73TozwUVEj9aiNYmIovuz2B72Lrf5YaDfyr+54IVPvqBUcYF9S5IF6uVTa4AzDneO7l1uKsWkes+VdIjZdA4o/xJBALASGj0JIboWzX+OscWzqyu0EwLaEmm0ldwEY691zHKy16Q77nqszxiKVMcCjOm+ftfGmc3oUdV6+ijrR0dnxUbvdPjw+xm98U5+GuNo5Osbnv8/OOv+c4f3zw+cvXp6wKJOM0UmI54M/SX1r8iW1DhVoidlhVKG3qb28JIJWATvUUvei+GpCmT++g+DIZjgfDLbKLfGkSLzi8VTD1KjAWwZvhSg99HaSGV2R
*/