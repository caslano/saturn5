// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_map<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_multimap<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_map.hpp
yoYOst8Xf04tZ85G95FyIdJ5RUq7LhY+sF4z8fCEprtifM/3D5p206lc8OmGK2dF5wx1dI/J2SMy+Ol2O94N7pPnt8+dfPmRrFTp3sd3fW3lJmVc0Yhi0lsmvi3QixIf53BJb3XqtVk3UibUJKV8+NihXzu+2iqv8va6a8qzs3YUxK7bLLlQ5f6jkEtb111bXvlm3kznbt/XAtFuL+i7MlujDqlrX5yllB/5hOfzgw+BVb7jshr2G46X4lsm7a2zLVE2uHtb+Y12cfqPIeyb4EkMfefEQ6MlCrBvgodXh/b7Lgax7sJw+csnhaw7sGH9vQiN82teJD2EqafL/i/nBw/e2iBKU2D9m8s8NI0+H3rHfTfedCa79yCKHhnkF0DXjWWEcqKqPtn+2flPtmdsH1RbRYBqYvK/YYBJjDAGcwE98E+ehxO42q212frPxIFWH+DXmnDKgOO1eEZccLNz35/3Vxak3dAcQpPog7vU4jduKDMmINLAQF83MCSE89PpG88fFRZHj6s4SxCcyuCfUxnaRUdFhYdxOZZTRszo0j/Aan2AE4MBsKH5P0sRuCDuX+VzYvOf3hPNPohpsYL4Lfn9xzT6w+pfCGu0YsPqc1Igbg2kAOmFz7G4VhUGL1x8GwI25LhwAy64D5UuqVwUYMHI0WgqfXAf7hfkxqF2fkzI7qbdgdcF4CHrjnAD6/+yxv6HFDinVDkJ8pXV
*/