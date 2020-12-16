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
OCRk/2MFbmud8Py9E27h3L237lYk+XLdYxdmI3tx6835YVjM+Q2I7rsrNkSK4GbcVsGn4Ql78OJWHLEXb+oVXJu/n0BC+/Jm49YbFsPVSHZf4oIH0Xkaxo+jfHFLvTJok6Q/knklZY/oHr7yw7IWCe3lu/PK0v18j19J3OhsQAZzvgtG7u+buZI0I6s4XwpD9k3WriRNcBuyX/f+3YvbFngIHsMtcBXp5LwN9NoPOAv3mTB1AteD7WHIVsoNLnspN6C3DzmEYDuFm2vckOSrubYTFzwKt+GW7bjB1TC0j3CTM6LvJey2tbKLMP1xS55Yuq/wNLgU2YgcwH/pgEhbLBA5hqRfU2qTZfQ16CK3Iamc74Re+w+X4D4Z92JkA7Id8d6TWG26rAruTdwGxk+mvGALWARXIaPV3stW5xzug5G2XwbD1Gu5LkyHT+M2ARYjByZzTeje13gr5xvhfmidSVnBXZw3uY50cD4YDofZuu9xEechezIlnG/hvMUkbAMi05BiZAOyHXkTOYakTo6zMpGZyCpkO1KCxJ8ZZ7VHhiNzkBXIxjMrbNRUHBVHxfG/ffzL1v87y/9/Avt/zvr/yak8D+o88vY+Y2tZjuZIx9Y8P/YOziMfctr0CwryinKnM0HWGPFjRTafE8PnRXt/w9J47PB5N97fsND1WE/sPQ8JXc851p5rJ1TXzGE5UJufyHLMV4qcDxfvMdckIXydrM7pj75Gm2d6Oeq67HhnUO75wXIff9qI04ZgdDFkOdFVJlREtHknrjLp3Fp0cxYuKPLeB8SjTKaUu0xIi6tMuCZucs2wtaXHApYco5HKyChtY6tdedVWJpnFO6b8rvZuW2b+7k3iP9gr/4T1WnPm2dbQPfla9CfFv6Zn29OwuElYjpyixfm505npZuZI3yo6PdHRdTasAZkxb3ahe33OPaLjrLTxmbl3jAJSb1NjWOt1Qr3F1JalTKK2Za1f1qybeYtyNNL6PRys37zOIfOfXFZHj5jGjsPlGDsOl2PsOFyOseOwRz+ZVu5+8tOMHUc5X+mL/k3d+1tv+b+1l/fbebRvyUdedtyfPnf735tUsu+855bxe9/ts2fLf943cu9v3uWf6/BTfSP3nnMQbY7Cv++buuydEPp91XuIzRF7J9TT96NpsLl+ZwqFy9dwdT3CddRw6TAFdtJwWWZMpZw0XGVkcGjutH6/bAqTYTNYDzbX71otNR2nwFGwfSg9pq8Th0d6amt6kmEjmAIz/LG9t4t4Z+d+X+d+T6fv57zfzXm/lyt9Fzcc8Xr/pu/e3O/dIt+vud+tRb5X451a+Lu0yHdoq5DId2eR780i35n1RrLVTq++H9N3Y+admL4LC70HK/sd2Cqo771OeOe1BeFdF++5vN5xxfZ+y/VOi/dZ5l0W77HK/w4r+vuraO+uIm0Je72nKt87qjeh2h4276NWIR7voYwd4gOI+53TRsQ6k7TCNtD9fsn9bukg74KSp8RZGciEKRXvhSqO/53jX/b8Py/vnJ9q7/+zzfO/zCeRI0nz4zjmOHv/n+paRz5uyKARWbKmIGgCiIeT0DPaHJnLXpDnPYdV49F77eli44Cs55TuVTkBf3y97ukJW+Z+02H32k5a6mhaQvfaXBM3uWbYM0uxPn9/itjIJ0hv5/k7Sr4Lc4tK88u9Oxcx62/PlzAHKTvbuhfZ7W3jiLgj5y2LXTKz9nWV+L9grSOlv0U8yoQ4PO1TmfXYn4t/b6sD2qH1Pf074MZV1E4Fh9od0DD7JMw85v6MPCFMyOZIPoo7qIXvuRG6kL9vRv5MWXzB+VLc04Wx2a86s0PkOkatOynXiLnWxnZbj1qfSTqZ69Ba6tI=
*/