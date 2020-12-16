/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ACCESS_SPECIFIER_HPP
#define BOOST_MULTI_INDEX_DETAIL_ACCESS_SPECIFIER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

/* In those compilers that do not accept the member template friend syntax,
 * some protected and private sections might need to be specified as
 * public.
 */

#if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
#define BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS public
#define BOOST_MULTI_INDEX_PRIVATE_IF_MEMBER_TEMPLATE_FRIENDS public
#else
#define BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS protected
#define BOOST_MULTI_INDEX_PRIVATE_IF_MEMBER_TEMPLATE_FRIENDS private
#endif

/* GCC does not correctly support in-class using declarations for template
 * functions. See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=9810
 * MSVC 7.1/8.0 seem to have a similar problem, though the conditions in
 * which the error happens are not that simple. I have yet to isolate this
 * into a snippet suitable for bug reporting.
 * Sun Studio also has this problem, which might be related, from the
 * information gathered at Sun forums, with a known issue notified at the
 * internal bug report 6421933. The bug is present up to Studio Express 2,
 * the latest preview version of the future Sun Studio 12. As of this writing
 * (October 2006) it is not known whether a fix will finally make it into the
 * official Sun Studio 12.
 */

#if BOOST_WORKAROUND(__GNUC__,==3)&&(__GNUC_MINOR__<4)||\
    BOOST_WORKAROUND(BOOST_MSVC,==1310)||\
    BOOST_WORKAROUND(BOOST_MSVC,==1400)||\
    BOOST_WORKAROUND(__SUNPRO_CC,BOOST_TESTED_AT(0x590))
#define BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS public
#else
#define BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS private
#endif

#endif

/* access_specifier.hpp
6zaNnLTI4+tOj9btTyG9ajizO2wQjkOd3g8c5ViVRXIne3wI3t88YP2WE4M8vYi7E94r55zaHgnxs7sNvCtPblbbeIf14I0Bzwq36R0HW6co85pOUT6m6R8rsmZ5zJPWzPS+7ZU92/DnCs3GsfLnmwBXlaslM642Ru0n99dMp246DIex0+dcGeToLQKms3qzQc5adx79Wl3+BOkTR0rbCyMnFJXtkOnb/M+Ua4ciCIswCOxSyCq00yh3ozyQTQUdHU7qtfiIlt//yQb33RjFtp1YTL5+DaJaqlcxjKC/VyYfiCQv3cJ2PSa/gskz31BzTNYSue8Xruf7VBYN4Ilv22Um54rIKzw7yTIqV19FHPBB/2wqe9TPc6e0ZNJo+FMLLGr+acZPC9eJPNcRaBCk+bpMrzXKlARpWsZZJIylWy0ndDrvoXKpSIsgK0MHMqbvlXI/TJ/k/CLy4iINYs3HWkMfh5SfiyhMEy8pNV12RPJWve6H36EyR1LPtd3Yz0RlSGi8nfkDys1E5vhZ6GaxIFaHA/FfZvF7oeu6VhmJavIy3pD8s9Hmbmm5cWjbYnALM+BXeN+nWNlTN5Y9PMoE1SbVQpje3T/F+3UUBWUoe6cYanrIbdYEyLJ3etPSt4tADDPBMXyhPp7KZiJMczsJS0eQVYIuH77Jtwoy7H2BLMkDO6BCWKXk7dJnG3JemNuyBUJhLLe0nJ4zzjK5EN5SDu0siMXwpRXOObb2IcbkU3j3PS7Ao/v2S7MB324XjLw7nl9GoR8JvpzSgk30R8fkbOEUsp8mqWvI6dHQ1OPtCpU76vpJnJShJdCAWfuv1OmMf5qnk1hWHuSeI4ylgE5Hy+3/tFmuKHHgXVjjs6rLpdvkfkwuEVmaWHkReWLbzzbvsymT90UO7yanjiWGfc4N34jLRp4z33XjIKGydAKw0Ac3k3NEZCVxDI8MD3z++Vx2lsqVooxdS5bUFnxlyH3tvYulFYsgz70gcWOx3XLSeA/5i0zeE6ETxHnshmLIcZbp//QiyFK/n56TeGpu5L1NUk/q/naJyhyNXMtRp/540Ku/H/fR8yPlH8nSKLdtOwc+Tm44745/hnAf7KeyHIlnidqomdf1XsotRBCkDrxxLJgFdCWCeT9AZY7KHuxFhaskyFAh9XM/ys9F5qeuZ0kJuvuvhU7qMjyMl8HPrNjxVSJb8oSPlyHk8btRXrqZ7wt5wDAl32iHN2s3TzyIr02OU5lSOEEeB0VeiPkWPK2KdvAD70GvfsaYi/00K2BurCzP4K3dDZkmvA7P0ns2T8927NKOMk+ARrYW6kobBkzQ1mPhM8b6LQ4CN/bFguTCK7CgvpRvpD6lLW1lZWfbWt3qDnwfP0jjyISd+nHqOKGAr/z0vHzRFlavldQ0vrHN81uWYeElkqFcnMD73Ma7rPimL5WDDppY6jUJoT7iMsNg1Fvpi2Taqs7Yq8a4HmDxOCJ2PTfNQ0esrMs1Vv0wsvSpsrXQXtTfdnwP+jyv69DySzv0pahUBK8s4rP9Zj89eJ6PhSJx3Tgr+3JkMGiZGUMmdNwyjkhaOCRIf6UyucjdOLKdvP/Kv/wobpo+1FepTCrkII1i36seL8cJ0Wj3Z1CZTBRZkjteWSgZ+fndAgtrc79x+ryxLspkJThRKOhr57qXtzZ1dfSO6HmY133klDJJtxQdmc1u3WywNKrlTuj2/iRL11Nvuntx4AiV0lprXSa6Itd/yilP3cV9/f4Mk82Fn1luZNkhlZVuAOXDya1N+denSGc3YCCMAwXOaF87I/Vye9S92pxeu4WzzxffQvaNmyKGV26p7uEX8r+fkTu3ub5yS3QPn/+EoQuIs7zMr/0=
*/