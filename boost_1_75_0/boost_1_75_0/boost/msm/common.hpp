// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_H
#define BOOST_MSM_COMMON_H

namespace boost { namespace msm
{
// wrapper for mpl::for_each as showed in the C++ Template Metaprogramming ch. 9
template <class T>
struct wrap{};

// tag to use in grammars where states are seen (init_<<, states_<<...)
struct state_tag{};

} } // boost::msm
#endif //BOOST_MSM_COMMON_H


/* common.hpp
EAXh5QLOy2M7k4FYgqRIuYMo/QDi+q31hNkNG+g4m//+cSOieNp6PGzeqMh69ZrWnV8qzCz5XT3z977zI7GzUQn9Msr2/S5pHr2bDPH1sZE8LxugpngoZXBMcNr/QwO7khviFLlMYdVZvLpGpFS1Y9sJlRX+AntjAxPsWthaL1DVF0GajU+Vc4JF/OjFV0rBDt9qHF5mYExqwKUw0zqJke5ZR8OazYf3ARrXzPUB15L2fuE9D/QMmTLvJe5RZxWmcbU9BjPB0aoxYoOfP1KaGVJZuodkmRK1NxR3wC33BpoGDl0rAdl/LQI1aR0erOvUsKljwmQ74fR/PewEXp0qARVCCQO0BPqXs4coKFlRCMlGSSH0gi2YKavAY2W9hVnzArfvWzvfXAbLaLNVfq1VKr+W/WuepFgqYdWECSMgmBvVikXRu7YYyBv+0269xoTJ5VxZIHsluZDLyK4qF9QJBjBPbCYzcUvpMQj9NZCDVFIruabptWGQIbweO8Hk6eFp4hkMkJ4EszvIBVfMlUoWiHdIfIgyHutX4QwQMwtjxIsiofo5JQmVHsZ1ylbuL0KJk7rGFo11UfbpPeyHyR4yKEu+miVd9UhsKmdgZe1LqVlAbaET5Hst9S1fZXzxQns4bYagFrmKnpHEBxW8eHEXo0bICq3IcgtkPGePKb4ZW3/0y2ByLMj28upt3MHMGhi8i7MydRu17kD2pisy
*/