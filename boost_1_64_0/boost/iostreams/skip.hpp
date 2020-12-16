// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// To do: handle bidirection streams and output-seekable components.

#ifndef BOOST_IOSTREAMS_SKIP_HPP_INCLUDED
#define BOOST_IOSTREAMS_SKIP_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure.
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Device>
void skip(Device& dev, stream_offset off, mpl::true_)
{ iostreams::seek(dev, off, BOOST_IOS::cur); }

template<typename Device>
void skip(Device& dev, stream_offset off, mpl::false_)
{   // gcc 2.95 needs namespace qualification for char_traits.
    typedef typename char_type_of<Device>::type  char_type;
    typedef iostreams::char_traits<char_type>    traits_type;
    for (stream_offset z = 0; z < off; ) {
        typename traits_type::int_type c;
        if (traits_type::is_eof(c = iostreams::get(dev)))
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad skip offset"));
        if (!traits_type::would_block(c))
            ++z;
    }
}

template<typename Filter, typename Device>
void skip( Filter& flt, Device& dev, stream_offset off,
           BOOST_IOS::openmode which, mpl::true_ )
{ boost::iostreams::seek(flt, dev, off, BOOST_IOS::cur, which); }

template<typename Filter, typename Device>
void skip( Filter& flt, Device& dev, stream_offset off,
           BOOST_IOS::openmode, mpl::false_ )
{ 
    typedef typename char_type_of<Device>::type char_type;
    char_type c;
    for (stream_offset z = 0; z < off; ) {
        std::streamsize amt;
        if ((amt = iostreams::read(flt, dev, &c, 1)) == -1)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad skip offset"));
        if (amt == 1)
            ++z;
    }
}

} // End namespace detail.

template<typename Device>
void skip(Device& dev, stream_offset off)
{ 
    typedef typename mode_of<Device>::type     mode;
    typedef mpl::or_<
        is_convertible<mode, input_seekable>,
        is_convertible<mode, output_seekable>
    >                                          can_seek;
    BOOST_STATIC_ASSERT(
        (can_seek::value || is_convertible<mode, input>::value)
    );
    detail::skip(dev, off, can_seek());
}

template<typename Filter, typename Device>
void skip( Filter& flt, Device& dev, stream_offset off, 
           BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    typedef typename mode_of<Filter>::type                 filter_mode;
    typedef typename mode_of<Device>::type                 device_mode;
    typedef mpl::or_<
        mpl::and_<
            is_convertible<filter_mode, input_seekable>,
            is_convertible<device_mode, input_seekable>
        >,
        mpl::and_<
            is_convertible<filter_mode, output_seekable>,
            is_convertible<device_mode, output_seekable>
        >
    >                                                      can_seek;
    BOOST_STATIC_ASSERT(
        ( can_seek::value || 
          (is_convertible<filter_mode, input>::value &&
          is_convertible<device_mode, input>::value) )
    );
    detail::skip(flt, dev, off, which, can_seek());
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SKIP_HPP_INCLUDED //------------------------//

/* skip.hpp
W8Fa2B1eDXvCGpgHzb2M+E2wWnsZ0X9erT2J6Meu1t5C9AFXa28h+kVJ7S00KsF5dqm9hf7Z8+rW9py6wp/TnVG403BzcYtwmb+kO/1wI3HVuJm/pObTpY7UkTpSR+pIHanjn3WsJfv/8mkT13z/v866/18X2f/Pi1Z2/pO5Aed3dPzxlnGR+/7p3lGzP/XtXRD29r5KbO8oZBtl76j0NLtutWG6JbevVe0a6xYS3YrT7PslzjN100KfXLpqe6iwNXe1K7xePZCtX3O3IizuVe8lY8k/cSS+5m7Fp4mvuathw+vAPreCsMmto0t4076MsdZVl+faWg/VrLf5Tez1Fgqrt9XbhyKURL2Fkqi3UBL1Fkqy3kL/kno7rZm93grD6m3Va93b6q0wiXorTKLeCpOot8Ik663wX1JvhS3s9Va32Ky31VubvG5x4vVWtzjxeqtbnHi91S1Ort7qFv+z661+nejkx/vs45Kxxh+TH+97/BHXf1bWF9+0emfcyBkD3j7v+PJnPk5+nNE+zvvvGU+0j0cnv762fZy68daJ1u/X2s/kXrCMFx2o369HwSbwIOjJ1caR21fl9lO5keZ4QBy5virXT+U2V7n+Xv8Frqdy5vrGg1RuN7gO3AOuCwcb8qE48oUqv4PK76TyA315wsSRH6rye6v8MJUfbsjzXIkpv5XKb63y26j8AFia4HjBwF9T6/Kl1uWLP4ZQTBuZjpuJewi3CNd6JWMIK9fOuMHa+v2PRfMa//53f+NfaOztT5OWYx/Nywjclj35s9g2B1V0SGj+E/K2OSr+nj3N5fpAmd1fgLP0nYgj8XlRhLXPSVEb33S5PsjpjHQ/nK1P5cdBHylN+kjJ9ZMaywZX+rER6zMM13fLMNxW1E/FYvuco/oacmLuM3ilyGXaf//b68yfrzNNru/pdHcC9m8CSdRXhb2+/LkSR8r1XZ2uTpqtrpBPfG5bRQJ939Z/cZ1G21X/Nfuj/CD91RntjrnzytuGlp3Vu+CXdevOnvnv2R8l2f7wv2UflLXR7632nmH6PB+k7XqiN+dA+2PtodyPcH3YAXaHXWEPmA17wY5wG5gDt9Xr28F14BDYBY5Qf38/FU1/uBO9n8r6hAvA7rAt7KHp9oR5cCOYD/M03Q3hnjAfDtPrAxLsN6bsTP7Z/cS13UecRV9w/lrqD6aO1JE6Ukfq+H8ca+n3vztc3Ci//y/21v8z9pI5ERfAnYD7xF13rM77fSnpFpVOq5DfWnMy3XCuV8N8rVkSdhPbb0qNJyCyl2aE7yXfEV4t16c4O8v8ygOQr59Te23E3Nnw8rb/VnN1yxLddDw+4hvHhprHPNxThC38KDyPh1SWlXFJdTXyqbruLOG7W/NJXOa3A3THJaE76anu4b//l6vuzVWoGW6R22GO0H1sWVVBUUlFRVFpSRUNIbKubDoTR3L2DpHlu7XXhoK+br7dw2K3Ddl0LC+ZVJagfjVrqJ/xDSWqDE8lkdpo/YpGlxdNmlxaVFZdkZiOtWuoo1eGCyw6fkoZzo7WUe1tEtNvdiPpV90kWr/P0G+eTb+JJWOnWu4j6xzsJPUjPqt+OU3t5Tffop/YBCXYBucnqV+s8ptr0e9z9Kuz6Deh7IixZeWJ6VfXSPqNbBaln2xKuMyin94gCem3bA318+7hlRb9DncT+ThKP7GhcS0xEq1j5+PG0bG2uV3HUCwdy8oT1jG0hjpSz2oXYdcx16bjtNFuMSakX24j6VcXQ78Cu34UYWL6FTSSftNbRuv3RU/K1aLf1PFjyxOt38JG0i+3VbR+X6LfUIt+h5VVjj/kiMT0G7qG+nn9zX76oX2c9sXG4m4lbHGEfuVlh4s=
*/