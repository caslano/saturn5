/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/registration.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c registration keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source registration mode to a sink backend
BOOST_PARAMETER_KEYWORD(tag, registration)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_

/* registration.hpp
wncK2AwuBGdKfY8D7wJPkPqdBH4k/lOfgaeAvajXbLA/OAfcHDwNHAaeAU4AzwIngWeDh4LngJXgudLO7/XzGm0XvWVCa21+pS7wAuln82U8XST95z5woPifDRH/s+ESvxW4ABwNXgYWggtlvF0h/ecqcAq4CCwTP7Np4LVgDXg9OAO8UcbfraLXxeA14O3gjeAd4G3gXeBD4N3gY+A94LNSH/XuDr4k11+Be/mfm8Atpf09ofHS/tdEz6+DG4NvgJuC7WAK+B44VF135dcm+R1qyG8IfHHgFiLPYWAWOBzMB7cWeYwEy2EcOg6fHWg6tABaAf0M5eJPVQrNh8TfSvysOn2qMiEP1AL5/KYWgn6/qaU+4noVuBxcDfn8ozrA/uPx3YCKIA9xrVAJf1dB7fw9F1wALYPWQMk7cV1MeeB4aF+oFPJC86CboABfJnA++D3o813KgcZD5dAa4lvAJZDPL6kNbIc6oKxdlO+RPjvEC+aA88BisBVayN+LoeXQOiihkHpBOdC+UNFMzpkAvdAcaD50HbQMWgWt82EJ8oUSdg31/8kiLhdaLj5Ahbt2+v/Ugi2Q3+dnGbhK+ft0+fqkQ3lQJtc5UCFUAvn9eeaCC6Cl0HJoNZQovjp2/5wiaArkgVqgVmgR1Ab5fG1Wgu0+Hto6E5oPLYFWQeuglFn42EBFUPmsmE9LLMRCLMRCLMRCLKw/JED1f7r9v8xTV+2d3l0+ACdlW3rddVZc6JnF8ZkWvumd664pv8x37K7f7vnZoLB2T9IF2+1Ibd6DCN5gGx28TnacoLyPSPfx11ER81niwqu//Z4cxVnitNHB1kb9Qmxtus56PTV1I17VLWBvn5T4kO/d6uWyMFTWZTWddriIZF5olItZ5sKr/QtGcMMz6I/JJqi9um8ViCF5uGQ0DDojy7dwSrWXDYfLmsW8I3UP207SBdtwSFxhbCe8wXYbdVi0sV8Jr5bJqjTiougv1NtsB1H1C7KDSD2kXwTY+DeRzDeG1iHntslKTh4scGWqc4gjTqT9gvQBY+CUKNpE3oG+NlLXZLH/j5ZEudBX8LaE1BVnm4B6VjV5bfb0MxX/CK77mXUtde9K39TocDa+5s3Ax2QNie/pwZIp2trb6p3TMyF5I6K0DGZnd/qS+K/nRC0T2qH1LHFSN7ucXt2oa6+3XtCJUDJjvfXAYDl5G2tD9anlNF/xV/LdcZBJTuQXbPvxzvJUG+Rk5PWMtu/h9py6n2QcI/a08Qkq7Rh/2j7gE+p+X+NcLGnt/im+yULbUBeq+0cjRzwsbOPwtGyffiL3D9N9NuQMfyWTQHsQbQ/ZA0PaZB+bC3rJ3mAu2gwm8M+m6DG3xKDHsiZvY6gutYzOU2lSjHokPy0jKqT1mCq62VXdfxq7QQ525p6h+jXmwdYfzdVWtsh5e3X/N2sj/j0Iaobuh74z2wZ1fkniN4HedF85Rd0bbKUy5lbR14cip9PRVfzhPVOTBybo8XaajDe/nflA5sp0ZDNw0Pr38AqnV9oXpFeJkzbbx2JxUuieTV8MIj54zlI/umb99QUPVfwDTPqTvFy2eWb9+/Ktb66d3lv25oBcUBH0HbztwfXmj2nV9RH9JpBW95FDlS+MLxvjfAFv6LiFWfvprFX3C6ws235ds2XMngI9E4FvWTgdUz/iVP203XZlN9ptzfurONlzo98Px7wvjbNd2Gz3dLYXv6bsxWt+OLJHUt3uM9/ylO406snzhnWfvdi8H86/x478d9mLL53mi189u+rcG9K+vnfNgMr3l895dOvwdmTZilI9tyTCl8rfp8vfxWJTztXvNep9jXuBNtCJYpvZB0wD97XvTSDptpR09r0=
*/