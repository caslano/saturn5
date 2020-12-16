
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_DATA_H
#define BOOST_FIBERS_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace detail {

struct data_t {
    spinlock_lock   *   lk{ nullptr };
    context         *   ctx{ nullptr };
    context         *   from;

    explicit data_t( context * from_) noexcept :
        from{ from_ } {
    }

    explicit data_t( spinlock_lock * lk_,
                     context * from_) noexcept :
        lk{ lk_ },
        from{ from_ } {
    }

    explicit data_t( context * ctx_,
                     context * from_) noexcept :
        ctx{ ctx_ },
        from{ from_ } {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_DATA_H

/* data.hpp
b31ZKdvUHIQWLtzIbji3kUGGNLub6IfToA/gKtfYxnzlbKLz/OMu2kPZS35DCv+0W2EXmX34ZhjgVWP6Hpg+nqafpEzfDNO/TtdruSdbNMPDRl9N/6TeCX/8RtA/5lEd4U9sKo3SJ/U6x43wIy21Bd2HQLJKbQS/5pHR2agG8Gsh/DI5AnHdrjVwlIwcfRCJE7sKjnJI9w7M69+y9xIe113dF07yWhWDc3cS63ew9jvMvotUBXBD3xtnC6oicKeY/9JKfkWrlRPA5sVfZG88PPHu9oc/g0zZL27EebNo0B9YSOaulqLtlvNgJmlm1xFXx/Gg+vA5GlvYAfk4V4iRzUWiu+Bd+bHRJYUTyM9p0pRCyafvV05u0qn4Rtij+SwCYA4EmFM5zO9spzB3hTY6gXRr1wzk+3hh3BjPTsQlYljIB9g9wDcTiQHS1aUens8bGLFQkDWImLvh5IcKEri0Y+1rHJVi80Ju80un/m8raH4km350Yrqmv3XqZ4W7U5+Jd1jwk17wbu+4XT4K9q9yEDtOki2FFa20eiAlkgLeHPdKwRfJ8iEG0eXx9ix4JD2vvwJBe6ARgJYFoM3koH1PJjCqJpAMeFcJ/E9Ek3FZdUlGRWC2zMjaXznBDVkC0Qfm2H4zJs5id1vATzQ7uAc4B4pSaIK9r8hPAfKzriHuRlfw0wf4+Y3YF16ySPlG2gy7iZU9ziW8EwnnjivWYxa93WXx+zaSxQyeBUky2NaXJiZxiw241tsQq3/AO8plNUp8s7TfOhznohTE5wHxWwhxfpAL2unuJXQfu39VC/JFzjeVUBLdi8EHifyAQbL9pjJXryLHicmR7ueBTCV/nxuAfGqnuAKL5P+esIafHv2YfmrOzjXQNUue0Eq+otNTo1McqS2ZOCA+VFiMXJdF7o080N43fmr9nvQJfeFL+sz6AjHMTz0vo/2745Qtf5jd4tqDu+EwaxQQ3kRCwLXNdHf4Ao4DZJwx0k9ZymMdHNsHYb8s34IeS3erxjqvVYodGcP7gYkwQUF+AN06sPnQHWHHanRR1ZVv56VekloRm0fPjOz5LWcb68AQeqaWRfyaJhZM/Npj7cC50ix0TbcWjIaRQ5P3Mcx4/4x4TruMXYB44w/UTvbzLSpqeDy3DycOKdoHvhIOFwu4Ng9zKgWbB/f5ldDzb5ifLcc/6dhl7IKOVbibuxs2FJK62jvtUO5R96/6yYzth93ZflRg+0GD+IVAv5KuIl+hJu3HWpKOJDvH2w8rSXGOtR/nePtxjrcfGIztB/cwHhLG249RzvvvSW+hqrfkn2cXaz/s+3j7ga4L4Iu982HKVxdWc/jVRlDvQOmxAp3M2dayiBiH62QeyKeGQt6ZyrzbQ97HSduFxrEZXgrFW6Ez0mYSvEIEio2tUBcsVQJStlLKg5WUD24klDMJZWnjZRdnG3OOtzE9kMCvIW4IzAQC8Uigi1TReVG7riU/oHj8RMuHlMY4JY0eQMPgwgQ2qbhhHkgqGowkGh5X8ARajSdCsBGLm4OahFfGS41YH8y5E805TpnzoWKS8zjJ+Z1dbsqtzLNLB6wT1xB9ptcnJardNxIjv/Xjdcq4m5uTYvjNSWvRAUfHGmbWxs0spnW1sZjeHS98IQESGUl7FYJmmPJncuxXfodW35mWOjpGzAai5KqDQXLjlZKbv4FIrpuR1zfDiFvlzX1n1B+kM0Q6bxLsplolAh0zb+tJvWajyflrXNr6ASQ9fhqY72zrrVJbf4An7JYvtdH5BmUfhCTpIH93uSeMH8VAMv5IxuR4Vrp+LwXDr18ihT/Is6ctfi5Mz+0JtBjYfuQRWOzCulDsZGWxnyJDGLSE0hXlIEo=
*/