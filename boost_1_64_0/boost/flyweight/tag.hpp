/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_TAG_HPP
#define BOOST_FLYWEIGHT_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

/* A type T can be used as a tag in the specification of a flyweight
 * by passing it wrapped in the form tag<T>.
 */

namespace boost{

namespace flyweights{

namespace detail{

struct tag_marker{};

template<typename T>
struct is_tag:is_base_and_derived<tag_marker,T>
{};

} /* namespace flyweights::detail */

template<typename T=parameter::void_>
struct tag:parameter::template_keyword<tag<>,T>,detail::tag_marker
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* tag.hpp
ilSIuamKAX1o/hhp8MT6GGpYpZUF69GoJ5aGT2wiSo9eX9+jWz9lYr5emNFoAXWtpLMuUo8hsJSSPdHT59CkOWW5gPsSxC2r4YvnIO6ivoJSh6QU7JKkzYgktiY3rfte4n0A8PJJeKuLsSCwFADKd7s4QG9YEdlYe1XmuQHyBFqy4479MrE3JJr4XPJvbhVEOudOY+Idd8L3Ifj2ge8R+N4I35fgW/fWeEc/6HN7/8Qfxd/HvDKaFUIThMAdR/5746Z0xaTJ48nNDnedHVccCiY56MTjLfgVvelYczsePDKCxsepU6ZvwuXKIS/H0pLxAIkUFzyFS0YhLhlPyiXjyC62ZLyDY5q2VuSDmPrHZdqcpYDfvAY9TAjfeZLWIAPC+wnhdAoaV6DMPSud+twz+H4293jG87mH7dn9z+FNj4PS1GwxyH+qfNQNy15FZV/Hyr7TWHY9KDsT72HQkJoAMLS1nn8Cht5hp9AdkS2Q1+1PgyR53zhWFlzi52sNhqILNJDpS99Q0oU84+aEbSTCSpchYXcYCZuw00DYx8sEYeWgzWfynP8FeOQOflR/agfhOEk4oS2lEoayEhYaS4jdCYh+xhnjNgsse8N1LLsISyOG5e9GLAd3AJb1iIWBvk6gXy9F0KeNoE8jaDH84uoCX55Wf51iypFqMuXwtZZsfBku8ODkRCQqouJu2JiIXfHbVPbtSy36WBsoO1CX5UMdw2xqi0B9rliIpEonQNflcsIv4+Idz+XRt/vt8Y4N4/AvPSfD7xfz/tzz0d4zzh8WpkHvvGfcj8jpg9sc1qcgWqlOce9+u1O+i2XvKDpQJ/E7lutT0qjpNizBpivCppsgmy5vO3SbEYhIIvDF0G+UIifxIe8N1BOJsVrDDTwRV8WKCuw88GNTirxYFbOnrEI6loyeU8HlWnq5+Q0uaNFKlf0EbSb/uZlPLmKu9MXreZZ9CS8ZeC6c+bIleBcWwDU5dbX8Rw3TInXZQVTvLY9TlzXUu2AbdNk84/QjOc+SyUhAis8FWsMoXUc0hFDfZIW6KaKOka3nPyzM2AMNaCA0flxsex5/8b/TDMW8ql36DnVNHM+8I+YoHfEqp3m1wmmYOt9x2h91eQw5NQk5dbfk1PFS6Hwep9RqDpJxLXD2GbVb6UVFMm4c9SUd7FCpUa3XkDvme0vtEZyYn4iYNY8iMRONxIxEYqZWGTbuqQgHmXpfqYeNS4/keka5XcrVvorQe4rLSfVnRaab6r8VBbzAIsIEAQAc1E9cv/F26oz7K9r/viX2VymGIwMt8JWRtWEUG0psJvO0PfuMgkJXZER7F2NE+0eQEQ8iI+ZJRnwJByq4TObCYlwyI4wvxrccBfakgEjvUVQQqaBDVvpFvouHppfWx5gs15wDi4ASzEqEPfYZzR7nmruW/KvxJuOfNJzadKlQ2lfEPHxdbcUVKBlwVrC4Ks9x3horpUQof08fJGlu0gegYptVq2Irj1u4S9v+umgDCSvnOWwVQlbMkeWSvXAbHqkhjnl3St/YlLVZWNFDuNXYT5171NPc9lT1h9jhIJlZ3fEhV00zK7zZzvSS82l32gVQEMhXqCCVNE1NJQxhv2m0xErnZU4c8Af4pjxs0NtRwlNcnpOfwMBftlPPQmUASMt38MAZWSAtt53GpOWcSVxaRm9ZS2gb/ME/mH3Wp/BHWwSzO785kwa5/R3gPwV0LYHuQtBbddAYBHUbQacR6BoE7aaDfolHU2UunWJkqchG7qZrzcY8YetknvWY55mq81yPeQ6slXnuwTz5Vedpi3ke1fNciXnSWVRrXEjJa7DM7oVT5yXAfnRNTIg4CGD694OAacgmiSkUMZ1S2kU=
*/