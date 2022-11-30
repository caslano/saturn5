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
k1deXEksXc/v5qek76IUbUphpOihEw6xLKcPUNMi4EbIR7DnXmEpRc7RmVyboIXNjT9mObATu0RzUHAxb3lHyI8vhuPJeXjmu8kVblGzn0UpPti2G+ZhwxDr4Um/JLdCbJM8+acb8k+Bt98x4s0rSRgJ7NDLM7EQ0Fds/8FQ6HBTHY58I0+PMByFet0uolk3fDrRBNyBBJKwzmzEAXBkrRGRIfL167rh8QEIXPsUFy8I2B6PrC3PQu4i79IzWagFzf+jWBB5S3MQ5zTUX5MN3hqp2wTSK5NgO+yFEWmAUbaA0VrP465ZLubGC7kflXyh79EtVddI885V1BB/w9/+Hg0UOjF111z9uKg34USr5jGzQd1duVl+sPvC/3Bbe3h9uJl5wFja3750ujk/p+xmgsbhjaQ+VI33vh0UqL4fxX9hfDxcfHKqPzjst6Zh5HLwiRjOPHupFhsdq/uyiHxz1W9sStEAN13h05zJhpTfjrLJfi6V84F+sJfi1VGnUvNk9+WCgD1fR6wsSmTRUSRG5MhtKMf77lV0XjEQ3qFiWdhkaiQ+QO/qUg0zVnFbue91w+fox0JE3t+nkHZ3DmRoFqgUX1naNuw7QnWZ/dLMiz2cp7FpXvuXTguiTHVfV3+C8DWRICe+ft2hgWOwqjNPcRW3uliCxnGhQ+HUUuKzhyWu4D/iQlvEjWTe9OrpmXqvChiUrkgOTPBFueevkg0KEPEOLloabHjORjgUsZEhvA1VddqILv7P/tbvbaK76eqkxcMbDDg9o6PmcsgUhPKRRijo+PMhp4il7BzS9G9wvBZoZhiPQnIb4Jlg52ZcVFELhZUTGWIo4+mf/q8LL2y23rE8YlU+/Z0Snysi+XtQKJFI960SEW+E9uy2ngyPg9VDjmylZ8rk1G6uo7ThdZJgk/vOxoWUHDuLzTCb0cgQSWdIUMzP0VoRlO7pydhv/hpnc2G4By4yF45DyeEMHSPYPdvir1LsIDq+cAOyOgmWl571tshc9jQ6wF0merNaeCO/vq0tEjU7V3G7gA89CTsIePze3cAOH/Y+CMTNrN2gPmt8dv/Lly9XuA7ljqbQrkuCUNWlkevy6mqfL8+vxYXi2iCRTiFJHNQ48mzIhDZXqQG1GL9EOXCi9Dpuh3vBTsUz/S+2jgjt5l0YIihFwSPBIJMQTAa0CJkVKuS0Jt7njjUOGhCBy4aUFJCzBkThrbaDui0CwAnt4iGysh3G9Amzf1W5bqLOk/9W5wu3yiHvgnoU/Rqfgwyrp4NEq23i7H25HM2Ws76Y84FfqUUWBPaozj8y71M2rkuUN7dN+6AKMRQjpAw7FXP2DIl4LVMQJ11TnQomDJSYJBUkJ2AHX7CJ6A5vjaXEhfNC/8olyXgkMPpIvTvd4LEUL6FzCwas0497RDn72NJSbGZTXmo5a2lVQM6ocdVhVspIpLpJVrxAVLyoObc04i6RXioCgyjILFdOw2tDWshsS5kDN1lwm4/ZZdy57GdAIJtcs93APFElb31VQJYdnF1oiLfLqpiXZzT7n9iOUXRkkRoWJjVsdI0G5QlrHRzQiD6C12CuhqhLB7paOERo67WyPsJC1vZywxWEHwq7wgd8Cof1B3Vdst9YG9u8EbI6ytpJMyGCsIt+jKPJGTFIpktqDBa8pkKE5d1kyL4FX4be2xfr1++ewFrJEPXFHy1IXaoUa8qxobq9oO+FzWeHVFM2kteZKWv/y6mJGWL8dyfHMJMAnDond5qYuG2miDLwURHgsJAaVblH8o8cf5NQWXPDVtGYx/YMX7MAUs4Y1JyzVjHsriYUpNBWz6T5lUXra2GUK2njOS92fuYoAdLYXcP+kCjrVB2iU/igm3xFFxJYZ0VkqdTlSMzuH96a8hX+dSu5wnNGF/113HoQ8Y1VoujVgNjHk9DWbPXTqa/plcNw1vjrMWolGfF+7xjuHoFwVGuNZtOdL9nRkbecouvQrFzdG+P+qb2gVTgBX+wUGu9Ev+5bFlIRnZI2/ESRI10H+WC2wCAdWYV9XZqUb0vprshslHuiLcUWFP5OrClsqk42j1O8y6As/b0d6TnOk/KZUh2Rj/BBxjSgcTKp+CJK9wpjYvkSdiG9IOxSgAAN8ko9ZOvMLPdmG9q/l6kKlC4B56b3smgevmO9dU8mCW7vBlXltwMlnVr404QUEwhidmrTQawIWEIdg/DVuDK9tIZEktonYz60Zx36yw26/vKtRnWYwcXMPmkx7VrVlfycvqz+b0n0In7+lvI4ip/NEKFtDOtuqInqp8ZNeA8lZvB4YqnGzqvZohQC70hgunn6vJ/pU4emSZHyR0VNCLRRCfK6NEWrymGM5CWmFkU/1fq01Z+oMlfFFugu/jsv3md06pgXf1l1cq7H9mG4/fzb82DIoCtMZw/M0tHPhs1XvwZ/zC9wUmUIBTikGs0gWe7+YP8A1wqFYpUqsnY1UfMsJIORh3EagoS/xKpq6n54Hkx6ayKNFIY4HKD3gnmbjcNGwKvrt7fjRpe3qWOcX8nSGfoKGK9nuXZ1Wmmr6BI4X1tAlVUMGbMTwK+YMzQkQhYFt8bnG+kIi37NmYn0pzQEQQACaCfhCKrLTurJngaFFmFRUqQ7dkdziBuYBEc295rg+P9oDMCPnpfsJPU0QXXFYNsjKyxlLZcsgmTuJKvT7ez2mvWI7mnjpckWLER+uIy9Nol7NYwIKYMLc8C/AN8O1A9Mg/3VKWubAS935YP5OhJvBswY1Z8qY5rAy8ssSA7cAJuUirkVv8t+xF0qMPYyjHUNvSRoipE0ZCcf6qr0gu0injEc619bAT4AONUL/YttOaDmh2uuU4K/w8yIJMEHy084xhZ4i7wavw7QRZ2raanWkrH/xqo2tkEIAQz6ozubtdgYMgq7N9Ep+oZmG4OYvCJtsKDDG7DJx3Edt9AiZX0fbj+bjAc9RWKSrDTXZCirQNur2u4iK5MkiA8bnWo3yc7FvbTC7mp3Xr1GpcLBwO7jZgYxak2V5y3cCXchsVsWmma+7cUzf3ZnO2kB0A7ALTe1rEwcV+ZcRjqnN+3KHmqZQ6OYOethqGCgjSvm/UPX2E4cIufwYgDfYmylIYpVfBkdUflLNtBPNvgymujCA215Mie02zbvhUEKa9JPFOGAuqmrKmg77uVuOoORzixw4VR8qNNqDY5MvJCYs7Jviw6wvcI9k3RfsYnjG5qV53toJk52e+xcLw9RNgMhb7wUqlFs3ExwgkyvSy5HehlKoj/PtokKYly7mTCfGKIxA6Uc1aO6NAurSZST+ji134lNuD+uBzuIyyYigiKsiIcE0DbNXsCHxN+Hv6x8OFNSL1oLP2sbAKdyGXxeNZ5TbjeL1C2FfIXLqTzikwEphhURZftcAYir6dTJLCJC55d/BmfprXGk4/I8ErSnaWRaC8uxAuzdRMc4mFSVTaZ3NqH8PB9VcG06jNE4Mie3SEyrV6ataCuugSGETM53DiWaVa/s3aTP6Z+xFqXPaLzcKMkMkVtbxqHWPu68qjD7KD3xSsKU4cLFIGyOVZpgHm1Y2Uwv8aQVmdZJZ9eOBvSuc9MQMMFr0G+Pf0j7nYBezg3LvmNG3z0R6J4HWLqDUFPFpk4vViGDZbtd1PE55GSlAN4BCYr6ePHdmQkjqzgdoccoTKNs7dSbj04cByWlbFiBmDa4XyFaQLm3TEN8I+4EgQogy/AMelIsPCEqobqu5Ugp3rGJJmOLGuNfogurf0yTkGNIl4vSmLCpv4fTcxp9MukCS9FEogkVCEFydJNnL1wArFNKuh7s7frP4uU2LJ0aU8+0BJ2WVQJi86RrE0zJXX+YJTijunL9aDVg3r7CgAZSN+uWxrbAApLr+n2QHwUPg4x3rrcH9Vu5naeBJcG4Idq608w3sjUOWoqgce1tyL60AaeCuzeF1UoKSL30ix8jMb+KMIMngzWqk6LzrTvgVVo7TtooF1NGiNNzkjKax8qzliEy7x2n+SBmUZSSqZ8xaWMnYwqbjlI2ZkGmz975QL10os1U5iNgTa6ojIvbtZN/LDMnBUAR8h/FsGmcAMQ+NuqAE2RtEm2OwQy6g1aYzN2fvDlTR9/1hLm580qKIPPzO/fqfJ6pyTpxOov2CCFfvtrJLkhkl6NcPLELPhfLVpvtlvmPTkLXYRfahLQxrpSVa/zhBWDAxKci1+IPpTIltXAhqi/ohC/n5anX1Lhw8QIzNw+G3ynffkV/U9m1iOtl2z1lta5XucVTgE9BRb2Zd4WSRSMBaPo0+hK2dRvwVRDS7NY5Ar879Fh9Z64LjIC9qovXf0vAJsEs6B/rBtgAQmOGUgXX8YKD8sUutoq8YfI5BRYqoW5algZi7CVqtG6Opzlc2jHjDBlRk0V5c7uqGJ4jftiq8OnUhzsndAUt4xoxIhMTPyuXROTF2jDQWYfX1vy5UA1KYkI5/JFsEG2d4UAPZFE58M/NEis37MA1qKGb34hoLhNR77FOmfxBWhO4BFhGORiq+yDiLAqzDYHqd0GsiSs17kvcxf8bOuDJc6P2WQ/WVkAJ9nEDSFacwvvkGZAkOx5SaTAQlBadL6nn8D2pubdY6aWuPPL18/MT0AEIEPgr6Ffwr5Bfob/CfoX/ivgV+SvqV/SvmF+xv+J+xf9K+JX4K+lX8q+UX6m/0n6l//r3K+NX5q+sX9m/cn7l/sr7lf+r4Ffhr6Jfxb9KfpX+KvtV/qviV+Wvql/Vv2p+1f6q+1X/q+FX46+mX82/Wn61/mr71f6r41fnr65f3b96fvX+6vvV/2vg1+CvoV/Dv0Z+jf4a+zX+a+LX5K+pX9O/Zn7N/pr7Nf9r4dfir6Vfy79Wfq3+Wvu1/mvj1+avrV/bv3Z+7f7a+7X/6+DX4a+jX8e/Tn6d/jr7df7r4tflr6tf179uft3+uvt1/+vh1+Ovp1/Pv15+vf56+/X+6+PX56+vX9+/ADp/82/tIf8i/YFkvfM8e/TCHCINJsQpoZ8JDoao/sOt10uy+Wjh6EnznV4Hv0HQrzZbfUx6rmh6x0PGvfGOuXLGPyDgtYcz2cMxCygrVExD5W3sdr7uORV2IHRfGeyVliegyT/Yqwc7f1L4fS5486HemArX1x82PvLxWKx2VLonIGrXKbMDFFLjLY4x8y68o/OMQ6g6XCcHmt8NO0O9FYWcPA/w5BFWjRm+2AaVFqJ8fNt1fD7EZxlNYKqg9MKbtv8UxLkW9fHBxr02q//27DVWKOHdNMfv1ILm5PuY/M48S/lV8xyBFIv9VvFqeVLu3vtH1XDucdy4C7nx3WldIT1v7eh/0PWOscLAzNbotm3btm3btm3btu1n27Zt27a9v/c99/6657tNuzJZaTIrnaSdSdr0oEStiCH9SXjxxLeI5Ec62Rref6KHy6zcxpmAieI+cHE7xuoPB59Ide5e2e6eEXFt3i4RL/rPsOXrF1Srj9Kil+XuZKVga46DhbypIIBDPHBvt2L5qf3XGdtjr93uE2IFz1zJmbpnD1TBOxqpmpXTVMqXkVm751r9uVVFLDlVaV9Dp/7ve2prqA6dvrxTSjzw7Lu+BVpO9JKb2Y3UphAzgtC0SHnUVQtFAopedcreWnIQbZcG5e/gLmnzW3QFJ8+nGk2/4zGEvF+3j97TYw/FwxPwK7B3yNw3+DaNfcckoh2BtFNxwt4tgpmd2sZzlEsWsq2D+lSIoWn3wb5JwlNn0/auitllFLc5X6tH35SjdqDvZUaH5c7K0H2Sq6mb36nT5afHPaoWN6WVz/rMUZnvpyA9H03/ceBA6fztg7BzyuArR8tZ46IEzmhxf6ksxesnqvv4H9zf5sPaJ6t20lfXRKQAVSIrwiJx+jnvxTWY4Gwddgdi+4fqldjs2IiHuu5DbYF+69qWOnLySVjA+1TDXgqAePxStTnlbveftL17mf+hfpoamafCz9jir8YmvvSXsaU/zU186U9DM3/a6/+Qf8V5CTh/hpZi5HE9PCJ0zLYusuGdxuD72jL/HEN1SulLz+aGhPG+82os1unTeO6LMP58M2kWBMSATM0yRETtEaoy8yvjhVRzP7TKfObd1M8nC9jlMZ+w6WTY2m6Rfz6pca84etTjf/V7j416fld2ceokVvkvBM7Zin0fAIgVZB4ZR9rDauX5e5fE7thtFhX7rGTyWbAXmSKwA201760pbtFnQsE+cgCc+IYsxu9DnqE/pMCjHBbNwu1vwN2hCUhZUJgB77ghzhdZwYSS2gxyAtuJzR7ZmY4IzsrNDEbddKvSRuxeTkwYyeEK8s+8bEKjwyLJt5DKXdW5jglmsH0Wi8cOB4lFBBJlrG6AZ/eOKnvQNsYPLXagiBG9xuGbDoUjLaS6fNfHUMzrWRebBxk1tYZPB7Q+M09GxLoaTEmEf7aiYoobTAMReC+FeFa3xryjcRbAl3IajvD7TfFg2H705nn6mbPWYE/OfX+iI/oZBAoxDisfJ/auwFlUeAFp2NltkHOnwm6SqJI6TrqzHmLdrU3Zo5CSR6g7an+zyypEJmvON2ITFG8vAVW8pxjdxrIuoIKsKVG4/Arw/d/ESti8RTNkg5UYxU2DE4ReShVDwmfbsf/iMZF4wXBb3rypRqbIlbZ3poZ+WPRge1ShZgDNCFLL1qZbiOqLoWuyooHog7OqbXTzOycyeCI7pBDX/2Ff+BZG9TqAyRkKJ+g1aw+sxC+pxBx9BRhfG1+mSgYEDBehVTBEPfX5jaT+2TsRVPYF7+9dQY6Qmf8q92EN+gNxNKG9QwMA5H43fYiIET/P3LjCEsqXF03XTE9Kak5Jkx7dv9Dva6qfN0vaMu3NqMCjjuOcNEPqSwnvJoGLfD+sFuVk2xM+LjtVaF+KdIgXByWSP9XUZFh6CpPrlbbSuYhZaPzQvGW0ThRYgeLfkUGneh1dq69tgFbp/zsaH6jeyfZszfbs+cXiLZ+EGjuOxJG0RkHd3hvdxfGuKvVDChw9UUUFXhOzj7dgXjZTSm9OulPAlxUR6YfoLEfL6lF5kkv9QJzZmOhpIvdTVARnH4mBm4PggQINFPvEtDoGd2G6cp4zYhRu7YuiB38wx37/2KEJLT4K9utkQOAh6tsw1FGmhQIYCAkJoaAY2ElnHWXz6QWGjjbLB9b/bOeqx7+++yKrtZaKlKWn+ZKWsQ3rQXUPVwixbjAg5rSDCMaro1kOuv2hU59yVQVc7J+ZzJIUddT/ZpdHV96ZC68yHS8MIAEIPkuIcZhw7h6/QBXEK0G6fghecdpej9x17g/xBPeo2bl5m70YZvW91L5iDfQR2OAxaNaLRh+rS5bKmwV9uTjqP3JJgfeVynZMNOJJbSugN43mJiIrv/PTnOfDBxmEPwKXCxCgZyhsH+jvReSievTlP+5t6OrYGvJRT09ZPxnAs9RG5tPLgmoICNhLk69iodZiVKSx1wQF7ScKBiE9Jtaj1l2XPBQ6aTsrc30EVQB7Vdp0cKk/u0KVoQNAl6U3/HoFB5Uw8dfeiu/c+TcXyS82LgpDq64mdr9kJNSsULlVZo4/W4wWf+jxgu2IQyOcw8owGIy4C8g7w+I4iD1be+yAH1Tgyg41xiF+zC2ZRmjELwlBYLQVAYZoLq552Qm9dvM0HQ+1G7Gtu06uwekQQCK/IDTS/WjK
*/