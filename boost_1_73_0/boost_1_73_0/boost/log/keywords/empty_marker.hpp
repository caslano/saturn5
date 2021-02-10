/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/empty_marker.hpp
 * \author Andrey Semashev
 * \date   15.03.2014
 *
 * The header contains the \c empty_marker keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_EMPTY_MARKER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_EMPTY_MARKER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing the marker for the empty list of scopes to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, empty_marker)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_EMPTY_MARKER_HPP_INCLUDED_

/* empty_marker.hpp
oeJvVxlvNIWJ+YhPPz96RCCiWDSG/8Gyy0ESMAHqot0fAyxoc8QdtmUw+8jAvPTZDThGEbIsyURQBezqXWf8zfExux71HiEUawI2H2fp8TGowxCoHKXQI0wrTC5B4JMQLhokp+FZFPx9668a/G2L7fPWp/st9pcmn6DCeD/D/wcroKDxVgwBX3+2LFw+JjB2UH+SPeSl4T8CktTgDPkktjOS8SA44DuSE0DIFaPvhHDDhsLVuQBigoAB0YEPQWmA7AYfZ8tb6o264NJMwd7/SELRn//PNs0ONSj+asVilJUAhHxRwAB6JvnJUEAlwosNI3IAZ34yx5nA10BecJtBdCOwyxhIvYH/oJgGLcsxY3chdDAFnNbQE3cIwUjzk3vxfhV+DNg/QG+DQztbwlxz5xY+65wfnb8/B4cLZGUq3WWAJHwyn40no2770utfMFTWQEUcjiQLPREDVSxCkx4vFl7GcCaQwoQF0Mvglchf15AD8MMbceHjYSfIZ37mTbcLzmkED/4CGfXXn45/PvkbcoiGBqijKMNn4HIgJxEQ/PsCRAG6xIDemVhJezNcFWBk7+FEkCFwMbzqDi6H5112zNcTTdULGP4miBo0DLaf7DfPsD2wIv8I2J9/94INrvt9i82fSR4n3AAYPZC4
*/