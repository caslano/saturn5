/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_SERIALIZATION_HELPER_HPP
#define BOOST_FLYWEIGHT_DETAIL_SERIALIZATION_HELPER_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <vector>

namespace boost{

namespace flyweights{

namespace detail{

/* The serialization helpers for flyweight<T> map numerical IDs to
 * flyweight exemplars --an exemplar is the flyweight object
 * associated to a given value that appears first on the serialization
 * stream, so that subsequent equivalent flyweight objects will be made
 * to refer to it during the serialization process.
 */

template<typename Flyweight>
struct flyweight_value_address
{
  typedef const typename Flyweight::value_type* result_type;

  result_type operator()(const Flyweight& x)const{return &x.get();}
};

template<typename Flyweight>
class save_helper:private noncopyable
{
  typedef multi_index::multi_index_container<
    Flyweight,
    multi_index::indexed_by<
      multi_index::random_access<>,
      multi_index::hashed_unique<flyweight_value_address<Flyweight> >
    >
  > table;

public:

  typedef typename table::size_type size_type;

  size_type size()const{return t.size();}

  size_type find(const Flyweight& x)const
  {
    return multi_index::project<0>(t,multi_index::get<1>(t).find(&x.get()))
             -t.begin();
  }

  void push_back(const Flyweight& x){t.push_back(x);}
  
private:
  table t;
};

template<typename Flyweight>
class load_helper:private noncopyable
{
  typedef std::vector<Flyweight> table;

public:

  typedef typename table::size_type size_type;

  size_type size()const{return t.size();}

  Flyweight operator[](size_type n)const{return t[n];}

  void push_back(const Flyweight& x){t.push_back(x);}
  
private:
  table t;
};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* serialization_helper.hpp
66KufoPoyvOEzt6h8j5EFF+f0FY5zttoC1WrWzbTqkXLyraJiUIcaUtzXQtWEle3tu6C6gythCFW5k38Hy9FpvHQdyA5n2nwE40IqWeS7pIpgX01/UD6jQnE6t5VxyawTVQ/d9K0j+Fd9H8sa0BcMtZTys4yzMcrLhQbKOXDmDxsKrZakJOLXndsjs5DuG4ImLOe0nZG5SFkNwTN2UBpH7ryCq9jaZUq5rxBaUecXkzrlLSuejWZBoSOZ2ntawH1yG82MJ6Vi4MPtywZufAK2prduYXbgbWmJxTWtn4AyjoMGYT8pSZNewkerQIVosrOkzS7UGHfIdnfcswtWsApW6DsFtqPHNmgVNcfqqNhBtsW1vKIOLagMhSckBWlF4wGXVugGmYm+Sqh7/JPnXrmN/F8QxLArBveUCo4/X6x7uLqxmv/9CFnd3+8BNRFUt+esNnW/dg7EUbVd/eIsn0fN1Otb/EmW/X99oOpvsMuO/ZU7xKYNn0nr8WS/x9U/jfZO2+4gwMpN4T3RXD+0tjMT7zgJ5L9PltpPz/JUMHGe8xBp/RCP/6bWO6F/i7U9MgghpXoUUgV9wSKyQ+XT5bvAOUxHsoRJ0+IBvtbwJ6iYB8gSydBaSk7S7QP/MJw3C1xbI49qhcj65Nu8l1PaynTzMFcFn6i1372a1H73N3FF3A30M5PnlU81zFopkjnM4PEscwI8TBOPIxycN8Ga9gdGX8xj4ca3jcG5mkNk4VvjGtdKEcqWRMhy+yirYZsKh5x7UGR6eExzs7TScKPX+FJwj/xJGGRPEl443BxqLOLjLXhnF1cttbg7KLKWuHsIh761f8q0GuiJmlafTqWGgJ/9ExyVinDyR6ntmHTpYx1S8S7yTqiNSN+hpH484csiL9jTTjir19jIP6aNYL4XmWA+DNO61WGTt1z5GxeWJGi4j7YFE90ZPLxinReNCpvNvO3xzTNO7TZYHjAjqhWifMjyfR1oHlB5HjqdD8aydxugicFbc8odlTUK4TRh1aHY9S32sDo6NWC0VtigNFy6Ixu6u9kUDCC2+/XomZ+/0ts5oXGZn4SDiX8eJ+EgmPOBWt5HLCTwT5nEfS4Lx6f/glPBc0pTCH5dUsnlA8wlE8bUeYiymnMFT20gnJ5iALGNSLQbAaaYwSNA9BALyk/S6/u8hNUc0bhbRz5LaqREN3yUw10Jr4OvQ2UYKZW/k14EtkMjdb4LCWN0n2dvYWfDs0A5PzyHXgXX+oT5Xl1f0dstSN/MH156oniS68vz7NaP2e6Mf6Nn6/kMXO+LSsu0Y1y06zA+/hfx/DLAl85bu68sWp1ct54OXfQuAAzcH0dj+P4Gm4ffAzHMQ7hDfPlOM75GKrjqNTPeuVK+VlTpmH1W6nXTx/34yvFxz3DyYxznylLF20kkR6t0Sk2Mom4WU6VzgJG5xCic+9nSOdII53//MiazqiS6PzxRTOd/3lR0PkZGRH/Eg/T0LvxrFm3F5ma9e3LqFnTeLMuMTTrcCK3NiP3KSO5J/Zbk9vvxRLI7RxCbgdJbiaR2yOeTACQEmxLLKrl7EQFP7XhXUTUI58iUYuNRPUPQ9SmFSUQtWqFmajlKwRRi4LM6PG1OLRRjGNt2O1TUxtOqEpteFOcYkCCJZbzxkya9izi6rGDRsdyGh1qCeJsLHH28lGajQ2cPfChNWdfLS+Bs4+Wmzl7f7ngbMt5xtkR/t05meFINH19dwIF6sAOJq+6O5Hx6EXJQyVjyuZoXENzcQ1+B1CqN+4GWBHcqiSC64YQXEMS7AHs/mi30rSFDviXl5Y7O9ft9C6QTVsYl7N+Bt2pG16M+Payu60fFRkMeZKmPqx0k+qHFHU=
*/