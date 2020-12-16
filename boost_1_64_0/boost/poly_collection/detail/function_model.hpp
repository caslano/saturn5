/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_FUNCTION_MODEL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_FUNCTION_MODEL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/core/addressof.hpp>
#include <boost/poly_collection/detail/callable_wrapper.hpp>
#include <boost/poly_collection/detail/callable_wrapper_iterator.hpp>
#include <boost/poly_collection/detail/is_invocable.hpp>
#include <boost/poly_collection/detail/segment_backend.hpp>
#include <boost/poly_collection/detail/split_segment.hpp>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* model for function_collection */

template<typename Signature>
struct function_model;

/* is_terminal defined out-class to allow for partial specialization */

template<typename T>
struct function_model_is_terminal:std::true_type{};

template<typename Signature>
struct function_model_is_terminal<callable_wrapper<Signature>>:
  std::false_type{};

template<typename R,typename... Args>
struct function_model<R(Args...)>
{
  using value_type=callable_wrapper<R(Args...)>;

  template<typename Callable>
  using is_implementation=is_invocable_r<R,Callable&,Args...>;

  template<typename T>
  using is_terminal=function_model_is_terminal<T>;

  template<typename T>
  static const std::type_info& subtypeid(const T&){return typeid(T);}

  template<typename Signature>
  static const std::type_info& subtypeid(
    const callable_wrapper<Signature>& f)
  {
    return f.target_type();
  }

  template<typename T>
  static void* subaddress(T& x){return boost::addressof(x);}

  template<typename T>
  static const void* subaddress(const T& x){return boost::addressof(x);}

  template<typename Signature>
  static void* subaddress(callable_wrapper<Signature>& f)
  {
    return f.data();
  }
  
  template<typename Signature>
  static const void* subaddress(const callable_wrapper<Signature>& f)
  {
    return f.data();
  }

  using base_iterator=callable_wrapper_iterator<value_type>;
  using const_base_iterator=callable_wrapper_iterator<const value_type>;
  using base_sentinel=value_type*;
  using const_base_sentinel=const value_type*;
  template<typename Callable>
  using iterator=Callable*;
  template<typename Callable>
  using const_iterator=const Callable*;
  template<typename Allocator>
  using segment_backend=detail::segment_backend<function_model,Allocator>;
  template<typename Callable,typename Allocator>
  using segment_backend_implementation=
    split_segment<function_model,Callable,Allocator>;

  static base_iterator nonconst_iterator(const_base_iterator it)
  {
    return base_iterator{
      const_cast<value_type*>(static_cast<const value_type*>(it))};
  }

  template<typename T>
  static iterator<T> nonconst_iterator(const_iterator<T> it)
  {
    return const_cast<iterator<T>>(it);
  }

private:
  template<typename,typename,typename>
  friend class split_segment;

  template<typename Callable>
  static value_type make_value_type(Callable& x){return value_type{x};}
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* function_model.hpp
ZXbsd9NStc3cdLvBZHc28WJG8P7gWVtyaMEWUraJ27+dtDRUB42VJ+pqEvztt1Pq6bi+qarGszZpjKF9BDuK5mvWyDhu06RR+x2mz1p0Wd9v84hFk9V92lctmmdt5gui7ZDcNVohQh5+lIXhNOGqLpB7zTbhRGXMyXjdKYh33X5dvmZ2DQ4Qjqx3zBZfEcYQ8Hb09nS6Q46l53PDOMaZ/ivd7KjPH79/7tmitl7xydwv36b7ngYV06n7Ct33kr/yyhWJilXlzk5DvyiHXlm+YnWisnJF8J7YtN8ecQ++9+wilhi5XuTSItY7LR1eTP16nyMX1xZgVoDROx0hTGCz54FRW+YHKvqTGcY+NzRaOoyFcD1DQ8MM/1nD+jqx+DbWwBJqi/Vtq47si1Ha5z00TIbD0yd/HPPis7WXiLEE3zX0yzyb8MBknTLFXjwoiLOTKi8+gh/0Cv3+2a0evy01bXGWq9riDbW5vz/Y6OvYxgR8tvr6zaWbnGGUy+QM2SGxexB/U1/x54XYn3fDTJmDdhmGYLvMuP+eCgqxxu1r/fdb9MKJ3nAxvlb+WZNX+qHIl2HqMz6N1zQMPbBZ/F2zRLd+d4UPhq80tqUe4b4/26/H/ESg/bsBI6+w8mBKewlf0M8mBwI6PdDnPb07uK8YRu6gMi0+zRMc2sWijf1ots23WS/A5/qS+/xX5KzfvzgbHSoXDf94k+Fx9EkBxuYxtiS4H46zZVa94pH3J6QTi5bqVDAkIaHn0e9kn1xMP2SD83Xf8QQfox6VhZg6SOR9un7IRgD++XWUWRgTt63fB5l8ahRde9mMDheF+YBj3uhVOA5+S/2G4gLrEXpPmN+u8OceXyiOWCeJxpZ/v7jgmoXQwfzoAR9r/z5BX5f1OzUjF1gyW86v3/AZqhRu/E5Tl8TObzfR6+VOVYbX6RCvUZIZXx6/O8AOpoBHSWb5/mQYH1W7/Q7WMiOn+Bfa5h/P7d0P//548C9/7lZpBg6mrPxmTTc+pXojMD1d1juHfw/Rs6UD+uSDOTaitDvrDOavHc/IsY8MI6e0fo9o5OmRuCB2PS7kt/pRMtPO2FNyyxPgtHOCSGm1U3ZXsR1z+NXGAV5mD357YvpkcTgOZ+uy35sbvz8aI5aGTF3jDwe60y+ISirrnffzLL6TxAxB7Dxr0opp/EZKJ4+ufZjP96MhO6WFsHK/jocsjH6VNeV3Fus3gqZtm8qPSbGHvF82RT7p8rsGp/WNANNr/LyjwykUR8wPDWh9Sf5GD7T7XMES+Llpo5y8JDr+RLcxusuJ6teRbZhxpfQvRSpD/LHGzPgbszqwXkXKPh+gf6jcaIjuNSm/5t/rwnREsNZW17zLXquNx5rWbdiwfkNtVYz1Ty3SDgwPdqYKLdjGrHXfA4ftumpiDdXVVVUb6+Onuu7b27Nj7YoY/qT6Hl1v1be8toHnchvW18d4KOstyBnc4cM2rq553bqqapada4VjrUc4u76VG5qr1zWtb26O1dUISdNrFztz571oIXofc7EMtYok53F/O/dvfr97P9XJxIHFrCEzaGTpl0MfF11jo8jkYdCvgH5rlu5luxpAs+8LdkArduItbJ1wk1rtP+UptPugmaSyra42W0cS3JFsHV438+OY6p+y6zdE/rlydUG/zyrb1+XdT3G//IacOrNtdXO/4wYbn/0dHNo6c97yBWZtLrw054iutTnRbYToWpsLL815zz33LfSeqW9e7uX4Zv/OfHtfVPOmxkZH77l5z0kb4lVdXYMEsHXJvp7e/bnvWb3BevYbb2lsqNmWaG6prcvbHzgGTnR2msZ5duy1cWO2vLaR8cBuU3V7a13oPYqbsxhvLtA=
*/