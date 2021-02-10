/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_DOWN_HPP
#define BOOST_ALIGN_ALIGN_DOWN_HPP

#include <boost/align/detail/align_down.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_down(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T(value & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
wSxAyczWM6un7fjy9eHbP1yQ7PXEBZ98xiMiH1mJjrweKFrZ6dh6hJsVLm3/hLA+ee7MDtLtrhDHhHSuo9EPUr0zU8r9n+r5Sq51U87Xql3I0yVUCWB4uwQ0cBNFPD+CkUPW15KcLfN1glgpVAWJ3U3H62WSI8As3GS1xANFLjeUVhOEAEZiAk7vij+wmZCuaeOdwGBKAXolj30qW0UBDHAra5msg+U/mJeNnQBatBhoiKNvY5S9zu/uotpocr3guixIJK/uZsAoR/UE6OUXQWjgtAZuu9bIRrmALnVN8VuQuqQXivBWPowFqyz7UanCZAUNR2jf9CNuXPejFEquECwN+XUO4xqpZNgFbwagAs+dkNsZzZq4E3J2XesW90SJCtYJITJc44lsZVnouCBGemdEXlk5I2prf0mFqXvMC85HC7Yyyqh0NFD5HNGc5gfGXwLjqmiGJgWoBE7JXYnjAc4TZ6YhgaaG1LTChrgHs4p1hUYOupB6AVQXeB0EmKrHthgbjNrRTbeY6736t3Gw8tRLKqQmPkALBlAfP3q0PwjPCRRaOdNWDn32CWZl1x5A2aJtXWntveC8IBkJCg7MfIO1OALjEgr8q5qYnrdtLYQVJDBoZ1yDDiIzHpljwCeComhTcch38YjU+8Jb
*/