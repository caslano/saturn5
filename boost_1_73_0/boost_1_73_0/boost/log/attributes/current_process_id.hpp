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
wZIxBd8mNKeJ98P64E81eNTNbbR9tUauaGGXrUl4084jHwJPCxSR1jTPbm7b3im1aZpxmpJxw8lHRQZuAvhMeS1r7SX4E03oNSiT+PzqiV8gzVFcY4saJe5vcYMtLnOvQM5v4SHI10L8oHLGRqtSh8Kqv4qzWaEZOdD5L9j5RcgnAv5bZsMssaZaZ+utnGiUiyL+0x6zS/6f5s6V27rBxvAb34kcOC+8NlhssmgnQnNN7ER5ucROBMALd6L/It03YVn65c0e5+ehXMRF4bXl6sYpmqyCgQpTOgyRFJrSAnyjiH21ubO1uSWp4lhqMMzDQhjS6FqOkjDEqeh+Q0kT2M7E6Gtw0ARlCvdAjnAaeu0KmyNkqxXZ8LL4snbJGrL1OVle5XAKszuKkvB2gWL7PKqUjnefsuHHFbx3X7DhybYAfy13KKkbwU+qRRutVPB2ZsbWbGO4qOBrR2xiiKsWuG7RBjYauS0uNdXs251tmiZynsGFy2aps3BdDGmFwbt/2hiyyp5y6PfB074an6fgciFbS1iw7SRKzyUeG15tqMVlzMUVPJ96Lfh5LuEnEWgLvyVljpg2yCQbhkl7mnl0m9uiVKvBr/jdFv2qRdjID/l8pmYuKdFDKOMr4HBG/gL24La40rQWbPZ/2GNf
*/