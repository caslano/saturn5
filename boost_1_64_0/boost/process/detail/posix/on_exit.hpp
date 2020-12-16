// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_ON_EXIT_HPP_
#define BOOST_PROCESS_POSIX_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <system_error>
#include <functional>

namespace boost { namespace process { namespace detail { namespace posix {

struct on_exit_ : boost::process::detail::posix::async_handler
{
    std::function<void(int, const std::error_code&)> handler;
    on_exit_(const std::function<void(int, const std::error_code&)> & handler) : handler(handler)
    {

    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&) 
    {
        return handler;

    }
};


}}}}
#endif /* BOOST_PROCESS_POSIX_ON_EXIT_HPP_ */

/* on_exit.hpp
PO7R8vcVHAO/hZPgd3AK/B7OhQfgWfBHuBAehIthFPFYAvdyfAX8Gt4CLfR3AA+8H3rhw2q/D04JzT+Gr2i8qyFjNd7P6f2xHfaBL8EJAVs4Hb4Kz4Wvw0vhDngtfBOuhW/BTXCnXZ51riXzdl3K82Ts4uF0eBwshK1gEWwLi2FHOFPvz1nwVDgbDoNzYDE8Ey6AC+EF8Bx4GVys+XIufByeB7fAZXA7vAi+B5fDr+Gl0OchfjAWXgnrwqtgc7gStobXwU7wejgQroLD4e3wMrgaroVr4f3wTvgYvBs+A++B78D74IfwfrgHPgAPwDNhdS9lCybDR2A7uBF2gZvgifBR2B+WwVHwKTgeboa58GlYAJ+BZ8It8Gy4FC6CF8h14phCIHOhdN5WGQykax56fownDe5t8Rz8AD4Pv4YvwENwG0zC/h+wEXwRtoLb4fHwJZgFX4ZL4CvwWvgavB2+ATfBHfB5uBO+Ct+BO+F78GO4C34BP4A/wg+hx8t95eV6wY85Php+AnvAT+FkuA+WwG/gHPgdvAAegJfAH+HN8Ce4Af4MX4IH4WvwF1jNx/3Ex0Qi9MFUGAUbwWjYFFaBbWAs7ACrwe6wOuwFa8CBMB4OhQlwHPTDbFgLToNJsAimwFJYG86FdeFZMBUugmnwQlgPLof14UrYAF4PG8GbYWO4Gh4N74LHwPtgM/gwPBZuhM3hU7AF3ApbwW2wNXwZZsA3YAe4E3aCn8LOcA/sCqlzrG6wCuwBE2FPWBv2go1hb9gM9oUZsB/sAk+GfeAp8BSYCYfDAXAcHAiz4WBYCE+DpXAoXACHwSVwOLwUjoBXwlHwZjgaroZj4f3wDLgejodPwglwC5wM34FT4AdwKjwAp8GDcDqsGs1zAsbDIlgbzoBpsAQ2g6WwJZwFO8LZsBucC8fCv8EcOA/mw/lwPlwAF8OF8AI9vkiPL4OL4E1wMXwSLoHPwfPgy3ApfBueDw/CC2HtGOo7WBdeDNPhcngMvBS2hpfB4XAFLIJXwmJ4FZwNr4YL4DVwCbwOXgqvh1fCG+EmeDN8At4K34C3wZ1wNfwnXAP3wrXwZ3gn9FShfoQ14D0wEa6D6fA+2Bg+AHvCh2BfuB4OgBvgKPgIzIKPwbNgGTwXToTXwhx4M8yFt8JA/XAnfJLjB+BW+A/4HHwFfoL7Lvgix7vhy3APfBV+DV+DP8A34dGx1FuwJ3wHngx3wSz4IcyDH8E58GO4AH4KL4e74Sr4GVwDP4cb4T/ho/BQoD6CViA/4d/h5/AZ+GXADveYqsSTetAPt8N68CV4LHwZtoOvwO7wVdgPvgaHwtdhFnwDToc74Fz4JlwC34IXwrfhVXAnXAXfgXfAd+G98D24Ae6CT8D34XPwA/g2/BDugR/Bg/BjWKsa+QxbwE/hSfAzOAB+DofBr0jfRLgXFsCnSPc58Bl4XsAdXgL3whvg13At/BY+Ar+DT8IDcCf8Ae6CP8Jv4E/wADwIk6tT38MG8BDsA31ezg+j4VQYCwtgVbgQ1oBLYDy8AibANdAP18EkuBkmw2dhXfgdTIVV45hrD+NhOkyG9WEj2BC2hY1gV9gEjoNHw0nwWDgDHgevhK3gw7ANfAy2h1/BrvAg7AbjavB+DxNgd1gfngibwp6wPTwJHg/7wInwVDgVZsI5cABcAAfBS+FQeDUcBl+Dw+FOOALugyPhITgaNuaFLxueDHPgSJgLJ8DJsBROgQthHrwIlsKVcCZcDWfBe+EcuBHOhZvhPLgNzocvwbPgF3AB/AkuhFE1eR+EcfA8mA4vgMfBZbAvXA4z4WVwNLwcjoUr4CR4JZwDO8ALYUe4HB4Db4FN4RrYF26E/WE=
*/