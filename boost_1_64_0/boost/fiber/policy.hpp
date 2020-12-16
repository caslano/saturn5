
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_POLICY_H
#define BOOST_FIBERS_POLICY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class launch {
    dispatch,
    post
};

namespace detail {

template< typename Fn >
struct is_launch_policy : public std::false_type {
};

template<>
struct is_launch_policy< boost::fibers::launch > : public std::true_type {
};

}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_POLICY_H

/* policy.hpp
MupSPXSnpZxIIHJQrMzJoozfWsbdCdemhPaQt1cKRsVktvE2DtZX4jcF58tJ6tIE6yx/1UqLPjNvafz8RfpMYZw+E7DRZ/T1QRZthu18hOemS2L+n9eLUbecBtxDHiCqWrDI/gT8OwG8yAz8xnUCmAwY6u5+/7+qA7XXPr/5raV9zr8toX6/n5rfy/lUzuuwTuUUxaillM940K6UjxaY46lHrfkdnz65lJvhJRg/1TDp2j0qTlz977LWfwkKOhy1vB6zq6QFPd+k0qozyB49+GctaX8frOc5vJYr4l4ovmelGQtP3SQjy64XRoFHF8fsEyLMJkz1m5x83ncBkZkpyFxuJnP7tW3R3SEktvNfjZj/VojmUkdHuyGvdKeqSFAdq87IVrKT6r16vUsGMIRrUv56OlSyfu7OtX0dwZTmaCv5xfCyDj7A4mVsAaQsHgD4yPB1LpP7d460fHiUhnwQZ+JOz5mXAkKZwCe2T8YDwscyHp2BsNwMDOpZQWSAo7hkIrTTFvrTK6Xep2eVK+hyhH7FmYD9N2Aetc147HZporoZUii27XU3x+KCSEkJgKSEJzntuBp+szw5pWdVKK4qkKuhFq4KXkPKJYpyX6acFU/Zh5Q/d9hRvv0RojxWzxqrKI+lk8B2lLctl5RXOBTlpTfplLl3RGbEk330JrlA07MqFdlKVNROjqd5hqAJeYfR4LRa3iu+lgenydzZ8hutg1PN0xMX3fVgX0cO/Kt+qK/jz/B3Igj6Z/D84v/oz6qvpy+Pd1sKioG1200xR4fsqp/hH4iCcS+Uwcc+VeeRi7g/vJrBpAIZQJ2Pkzi2he4glGMUyJE6oJcjxyMx2YzT033x8F/MtIH3xeAPMOFl1iLduKoxXyVy4AjgwfYWQtFY4lP3BXnU+u0ncU2K2/9aat2/unhGp/a/4uAPndFx/F/a/7tN268bc2Fy+3WP3Walt+VKCZmM//xMAo9Bn/1AMveDjCAwo8vlXDrR/Wdx/PVl/hLjb1tC+O+d0hH+x5bE1b+mPfylbO+y9szLJc2vJilBX5j62jyvvPAcp4Myy8Ulx1/TsYORld90SeX6Sdb4+DVjJN8d8ysWsM23smZWKQaQFlCKUS9ALUCeMas0G4y6seMHWoO8W75JQ+dcI0XWuIiDn+WrPotmBVF/vsYzGLvHsx9w3NlFXOL2/3wxtUz1xcSNfZsffL9s887YMyvF/hfhVytQdsDQgxp9SMrj9FV8EHAqz2dj5wlj2keo1bC1b/RC1Ib7VA3StjiHCujLzdA/J+hVLi0sZFWJMDnxseCRY2IOjZ8Rrr/dh7hmm3G9NVfgGoMLJISls87a+bbbLzRZUQnjl4RxmcA43YyxnjCmAUZ55b+4zdhbn+HEZcYEGf/tGrNL0JEifguhLRVoS8xoB89VYdnPXSsIYGhPFvmgcdQa84X/xyJCp4y3dK8NwvdA9STQzLUKdQqhPtVpDpNTbsyp0daUtUdQ6ccmwz3vWM/qA+T5YvxQlDf5btH+0hjCxxweIt8b9AoGjrpTIJvRwN5mhw94qv21jRORlyoxxK4SfaASkVklmxBa8xnCVb5acDtmDzP7BbnbYXvjSjPbkQNKcXFKqNVK5ME6OooBS3hXpK5k08+pGgvvUS5GU+5XDbr+wb3F2egn+CUeX8fdSOMrh38sXWnTq7aS+I+4mz/0FbH931ohmT4npPbhzxWtkXr7X0QS35nw4DWYTh4YTxPWz1Yi1ivNWN8BRS58r63Vnu9P6COt9qNidyqk+NlqzyJ3ytS2WFDu54nmVYJmjZnmBUAzcmTkVpw2Bjp84nCf3GQ5koNYVRLSw2A5ydnqhOa5q5V0Nc/+Ka4=
*/