/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   nop.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that does nothing.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_NOP_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_NOP_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that does nothing
struct nop
{
    typedef void result_type;

    void operator() () const BOOST_NOEXCEPT {}

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template< typename... ArgsT >
    void operator() (ArgsT const&...) const BOOST_NOEXCEPT {}
#else
    template< typename T >
    void operator() (T const&) const BOOST_NOEXCEPT {}
    template< typename T1, typename T2 >
    void operator() (T1 const&, T2 const&) const BOOST_NOEXCEPT {}
    template< typename T1, typename T2, typename T3 >
    void operator() (T1 const&, T2 const&, T3 const&) const BOOST_NOEXCEPT {}
#endif
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_NOP_HPP_INCLUDED_

/* nop.hpp
FWS6r/ngmypG60O3vF/0lOAvOVnSfWvgJfzd3/0ugXa+8wj+3g3XrIGh+L6GPc7gbz74bhHWvmCepDuntgl/V9l5R5u0D59bS8GSrN1LKIMyp4bUfN6MYxRoMw0vivgf2sDtPsJFk/sIAc01m6AXSVLNZ9v1ctt5GMsN08utdpca19p6DJHO8O0c5kPFkP4ANouolst8B7ciDM9Dd8N8s83OQzM5NuBp91JAVEJSVpah70B+c9+pD3QU/h5r6Btxzdm/TwJ29oDn/eBMWwIwWdl6hNHeSKjezprOYtsN82QCWNsN53s4YtsVzM1J0eMvzVffxXx1jPd0DNohW+fnV/H3ruzZJoW2cD571Hhe2Q1n4dnHv6EsSQpvJu59XGGN9AX86MWoc48wqolWP9wi1NetF7NTNOb50BYLfXEWpAWSr/QQaLMHJL0H9Cak25BUmyIF27yke2zexvtITWq/txjVpPZ7i5DXcG8xiI1RX+LvfeBZxTYOBV6bpvidRMP9R/ey2ZiG7REMdBz+ftE22VkSpMWQ1kHaC+kdSF9D+hGSt80mhUBqbFOI7Xsx209AWb+1jYZap0C7FoEFVoHtt0MvfBPodUjfQVJsHtC+DqketK+f1l9QlNZnPkdZdaQgVsc8fI4Gz3KwPDYpE+vtydqBP3to4+micBhTDc7KB5jsvVY0ddt7Zc9Bzr3XpnzvtbN2lyRe43XqyXmjXbx7OW+Qi9ed81q4eF0578cmGq8L51118bRyLzahd1hebiLeYcnRnrvic6ZL/3/53jHvlwpb6mazcSeLjTtXwrV+aTpef455ZpqN10yGDcoaFfgZKHvBu9q+qpfNN9ouq3a7r8Ouejh82/q29B1ilz2C7HbVUddozDUdw3/GMoYbjuE+bG2A34X7VefB/87edYBHUW3h2dkkhGxCCkkIIWAkVOmhCVKCFFFaKKLUEELokBgCig8V1KeoiLHwVLoKiAiKAooIih0VFVQUFRWfXVEigqIP8f1z9r+zO5nZsAH0FXf5Dn/uuWXu3Dbl/OeO1W8mK5r7OPKa+SjfFY5KV20kr7Nt70PVPMiXdOu0BgH20ZJy7O+3zfV5t8Rn2dcpyRv8+26m9fNXmWAe4y6Ja+cXN9G8x7pC4rpoUawfZrbZxv+QuBq2NUGNkQKJb6jV1CrJ/m2RGG9v42XAHGMcuPt6unuaehrj31meuvIvA+PCg2OU4fPbfAlU/78k5fe0r0lcKzdL/MW+/eCkzBOvL6frnf/kGG+hSzm/lkC+Nu6J6qmxI3vqBXznv1bSpTuNGylD9X1tKd/wap1mHye+tLZ5lMx+6iLx87TGMsNxzUBbRUC/CnW6OkPmIP5Wc7LCvkwT/NuvtrSV1NXSVtFVvAXEsqAqyj5irkViHrG1laM9JMPqO3dNxoltmvY6W/vy7Fhn37R0cx0Q00hwdpH08v3S6qQH8EuTvOX7pXVLD+yXVi/d6pd27Wn2S1Nt9TZLnMC2Gs81s+QM1VZiXrHc7yVwzi6QNHlaD+frCsoI6Jcm57hV4lshXMXefiq/3QZjttEDEl/Vvoba8tp91x+V+O4YG7p9TeSatVzSDMJq69ZO5LcU7fdscbpsPYu5Gc5a+hA8SFvP+lqqb0xTj6V/1FqxRdLlaRniWebYRygreBvQ+lrB24Csae3tX1PatpPW1pJmtDxcq+txIvvoHC3Cdl+cyj56So6zGP2hI6WO541wLRV9FS7P/IZIn8m96jdJ5fWbzCG5nxsix9Xyp445NRuV6sesqs7r5XbveokneLVkBrdmbj+Na+Zf1Y42Uuxok9/Pmd9v2cGGxbuj9dVf3xIVsqN9EoTPWxoH1lX0eZsHmcM=
*/