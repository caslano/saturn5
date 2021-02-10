/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sinks/auto_newline_mode.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains definition of auto-newline modes.
 */

#ifndef BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_
#define BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! The enum lists automatic trailing newline modes
enum auto_newline_mode
{
    disabled_auto_newline,  //!< Do not insert automatic trailing newline characters
    always_insert,          //!< Always insert automatic trailing newline characters
    insert_if_missing       //!< Insert automatic trailing newline characters, if not present already
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

/* auto_newline_mode.hpp
KwW25MMwsr6zgqfG7NaYoqoJKrLGoxL0xJdiFGnpMBxz6eBiICCW97DPGdBcYYQO+VEuBQ6K18fZzZ8CsoMH+ZsCCXLxrpxH/P5QUJ29yOmPU16k3cackZko4HJmcCb/r9Jq5AKgwn7K3bA//hC6UZJEPDfKzaD6WgUebgunC1TLYuRauiJ2A0Jpm0QC3tkj6AoxDWf8ODqYUh7BpiUGsz4FdQ3UDvz0ni39aI5UBlMkCaJsdS+8RNQeR08fsaf4N+p4vPZ9pTBJG02s/JmyJ+s4CTZPcMFikJ5qtSxB2FF9FnzHVBMEBp8BPBbcBhHzFxmdVMXyzQBdjCI9FIAJDxNyjPdTJASWgEnI7I56xAaHjxB1MXy0OWY4oyVjEHV13pAC7/Dg+9OqCuCOH+zjkj1dA+XDBzUav2VP0yWQqXYrqnX1lAj+wDacls1HyGli0KDNFCXYU/gLmUkRzHlCmIZKr9f4X3xE4ElxWqWSRJfGI8Jcf6J6EUmbEh91CpjThwn0zx4VMlotzmeo4/CEEypnOc1nOFbak1Irgf2iTt8pttDrSHAIpPBRAsglSqMFveRYqfLMFb2SViIsN3+FZ420VcXfmCJDNia7wueFTdE942fkAVn9rXZWi84JwvKhci3hCuu3gB2FM6E6
*/