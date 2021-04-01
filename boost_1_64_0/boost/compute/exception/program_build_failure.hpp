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
GBUdH1dsBTBRsVslgq69qLEkKc6KGgUpO2r7kFDNSU5qlcjWnaWM5sOzt04JcIsJMZE3VKP5cNojRk7RSDPVqkg4Z3xX4SZItsLa/UnL3wEFIRBm0sN4C1MI8158fBhGzaOA596IzDKj3/TVcC6mG4PSmx9Z5K0T/PfYUgwqv7pSMIgJUc0VDcfKoTZ8bUlZOYwP7bH55yS7gJjlTE9x53Egak3MyLisu0LCBshaxr6vS3sNE8YBgDXG6C04v8l9WoyYbZ9I8m78OPpHWVOgl6KUBm2vfYMAJAopkV1RVYS8jB9bWPdIKTg16sgaDPzmS0tRhvix+qsNy6QfGRfeVY2cgEXUWiYa3JIK/IeVz6qQy/HfUp/Ev1U2rSv98GRW8vIAPhKaECZ92M0Auc8xP18zYXnGW0xj5WX8YsVVWZR99B4/nDOCRvstUh4wueJalG04CyFLCngYv3JF4ZXJ4rkLbwCcbbYsQ/3PWS8000/eBe5IKiQl2kRqNPgbMNYm7JYpTYC6KjlBgTZM9Mw9WMHHOqHDJhItWbdDZgF234VwwKWOSTPKevDKlg==
*/