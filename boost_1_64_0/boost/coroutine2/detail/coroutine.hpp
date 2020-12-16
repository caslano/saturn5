
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_COROUTINE_HPP

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
class pull_coroutine;

template< typename T >
class push_coroutine;

}}}

#include <boost/coroutine2/detail/pull_coroutine.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>

#include <boost/coroutine2/detail/pull_control_block_cc.hpp>
#include <boost/coroutine2/detail/push_control_block_cc.hpp>

#include <boost/coroutine2/detail/pull_coroutine.ipp>
#include <boost/coroutine2/detail/push_coroutine.ipp>

#include <boost/coroutine2/detail/pull_control_block_cc.ipp>
#include <boost/coroutine2/detail/push_control_block_cc.ipp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_COROUTINE_HPP

/* coroutine.hpp
sJuU3U8r15QgRH1zwwL+ngAwtS7w+5cC+uOG7nu0sk6SVzdNW/5oU1SSywvkPb3lr3MjVk2973Adoa21Nk2R2ifWIXi+24j+3UMQMUf33Ztg9/NB1BRoAl6SxH+yQ/rLpKGBL2l8ewJixVSBbq5RXvS3Xue3N5q/zw3Mj2X0gmttSAIWO8NfW63P/Wh8Qy+CYt3cwBsB6ANZbmfOyt9Zi7pmdykdVALVzcghNkK30uvewN/J8jRUIyI36/Ns3Uf1JGZRBAEv9BZeBxrvW07vD9bSC2sEMCZR9ks/gkHaxVvU133KBhpyrE7MS6uZeQSgJQpR7aYRoIVWEYuqCPHLYJBrdQygP7whXlMHPTevBGivdApCxGSYGI/XyDmn3eWG+rxGc4J7A3yR1xuoK92AL9mKuqeTydumRwgPYuSPyCt/cR5n5G3vBn/LSc5YiAgF/Ght3hKqjVtFXoqOfQH7YajVKJ23fukviOC0L3TbknW/GgZXZySqVTWtf/K/rNXi1iKY4HA6PT3YR/Z9H6otuQBJgCVNemuvLfR7dDVJkynpJwW1NsHfRTMWMntd/1ybTa9+6IdeuskyH+tPawXKwUvxryD/7hjINTTMIvTso/wO2hilnS7qqzvjb7v4m6/1IFzrwUBizVsDHyOX1NpkarQwwMFHbV53p+s+RbcyS5ZANz8ZTutpi77iiIZMrUzB20DgLiYX7tV+1Jt2PYpbMp47Q3xWV/adxX3v/bTrP4oJ0bK91is1HqHg5lxmVJ9t2t9EktQUlGV5KHi/B+TgXHRP7RJwPzzchv7tCZ21nlXk1nW1/wUD/All5F6Iu9vC1SmZq25OVGvfBXkrrEGTHauTvHgMNVU8DvdPKxGLiUeJe08FwN9D2J0i19Dd5qB8T5P9osDkGDr44aj9sgLVqsyDg5caYV9UOkyB/XRIji+HZ7NFFMx9DXLYMFf6Q4O1sit1vbR2pjzTet8PugHrIRk1Xv6Io8QixyPMtDvW8rfD5Bz5w7avtGB9ToF7B2eYnLFA57eaNn+2X2bqjH1kq+6jHpBXXrtpTUvdr66WfVUIgL5bKI3eBopByi5SmDwzbeoZWshWLAQvvq/Wey2bJxd6IK8Jg+u8AOoN1PuSAQRDNzrQv9oMlyXrfUk3xHrVBpLlMq0WyaPkd4DkilvAl16OgI5ivGUUxJ+aUbe7k7XOb5Qe1VXAfUFFrqMHy+lscDGZugPPUmN7jN5vVEUlRrKgZmRSbbPMj4YVyOsykbojq9rAX2vodjnLP1QJgAWaPbcWwVWtB/AyLM6T/ihmLfsUkl6dIN57whH++viCt4hYcV3Uz9TN45ZTtGvST/7izkBtvcPALKnJaSfkwuXA6ymx6rfyQt6DOv+uJQiZAsmKsbRbOgxQx6oMmroLQVniSV73ZvInrqVa01jtl52NwBNJrRvAT04lWT9V880Gkg7F9B4kCF2daILQU+prPOuIV7c8eSlFCN7maLyMUn/o+VT7HPmvfo+UT/TcZGFx+Tf0NMIqDg7M5sJfRiKg/eKocTgb4omdiHldg7VPUuJ+XdIkttN4yQ98yQ7o9OdP7W/Gmh+l9N5nFcrxsAO0WpL8JZ0pDWtDXunWOp8PCYC/FPmLY1zBk4NpwHhihQ7AeI/rNFlhuT/j5RBDamNnYgPjCJ7W8ARPd+oZ5eVvMgM0XjXeeMv/XIrGm0yktUaViCV2Aq+sI6XO7ymNlAe3mWyBjaNot6t2nKfjiZm9MGd9nk2yTh6IL7WFpLKxG/LqQF5wNEGAB5KX/wMcNJVtO/SQ+DP3As8cuqqryTN0An67bOUOawB9vZZh8ayF7muTIbk7lLrjEiSvJJpvjIpbxZE=
*/