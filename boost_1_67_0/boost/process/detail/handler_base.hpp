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
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
*/