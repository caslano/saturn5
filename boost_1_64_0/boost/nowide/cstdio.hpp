//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDIO_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDIO_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <cstdio>

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::fopen;
    using std::freopen;
    using std::remove;
    using std::rename;
#else

    ///
    /// \brief Same as freopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* freopen(const char* file_name, const char* mode, FILE* stream);
    ///
    /// \brief Same as fopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* fopen(const char* file_name, const char* mode);
    ///
    /// \brief Same as rename but old_name and new_name are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL int rename(const char* old_name, const char* new_name);
    ///
    /// \brief Same as rename but name is UTF-8 string
    ///
    BOOST_NOWIDE_DECL int remove(const char* name);
#endif
    namespace detail {
        BOOST_NOWIDE_DECL FILE* wfopen(const wchar_t* filename, const wchar_t* mode);
    }
} // namespace nowide
} // namespace boost

#endif

/* cstdio.hpp
gU2p8tqtHD3Yk6lJZM487/Xt6sr1wh0rBKBHLJK4erfR579hVBEOaaeKK3nBnyfBydNSGiDkAEusQZm7c9nHoR6JAOwprjD0Uyuu45caUkaGXdwlV0kgzJoSMESPsCjPptjfyBdHUz4ieT38T2m/ykyiVUjA4G0Hx0tJ+O6yu2uWUSoxlqquwbmxxXeFnwbIUh3pmNmyVaKSfWgtcowUB8QWrSkA38o15DClsX3Ae7Y6WFI59Hbsr6daFi9zsmohEnDXyTMUl1/WQneyglsyHrj5vtPjiTVMuQ05iTM33fRDqXKuJW0olNMNJ9UGmX/8e8PiuadiukHivSWfCZM7TuXRxin0uQUMnlRpyhqZ93tCUVJtBP/6JxmEq/xdS2LEQQFDh7sskXB+SybnhBDz+R6SF3IUdxOycYod/c9zYV0LW5VlsuHsYY4jILfqnuDlBYmobRoh7faEruolp0aR9g1dpKJTa7mMW1NSVPlRWul5uwWWkaCgDatecdQcApwGKrQX2DtkCxJYQg4HXiuIKZEa7w/Bmgok14ih5HuUT0il8KQ3afiRLAnQFQ==
*/