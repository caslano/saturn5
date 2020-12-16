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
0bVgb9+Zd+859973JvqHfzKfT3J33u/3bjn3nHPPve++O8fSh8z/Zz/E9Sfgz1lfqlHPmd/ie5YREwwRI6xjnP4t9WAs7R+jnr/iPvp94TruKTIGszbYMY2vvxYZz5J2MAZ+Cb+9DluhzNqTD8fPHUHfY7ObqNsK2kU693Xum8Dfn4yePJU2cF/xGtp3N3QNeXRcjqywgZlfEuti1wvvoX7EyzO0PbmJMQC9mLmU/G84jD4grzvwM1+kncQYRd47eRnjRcIcqNZPn34WeTIu9H9lKTaCj3whunIJ/u+++Lf3EH9cQezzWWwTmc6+nn7FH80zV6n9mGefyG+BZ+P8/iQ+Gln8hFhsA30wwXVkZ16C7lNPw1jc+B72yBg1eyVtfQ0yIyaaZz46Q/zWgW9P0IPe31D3G7AB7Kz2etrJPb3Uo/9BjFfoZePX6PBK+o2101l8T8dy+uEH5IPcGqy/1b9Lm75IP+wA28LYQNv7Owvo8SpsEL82zNyoA5++hvxeiA/imdXCaw4hXmGMeiY2vJ+6PHQlOrqCuRFzucX4XPq/yHg8dyP9j+zML5DrI9FRfNrcEymLdcjG3fEZ/N1/EXY+i119h7WtOXQOec1cg42yZlw8FLtCjxr4nS7qP/uCFfjTI/CVlI+fmGdsKpyF/F7A3OR54Nhf1/dXcI06b2SMIK+5++BjsJ3ZW7GrF+H7iY0XCvjoHuwGe59DJjPj9PNnGYu6mO+gN7OshxevpV+PZ66B30hupH3H45+J3Wdehn59lPufRT89nrqBNa7HP80yp7t8Bbq1jLkPtv1IdJ36dbyB8egE6vw6/C4xdh2dqr2YPFZTLmNN8gD8xs3YxzeX4PvwV/Ps37oUP34889i3Mjd8M2PJ4fTxE6j3PxgnRvAvT15EPEAd6OcZZDz7Rup+G/OrI5DboxgzvkF/ITfzG/rvdwXWpVYxN4L3jAK+Ed1eTwyxn/5F54s9lEVcaG4pMEZjS6cx53onY/4FyJwYtKvGfPeDyPHljKHE9bN/Iv55OLaDzXZcRbyBrzBnk8e76IsOxqYHHU5shx/jnuEXE5O9DpsgRjHPwB5pa4F5SwFu8dnwDicP8iy8BL9xLu2h302DMamPPl3MuPDxlazDUBf6aebe9O16bOEy9Aa/NHM9uoKvqCXY69HIgbE7qdF+rs1fQb8yVzU/xvc9DN1Ctzl3C1tCR957JOuL2Br8+lXkdeoxrBuR4scK59Ent1CPrcxvR6jHmfimx3GNtswdwGYZ9xtfOYI5E3zW+gs3MnYSB9Qvokz6qnED91G/OrHp/JGUR76NMcaeS/HvF61EX+hTrhWm0Gu4Haxp1Lmvn7T4bOq0D3mQX+HD+Jcv0T/X0v//pP/hGNaJuo49kjOgkS3t67gb4wrxYW2YcYB+rD8UH/ID+hrdnXsW159PvV6Er2Qsn9vD2HM1fvss5LUNvX8qOoIfKnwJO6/Bexd9VKUf8TH1m5mnsAZceCht/hTXT2IML2NrVfzVMmKsMrK8Efu9F3k8kXGWdeg6eRS/wX2/IeW+hP7sfQq6jj+bW00MlNDe0+mvY5At3xN8Zv876AfyMfTjAvHNPLHnPPFIfz+224MvO505L32UvBqb+Ah6RR7zI0cR9zJvv5y+Wn8IfXsUexvx4b309VmHMU+i7HH884n0O+XPoy+N9y9D74lFsT3Tz1h63KHIkb6nbb0fZuxHxjP8PUdMXuvA9vm7cSFyIp3/IbbyGXSuCx9wOLwbkfldmEeehoyvPgq/iT2xXt8gNk1eRt+/hTGKeUId/zqHXidfX0UcQR2egS110KaLicUS+uH7BeaehxFjoWPY79yfGSPpj/5j8IffoX0=
*/