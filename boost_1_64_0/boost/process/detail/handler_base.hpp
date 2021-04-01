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
tGxUGCO3lEc4OtChr/IoVdWqaiFkdIk83/rHRNtWoviPs8X+w/sqEEpr83GmQgIl7XTgyvGGcvi9cjirafQp6PTaum7+HyGHAFJDpknmIGHoPsTFUIxax91dONSFe8QjgB2IPLwyh2sCKKXQ+p/TQugfXZMXkgsTWSXy1XLj5pdEOB5gkn+Qwbo3HcHWXcpT0LXHl0XT1FKW/FTFj2+WqGpSEviIGAkb6h5JTu040mqOvri+bKYnJRaUh2HbdGOFSuqxvqjoF6hptevWYB8kjUYu+zIuDJf07b6Ty7Rw4UdvbAlKLNYXb03QZIBrGb9RcPuE9jtdoTn4/ZpoeamliH+Kci4pq1le6zOaZQz6ty3kZIh7p/kyAjmb60UjHF7Hvmvw662WJZY+cBEhy3qvp0MsdYWhfIvXX2aEUNK1WkGB7bcfhC2MWaXFA+Ugcq/aYSy8xkD7RDNnyDAgqM55lD2+Ozii+jlNhmpAUcESLxexC5fNvJsP+sCpDjZmFFZn7W5jGiqdVRnU6dBqRWqf/4h7N0QRTwDVAf4ouhuXJuyptu8PhJacGTP9yw==
*/