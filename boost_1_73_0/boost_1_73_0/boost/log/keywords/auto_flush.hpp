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
gtEPQhnoQVAtvx+bdLuSSwwiZdcgcwNGQqG5ByTpQSpDEdETAcHBvFgkQsfeTTToKgsHUoHmSUK2UE9w7cLmMCvh8UgMcoxYGHpomWlytY5l2hBEHMlKVKgMHSEOKBRKhNmDIgu5ssJ25ZWLElML8IOpuYk3BJlhMNAezmA8a8OCaaE9uBjPP56ez+FiOJ0OJ/NLOD2G4eSSjP02nrzH1At0poBvcsU1Olcg0jwRPCx9/rhr0HousiApQg5tI2Xia26KvB+3W63nIY9ExmE0Gf56MvKPzqcnn/yz6XgyP24NdilxIAsFcp1BrkRmok4XocwCKhoNDctUFhtntOktiJZUQjR1aybVS31LI+VpyBfFEocBA/jCee7KFcv3ZDibQyWJvrfRI8YTjHp0PP4E7QuGmc6Wb6C9nZ+czkfb+Yk0vD45mk5Pp9tZWgXNtrRhRgSwkiLEW4Erx4QXyF4fErlgyZHMIrGE3cA+vdZd2sAZbSCImYJdTHEkNk9JRam5T2TFfOwRJIq82/qK81r8xX0DaxGaGA6h89NrZBwMLuFZxznqdg9QTkSdZy683rsUC7ULX631Uh/FD+x3GaJRjU/Ktr8ooojjuJ2oD6Ffm28/XbGyMCh6itFZIed1hW65MIWlp0rHGAHa2UZe
*/