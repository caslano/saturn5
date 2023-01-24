/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_AUTO_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_AUTO_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>

namespace boost{

namespace poly_collection{

namespace detail{

/* auto_iterator<Iterator> (for want of a better name) behaves like Iterator
 * save for the fact that it derefs to Iterator& rather than
 * Iterator::reference. This is useful to "lift" std algorithms so that
 * user-defined predicates are passed iterators that can then be dereferenced
 * internally.
 */

template<typename Iterator>
class auto_iterator:
  public boost::iterator_adaptor<auto_iterator<Iterator>,Iterator,Iterator>
{
public:
  auto_iterator()=default;
  auto_iterator(const Iterator& it):auto_iterator::iterator_adaptor_{it}{}
  auto_iterator(const auto_iterator&)=default;
  auto_iterator& operator=(const auto_iterator&)=default;

private:
  friend class boost::iterator_core_access;

  Iterator& dereference()const noexcept
  {
    return const_cast<auto_iterator*>(this)->base_reference();
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* auto_iterator.hpp
Uspje4RUHcBtdfK6g+B5NuBk487+tvvitu3xb5H1N9icPYcPG4Gqgfxb2l2UNR8vVpKnbA+pTqFpircPu0+PHFxEIyoyvfBhtAJr2r/rBgLPX9i9Rkw9TO/LgX/ALu0AYhUesoawmUDhLmLdaeCT76/ClenJb31sSQy1salVoH2KzD7v0MwV/kajFgxSiXx7zZDDLLMEXbrlfvAh0wdOBF7xvlKNRnnY+SLHrdkTSdFW9SCMuKC++B53cpkoZdUr5BH3lkGDjjLctFWkA7zjIm+492d+ZDIzRJeCYxRtG93L6rOydqZ9D8CbvkJVLx3jEDJiXzrljIvkTUVEDqsCA1SNix3/9AWmD2M6OivqzE/58ADtE4cDDlYgMRAan1DEdwQFp8imzVkiw3n3Cr1P0i29tu+PDqyA7Wl+GCocr10NqYSUQxrt7K8HbqzggH9hmwsGT+RXpxU71Qq8e8BykuOfnIE8CBGOpECc/drMyrc0+gsN5FrLrV0CL7ysBX4kGM13AZzwUyJBqtvNUVjLlpXmne/MT86XI8XMGmmyCwyj8wivFM6W0mworTfCp5aYiopZ6jaGffOLeA59xXmXjMGrG0rGHrmaI67557K2TJ5EYO6SdfPNGgNta0XuvdocL8biPXvAqKKRSDegPulwbK82lsLoQ2uOMtsr7xozvkyboSHYpZucoi9P5lt3Hj+eQWcsi9EfWZTKMd6w
*/