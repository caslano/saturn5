
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_spinlock

#ifndef BOOST_FIBERS_RECURSIVE_MUTEX_H
#define BOOST_FIBERS_RECURSIVE_MUTEX_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/assert.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class condition_variable;

class BOOST_FIBERS_DECL recursive_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };
    std::size_t                 count_{ 0 };

public:
    recursive_mutex() = default;

    ~recursive_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( 0 == count_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    recursive_mutex( recursive_mutex const&) = delete;
    recursive_mutex & operator=( recursive_mutex const&) = delete;

    void lock();

    bool try_lock() noexcept;

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_RECURSIVE_MUTEX_H

/* recursive_mutex.hpp
r2h0Fw00WsrhaETr6CK0ohVYfhXIoVE7XIjBrZhwKyYcUN0GDbIM3iF5DiYfOA6l7soFShrPXkDSuPN8TD9RpodSx8OTPBU5RsnnwQtIPkdVSfmsoA+nPHulxbOcvPGKQGuGOhNsZmQ+jv9jWryBZhz934NXUOQR26vwOC1davXPwAuAj4HDvTgTRFPUfcMHeM96TS0c+lzhhRuYYAUMBMGeJzYqIu8gVZSn1LsBB00hqRPgUZ7aSz1NPtfoemrZ/Dg9dYqup+Zp+U6Zz3rqSMQo3SGNTaFuWpSRzEi9pqr+CV6Ag1fqhaK5A/5M6yu01Wcx5esjN4h8VFYfgSedvzXwDmRjSgTSvbVeKIzQ/+tV/x9B/b8e+z9o8OzGed1sGDDlW9pM/GZj00ihpE+j2aEvCME/cuYkPZJKGC+cZdYUvx0mVZ1RKSqqZdVvSFPSFKJNh8lSePhA5fLxYtT/VAFPinIF57xfwPpH5P2VlVG+J4zcLBTwCy6LzjbForPlq5J3ufiSI+h2g0AO+Lqv2omb0rDS8B5cAo1+dR1+O3JFYE3y4yESUYXUV8t0fXV0nZ32+TsFkwswEYyIkCfK4ZavIMlsNqqS/yDV0lzdVQGZ+x45UxexnlYk9LQidL9O8y5cCMlAZNs8VNPKYH2w4dqMRSp2I6hrvoJmqN4qzMaUBncPahFy1igmKxO6Y0/txh5fKBW41pg1hNYgOGSBlDShdG2odyP6Bidb1xETPQpXy/AVoGsajWeaJWjj0WJsK2n3w00fLAr1t/v8vxks2+NF6mx3zAW5v/cYGPBmgorO/fM+SCaAQwmZH7hAvxpOH3WwQNQdcJyNOFLROWyGES0R3WkkJu3C2YGCs8I3okEmg0b7dfgVyqB3Cb+Xqm6gbdyOSUNxJvuOnFFDk9G77AKHisiM2okxGvADH2shTwiR8e6l4iTs+doB/tMFYBczYL8SxUzZEAGRjxCpBJEjIErMEOFiBdFXQNDFTaRJN5wvNOlN+zTp/5lfzH/haYt9Vb2zLt50esxfLpp91XvZdkoTFb3l9Dh/tfE55K92/PExf7VROcJD7dZRQrrH0VvjqM74q7H9TDcK9ybyxuoDTcFQqw6kLQ28brWqDygZsKnMkU5EVrTc34EiaaG05jSiVGKhNEBR8sC1D1YankgqHlRLyjmN1jMjiAy7z0JrrSTTaS6MzcaXZyvdbz94RTasa5CuePSJxr5PcJB64Bdo6hz+5lxU5s43np9kut+uagjdMTbvYqGJr4NSUHiVKNyLsrrAkGyJNIUniSABAC6DkpEM4+k+AvxyMXqmXox/aPs6cyLysP1XkL27Fx6W75NRTt/nrgMSfJ8cm++T04nvY6G3fBTRO9xCr5+kBzeC+CzkfO2S0XAXE25qdRKCO2h1O2AONOdnFUoIsubYCQFFApsqvZ2PIh/JqnP4RrwKSrmu0iQK6ih67yKKWY9289lA7aJCefubsQ0lgbZfUqdBFpSYjiU+Gd22G2471Ot/qlrUi1OmcM4PyXxzlqr2/rMTV7sYuPq8FhfXBWKmfgmfjztK7Dg8Ds/4U5VorhWVeAqLDOxsJYjVW04hMTh0gFkMeiuxg96SJqUtwBGgE+MbQfjU0td4+ijRs7y1omN2rVUL41zMjRk10BiIO1ZyrzXHCBHcx7ME3J9nKbgAwwUkXECH68wCW//xfDC/jNpjiFhvV83i9XaC+p5ZplbYhVCWW1DFVZahGTyyBX0wa5QUie+aOQuVsoPF8+cz4fnbgzqIX8X7+1r835OJ20z4+MYN7AJvX793EOKekxW/N49ii0CTNNGCVryTHDZBm4RV3EIxf4ZezsaTnmeWLZT3b6I=
*/