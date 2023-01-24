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
SLPxMQJ8lvWIHSy/Iq781ye9buO+LSj5cRfBMTBa5jRxSeYUT/Ek0aLYEEoXrBMt8Aux9044YIcARYjoxW8B87zZt4cIjuCwAsklqFgArlh3FU72BG3oKV6KmvIMZZ88QMYtoj/3j8aZqsAyXJLedPgL/GjAbEkvRk7bm8t3OSQwz22zucwT1i9PejHCKEKTwLl4++BYQU6YEYzimTo4v08SoIYILSCRyelNBU13GMlzKm31KQClehqPMYNz4dl90n9Let2v0z0ohS0DrFg/utE8fqPX0kruG0QdlfeO+y6ugvMKQGVipKKkt+QXJQUTqIOdSTWJCdJtb+R2SOpIzZw8oQkoF3Tt7iFSDuk3RAfKBpzcFPX7Jb48zFo+1o6eecRhIkaTt1QTkQkxoLL1lqmwgpxgWabmGk/qhYKqpuZPTACaVTuqUy/B/NlT5xNoEAkB50FzJDYHp/dFaMi1bgV97uygrbXdulD6Rhiox443zyAj5UJIZE8/UDyv86gnWDz5nGDv6PYkcMHHEOo0lTYnIGLbDorH91pLmX1L2jPc+bYH9XiArLXDkVQki0drnJm4CRJJsRp/ot03wX/oD+Y961RQtL0oj2pCF0s/d77p9ZngicOGbrVeM4CnzVeaLFox1wR+VXkazA1mjpssNhXo8jfjKvadFdbcJpfgKYkNkc++C8pJMw33Ofc8GArKCBQtjbx7ecYQHWw6
*/