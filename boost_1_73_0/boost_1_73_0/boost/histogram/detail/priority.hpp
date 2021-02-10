// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP
#define BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP

#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

// priority is used to priorise ambiguous overloads

template <std::size_t N>
struct priority : priority<(N - 1)> {};

template <>
struct priority<0> {};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* priority.hpp
zzA4vSCwX9PTEyy9QjIL8rqx0iG5BVU3lZJixfn1riSKdpTmVSskHDkvKjXrl6+jncayec1A6rbuKu17d1YdqnHupG+bftm5t47LgnlGi1GyG7qmMFVlrpSeY4sWSmOplBaKM6wkZRPjw5nHLIm2oZShHRHCglVtsA01JjrJ3A1xYtPknDsluj3q9Ybxv9hcumScvdzbS8JOaEHeh7QABrVyNfO8XFe6YvN54AtkpGHWqkrEgJ2yloa9UmJLb+XF5iUsLRGobTDkAGWo0wpja6AkwOin4Uk6pOVBNkzT5SI3eoHtiENFfYHshLMMfN1MY82py2+ANVhwHuaLl0zPZWjhraLCPM+kDCmrmcAhoOhGv52NhtPRSZ5NJ9i3+dtBNv19NBlPR5N36ekAd5LHTAhkVQSO7TuTy0CXE7JMKKFXlC3/oGbwpQ8opiTaWZb+GVIAuqu9LHubj4b58P3kwyiDF7Df+1eYh6fyGmZwnuVZ+ubDyyVEhI2M6pWmjsaDbM5jyq2FXXxe/PFnL/oUAdCe5XAMe4cRvRbd7YK/OX5GWD0gWICiwUL7ootTJq2No/uKO1u9u9+KHh0q2vi7eQnJpp3+pe5sIm0Fip8j9TBgYfgvjmGfXj7/IwXbgt4S5kZo/yOYx+VvCD64
*/