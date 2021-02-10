/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/max_files.hpp
 * \author Erich Keane
 * \date   29.12.2015
 *
 * The header contains the \c max_files keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_MAX_FILES_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_MAX_FILES_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to specify maximum total number of log files
BOOST_PARAMETER_KEYWORD(tag, max_files)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_MAX_FILES_HPP_INCLUDED_

/* max_files.hpp
ILW/8oIN/DMeWJExDkmnQh7eP+0+9ZifhKJbIJKTFe3IbeQnyhfb1QqZgzXCLGclThWuTvjy0Nua4c4l7SrMueMbxQjskJtX9JS0A8b7ybsD+ZDE96LmVi6KeI2ZLA1WWJMoEUWb8TMylGRZEszFwOzjMOIpfPRSqRpTOyiEdau94jO+pNRXFp/peREu/oQPVAt9UpVtakGgIXDdjWPACRC1FWVarpo1dJmYGIRa3MJDDj5tMMckPx2jrxDZhpeCMA1u7Yis8SJXxKX004RlEdyDNGs9vWqkTH3WiSOkoE57/ijPdtnTswjixQKJIZshXRyewXW0QssPSLsKZ2G2umfpksawcMSoyDeA3huPOaSWhA6qzhb15eq6EM16ZQavTmk9ahMgVKCbRiaDKnmvC3pBQKXDo4wpp1etAGCsG4wY0E4IUni71hO89nLe5pTkrGAaa2A1e2m2VuvBEGAWGOW+2Ttu9iS55oAi0zQRBXgtZnlrFhm1ox86Bzat6XqQyfhZ+12ag/lI7aEUUM6XoSRrAfdddHswygZNK1ekPcD898/6zNpMWljKDl4iLmuaHGJvCfKfI17y8dI2TCiMPsftZ6qDTlWkWS9KM6wDCa+2VvYSd8dVZSqpdalMM0fn0Exa4A/JONhGGWe8
*/