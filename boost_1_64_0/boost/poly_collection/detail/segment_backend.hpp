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
OsauiTSrY7Hz3ljGcksFsPqbrJudD7TT0jzO6uadE5i1kQ6KRUx5+zzIhSfXNInna8kEng40+L2FB9uY6WvJ1y3sZmtJvHsaltYSVq6fTWCpZrn7N+sj5x8ygR8xV3ySAZiH2rjx8hpiE/G6ur/syxaWDnO0T9PDLDqNCS7Xl90YWr90XkceznF09Mvk/qpJHzVxkOR14ebygMRWjwB24l5A8xwyuWOqNe66xFJsDU478Uii6UMk7bcuaZbOLunnH0X0xmZJ9l2mH0q6Q5+/u1yrH00YSi15/0N+n6Ljjx9DdBo3shvwsv1OYSjGB5Mte6ymrZ1jHY/r2hJj7SGk7MPHKTqqRfO+uJe+O/YOkvd993EMsWbyfVnSN9kLZI83MAiDNCdaUdF371f0VR4XRMp/XdM31li9feIAfdf7C60vH5S05uEF0ZgwqKPnjdHn51ALmv+RJxDW2od8S35v9HymlKByed88xHF1IfXec5I2O7cBLVRMNfwO+2ELRxXF56FTT+QYvqCoyCd9Xu+tJ3E86Wcsz6FFH2BIjhbGRtv9xcbQgaks38kjRL/BXuhnBq6ZePBIR+OBx+aW+MkMt3dWve1AqhaXDfH6GXYWP8V8xMr3JoNe36wenYNJAaeYCrP/qRzj9sf8hMTws1AHr4uewtm6oe7r7UnMiOV1idNpzpAw3nZbOw7cOsbO6rLi9UGOocNXyYzP5zt8F449B8T3VU4sxtgc+YYSrhUQbspedR/hzkrcTexTJe9/OdPQXQ02Ls+HGkeXHfSdkIjTqLeytJ/hdLQy73c7upqmY1axuy2SPnm/VveDmGNo1eD9gNMx7Mi5n8aLxAGTOHHUibVM753EScEVxks5hps/WNk4xlj3tUy7em4M6QZ6P8Vxtl7H2mJ7xnHruBLB5k1Go1Bfc4v421hfTQwak+lqOdHctgeF+4cbR7qilmex4DjSfWlcSkyrtDE0qfL7yFMw5ACnx4LGkf+BPVcSruI4WcvML/RpRJ+0leg5XGKcdhJmbzzqwJGOKTFfdWHIPiIxDz/mwGBKwmjXerGNoflKtv22GU5/EfqOpq2ZNPQLdu/iuKThUFVoDQvoumfc+tdVjlVH9yx23tOJDuWsjgLJdRhGo2ZWesmOZxCN7D13l2nk9/oql+a1eIK+SxlYmmuSVo8RLfsnnqm/Ky2C1cOuZznoeNBmHjftxK98LH3GiSVZWLve99mEI22KaTIKc+IkYWSVgyfWAmNcf59hxnuaiUHZXp+jaE69RPK4auCaDiJp1XMZzdpz/MykSd1K0atZTXfpJr/jdNrvUFhFhZk5RRjbdsb3TAYG0jMZLswRjdvJ+L3neU7n+gqzoXAM7U9IUKWX7lggzGa2LibzlzkeE8P8xhl9377PadP1hq9L3E3Yp9Q+ZKDSONf8Xxr004ad+MJpok2zEbF8tp0hrOXEqPRSSd/kbYUdi4Rx2JgOEuaSxNyk7UfpHksqndN+f1nSp9l8GPbhzyPsNHsPy/eKxHJbD7+/BTDRHfoAWzs0buqaf2ioMfaaf13TNl3zzy67cLTmszporRBuqm2Izbca61yHd69qunsdBn2NMC6bEauD93Ic2YukHPd8gabR2mrqeZo+dQ3fv+7A0PosZfgqx9AaK2lrI6KxepC0e46JJu1PXDeWNKftSee9e4NwWi/QY1DRXjS3NBZLO8IzNXs6tWa2XqgxYKu+9/V3dIgB8qM77y8S37n73Yjun6EtGlrt6Ls+h5+rC6M17W2FbbfGfueshYXKoK/fNdjHEvaD5yzsWfgUvPDxNlzJePbFhBf+zxbtyEuItjZYX15CL8YrA3cn2s8krXm9Ut3H+eF5fG8=
*/