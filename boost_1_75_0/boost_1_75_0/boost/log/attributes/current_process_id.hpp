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
gFYlHKa0xwB+abg3LDkp8uZh8awqqeY0Y18IpUc2fvpYp3N+0RabLTjm+fxkGkWt/6yG9jfp42UYXKb/z/k/x3+VPv9/Qv58Mp4eHkDnf3M/0MVoQVvy7nDFNMmp3wv5gCR+0Gz2qiHiuIxqpB8RbXDs19hpbWaXVIROR87VLhKNxvAGfrP8Q8Ur1+qI8MPS0u++HpUOjPekI1L85qxSUXwYtKUebzILgh+iNJQINKmSbR7y/GH+HQZ11jVDHyIOxd3XO+Cd7lCRu1V3eBv87LkfXPc0zwNpeoBXFOcWsyM+wKSa5ATMizjjMQlvkOYSYO+hB/oMlOZulNRfzb9ON0i16jt2HHzT82IDb0Npg/1vv75sWAqCXO3RTy/4rukz6Nfc8i2CWQ5Ji9+duWZzGOORc1GXD+Rd0VDwCNUmX3vPHndbrM9LTtA/O29RF1J5OhQVzk0ylNhRmX1eKzPv19YjzUhliVBP5C4E0du//GtfdBGASTOp1cV2/V2TpEshgLag5K6ttZpJ9Tx3Q+SH1lOYVB7NU1k7/DERax2P2xDU/wRH6z66Rc1WLJmxnG8N87xI4OzFjh+drMOoyX79tHYX6p9eZnpu0MfbpPX0Y1YMIUm9uOLdd9cOr5HqABrCJR/utK36X3Sg4skOJFV39rQVUDqo2BD/X8e/RhpJPhagOJx8lefo2aehDzmyIe4ij/XJN+DHTvLWBK1n
*/