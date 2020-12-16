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
iXqWA+1gPDpash1JNZLr5zrvhdThrWrznYexZ2k55inLjS8wjSh4s0otYpxlOcnWSK+KdNlEpqnIOJtIn4qMt4nMUJEJNpF+FdnMJjJLRSZipKqjW9VxgaWOCyx1bK6jXGCpY5JNJNexhU0k1zHZJpLr2NImkuvYyiaS6+gxIhO0Vr5LOpV79OJIVBcZxa1l2onKe3QkCZWGAvGt4aG9DMBwEcsxVkM0YT1ZjUSWVaWm4rpwcUyadp2o/RIPuGMQ4SzU6ebF9UFxPuIoY5SzRi9ECc1zm5/zOOge/FmRbL3ckp7qUP9ibRQgEfr1jsSgfiE/UUoDvsnhuOfgTY6DP+v9fN9Y7UV8VvjJU1uH0BgwgasBtF6mCRaFnjq/cfswsfzFsTq5cIxSJ6fezupkaR11Ut6jgk+kLNjWM3lyM3JfFoTTWpcfL14PyNqoXg8gt4qBUA2MdSVGcskp9Oc30pt94wfwPiW7RgcAVomkNWKpEo84t3auU5xbewiyZ1fhltGypXxubdtwcW7tlwR7tVBXG200KBZEDC42g7iYSbZRt2gVNgFLJX+Of9MVr4LQisu49tVD6Am1LTeIl/PpqZnPTyerOsjK7CJa8E0oLZL1HUr1fe4GrO8/zPXdXSjq2xxKJhqioD4rGTomCb/YXf6WeEm4VHrKy7A6lG21kS25GBO/EK/N4XSzgtb4PF+jVKXA5CRhYeTJ2hzjNWLi9BhlVcw1mTz8dFjDaTJScWipDUk5zngbmnKT4u2I4igrVRylyMrjdaYiIE8ny8mhMcly25Lljk2WOzZZbkXWIF7aKgIG6WS5OJTJCm9zxewSG+SCiJTRE/FtggV2sxoRElr5pMfSgxZzD7pDLyVNlTK2lWnuxDL/AgljFrSBL/FcCmUR5mMkZn4SpD0E6OMroNjfQqzasZfCex6sHZFFCnqcYGCWiaDLcZ1ED8m87iQfN/SkalZ2VQvMj3lxSi8MrXnCI4wghaJITEmaHetnhYqMZGix9CxQBAsrtBVClb7QNtkuaOX8b/aOBDqqIvknmcAAwQl3ANEAAaKghEMcLp3oAIPEdVDEKKhZOYyKGmQCcVEEAwrGYPBkxQMPBHS9FQNeBFzAG7zdXRV01Z+Mt6viOVvV1V2//8+fZBIQdd/OE/P7qq6u7q6urq6uzisPGaW6epanmsEtYLW+UODlwR2ajOr3fa0sdb4en2HFp+rxma3wxA71eCmlg6ptGpJcvf4UR/04O+ogMCHD68SAE5wocEIiHFIZBwc3zlvfWu70goNe4W3crs/icSHgxdL15ylI3wpS1o2LLCmr8r6X2hvdXk/879aX2xs9tydOv+mV9sYQ+HeKI8+3ENfx9f+/WfG/+sPzymkOfw3ZXZKxpxlfwuJcWHtqddoF7HiJVK7z5SCn5NGYTHJBjnn6UY0T7lzkO0ZnU1Sgg9goB8DN4N5dzgYfu4SLnibuLuMLMB0pphnoGPW51TAe9bz/FdXsF8yR+8p+4e1S3X7h4+I9s18ounyf2S+0mZXYfuHU83X7haVjbfYLqcXJ2y+0Cer2C2nhvWK/8PR5uv3CF2Gb/cK085O2X4geqdsvFI3ZF/YLiftjwUzNHvvW8xz3OciZ7nBK/RlQJbq721fLmxvzWXr6Cv7nagjXdbbe0avG2EjZ5Ty7IVww8UXQM5vQsXUN4SpK9I7tJLEJU/DKc+2GcOGEF0Gn74uObPj8/3w5v+gkmij/OJu1/XCObtZ2TVS3ku422mbWdvUM0fJwYrM27hHdqK3/ZN2obUmI9GmIi+olCrHFgOwbClF3pnF31gzSLbyjFxHUwefo5ngvztIt5k8aZTMQfgGywke+akWIW1E=
*/