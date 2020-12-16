/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/severity.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c severity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass severity level to the severity logger methods
BOOST_PARAMETER_KEYWORD(tag, severity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

/* severity.hpp
dwTlRWMeLDDgtaT4RlhhiTeB8vKdla40eXdQfOeznJSx4N1KvNNVugng3Ufx1VjpEu8lyl+KVX8iGbyxFHaxFVaavJNJ7gdhhTV5GuX5CBVfGnhvUhqdlG6cAV5bCnuTaiOT9yrJHWrJEa8FtVtvj1UH2eAVUtgyVTaTN4XC9rJ4og14B1O9xKrytgNvE4XN9Fp11QG8Y8LC5oFXWRJSz9Lk3U/xLZNWnruAt4Xi+9ZqI93kDaQ6iCObci88B+2v1aIj69q30O/huvhOYpPWX98qyo2nxMGeBP1Y/zvaGTFbxZWxD4kT4wyZzrbi1fQu+CWuAF8G92ArRVn0NL2Qx9TPKa6qJkPENXJfLV0cozXXvjKmyFO8rcUWb2ttWNSHoiY6S9wR3VzLicvU9mHb5BiKc3V8sZirxxtD5FrPB+Ipb1u5j7+5WOEfpg+Obac52QnWd6H3mLJjNysL2PBM2Z/IZjxZ2ZGD4+ux/P4O0E+U52SvLrZ7smzj6j3dTP7mmAFimL5SP984E/ng9wNRN2qDl9SYaMCN72nyhviTeGxKY/41FNeFUUPlV167LXIc8Qf740Vnf7ptPJ5D8dT6O4urYXcs4fcc3yFSGhwTUpiXR/Kn+w8UO3yULvP1blZ+CuGCY3sL6hctQ8bzU7uFvq+bMv8F6pOn+ftiVx+NF8yPozQr/a3FOtlEK1DjVgLcKb2D43Yy8w6h+H/Be3uhymMC3FKK5wr/8fIxVTfJcBtJfrQ/U7TxUz6ZfxPJH+nPEHsRP5X5bUj+VH8/8TPiD9pOR5L8xf4jxOfET2Z+D5I/AnG0V21lumbEH+/fS2SEzCPWh9aPmkecQfGv9ncSSSqeDLjPqU+XowdDnustG+5E4k/0txfNlXw23Goa13v6o0WaKm8buHmh6arx+kJKt0lUvkwIGas7kfzbsT5xmXGjsUQ/0H+aYR9nfeSvq/lHEVxv4l3vnyDe9Flp94I7j/gT/Lmihd96T5nj3VAqw9fWu5V4a6nNp6l312bwDu1B4a13F/GKSe5NjcOKreBFU3yfqHecyVtMcn1UfNvBm93X5O1nhSXeNZRGnRVWN3mfBN4negqn+zN47UmuY+ztxiLrvU78tygdi4eDsOb7lWRnafYx9RWKc7kaAw3wNOK10uzjbB+K7z41Jpi8tyjf86z4aJy9ndJYEDKm1lHYAis+8BAfpfFOyJg6h8L2UOOJySvdn+bwknk0zh4XKLNK1+R1I7nz1Phu8tL3ozFVzRcSwGvbI2RclDRG97XH14fG6E2U5+elfTzeSnLxVrrEW0HxfWjJ6SavK6Xb3uKJNPC8VN4NKt0M8F6iNPpb8RFvIMmdETL23kBpnK3GRZN3Hsm9pfLXBrxDiOdX/agdeB6ql6FqzDd5t5PcKKuNaIweTrzmKt088Bb1pjxbdUq8h6gOdqo67QJeFfE+Ve1h8j6isCdL09adLBtm61b3eXXidUj7PUJh65Wxal2TdVLwetls3/G8TvkTnhGXsoUfLSPtg278PuLG7l8e8aAEf8fhV9V+t2JtZXHU2xPOajbk18bb2p1t+ZH3WTvvZ4+8f9x5n3vj933Tfe4a2wLYzjEHOAruSy24P7o3sC2wCtgOOJ3voKgF5gNPYZt8E0RSCCwAFgHPYhv8MrbBbwL2BHrYBt8bWAwcBtwPuAhYArwR2BfYS4fNCDge2A94PNveVwEPAD4DPBAYg/L1B2YBBwDHAg8CHgs8GHgdcBBwJXAw0IP+cghwIPAwYBVwKHAVcBjQgzo+AlgAHA6sBI4AzgWOBN4KHAVcBzwKKNEeo4E5wLGmHLAcuAQ4DrgeWAHcCqwE5qB/VAHLgOOBC4ATgBc=
*/