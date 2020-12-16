//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_ALLOCATOR_HPP
#define BOOST_BEAST_DETAIL_ALLOCATOR_HPP

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_ALLOCATOR
#include <boost/container/allocator_traits.hpp>
#else
#include <memory>
#endif

namespace boost {
namespace beast {
namespace detail {

// This is a workaround for allocator_traits
// implementations which falsely claim C++11
// compatibility.

#ifdef BOOST_NO_CXX11_ALLOCATOR
template<class Alloc>
using allocator_traits = boost::container::allocator_traits<Alloc>;

#else
template<class Alloc>
using allocator_traits = std::allocator_traits<Alloc>;

#endif

} // detail
} // beast
} // boost

#endif

/* allocator.hpp
Ogn7DO6bUu9oPGhPJ3PRXEN3pjgv35cNsNjpzzBeoj5HuE38Q4X/+oZyHqrPoUZp/hb63ONm8Y8W/l/Lfv/lJdYzhs0S3lUl4OzGjedXgGcqqBA0A+WaVisdJN9ZDvJfQ4cVecQz5JHnO4NZT2m0lahgPeWD9iJ+7Dz7esq6fErxceqKcZN02dPEP1aX3VDFFeX+utL8rXTddhb/GMvdMNBvIv8UhA+X8JTAs2Dq/IyUsOTA8z7eaZMqYRn6fOyWk6xTlAXPUJagOs10hZa9LaHrtKIsZzJr1q5OGdcify/Bbyt/5LfK3wvit5e/t+bZy9+sH0H+hrOucBGRuAOgVqAXKX8D5x+3riiFdvXF+Jb7O6eKf6udDJI/RetDFIj/Xp7nBcpgHHCOhHfVZ8czxO8OKZOzJaw3/eQV3WedNgqWb27zaVnNF557LO8vLy7PKdT6HbkS/jh1FU1ZJrGd0mqhAxbcTuk1ZVrrcSZ7Q8t0dmVQO1GQQ7cL+S1yPA9+Wzkmv1WO51QeX45XVtrL8ZU/ghz79cXGRihxF1KPYqjhk+PDIeqHwluzjliGmAXyLXSDdcY0WtnJLsMTdB3Vk/g9jeGog1iRjZOjk6mvYHk6AhxofhdXzm/vXP+7oQtdzu8G557xh6IDZ+TA3knOY4/teypi3bwFVSP++lXOlEtP2487ReU8+ZMVSTd33ll0bMEXGx++emPre8BvmM9LXp625J+HOzz36pohLTsd7PNE3c+r7c6Hfy35HH5ebsLB8Uc6RZa03D+/19En6n6+farOk/fLOfn2gx8WLX1l1cZDXR+OX1N69hD78/ArpH4ODz6/ZUXKyhWPN+u3MnL/dx9hrtXZfP7KnFef+/6fq47MvrZ10/tXXGre9yPPE56cu+JYu/GPLZ01cuuSR+/dXfc7weY5zee3X/yMK2bJvze3fWBv25TbRg7A+Yqkf9mjczbG7o3//cirD00sPDoeB6675dz+7KT8r67KnNzROWNy1NwP81+1P8/3nSFznsVxqY8ReIZ8Gu+SSuEZx+n8Lk9HfpenE884OvPMpYviN6UV5yTACqbrAfZjumPBJ2Mgz34n8Kz3EuBo4KXAfOBEIPOJ32P7fHZjPnsyn72YzzOYzz7MZ1/m80x91sHfLeABpms968jm2XkezxQnMb+Tmd8CfvN6CvB84BXAC4BTgReSfyKwiGc+xcAFwBJ+E7sU+CJwhvVMv9K+nM1ZzpYsZyuWszXLmcRytmE52zLdLYpjHMfXPhxjNzLds3mmNRDYCTgIiGdyxj4GOITtMZR3UQ0DXgscDrwNmE6diHOAO4Ejga8DRwE/Ao4Gfgs8FxjLb3u3A54P7A3MAA7lHWLn0f8ycFMqvvUM+gTUsiPuqwJVgh4A7Qdl47nd+dARUCzOhpJAPUHpoEJQJegG0BbQjqAzpBSeI80CLQNtAm0D7QLt5/lS467gA40F5YHKed60i2dOx0Atcd7UCdQPlAkqBFnPovaAPgEdA0V3851NpQDHgvJAc81noLtBO0F7QO+CjoBc3ZEHkPX8qhy0CLQBtAW0E7QHpHqAF5QM8p9xzQWtsJx1vQzaDzoCiujpO/vqx/OvQlBViHOw2F6oV1AaaCAoG1QCqgRVgRqXeFUfUDZoBWg7aF/J/9f5149s/z81b1JmeWFZt6yS0kmn5P7/KebanzqLc7n2v4g6VKNAn2CAiC2TuVjJ1PzZWf6XZ+Uie0UVJf717HuNRH+/fJZ1PSvx2kv4LpnbTzUZ9HytnYT313PxNsiFN662dkO+uRPei3mSmSznlSxLEtfnbXnvewzQZX5gLmRZyksLQ5QjXsrBOEhpJubT9/i+I0B98vI=
*/