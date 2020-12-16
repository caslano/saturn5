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
z1WLeRHmlfBXgmugDVCse7tG8909mKesJF64eROzXvyegnlKEXmGWSHvlbx3472C3yuhAr3ra537Dm4Hvfd+rcVsNJjzU8IDrsZ9Pr+3Yj4RrIR28ns95qt/Gn4/WC1m6zBby+8doDOZ9AU38X4Au9yfEUbMRoPjwCl6j1gF71X8XgPV8n4P71msXg6HSqCV0HqoBtoFpaBRrxs0DiqDVkHroe3QXiiFs4i50HBoCrQYWgtthN6EDrr2nFcrgGZCq6Ft0H4oN7GpMxqaA1VD90DboMan8Wl8Gp/Gp/FpfBqfxqfxaXwan//W8+++/z94/1+Je/nfD3D334edHXPe/myf6m7UuGTqGeyMRwLn7XVTul6INmverIr4zkDiPmzf60cNPn+O3xF6+dkrIc8gdXQU9Ca8+RrW8A30nHdCydvcsvjOxOGH5SylfU+v8oqO2ylErpBw7SZ+acmcXm6RxDHmDPdHk+C5xD3YfQy5frcbHAhHierjyQQHi3/9nExC0hNyzybGexbdcgYs8lyhSb/VesjsaPVoCHS6u7BjTT+ODecXT50zozwy/YwezhXirr/9XI8nPa/N0nOs6rYVuFzsW1rTF7dmP/k14tacSTPurxeeZtZziN5vF7eRb6NjPOT2VnVrOYdoc1vudXuf2De16mhQt3HLuS3vSCs9JxrSuUsaWHVoED7MJW6qa0HNNMzee1KGNwnXE5sMvYcs1sTO+7klxZzBjPNMac0hxN0bzl2WcE5w9cHEDKeczHZDGlc4aw8xnGM1nKuSosO53j07HjucbgZOrVjIwcw403TvDxTW5RrIk9VRAfQ+YXUerSusvBfPKok3rPjl0buhdz/hPFhujhX7VGt5x60p77s6yHmK8vKF4eW9pfC0sJR327fL5833uM0V+0xbeTduXb0Uq5PwjwD9Q+pylA71SuuJQqmkdH9SWlFad1ftUkpEHW7qwmTxZ6zU3d8nv4Lln/BjJmlnyj9pgpmmiSn/yqtx9eb3utRQPZ+k9fwuwjzFmt+i3UDzW9oMa32fA54v7o+w5T9+2/TXhvKwDVgqPEfaZMC4z6bNlPaYjLsA+oS8eCKjfn3X8ek7JTwR+oa2iwDJPj5H9DaD43uQhva04mdU+hgdKZvETba/PyuVf4TQd0eYgn61NfE1ZuauND1fHrorTfQ0ut85J8fhmUv1FtKd8LK4TfJ3hvNBSO+h4pmKgpDQefumG0V3ggnHc4Fy4A/eXYK/5r61LHCn2H+GJplEeiOXGN2Hkx+TfDc6eHcL317Rwftxe9F8Q/hCOj9uEP4M8sgvcdmPm5B+h6nEMlRuEiSMbfSdW5LUrVse1yPH+9OoBzvDNxX9/v60Av4nJmWkp7ZPO4ny2NwfPMO9iwh8Cl8rMOzuLI1bK/H3EspI/+h4GV3CFTgL3QHQQewvco5TN9nGTR8p55P4Nn6LPrBqIvMzXvapLqE10PntA3QhmVZEen/m2sHbByGozAnw3AxVqr3LuygnIOvp9ej8mvFY/bp+XRkS3Sch2VJevRNL5QUzySPyEjPJy7B+49bmjjwn8cF08ATQLSNlj1vKiOqjsLQbRpdDlbgbghbUBOcMvrMPtNQp+B+lj8jowlwmdoN8+YS0CNoLRZQXk/f7hHczZx2axCwrRz/h8qQb3Q62MpINviR+fYhsJzu/IZSx5HqA+NfKyPXd8k4/B5lpoTqHvHLTk0jv4nv7kZHPjZyE5OitXMzkd3y6oO9+on59EW48PXLgbUP4vvYVqA+7ggPB591x4ZMx89wotrLkvdEpky/uP/K18E2x5Tn+R+qCmDZz6qx5UvdsILyDxb67P5hvveW9la1Nwa8o+TFt2Rg=
*/