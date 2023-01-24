
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
#  include <boost/context/posix/segmented_stack.hpp>
# endif
#endif

/* segmented_stack.hpp
hxVpBEUcEK9ltEF5RX7yCsfvfphs4hg5R8Iu2mSUrmJ/PMJ7h8mXyEyOTUs8oQGLpI5qOsaVE1Tap5N0yI9cY/V0yu5OPV68FvgFl6C2uLFPQO0CeK9CWFR5nNIYPZNxVWu+KKS1hVb1+WJIsaH+W9c66PurRvDnU4bn4XfTqBWYddMn8gyLXMJsSVRu1sVaDm9ZXc45rAJwsRWYzAiMeing5Y985CPCX2C9bhTA9gsX7047eYDNNpRGIoIMU+hATodEG6ZSgQrll4VkqKt3IJIynU6waIzRDHcmmAGoPINh8JOLQUGne4a967dRLF1lRZd4J4xLh9MSRnCrkGCk8GHeu/gwl1MHHiJY/xBOdIR4ucLNuC2hYY+bpI9m5Hqwyi4qguAeeJII0UPzi3ooZlByPpa3ShPe02gXuwV7wTsiGRjKVCPZEHIBImJo+ABfs/yE+xo/X1226hs3Qchyzb0/9zzLnYu4YUrlBPf/cffmsZZk933f5yxVdbd339Lb9DIzPTOcRTPchqS4aKFCMaRkU7Ik24kox4niWEBgxAkiAREsGwgggIiARIoTJUACJwKCxGZgWYodITYl0US4iEMNhxoOhzOcfXq6p3t6e91vu1tVnSV/nHOq6t5+MxyK+qOdA9y+991bXbduVf2+v9/v+9uEp8g0VlXUpqQ0MDCCfp6TZwXWW4yz6J4GV1ObBUoO0bLH+N5dst6C
*/