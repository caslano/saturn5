// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_SEEK_HPP_INCLUDED
#define BOOST_IOSTREAMS_SEEK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/integer_traits.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/ios.hpp>       // streamsize, seekdir, openmode.
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct seek_device_impl;

template<typename T>
struct seek_filter_impl;

} // End namespace detail.

template<typename T>
inline std::streampos
seek( T& t, stream_offset off, BOOST_IOS::seekdir way,
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    return seek_device_impl<T>::seek(detail::unwrap(t), off, way, which); 
}

template<typename T, typename Device>
inline std::streampos
seek( T& t, Device& dev, stream_offset off, BOOST_IOS::seekdir way,
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    return seek_filter_impl<T>::seek(detail::unwrap(t), dev, off, way, which);
}

namespace detail {

//------------------Definition of seek_device_impl----------------------------//

template<typename T>
struct seek_device_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          seek_device_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, iostream_tag, istream_tag, ostream_tag,
                  streambuf_tag, two_head, any_tag
              >::type
          >
      >::type
    { };

struct seek_impl_basic_ios {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.rdbuf()->pubseekpos(offset_to_position(off));
        } else {
            return t.rdbuf()->pubseekoff(off, way, which);
        }
    }
};

template<>
struct seek_device_impl<iostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_device_impl<istream_tag> : seek_impl_basic_ios { };

template<>
struct seek_device_impl<ostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_device_impl<streambuf_tag> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.BOOST_IOSTREAMS_PUBSEEKPOS(offset_to_position(off));
        } else {
            return t.BOOST_IOSTREAMS_PUBSEEKOFF(off, way, which);
        }
    }
};

template<>
struct seek_device_impl<two_head> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { return t.seek(off, way, which); }
};

template<>
struct seek_device_impl<any_tag> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode )
    { return t.seek(off, way); }
};

//------------------Definition of seek_filter_impl----------------------------//

template<typename T>
struct seek_filter_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          seek_filter_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<T, two_head, any_tag>::type
          >
      >::type
    { };

template<>
struct seek_filter_impl<two_head> {
    template<typename T, typename Device>
    static std::streampos seek( T& t, Device& d,
                                stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { return t.seek(d, off, way, which); }
};

template<>
struct seek_filter_impl<any_tag> {
    template<typename T, typename Device>
    static std::streampos seek( T& t, Device& d,
                                stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode )
    { return t.seek(d, off, way); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_SEEK_HPP_INCLUDED

/* seek.hpp
0XrjLfite/0M7IwKRIdSdBggMmXB3YLBqH10JpeX6TY6xpoPy+p/s15HLOLnx3u6xqv7WMnvtLJSegZ+O7pV0mrjx3XGN+758Xwt2M5fH6ebxF8R2Ml5Bvs/4tO2OUdkl6bdl9bV9ptbym6FlE9NMBQYk9ZZ39sDJY3BaZPRbkJgA2cD5CPnMLrqzpf4KwNV3Ds1lOhKnBfvixJHywC7/+g+Yl68NxC6BS2gyOkWkR7+5GsYIS4m3Q3ddKUdFZOXlaLn9cGI/pO/Hsksub44WJKW5SxI21HKYCRyw0THIcG+waBtPye///X+svr62JD0syPqQ3otxnpGl0ucdzudtfyLRf/N0vKdGfRjnsHmsCByXyh/r4oake0r+RqKfq+I3q8FjfoJmy/8oeh1DHMMhonMKLefJzIfBBvyQ6sz88PVBSK3m9PE6S1yE5F7QeTeCkbsRaX1w72i7bSAJ8oNkh7+2lZlXyR9jj4iefgk7TapH68vXTGuZOo4ox9t9rEd8T8af3evGnefmrMyvb1qjt8m1p5BM0jH2+OpkPCnZXr7lRy/i79nkMa30I/vxCax4hsl+Wsr8dUQfoEf34mhyPj6Z+leSS1PHEh8kXs9+O3mFImzh5NOmYkscfZDdooh6+/tpHFXZKmuwRP3bp3G5ldNHNFpgOuPU51G+XvNqNyiLG/frBNzXbnm6a3pkzuSbhXX6nBaBhvHKoPTRN+W9WsKEH5hQ3r9JT11W9OHaWP0t+lf4/z+tfS7a4y1XGZG7Nc0N8E+tzunr7e0L2cMH4TLp1WQH/xa1Psxn36ydDLokP+j+kquX66lj97D0kcP/0Ym94n4HR3Wbw9fL7A6x76n1Lzv2qzWnlLIJbSnlBdO9hoj0X45q95T6klkvD2lPidsQc5fs6eUNxd7QCf7fkl137VJer+kRcjY90vS+HRvlaPJU/NOa75fkrem7Bud7HsFOd+3We29gpBNaL+ceHot72zfKyj0fZuk9wrKRMa+D47El9BeQYRLaK+gUIJ5X9O9ggq62PcKKvi+zWrtFdQvThkRZ0J7BREuob2CCOe35xXU84J1/tl7Bdnn08aaV5z8PNs7HnT9zynY/5flJRXt1pvc4oVbTxq9S2qvoH/jXkGFkXsFreaeQM9645Q6TlwDs3EPafw/u3uLwF/gZnAl3Ar+AXeAgUD9fOgg3B+mQ1lbGFbAZrAStoSnwTbwddgOvglD8FuYAb+HHeDPMBO20vllebAjzIdN4ZawMyyEXeAucF0o87G9MSPY0/0/Yj42nO6yJ3T9NnB0PnFAv5frmE0N3AhXqvN8NiZcX7gJHAL7wuGwHzwYbg6LYX84GW4NT4DbwMvgRFgLJ8E7YCGcA3eAL+r11/T6R3B33etlMOwN94RbwL3grnAI3B/uB6fAkXAa3B+eDSfCC+AkeA08CD4Ai+CTsBh+q+dd0+rPd4HuebGeHwZHw4tgKbwOlsHn9Px7Pc8M1p93h2WwDxwLd4Dj4O5wEtwfToDj5Vzry/uOCDe01Fel1tdUmAenqdxQV0eV45udyO3qyLwwOY7W+VcnwcPhafAoeDo8CZ4BT4Fnw5nwXHgnvBQ+C2fC5+EVWh9Xwt/hVbAtic7S+rlN62cOLID3w230fBC8Dw5R/3L4IDwGPgRv0POH9XyRni/Tc4e8PAK7wHmwF3wM7q3nR+n5NXo+W88fh0/ApfBpGAxyn8Mm0D3vDJ+DufAl2AO+AnvpeZ6e5+v5AD3fDr4KC+FrcKD676XxDdHzveHLcISG20/P99fzUXp+sIYfp/7V8E14JFwIj4YfwmNgHTwZfgzPgZ/Am+E38EX4HVwIv4ffwOVwBfwUtqB9fAY=
*/