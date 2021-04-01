//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#if !defined(BOOST_WINDOWS)
#include <cstdlib>
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::getenv;
    using std::system;
#else
    ///
    /// \brief UTF-8 aware getenv. Returns 0 if the variable is not set.
    ///
    /// This function is not thread safe or reenterable as defined by the standard library
    ///
    BOOST_NOWIDE_DECL char* getenv(const char* key);

    ///
    /// Same as std::system but cmd is UTF-8.
    ///
    BOOST_NOWIDE_DECL int system(const char* cmd);

#endif
    ///
    /// \brief Set environment variable \a key to \a value
    ///
    /// if overwrite is not 0, that the old value is always overwritten, otherwise,
    /// if the variable exists it remains unchanged
    ///
    /// \a key and \a value are UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int setenv(const char* key, const char* value, int overwrite);

    ///
    /// \brief Remove environment variable \a key
    ///
    /// \a key is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int unsetenv(const char* key);

    ///
    /// \brief Adds or changes an environment variable, \a string must be in format KEY=VALUE
    ///
    /// \a string MAY become part of the environment, hence changes to the value MAY change
    /// the environment. For portability it is hence recommended NOT to change it.
    /// \a string is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int putenv(char* string);

} // namespace nowide
} // namespace boost

#endif

/* cstdlib.hpp
ckpybxP9WGATui9k3ZCzyO66Jq3eYnRiIBWOy9kZgxXpV+hHIw5DVSsVcTT0x83sO/dR+bQNi/sfjI2zZpfrcAP+yszw38fvRqrla+osX1Gugq7mfzZ6V4AfKrStic3ZEaJr0Wxj6N+tdvG2p/pxOWpMAnAtXEqkWsU9nITh4KqdtPDRQw/PNC8R31yDBIDG+fROIikb9dwUreDUGOrp7zFCtBqQn4o3COTIgMCf4qSZXqx0gjkoCgN18DxnWmSyB+Ix7joup45lMbKesQF3Uv7xU0YN7M5AvtzM5JeQvz7yQYTwEbA68rV1vajq3pk4JvlkaRc+6zuXCOXWUcBMDTW8g10ljsX7NPBZrEklYFkdmQsrL5uZCi1751mRSdTDBRhbQ6KuLsBOQWnmcn4CAuem770gqeVu2rZDeKe2OoeVUwUFcUvFxwfNXrTcRWtxBckQAoGcPaaVSxC7HEovSS1FNf6bMCKRUYmLbJw/jKQeXoc9c3VTZqGFEB2t/OUX0fDDtLTQSJwLAE1TRj5RyGJbjTTMIjTU2tfiaF6GfVV6epvPvUMmw+uBkg==
*/