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
pXYtPCYyd3IODIYmAfkcmdqMXwlBAe+ve0QQcHi7EfPVRt8l6oNdLyoL2QwQ26mlRSoADNmejjtBi5bcVztbVD7xTilF5PbWzIiCdXt0g1jByCGIi8sKS4J1RzittRoKjHD4/KiqNCAC0d4L2S41MlsjWe9AejZ0PC4/4mt/KzIxFk4Wh9CdrL96BGI6sZkI7YoOvkaCPrt/pjTyPQOEJuJg06zhJLD3MFBKN9G4c6ytx0K+CYd7kl+/M8E2YdsDZSp1deJy9odcUXfgbEZSSrGZAHYbI0UHUyKRY/3X2ZcSPol9pPZ9D6AOLLD7q/gZo5TWsUAodCCSJrI40niQY/D9rtWgk5TUVd7gc8Vows4r9y7JIMmg9ncHcTbGDBPSdZ5Bl8jM7dw+oaGBdyZE18EVyrubYiVyP7cYMZm4TtHNhMsoFRXKTKzF1EyiKvFvG6sAuPJTg8jWzhLL5pgsuFQ5BdUA3PyFL/jfDf9aeY3uJqU8WdXBAXCHpfJaKUT8sLNe+8T9UZ9MmcT6JtR77H1ldNLc4jGHn+pi82OqcgwTrCtAJ9dzK6ONu2pQtcLOnBdXc++bq0q+3JTR8M+W6gh6iK3Y/CI6TSFIBrv6liaaI06S804qFlvkq9yssTq5hmljkW3CujUxdFuawMrgpbIkKXOnMZZWFfZuTTpfFZOV71yGyOWu2P0i1HxQXd7gr/Mp4T/eVxCnqk+y
*/