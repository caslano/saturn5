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
oZJhkEQ/QVOThUwKLuuqz9PnHiy7aQmDAstWlXUo8xz3zTUqKcMyjYoCeQqFsVaZx4bOY+7Z3tm39h9tnHwEGJt1ppihN9b0wLLOIK70zTUadrzAj/OelTdmmGWqK73f+37fauOsCNpVwPOlmsaW1XHe9zurjaqgiAu/EyDv2umwLvIyFkWaz2W+/+qbcwEedQ1gfM1YvrTpMTOWa+nOgbmWxjDCw+mD58vVS2tFbnlS/kMDUzfy4TGY+9TYJIHuZNr+nPF0ELvj53EvxFyo8m+C02xgSqolwAVsqdups9KB2W5JkWVpyLOWF2DNefCilXdRFHmY+DHLG81NPp/KEG6dA1h5w2sghBG5nk+EWdAxrs/Jtvv6wFyDgryK2tDtKXtpH0DMI15s3V9/aaQPYQ+O2lhJfTPvce1sbO9Lrg/MfpO329iWxKzeR2Iug0OoeUSt9OnT5t6ujKIiyaELybzZGY5xFRlCSBkOnbbOHnCE0oZSw2WQvtu0ohsyzJw22w8ODG2cjfacMhjHSFqGscEjgl6el7C2FiSDPMPegCSsCbQuc8mohw58BaIsyHKnCGAyK3T1WQjC/SO+atdDAlUm4/XQxAvA+kJ31cx6+JkhA+atpMj9DvQp7O/Iy1D6wm/MPw97hJHoFODJzpJaZ8y6DIOwiDHxahmaeL/1Rmck9XxTjl1nrD7RwQFwHJAYTSwBlxz8TDQ7Y61V3aQL5STy3KeaCzLvU1beUdTG6XGoxgLt7Zz9Ueb9JivvPKigWPQCz7Wp4bZ3q+6wzAXtOCqtvJ39UI7lbxk8Oih3BrUcezMj7xHeLFJpn6ra/4zZB4PUD/M22s7K39UJ90kdhXjQWl32ogqHUii6PD3EBXHKeFWm2b7I0mA7BP/PdtStPPMWjal/7aI0tE5i/xd24CdQ6oxwaIwpB4Ul11dzvj2yaJ19d9JeFZR+k+nG0nByxt0t6+nEoqlbQOHHFjZOPPSpUb1x64/mlDFDez/xsXrW4gGPFWyhcyo0FjjRp/lZp2WHeK+RPsN6G4c4Zam0DIOFKVLo+cKSIcFhWDvNmjoQcNHoeyiwIiXntulfLlr7h06e1m/gkwzkXzRxUCTb/R+Lpp8a7BFRhOMBHrhC+tcpu+ySuefIoxj/+1aWZEhg5eb5PnzJyLes8jRpo9g8mAbluybzPbRk1lUn6OCsvV2wjKe2uexzJ5asdTYO4EoDPYFHqqD6ts9k1qxy4wyiCrMg8HAC+dRD43qfhMn12NFKrnbkMGXtV9+5ZO13O3EZp70Qk6vjyTxzzFxZsvwsenmRVF3W78fLWOPIwmyd5RhpC8yJsKHG1NYiW8fkZusaf1kyxyxMBXgYPsqs/NHxSQJKL+tw2/MMmzTSF1XZRSXc4Doe8VFr9Z7nWX4KVRwUGaJpYrbhvX3EXD1t35nqedY6CW83uDo145+GvToYQmxEmLgn9nNrz7N0r6pM47QobDmE+QAdU4qh/YetcuBoqYLxKuEyIN964Zgd6RVD+T0hPe8PsDu1k3bqyB/92oqX8B2e9jC8Ett50BWaBj2+aO8hrxJe2UpE56vg48Nn+AOWgxDbn/zFavscIU3FOiNybCIvYq5zXICwbSY7n2/KAT2x0+3GXS5H40eMwut27ysfPEpPc08aZLAe+z6JgTCb0NIp0WmpT3jPt/SJqpuGsP6zPOko1mzfmedba2QbJ0A4/fTcEXSUrKp/Pd+cK7IcFrYUmzvkS3YhacLnldVX9zooPd3rgM8sFPNMFJWbRVvrak0jPPVHlDOAPbOgcaWbxlG/bbWmPd/yZSoxNotmesOrPVOmOO13+0uePuxiXcVhBRxNvGqAWoZS8cJBM98=
*/