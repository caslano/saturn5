//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GETENV_HPP
#define BOOST_COMPUTE_DETAIL_GETENV_HPP

#include <cstdlib>

namespace boost {
namespace compute {
namespace detail {

inline const char* getenv(const char *env_var)
{
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4996)
#endif
    return std::getenv(env_var);
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_GETENV_HPP

/* getenv.hpp
mchXf4989dUZrLLwIrXKZyNfbo34bt4i7fFf2eMJ9LhUe7yGqspLZlXNm6S9eJJetA3kL67XXtzHKroCeqgMugi6uG95v6AdnvoGMUYQlt8Kd9TX0JlZQvVuVD+p03K3CcuR8VmXQtFqDDEGPZzCcaG09ViMNA3WoVgMT86zXsQ7dOrwfcvunAt8ZfHs6hHft/zqPl9ZArsqZqRHzzXft/zK6itLYle3MCrCVZavhV9d4UsV2NUQRhi4ugTQb8GLvgil0wDIAWfu2OFLJXADzkdRJV4PN9JWLDH/EsA8qdzlHa+Hi75CfkvoAcumcVmEZVP5TF9CKlVcPpD0Upg6Ak4RdOpURobQLl9GKqu4v+8qfhXvu45dufrQR3U+XRbd0x1AZs1tEqwt0laE6xoO15W+JIVdDfVl8mdJvgT+zJDtr2N1gdDlNj9KeYvu6XIcM+zl1GmxHu3RBwNJArHQ2xbpqI020sg90+801KNMu0r03hWTrYTihI2ZsAwAYbRTbmK5yb7H6yJgfwxTHweC32kMxbt3xfCStpoOZ4rFO+GMu/PyBQIezDY4PNdl+4MzcGxtqsAmPywGNGze29ts3tI2+MB1C9bpASW92u/qY/M+8VzobiBKgnMQ/PZz9offwc6L4DfNabJ8jBp/6BbLx8n4tw9GmXONxO8L6HtnKn15CX2ZSF/2wS9dIAAfjgEIY7P3AM0sJzqsUpsV
*/