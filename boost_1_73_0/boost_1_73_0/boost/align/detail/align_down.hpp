/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_down(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        reinterpret_cast<std::size_t>(ptr));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
INKmCsY01E4SmOeWx9lYK5+no6+COww0NeJL0Y8R8qti8j8wRCNP5JfgNAtfezG5UDUu1Ilj1TgtERcLxA20g+CbEremvuqCcSap8GdFvYZMAbUg0xB/2gsnHoV1EWBxVMQXyGAdjjZUG4PJNnyKc8stL7/4VM5JwbZCVXdgLtvihLRKheH+o+zN2jVZ1TyUjMBlM4B3BohjrouURH/Wy9pwI4JmM8BQWizy1OfrVZpFfNPLqZWv3NRlJxUKhppQHX00vRZdbuJIYsCYLOCrQBFpLcykh0v3Ex0BEKus1VQIa4aNyfmLhspfi+DjMe5d80N5QH1XdgxGDHXC7xWKopsZWrcGSaRNw4J2FoohMvy7nzXuZ7afpLHp0dEBEkBl6gNj0lAR2de+YevzNq2epz5JW032NPmBh6DZOckbtFjXtebUl9cViHfZmeT28PTuqrJdbLgYtu8FbGpuJyIavw5BB2mdTQ/QVOuMybfPH9kvcAxs1P4z32CoqhdCkXtWrJ1+XPKtpfuOQq+B1JWUPhnFso3gWyxS52KlQro5IXGp7Hp/oFCzUxCxcq0flXKYp9IVG7GSPxTpqlbI4UfDNNxeGcfb0WoMLBSQYVkNZZzhopzNtHZqPv3oFVo/elEzL7h08vbi+Oj9+TH4
*/