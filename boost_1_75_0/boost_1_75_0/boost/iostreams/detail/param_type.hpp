// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED //-----------//

/* param_type.hpp
m8T0csyMf4blcYlVNEBydMAwGfXG9ZdKX2zrwTcfeLo/6Fif/VoviWbvEh2R7ubYDuKjA6tyX8s3owO5kbpGoj3tqGa9B6JjiVwOfs/xOS+ogZUOCjZGRQ2ml85LGMxZufJUeBcSd18ufxML0JTFFtu0YG6mb9JeudjHtynqMswqF/+K6uWS3MXAe06ZqbjA1G0RaNHAJ+3vwOCI8FBGsH6xIdQBeFTwtW612lr1DO/uFrtbv2R+6tS5RQDLPw1fiF/AoRJFsUVSIWrbr4EKT7NguMv+j1yFHNvKR3Bk9xCTJFHeWj9V7vEDWO77a+jEx1btbdf8bBJmPj4Y9vakc+zBqe1De4bu5x3Y7v16L/bhFW78E1xqg/TBF+zL/+WuXy8OtY/sMet/Wfpx8huMpHqRfiBkOKdWuXonlJ/51w5VsMxb/Fr/44vivnbc1vXjZkwhdrBgLXyS59ZyJ3HLcKa/e+jmuyAOP2EnjjfzZUEoBd1Af/7xM1iXrzLQTPat/rILZQN3c4NDi+mXIPK7odj5bgEX7Uw6GD8POP0BhvtbN0+ygBWV+7+A5c//qrjg/FtWdnG0dDF3df13PfdTW/MH59nifkAh4kBRBAUNR8Dgy+GYmhC10Ve7hA6KLMtIsbk2Mj4rmE/0dv3BTVPZE+Gx8Ru3ab4Vv2qRs2UHr55Uf9PBlrXNQ7fdwfZFurvmKoPTTXd1LeWxucwW
*/