// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_VECTOR_HPP
#define BOOST_ASSIGN_STD_VECTOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <vector>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V,A> >, V > 
    operator+=( std::vector<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V, A> >, V >
    operator+=( std::vector<V, A>& c, V2&& v )
    {
        return push_back( c )( std::forward<V2>(v) );
    }

#endif
}
}

#endif

/* vector.hpp
dL5zCVIsdp13oxOeRY2l0ZVjG6Vv5paH2N7Esudq8nSAo0os2yL2+0h8k/FhaL99sQKIJ3Vy3lXsFVyAhcJgX+izBtJDHLeo9jyxCgRJ+892aYlzeMV4tYKaaKOdYgAUBRWG3xtf8ZvYlu8Mvyl/B34DggAfAENsfl7gVGXCROZpkRc4Lf4++ft36J2V41g1M6EYx+7vwE022zI335WixaBZ1jdFqs6I+36waFC1zAOgxX+HOqKbQKQUTyEdV55sBDCPwzm89WtZC0PF3cNBgqWyL2ie8zLeztjauUrJeey3HEq1uqyel9POoNMTdSjXjz5gUjFQKY2Ue1DoePfqK9ZJeZ3KkIFFVnlultIQjUvaWAuInEf2MTHAtdvbV4CMw4DRpJq3dEkB+0OE22gPdJy0a+VishThlBVs8FnYbIqTFoZRIMq5B8FF+AoX0KFZweuXvD/Bp1Jpot2CwwPk1x9MM8g3PebSzaqg9pYCeb1ImxG5eTfHHKGOCrvqeC+tGr6PXkX38wFyZwct5lf0vg8bkaJ/hd6/FIY/oDfeefSG1cABkOQv4AuJASBRv4bfHMt88/94eELxfMqIc5SzC8pU3fV3UAm5rf9rUP8fSVnYWOMlhXcaIcoKTK3UlnlN9PloqcFXcXu4GjphEd7ve+QX3cD9kiA30smiQQ/huTotoWbKlK/knF5ThX4q5SwVfEhpk/dWxMCaCPz7
*/