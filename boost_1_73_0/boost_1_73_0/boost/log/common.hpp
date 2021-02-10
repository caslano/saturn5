/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * This header includes other Boost.Log headers that are commonly used in logging applications.
 * Note that the header does not include any headers required to setup the library, as usually
 * they aren't needed in more than one translation unit of the application.
 */

#ifndef BOOST_LOG_COMMON_HPP_INCLUDED_
#define BOOST_LOG_COMMON_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/core.hpp>

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/exception_handler_feature.hpp>

#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_COMMON_HPP_INCLUDED_

/* common.hpp
xmKVWZXNf+vYbjq6B5Aair8YN+kgpG94CWRnJkU2W/Qr0BDlDx3FbGHAiF0fC2ddQVdhGiw6V3dqiEdoTit0tWVOSNr01EddIzpuNLTav2G4N83uBT0XWZo8wD+R9LyJYXWWTuJbdzSESWGReo+7WFyCWU7E5+XbtIW4FDw5/JtmgeOKhHDG1ZykdUJGjtADkwO+eHN1Pjz79vpmsBjQCleAxG7NeTlkdywxt5I5xhi3rtKllHeqrgKeD1YTzrpeEDuZQJDapfgYo8ZIfoTCasgUCpX3cRVNOwoY0RurdaLf6/2A9bkTjoBpXlzjgs6MANTdqTesd/WycZj1hWaQUhHV0USFLhsQJLHh/OxqgD9UuvZkQY1Q+IiCRMyu6CRZCjKkoe8yFuypQTEI135vENSMyPJZEVuX58/VCk+3lgzGPOgDWflBEaZlElIVWlChLoUMklhSYQ0PmjJIH5J4hOy2D9g4qrKAyYGRn8fYkQs62C528He3KRNem4OThNXdv5Nw17Nt05/c1g79a3XKgQZRAH1xHjaUGdxM3S2y8cS1tfIqVQGtK4w/ZZmAIdZoKLwMPsNwPMa2jjOIh2GrDby8BdcLBVr3F2ZzVjOzYYieRemZiunsKNIav6p2UkPEEADR1uvHVIWJWwu4
*/