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
AGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM3LjEvc3JjL1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL9D7GIFwAAABgAAAAxAAkAAAAAAAEAAAAAADo+LQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy4xL3NyYy8uZ2l0aWdub3JlVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjaOiYAgAwAAnx4AAC8ACQAAAAAAAQAAAAAAqT4tAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM3LjEvc3JjL2N1cmwuc2xuVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUq6/HKJZBgAAQq4AADAACQAAAAAAAQAAAAAAH0ItAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM3LjEvc3JjL2N1cmwudG1wbFVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAhAAkAAAAAAAAAEAAAAM9ILQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy9VVAUAAbZIJGBQSwECAAAKAAAAAAAtZ0pSTDQpWgcAAAAHAAAAKwAJAAAAAAABAAAAAAAXSS0A
*/