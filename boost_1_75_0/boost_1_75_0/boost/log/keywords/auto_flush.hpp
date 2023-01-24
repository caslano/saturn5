/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/auto_flush.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c auto_flush keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_AUTO_FLUSH_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_AUTO_FLUSH_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing auto flush flag to a sink backend initialization
BOOST_PARAMETER_KEYWORD(tag, auto_flush)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_AUTO_FLUSH_HPP_INCLUDED_

/* auto_flush.hpp
mgV+sKZDEnn5MEGwgKHpR0mEHl9KSv2FVdEm+Dr4yx2lmrIx4jGyp5S06uts5YrUU2rzxVJxiS+pOmI1H2oJYvIQuuEoaUuPS2idA6TMd0yqKa2f21t4dLkFLryqxi9QqwmViWVLa9+L9pVD3bhqWxH4VozQEMmeE3jRJ82XqpRSseTSw1Rtv6tnbjd//7r1NL4Zb0aexNm4Qc1U/KgMJY17qR3/IubMT5Q8HWOfdomN77P6avqLmzGnF7I6Nohp+MOx5bihMfb1Dx/XrfOVjfw5p9RZRa/uZshxmAlLPnYVPBOMbIc83TpAxOTblxdV7DpGo1yYNOXHlclZa0/pPU/W4tSNN7lFwD2n/daXolfk7apAtKoxBLa/3kyUb07SSH+oTb/ycRiIl1NipuqeeVbJbxCCZTddfVuND3lWluDoyvtIy8fQmjLdd9KLRFRIo5WZHLzCAEOs3a1knkx19QrHiadkY++s/ZHOQs1O3ccqvUSpyrmstPcliXpK9WfmLI9lwKyxZdS4puKQOkly9ZcrotsyZm019GdtQUm/NyUJzMTnbBx+MrRDrBZsYhnZPzpM5ESXw+pxDGsJ3Q5HTV3YzRy8TA+g/SW+WItJ39s557crRmVx5kPwfUbABuaq6qSLGcY+6b38fwbfog/sbb5hbVWMM5vwo42ZcZp+rsGVkO76oHa2kwx/FmaRUOM2NXpi6YhAXvt8y/qE
*/