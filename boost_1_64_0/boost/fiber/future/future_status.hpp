
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_STATUS_HPP
#define BOOST_FIBERS_FUTURE_STATUS_HPP

#include <future>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {

enum class future_status {
    ready = 1,
    timeout,
    deferred
};

}}

#endif // BOOST_FIBERS_FUTURE_STATUS_HPP

/* future_status.hpp
paEnHHp77zvXkhZKszC+tD3Cx/wgt30MePaVdWkq2lfAF8wAYhvMcokOu2xS/ZsMrOzBBe0GzNODGxX7i2Fr/zx6A4h/7KxkVSym2AGqPD+JAFLx36TmQEFxZTBN14YHTpZEmU0eSsTmR+0qXaG7BsrINOwu28HpsIUgS+W4WUZ3DouRj52mI0qqKYRhsO+cCHr5LumT3vdbGSVcd8+rL6wauaBbq7MacoLu4lL+rTyaHMRqMIehdn5OPg+yHpCBoCb88hOjzNDNL5ob0byKo1hgLXFonLH0n6aQ25cWFlCvNp9zbJF6xku1uoNNmHRa5F6V/RYCKsuLrXeFXEzMqcAxeE9Bm1Tqc4KLQE5YKnrw/rLFs+nv7hemxAoxye54LpuNx+dto9+LzbWo5Hd8YEUdJLAFLmN2wfnrOWQS9hW9mZvkRf1muKQvGwHJmlWXkRU41txu8tGlBIz5gyHFBbAGQeRLbAa1JnvyFqza3eKbI+/0HJRPmCgqUtj18Tv0Hha6uSkiFUMWQgYKbbSpc+J4M2Mf3pXjkrPredbJJsb80PZfsvWU+uZtvw==
*/