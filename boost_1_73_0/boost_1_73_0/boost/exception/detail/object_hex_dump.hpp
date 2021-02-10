//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593
#define BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593

#include <boost/exception/detail/type_info.hpp>
#include <iomanip>
#include <ios>
#include <string>
#include <sstream>
#include <cstdlib>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        inline
        std::string
        object_hex_dump( T const & x, std::size_t max_size=16 )
            {
            std::ostringstream s;
            s << "type: " << type_name<T>() << ", size: " << sizeof(T) << ", dump: ";
            std::size_t n=sizeof(T)>max_size?max_size:sizeof(T);
            s.fill('0');
            s.width(2);
            unsigned char const * b=reinterpret_cast<unsigned char const *>(&x);
            s << std::setw(2) << std::hex << (unsigned int)*b;
            for( unsigned char const * e=b+n; ++b!=e; )
                s << " " << std::setw(2) << std::hex << (unsigned int)*b;
            return s.str();
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* object_hex_dump.hpp
OJ0OZJak4VV6O7wNo3mHh/N6jR3KuGqKgmUM5Q8lJTUKnWS0FZYbD4cQjOMQJ9nHaD9f4KK8kbRnRWynW/diJ/Q6SabBDGftyyiL+e2N6/wLUEsDBAoAAAAIAC1nSlJ0fRKhpwQAAOoJAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWVVTRVJQV0QuM1VUBQABtkgkYK1VbU/jRhD+7l8xSnVSQMaBoxIcpaeaYEpKsK3YOS66nKyNvcZbHK/lXROi0v/eGdsBckWCDxcUnMzuPPP2zBNr3oPdn/YyLIKDN19R847whc+Nk1/Jv3msX3eIokdo/9Bxjs93hBrAs9djtAPv8nqEfuMVdbFO6XMUvSPcnJKkfwNynkf0ES2tZ+c/lOW6EreZhv5wBw4+fTqGPfi4f3BkwjkrBM8h0LxY8OrWhNOksfyRsYcHS/HPJnANLLe2AMNMKFAy1StWccDPuYh5oXgCTEHCVVyJBX4RBeiMQypyDkPPn43cP01YZSLOOpy1rEFlss4TyNg9h4rHXNy3MCWrNMgUERA/EUojZq2FLCwMz0Hzaqk6GEqC5UoCu2ciZwsMxzRkWpfqZDCI6yrHSgaJjNUg3rTCyvTyh6pmmM2S
*/