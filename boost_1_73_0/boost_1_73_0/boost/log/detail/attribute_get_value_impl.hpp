/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_get_value_impl.hpp
 * \author Andrey Semashev
 * \date   04.08.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

inline attribute_value attribute::get_value() const
{
    return m_pImpl->get_value();
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

/* attribute_get_value_impl.hpp
vHjlER+a5f+y7UoR8X9rIqCGzEk8i9DsekTaxMf/+0hG7X6mtzdXS/5ENlVF+2OGxZyoNDGv2hgWfHnTNsDLGcrchzgV/YS8unqENfbQsG+/wktnCLPJOkJ5gMwUWZZuarqnF5V4AUMgXcPfMZGgd/Dm5LCLe5KWSIRXMADQUIwLZ2NeJgFnhZBPJwj8Ug8C4xGAuJyIMs8j8FV0qfY0gDfxn304GCOB0YotlyJkD/+vWYrPw1mZVTsx7oVlbinuDoCAsxsPgQ3jCB+WE4yORsogvMW5hBUMe5h819Wsaw5ygfXssbY56nffbVZAIxHYMXpBvreMCMVUVX/6cliAwjhIcN7342A2vz/4Z7nb+KT2rbiLN4QtPB7HWPfFCXcCLfvwUScdnYCXgo8qVzNWnRBFWM2kqmoc3Qbo01yPNLH1nK6Kk+K9DsNzVHbSfeNDb55FhRzXMq8cYgtxwIcaYF7vZMsAUEMEosYj+PNXyDsY98IBAMxy7/I5nS8aBHJ/iTFELhqcu+lFHs4ve1jNsjfhGG8CwkdrjYgQJfSG+e0UdFGUnsfpXNwcosaCNoHQtTHfCrc7aeGNnFZ9Amf36NXBEZjU+JBtt9fvvpw7lHMl1CR3/N2FLJ+btj0Ml7j9rirlTWcDmi1Y3qAP
*/