/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * The header contains implementation of a current process id attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_ID_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/process_id.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Process identifier type used by the library
typedef boost::log::aux::process::id process_id;

namespace attributes {

/*!
 * \brief A class of an attribute that holds the current process identifier
 */
class current_process_id :
    public constant< process_id >
{
    typedef constant< process_id > base_type;

public:
    /*!
     * Constructor. Initializes the attribute with the current process identifier.
     */
    current_process_id() : base_type(boost::log::aux::this_process::get_id()) {}
    /*!
     * Constructor for casting support
     */
    explicit current_process_id(cast_source const& source) :
        base_type(source)
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_ID_HPP_INCLUDED_

/* current_process_id.hpp
O5kAwIkzHO+g6F9Rbqpw9O8uU6c6HDF9PGbf3D3+Lp1tO6rH4zcvlEKN42I4ku4ZLnFeXha3lrGwNH6nrYDlQu1o6kGpdegPCz4D1S3YpKjdrJT7QHJBTEdqiKyii2PXiicUwQc22h7MDmMMfXMRY1VZF5yzwz7tf6ifJgvEFXSX7kbXVhTUPZ7wKozMrHSgUagNG0uetARMNDVqXIhWSiyYOFtIkjR8Dej/PYMwqccp2TiZum9D5LucQJGVzrH8EBIdnssMPV2SR3v//TKmZJh72o2k2U9wQFaNIpHm9TAXj66G25eDOeO6oIjUuA/U82S3XI97PiAZj1bdVVzEzYYrthNjCAxKPq0YI0LNnQ4OKJK/bjkNngkBcqggioRzr3ycMVoPBPhWv/NFI1H+j6YMalwD/JAju7A0piEKlG5fA+lXNFz5Z23JfJHXl6uGA4J/9DB5bNEGdfvAUG14Rz9dRwfq9NNdntSW2t3E7pNIsaOpvcAql0GSIqlkp76RYQqYggWORbLvYK8ZGfHAVjql+bKwEW/Dn7DU/qBMY2R3qkMtgStiNt5ixw==
*/