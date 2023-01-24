/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ordering_window.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c ordering_window keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering window to sink frontends
BOOST_PARAMETER_KEYWORD(tag, ordering_window)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

/* ordering_window.hpp
I/7oWNHnLjDD+FdMTxhRGN+x0sRZ6zFrV0uX5FbRVqnzDNVsJ2R4ek6sWKzwajpvDjDtfVJ74nzsPNjJDJJ9i4DlwJJh0aIleWwnim1w1ol+ODBcHj6eAj8APkknAfmpXhnVH/rfbOMbSsfHcOlTqYCSz2e1zKA31oPaLfMGuFBonojY+YP9JXe6hvvbbI/gmcaZVpnebhLGWOlpIAC2udp51RCTBzguVWxmXeV1DH+oa1FcK72w4Nv5tbiNYTct1ocLiqtI5Buxa9rTLFVKSBeJINc4m4eujutXaisMn4TxllAUtn9ghxcs1nR3WJyol2dBmDPfRzP/6Z6ghzaX11cMxAmnqrrfugH1t8rFXpFo38HDpS/hVGyoYpjYaPHCuWLOlE9wvgCjNqOqFJCYvH8yFIAOpX3yr3x5lL4B+8NU3tU2okCzcvpE4Xi9+CPxcLqJvDXRRyTmAzjtKIh+HQoqfebYUtG+wf0jHB62ZqBGCfWXg0VTP9dq31kwIIGmWj/iwqCBNu5p8Pdb4O9wYigtGA7k3AnWqgLxjYLMaUG2IHZk4Ohjy5X+tfL1RRBffKLDLygXODn19urTs3N0FvzhgS9EFiq7erfQN1n5A05CBH/Fuz0A9fZbZ8Dh7/4KvdinlJo5/zdHxvLfc2T/8sR1LM3+3Rb/67YSUCPtIG7gjwIb+Zb7+gIH9YbPUd4F0qdZj9J5DoHTgplR
*/