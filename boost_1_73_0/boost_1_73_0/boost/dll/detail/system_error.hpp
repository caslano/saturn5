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
Er7BcdspH3c2LT18cfgeVmz7yjFzadxMsS5TFMMO7Aab9PD++PjoGPvPOaTE8CZQN2Jfs5ICspO117Xr0p9PYud88yia5Yn/B13xJbnF88EQkNqK2EbOwiAOhsEkQiGxCUZl5AtbgZUt3nSJ3BpNdii2CKO//S+zycjxRO60JrPj8MczCzLBdB+dxfK+WdyDfxz4v0PNwpMz8eZCb3us0nuCo069VJaDXEpvxUQPAV9Eaf19enB6MLHba/TGc2Z4JmLJZUtrFy/llIim2r761/FyZgv2v/rjiX8+nozjhePzNdkoux6O4nk4ha/+ZD5yQqrxIFWWyCgJPtsdvWg0An8SBXgUnIePJKP4YhSG0Osf7WHJj8sXo/P5p8v5dGimcPvW+Q9QSwMECgAAAAgALWdKUuopIEJ8BgAADw8AACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BPU1QuM1VUBQABtkgkYK1WW3PaRhR+319xhr7YGRDQdJLGTTNVMI5pCGJAxKXjGWaRFmtrsatqV8a06X/vOSuJi+PEeQixI7zac/vOdy7edQOefbcP80gdPPlZuN8FfvBZC41z/ZeI7OMCi8UnKP+h4DU+v8FUG/ZSnxan8E1Sn+DE
*/