/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_process_name.hpp
 * \author Andrey Semashev
 * \date   29.07.2012
 *
 * The header contains implementation of a current process name attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The function returns the current process name
BOOST_LOG_API std::string get_process_name();

} // namespace aux

namespace attributes {

/*!
 * \brief A class of an attribute that holds the current process name
 */
class current_process_name :
    public constant< std::string >
{
    typedef constant< std::string > base_type;

public:
    /*!
     * Constructor. Initializes the attribute with the current process name.
     */
    current_process_name() : base_type(boost::log::aux::get_process_name()) {}
    /*!
     * Constructor for casting support
     */
    explicit current_process_name(cast_source const& source) :
        base_type(source)
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_

/* current_process_name.hpp
xL5HqNGpozMgt6xqMDTBuiBG2FJjkm5TtA/5moPw+jqQQoP9sekUHBU39mQ/bxi+YNewS0WRuxiFiOS8fsaGdgrE4qag0mK9LayDu/hJOoqbBvdpLNeTSyG707Pjc8cGYaqgnBDpVdNLsRboDeKW8h9zz4UlYdCgwP++Uvv6xLW1WUEZeVtku2JuDhyDJh1SAaEaN0skx2DgqfprPmJUrtdmLlmSMXjlIac6YRcrEApgUe8GynHR2TY7Jm4zbvYbIcafMptErNsTFkqWQfJ7zeUuQ6PK+5eNHZGfl7utQKAY/usjweLsSYHy387+Jp/LyfyHj5zNvu7mrTApw1gNNuUZxcDYh4vNQnX13MjC8v9/WJEtA84fWzNQ35qQfstPbqBPCNChs8H0hP5cxK7Wr/jIpn2NUJi9C27I1FWECqHWp/WlkH1DQWvLs7N16HkzaUS9KD8/BcR796Ktpx1yaWUKi+JjoMacm0UupLhgzZzk7jfPbczJratub52y5V7N8Te0inoryCSKllHX6qw7zI6IyCUyJgy0lFbMNh1L4thUk2Dpli96Q2saxg==
*/