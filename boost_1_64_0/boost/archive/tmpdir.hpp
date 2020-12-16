#ifndef BOOST_ARCHIVE_TMPDIR_HPP
#define BOOST_ARCHIVE_TMPDIR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// tmpdir.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstdlib> // getenv
#include <cstddef> // NULL
//#include <boost/assert.hpp>

#include <boost/config.hpp>
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
    using ::getenv;
}
#endif

namespace boost {
namespace archive {

inline const char * tmpdir(){
    const char *dirname;
    dirname = std::getenv("TMP");
    if(NULL == dirname)
        dirname = std::getenv("TMPDIR");
    if(NULL == dirname)
        dirname = std::getenv("TEMP");
    if(NULL == dirname){
        //BOOST_ASSERT(false); // no temp directory found
        dirname = ".";
    }
    return dirname;
}

} // archive
} // boost

#endif // BOOST_ARCHIVE_TMPDIR_HPP

/* tmpdir.hpp
6nJ+Ww5IUGzTpjOlmLTr8ufOLSiBRoRg4QnSp3CGSbuVoknNfoQHvIVVTNa6ig3koKDUmdrrkVUwXslddBVokJ7uWHzvRU83+Dp3IXT1siPV+hiHjB6StgSKT5Up4Nd354y1zpc77Forn/Wwa8H8VsOuW+yEDuIZPqmUUCXOQxQeeWKX6U4oDfaw+2qsYnLr8iqcwYlF0qLzT6EHLg5ktu9GMJTINEmKe+RfcWXCK5K043CCPsYOV8k71ynjyryoKoxW3FtXpb860vyf6azbk43HRHtisXefT5GqTjiyVKUIUnj2yQiQNyeRwqdlgP8pxTg67N/lgT40L16ZgKE+1n+1Nq//+pXXf+HQsiPH52KM02hyMg9q1d+JnuuhFNPfvH3qW/MTrx1VGo51RcX8RN9V79a1O5rcunZIY13X1nlZ1bUmKCLVNekmzXnuWtQyP3HqIuPfNz8xCI2duTtU9ai5O1TcN7c7pO/zmBs8iLjpMw5NcZaSjZXtWRcTRj0feROXaX8RMQ/bOZ4HWB6gwHTosc9kwv0jkucUrRRDK+LVqFspr+bNLta1tHRXWbYGWiW+Dy3eKK/mmfz9DqOJ7Oeup56LQERMERuIj7J9bTvrj3JaHI2Q/NBSSX85p7/IOv21Iv2Hr53Mw9u6He98yNvgFuR9t0SuSB9vY9PblsQ34WrqA9Wfy62LcltVzNmW52xLWGe7WWQ7xpxtmnx4u8jgmIqta2ZPhpTXAaY3zlnsozhWwLywaBgOagOzFccnPoSeikx4YCd7MaqrDOkqg806O8wb8WCxra2kXtlCKcsf4qksC1pYlSVelCXjlVKWl3IDlEU+sp908bsdxHpnRFI1y3+dS5lRUd+H7UedI4UEwmf70WNJFCd/r5x8FwZ7CB/xnMKoG2Tp+Sw6Z+75/Je0WGL9EtYpifX+rcPN61928voXHMZ/oTzQKuKBLn1paU4ebOXHxmuO/gJ/HZWpLz1Z/3vQDOGSormG3MzWcWF+T7GeHEr98ueYNGk4bpI/oUeuDfIRDBq2M4O6V4LBmD3EYHlEUg9g2XLxeRbSdFSYcj/j4+h+RuIwfrhyP43F/Rx+odzPU7kY7sfY2J52Yl0Bf0qdiMqGl44RxbFTfoTG8HJk5KfxLqi1RlpEzysbjN/QLwf6FUu/3OmXge7jSJTxeyQREcEIi641bOTnUhwke0BZhfWPzc3rH3fw+sfmViXsI0roZy6hszzhj4LiIDPFXZGm/AqPh5eRxnuiABnqeI+pQuXBdvqtlmOYtNNdzdMh+psz7sEZd7TOeIjIeONzJ/MyEXtkLM9JRG+rtHlUnhdipIiFGGpLshpzsi6crMo62ZEi2U7mZLPldVto/gclmyjeudwa9cOcPC1ip25Ce5/clkCZBLg+DzLkIaDlzZQMv9lOGc5pZpXheJHhvRwlQ5NclzJMSYCOoi3kQ0r+FBum1j1LpL1nRtcR02st8m4IGqi6IZUO60yHdPhZRxftWFdn2hcS7ViHr9dJh04ag+udHHk2JMa9DBcc/SgUTkq2mAmEip/NBIrpQP8tLcPHOXzNhbLRes5d8n5lYPF5qJRZJ6/mqyiE8n6M+PaP5T0q7JRh25/mWLr2wZL6lF55l0e20rtMwmH8aOVdVhCCb5Fnlk/aMOgq3t1+Pdfy7u6LYrHJrTTlrN8zbe8vz+froPR/kpSmLJ32jm82j/rmU8wG/4ZaNq2JoU+KsN8TADVtKT5v8lv7d08/zesMaN7dKowqK3Lg1cti1ERsVpM+l22iH7fs0Y/krLIRe6XePvo7HeyRfXA+qIO4N9kw19Kl86bGdne8ycT7gOLJlsFrNi/r+1ibWJb1v/tE+qU=
*/