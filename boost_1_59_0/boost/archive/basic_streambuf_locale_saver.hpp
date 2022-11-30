#ifndef BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP
#define BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_streambuf_locale_saver.hpp

// (C) Copyright 2005 Robert Ramey - http://www.rrsd.com

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note derived from boost/io/ios_state.hpp
// Copyright 2002, 2005 Daryle Walker.  Use, modification, and distribution
// are subject to the Boost Software License, Version 1.0.  (See accompanying
// file LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/io/> for the library's home page.

#ifndef BOOST_NO_STD_LOCALE

#include <locale>     // for std::locale
#include <ios>
#include <streambuf>  // for std::basic_streambuf

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost{
namespace archive{

template < typename Ch, class Tr >
class basic_streambuf_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_streambuf_locale_saver(std::basic_streambuf<Ch, Tr> &s) :
        m_streambuf(s),
        m_locale(s.getloc())
    {}
    ~basic_streambuf_locale_saver(){
        m_streambuf.pubsync();
        m_streambuf.pubimbue(m_locale);
    }
private:
    std::basic_streambuf<Ch, Tr> &       m_streambuf;
    std::locale const  m_locale;
};

template < typename Ch, class Tr >
class basic_istream_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_istream_locale_saver(std::basic_istream<Ch, Tr> &s) :
        m_istream(s),
        m_locale(s.getloc())
    {}
    ~basic_istream_locale_saver(){
        // libstdc++ crashes without this
        m_istream.sync();
        m_istream.imbue(m_locale);
    }
private:
    std::basic_istream<Ch, Tr> & m_istream;
    std::locale const  m_locale;
};

template < typename Ch, class Tr >
class basic_ostream_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_ostream_locale_saver(std::basic_ostream<Ch, Tr> &s) :
        m_ostream(s),
        m_locale(s.getloc())
    {}
    ~basic_ostream_locale_saver(){
        m_ostream.flush();
        m_ostream.imbue(m_locale);
    }
private:
    std::basic_ostream<Ch, Tr> & m_ostream;
    std::locale const  m_locale;
};


} // archive
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_LOCALE
#endif // BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP

/* basic_streambuf_locale_saver.hpp
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
*/