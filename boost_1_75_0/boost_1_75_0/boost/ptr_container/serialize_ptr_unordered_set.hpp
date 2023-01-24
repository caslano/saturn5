//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_UNORDERED_SET_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_UNORDERED_SET_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_set<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multiset<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_set.hpp
kFgtNEb7rF0EBWJ4oCpBsovbiWXCdjdMwPkppipB1pQbrnPymJpnUNCiVqoiA00avNfoPam7CrPSh9JUkaARZaXVDunIOrBRSzlRy/JVgdYlQy3fFR5RyUOjGQnQaJJ9w9kbqr2GMSA8NDQ8jItFPN1gf88Seo4LK1SRR0IWZPJ0iL13h7z/s4Yr7D+8b8RNZb+sXCwMOelAiypBppOb/GfL7b67hoVyjvXLtA+u4DdVmgOD6ecfQneLjnILco8MD7CLZoQE6sHvshNWugHskCGY82eo3wlpOwIdtc/foDqgdNSSxB7XNsFA8eNgNURk6kBRS6c9zAQqFw0FBGlErFwmjptb/gVbRU01pLpJhdWmZNpjJ8jB/BZqiCfIOFjU0NzzJqxUHJgMYckqFUt/bePVhoJRPlONOqHKTTBmv3gfv0AMZWAmB6shjUXg2M43tjeIhM7yoBg1oK9IMDWSRwpmwkxRxSqumB70YAYziitndR5TMDSFJD2droacGDI7e8kiT1EWelt2+xHDWlB6W6tvu9U2QBE4chI+PKkIBIgvGbEVUrWpFFKAIP92UNjOvxEetrIayiupa2j3ZciQhfCwQ16hw1oQHPa511LtUHhXtz6rcfNcBhT/LYr0t6nwlOt41JFAEZzSXsVcRZBlqm+zfo3qgxkm2Yv5B6M3RaQXSo8MpoeGB0aH0HVjAiNY3+bECxL7/klzEI0W
*/