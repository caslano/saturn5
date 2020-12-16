
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_TIMED_MUTEX_H
#define BOOST_FIBERS_TIMED_MUTEX_H

#include <chrono>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
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

class BOOST_FIBERS_DECL timed_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };

    bool try_lock_until_( std::chrono::steady_clock::time_point const& timeout_time) noexcept;

public:
    timed_mutex() = default;

    ~timed_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    timed_mutex( timed_mutex const&) = delete;
    timed_mutex & operator=( timed_mutex const&) = delete;

    void lock();

    bool try_lock();

    template< typename Clock, typename Duration >
    bool try_lock_until( std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        return try_lock_until_( timeout_time);
    }

    template< typename Rep, typename Period >
    bool try_lock_for( std::chrono::duration< Rep, Period > const& timeout_duration) {
        return try_lock_until_( std::chrono::steady_clock::now() + timeout_duration);
    }

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_TIMED_MUTEX_H

/* timed_mutex.hpp
TR+CuHIELiIkiHZqEqQFm0qEEHbkLBvH8Q1LLgqNNjcbiVuSnez6L1Eu9v6+Dvv7gq9Ff+fPjBO9dEO0+i4/v2O4QT7izZG0i/WJPlRivdpqkqPeyDp3j72KK1L4lSxV7DVTXR0RMG1DCUhdHqAM6zYU5zKZjSiT5VhGLtmWHk+NCaOqVJ+n7w2MS4QGmu9n3NSCFpdzjLzTkl2Qmy1SUyjVb3SDVOT/8UTUWHnDVo4kyg/NDpsvMN2UTs3PNkpORaLohgJFVHfjCkjFPnY8ERVRHxWVRHVPBEJRx0uifJsyqPk+4x6fIMovUlOU/OZCKsrueCKqQF3YL4nKgWZHsF9JovybUlVHe+lHgqjuIjVFye9JSD3eBvhIecepn4iCbgeEYr+SRHXf5FEdbecpgqgckZqi5PcBpKLsjieiijSKYqRFUXhVR8s6RacoEk45/hTFaI2iKLIoiuaqow08Wacoepx8/CmKQo2iGG1RFMmqo13fSacoCjsdf4qiXKMoCi2KooXqaCs76hRFRcfjT1GENIqi3KIo0lRHe7mDTlE81eH4UxQzNIoiZFEU6aqj7WqvUxQftT/+FEVQoyhmWBRFhupoHdrrFEVS++NPURRrFEXQoiiaqY42KEunKM7OOv4URYlGURRbFEVz1dFK2+kUxVXtjj9Fka9RFCUWRZGsOtp9bXWKYn5bUhSasZmvN+KXtdWNzX6Ex2/G0xlKyCExmj567155061XWc1nUlvdqPjqJBoVPLoIXbbsjAXYdkZn7o/PnaTrjw8Ruhzu14TOZ+4GMXR+QSx9XfskXU8IE7ps7lGEzi8FEEYSGJ1ZWbc7SScDN6HzsSwJXXezjmR05olXTRudKJ5pE1cURXZRJCuybmqjE8WYNnFFkW8XRXNF1pltdKJo0yauKCJ2UWQosv7SWieKV1rHFUXQLormiqzFrXWimN46rihK7aJIVWT1a60TRdfWcUVRbhcF24qvWulE8WGruKIYaRcFu3MPtdKJYlGruKIYaxcFO1LhVjpRnN8qrihKHEXhbqUTRbRlXFHMsIsiTZH1TEudKO5vGVcUhXZRpCqyxrTUieLiliyKnANbW8SEEJFCWB396HrB7haKoA4tdUJIaslCyEZEzH4RQIwh8isC/XCoRcf+FzKZ/T5EZGc8IUIWN1NELMzUMX5qZswkICJmeQE2mBEBc5srIi7M1LH8jExmeXdAZOv3jMgcdfkmQ8fsbRkOzM63M5t7/C8zdMy+J8OB2YWOzB6boWP2JRkOzA7bmZ2hiOiYoWO2J8OB2WPtzGbn+L10HbN/k+7A7NF2ZnsVEYvSdcyelu7A7FI7s9MUEcF0HbPPTHdgdpGd2c0UEQfSdMz+a5oDs4vtzObwyVNpOmavSHNg9gw7s1mvj0vTMfvSNAdmj7Qzm/2cTmk6ZjdLc2B20M5sjyLiD6k6Zr+Yysw2K98c1S03fvybjneKZYTENxJt8+K5qTquTyKM2Tb9my1ZVq4wdieMyOhURdbZqTr2t0+1+Zpsb2japDDmEEZLp/+khU4Or7VgOZgNol8yMaQwZhNGi4mtbKETSBlh7G6zid1l1y1VGH0Kow/bSPT1aaGTTOcWcSVTqJEM+zxfpOgk825KXMkENZLhWcDyFJ1kZqfElUyBRjI8HxiYopNMj5S4kinWSIb90K+TdZL5S3JcyUTiSeahZK3/kxxXMqM1kvEo+i5O1knmvOS4ksnXSIaN8RGvTjJ/88aVTEk8yTzm1UnmLm9cyYzUSKaZou9Kr04yed64kinSSMbD9s+rk8yu5nElM1YjGV4O+HVznWQeIIzZ0hiZ+/Yl3132mMNomdBcJ5PhhMtntkdkIQk=
*/