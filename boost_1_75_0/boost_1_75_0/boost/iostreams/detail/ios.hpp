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
ufagWxashpbMTlqZiLD8vSAEjaIImdzqOoYUDw80+KlkgZLyYtbOTBDCbkW9kxx0/emfpxvK97uZ6D5MXSp7j0flz+PMOZzTNhydHy/t/RibmAHcrI5f6KvbGy3W34CX8YHgr31pMr+LPqk/dE+KQn3iCtagDYgtpgIpb813Kb6usMm1ZhLBuWNzZ+8ajGDk8DV3ewAQ34+7R6Cj6sG36Mk1xYRndO6C/Ca0+ag/cXxLS/+LTqw9gklSUep4NK8C8uOE96uX8kPbweMbcGqDolkf7D1LClNIOVBa8ozs+WmI1IPYAeXFc/tjL73kOVyjxC8QoAzHCZUTZBusBVkPywm9hjpn/xswED+gMDAzwDCAtadZLiSUD7nHaYTvxOcE93fjZbsYFz5iaEa58VoJ59r+J8PARTBccGQQFwQy9K6s4/XntbLdPDceXxYzUrb/WRhqwhiaBXghmZTc7Odi6ERD8nnrgZjHtrzHswsRa6q/MyNB2zTpUJOUQ8CWwp2gL4nN8DvcpeJW2wHVUlsyr01uW3fcn/La4vLxawSHYqjeQ+/MpvF4sORKFt73krLYUzyUylcKiMRF0LxX4EA9JtwOuL1t1vGPPSM4PATNcCQh9lnwlDaJD6uu3xGLJU3GvV8O3fr55savTlUtitwmOeFWKrpmWlYQBH59RtSC4v+2tQoepyeMXoXtP69htqu2vaNxKo4swt9wYMg9
*/