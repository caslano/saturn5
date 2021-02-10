// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // BOOST_MSVC
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/default_arg.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode.
#include <boost/iostreams/positioning.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

//--------------Definitions of helper templates for device concepts-----------//

template<typename Mode, typename Ch = char>
struct device {
    typedef Ch char_type;
    struct category
        : Mode,
          device_tag,
          closable_tag,
          localizable_tag
        { };

    void close()
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
    }

    void close(BOOST_IOS::openmode)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((is_convertible<Mode, two_sequence>::value));
    }

    template<typename Locale>
    void imbue(const Locale&) { }
};

template<typename Mode, typename Ch = wchar_t>
struct wdevice : device<Mode, Ch> { };

typedef device<input>    source;
typedef wdevice<input>   wsource;
typedef device<output>   sink;
typedef wdevice<output>  wsink;

//--------------Definitions of helper templates for simple filter concepts----//

template<typename Mode, typename Ch = char>
struct filter {
    typedef Ch char_type;
    struct category
        : Mode,
          filter_tag,
          closable_tag,
          localizable_tag
        { };

    template<typename Device>
    void close(Device&)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
        BOOST_STATIC_ASSERT((!is_convertible<Mode, dual_use>::value));
    }

    template<typename Device>
    void close(Device&, BOOST_IOS::openmode)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT(
            (is_convertible<Mode, two_sequence>::value) ||
            (is_convertible<Mode, dual_use>::value)
        );
    }

    template<typename Locale>
    void imbue(const Locale&) { }
};

template<typename Mode, typename Ch = wchar_t>
struct wfilter : filter<Mode, Ch> { };

typedef filter<input>      input_filter;
typedef wfilter<input>     input_wfilter;
typedef filter<output>     output_filter;
typedef wfilter<output>    output_wfilter;
typedef filter<seekable>   seekable_filter;
typedef wfilter<seekable>  seekable_wfilter;
typedef filter<dual_use>   dual_use_filter;
typedef wfilter<dual_use>  dual_use_wfilter;
        
//------Definitions of helper templates for multi-character filter cncepts----//

template<typename Mode, typename Ch = char>
struct multichar_filter : filter<Mode, Ch> {
    struct category : filter<Mode, Ch>::category, multichar_tag { };
};

template<typename Mode, typename Ch = wchar_t>
struct multichar_wfilter : multichar_filter<Mode, Ch> { };

typedef multichar_filter<input>      multichar_input_filter;
typedef multichar_wfilter<input>     multichar_input_wfilter;
typedef multichar_filter<output>     multichar_output_filter;
typedef multichar_wfilter<output>    multichar_output_wfilter;
typedef multichar_filter<dual_use>   multichar_dual_use_filter;
typedef multichar_wfilter<dual_use>  multichar_dual_use_wfilter;

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED

/* concepts.hpp
PVKVEO1n4Jg8RRXmv3NGaPDckFiQbuHVQ94RRE1x1Wm5FVbWrIeutqp6z4yTubJzHC5/lzDXObr338digtuJXCmwadjqWGtwM480gEkZXY1BftZKiMrS8v487gZhroekNHhuSCxIt/DqIe8Ioqa46rTcCiur13NXz5I7V4VMcR1VMOShNNMvMUX/+/nd/OF8Gr0/nMli84ezSbT+cBOHyh/OUET84TY91B9uV5P7w3VayMoMnFshlc0fzmay+8OrILL4w+08en84TRv2hxOUVf5wki7oDwdVhf5wXVS3PxyN6feHayK6/OHyeO/lD6+CyOIP5/JY/eF8Gr0/3Mii9IdzVDF/uFUT94czFBF/uFYPfQrD30NXRWb1h/O5GP7waqhs/nAGk8UfTtRX+MMp6kp/OE0b9ofDymJ/uDayzx+Ox5X4w3VR3f5wWczXLhPkiQ2YVxGN3h/OZLH5w9kkWn+4iUPlD2coIv5wmx7qD7eryf3hOi3kiQycWyGVzR/OZrL7w6sgsvjD7Tx6fzhNG/aHE5RV/nCSLugPx1VRRwLiyebT6P3hTBabP5xNovWHmzhU/nCGIuIPt+mh/nC7mtwfDmoJ/eG6qG5/OBrT7w/XRHT5w+Xx3ssfXgWRxR/O5bH6w/k0en+4kUXp
*/