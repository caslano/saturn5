// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_PARAMETER_REQUIREMENTS_HPP
#define BOOST_PARAMETER_AUX_PACK_PARAMETER_REQUIREMENTS_HPP

namespace boost { namespace parameter { namespace aux {

    // Used to pass static information about parameter requirements through
    // the satisfies() overload set (below).  The matched function is never
    // invoked, but its type indicates whether a parameter matches at
    // compile-time.
    template <typename Keyword, typename Predicate, typename HasDefault>
    struct parameter_requirements
    {
        typedef Keyword keyword;
        typedef Predicate predicate;
        typedef HasDefault has_default;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* parameter_requirements.hpp
IB5bmm66udkmggVNghK6ydmte8K0yh3pEe3acsovK/M0q/g6RHdeL6bgli22/HrV+xU7Lso2P1cu4MxoWRUMCcPD2yL4GE6mhBFgSHUG1d9gAF6NOMSwymY6JWaP3pInh/e7Y3SEHdZEIliOA7NEVHLM5nuiQIHQl8Sy6LCPkWKU1nuvp6IqUNUAPigvNmzfv9JkKrtj8yotFHL8f3igM+xE85C5xIjFge3bpVnQ9FnWpRLZfPh6/rYxv/ElhBQ8hMOkAv+fCssA5D5J0EzXcWx5Z2m00QcxNIPLnbrOhaKrENfyYVb9+nAHekU5qdoqOAUSXrI2trAakQUGga5reiGlNShEx/lSrJnk1oxvJg2NAWhKgnkd13OovLY1cbWPALUKs0tY8wTRGoqUlZ1t9hwcdeyMcx1Z/divQ0r894KqPBbrqx0F2884TrGXrECev63izFM+XUWy1lmCzk+uKuj9dAtI7qqrSDKjWVVeopzZX0itIBXEttBzH/CDhgrheccgrsgwzRCbCFksoGvmFF8eI8OV7d4wQzA2ocBQiR56dT+AypMhKQ+Bxg==
*/