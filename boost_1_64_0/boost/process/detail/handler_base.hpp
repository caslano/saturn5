// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_HANDLER_BASE_HPP
#define BOOST_PROCESS_DETAIL_HANDLER_BASE_HPP

#include <system_error>

namespace boost { namespace process { namespace detail {

template<template <class> class Template>
struct make_handler_t
{
    constexpr make_handler_t() {}
    template<typename Handler>
    constexpr Template<Handler> operator()(Handler handler) const {return Template<Handler>(handler);}
    template<typename Handler>
    constexpr Template<Handler> operator= (Handler handler) const {return Template<Handler>(handler);}
    template<typename Handler>
    constexpr Template<Handler> operator+=(Handler handler) const {return Template<Handler>(handler);}
};


struct handler_base
{
    using resource_type = void;

    template <class Executor>
    void on_setup(Executor&) const {}

    template <class Executor>
    void on_error(Executor&, const std::error_code &) const {}

    template <class Executor>
    void on_success(Executor&) const {}

};


}}}

#endif

/* handler_base.hpp
9rqu1/WxuesTeZtOPTu2662JPAy587yA7+M082xsr9qcsae/X1fxJ+60fMuYFyCTAoLmBFjjhO63Zd9l0rCuuR9cEZH5nPcYfevy5wcYusHj9rFq3P5tuf+65yNXedt+dblsWijjedLf/qDo/OgJHts3xh1flPvvy7hjoIyN0xqqfccOyL3NnlS025Cjg2E2nI65E7NEK0Z/lk+ro6ewvigyJFbsMTK/S/bWpPzE2cYGs9QmtNa+ZpslnRLMvcss3ZxJo9Mys9NtZxWsFDdD1bXhh8cc29wiYd3vcRpfr6TG/TruljFDl/8c8NGY6Zg1mO2YQxhjfLaO6F10xbFrRpQam58s7pcIdRiTN8fK/yQ6RUNtY47m3JG735EzZDUPklJaETNMD++R8Wp8j9FKMvOmBv9dz++J/J6pPWCOMR8X+125ts4IykwfbY4RPyp+/+BxHMtXY9/jRadMaGHj7jvRsdzPuWk4twJpgm9it2boWlcltxGmbyVMbcX9DdhdJTqfW2PzQXvG9pT7LUOPesJt5YJx7JvG3DTRNsfiKdH7yhM0nm7unThR7pcK3ewpogWPl+/A/gC53zgonoRFxXM3OvHB98hII62Oc3+2uBGOG7b0QM0+r2K25F05PYZQVMY0ZgQrC96GmU/PdLyaozNW3Cof+jln3X6lf+o2yvCqd2xnmJrp2V7C8BJhWCv2PrGN6RMA9RAlqTBMkzDsobS01gayOmmrmpe0tUBeZo/DpjmvaJm4e1LSN1/yiWdNpc2Zgs8hQ/nDcjNte2z2lmf2HLM8XGa4t0q4JxQ6lyJf7KRgI9ksT7HyjDXkdJ44h+fuadsZiUwDUHE26oLnxb1mkvfu4hI/s04MuFHEHaelc9+s88zn8EO5PwNfPVpZ6m2Rm37vcEWycqq9PlaXfVuD9giNgxdE7zpmgJRUMmYzSR4s1ktq2LOlgf1ciM6SRpMuSTOXPiimhfNcA+u3w9yDVzHXxxace7DFmluAuXQ+wZ38PsXvHzAyR0DpnVTMj4PwNDyjfv8IuZbfZ+FPmHOYnzG/YH5V987D32x7IF/g90WM5is4lyGe3yS4zJN4xHaWbNfLmJvQeK81F+HwrkvH69+xZI0M2Q5L1tCQvWLJGhiydZasviF7ypLVM2QPWbK6huxeS1bHkM2yZKmGbJqS2cfrMy2ZGY/+lsyMRydLZsbjWktmxqO0JTPDHG3JzDCffsuUpRpj/eXfNmRN5Jr6qMDYf5G3//6x/03G2L/VDhD5zkvH/kW+25Sr+lnJtxruWHWheQ5wvvgpdZl5fgT1A7JsOXdyijy7zFVMts8vuPLxXud5B1c+bv/PmqdQ2Hjy8Ov88pXvjy939vxrFabPuDVlQKPWbxQ2znzl4+f/bXt/Os9HKHyc33leyZXP43Ae/y98fofzvIArnzdxpfMjnOezqP07Q4zvDX4jOwxnY9oit88vaAcTYW84F/aBj8G+cD1Mg2/DYXAfTIfvwwz4MRwBz8JR8Fd4o9p3bzQMh2NhLMyGCTAHpsDxsCKcCJvAXHgtnATbwsmwPZwKe8CbYS84HQ6Ct8Ah8DaYCfP4fyT8M8yGs2EOnAOnwDvhzXAevB3eBWfCe+A8OB/eDRfA++Ff4CJ4H1wL+8DNcAncDh+Eb8IB8GM4EH4GB8NTcAg8A6+HP8NHYDz5+BisDx+HHeBS27h/P/gEzIJPwmy4Gk6Aa+BN8Bl4M1wLZ8F1cC58Fs6Hz8G/wPXwPrgBLoYvwOfgi3ADfAm+C1+B78ON8DjcBE/CLfAHuBVehK/BEP8YLEyEr8MUuBNWhrtgI/g2bA53w65wD+wF98MB8CAcCQ/BCfBdOB2+B++E78M=
*/