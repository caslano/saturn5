/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   predicates.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header includes all template expression predicates.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/expressions/predicates/has_attr.hpp>
#include <boost/log/expressions/predicates/begins_with.hpp>
#include <boost/log/expressions/predicates/ends_with.hpp>
#include <boost/log/expressions/predicates/contains.hpp>
#include <boost/log/expressions/predicates/matches.hpp>
#include <boost/log/expressions/predicates/is_in_range.hpp>

#include <boost/log/expressions/predicates/is_debugger_present.hpp>
#include <boost/log/expressions/predicates/channel_severity_filter.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_HPP_INCLUDED_

/* predicates.hpp
J0ZarxF5fcQHZq9pGccW/fWx/N3N8Xcvx999HX93Cfwt44pNcBySpX9PRXrr30m4E71bM9ch8ylyjyw0e2jXqL7oKpgMa2EXWAcHwAb4rrjTMX6du2hy7put+rMeOBhmwiEwGw6FQ/T8OD2/QN19FZ4AvwbzYBPMhRv1XOOvY9nkhUv8r1H75BtgCrxW4/912Ader/Fv9o/7wuc1nC7IDsRS/fE4+CsN55ewo57n6fqKAvgEnAx/DafrOosz4NOwGO6BJfBZWAf3wvPhc3ANfB5eAn8PN+m6i1vhS/B++Cp8WNdfPKPrL56Dr2s6Gi0dT4WnaTo6IvWajrO1PM+BGXAJzIQlmo6lcDhcqekpg+NgOZwAz4NzYSWcr+4WwAq4SM4D9uubNB6jkKYQ+/WJWh/aw2SYBLNgMuwDO8CR0KvlPNo/9gczNbwEJFfD64I7aTOwI+wGu8FM9Z9nxtp4pvgPtmN/jPpPhYmws/HHNfWX5OLvWPXXA7aHPdXfFiRb/f1c/XXW+Tz99pH0vwO76TqYY2GL5v/f4UgYR3ij4UFd7/A+XAg/gJXwQ1gFP4broIX77TbgDvV/H/yHrr/5DO7S67oOSsdhKFukKWQd1Ela3+doe5mn7f4UrRfz4Xh4KpwDF2l9WAzL4emwAp5h6qeOG8CvuNTPCzRfLtR6uQb2gBfDYfASrZfr4Qi4Fs6Cl+nzL9fnroMV6u5ceBW8UM61XP3f2zDDpVynaL8xFabDaY56vUT9DXOp12Ml/oH9HcZrOk6Ex8EibWcTNbyd5juROqHhZSDbNLzNqqe/FXaHd8Be8GHYF34XFsK7YBH8gbbLbXA5/CE8D26HNeqvFv4Y1sMdmi/3wUv1/lq4E94AH4SPw4fg67AZvq3ujJ79uMj704916tlH6a4lSndWYXTuUg/nTvXx+41BHxxZgdyMPIl8iuShg38WshFx6upvQwI6+k7dfHed/M3jAnr5O20ZF9DL3z3Op5ufi+zj7xmwBWYUoreMTEGcOvkLC506+a7690b3fhd8C/GOD+jf9+DvQtG9h/zdAmfDsxBb974e+vTvIeLQvze6929xvhEWFsRbh8YH6+DnIoXIEkT17/269/gP6N5v5+9S2Az3Iy1I9oTIOvf1MBe2PJxsbZhgdO6Nvr31SDI69/jl3jbEr3M/mzju5tzWuT8Ie8BcZDZSivj3ra8vCtbD32h08YP171+ww0F2LAzWu0+Y6K57n831PMSpg180MaCDX2n/TdwDuvhwYqguPhR9/IAufqPq4BcgPbiWixQhC5HD6eKv5++bkZ3Ibode/r5JcLHo5Btd/A1IqA7+FLgY2c3fryM1/N2INCFbEOt0rvOs5smid2907vdMDujc75/s07kvIN0LkUZkG7IHaUG8v0i2cpHZSA2yHtmO7EU+RfoxGTcDWYGsQ7YizY/G9PFjR+yIHbEjdsSO2BE7Ykfs+Lfp/zOTezT0/7PY/z9jpAykMEZjW+Srry22p/Dq66xe3GtmTHtJd8e9WmJUXaV7As/uPID7ft3HJbp2IN8K6EVszWB8xLd2YOr8+T6dA19IRINQ/PPhyYSwNtWW1nWf/XNRjZ7IczPucwyR5wbOlDmkQS1denQefOegaRdUfdR0dccrIs8xuM+dRJ5bcp+LijQndPTm0to6l9PWOScdt9Mypuz13Izb6fimzVNgGpwPe8IFMBcugsPgaTCP9NU8xRjEU8lRjwk1IsH2GcJtM+Qi/rGfGtiEOMd53Md4gm0r7EEYz5FxnA0Rxm42Is7xmkLEMUZjxmdKkcONx+QioWMwLyA67qI2DlzsG7iPqeh4SnQ2DFzsF7jaLtCxEh0nidJGQRQ=
*/