// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_START_DIR_HPP
#define BOOST_PROCESS_DETAIL_POSIX_START_DIR_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <string>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Char>
struct start_dir_init : handler_base_ext
{
    typedef Char value_type;
    typedef std::basic_string<value_type> string_type;
    start_dir_init(const string_type &s) : s_(s) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor&) const
    {
        ::chdir(s_.c_str());
    }
    const string_type & str() const {return s_;}
private:
    string_type s_;
};

}}}}

#endif

/* start_dir.hpp
h6mwddEHxYYr/YzcxchlYGx8ik7CC0b6QAhU5k2mpi4Jo3mEF6vDBvKHJdeZUAN2ugjSiiP6AwA9WHvF6a4WsBnNZ6OyANlcw6xbueNGMDR+ur09EOr6c2gbXjJzRJNKc2el4N7TQToqZ4gIvJtnMqMSblhX0DY4J79ERtYTTp9qcxjTNR2Usos3hwolTZjHf0fFUyUj7AEZe4dbj5QKf1KNqg1CvXuVZZBK/KQU0WaidHxaYdVV53TN3dlZc+3x89CMJ94iKAkDq4s0uMysdDpj7SbYEv6tobjYA04gPvtQyqKmMUj3MuVuqc7OEmV2YzUY6MmEU5OqZds0znI4Sncvw0OfX6nmBucZsmiaFFBGl003mD9QIvscKeg79N5SaQGJ5o5CZYThrSGDIBugmy5HW/thsYAVdIU+J4qRR03loWBAjfothD9k5kYwZQQ1F+4wLH7liKSMvk3w7m8kexK2KlnDe/UOVl9Ptwq8yGvwLJnhMSNhrDP1pnN9B2xlssQK3dtUk5p3lZt4+1QtEHB3n76jptnHTmh4e31pUFjIrPI5H7YS5cJGfg==
*/