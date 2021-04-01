//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::websocket::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::websocket::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace websocket {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // websocket
} // beast
} // boost

#endif

/* error.hpp
vcfXjwYH5emgDLRv7BDCXmZ7QYzysyQHxCzayLH+IT1aZdePCpbLWd0qqypimTuCOOP70zbTIT4eJyqHRf5IbDz38oRxfdkUpPMANsEYB8S4MpXBRsP3nbiATOBaF1tec8R5FYmQYmoGvFPwwYLsr/5xoZdpzI6tAOoqZNsi3rwdNGDolUNqDwpIcAAaXTjnAsVgSf4bXP+y2WDlVhszbFqfkN3qiQAx9stD8LsH1TpPQ9dDgZJ/6n8wcz0JUTLRr3UgTYAYFFHAJ4kicr+DARp3uLGo9ozKpdmAyAbes5QQFSdikUED62HsiYoa+CEWLHtr9JsOA/CvkKb2sN5x6XF4EPVjHVx/hbG+Pi157gSDs8CZrYVKrAnePRiVblo+aJ0RR/tt4fiSRC2jmhCcAszl3IJWesbC4OC06ev2Dc2d3MNUNerh8NSAH6Y+LKcs1dxd9K6+cnryxD4iMH4ZWfDnNqIdo9A5jYSvok7FRPrXZA/01aWDwaXctSZaFregNDug8wFGamcbrvy/taA2pGb1mXmpeh+m+mvizlIMRbR+8bAlhsZUBG5q1w==
*/