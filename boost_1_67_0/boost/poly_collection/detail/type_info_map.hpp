/* Copyright 2016-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_TYPE_INFO_MAP_HPP
#define BOOST_POLY_COLLECTION_DETAIL_TYPE_INFO_MAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/detail/workaround.hpp>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* To cope with dynamic modules/libs, the standard allows for different
 * std::type_info instances to describe the same type, which implies that
 * std::type_info::operator== and std::type_info::hash_code are costly
 * operations typically relying on the stored type name.
 * type_info_ptr_hash<T> behaves roughly as a
 * std::unordered_map<std::type_index,T> but maintains an internal cache of
 * passed std::type_info instances so that lookup is performed (when there's a
 * cache hit) without invoking std::type_info equality and hashing ops.
 */

struct type_info_ptr_hash
{
  std::size_t operator()(const std::type_info* p)const noexcept
  {return p->hash_code();}
};

struct type_info_ptr_equal_to
{
  bool operator()(
    const std::type_info* p,const std::type_info* q)const noexcept
  {return *p==*q;}
};

template<typename T,typename Allocator>
class type_info_map
{
  using map_type=std::unordered_map<
    const std::type_info*,T,
    type_info_ptr_hash,type_info_ptr_equal_to,
    typename std::allocator_traits<Allocator>::template
      rebind_alloc<std::pair<const std::type_info* const,T>>
  >;

public:
  using key_type=std::type_info;
  using mapped_type=T;
  using value_type=typename map_type::value_type;
  using allocator_type=typename map_type::allocator_type;
  using iterator=typename map_type::iterator;
  using const_iterator=typename map_type::const_iterator;

  type_info_map()=default;
  type_info_map(const type_info_map& x):
    map{x.map},
    cache{make<cache_type>(std::allocator_traits<cache_allocator_type>::
      select_on_container_copy_construction(x.cache.get_allocator()))}
    {build_cache(x.cache);}
  type_info_map(type_info_map&& x)=default;
  type_info_map(const allocator_type& al):
    map{make<map_type>(al)},cache{make<cache_type>(al)}{}
  type_info_map(const type_info_map& x,const allocator_type& al):
    map{make(x.map,al)},cache{make<cache_type>(al)}
    {build_cache(x.cache);}
  type_info_map(type_info_map&& x,const allocator_type& al):
    map{make(std::move(x.map),al)},
    cache{
      al==allocator_type{x.map.get_allocator()}&&x.map.empty()?
      make(std::move(x.cache),al):
      make<cache_type>(al)
    }
  {
    if(!(al==allocator_type{x.map.get_allocator()}&&x.map.empty())){
      build_cache(x.cache);
    }
    x.map.clear();
    x.cache.clear();
  }

  type_info_map& operator=(const type_info_map& x)
  {
    if(this!=&x)try{
      map=x.map;
      cache=make<cache_type>(map.get_allocator());
      build_cache(x.cache);
    }
    catch(...){
      map.clear();
      cache.clear();
      throw;
    }
    return *this;
  }

  type_info_map& operator=(type_info_map&& x)
  {
    if(this!=&x)try{
      map=std::move(x.map);
      if(map.get_allocator()==x.map.get_allocator()){
        cache=std::move(x.cache);
      }
      else{
        cache=make<cache_type>(map.get_allocator());
        build_cache(x.cache);
        x.cache.clear();
      }
    }
    catch(...){
      map.clear();
      cache.clear();
      x.map.clear();
      x.cache.clear();
      throw;
    }
    return *this;
  }

  allocator_type get_allocator()const noexcept{return map.get_allocator();}

  iterator       begin()noexcept{return map.begin();}
  iterator       end()noexcept{return map.end();}
  const_iterator begin()const noexcept{return map.begin();}
  const_iterator end()const noexcept{return map.end();}
  const_iterator cbegin()const noexcept{return map.cbegin();}
  const_iterator cend()const noexcept{return map.cend();}

  iterator find(const key_type& key)
  {
    auto cit=cache.find(&key);
    if(cit!=cache.end())return cit->second;
    auto mit=map.find(&key);
    if(mit!=map.end())cache.insert({&key,mit});
    return mit; 
  }

  const_iterator find(const key_type& key)const
  {
    auto cit=cache.find(&key);
    if(cit!=cache.end())return cit->second;
    return map.find(&key);
  }

  template<typename P>
  std::pair<iterator,bool> insert(const key_type& key,P&& x)
  {
    auto c=map.bucket_count();
    auto p=map.emplace(&key,std::forward<P>(x));
    if(map.bucket_count()!=c)rebuild_cache();
    cache.insert({&key,p.first});
    return p;
  }

  void swap(type_info_map& x){map.swap(x.map);cache.swap(x.cache);}

private:
  using cache_type=std::unordered_map<
    const std::type_info*,iterator,
    std::hash<const std::type_info*>,std::equal_to<const std::type_info*>,
    typename std::allocator_traits<Allocator>::template
      rebind_alloc<std::pair<const std::type_info* const,iterator>>
  >;
  using cache_allocator_type=typename cache_type::allocator_type;

#if BOOST_WORKAROUND(BOOST_LIBSTDCXX_VERSION,<40900)
  /* std::unordered_map(const allocator_type&),
   * std::unordered_map(const unordered_map&,const allocator_type&) and
   * std::unordered_map(unordered_map&&,const allocator_type&) not available.
   */

  template<typename UnorderedMap>
  static UnorderedMap make(const typename UnorderedMap::allocator_type& al)
  {
    return UnorderedMap{
      10,typename UnorderedMap::hasher{},typename UnorderedMap::key_equal{},al
    };
  }

  template<typename UnorderedMap>
  static typename std::decay<UnorderedMap>::type make(
    UnorderedMap&& x,
    const typename std::decay<UnorderedMap>::type::allocator_type& al)
  {
    using RawUnorderedMap=typename std::decay<UnorderedMap>::type;
    using iterator=typename std::conditional<
      !std::is_lvalue_reference<UnorderedMap>::value&&
      !std::is_const<UnorderedMap>::value,
      std::move_iterator<typename RawUnorderedMap::iterator>,
      typename RawUnorderedMap::const_iterator
    >::type;

    return RawUnorderedMap{
      iterator{x.begin()},iterator{x.end()},0,
      typename RawUnorderedMap::hasher{},typename RawUnorderedMap::key_equal{},
      al
    };
  }
#else
  template<typename UnorderedMap>
  static UnorderedMap make(const typename UnorderedMap::allocator_type& al)
  {
    return UnorderedMap{al};
  }

  template<typename UnorderedMap>
  static typename std::decay<UnorderedMap>::type make(
    UnorderedMap&& x,
    const typename std::decay<UnorderedMap>::type::allocator_type& al)
  {
    return {std::forward<UnorderedMap>(x),al};
  }
#endif

  void build_cache(const cache_type& x)
  {
    for(const auto& p:x)cache.insert({p.first,map.find(p.first)});
  }

  void rebuild_cache()
  {
    for(auto& p:cache)p.second=map.find(p.first);
  }

  map_type   map;
  cache_type cache;
};

template<typename T,typename Allocator>
void swap(type_info_map<T,Allocator>& x,type_info_map<T,Allocator>& y)
{
  x.swap(y);
}

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* type_info_map.hpp
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
*/