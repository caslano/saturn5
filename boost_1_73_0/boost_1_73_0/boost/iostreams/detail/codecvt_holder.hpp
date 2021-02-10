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
WWX9sjL5YhELBVlnkxVKVBWuyqxEQVwQtzjERfSzoMid7fGFnFUVu+LhKqebN52N4NdVB64S+HIR71x++kFyqsI+mSUnqAgqFoWKiHBKisWXnkmBJFQVi+LhJ9zfigdRiuV+Hb/zx+O97jq/pPPLIhIKAkOWqs9fmWUpyAwyg8yImALNOc/IQB6rimfxEJbTN4wHY5R1FedBWAIfMiKry09JSFhVGCmzhAU9QU/QExFYmfD5bA/lu9qkRwJmWiRObU4muY3QuC62xSgzAq4Rj7tynCGlTjK1tLXOj47WaTRbdWO0a7iDtyqpamqtyRw8q9aT57WezFfrcJaYXm97atvizaQTjl2/y4Ab78y2DzavHRqZrhFGtuOnI+fryv9QSwMECgAAAAgALWdKUvFMw7VSDwAAlU0AACYACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9idWlsZC1vcGVuc3NsLmJhdFVUBQABtkgkYNVc/3PaRhb/vTP9HzbMqIkzBhtMie3GaQnGieeIzYDjXKa0jJAW0EVIqlayw0zn/vZ7b3clrYQEApNe67vGoH37eV/2vbdvV7v+hRpzl7jT6fff+XRBXu7vRwKSjT9j/t8YfuB33Kvvu/+hRpDfYzz+k4j/Qc8R/C7D7Igk3f4c
*/