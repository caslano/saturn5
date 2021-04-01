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
V977fRmrRDQsXqe9mWsUIty8R7eM16xDL0LZ0DXV9ri5fDjf6Oez8wEwV3xfKTx7rI5YFK3KUiXZZBGqo4wx72nLPjAsjNz3tSw4Kh6k1oOPyqcFS8nQ+7tMm+kNmTrvpxOWwKhhqd6EZrHPn/JUak0RL5hirxYP/GAr52RSg4jrJLQlDiHTa/rvleZm4hXzvfMmeQo2p41Y2k4DAFZFIOH4YcH1fOqvgH+xIWH7yaLHPvIgTh3CGy2LN8V9OPe46uz2hScUTpauWmirtvKU7sL/BrCXxCyEgg92CtG2a8zsRMWzdijzkGN45TyqNoqqyeOmTwWpGoW5t4pJ1e90lnP/3ad35MV8qdSMD7fDmHor/DeqXznQrmP9G1s1OZqe/m7lu7trxs2dhYEv6uI5iRWua4VIB9LzA6kQv0IEghbsvF0himrr5+6zdeB5y7y2II6AlA5W9NWnHs9pcVtid2P0wKTmsiwwZhNhJ8z5Y2AoeVhVteqQ50gPEAOBSDo/tf4kJLDnQWcXbrKo0uw5cLd76wPJkZRRit0klFHTB6fe01xfsexwfoH+Zw==
*/