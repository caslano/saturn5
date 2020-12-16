/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   expressions/formatters/auto_newline.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains implementation of formatter for inserting a newline, unless there is already one inserted.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/manipulators/auto_newline.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Formatter for inserting a newline character, unless the last character
 * inserted into the stream is already a newline.
 */
using boost::log::auto_newline;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

/* auto_newline.hpp
vmM6H5J4YZOzq+88XsJnHUROcBkvSVT7GR7iDQdCex1Ntrhf6y+Dirq6strVFcvsaEh9zZL6usLMq14u7ndjF+c4ayT3e9n3E5aE+R84duySfP4pDg/Z2AEtlLAmYGenh5TFKqknqhuibp4VN2lmX4O/y3l3K40sPsjc9StyfhFzO70kjD6SSqnjJox3xU2iafM/kfN0ozegNkM5VlaXWoH4nSzueqCD0V7K2uvaFj2Xp0lejVWbxXHoJHklXwYxCRJvueSAxC1Fnt1HY2uX3XQtu4Oplpyfpucf6vlFep490nd+o5731fOter4nw3f+Ssj9hFzfeX89P0HPX0kNriu71Da5PX2SpUzgzvbcoLpSt6L6/PKS+pJKnDjb38r6Es517n/icbafM51tVsPxmP66g8n/FaaM9oqbS4yux2XH2+dJ8pwzpNXxHMd8/1nynNs8AzxZ2u/6/bQXPwOkHouSgK/c/0G5++uLzqdLneK6V8Jq8uSzS7T0ES51qpu4ceoIcL84z+hgzZf72zxvMJuVR5xC09HB+KswdfsS8dNF0pTO+Q1yXuE5w7pb3Xisb8i1OM5xw19/k/NM/Jg8nLoadZLZ1ctNXo6SZ444TF7WrKxbHkj/TLm/gPm+rmKftjSROWYKajh9irdguNWVaxdwvhf5c2/q+PBENm/JNX3j2FRL4vM5ZNZzflkdu5048s6Xvylig9YW/zMymEYosJ8xZO0E+9o+wk/l2phU3zVH+Mav/9oI/EkbjQvTs3Bro8TFK3V9h6TVMueb9TyNvvqPEk+Lvjp/pKXXXgpcG+G/tjdwrcB/7enAteH+a48HruX7rqX4+3ltNdovUAbUV6mtnEuZ9NFamqbnlJuWmq8tP6ltuTjHd/57Pc/Vtp4oz+bdscB3PlzPT9D7tXr+vvYdqZoPcZ21r9DzYer+bD0foeeler4w13e+Rs9Hc9+5X9KUFLMXg7Fn+hlp2XKC7b65GF3CZSWVrOUsragurmFBZ315cbUYHa87nN3RSQQua0v7wpuv9PW7Pm8LMEzN72rIO0l2x/B1pYOI63aJR2Px6roq39NVD/WRHIvrxZMayst5y3V/L8Wv0QX8KNXhfnJ1Q1W9+/up+pFnDPH5mVZdu7Kk3lV3MNh9TYK4n1i7fHZFHR7cdAfVvbTZGeT9eq+0WVofbTZlQNRt9nkJxyvtrhX7r+a9xs6zLibPAvpw5I1eN3lj7LkPkXsmD4wuHGnlukmr1LE9J5g6bcrWaZ+fy3IMRyZy0hJatsWVUZdtyxco25Y2lq3T/Sc+97NpDbz+uZdtSyt1IcPhPiPg/rDlnJkn5RyoF1HY+/1XlPcncl3Tr9czItSDtDz3epDQObyND6GNF+WZenC+v5Gnyftn6/VA/Jq91KKrB/gx+X5GFPWgKK9tbRz3po3nUvcruTgmte1tvDyv7W2cPHMtc/ImYpmf0YY2viTP/A4F7e2Tmh7exv9BII1hZUsj1z78UGrr5duY1/Z2rn7kGR9HUb6NeW1r5415bWvnjXmtt/O7jqCdH0ptezv/+Ci089tMXQjovq6Pi2zD2932dmQb2z072NfPvWDZPb1XvJbQMGr6D69a9OJK2oVcv/udH50945HvXut577OT06/fgiHPe+R66vDvjh9ZlbjshV/c/+c7f/DTbeigik5s599ds8L6ZFq35xc9c9qYye/OPHq6rO46upFsWke24b0+2b7+tScLLx30t8q7n7pj9tzMtbufjWzb2103NbJOr7sN8rbb9na3DR9ZR9fd1nskHemjZxfjg0B/JP1vM+yb4Hvfuou/K9vJN5T8fVk7+dYRN1W4eRfO84856nhpE9IemaJhzlI=
*/