/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/use_impl.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c use_impl keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_USE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_USE_IMPL_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the type of backend implementation to use
BOOST_PARAMETER_KEYWORD(tag, use_impl)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_USE_IMPL_HPP_INCLUDED_

/* use_impl.hpp
V6C6ETsWvXOv0+687TqcnhyvsslP/Lt6005Vv+SiOu/KIks1w4/UWtVoKmnunuO/FFS12meP4o9BsPFXMDH1BoGX9Lzrdq/a/d5723Ex6z4iTNrm3MNE75qZTRJ871wPIylYNXOvFJTB5H1/Fxj9plL5W826QBYxypjn5FkpU2e4Oqarj3Ut9wkuwtf9d/xCCicUd5Bj7YcrXv2opny5bPf6VPFIr9UnYVT0kczKKkq7gpTUy6hzNbF6IShOYv748+GnOgJfQUZTvz/8gAXEDcev0B9P0MGKO6m74pgxo58qrN9NErhpUBLaAH+pkPlmmk4gNMWljm7aUhZ10W6aDDvDvhYOI0ildRkyzKUCb/fhXYmqeyUdcqil2+pRBn2Bl51u4jTEqLS+xvHUCXSFl5MBbSlX/DF7051geBe1T/dyODHvl1nOk9kUM6exTBFYKt6Mh4/pnkPXJbf124rs/UeOz/HKX7x6Fv45c73H2pz4Af3r/CLI/BsvxT3DF0z97vySh7zUTbnObzh5tbuwdi4YXgDUCoLxkqJmFKwaQNnNaXmuTIoXgFvKW5jjVNOw7HoTpwApRBok/FJuo5sIYBWUIGCHlnYhIG9EmOjlovJenF4HDbPgjm53Vc6Y9Md0QcR4dGXqU12hrFIy
*/