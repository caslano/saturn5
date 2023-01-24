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
FgNWVBZY16zdACCvxf6+FPtIajlBk1MCTFLUHTj74GQFs0/P+QrQGbUxzG+r2FBaTYrNgezdMAnRzEUECM9ZMD3R3LR8ThcuOIrWS441hl36RbFW/X0mq/6hRP3dyfrx/a36RSlW/R1DPPFqDKIVV7PVcRVZBWbwxEpPihHJlWb2jNmeld3BsnA4avwuMrnHZvtDN9mlregxiSkG74EFHPq5NSlmtDjg+YCBNf4lybkNSxO9oiKW7i7zjJoaMpR5snlgX6cav7lbfOpUtkOK3sbTWZpoDIbv9qdglGTvREUce0bR6cqHCxuV7D1Ss1zbh1mAh9ByogXjsNUN1Olw95pSXqAxW40YzePSbjJiIM+1N2HMN9qzulh0H05xNyrtQmB8slvWL+1LWcb1mHQiItdgZAz7SyizzmWid5IsukMpYu52p839ZLJucTZGyR6td2XK/0bIpHYgC9Q7Odkd1C9NEqUEOoGit2Dd3gmAVVwo0SqNb8eY1MMGsaUQxaQOx9HV4mVSYnYere8Yy3goVK+ipVZJO+gnW+GvrMve4y5p05GDo7ukVUcHMV54F08bkE0/s7NGWXK3KPWTJh3PHN+Z2ZwQqExitPrzQGy/Hwu4zirAyK52qZ7OI+AynR/sEN/FkobciuNLr/ZUtCPOpc31sXpdyIQVDe2LrzGYIyN8IQvetwmD9slDblT3NaL88EWPaGIxN8m5hQXZ
*/