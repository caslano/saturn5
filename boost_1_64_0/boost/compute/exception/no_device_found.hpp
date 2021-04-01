//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP
#define BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP

#include <exception>

namespace boost {
namespace compute {

/// \class no_device_found
/// \brief Exception thrown when no OpenCL device is found
///
/// This exception is thrown when no valid OpenCL device can be found.
///
/// \see opencl_error
class no_device_found : public std::exception
{
public:
    /// Creates a new no_device_found exception object.
    no_device_found() throw()
    {
    }

    /// Destroys the no_device_found exception object.
    ~no_device_found() throw()
    {
    }

    /// Returns a string containing a human-readable error message.
    const char* what() const throw()
    {
        return "No OpenCL device found";
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP

/* no_device_found.hpp
QUDozShQmAwu69U/2NfpR5kAK4qVwZhDxvqIgmh0WBrIfU5NNSOPTkYik3Ai+7a7i94z7sV3w+aS9zqmpILwkt74F5BCcwoNWjhUxHdKkvX/c5fZ8t8w5Hb7AqGUn0w0Xwn86Q2MVwwuiFwSVOoytvSWeHB0WTQEBSf9cOWmQzQZRHiOTl0ZlHzXp84jYg4Y+gkRAmENHaEM1PcpD49zmuNk7Haj1Qw19wfxNNHGMesmk4zUFJqgtf2djBunRQRzsx4Btuw4Xjyy01g8lQNiVkkvRJT6141OQIEYexRqeGtaks+3ZzohNwTpeaebfK0f3IL4VayL7+rUkzIhNTDlPmqbgQ4voTo8G+tYFULSpLR7kIZKYjE6+apo9pMjD5NsCELL1UOJdYMM4pPcxzU5CO50DJjC4XIaXMtsi1/u2JX+uUAvMD1ktUF9I2ODpSkoxMb9Pt4ZFUYHa96ZjYPKopFQ44IUDnHOQp4Wp6f4REosYbNT79sVK+/2v4qzsRwYcG1yjAwDk8qq7xZFOAeHc+z9bxjN8OWmhxBl4dMViDE5RSXwvU62LHpU/w==
*/