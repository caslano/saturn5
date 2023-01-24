#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/text_wiarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_wiarchive :
    public detail::polymorphic_iarchive_route<text_wiarchive>
{
public:
    polymorphic_text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<text_wiarchive>(is, flags)
    {}
    ~polymorphic_text_wiarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_wiarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP


/* polymorphic_text_wiarchive.hpp
MCQGjPWNXHEPeRWLWELd7s5sUIFNRh4GCArXBDwiucqXIHdd4b62SdjWoGkqVhdiEhcnsHWZiEExAnFjTECcb4ySMwUNyM9QEhOyEehJfpXlraE5K7Vm90NR9Vhx7GwdERGFmCylOMpDgEgJnYmSH9tacm5ciCvwVSv7Ed9BrIGcSmR4XAkqBt/yWLZzlHBdhuQeKD/7Ft7BoDcA5BhtsLezGZVj7HEUvmcXEklbNLPcUkwm2nY2WA1E26fbQiLuWQyqZHa3Qxsk0cQzAQr2crt7C0yI192LX4FBxPbSELdDxN+sI8TMh7jGKlTGqSZCXPqY2P98iMERnmLiu9b5dvi/QjXeqrVPHZBPfh3aWG2DURM9pmIE5k78e3OjCntbmGeWMXXGPhkn5yeMDetEmazgT8APHspfhtkqfmRVg5qAjlZ7oTfHmOjDNdtKcUWOrpnD26I+RQcuNGGpz0Gb7rE8Z2W/b9WIn9Y3klnMRkH32iOaBIMhXV5uCxNe0iF2aJWw7lltLe5pnXPQUsRv9YKtPDRYtKeHM3OrheVfvYY4MnCu3wuZ7AgqJHcsP1Oz78HWO8MfDvSh+NiHYgd7SaD4fo72BPocvjoRKNDNZSMztRcM+C6AXwtoVKdKzrdAsU61J3pc61HYmQ0G6HHJlM5shcG8C43p6dJm3MoL9+NJd6O0+UP0wRd5LG6rx4PN2OknKAxux9sELhQQ
*/