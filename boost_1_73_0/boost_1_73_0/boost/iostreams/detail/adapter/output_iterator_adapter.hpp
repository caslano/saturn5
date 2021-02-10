// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                      // copy.
#include <iosfwd>                         // streamsize.
#include <boost/iostreams/categories.hpp> // tags.
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Mode, typename Ch, typename OutIt>
class output_iterator_adapter {
public:
    BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
    typedef Ch        char_type;
    typedef sink_tag  category;
    explicit output_iterator_adapter(OutIt out) : out_(out) { }
    std::streamsize write(const char_type* s, std::streamsize n) 
    { 
        std::copy(s, s + n, out_); 
        return n; 
    }
private:
    OutIt out_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED //-----//

/* output_iterator_adapter.hpp
ZNqSShEN7EQYC7zKCiX7SM3Jcl0YQLjkLDeK2D0TOZshDbOUWVuaQRTFlc7BPEpUbKJ4tfB+Zot2FbdgULAlqdKSVVQZHpDzC6hQiUjdHVsBY1nNcmGy4JkKEskkUpoMz3NAIUxw01DmNG53JnBeVIKtsO5mlDQu0yJTxYYjthAgaaUl0mAL4JMobHBAlUy4rn3rRa8ytLtZb+13SvLMNSElwYT84ZjOxz7NmBEmoJvzq7OL6yu6GV5eDkdXt3TxKw1Ht8B6fz46Qb0FMmniD6XmBpk1iaLMBU/qhD/u8tb4QzgoBmSxMKhsjgJIV3YsIVayWY7ShlLdbuAcipF0kDGTHUUHls2PAFUhJqez0+FJvf8sSUztvAHBcs1ZslzL0KqVP2DjhJwD6PL0w+lwfBqOLq5Ox27VnrFQ5uH2nucJFIIbS/52bfPpkPww8986DOm5PuRxpsi/NmzOB7S9SwdGyJg3mgbTqCZNn8JQ85wzw6UC4Ge/iX0Q1kvFU5bwr6dEaxkaNl/mUBcAKQyNwjOGc64TBpE+0lzzkvw71wuhj2eLRqFw78vbNYrjmlcDP/BdWqz9pm0tzOVVgs1zCIvFgkCpVMYIdFufLu651gLTsyVawbp9o+Pryw83NzeO+6eGeGvx6TOtsW+t
*/