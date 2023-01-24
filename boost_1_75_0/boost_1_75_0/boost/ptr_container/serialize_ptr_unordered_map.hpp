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

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_map<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multimap<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_map.hpp
mCJgUxKNJDt6mo5GLygnYd9NkuJqzMLDghiRoVwgeYwvl1vx0mitLIOk3AcyaIYUbQbTgR4REr5EL4YZGBESHcwIC/dfyGIopqFuVIg/J9anui13989nnS9emzakD1brrN/HC4yICAlGrKjUZL5uDVQVVcUjEbnIrL/4O+NNTvB6j94ciTQQ6fUytSSmD5FA/Ohag4D/MWQD8/key+0fiqBbfbIFHngg30DVV59nKGSXotaR3NhlYNFu3N/NJw0hlWmjkBxSQ27dWZwcAmO0NeII0pQyRtMo+9LuBn0+B5VRyJUk884DiueNOjaBRss4wM8R477VHUVjhodERzHCw5wCwsN0GQHhnJ9WeMs4x/YFMkLZl/vvr0eLRtFmeDrN6xWOeYEhIfPizE11IxYFB9KDOFEstTaZePfGiZyGSjue66NR+BMOfBmDFWDs+TRlFFLXpI5Kp8r5kod/mEW7D/DUzFEDrjSgUoRSkiHxLWLIciXkjQK2ldSP5Fu+f7AudHpLzkDykji9pT8Vj32CSsjmGgI1JFVCLh6t4o9h2JzyCAGbECoh7yfT53+DnsvZxlHASyf2XJ5XLh3KB+PbwZ0QmDIaPcBXvloU0nYuvypyYUiPGpUkpBUBdUjZMABsTBjh604sSf0F/Zh1agjWlDAdk8l3uvAldDfqjRCuBYm7MTc5IWk2pIG0AyKuBRkNXmRH8P6EaqHcE53V
*/