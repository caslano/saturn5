
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_DATA_H
#define BOOST_COROUTINES_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/coroutine_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct data_t
{
    coroutine_context   *   from;
    void                *   data;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_DATA_H

/* data.hpp
qh+ItbGSf+uZdKmy2hLxYukHn/5WFleUfleYWDd0a/5gbsopkJ6hqGL57uFdQ2JgYttQ/NDjzsHO7Q7Y3KSeu01QN90g0yC3Utle0V7ZXsle5UwxonxQ04WJlzj3e668IkOpusZh+agmRNPtuyMTHw9nci55NnluRhqTYnKJdimTho3GscZceXT5WHlV+Wl5NiMHVXqM8kDJ9szpTPjhjst3QZHs9LPMcWWA8n6JTAlspnBme4ZwJvhw+urIxcLTztOnXbCLo0ugi6dLpIuLNSLetPENc3/kaZ8kh64i8UyfYl1NGisuCbAv3rSbX4+SXZkIq0/dqekLYzXxQuTclrRTQ6vWKtsZUZ+i+TtBwszwicYJessErvL0K0XLEod3Qlz8iZlk6UMTUeNRE4qjRJbyXBVcyelN6dfpR6P9o3uj86M3o+NRadGj0lZmDRdLN0tgW2densycsdGbMUsrDCtgA13D3dLU0sVS+NJvW2s312bODt4OUf3stbS1rLWMtZy1dGJgfNuBgS2b6IJoaprCePHeNDC9rbvtZHXDwN7enE2MT5BPlI9DJ415rGpca29+b37/F5ACmAnUB64AhYAFRIxSCnXqnbNG8kkJxZqMhsNJ9/JL018ZdcgZdxUKiy+mJctVmZK1FZKn9ay7NFntkngV9ItPp5XlRmX2CmF1d7feD96mogK5GSoTVnsPew2wQFjbXfzd4+PB
*/