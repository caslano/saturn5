// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_START_DIR_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_START_DIR_HPP

#include <string>
#include <boost/process/detail/windows/handler.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Char>
struct start_dir_init : handler_base_ext
{
    start_dir_init(const std::basic_string<Char> &s) : s_(s) {}

    template <class Executor>
    void on_setup(Executor& exec) const
    {
        exec.work_dir = s_.c_str();
    }

    const std::basic_string<Char> &str() const {return s_;}
private:
    std::basic_string<Char> s_;
};

}}}}

#endif

/* start_dir.hpp
xumwVPTdIb/9nRpXNo7EMxGtZ/DRYDMM+PNk/tTqIj6dMR71JGZ7QnF5Wsn4YPnLTV4MStdzmZVRzwa6QL6YFwQukeemOEVnnwh37p9yjje3/wJtB/IbGHRGKRos7J8bDFYui+n0n5lO2r/dZNnUt55Ulvt6HRAm6YXlJ0nUEx/MvbfJ/ZyM32Q2TYWgjqo2dIfemRMTDmF4Aca/f5K4P3rJ037N9Q6zGrPaXHmZZNNhYrglcvZTC7VTa/3gieXiSJd9FVvNn9ywsjUHhRomq4MczLTxHC1mW+TSAfSaXxWN+WeyOTIXSU/fnIr1ftQZdsQN76PKlvJi3oMe/GZqECTibTGplmv54pJLwvHybswd4cWp/NWfW8UPBto13GvOoxPRfLi4KnH3PWWFTME7RdghXtt3LhCFS7Uzl0QvZ/Ux6LVN4p23FIN3me7gjpExY5KX11sWOJyQz9vJiyjpzk8+o2vDN1kRRZnRReQXNSr+J6v0Lsqu713PvXeTrv4ohfxFqRfg3Zy468ixEo1VXltoPMfiDR+H3xDqXYQQz/SrFcKiDjHceEhofutKd0hgHW7lku4Fvj188C+o3IORDMe0VUQbJNKmFG97/XiqpheniKPzum5JB75OgtEdicOgP2iI+R0HFJfLdHfPkKy7o6Ch7sPybWE6D0Rp0Y8N9/ndDffsFM/pjbVF8oclKyp4+PBVlQ3C65Px3l2C
*/