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
IM+s7VjfINfYMMgpnKK2O9Wn/O20fAPEJUgXPpXGtedhP4f5USu1aus+04DmV7bup29XvO5rIl/Slj+37l9PU2/dz0/9Y/tb006K1/0EbcXrvXjdj16teH9bNAzj/v/4uu8APeLXfYcq2kcGKyvfN+oqsY+MkM/8T9pH7mraR9k7Pq7+ZKyCf8EQ63xnihmfId6FqVR/zP8j+qMn0h/tXVXTH0ODyvVHsk2x/pggn+ZXf05/Sveqpz/MR55/tDqrpz/K7I5El/+G/jz0E+qP29aq6U95QeX6k7BPsf4wd+En2/vn9Cdhl3r683bbH7NblemP6Y9C/Sn8UagvquzWUuf/hv6ki/THOq1q+mOuo1mp/oSmKtYfCfKZ7fxz+uObrJ7+mO77uPpT1kioH1X1e0j+I/oTJtIfw31V0x/dIyr8w7sV608r5NPY9ef0x2Sbevqjtf/jrl+aGYr9ZoePgZ5R+frl4fTf0B+JSH+ioT/+mDdckkX243HYj0AG+BB+Dz3IwRVoBIyfj/VsAUUzpOf9JaW+NF3ZUIr6QAd7isqe24Rsp34hgxT4uYDpO+Bf21mn0vzKMGsFzWe4Ev6nePi/gEarKGqvpugAjAXmAnXXUAxNENKV4XWkS1wLv6QjbX8h7oea0/j1DXUEyCRTlAALQS8FvgUmbKZYtEWIb79E/k1o1xahH5DHMhFdVZyXp2Q9/HfASPCZ2Kfy
*/