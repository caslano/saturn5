
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H
#define BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H

#include <condition_variable>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/context_spinlock_queue.hpp>
#include <boost/fiber/detail/context_spmc_queue.hpp>
#include <boost/fiber/numa/pin_thread.hpp>
#include <boost/fiber/numa/topology.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace numa {
namespace algo {

class BOOST_FIBERS_DECL work_stealing : public boost::fibers::algo::algorithm {
private:
    static std::vector< intrusive_ptr< work_stealing > >    schedulers_;

    std::uint32_t                                           cpu_id_;
    std::vector< std::uint32_t >                            local_cpus_;
    std::vector< std::uint32_t >                            remote_cpus_;
#ifdef BOOST_FIBERS_USE_SPMC_QUEUE
    detail::context_spmc_queue                              rqueue_{};
#else
    detail::context_spinlock_queue                          rqueue_{};
#endif
    std::mutex                                              mtx_{};
    std::condition_variable                                 cnd_{};
    bool                                                    flag_{ false };
    bool                                                    suspend_;

    static void init_( std::vector< boost::fibers::numa::node > const&,
                       std::vector< intrusive_ptr< work_stealing > > &);

public:
    work_stealing( std::uint32_t, std::uint32_t,
                   std::vector< boost::fibers::numa::node > const&,
                   bool = false);

    work_stealing( work_stealing const&) = delete;
    work_stealing( work_stealing &&) = delete;

    work_stealing & operator=( work_stealing const&) = delete;
    work_stealing & operator=( work_stealing &&) = delete;

    virtual void awakened( context *) noexcept;

    virtual context * pick_next() noexcept;

    virtual context * steal() noexcept {
        return rqueue_.steal();
    }

    virtual bool has_ready_fibers() const noexcept {
        return ! rqueue_.empty();
    }

    virtual void suspend_until( std::chrono::steady_clock::time_point const&) noexcept;

    virtual void notify() noexcept;
};

}}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H

/* work_stealing.hpp
hIxVj2ICNklLf5wk4z5cKOfSHeBYxqKSo4wKNOiKXD4MdhznB006PvQfRX5Y4/kwJcsqQ9iFZr/ub7oQwxghJJnf/IkWxNbXX2XdjS/B2JpSOokKeDz/kKcPFdKEESSXiyJxBMVsld8LVR3smELhCTtkmALfr3yg8ONX17Is/JPkW/k8+truhZ5l8PQuZR48U1QELkebMtmcYU/WgOymQOQDRHsVImC8IiCoMmyeXKzWrtGp1E55Nn74RBmnZp4ce4fDGQAM3Xcmikgi64D9IpLIG5DKQhHCwHwNvjNrnxH+WFiPByjNAWEPq7Ks5apkU1X+UEIXRrWq3PQkq8rJtlWZplRliqyKQ1blNqesCq1aZAXvQuWNZuXN08sb+KRAnuPU2mGeh+AQoBzx2lna3WBFGmJfWF8q7MUJNoU9+YQobA/8FP4j0giHPppb3V55i5Gui2fqF7zxB3Oi8K3EtVT8xkVP1rAglrNnZjb6SIeK7Eop2ESJLztKOdIUEHF9j7i9R692u6Kn2BKFF5tvb4loYctEPU1F5PGMVik8L1rwVuSnb3w6BB9V/9/xo/jHmPEPqTzzKeXqXiwepxD+vEqOdskd1t5E7ivueEnSD8BFPTjOwWG6gpl8/CTHPRJId5jGgJvfBwQG7RBhzND+Ma24bjSBX6GA5xnnv4/y5hjKmq9kFRgnsKyxlDVNySo0/CxrAmUNZ1m4hPZ6/wANEInY58uZBelF6l4uCJA5jmzUN5BUvXG8PJibL1eJ6zfB6jKTm7+ReRznJsIJ2eGcjTh9pZsgyh+0cAT42AmwHzS6JtB3mt+0MsdynjmR5nY+FnU7FZXKiqrUi9pXD3buO1UjYIFpBMwr4VtmiVw4pHtAklO/7HcRJc/ej4G/lpxByxwKVah1yV81qIPyX9LTvpC8heSVj0rcn2Vc7I7MCbIREyi2z0woIppG36fsj/0IQQRa+JRY7bdSvbvqeZo+4sRJPS+ZQz3yi7Gy8xfIHqmsg85/ktz0K52hdvjHFUrBP0nVg/iw66dEiR/CqMzTqfQGKtElYAGkiZIJMPUBzBh/lR46vVz2TTnq53Tmm2YXtIGcQAvh8q74XgUKsfheucar9XIu+3XQNbr4/O71nDY/mzu5lGAt2bPhSnzlMd/HNHZcQsnX7mPDeA61jkaqGMd8k+R3r/xCrKSRrV1yvdXZ4kC+cp8cyCx+4cFQgW3jfSc/yy0NAbpGvg54CMFk3OzQ0yP9cZBZQtSTamg/mULBx/PExCWV09xYElNqaOuq3k7+h8Nvb8H/sGy74n/4+G8S8z/stt3qfzjkybb4X77eaMXftbEN/os3EbqJffE/OHbr5+Fs051FBOh+iAhydBccXogd1Rlajn9cvpXPQD7tsZ6mBU4Be9FduAnnnPWtDw3zsZwB07N5zqRbWc6xIieb5WSOgt+xnIESLHhDJAZ7PcT4Yrd4ZAz8d5JB20mT5WRTOd/t49S2TGPUPt6H1N6cJqjtu55RoxM0neBVSLBeNrLhzgiPKbNiZDqSuh1IGe+/gcVkXsvIXiHJ3hGf7CggK+8fL08Ow9foSYT1xgbuikU/r8axQnd4d6JquvYbtwP3TPQboir0wCqcSVVoz6rghiqIOLSJR2E4dB/r+Om2VU6aoLHgOXPcuJcU4h8PmN4Pp9ypd7AeHPUN70FnGevBI77BdnaHH4m0UY3//QwVLU/ZJv4BbF+eN/f6HE7aha47PBldcx3+dChhIRa3xvMYZMO5ycPwx1HdHu0kkHf+VJZ3KyTW78EFJqfjcdns3Hwvr2zGsdnM2DZ0eywnQNDzIC86bptnAZKiAo+gAm8cgQU6qcCjqcBRrEAf4js=
*/