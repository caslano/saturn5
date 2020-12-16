//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_FWD_HPP
#define BOOST_GIL_CONCEPTS_FWD_HPP

namespace boost { namespace gil {

// Forward declarations used by concepts

template <typename ColorBase, int K> struct kth_element_type;
template <typename ColorBase, int K> struct kth_element_reference_type;
template <typename ColorBase, int K> struct kth_element_const_reference_type;
template <typename ColorBase, int K> struct kth_semantic_element_reference_type;
template <typename ColorBase, int K> struct kth_semantic_element_const_reference_type;
template <typename ColorBase> struct size;
template <typename ColorBase> struct element_type;

template <typename T> struct is_pixel;
template <typename T> struct is_planar;
template <typename T> struct channel_type;
template <typename T> struct color_space_type;
template <typename T> struct channel_mapping_type;
template <typename T> struct num_channels;

template <typename T> struct dynamic_x_step_type;
template <typename T> struct dynamic_y_step_type;
template <typename T> struct transposed_type;

}} // namespace boost::gil

#endif

/* fwd.hpp
InBJzLMC2wRv+0TgeXCUwwm8s0LLsHwtSD+ulemmQXj+zfYNmwwWG8XgFRtxbv+w4HGSIA08Xa6vb1Fjb7auocmp7orv2acIGyoEh29SmjmlXK1X3OLXvsBVuz/xCFXf6MjMwED4rg04v0B73v1IzdFVohm+jApknP0ExnlLRhGHNJV6FvT3x4IDzahYykFXypXC3tGdzWE89fvxDOJTQ5Inx6jUZeg8WzebuZc6Ez6t13JzcwnGz3LwVL/N5oP+WbH6erGQzQcjupJ3UKWzL1/I7yjkEkPZXNr0bMFDOvwykX1+rwoXIVRx6wrTAxR9VMbQnuasG/0ukua5eoH0FfrcFoszpZabvgpArnhHwea6EVPm9CLw5u279zH+lsAdCbos19Ijpu+Sd80SyavBvF6dnKmTGL4nf6vfbhmpr/qG6ozHM0aivzxc+dksVqbUWYcydn2SuPUm++CBufpgVpzXjOQNjSm7HWiMe6yZv+dEne6c76TmAtU+EwM9aX891ZMekG+HqXbQPJ9WmpaC5yrTMBFgSgIP4/aipfPz1Lx8yVqlyyYGUsnuEiauZB+nR3v9sS1adw/HFjUGORwqb47Pa6TJUfSsZHG+aBcyNcOXrM59o15HKqNBXu/TNr/+uV74in5Is3RK3/wx8BYQd2rt/OV8oV8fC8v7BaKOzyF3T3UUfmv1knkOjr7cKewZKJSQo212tCV/Uo3RwbECdLo9eCp9Bs92Lrj9XABe99p50grOBfOmFZzotPpjcBZxZPsT6DO5AjZRtYUilYUipRRFjPyIZ36edyE4fZEcqLe6QxobAHQfyGteRjz/p20TowcnSriR4HdZGj/F25C7z+oxbASjJ+xi0QGCNvXp8+eXe1e1VgGvGGQGvs9pV0CcYVvfsqA4tY1P6XmGP6P+GkVdVxVfZVq8lb2MeQFMKnnIw+vuvBB5oU//BzeXF84DQbzISWDInampm9v79ZVN9DOs/boCWxokBNjMRLDpXBlVv88oxdZ6U/oo/jxoDpmXmjz/StRflSt6HsdRS+hxiBiFm4xJX9+pcxw7ocMKjt6XIbVsuCcjuHWcjAupXrnbzDl+G3lYqRAgg3i5Dj4a4w/bCDfAc0QWj18S31zqS3hGzoGFymFCLDEcM1ei/26aO5/kvsTluuJV2Ruf2y3g/ptlb2yHV/ltEIPJtN9t+fZOUefZ33sJPBVPTU5ijxL1Ho9v2i4A/S20Ne8Uc32WyRnM4cxGBmqBqXecOw/6CVIWSkOqcVBq8mBwxONgp+bO+vWO9LiZZMB4fFdi506o5iUT5ogMg5Y+Vyg1Dn/nfJPvqGwH+slvFGfQt0pk0gmYfvXY+pK7I2KYq4ayXXh/OYmTw/VUBfFWa2gteo3/ykZOYmqqjBVYoEt/gLiPZeATS1lkDkpBFwr7Wac3R3Go/k7bkeBGF0PoTyMYz2upoO0MlK9IjY/3w9eaePc95debH+s0ll20l/Xa30sYIMb5lqJfF5RV2mr6/h/kuFFHQU+obX5twaVyXN2nvKsK3ef0b0S48sjjZuCsniNUcH6mYri1PwqufiHb4fKdxbbfR49j+JXj7DEhD+XpsHB30OT5d4KH8Vo9jlCqmPVeaY9eKFfZXn8bwR+uQJ2qWEkBtcJ5MypMeQ8E20EuNGmPSJOTB76/fGZ+LqpKaTxhek5GpUf9e9pfEuDA2zQua4dl1ObE4fJHKwGfdnapJ+zB+Xy1wkITN+0sHqyFktjeUpYv2otng++6AQIeDOof0JThtOjxCPugtcqIciCrn1XAnumd6LMmsJEfqJbKai/uTvR7xu9Xiu/40d9HbH5bjN99vtkbva4c6gRs/bBr4C4hm6w=
*/