
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_SHARED_STATE_OBJECT_H
#define BOOST_FIBERS_DETAIL_SHARED_STATE_OBJECT_H

#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename R, typename Allocator >
class shared_state_object : public shared_state< R > {
public:
    typedef typename std::allocator_traits< Allocator >::template rebind_alloc< 
        shared_state_object
    >                                           allocator_type;

    shared_state_object( allocator_type const& alloc) :
        shared_state< R >{},
        alloc_{ alloc } {
    }

protected:
    void deallocate_future() noexcept override final {
        destroy_( alloc_, this);
    }

private:
    allocator_type             alloc_;

    static void destroy_( allocator_type const& alloc, shared_state_object * p) noexcept {
        allocator_type a{ alloc };
        typedef std::allocator_traits< allocator_type >    traity_type;
        traity_type::destroy( a, p);
        traity_type::deallocate( a, p, 1);
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_SHARED_STATE_OBJECT_H

/* shared_state_object.hpp
yU/tAxuHynDUKi7mUoMFl7wR8N0hrN0Xsm1/wV1/o/vRvF8lo8vy+3O20p9zKurP2UxZhiifepKqHHNCzomRuuE4h2s/E6Y+Fp1CoovZIUV3vxTd49dBLHpCxrp52r5LdUM0KSGgRK+Nfw/aCna+3AaodOfZdQVruTlGvs7qATjRxLBPZyktKYN3hemyWK6T62QOvd90odBpocU3s/Vxyp0kvlWWdHmBLqxFfnnoopJvJHG8SfR+F4Y2Jmo9HnnzCPGmbDvy5j6VNzNhcoFqyy9CnoILBW1f/JbS9joDWcMuYQVFT9oxQUDuApWjH72jClJDMpUCEt/ddaho5m/xpUNkPzN/FRmvDRgsNsKlD5Mb4ZiqjJyV8hy1E70taA0trECDSYaFs1Lm8vxsuKwdd7vFTowpe86KpXDu4SO74BL5MDFlC6ycMbD0wC4DgKfe9WeUjAObKa/uys5ova13wQF8zOxZYEGi3fzFHY1vaeLNjm+p4i0R31w0y78HhGwFIfMp9Z7QRn6LQxSex8wawGm2TJxcMIs95RfbCop7wD6+tbQp/TAoVMEBQrEEUNDTk9CGgmIjMvJVAruDL+x2vFS4qe4L/5FgwuW+2rxocbDoTsstZokWNRHoXYn05l6sdWiNHXwWexfp2Hva4RxUjtiKqJ0aw/TaIRMuhDVAP9yeT5DkQs2hmac1xdh7JmDvmSN7T49rxc3o8/jWxq9Gsa2NSyqxtfG/8tPffzvoN9gvl2F6/tNNrGZQpUNvCoNDWwt7gbF1ytcLu3NP1RXJefzMf15OqLXEm4xzJo03WyXiyQNF+MWcKf/Vui1am7fKoWS8FPiN4BABuR9s1ZHr1Zr1qoQnHf57F6K8dCCPfJDABrVQgc8EcvshZZlEWTKj7H6k7G5J2SY3o2ycStnsnsDIOvL17W7M723EXCLkADm62XTwRTXCHd38JfYErfFAYTUTMrnVRLsYcjoF+u8B+GEXYqNKU+iB2qzbVaHFlPW0Qt5ZmKzC7ceFbGA5IGFWgB8kjhTXX+yf2o2Px3EADVYAOyU4p9+K+ShyNFtoja6R7oA4SkQ4mm6sfDdW0uIioyu8Tsxu77JE46MgB6cEcM48G5dYyvFffbw6N90ThhTvjOHDeKbkkCzEfNxrUkqDvOqcRhUN4ot0XlmWSVtU5rUEFfwqcmHXXCym/R7sSevy8WTldmyRSn+PVK3h16DWsKEbTVx8FjNx884pE2f0J5ffoMY22vgko/zoIgWWAu8pWpnNJN4Q4ophixnC06vzS0AJbRqKUITE+KaNi9EX7qyaPK0gmp9V07tgoEg7Fs39P2mivNpTP5db1UBRVS3/YyzRn0oifq0xCbbUxgR7YpMU7L1SsLOvRsHWiBOmP//Wqz/fvd6nF5iFqVT06PVktZ/5Qzn3KxdTIdLfNk0i+z6s4HrjeumqnpVZL+0bAt+nXSW+L0u83nj/94hIvi871J/4sfiyir4vW9PfSN9fLw9bg8Sfy/F3rhB/3xD8fQB/RPcBOPvr5OVsrkAZ5d+Py79FefLvp5d/owjl389I/4NtKyG/jH4G+bUaXrn1+oSQ+uPbRsi/Axm69l59cUT7C1ZkGOi9f1hppN9fZunr239RZPxtnWFsX/ofK8HfE30N9O4dGjG9a/sq90ccEvYl7P7vvvqpNRb2a3vAtaCEXWz1Ro68Itr9cFSwwEJDARYnvu4OFoCECK78Cbc+pFJgN1Rol/hx+I3kfLaFffTn+zPkNBCKzYA0YLS7gCZP24AXuXW9Ev93h20Yutd5Hdi5gQN5sJqmHpkg1qmlG+ZKD/8xFP+S5ToiDhfz6sF4x7YBdqDtfiJ9rBgHaeJqTlo=
*/