// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains machinery for performing code conversion.

#ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HOLDER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CODECVT_HOLDER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <cwchar>            // mbstate_t.
#include <locale>            // codecvt, locale.
#include <boost/config.hpp>  // HAS_MACRO_USE_FACET.
#include <boost/iostreams/detail/config/codecvt.hpp>

namespace boost { namespace iostreams { namespace detail {

struct default_codecvt { 
    typedef wchar_t         intern_type, from_type;
    typedef char            extern_type, to_type;
    typedef std::mbstate_t  state_type;
};

template<typename Codecvt>
struct codecvt_holder {
    typedef Codecvt codecvt_type;
    const codecvt_type& get() const { return codecvt_; }
    void imbue(const std::locale&) { }
    Codecvt codecvt_;
};

template<>
struct codecvt_holder<default_codecvt> {
    typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;
    codecvt_holder() { reset_codecvt(); }
    const codecvt_type& get() const { return *codecvt_; }
    void imbue(const std::locale& loc) 
    { 
        loc_ = loc;
        reset_codecvt();
    }
    void reset_codecvt()
    {
        using namespace std;
        #ifndef BOOST_HAS_MACRO_USE_FACET
            codecvt_ = & use_facet< codecvt_type >(loc_);
        #else
            codecvt_ = & _USE(loc_, codecvt_type);
        #endif
    }
    std::locale loc_; // Prevent codecvt_ from being freed.
    const codecvt_type* codecvt_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HOLDER_HPP_INCLUDED

/* codecvt_holder.hpp
iJrpjWTROQ8N3Q+ll3EQsy1mU94EwHSgxX2jznw9hgMLOMKp3cLqvLSkaFTBIZ6WAtWvlba/3KFN/YFIlv9tE/ZU+xNXeZEBhrQlUWuBqLLFo3s7Cmxt+he4mR1QPNC+EOUSunV30OHJjNDYUJSSrYvsSNM439BWoEf+W5W+NuoMM0APfDpmIbhVTGdmfFL3Jr5Vm8GJc+yMPNXPOSg26mZMo/7e7k9ucahT0gffalhZ4y063nAfCx8KvBPq5r0XQ+BMgC7buQEvzR+idC26/toDz5rk9sxslfr8cX0NmfZ/5VK3VlCbFchgJDNIVThlfyqOJ/a92PQ1/ZHfvqphyzDk78rfCDN+OCmwX+zy9XdgLI+xaU2w+rC7KaDhkHi4esAbdyJKajq0YWa67G1BYX7W/zp3xxZS75ihWM8JZeBKMwaC3g6/V+bx/0L6p0PxdN6hnWa+qmiCYNP8kpoHEkWMfEOXj6KK0RpMNuiBn4UqekoMJOPlu6Tq7YdffjqiQZUqxKqxB3qs2EHwqop/NM2Kd8VMOBY3kksXYD/wyGVcOtN+/51CW5m5C9rEG0nQOJ59Xh/zouKneLfuubyoLA6OVVNQvso0vbZRMAnImoMqK129eU6NPRdiFkkIaIT1mbT140ym8F7ivYG1xJ+OKyBF8ad4yMLlhhQbqX13VrL/OfBHAgnpQgu6/hOIYPwC3dOY4JqdLcQQWokf
*/