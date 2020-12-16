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
u9mW/xb7vWMpKXK39TnwBu4zyP0IQ4pcbb2O/7O1s6eRH+lzrD6VF5GfQX4/JTX06wu4bugnm9/0hy1vPfUn/d1p1u4s3lMwpLRvscX3kb+hPfcwpNTrm9xvaPfbLD6B3Elvr3Kd9MLlfCf97t2XklKvy0gN9vWB5aTI6TN8N9j7/GJS8jHkQ3rabctIkdN2eIbvVm/eeT3fDXJ4O6mhH1graPXfu+CTHvdNUgPvIZRvkM951p9cbUjRr5XOnrlu4BVWkqLnB1aQkt+pyMkgx39bu/yGIcVODjOk2Os7yJf0sJcaUuzZ6t3HHmpI0auj+E66fJ8hRa4rlpJih4uoL+k/L19MijyupDxDfW05R87y3SCXLywhRd4f4rvhvv18N8jtUso13PegRaToufVrx2+mPEO+J1i5voTUIK/vgJPe/APrV660/u1Htt+PoV8M7b3bMlLkfgj5Gsp5JfUj7X64IcUvLue6wZ7ua0jpz28vJ6W+Z1g5fpLyDPV54hJS9Pt51l6WUi/SHzzU2svp1t99jNQg3z8ZUvJdYfV2Pfka9Gc59xns7gqrp2upp0EOnVw33H+01efrbX+YFaTI/c+LSWnnqC3ntUtJkdcqrpNeObyIlPyuMaR8P8HK5+FLSLnvOr4b5LITnkF+V5Ea2vcTyjXo213BDfL502JS5L2U7wb7fIQhpb0vtPL4I9cN7fgJqcF+3mhI0Yct1If0DjtOLTmafEmvZRxs+cubaKdBvsdauR26hJTrnzOk9M9DabdBL65YTMp9tpzTjuA+Q7/bfu1+DbhBHztXkiKnHxpS9Ps1y0hp/y7kRbr6CO43lLPR+rm/ch/pez4JTvom+/2479+FFPlsohxD/55t/c918Az29VZDipyfTn1Jr3gzqUFe319Kiv3acfzC18E31OtIa+dbydcgv7fRLkN+Ra4b6jVqSKlHkfIM8nu79Ss3HUKKvb6Q8g35Po/vBr34pSGlni9eZv3VclLk0Ud5Bj14DDxDe55v7d3a47Xrl5HSn6zntvThhza/Z3I/6WEft+M767kt/bLjRvfJ1Mtw36QhRX9u5Drpl39l/dty609t/1xs7bN7kPwM7TrA/aSrbgc31Lub9hvwYw0pdrSF6wb9Og6+IZ8LydfA+zypoR2LaRfp2qusvvKvdf/IElLq/7NlpPSDHbfueKGNm9bbcn9i9fsPVu9Grb88k+8G+T9rOSn1ONqQ4sdfRXmkn/wQ5RvksM36BfaqtuT8LSu3Z9j+22393pMNKeX/xo6H19vy/kg+pI87fSUp9XkN9SFd8kxrR2utX7Dt/9iN1NvA/zj3Gfr3MNueFxhS5GvH1+6t1Jv0xO+QGvTtMjv+Xm79xIQdV/ps3HLFMlLkafVz4Fhb/1ts/PcKa+/fMaTU4xrbz9YPHngO5Rq+376MlPIeZfVj3OrX00kNfu946mGQx8PseHo81w1/f9fyV9tx4zQbP/TYcbWL/A16UOC6oZx7LSbFXst2vBhdTopdWrldtmolKfU9n3wNcn8z5RrkPmrb+UG+G/iftPGgtbsDNp8T30s5hvr9gusGuX7JxuVFaz+H2XzfQD1IH/SiRaTkfyLXSV/3V9uO+9v6LKY+pC8fWUaKfG+2fucF3Gew+5fbuPVyO36wVt5qd9FeX2v93yrrt19r5W/t/QMr7XhznLXDGUOK3N9i46y735WUclm3b/mnb1k/MUA5pEsexnXSZxxn/cWRlEP6iyfZ8f7J8AzyPpn6k962w9rxY62dfpH7De35GuUZ+mN4GSlyuMOOv8Q3rfSCxaTo2/1svFa37TnVxo1bjI07rf4voRxDvX5OvgZ5nEd+hnrNWr9j+ccfZ+M=
*/