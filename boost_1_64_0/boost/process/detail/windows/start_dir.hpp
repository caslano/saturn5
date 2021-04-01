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
pmRKsPRL6eBRnjj/z1N4vumZpoHfb8OuYSk23wXm9cMDgFyiAfEfKSr44GtNtFZ4fhhvNLInRbb3tm7/TQ51xaRsHb711R8Mo9yHTpwKjevC4XlgEtmKs6ZJC4taq8YiANLlz8yKoNe+jROlDLXn8stWR7WRFLS8x9jU84qgyTfRqkRHJGB15CiKCMA+r3ndm3eon1ca2fDFDD8aMc/E8IRViHlJsT26fryhcCFEXRTUpDo0Hd/A/PdWnk+xUNj/C8Bj7kMu6sCnxtW68RVTy/tQzdbPxNLZlEAQvKyZHClceeNfOxWg76xwTN13pPkJZqSqAb9Y/b60lsXmjnM/GUM057FI/6WmCqs5a1yVfTVIudzAsFUgvj+agyxj/r1yQ7Y7D1pqefy7NZV9jKzR0dK06sAel91cem1NHYufSM1uqvHkf8wXSkSBelvAAjMDlIgX3etrdbKa3lGvGvKDJPLFJsvc+uaWcWJQcY6XOOdBx+vYRPrmPFyE5L5vCxsNSzyu/ub66uYO2ui+RIdnI0024ysKto5/K/t1ktneLGiCJJIbeRVqN93jwg==
*/