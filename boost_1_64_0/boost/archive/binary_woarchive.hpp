#ifndef BOOST_ARCHIVE_BINARY_WOARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <ostream>
#include <boost/archive/binary_oarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class binary_woarchive :
    public binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >
{
public:
    binary_woarchive(std::wostream & os, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >(os, flags)
    {}
    binary_woarchive(std::wstreambuf & bsb, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >(bsb, flags)
    {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_woarchive)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_BINARY_WOARCHIVE_HPP

/* binary_woarchive.hpp
jzTUb/+OxVzxrDFpQTV8H3pYdWfk88y7dyLDcRF3fvoV+8SFOGz15C8oKEbc9CWkqq67FzOdcbFIOjs+z8z3WoCSQO/rjyhzTCP6qR/FfJaKCVN4Fd8dIXwk8u9fiQjV+9d6Y/4HGfOZOi3U+9c6Y/5bGfAv7r2w9ynT8m2O1MEKjcWo6ZWPQYf9eW+QtpsnGu0g4gLPCqp80cFR6F9aSsjJau929ZeCL1m/mOjZhCjCLOMHj87ygou00Zdxp6TFwWMhEKDL56f3XAQcdOl/clExf1Pyt4FGSO/leAvGWQkEQ7TP9RJbN55d0opqy5BnRbVlJBMpy9hz66eLBeWdepywR3mpdv3fSWai+J+1xnvprMVqfZ74ItT7pwlf14AfGgr++BoDftAiBd8uFPwKE/5Ho37nF+fbL6WfGh6VohAMi7a/j3Rd9fYrRcF+o/74ct4xYtM2S10HHUX0+cwSQ4H/tN53nrEQ1pcFMp6lKA4i3/gRwrEJV+CHDicRcrIvRzf9JCOp/4qwMg0hRJZaiFZFUa7tFwcVVfhvtfHee2Chmp9VO0PhPxP+TgN+Zij4dBP+nXwFPyIUfIIJ7zXWNxnwofUxJOjG56u4aHaKg1Z7g9PhVnYaO30X01Md8IV+099FKUO0iXWyRPRfRZHaAfBAgbqh3bmpYSR5bcaXclsUkWDvrHirIr7PmSPvJltEHrR3t6zNSMGMylpmyM9ZGPt4ppGrjNsDsmKWMh7DPTBiBt8DA3EPCD6SXReNQVPsatGrrBMNu4t7wD/KfnoLnLAS1RZjkkm+tZnB9SbovFwT8TP4mpgbRPq/0LgJn3Km5SmFyoBmc+7IJe5cN7wD6eh0v/Wk1LqUJjwRw2SKiAJzUix7Qszv0fbP7pqGNwxH1rXKT9PFl+On1r+EUPB7uC9IgAyT84ikE3xkZm6SkfX6ytSNTf1K3BUwL7BCRMmQdwMQ5cjviReNEeBFAGQhM4//59ulX+j6BmUvDVYa2qIS1Q80+050SAPCQgxsNlgJJKRXY532m4lZpVFnngkYEvgWGXhAgmUUkf0vlLZZiVtMZOkk4KEwfbVs2T25IiHZupB/Xv+0vGAvx0/QDUX0SK7eyWqjsH53Y3nwr+wk6m23CITYC4fqSIMlJhPSzGx+gNKDXGSgwRK95xxpoBBZEg1YSXv2A69JEGE8p6WyoOYKpGfkdNQHPCqKAOmBAHdy5JNyHXdQv4fgN/6ngABrIVfoNDIeagEg4M1+DJd+uBYZ0xBe9AMR+IgvOQ+Du/lzUgMRdYI9lI69UB0dFAE5eVkXj+g1xMc6/yBFjBx4sgz7l0bX/ulPqsXL6SfLzLdi2k9r9C2LTdXhWIMmuGFZZqducZO/RIFSxv5u7aTE2cPrxUD94DRZglk8s01e/zCa35NN+3/W3x/tQlW+SvrD84z5zfJ5O3WdCOAMbVdWL8Jb/GwJs5KWBcMVvxffnULqtdxM/mAKJq9mfzAV6cx6Oz3g8m00nMGIq85zuXzqL6G8rJpCDvWdJuQQcUzuT0zXtMpfAIbk1TAEcib6nKi8bswjI61CNQO/r09axf8stci/p9rIfy357fJs5L9LLPLvLTbyX0v+k8/ayL8t+Q1t2p9hyZ9jI1/2WfLvf9lG/m3JT7bpXwdL/iuP24zfkt/Opv3jBRb590s247fk5222Gb8lv6FN+zMs+XPm2Yzfkj9w8/nswXoLFJuCfU7nbSxj2d5AEWOgr1SN9n9nZxYcHS2pyUm+o+L/whIb7Y4NVCSDEPFtC8hAtz1qtuT7tJ+nyQmRQ1+QYMtKx+OVqxlmKMqBlH7DMyZmaElyjXyRKfUR01ZDovTg28pxmlyOwRg=
*/