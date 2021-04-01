/* Copyright 2016-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_SEGMENT_BACKEND_HPP
#define BOOST_POLY_COLLECTION_DETAIL_SEGMENT_BACKEND_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <cstddef>
#include <memory>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* Internal *virtual* interface of segment<Model,Allocator> (please note that
 * a non-virtual interface exists accessible through downcasting). Member
 * functions have been defined to minimize virtual function calls according to
 * usage patterns by poly_collection. For instance, ranges are returned rather
 * than iterators to allow for caching of and end sentinel at a higher level.
 * Passed elements are type erased with [const_]value_pointer.
 */

template<typename Model,typename Allocator>
struct segment_backend
{
  using segment_backend_unique_ptr=
    std::unique_ptr<segment_backend,void(*)(segment_backend*)>;
  using value_pointer=void*;
  using const_value_pointer=const void*;
  using base_iterator=typename Model::base_iterator;
  using const_base_iterator=typename Model::const_base_iterator;
  template<typename T>
  using const_iterator=typename Model::template const_iterator<T>;
  using base_sentinel=typename Model::base_sentinel;
  using range=std::pair<base_iterator,base_sentinel>;

  segment_backend()=default;
  segment_backend(const segment_backend&)=delete;
  segment_backend& operator=(const segment_backend&)=delete;

  virtual                            ~segment_backend()=default;
  virtual segment_backend_unique_ptr copy()const=0;
  virtual segment_backend_unique_ptr copy(const Allocator&)const=0;
  virtual segment_backend_unique_ptr empty_copy(const Allocator&)const=0;
  virtual segment_backend_unique_ptr move(const Allocator&)=0;
  virtual bool                       equal(const segment_backend&)const=0;

  virtual Allocator     get_allocator()const noexcept=0;
  virtual base_iterator begin()const noexcept=0;
  virtual base_iterator end()const noexcept=0;
  virtual bool          empty()const noexcept=0;
  virtual std::size_t   size()const noexcept=0;
  virtual std::size_t   max_size()const noexcept=0;
  virtual std::size_t   capacity()const noexcept=0;
  virtual base_sentinel reserve(std::size_t)=0;
  virtual base_sentinel shrink_to_fit()=0;
  virtual range         push_back(const_value_pointer)=0;
  virtual range         push_back_move(value_pointer)=0;
  virtual range         insert(const_base_iterator,const_value_pointer)=0;
  virtual range         insert_move(const_base_iterator,value_pointer)=0;
  virtual range         erase(const_base_iterator)=0;
  virtual range         erase(const_base_iterator,const_base_iterator)=0;
  virtual range         erase_till_end(const_base_iterator)=0;
  virtual range         erase_from_begin(const_base_iterator)=0;
  virtual base_sentinel clear()noexcept=0;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* segment_backend.hpp
+EQCih05gdUX0JDNGOBh3KuEGVmba++AUzI7cedXlaSuo7TkpMYoj+1rQVHgI3bzTj2Yxz0Skx92oz3BgIMbp6Q5L3+SPomjblwafbx+bUfC33T/PUkLBR3dUjeNvX3JT0Wk7DfXWoTRa2yfmSFlicYa5DwVr49ZeL8yxGo8k0dBvOE6kxCKH7Lz2br0bt4A0k8pq61LlktmOuYws7mUNgZH8yxr4SZtX82yFm5AcShUN5gOvghUiv/3+foJ/r5E0HAmt3VpEvTZygrKDNMJP5ABPvXh3GVXMr6arel6buhZMm1kM+BQJMS3um8eLtgKg0udljU8818i2CPVbGpU8hkU/TvQ1q+WUu+actYvw6MG3PVplyQxm0Ng1qMEGWSb8RwWs8EZf046clkanFFQr1QbWYhzp0i+AFYarfXdPa5lrX0CA0J+H+wEW2EvDJPUfS64nyjkLAdKo8yjoRvt/IoCe8qVYc7pZ3sdSGcqvaN7z9/jIhJoeKi+Yftv8FKUErbU4w8cTgkuwVpSLMo21chEjbKf0OqqClUFoc7nHJ1L2ooP613Rg8rsBw==
*/