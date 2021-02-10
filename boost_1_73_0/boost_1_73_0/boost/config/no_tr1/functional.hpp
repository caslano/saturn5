//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <functional> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/functional is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_FUNCTIONAL
#  define BOOST_CONFIG_FUNCTIONAL

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#  include <functional>

#  ifdef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#endif

/* functional.hpp
fqJNntl2AnJDmw2j292psijDQw1fHi3KCQ6xwONjZSYAtZlM4zQ+j8eJE5jZxJXR78H1ZDxyfFE61hzv/tUOJpgeoKysHJjFI/jbgZ1+RoGu5W9xcZ+jqEYT2fiuc/EkzfCGc4oIJhZle8CCk1/KZt1RmACkM4mjLL6Cd+9MfMd8mLrb657t6z75aV+tZfg/DoC6QbuUAzfFJr2BH/2T0vXgAOGz032HeOjyLblDB3BKBI7A8fCBIv3ybn+fHb9kVvvgUxCOgw/hOEznTmD7jg3F6fRP7PvpKJ1NI/gUjGcjZ0o1nn0KvlTNumOum1jjHNXWtWy0sZg5V7vAWXQVxTdRFtuBMElC6s4MbjIaQTBOYpz2D9NDVcFFD3ngHjT3y4vHBM9SG+I6/wBQSwMECgAAAAgALWdKUnMFkU84BAAAVwkAADoACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19OQU1FTE9PS1VQX1RJTUVfVC4zVVQFAAG2SCRgrVVhb9s2EP2uX3HQkMEOVDlpga5rk2Kq6yxCHMmw5GYGDAiyRFncaFElKTvB0v++IyXX8dK0+VAZMinq7t7x8d3JXdhw/NMuy9Xh4IdXYu4ELxx3ThPB/yaZ+rZDktxD
*/