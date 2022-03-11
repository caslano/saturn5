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