#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_oarchive :
    public detail::polymorphic_oarchive_route<binary_oarchive>
{
public:
    polymorphic_binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<binary_oarchive>(os, flags)
    {}
    ~polymorphic_binary_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP


/* polymorphic_binary_oarchive.hpp
d3Z6Q3COgBgCYkC3BFfpR3TbV7ncqj9eIeIN6HuQQiMKhRp5EGspxxNufNXjsKtKbpM9CwjhL9KwoYPWPsxBhFdD+WvYBqN6bomwVfZ6QOid/D9gG6Fj63A7tp7Z72pSs2IVMSAKWKThHAQc+wWbrkcZXQMzch44pSSfgv0l+QzuL7jwNQbd0TVQFEaXyy5Wvij6DruPLi26RdvNc0CA6N/emYAdWgDlaNKCIKj6Wu+0iZbC3JU04UoyzHYDqAm8qjL5DP8uv0EVTXZYaWdP9yke1J4gpHx/PhL6ERLa9+A+HB1fW4AgGHFw34rIMuSUNgS5nf+6lKf/t0qgSOTBd60kOaMKBIOoIl0Q1KvARysMr1pb6cMVGl7+Ck2eG3zbZwhqQS8S/1nfY5FHkD9jeE9/FJdRulwFokYRR56LWgP9a9VhrXkFLbXj7/1rmHIFKX8uIVKuLsf95wMl5UPkYMoZbvOvHKZVzheVP9Ur86kFaOTk3xdhyL/PsGV+rrxy1aIlq3MWr3kSbT89D7n5CxbZ7Kshj+llKxcuWBaxWl4gL1kYsWjxanmVfSEURWQvXpazeNV91BbNz2UL5MV6NbAoI5YvXv4Y2JkLV674n9vcpZvcJatkOxCCbXNWLcmFliMxk7Nqpbx4Idi+kJsjZ9tXLM0YiXUWrwEjd0VEn3F9IgxFWcJAA+vTPZp/CWpw4kTJie4NXjfHHpfQ
*/