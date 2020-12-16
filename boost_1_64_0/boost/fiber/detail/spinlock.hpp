
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_H
#define BOOST_FIBERS_SPINLOCK_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#if !defined(BOOST_FIBERS_NO_ATOMICS) 
# include <mutex>
# include <boost/fiber/detail/spinlock_ttas_adaptive.hpp>
# include <boost/fiber/detail/spinlock_ttas.hpp>
# if defined(BOOST_FIBERS_HAS_FUTEX)
#  include <boost/fiber/detail/spinlock_ttas_adaptive_futex.hpp>
#  include <boost/fiber/detail/spinlock_ttas_futex.hpp>
# endif
# if defined(BOOST_USE_TSX)
#  include <boost/fiber/detail/spinlock_rtm.hpp>
# endif
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

#if defined(BOOST_FIBERS_NO_ATOMICS)
struct spinlock {
    constexpr spinlock() noexcept {}
    void lock() noexcept {}
    void unlock() noexcept {}
};

struct spinlock_lock {
    constexpr spinlock_lock( spinlock &) noexcept {}
    void lock() noexcept {}
    void unlock() noexcept {}
};
#else
# if defined(BOOST_FIBERS_SPINLOCK_STD_MUTEX)
using spinlock = std::mutex;
# elif defined(BOOST_FIBERS_SPINLOCK_TTAS_FUTEX)
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas_futex >;
#  else
using spinlock = spinlock_ttas_futex;
#  endif
# elif defined(BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX)
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas_adaptive_futex >;
#  else
using spinlock = spinlock_ttas_adaptive_futex;
#  endif
# elif defined(BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE)
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas_adaptive >;
#  else
using spinlock = spinlock_ttas_adaptive;
#  endif
# else
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas >;
#  else
using spinlock = spinlock_ttas;
#  endif
# endif
using spinlock_lock = std::unique_lock< spinlock >;
#endif

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_SPINLOCK_H

/* spinlock.hpp
zWsqFU43rJ72pjsHc6WXzsFgWMmveJpJWB2h6NKcblht4M1gWsbnpdMyGFnyY5sIiawPPaY6kXQj6zZPBjM1J3voTA1Glvwmpo5EVkxRpy7dyFrWk+7kzbd5dPIGw0p+txIlYfVUnqlLNN2wuiAv3fmcA/PofA6Glcxx6klYhRVd6tMNK1deulM8b+fSKR7wZCXHiZFomplr6hJLN5qOz0131me7XDrrg9Ekc5wGEk1+RZeGdKNp2J3ZRNAjbjoRhAElc5xGElDnu02NGtMNqN3ZTeQvCB0u/inbVH7W7VT+stDFuiIZm7pNjtcFDUiOV/l7Q8YJmByf8qeHjBMyOaXAmQZKjwxGu42fnf38/45jc4Z3GLu/d5xf+OwILMXR7vxnS3Fkj+yRPbJH9sge2SN7ZI/skT2yR/bIHtr1fGBZjsSuT8wz1qfc4pnFxPqU04z1KeNyfcr27xkTVkuQi0sedOm8EViXsg/XpVRWrnz9LmVdSrghccxsti5lq7zgpkv4upTYGF/XBtelnP7yPCiGZ4xyXUrr+l4nDWDXzJW9hl9ItYaocmsEb920r1VZr6z9+zxlPSEgPet2zrkmd0AQnYLoeaNjPUHMEcSl3m8NCaJLEDfYvfhnQXQL4tqF8RFBzBXExcobWwQxTxBvueDXAwTRI4g37vDbY8ZCaVMqGS/jhdLS9B9uqSXj3FLW1VqH7jAsnUF73B+feVz44/1PpvBH77dWf8yfofPHujus/vjxc8Qfyy+290f3i2Plj1GQOvzYPHV91CAuK4ZrH7bIhcPQgHJ9VCSNxOVSbmFlfVS8OIzLiymrm760II+vjxqm66OGcMHOLlwfNWULU6EF8CGxPqpQNKAuzhg6xynXb6XXlKZxjXeh1yzsAn8ayvjTUMafhjL+lBeExPqooSRzl3vl+qgtcn1UjJKrpjGPwOZhMiUIy9NVtpXC//wlXY/AUnZTWGsMST/cOVwAb6ZH4vDWkV3j95R0XsTIQOSietyni1fpC1lCExBaCN+bkq9lzt+dbZ4yvzuF1t4Jq/VrDgOpzvYp/uM81fH5Qw77flS/KmDjK9D9/C0s5DgR+7U16xeuajo9u6rpPzyUp57/IZv8oHHYJj84+LP8Q5PygzPvPPiRpPzg6O+PqE3KDzb8cYebkvKDU3cq3jEpP5jakntlUn5w+9udyyflB0u/OHdPkR/4xzA/sKYGvz8475+vr/rAg/PSXF/Vn7y+qp+srxqQ66sGrOurBgRDWV9VNNKiXV81OHbrqy45P2/RrK/akry+6qxE3kLXVz2LXSP6r6yv2vIvr68atK6v2mJdX/XFz/P+q+ur9rkg/71P5r99Mv/tZRxIUAfh/zAzzdZJrWO/nQ6kD3F6F/NkcS4mL/FnZz9nMfc9dmvLmqhxl1ilLiiHKUqvkiMVpZvFDKXXyPGK0sNyyKJ0OejlUXpEDlyUXlfyGPYenmpbLiVXht0Ifr6KZkpeGXbSUhi3Ue5X0gRiEzEeds097pzuLl+zS7FRT5cbzvk0/jKMhhH0aZ4DPpRgjIfLBfFKRmSKArEap8TPgWzPI/gnIR+IwGe0Ohf+vxZC3viKNPzzq+zj0Ug1my43dTuvvPlPn8PlLuix+aI0mFgB1ZkK4pYQRB+Km4ri5JqyBYL/5SecPw351i99Q/il72T4mLVaEqqQAMoBEPithvlBMp5jt4CPicfTf42MSNcSfXJq7O20sXdNIsJ0FSvUlgvi6tiB6WYHL5P2Bn4h8i8zOxgx7B1WPiGu4fauVe3tZPZe8LvW3nWJuz/m6lwl7Q3EqxgRl5IV6vRKewO/A/m9yBdfrdSpX1bXCfMKQpDYO4L2NT+4xnM=
*/