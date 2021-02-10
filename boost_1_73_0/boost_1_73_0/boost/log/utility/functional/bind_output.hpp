/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_output.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that puts the received value to the bound stream.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
struct output_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << val;
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< output_fun, StreamT& > bind_output(StreamT& strm)
{
    return binder1st< output_fun, StreamT& >(output_fun(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_

/* bind_output.hpp
PdV5t8a3rx1teKkY/HF0svgmjfp8P/Rj/fAA42/hf0UtWWwMi1rOnahpgz8hziYfIkIlhoTN/2tmRDzERRaQCW8HgEzxWsRX9X/V/TapCy6fnCB6wK+2G9JhFxioxfCGlUiZSE+ySJW+qA9kuO+mY0326ThWeHYtCTnCfT7EUc3EvVenq/baevpSFicjM0vcqswc252ixSfESqpnxDc95JW69bXmPGaLfDJVN+O6ydMojZibH49IP8qQVvdjPlfdumxE5190VjCqfLsaf2xy23ehJW88E2Wsbagf7cXvlJAbIjDlegPzaP8+lIcVLqEwkQwzi9xbZN9yhxXNrUi+IFDeWQPbnzohMhyn2OOV49Jr7I52KHUsjJ3NaDGZzZT1hCz00Hz8tOhIV9umoZzvxIfu2DU5bZcGfKFQP3q7QUvrvS/ADWNAGMao31eL8L5G0EL7YCg4KoFUtuKD/OUQs6V0+x2tEjhQqnsOe5mDwgz0QlXa6rCi5yf1Ct9o86VdDieYNqyAmoMuKKw9GJ31ui2gVEFDGxoV/XV1+LnbUk185VgVit5rqdUEOBTX+GoMs9XF14mAJ+hr6FTyL4AbxuDupa/BSN7zsBEJXxpRjSSK2xUIRk8/eSdErmIHcOhVYRumV6KtEV2igC8O
*/