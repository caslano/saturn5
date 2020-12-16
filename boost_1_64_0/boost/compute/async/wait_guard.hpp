//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ASYNC_WAIT_GUARD_HPP
#define BOOST_COMPUTE_ASYNC_WAIT_GUARD_HPP

#include <boost/noncopyable.hpp>

namespace boost {
namespace compute {

/// \class wait_guard
/// \brief A guard object for synchronizing an operation on the device
///
/// The wait_guard class stores a waitable object representing an operation
/// on a compute device (e.g. \ref event, \ref future "future<T>") and calls
/// its \c wait() method when the guard object goes out of scope.
///
/// This is useful for ensuring that an OpenCL operation completes before
/// leaving the current scope and cleaning up any resources.
///
/// For example:
/// \code
/// // enqueue a compute kernel for execution
/// event e = queue.enqueue_nd_range_kernel(...);
///
/// // call e.wait() upon exiting the current scope
/// wait_guard<event> guard(e);
/// \endcode
///
/// \ref wait_list, wait_for_all()
template<class Waitable>
class wait_guard : boost::noncopyable
{
public:
    /// Creates a new wait_guard object for \p waitable.
    wait_guard(const Waitable &waitable)
        : m_waitable(waitable)
    {
    }

    /// Destroys the wait_guard object. The default implementation will call
    /// \c wait() on the stored waitable object.
    ~wait_guard()
    {
        m_waitable.wait();
    }

private:
    Waitable m_waitable;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ASYNC_WAIT_GUARD_HPP

/* wait_guard.hpp
bFOPabafYlf7Ejq/oHawutZj0fa3EQ/t31XeXby8EE+6QV88PN+KZ7Sdbv4nqJfh9wU36lOzj1BeGvyxHh/RD9C/u++pT8x6kG6yA091/cgQ19qPux5fneozbon9Pdvkj97ytL66mlHGD67Z2tfnZ+Ia/j+fPlQzlf29Su/JpBOLe5vPgaMP08/1Fj9Zzj7Knb9xH31mvLx8Nh2EPa4dpg71mec+HK+7gU5Bv6o7wbg8AQ8dLM72cN9y+OgMuLMTni7+5L+sTsTeCt9X7/oE/3+I/ZXor42w/nkUXjDZ/gRb4Cx16rYj+e1ZvvdspHmn16wXl8bAfbPgHHhtyiV0PTy4wLyXfKLeO4JfPuu8mDsj9IWz01bvBQc0bdH/dz2d62x8o5F99Rd/nc/7z+sG71EPf3yvH0EeKrjHPh2/wqniY9l9+pi+lf+HdaCnqXvQG7PpHaVb5aPb/V2M93bub9IL4Tmz9KwH/b5ZHO0ED14hjwynH4TrsHbrd6CvNt4HX4Xjvc66uLQo5zmLczPZOf656FHjD09VNrLDU+mJN4lrn3eQv9lNW6z9I+jKOfSIofD1I/hLaHcp1o/MoZviDavC/XuHW69jfNbSP/Jmm9ds41Mnr+2CIyI9ZwO+nICnGs8pi+DRSHXEofiq+8bth/vewddf8B7p8Jx9z+qT9d/AdWuXhH0n1s+t0D8zRn/f1fLfQHrEJnYc6lKeM6nS814uDi2Dgwa1o9PLX2nsap68MsR+1zv0sanvTO+h3pdp3OhXFYfjDb/S9az7aIuWPwvgv2niH3ybPo7/05fLHqIfiSNbD8EDxPnqi+lJ8k1TqvV/zs1twoNLu8EVo+k33fQZOHd4yRH4Yol5X64vyP7KcfBK7Wh8Vh1483+Ml/EslK/7hzpMtPHtA/c/Kd+9Sv8ZZr38EP0pdIKCnuJdIb21s9+rn7S9y57t91p8U6x+Fzj+RHbyjXpSBl71oXlNVmc2n1P/xtO8z9ZG9Zgj/byr+BIFf51LN5vErnLFDXki6w77o16lvhaee4MvtPbmJ0vhq2997y959jY6kX6vnFHw7wN0ePNZgF/XNvCnZ/Rp9eV3feW7mfqRnHtV/LK4I17kPa0uG82PN6p/hnXpReqRdXR0eXGlc+gy2eWsG9n1i+pEk9RJ4YEVWeqVGerlL8XSc8WZ8fjcB/YJ+V48C89LPkEcPwO/OVLf2Sjjadwj32KHOew11N9+Vv8bD9eM9fPvIr0nO+IfySfbV2KuOD7Be7wda522+XoqQhyiR+FP1fBaprhTFa7/blL/fMb6+LPUMdjblBL9y9/QJcaKc/S8VfhRuf1ZC0rhuGr+2x5efk18Cs9ruc39flTX3kLnUK+cah1t/yK4kr/PTjY/081fijy+w/x0h4/fpmOnwFvH8PPl9Al1jCb70eTH47F/G/8e+gH0mRWwt9Qy/PJqemPY57NXPluD9y/wffsR1z6k/2ygOsBTdOEyfaX7vM8N/H4tvlulPr8ff6K3JZ4kHjfB2SP15R7DzuzTVrGAXz4uLupjTrwKL33JfeynVLlYP9hBEeqR1hmkw79D5IXdnqcXnX8FvpEJrzs/pOZ+dbPP2WOq+lW8PtsR8tgUOM19cxbJB6vxtrv1h5xIx45nd3HR6rH8dTle9gUc9TH76RYNrztHaT3/yhGnFutb68l+vGfdPuv6N9FL18n/1XD/XOtn/9aXdr165Cb6aQL7GBjtHBN1P7pRVoL56mq/NXl4yZn8rh1/uSXEB/o+T6J3ro7WP+z3zuvKnGd8P47DF+GrveJNLH3hanbe3vPE8+uvxdV7xJkXfR9vrJpMz9b/tnIRHjGBfe+I0Ecnfsa2Y98=
*/