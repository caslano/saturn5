/*
Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_DETAIL_OSTREAM_GUARD_HPP
#define BOOST_IO_DETAIL_OSTREAM_GUARD_HPP

#include <boost/config.hpp>
#include <iosfwd>

namespace boost {
namespace io {
namespace detail {

template<class Char, class Traits>
class ostream_guard {
public:
    explicit ostream_guard(std::basic_ostream<Char, Traits>& os) BOOST_NOEXCEPT
        : os_(&os) { }

    ~ostream_guard() BOOST_NOEXCEPT_IF(false) {
        if (os_) {
            os_->setstate(std::basic_ostream<Char, Traits>::badbit);
        }
    }

    void release() BOOST_NOEXCEPT {
        os_ = 0;
    }

private:
    ostream_guard(const ostream_guard&);
    ostream_guard& operator=(const ostream_guard&);

    std::basic_ostream<Char, Traits>* os_;
};

} /* detail */
} /* io */
} /* boost */

#endif

/* ostream_guard.hpp
fytkefTutVWS9Jgj0dH9f/orLmbRpcMpFuQqKU3KvbBm2g+in2NdM5ZgAceQ0XYQYTlFRiPPNkE/uePqN/pMVw/Nsc4PPIfA51YvsSc4bU2tG9Qig3yzu3i+oOB4Novh3POCAgSs4M7nxcSHLtSGYv14sRqfoMwvu2JV2qbtRM0cpLLENJO0ZN3J/xe6/lvOFLGUPW/pAzp4S+T4N3lfEahA1TyJ/QxeEzD1WYXhvUbY9JYZRIp5w/6lh3PWyqQ5VDJ33dCIsQCji3FIXuEnQEIJcQT1yIy5a6tfjNN6L91zwkc/eyrmzUV6aNde301Qk5vBBpbZmv1ODyp6IhT6r+Hckfv9HztCFMzP3levVeRFF8ch9ysWCq21TCigsptpTr9U4eFUhLiV3Mq+7YgOs3Fa7Y0+EcNFDJJISPjyJ8sG9aqNQPaqqJ1qXOp7j7b6fJWoAHy4qGvxSey3mAAyzQo03PU75pCKq5dIXjcUeOgzL+/vnND8DogPJc7VAiXPFxY2AkzCA1X/ljUicfO7GzIY2Y8/VH2dn2V/mXrP3LcYB1JmTDRs/c91oA==
*/