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
k9kdFk55u/Xyvd85+BOI1c+/3efrT46quuacveL6tx+TFV32gR/zLZ/l9NPPvuWzzmEvMD/lJ/b8qelae7oJenndOLHi8tLcyJnpipsS2VqTKg1qpBDNAMUZxOacqzSoJX7PEr/rit/f4bfU1RPJ/mddSY8m+3V+b188TT8oxRfH9nqyvt/863N2/Upalj8t+6wK6bf/5LSyshP7BHMykn0P7GoncE+dBZdvi2Y6yvH/lXIW2lJAJ9zzdGqfpYw=
*/