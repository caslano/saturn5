/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keyword_fwd.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header contains attribute keyword forward declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

template< typename >
struct actor;

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * \brief This class implements an expression template keyword
 */
template< typename DescriptorT, template< typename > class ActorT = phoenix::actor >
struct attribute_keyword;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

/* keyword_fwd.hpp
uTR5JWq+4AgiHMh/e/c0tkuh8S6yY7bku/1YYIDkPfwgmhFb8ZcldT5IohMSiG8g+YHbOwiJYLc4ynLCNfP/3Uk/y6LZiALLfwUFXkFr8QMMPudBYwU9MobksyOzXn9dmW0vCVjEnXaAWY5BgPv9oIpLIyw5gHdyPTCwy1cLMCdu5abDz33GpOCwHhn3DFPA7FWaJ1PERbah9MgNzJg2gUa9McHHDcgLs+sclV3/Fb65fQfxULWxbjqShs8UPacqQX5AgNNtIyDswMJYfQlv6mgZ6YaOa/Agi2+hivHKSjZLVgBYITdrHxov+VcP6rR5jC1PE7bH7ufesgdwuvoa29lEyIW3c/47Iqd8STWwcu9LjfONt/Z9mWrPsuj9LPyWK9hgemIe2JzPMvQsPquvb1UDUJzfNmMsE+La3DHuSVDycwhvu+tYpo21W35pEGJcfPTj/sm9fEYlOCpST+yFcRYfnI8WBMNvnlModUJcq3MDzMJTaVObvH9lGsIcVBz4FiNPef9/KG2S3TtrKOo12a1OcrSrdNkKEvYzigyVzKiG1N/7l29QLZcDrA==
*/