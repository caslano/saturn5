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
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
*/