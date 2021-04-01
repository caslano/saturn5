#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_oarchive :
    public detail::polymorphic_oarchive_route<xml_oarchive>
{
public:
    polymorphic_xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_oarchive>(os, flags)
    {}
    ~polymorphic_xml_oarchive(){}
};
} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP


/* polymorphic_xml_oarchive.hpp
cjXrgSDCuPOnmnFeWGy3Tt7gbrn8AQHyeSonly1XENWzRjlCYUEyoNwjpV7KBT7X+c/JqYt1pl6UjUYtPw4ALfZQiYmHH+NOxE0K9o4xHrJ/DMxjDgU+eU2VLGF/1kL4HPqzmLyoEmENH29DGh2KlYA7thPwmkln1UKYesmdpXx/kZBwLRBeuQFNamPqinzOwjX4yLE/GxXXZ83H2IwIiTgmgr8aknAnWO9cSYOVjyvO1eJCbcrlRRq5yIVReeyP6nPklYXQIzBM1nP30EdZJPXNYau0DqAvBxCe/CVGHBU+5M6U8KzGU6xPIDXaaocAsfZB187ruMRPkj3l78CsS5Mz3/6Ioj8fWcvCYHx7TkW2ldH6YWk+gHtriU7ZPNNLPhyfwhZJzdwczZV4yHtVqfzwSnJL5MuIbeBiFok6qWckHf68vVModPU+92r8SJUom0U8bEoaCKQEdaNXQQSsds3rIJHw8smWmjlEwxmpQPwkjaujCMMtL4yWSJ8vmQ659LKDoH0NhXSvzPYmBAmR60OyaNf47h63ghGPZnlKxNSvE5sGCkDZXfAm0w==
*/