
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunction to add const to pointed type `T` (i.e. converts
// `T* [const]` to `T const* [const]`). `boost::add_const<>` cannot be used 
// instead because only adds outer const.

template<typename T> struct add_pointed_const { typedef T type; };

template<typename T> struct add_pointed_const<T*> { typedef T const* type; };

template<typename T> struct add_pointed_const<T const*>
    { typedef T const* type; };

template<typename T> struct add_pointed_const<T* const>
    { typedef T const* const type; };

template<typename T> struct add_pointed_const<T const* const>
    { typedef T const* const type; };

} } } // namespace

#endif //#include guard


/* add_pointed_const.hpp
uilP6N2goIil85vVynqpu0wvnzlSHT1LWhpFQlQHchKayhxCSX8qUzlXmT9JbGpaFfjF1mzjFaAVBQON7hSG0wYsuJU2hKthPBjPYrjqTibdUTyH8Rl0R3NPdj4cnVLrJYkZwPvCoCVxA3JZ5BLFRvP1VhTsSZXkpUBoOK1zZtGVRSdrBHSQwnp0iObVcPTuqAX7+/DmyTTo/uizs3gyG/W6cb8VBFL5hhJF6kypEu7ww/umN6aCOkwXg+k0ZY7agAZbn0mgrCYX1P71qKotTcKu/f+mro+C7Yh7FhMc1gezaX89834/DPZQ0Y2DqA1VflDl9ycJlYgGZNCm28bzfMGTW0ipIX6Mji9jP0HPz8g1Ho5Hgfety2ARb1myaK60FNCme24Ed/xZKehJ9Q7BYygXlazrUof14sj2Uf0CUEsDBAoAAAAIAC1nSlIHmg4pAAoAAHQaAAAdAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfY2Jfd3J0LmNVVAUAAbZIJGCtWOtz2zgO/+6/AnGnPcmnxGnvy27TZM9xnMZzrp3xY9PcZIYjS5Slqyx5RCqu+/jfFyCpl5Nu0pu601gCQQDE4wfQ3c6v+7SgA09+mPrP8IPfasd1lv6Pe/Jxbsa+gf6Hu+7w+yklXai2
*/