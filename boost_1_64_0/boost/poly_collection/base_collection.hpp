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
KnQvKm66WmTi+bYpk4MSdPud5jHvpB+Eka7TXsvondWsDoKy4x3oo/EqcTQGdeaJBPV+JaerazNrRQklostQE9MsvRsEwCfw8J+WdWtzfmpOPPqbDb7o6hTmEaO125d6rN2QBgUH60PnWKJDPuceCm7zsHY9Ziw9xA4q0h6qQwTQAR1CfZ0b712MquqdMt7tGrfPyqIVl7/PCsyHRjGtiIbHZBAVs5cpqD9IjvdoLrQxsxilUjQemWq+DmBVF6TuI357Po9XiGU7cXMV43vclu4rImkmRe7a1UbTqRR+uQWhaUL2uV1B55gErclCWgiG8J98isS4OS/pn8t6CzwGVAs4zdEdJAW8Px0MbhnUgYBHg6yM5RM6As9jIlbA74TJVZ92ZKssptwqATEl2r5+OfutpRtOXkKOlCT74/zkoE065q0vbFNIrSvKF5vQa4QxWWCSHYnF1hhUYAEKccoCvxvSrllmmPynYukX0MWvy9FGNvbokGJu41HjllIzwaJw5mxLfzp1/CuOx6Wr5Ooo2vx89tw9Nf2D1j7+hwSzff/PbkPXBn3W2VBqeg==
*/