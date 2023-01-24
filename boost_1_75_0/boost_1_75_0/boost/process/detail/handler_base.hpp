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
qcxYSSonb5CpZysjkZRUR0ciJrmiAJR4LlyR0uBBeTzi5svDsdGrtbxHwzZP5zJak3FJzUu9L21sI1ckOH6+O1NfNj3CefV6J1uzLcmpi1BSM4xPAh19PlK6+D25I/FNW3ajoX4qCevgpk4irUDhGQ0JbmIZHgEcHUvT80mKCpqUq198kT54ObeKBTNT1sjMrTQ8oZagkpXn5O06LQiLsodlKSRjnehW/z3DmyOECz8mYxhiSec2+ZfZCHxJXm9563Q7QMPPFMJnflqxXRVeN//PMA1dm2lrHLPTcKGqY36XQdITIgOXAinUBY+Xe8mFlYXuOB2OImGoiIXKKbcuzwsuN/nqQWN7p4fN762EJKL/JNU63S/aFhZPpRuzq4gGMf4h3o1c92JWDuiNrUGpFu+kUsVoSYzLvcWkBHbu5X1t4npLTHFA+9gD/vDt1FJbZ6KvvpNQk9sQhYQigH2vbvaT+ZudHz2XPc7NCajQXBu2CEzZ+PCFAea8fvtSHIRp82m7FSauaZ21VcfgaeKqhheqsxCJFPbG7vygovgS3+5ncAwQSpsT5MtKfXQCfKNtxAVgr/8yjAA8WSgDH5Dy/zZ5nxL1ery1NNWzA3AsNrzIKNaVnHdAXtIwGho1S0QnpC5zHe+KoQ/4jtGLs76zlbtGQU61LonUQBT/lwQHczQecSOGXigBK5ySnXb/VntlMMGwaveQq/ssoHpd
*/