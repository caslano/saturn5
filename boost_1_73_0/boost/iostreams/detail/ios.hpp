// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IOS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IOS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# if !BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
#  include <ios>
# else
#  include <istream>
#  include <ostream>
# endif
#else 
# include <exception>
# include <iosfwd>
#endif 

namespace boost { namespace iostreams { namespace detail {

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------------------//
# define BOOST_IOSTREAMS_BASIC_IOS(ch, tr)  std::basic_ios< ch, tr >
# if !BOOST_WORKAROUND(__MWERKS__, <= 0x3003) && \
     !BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
     /**/

#define BOOST_IOS                std::ios
#define BOOST_IOSTREAMS_FAILURE  std::ios::failure

# else

#define BOOST_IOS                std::ios_base
#define BOOST_IOSTREAMS_FAILURE  std::ios_base::failure

# endif
#else // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-----------------------//

#define BOOST_IOS                          std::ios
#define BOOST_IOSTREAMS_BASIC_IOS(ch, tr)  std::ios
#define BOOST_IOSTREAMS_FAILURE            boost::iostreams::detail::failure

class failure : std::exception {    
public:
    explicit failure(const std::string& what_arg) : what_(what_arg) { }
    const char* what() const { return what_.c_str(); }
private:
    std::string what_;
};

#endif // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //----------------------//

} } } // End namespace failure, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IOS_HPP_INCLUDED

/* ios.hpp
kTUtNmIbAk8jGWksjvyOrNtrk2pPJmUh8MskUhZJdZCUF9fslo5Oaam/yThZbM8bqqXKBbJSvmgizJ6ylXkLSkE1pRcv74NqDalWHJU3JD4qAt1Dlg9FaCcbcKN9UBl0RwJy/FhQ7F/6gZQGOCqVaBqIxj6I4+qj4aOu0CjwxLeUya9IpMx6y6PrirAJ677jBVjBnP8yFz/KbnkbdLF9V9NdqM4j/QiPRXivDuciHPzE0ssX
*/