
#ifndef BOOST_CONTRACT_DETAIL_NONE_HPP_
#define BOOST_CONTRACT_DETAIL_NONE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

// Tag for "no type".
struct none {
    // Some lib code use this to avoid unused local var warnings on #if, etc.
    static none& value() {
        static none none_value;
        return none_value;
    }
};

// Transform `void` to `none` type (for convenience, instead of using MPL).
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard


/* none.hpp
bbgiNaMcYkXrBW3ubbjMjeX3kmw2jqTvbaAKCHcOAJOSSZCiUGvSUMBnzjJaS5oDkZBTmTVsgS+sBlVSKBinMI4mMz/8ZMO6ZFnZ42xFC7IULc+hJCsKDc0oW3UwS9IoEAUiIH7OpELMVjFRO0hPQdGmkj2MToJwKYCsCONkgXREQanUUv46GmVtw3Eno1xkcpTtSuGUqnqyqxlmU5EtiKUCJaCV1Abtb0MlclboFUuExmW74EyW9j4tJKzzkWhAUs57OAxlVHZboBD31bK1Jywxe6b0IkUtNdu6FNWBI5a1ByrapkY6LAv65QILb0Nb57Qx/qYQO5a+yqbkLxzZPvccRI1ZwcCNwY8HsCCSSRvu/OQ6uk3gzp1O3TCZQfQR3HDW4332wyvUBkPWBuhm2VCJWTTAqiVnND8g/6GdbjnJNYxvp0E0SdJxFIbeOEn8Gw9TTW9iOIfB2QX80dYo8LOfBzDgbKEVABfO+YVzigb9llIit6mkSp813igricjxNYTujWc9Dz8/AcUqKloFhegOIBN1rSfIsiSSGox4FkaT2I+tn1id8TancKlJOyWW7y2Dnwm0P81lqL/AcYka4SiVZ/OwgYv6fpfK0TtDe+XF46k/SfwotCYEj4MYLwd8tesyzFWRvi0rsmFV
*/