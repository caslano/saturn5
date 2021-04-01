// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_SET_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_SET_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_set.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_set<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_multiset<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_set.hpp
cg0DnGZlLCjDwIwcvYB5I5WoUQwzUQwGlVMMTVzLIyQk6Xs/0vQWlfN5EKLEPEZTmNuwNR3+iaVYgg0x4J8BP/eJShoFrf1pAXKxz8DlCEb+DOUdJiMKHpgf7N1a+sQbtUDgfBcRrx6AGKzv4LjZX4u52VQp7XguB9Tw22gHbZt/W9u1SY3vM4wqTaxtpB6tJ2y+pt9rmWzUTBZxDHB4qHJUAGWOChhzGj/Dmc17ubcd5z2Zq2YrtzLvzvsj2ufXh5p30TvCZ34Cbgqf8+RPkyclKN/P8Pon/E7z8ewo0oqd2Yy8UmWzGuNDn5YxevlcpEp5uaIss2GRUCdbzkRj2vyZee+riVYJyY/11A2wGjhsi2y99fGa931GRwLmeOiI/rc+2bkYOncWMuch11K7MTZDQSbyM7soNm/3f3UvQgyRx/FyE60AqBsNyIWoXwxsANBJJwzCejp4HaTEZlvsRLFa7CXSAybGbm044TpS9rHElpLLJt83SmJzjw7jNYa01491MFtYeqgrE7MmyuAvUs43dxbOMZ2pOXNM4Ek2hpmHgNH1kzE7+Lhl4Q==
*/