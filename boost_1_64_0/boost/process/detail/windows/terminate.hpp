// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_TERMINATE_HPP
#define BOOST_PROCESS_WINDOWS_TERMINATE_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <cstdlib>
#include <boost/winapi/process.hpp>
#include <boost/winapi/get_last_error.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct child_handle;

inline void terminate(child_handle &p, std::error_code &ec) noexcept
{
    if (!::boost::winapi::TerminateProcess(p.process_handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
    {
        ec.clear();
        ::boost::winapi::CloseHandle(p.proc_info.hProcess);
        p.proc_info.hProcess = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
}

inline void terminate(child_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "TerminateProcess() failed in terminate");
}

}}}}

#endif

/* terminate.hpp
yHYVjt6I1NGwswrHY77OcDwOI+EKWAE+AVvBVbArXA17wbVQ1XOyQdcONlvUc/EqHTup8HeBXeA9sBvsquLTDQ6FCXAU7AdT4H1wHOwOJ8EecArsCfNgL/io0l8GE+Fq2AcWwL5wk7IvggXIdhXeYNUehTri6zozmnIRAWvB2rAObAvrwQTYCPaHcXA0bAzTYQs4CbaE82FruBS2hWtgO/g8vBtug93hPtgDHoMJ8Bd1XQTjkD1Bal+NSldfWEOF0x7ofF4+MBL6wiK4HSlU7kao+JVzlC/l7nQpW64v/B7eA/8Fh8MimA6vwCx4De6G1+GH8E/4KbwBD8EfoN1OvQID4FlYBp6DYfAGLAd/glHwArwPXoeD4J9wiNIrUvPJ8aUJN7ypwi3vUKhwb3TcD26CfvBF2Au+AlPhfjgDHoAPwg/hevgRfA4egjvgYfgq/ByehF/A8/BLeAl+Ba/CE/B3+A10BOoktMOvoT88AcvCb2CEso+EW+ANeFLF6wASX5Z4QVe7GQl3q3j9WcKW2wD60J9pB31hPPSDXWBlOFRdp8ASMB2WhNmwFJwGA2EeDIL5sCxcCkPhMzACPgej4EZYAe6EFeEeGAM/gJXgxzAYHoOl4ZcqHEUw1k58QtQ7suo5Odop174ZyrTUY91hOOwBY2Ev2AD2hE3U9RTYB+bCfnAl7A/Xwmy4BebA7XAyfBneD1+Dg+FbcCh8Bw6DX8Lh8BuYBAthMvwFpsBrMBWWIKxjYABMhxEwA1aEY2EVOA7WgJmwPRwPO8EJsDucCHvDSXAAHAEHQ8Ip6VSIFISSTrC8pBPk91H13IP9SCcYClvAcrAjjICd1XWCuh4JI+EYGAUnwWg4D1aAeTAGLoex8ElYFT4Hq8EXYHX4GqwB98Fa8Avl/wVYD/4KG0FHoOOgH2wEg2BjWBaGwQh1LfkZ2RNGPGFZlb/9YAMVz66qnuoGS8IEWAbeC4vgceSQcr9KuY+GB5X73eQ7O9wLA+C7sDT8HIbC92AF+D6sB/fDOHgAtlDXrdR1PPwAdoYfwp7wI9hP+dcffgyHwk9hJjwEs+FhOF1dP6Cu58IjcCH8DC6HR+FK5V8RjEeyyhE/WFnFzx82U/GjjEr6PAoD4DIYDlfACLgcFsF0ZJny537lTyAcpvyZrfzJ5V8InANrwbmwDlwE68J5MB4uhF2UeVeYB/vLtTvcl9T9KlmE+5/qfj/BUvA8DIMXYAy8qPyZjoSE4w9cpvwJhpnKnzXo+cB1MBo+pcL5NIyD6+E98Bk4GD4LR8Pn4Hi4AU6HG+ESuBk+Cp+Hrna0QN2/ukU7OoZ62sEJsBqcCF3uDv2FuwHK3UDlbrDbHYXKu7thyl2Kcpeq3SHKXTkLd9HKXXkYBitA13NKVO5qWTynRSUoP3AxLAWXwFCYD2vCpbAIrkZylT+rlT8hMB+R/El+dnAFjIYrYWW4CjaFq2EbuAbeB5+ESXAtTIPr4HSlvwgWwHz4DHwEPgWXq+sV8Am4Sq51PlLf5ScuFvmofiDBhw1hJdgI1oBNYV3YDNaHHWEb2BL2gK1gImwDRyv7KTAezpRrd/nbru6/wqL8+ap09oPVYEnYEQbCzjASdoFl4FgYCvOV+SMwAi6Xa9XOur4PDpur+9lhuCu+/m69ZUovxEKvntKLN/pnkU9qoOdgTdgI1oJ3qetm6lqXJ+VPWYt8WkH5UxGWgTGGcG5X7vwtwlnXoLdH6VWx0Kuj9BKRQqXX02I8E6rCEQ4jYQSsAyNhVxgFu6nrHupa5qv0t4z587l1vqq/D+0hHARj4BDYAM6AzeADsCVMgvFwJOwDk2E/dT1AXU+Co+BUmAIHcq9UOBSOgSM=
*/