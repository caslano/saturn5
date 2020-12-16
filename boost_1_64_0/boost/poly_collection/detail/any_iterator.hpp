/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ANY_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ANY_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_erasure/any_cast.hpp>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* type_erasure::any<Concept>* adaptor convertible to pointer to wrapped
 * entity.
 */

template<typename Any>
class any_iterator:public boost::iterator_adaptor<any_iterator<Any>,Any*>
{
public:
  any_iterator()=default;
  explicit any_iterator(Any* p)noexcept:any_iterator::iterator_adaptor_{p}{}
  any_iterator(const any_iterator&)=default;
  any_iterator& operator=(const any_iterator&)=default;

  template<
    typename NonConstAny,
    typename std::enable_if<
      std::is_same<Any,const NonConstAny>::value>::type* =nullptr
  >
  any_iterator(const any_iterator<NonConstAny>& x)noexcept:
    any_iterator::iterator_adaptor_{x.base()}{}

  template<
    typename NonConstAny,
    typename std::enable_if<
      std::is_same<Any,const NonConstAny>::value>::type* =nullptr
  >
  any_iterator& operator=(const any_iterator<NonConstAny>& x)noexcept
  {
    this->base_reference()=x.base();
    return *this;
  }

  /* interoperability with Any* */

  any_iterator& operator=(Any* p)noexcept
    {this->base_reference()=p;return *this;}
  operator Any*()const noexcept{return this->base();}

  /* interoperability with Concrete* */

  template<
    typename Concrete,
    typename std::enable_if<
      /* can't compile-time check concept compliance */
      !std::is_const<Any>::value||std::is_const<Concrete>::value
    >::type* =nullptr
  >
  explicit operator Concrete*()const noexcept
  {
    return const_cast<Concrete*>(
      static_cast<typename std::remove_const<Concrete>::type*>(
        type_erasure::any_cast<void*>(this->base())));
  }

private:
  template<typename>
  friend class any_iterator;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* any_iterator.hpp
W/YgOgTb0ezqHZl+WkQfAsO9iW7apu862LWUcvGXgTuMXeF16gfINIJdx2n3AHxWcL2adp5LuTfhc9uo59vYdj91uL7QjA8iS1kM2mgx8yruvww+z6dMLX3uDj4PoYPttIf9pmuJ667Pd9PWFXwnRqTn41evQy9/IH4tYYwGN361O85zz8UcZe0Mvkex4chbaRv7x9LYcDty43/4AWucyMy9cmQdWQ7tIDLRL+PYP83Y7dxE//giejuE76GfUWQcewSb9hN/lsHbAWx+0tvHU3YcGa+G7wfQYRUYPkcPQ4OnNL5Q/lf8bawYm6IrZJl2/ZCyDvFikmtqG7y8Eh4uhK86xontrOX9jrpi8Ov62p/woxdglx9SvgEfwD8n7qOeEf524wD+MbaGNpGt/FfEmnEu+sA4/jJCfxh5tVsPPnfEtRFyPIo86CpdDuZbXsyd/nUx/BAHF1Hv62nn69RBTCtjDC2/iDj0UnRz9yz82oFf+E/CQxyd01dHfgEO/y8d4f5i6nLj+VP4uxpfPwl/H0W+LnhbQxnkn7wAGSk71YJtH0Y+aFPl8Mh358n4x26wZ9A/fgG/9/IdGScZnybp++M/ogwyTeC7U+/nb3gv+2UxMYd7/3LzdmR7DbZ0SohJyLGHT+LodNKhL+MHlC0fxvfOKsYPkAfepir4rMFO89AJ1yT8lxK7xz9HG8g5gl7LGNNKj0CfwJ8Wwosr8++x+1VcI9xLgqXPxs8v5h5tVOObbr/CZpM3Yut7s+8T09/h9a3YE98cfTsxjbg1+il0j71Lr8f/t4PFXhPwNP5X6luJ7jcg49so18X9Q/hFGllu4/q9J//kUXgsps338R3fmH4F+McXMwcmzj8EnvsObU8n6ad/RLfcn5rGZ+DXwX6lNXxeRNs/g79HqNftR+SEE2nquhvZm/DtD6GzpXw/6MZ77jHujtEWc0QwDjIjhzuOuPXxd/pWaOh6/Gz87xJsWwpv/D15OeV+i27o52NubHoQ2jPQHTFhuqIYmchrqTvWDy+bsR9+N0096U7a/AVjwUnap37n98gAbuoRynMvzRU7HT26OfcI9/9BGcb1aTd/+RH0l/P50WKe8aMP/HdyFnwylo2gm/EX0c4gtuL+xGvghXtO9hyef//b+f+////7/7////v/v///+x/5V3aN9zu9pDBkUTr/Vp//5t85pz/ngZEXMd6fz3kyR3S+zXPNObo6r+VGndt5ls5P6dT5N+Y842epXp1v+sj7dG7zJfq+Que0HdE5sjp39MzrdT7QpTrPRp+v0Tlli27XuUH6/oL9+nxA56qp/suv0vlsd+g8wzt1bpc5t1fnDf5O/P24SnKU61y9J+scoBfovCydk/SCWyT/V3UenM7he+JT1O57dK7dAtWrc7aKvqxzlJ6o82K+632/89fiQ+eGNc3S+Y7LVe98nSvzkM7f0fnu79mrc6507uzli8WnzuFZVK5z116h84J0HvXpD0mPF+o8KJ17dr/O2XmzziOvWqJzhK4p0nnyOseoVOf8XazvP1W5PTpf7LDOzZN/fEzn/+3/oM7b/ZbOH/qCzr2ap3OGTped/6Tzhn6t85wq5H/fc3R+kM6tqpX+JMe9B3R+1GtVzzd0zuBqnRv2bJ3r9QGdD3dc50MNSv9ny5/F1y9v0vlNy6VHnUf31JOS9y06D6hE9v6s/PLFOn/oCToP/XeS+/3qP+ofz3i+6jlrlnA6N+pStfcmneOl75ffKL95vOx3ps4lu1nnG12lc+PSsrPOvS45qno/LPvonOwmnVN516DKLynycKov9W71v3+ov+5RP7tT/vgd9avzdN6Z/LFoQueqFikevFHneMq/75Wd71o=
*/