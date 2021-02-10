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
zi4w4ol6fGSzJjSH9jTXjVay4qiaaBKFuMnF+VsTMLYrmELyw4Ju9X4GEdZeLFIhbG8mCc7eLB6uSRorX4Ptdr3MQVY7D6edLzz2X3UrVeZ28ZXQ9qFILoieQ2V5H1i6GdktZxQt9hcRLyTJ0ZocbXBe4PjHUeM65T4qK+vLCqlP7I0F7ybxO6NdtT8cDoYX/Zv+RZV49CvEnj3tCTEHz6GgEHNtWsLhu0Q2L3+mzIUsyiNQ/w5CRRIuJhi5TpmQEF1sKwRf5HjxecvQ+XE2wbwvOO34GvJAXa9SaVu+7ulXUqewbEz8rPkf+u0eBC2+6s4h4sRjOhzJcW9siQUNZGfbdGtIt8yhdV9wX1bSpNK+3yk4kglo5H6dQlfOw405hyMYdFS/ZWbEGcBBGICBUuSiwzxJQ517JVB89hdAxmfxwTt/BjsFgVuZGncsSvbbNvj8La/vjjOHvnAGiTygMlB39SL0cBzkUwGJqLCq0FkIEC3zRQhTlcRdc0U3zFsW+GdVT3kQKm8exT9kAa3TO/r9ZkJyP9BKMTPFaqTrmbaqSgM1w0d+1Hk4uwzhuEBSRST89SjygVYeN4be+VzoS3pV/iRX9SrZI4jaDJy16dROIdcryF9Kbu9zB6hAzNi5qzl81fpE5jrWY5R4
*/