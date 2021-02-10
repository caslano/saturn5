// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    class tagged_argument;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* tagged_argument_fwd.hpp
9GPfJeekyI6JcSZCPAgfGeAeE7tEpPxrkYmOYoomDGWOpl4iJeqT+XNBMAvywo/jBe6JMNbb++jQMJTEC1HifxVgioqbQOELQPRpFFYJRqUJjxPhm8XEiByHXcJNPTYXuUxnihHDo0kR57IkXSK9NKAOLqkZfSjLZCoNZTpHdXDKkQicq35thlXb6GCYKxWTNIwxPxkEGLoGTUb7SlUNi4eAF2pDDrARROE0oueClLBLApUkpHEsU1Gtb8qJRJyhDFXkWdGSconwsqI8SgfeihvFYpstjslMs0gDVv+I2fBwKC6knwaC48nkGCR60OlgCAOhPsh3+RljIUWXmN0Orr4UHO1oOodQKDVopVCrTMmUo6TIO8kCejQ67u0d//yPz8++wPU1dAfdXZ6ZFjIOG9Oj1WnEr4ExdJmDzTuxnJKNw3Vom3IRTUfLVTIN4iIU7G7r86gkRBOVNuNnbAxZgHGZqayIfVLej6VveDMpWDhH/Hr8Yf/wp6PJU/TWDDfIWHwSlgrK1TPFmYU2WEyLOeafNGCwBujhqR98ZTByBscQsItpa2g1Dxs/YS1m8oqytuW1Dul6x5HGhwRVxJ0ekE1/slqPwenQ2bVdq/xu73Rvsn+4DePXsJ0i3rfdTRSYvu4geX/47o7ZX97v
*/