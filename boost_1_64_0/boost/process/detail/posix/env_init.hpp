// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_ENV_INIT_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_ENV_INIT_HPP_


#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/environment.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Char>
struct env_init;

template<>
struct env_init<char> : handler_base_ext
{
    boost::process::environment env;

    env_init(boost::process::environment && env) : env(std::move(env)) {};
    env_init(const boost::process::environment & env) : env(env) {};


    template <class Executor>
    void on_setup(Executor &exec) const
    {
        exec.env = env._env_impl;
    }

};

}}}}



#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_ */

/* env_init.hpp
vOCEDrQrvXe0v9V4wZWbl/s4e6UXB6RGJTqwnrovRS07yAX7M2mzPzzxPFj7ZN4uF8vDXnqJdO52ILxSWuSrsXkQpkNnWsbPLE0SKkhjmMiFeTINMMxx4FWYSzBxOFTCx6Cu2c1QyUpg0uuzu4Q0xH3oc14I3tVI5hPf4HnCq2NdU7l2xPS5fcXZLi7frFRp9bGkUruOeLGDSsFSKsRLL0FUZsAT050uodSWMf9gFJNclbWfD7GWerstvKXyoAs32e3FuOfaFgJRMFPtC4bH1/GTJ5HMBCEPK+bY6W1WivAEi8GIDg7TpipUnRBB/HZ1Gwl+kCs0ztJ9LlHwueuYjJvwB5GjPtXLXYDIg9WQGQpAEUScH+nfhP+hhwcYTVcYlgsFuuYb1V35AE3Q3u1r6dEZtaWlJpaqM2Ou0YCRO0TYZ2zVmXIdjQPvLbz+mOkwcFhY8l5zwBACe8zzYs3efNCAkAhHVqT6v7rxdgvEgy3Dw2hO00r8B0U5ZzyWgpbQe1tbzbwDYdBdczW/10w7VQjCUVjoYpzjBMYkdgyjl+EKRYjlF/S3XiW31w==
*/