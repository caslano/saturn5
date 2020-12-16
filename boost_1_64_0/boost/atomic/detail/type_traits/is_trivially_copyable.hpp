/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_copyable.hpp
 *
 * This header defines \c is_trivially_copyable type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
// For std::is_trivially_copyable we require a genuine support from the compiler.
// Fallback to is_pod or a false negative result in Boost.TypeTraits is not acceptable
// as this trait will be used in a static assert and may deny valid uses of boost::atomic/atomic_ref.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

namespace boost {
namespace atomics {
namespace detail {

using std::is_trivially_copyable;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

/* is_trivially_copyable.hpp
+qWqIyfvAHP/v1fie10cXRzqVuv1lJO7U/Jsl3iNKWM0lriI7wnb5uW/KjKvx+B3BNvn0Cqnyzf3TjGc+qXCqy01HC+tq0e3+3uGcGgf7gSH9uHOcwTDOLR7eoVwaB/uBIf24bjcOtI7z61LhEPr8FlrsoN98mbv6JxP3uwdndd7mE/e0pxgn7wlOzrnkxe5eLonvfO674hP3r05IT5mdyTOhS07CH2H+ZjdkhvMH43u6Bh/NNqOnqMHoeeO8Ec7ukd+MF8wjJfZcT5oMF/z0PEdg3mWHfd3GszL7DhftqP+Tk8vtM8/V/Hyqj89ddOfn+2x+9rjPv3YujDeahjPMox3G8a/DOMZh/E+Dx3/OJg/GsZPDecNv+dwoJQn2g9Unqj5m9+2HMYXq/mb528chj9q/p6s3NCRNt9M/z5eeaKvWfqcUp+nNsf6PBTfocPB85WfuAQ8RXmK5WAluBKsBi8Fl4E3gDXgreCFyttbDraAK8CXwHrwVY3/TuNvg1EQTqnkLwJXgbPA1eA88FJwEfhxMKp8xc+Al4Gb9Py9ylu8H1wDPgB+WnlOLea5kzwzk/ZOthhXIIfwGo8Er1He2QZwFngdOF95ldcor3IjeBN4L3gL+F3wy+DT4FfAl8Gvgr9V3uhflCeawrXuBAvBLeBkcCs4HdwGloP3gbXgg2AT+BC4EXxY2/dtcA+4E3wR/C74G3AX+JbG/6jxCGPlUTAd3AMOAx8HR4HfB8eBT4CzwCfBj4JPgRXg0+AFYAv4RfA58HbwBXA7uNduN/gi+Dz4Evh78BUwg7l2HzgafBWcA34bPB/8HdgEvg5uBN8Evwa+BT4Evg0+redfBt8BfwseAN8C/wTuB9/Tfi01v9mxfeUTpoMMNTmmKg9yJjgCnAWO1PgYjTvl7ItTzhwtp1zLOVPLKddyiJtyCreHlzNByzleyzlByyFOOcS1nIXOby+wSMvpCp6i5QzXckaCXZS3mqnxvuBocJDyVQeDo8ChGn8HRFh/U6BbLb8H2Kjl55JlANgbnAjmgZPBPmAZmA+eA/YFG8F+ytPuD24CC3R8DAD3gAN1HjgC/AU42M3LfNjwDzni8DITzMc61p0vnJeZYL4yk0/aGc7LbCffxP9wHqVwKMcE+oSES/nh8ijhUMKl/N/kUf43cCir+Lu8kxxK+JPwKP87OJTwJ+FRJjmUh4tDWfVMurWOsJXQQjhAGPgsXEnCuYQmwu2EpwgHCNnPJXmSySN5JI/kkTySR/JIHskjeSSP5JE8kkdHjn8b/395bcWh4v8XFlvqH7dt37fh6iP9CMJse3/2u9t4XdNnnlE+Z4bshevi4qw2XOcKyZvd9g5e4rmGp1lbxDugBHgzNkemxHBkVhs/vm5nkx+j/GGKc6ln090eLiJEI5xyBfrJpW6af4LxsXe/xGdGqqxU8SHaR2Ra96K3/WoaXpaRHSeyZxH/hsRnR6qtdOEdnZTTJovvfLNP/VbJNy9yES1SDpeWNdrKN3Kt7jfnr1pRQTcZ/353S775keUoQH2MquxI6YtVyv/y7+1ep3uWw00Gfywyp8P1HBG4L3ypyqJ7jkqV1T0dRPbEyPn86/D5L6RP37T5r7oHe436GiwiPrSYMsHPEbexQXkM69vZA6AJlP3Y4bKeeU8rl7Wq9gLorK381j/eHctv3eXxNVvAuSc410fOxfZhPmktILomzfSRyOw152P6wNjjKgIy6vfat9e7sdEn9LHa53UcXUyYb3MD7/XYaGM9ZmqF2ajmH2a4bZ+R+GKxsVdbbWVVxYXVlY2uPrpC8hxnjVIbm2fKGeqSk3bH8MybJM8SiZcZmUKzLzy2VYcKjS3fKemT6K8=
*/