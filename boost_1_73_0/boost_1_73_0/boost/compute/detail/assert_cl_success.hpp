//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP
#define BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

#include <boost/assert.hpp>

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    function
#else
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    BOOST_ASSERT(function == CL_SUCCESS)
#endif

#endif // BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

/* assert_cl_success.hpp
S4w0yBbfU+W95qvCQqd3AG/Pzk7hDRwfHR8FcEkkZwISy+SC6VUA57SOfCnIZhMa9jkAZoGIcI8wLbgBo5b2jmgGuBY8Z9IwCsQAZSbXfIE/uARbMFhywaA3Gs/i4bcA7gqeFy3PvarAFKoSFApyy0CznPHbhqYk2oJaIgPyU24sclaWKxlieQaW6bVpaZwIIowCcku4IAssRywU1pbmQ7ebV1rgTrpU5aabb60IC7v+a1czVLMm96BKC1ZBZVgALj+AtaJ86Wa0CINltRDcFMFOFhaUtKs0GCZES4dQzkyzBQZJ61bgMqFE9dy6yShpXLW7Qq33EtHWlmhZaYnl0BbMowqND6CSlOk6vzZiW6V1ubb8mZbttFNQElWBHyUQJz4siOEmgB9xejWapvAjmkyiYTqD0VeIhrOW73s8vMSzwbGqBrYpNTOoQgNfl4Izulf8P9709ApcPzP35IIRWZXwDvwTiKoVHum3pz74gi9czm4F15hHhO+FyRUMo+u+94TjDSw1wy5CbzoZTPE0SipYnZ/MhqNxEideeAGvucxFRRmcO4LmZBWfPe9WcfpEV6ehOmy4Dj564ZLXjJf9pDeJx2k8GnpfsarBwyvq9qGJqtK5ixijck5cc+7Q4/rtCq+G3BP4quab9NPp
*/