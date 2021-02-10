/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_BASE_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_BASE_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/base_collection_fwd.hpp>
#include <boost/poly_collection/detail/base_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Base,typename Allocator>
class base_collection:
 public common_impl::poly_collection<detail::base_model<Base>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::base_model<Base>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  base_collection()=default;
  base_collection(const base_collection& x)=default;
  base_collection(base_collection&& x)=default;
  base_collection& operator=(const base_collection& x)=default;
  base_collection& operator=(base_collection&& x)=default;
   
  template<typename B,typename A>
  friend bool operator==(
    const base_collection<B,A>&,const base_collection<B,A>&);
};

template<typename Base,typename Allocator>
bool operator==(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Base,typename Allocator>
bool operator!=(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y)
{
 return !(x==y);
}

template<typename Base,typename Allocator>
void swap(
  base_collection<Base,Allocator>& x,base_collection<Base,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::base_collection;

} /* namespace boost */

#endif

/* base_collection.hpp
52vKUAMVM7v729re16MVWlFboQv5yTaj0VLjb4arMGzw5tLITZ1mmsK8Sl8NHrgR5dHztpsOV+aZRrCff3ZvjEsL0Z2BhjttjNejQZg2ePvmbN8kgsdiEXr+dxzH9uHDtldiVFdFA5R7semFWcH9745hjsXU/d+K/Piw0/siLF/07AteXHffpY7e9P4DUEsDBAoAAAAIAC1nSlJeOPUjdwMAANQHAAAhAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTYxMC5jVVQFAAG2SCRgrVRhb6NGFPzOr3jyfbEjYgcSO3Zzreo6aWLdyY5solN0nNACS9gWs4hdHKKm/72z4Jx1qU9Rq1sL7/J2Zt57s8Dg6McNi47ozRE0V4CBuWHclvIPHunD6CB4pvYHlo/5rSQD2lOegx69TXmmbkMJdlnem3UQvJXIN7WZv4Fh+oFZIgKaYc5k8VSKh1RTd9YjZzIZ0zG5J+6JTZcsFzyjteZ5yMsHm97HTeTXlNV1X/FfbOKaWNbfSXmpUKRkoh9ZyQnrTEQ8VzwmpijmKipFiBuRk045JSLjNFve3s8X1zY9piJKjciTrEilsspiStmWU8kjLratRsFKTTIBHeKxUBqClRYy7yM3J83LjTIaJj3LlCS2ZSJj
*/