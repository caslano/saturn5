//---------------------------------------------------------------------------//
// Copyright (c) 2017 Kristian Popov <kristian.popov@outlook.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//
#ifndef BOOST_COMPUTE_EXCEPTION_PROGRAM_BUILD_FAILURE_HPP
#define BOOST_COMPUTE_EXCEPTION_PROGRAM_BUILD_FAILURE_HPP

#include <string>

#include <boost/compute/exception/opencl_error.hpp>

namespace boost {
namespace compute {

/// \class program_build_failure
/// \brief A failure when building OpenCL program
///
/// Instances of this class are thrown when OpenCL program build fails.
/// Extends opencl_error by saving a program build log so it can be used
/// for testing, debugging, or logging purposes.
///
/// \see opencl_error
class program_build_failure : public opencl_error
{
public:
    /// Creates a new program_build_failure exception object for \p error
    /// and \p build_log.
    explicit program_build_failure(cl_int error, const std::string& build_log)
        throw()
        : opencl_error(error),
          m_build_log(build_log)
    {
    }

    /// Destroys the program_build_failure object.
    ~program_build_failure() throw()
    {
    }

    /// Retrieve the log of a failed program build.
    std::string build_log() const throw()
    {
        return m_build_log;
    }

private:
    std::string m_build_log;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_PROGRAM_BUILD_FAILURE_HPP

/* program_build_failure.hpp
SZ4pmSN8Di+OvixHFEiQTA+QyOFoMvPG4+H4fvrw4I31Mw6sGIjnNAVahDKgwEdcvERQ9RlIwEsPxKogS2cyCGuGJPdlFWAhhK2TLpdwxXUKc4Qyh9EheZ4WOSu5CBDONkr0eAxMxD8Lldc+47U6zRXlGX9n1kT7MCd5cawD8pnwMWnqtMwQzAGvIHFKcybFGhjbcqpPsPg0KdVapnGcvmD8L06rO9Ib6M2GH8Xh6RFtYoytT7AVSFkLqUGyUAVjc/X4dOBPR6PheOJ1ZqPxcDJsD3vi8AwCCDXxCJt0Eyil1beRUTB6k1Pl6SKNtVkZe+0TYQq/hVs7qths0izXOGz+IdacX2CZAEZcb4A/7/NoLa0P5NaPwyhM3uUaXKPcMeYMMF6pjWSjljoYa8KuvE017axOq4BU4m1zlmnWsMSD2+3BCN1BdyIOz2GATzJ7FTLIEFZREuVREEe/B6wdb8YSLoPg0UjJ6/4q8ShsRAomOmaSwICIA61MBB6ThgHcU6VFtqgC8wXQCAOlawk7klcAtIO1THLIWFDSI0PAfZyQnAD2Ia0EWa25o+PerO/2HobjvouVXNS28oWXn9OMSCVQFjbgKA0bEgbDyex+2u1NYAxxeEnOBG3/VUhF4L+UAQKf0pq1LpZjts1O
*/