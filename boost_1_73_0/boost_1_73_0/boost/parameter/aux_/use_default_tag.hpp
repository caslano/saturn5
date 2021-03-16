// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_USE_DEFAULT_TAG_HPP
#define BOOST_PARAMETER_USE_DEFAULT_TAG_HPP

#include <boost/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct use_default_tag
    {
        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(use_default_tag(), {})

        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(
            use_default_tag(use_default_tag const&), {}
        )

        inline BOOST_CONSTEXPR use_default_tag operator()() const
        {
            return *this;
        }
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* use_default_tag.hpp
q33Hy+rNh/i5SJ5cQYE58o+W5wpo6skVXvSNE8p7UvMVUyvGC3Q/+b3yP/C/WL30vy6QxWtpbN8w97/DxH2GuD9W3B/LeG457zHvu++1e6h3Fsb95PCmb45bznU7Z/igPATVGDQbMPNs6eMncZueosLlT0wkzlQFxwoGU+rN7/zlvDrND8ei1JrxMVbrfex6g++ayvlbjElF1o8xdrTwnL+GqqpwjP0RP8rwyPUDX7myOqRYgAfMBTpbP5kLdds=
*/