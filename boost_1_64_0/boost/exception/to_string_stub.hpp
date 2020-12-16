//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593
#define BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593

#include <boost/exception/to_string.hpp>
#include <boost/exception/detail/object_hex_dump.hpp>
#include <boost/assert.hpp>

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
        template <bool ToStringAvailable>
        struct
        to_string_dispatcher
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub )
                {
                return to_string(x);
                }
            };

        template <>
        struct
        to_string_dispatcher<false>
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub s )
                {
                return s(x);
                }

            template <class T>
            static
            std::string
            convert( T const & x, std::string s )
                {
                return s;
                }

            template <class T>
            static
            std::string
            convert( T const & x, char const * s )
                {
                BOOST_ASSERT(s!=0);
                return s;
                }
            };

        namespace
        to_string_dispatch
            {
            template <class T,class Stub>
            inline
            std::string
            dispatch( T const & x, Stub s )
                {
                return to_string_dispatcher<has_to_string<T>::value>::convert(x,s);
                }
            }

        template <class T>
        inline
        std::string
        string_stub_dump( T const & x )
            {
            return "[ " + exception_detail::object_hex_dump(x) + " ]";
            }
        }

    template <class T>
    inline
    std::string
    to_string_stub( T const & x )
        {
        return exception_detail::to_string_dispatch::dispatch(x,&exception_detail::string_stub_dump<T>);
        }

    template <class T,class Stub>
    inline
    std::string
    to_string_stub( T const & x, Stub s )
        {
        return exception_detail::to_string_dispatch::dispatch(x,s);
        }

    template <class T,class U,class Stub>
    inline
    std::string
    to_string_stub( std::pair<T,U> const & x, Stub s )
        {
        return std::string("(") + to_string_stub(x.first,s) + ',' + to_string_stub(x.second,s) + ')';
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* to_string_stub.hpp
nyt7qPrcJMZclv38n2u0XkpPF5VylRcZbykPE/pMhE9YjCyYsN3JC5Qtski2vBQocWcbO1zaoD6/qVhSDKQlUXtajYwEVwVSQ65gHQkWmQVIfhk/s8j38caka57ocpeeovnZ4/yhWQ4K2ujWfg9pyyic5Io/cMFyeiCBIjaxXr+yVnCqixaURvpdZ9ezpU+/SVPnQdcO4/OgbOHtiedcieJX0MnyMdy63cOeoTCfF6e1EVe3btET+b6/sqvo74IQpo+j6F0Q7IoqbaG0VKYY7QbLYyi+UQqJk2L0IzvaMMPFUzy0IwNMSiAqcBdZ/LLxHCkP7JAnWU3CXk0aNFhVYveh2tUk2qBV0AbtQvn4ToX09esAC3NYBzxyLl0b/nU7s7+/6LwJNPpu6ISddzZ23uu58x46VXXeX0MpGsPv7qY/XRJD2edohLHG0v3ewpbmhBRsQXENiQ9fNqi9k2yFXK33bRPOU4US//syDFYqzsgsYHYiWRUK8mLV5b6tkGHCxsSKYWkbBkUqoehHKNAcOov6wY2B6yPtag8KJzOn3NVmAJlg8kEnj/TZaBhGqx7z0A3GPD4HWtgUB5xAtHRr1a8etTn33+rqUVbE8er+gWRagtqmESdNrcGTSHK0vr8LWljXqNNfFCf742NUvtZBztWwkSnU/2GA7v/gtGV/fGyA1f8hs8q2/4NOb2JNJcFFLu/Ty/tQhWsv79XLz3PYsy++099qX/w6pT7xydaHwP+2VT3sk5MIXLNuntsA+6TQx5aEiqPgUXAEEafxchjkVrcnN6AcWNXf1rGl3Iotay6dGFs5Ocihl7LGeaQZ/nvdBfLPneIk6I6uEhTvZGshEyYDsWSNWH8m1lER+wNDwMRHeV37yrzlOrWrmdooouYKTFOk4NRmApDalhgk9VYHRWpTnCx+lqIjpTrWTV3aZyJOJmIkSShYGzW6pzXsL6R9WVX6pSqntL3tSGQ/MD8pO05OTs/FcoixTkIdKTmaBMZktw2/i8j0N5+h6I/Q6L87WtE/Kzz9R8gb2y59+f4/0TL+5rX2BqvWd6SSfBU/SdpQ0mWsD4rsyKqGTONFgMtjHaoA3Slu4tSjoSSV2PUDCfve282nM1PZ+u2zWDpDw4VfW8PlNdubXIHLZPQmtdvCOs6V/vJe2jnsaSfVtx/O57lkQyfec5B3okNoOIirmGvPl3nxWl66pyCG8M6DbQ+uiF6l7cx97djedXXQ/tP+JJ2BRfL/O00bvwPpsuVt62fL05R+PtQmqJ/DRin9vNfDiniqctZnLf3D6fXS0tr50Q98w7J6dV9S77uiWcha8flF/ycg0gdcxGO0iNYoKV0DOLWtutv6dLQcSz8CONOdjBRQJCrTM0GWwZuPYXcRHNH2uIN2EvGlJXRUq+WhgUxoODJxCCu/F7IkbEf3JyiGTiWGXPTCaCozcetAmY5+/3O5+IHhMrm7LJ7toYy802RGXPVFsDT+Z8S10t+/6q3pZ6djlXbWS/N6W+b3S4c2ID5Dmmh/QpXF70mQtcBnJHaXa0a+NJ5kPHOKTU+2yPR297LoGw9nScFHHaDdLm0jLgl7YZw3nvgKagXJNoDeGJv0WhG9LzxA7+xG0PswxR697a0FvTUOoPfqlw2nNz0lQvvldAttv7WdGt1+Tpvy/baVkO/AF5U1xpdfNFy+1T3t0fuspaD3YADoLWgEva426d1A9N44BvRaNILe5h726F1A9DYOAn257/OG08voEUFfUrqG6ou7Y6P15VB3e/KN9Qr55mJ97go0XL7LbdL7IV7Qa18N9H7VCHpfJ9uj15/otWgK7fe3zxpOb5FNeitaCHoj3UDvhkbQa5kcQV/G9wg=
*/