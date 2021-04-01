//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_PARSER_HPP
#define BOOST_BEAST_HTTP_IMPL_PARSER_HPP

#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace http {

template<bool isRequest, class Body, class Allocator>
parser<isRequest, Body, Allocator>::
parser()
    : rd_(m_.base(), m_.body())
{
}

template<bool isRequest, class Body, class Allocator>
template<class Arg1, class... ArgN, class>
parser<isRequest, Body, Allocator>::
parser(Arg1&& arg1, ArgN&&... argn)
    : m_(
        std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...)
    , rd_(m_.base(), m_.body())
{
    m_.clear();
}

template<bool isRequest, class Body, class Allocator>
template<class OtherBody, class... Args, class>
parser<isRequest, Body, Allocator>::
parser(
    parser<isRequest, OtherBody, Allocator>&& other,
    Args&&... args)
    : basic_parser<isRequest>(std::move(other))
    , m_(other.release(), std::forward<Args>(args)...)
    , rd_(m_.base(), m_.body())
{
    if(other.rd_inited_)
        BOOST_THROW_EXCEPTION(std::invalid_argument{
            "moved-from parser has a body"});
}

} // http
} // beast
} // boost

#endif

/* parser.hpp
T4OZbXYtITfysWCRBVU/Jdkm5u5SW7DOnmWInd4uFzaFR4ddsLFF5WUFCEelWm++1Cm7cc+BVKYw6yWsZWTijOWAmx/maHmz9FAQcrdXnmwpPga6E0JofM0IkrJ5WgFrbcIIsuqR7W+CFdUo9B6nubltCAeBy0THwL2D94Q7R+OXqlocimpqvCMi4Yd8kquCpuYWG0b4BMZFiwTBsAhuek90JUytTmQ3xHtZR5+Oq8gvVrBurRA9P4HAl2MShhpbWYM5UvqfLj5FJxngY8tyT7i3NCaueN4AFPuXF3SOcptTDTiouYAf/5IXXag+jiyzffxshriymdWaRjkovWMeHBnegg66585Scd+zOJf2uQmzMB0i4gQ3Na22WkWlTMOSa78f/R/fWD+6OHQNctGaNesUA1YHqLNpWe61j96B7Oo09LvhmORTlzKM1eZvtHHxjXDfAJn1K9s6fDP1QTQ54UH/cEPMa1MstC2vdengexTIkCVM71QVKfKl2FLoLjL0l0edufcm+xzB6kKTCHUMube9TRM2avbtmeGzUSAXEgT5zsmwNSzvvkxutw==
*/