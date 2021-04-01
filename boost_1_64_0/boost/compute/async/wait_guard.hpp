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
3jnE314qQv8Uv3fpKDVql9kq8xdXvuu/G/VobUeRnvsMH5dNnnuj85ls2Mr/2qVWJM9TuMwCTVeBQcBz75CmWHf4oPSgx/TVXfuBGV8MFf5xnOv4JUskrAMtj01EulOOB7x+yuwTX+pys8Jc/3fSomMUvJfRYN80ud9tk7QsGjxbiXhNI8HHExeqHlcnk/kLHw0yKXofFRRQOv/c2DjqhXS5RnGj4h9daEaTcfrL/xjhZxAEi+7w2cLJelczDDMw8z/ju+euFzgPGSnLNyQFmWCbxnLSmzXBFddo2Rgi2yZN3pHbhTHK/Bi6FLISC7JG74zK26wxynXBNgnmDZJE8BT/lVsh11Vaw4BZSva/2ba3VEqKXvc1dvCUUe9uqsb7+a73Qoirj59xnC2ISyP5m5jlYlC0N37djoIUiT1UWX1Kr0BHiidx5Lz4ORvCZ80R83t/Fvozzit8HEBJ+ghDynaQzV19xMOyY41EjykjOYgarnniBcgr/91Hu+ZmljBRCJDAAUbw9k4Ib0Uh1KkpJ4PjVoYZffcGpPwMVJa5wBMAPqXBmh6cRAkA2A==
*/