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
AAAAAAAAAAAAAAAAFQAJAAAAAAAAABAAAABlzisAY3VybC1tYXN0ZXIvcHJvamVjdHMvVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkiPlaaoCAAA7RcAABsACQAAAAAAAQAAAAAAoc4rAGN1cmwtbWFzdGVyL3Byb2plY3RzL1JFQURNRVVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAdAAkAAAAAAAAAEAAAAIvXKwBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1VUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlL11Kk/DwAAAA8AAAArAAkAAAAAAAEAAAAAAM/XKwBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzLy5naXRhdHRyaWJ1dGVzVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUg9mclA6AAAAmQAAACcACQAAAAAAAQAAAAAAMNgrAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAiAAkAAAAAAAAAEAAAALjYKwBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dz
*/