// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SYSTEM_ERROR_HPP
#define BOOST_DLL_SYSTEM_ERROR_HPP

#include <boost/dll/config.hpp>
#include <boost/predef/os.h>
#include <boost/throw_exception.hpp>

#if !BOOST_OS_WINDOWS
#   include <dlfcn.h>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

namespace boost { namespace dll { namespace detail {

    inline void reset_dlerror() BOOST_NOEXCEPT {
#if !BOOST_OS_WINDOWS
        const char* const error_txt = dlerror();
        (void)error_txt;
#endif
    }

    inline void report_error(const boost::dll::fs::error_code& ec, const char* message) {
#if !BOOST_OS_WINDOWS
        const char* const error_txt = dlerror();
        if (error_txt) {
            boost::throw_exception(
                boost::dll::fs::system_error(
                    ec,
                    message + std::string(" (dlerror system message: ") + error_txt + std::string(")")
                )
            );
        }
#endif

        boost::throw_exception(
            boost::dll::fs::system_error(
                ec, message
            )
        );
    }

}}} // boost::dll::detail

#endif // BOOST_DLL_SYSTEM_ERROR_HPP


/* system_error.hpp
5srWXGm7Me7Hw5vH1xiuSD55q7D3j5051xO8KRYVM82I5sWhPtMLsjIj+sz6OJNxUmREI1alXZcwlbPFv80Q7V4K5r93VHEcq54qFhQNw/qA6nRwYmtQMNFVRC+QFKEPZoaWWkuuE/GqaajM/LwULPUXX31VwwZWyhiI2raqiYpWLzGUKtExJEoJZh4YK8uvADOS4wTzkoURIaIN/GWeuHO2xUJTdal+RzPKioH+AFtilumexehfh6KE/DbFeziUpb/hx8b074do7WgcjJJL00+g0XVoKoQv7yeFXjc/uplxMSWUkWMXUCm2m11FAFPvgBH0kK3ljhao5F6iRNhqc+9qqVpG6xtRVq86Yfjoyo2LLlXnALU6AiW1DCmw78n7Ibo9tXzvWI1IH/IbN8bY+bKhmKb3ar/T2qPepDWb7oWUdXaJ1zUooZ1yA+tphtK8t+LsjrK+sSzZB7Qo0kHus8XEKURNQ1sYRKZ/vfWXvw/RViq2BbGAmt+NkaaG14JqZPToLDiwmfDSMr4aeowc4W61gQHxlSMbBionpSUR+j8k1wW/v9THUQIzwA==
*/