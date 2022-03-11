/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_SEGMENT_HPP
#define BOOST_POLY_COLLECTION_DETAIL_SEGMENT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* segment<Model,Allocator> encapsulates implementations of
 * Model::segment_backend virtual interface under a value-semantics type for
 * use by poly_collection. The techique is described by Sean Parent at slides
 * 157-205 of
 * https://github.com/sean-parent/sean-parent.github.com/wiki/
 *   presentations/2013-09-11-cpp-seasoning/cpp-seasoning.pdf
 * with one twist: when the type of the implementation can be known at compile
 * time, a downcast is done and non-virtual member functions (named with a nv_
 * prefix) are used: this increases the performance of some operations.
 */

template<typename Model,typename Allocator>
class segment
{
public:
  using value_type=typename Model::value_type;
  using allocator_type=Allocator; /* needed for uses-allocator construction */
  using base_iterator=typename Model::base_iterator;
  using const_base_iterator=typename Model::const_base_iterator;
  using base_sentinel=typename Model::base_sentinel;
  using const_base_sentinel=typename Model::const_base_sentinel;
  template<typename T>
  using iterator=typename Model::template iterator<T>;
  template<typename T>
  using const_iterator=typename Model::template const_iterator<T>;

  template<typename T>
  static segment make(const allocator_type& al)
  {
    return segment_backend_implementation<T>::make(al);
  }

  /* clones the implementation of x with no elements */

  static segment make_from_prototype(const segment& x,const allocator_type& al)
  {
    return {from_prototype{},x,al};
  }

  segment(const segment& x):
    pimpl{x.impl().copy()}{set_sentinel();}
  segment(segment&& x)=default;
  segment(const segment& x,const allocator_type& al):
    pimpl{x.impl().copy(al)}{set_sentinel();}

  /* TODO: try ptr-level move before impl().move() */
  segment(segment&& x,const allocator_type& al):
    pimpl{x.impl().move(al)}{set_sentinel();}

  segment& operator=(const segment& x)
  {
    pimpl=allocator_traits::propagate_on_container_copy_assignment::value?
      x.impl().copy():x.impl().copy(impl().get_allocator());
    set_sentinel();
    return *this;
  }
  
  segment& operator=(segment&& x)
  {
    pimpl=x.impl().move(
      allocator_traits::propagate_on_container_move_assignment::value?
      x.impl().get_allocator():impl().get_allocator());
    set_sentinel();
    return *this;
  }

  friend bool operator==(const segment& x,const segment& y)
  {
    if(typeid(*(x.pimpl))!=typeid(*(y.pimpl)))return false;
    else return x.impl().equal(y.impl());
  }

  friend bool operator!=(const segment& x,const segment& y){return !(x==y);}

  base_iterator        begin()const noexcept{return impl().begin();}
  template<typename U>
  base_iterator        begin()const noexcept{return impl<U>().nv_begin();}
  base_iterator        end()const noexcept{return impl().end();}
  template<typename U>
  base_iterator        end()const noexcept{return impl<U>().nv_end();}
  base_sentinel        sentinel()const noexcept{return snt;}
  bool                 empty()const noexcept{return impl().empty();}
  template<typename U>
  bool                 empty()const noexcept{return impl<U>().nv_empty();}
  std::size_t          size()const noexcept{return impl().size();}
  template<typename U>
  std::size_t          size()const noexcept{return impl<U>().nv_size();}
  std::size_t          max_size()const noexcept{return impl().max_size();}
  template<typename U>
  std::size_t          max_size()const noexcept
                         {return impl<U>().nv_max_size();}
  void                 reserve(std::size_t n){filter(impl().reserve(n));}
  template<typename U>
  void                 reserve(std::size_t n){filter(impl<U>().nv_reserve(n));}
  std::size_t          capacity()const noexcept{return impl().capacity();}
  template<typename U>
  std::size_t          capacity()const noexcept
                         {return impl<U>().nv_capacity();}
  void                 shrink_to_fit(){filter(impl().shrink_to_fit());}
  template<typename U>
  void                 shrink_to_fit(){filter(impl<U>().nv_shrink_to_fit());}

  template<typename U,typename Iterator,typename... Args>
  base_iterator emplace(Iterator it,Args&&... args)
  {
    return filter(impl<U>().nv_emplace(it,std::forward<Args>(args)...));
  }

  template<typename U,typename... Args>
  base_iterator emplace_back(Args&&... args)
  {
    return filter(impl<U>().nv_emplace_back(std::forward<Args>(args)...));
  }

  template<typename T>
  base_iterator push_back(const T& x)
  {
    return filter(impl().push_back(subaddress(x)));
  }

  template<
    typename T,
    typename std::enable_if<
      !std::is_lvalue_reference<T>::value&&!std::is_const<T>::value
    >::type* =nullptr
  >
  base_iterator push_back(T&& x)
  {
    return filter(impl().push_back_move(subaddress(x)));
  }

  template<typename U>
  base_iterator push_back_terminal(U&& x)
  {
    return filter(
      impl<typename std::decay<U>::type>().nv_push_back(std::forward<U>(x)));
  }

  template<typename T>
  base_iterator insert(const_base_iterator it,const T& x)
  {
    return filter(impl().insert(it,subaddress(x)));
  }

  template<typename U,typename T>
  base_iterator insert(const_iterator<U> it,const T& x)
  {
    return filter(
      impl<U>().nv_insert(it,*static_cast<const U*>(subaddress(x))));
  }

  template<
    typename T,
    typename std::enable_if<
      !std::is_lvalue_reference<T>::value&&!std::is_const<T>::value
    >::type* =nullptr
  >
  base_iterator insert(const_base_iterator it,T&& x)
  {
    return filter(impl().insert_move(it,subaddress(x)));
  }

  template<
    typename U,typename T,
    typename std::enable_if<
      !std::is_lvalue_reference<T>::value&&!std::is_const<T>::value
    >::type* =nullptr
  >
  base_iterator insert(const_iterator<U> it,T&& x)
  {
    return filter(
      impl<U>().nv_insert(it,std::move(*static_cast<U*>(subaddress(x)))));
  }

  template<typename InputIterator>
  base_iterator insert(InputIterator first,InputIterator last)
  {
    return filter(
      impl<typename std::iterator_traits<InputIterator>::value_type>().
        nv_insert(first,last));
  }

  template<typename InputIterator>
  base_iterator insert(
    const_base_iterator it,InputIterator first,InputIterator last)
  {
    return insert(
      const_iterator<
        typename std::iterator_traits<InputIterator>::value_type>(it),
      first,last);
  }

  template<typename U,typename InputIterator>
  base_iterator insert(
    const_iterator<U> it,InputIterator first,InputIterator last)
  {
    return filter(impl<U>().nv_insert(it,first,last));
  }

  base_iterator erase(const_base_iterator it)
  {
    return filter(impl().erase(it));
  }

  template<typename U>
  base_iterator erase(const_iterator<U> it)
  {
    return filter(impl<U>().nv_erase(it));
  }

  base_iterator erase(const_base_iterator f,const_base_iterator l)
  {
    return filter(impl().erase(f,l));
  }

  template<typename U>
  base_iterator erase(const_iterator<U> f,const_iterator<U> l)
  {
    return filter(impl<U>().nv_erase(f,l));
  }

  template<typename Iterator>
  base_iterator erase_till_end(Iterator f)
  {
    return filter(impl().erase_till_end(f));
  }

  template<typename Iterator>
  base_iterator erase_from_begin(Iterator l)
  {
    return filter(impl().erase_from_begin(l));
  }
  
  void                 clear()noexcept{filter(impl().clear());}
  template<typename U>
  void                 clear()noexcept{filter(impl<U>().nv_clear());}

private:
  using allocator_traits=std::allocator_traits<Allocator>;
  using segment_backend=typename Model::template segment_backend<Allocator>;
  template<typename Concrete>
  using segment_backend_implementation=typename Model::
    template segment_backend_implementation<Concrete,Allocator>;
  using segment_backend_unique_ptr=
    typename segment_backend::segment_backend_unique_ptr;
  using range=typename segment_backend::range;

  struct from_prototype{};

  segment(segment_backend_unique_ptr&& pimpl):
    pimpl{std::move(pimpl)}{set_sentinel();}
  segment(from_prototype,const segment& x,const allocator_type& al):
    pimpl{x.impl().empty_copy(al)}{set_sentinel();}

  segment_backend&       impl()noexcept{return *pimpl;}
  const segment_backend& impl()const noexcept{return *pimpl;}

  template<typename Concrete>
  segment_backend_implementation<Concrete>& impl()noexcept
  {
    return static_cast<segment_backend_implementation<Concrete>&>(impl());
  }

  template<typename Concrete>
  const segment_backend_implementation<Concrete>& impl()const noexcept
  {
    return
      static_cast<const segment_backend_implementation<Concrete>&>(impl());
  }

  template<typename T>
  static void*         subaddress(T& x){return Model::subaddress(x);}
  template<typename T>
  static const void*   subaddress(const T& x){return Model::subaddress(x);}

  void          set_sentinel(){filter(impl().end());}
  void          filter(base_sentinel x){snt=x;}
  base_iterator filter(const range& x){snt=x.second;return x.first;}

  segment_backend_unique_ptr pimpl;
  base_sentinel              snt;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* segment.hpp
EroI/PrK9v5enmWyRvY7EUSQYsqjebpvhCJlTaTMpFn7m/+kk0cd6rH++yHEToYgNfeGB+PzW4wlndjOC3aB5E5IXufLpi6uy0roAf6DNlt/piik+7H6wc3rgfLkdsGxnVC5ar68rt0eWQQUAX3P+1WVEUUZUTewGTed1QHW6t7FlrGcrc1u6RDeeW4qXxC1/Fvjhbusw9Mlk4l+Y2sAze8q5WWp0mNBbPgukV1vnoGRrmqbbJHueLWl283wfGkQJt13TQgpjvcPoY5OH+jAYhqn81upiGJbWINlZSNAZKFHfllbAAYs+dN1WiAfMjHnFRo73GoPtlSvvtTsqHwPwtYbh0B8eC4Zp4Jz2Jj3tB28bqVqN+YLY7W8FjuuJo34Tmb1ZEtEbi4HkgJ2yAqJCwZX9Ms1VtH/3+WAI+NbP/YIca/r1CuQ+qvBFsd7cGOnawuBqRIoVfANlYPrPHWRzsn5fJcO1iYXabuB5518JIYiMUft6MfbvaKe0zSlASO063XKf71DzcZzRYjUueyVEhiRZ2Gzat7sEmrhLl8Pu85qtBtQ54T5noHYwnN7ftMbc3TmdLfQLEYsOOSdiv94thCjjYGRXPn4lDiCi8RQrYl1S4yv9xZkxuz8mFHRBSyyEadZcVmTe9PM0TKu5eo0EEb45kPZAD1029uMtTzoqkwgNX3hVxrmA3TRanXy9wQolph2a3MLkekBdTWqqBARhRKCq9LKc7WQG1DBM6kk6U6/verL6oGbX2szsBFmGkx2FfA+fbc9RslO9MxOfD8QvQYpkkp4v/qe0t0KhGi51kC1HL1HbbPsAO1dBR29FkTgaZE+LA3oUDae3XMfoeuJyoPBiagxVEqvGgxC84Lqlpy9VMPxH9lzUXUwr7YvSRURpuy9WAJYeN5ko99ciguKypdo948lKqyYcbXbRhtWJ9dUp4maER+4+XAxjqGp5wNkXfodOhnq2EHPH2DWQM1eEZwENcaY1bhsveljHPk/WmFAiJQm6mtDG371Y8WZunDb72blBSj5yKtu8GFb9OCbyxRPBz5v78n0/5PMySrVg14e15Kf8KZT1evmPBaJdodcF2W717DMnXwGyyWCWsswzTKH8vVzWpVC9oWefVvp0yruM8HuITprxwGkI/v/L1N9PWoY1Q6d1u+sbUuLBlTJtrZou0L4X+wcapMiQ0TaibQWxmi9lvf/jmMZ4LV3CFScWlL3rUVyxv1Yx0WgjjeU1TTRRi8uFHpuUZXhRNYzUy9a7ytTLRaiTj3hAybqeLd0fNsJKzVl6SIoj3P6u32PWhW3WhP7VJ3cZw8B6vsDVPJxo89xLWFClmpdFKuSuXElL6qOqYU1w6HsbAwPVG4oAHBsh+sGvtSdD95wkbcEQAyB7SWy7lei77mQ7W9P70wPbT3sspb87M8SjoIutheOLi0fvMJa/+OMpDHt76UUq1DeK2GU5C4YgMQXt70B1K0/5WTK5WD+obK1zqvNYI87Ph2Zar/MLD5rA497PtVnPqTaC3LWUiv2WMkZ5LPaCCLI88KRqQYCyYId4A3NGo3gIqnbkezawNeauZ/1bO8hXQYGfYWgV8CdV5VtaiU1y7VxcHabpvFUCXSRhwKhh0aFrASnBxWGuVuVBvTG9hMot0hL6SySCkvn4QET0a/Z5p1dctri+3KEEYIZ63Y7PoVeC26k58tg/mpS28GYjpzbYD6z3/kpC6ZekY4g/QbO4Fnvir4PbZbyCsG+7KP5rumxH7oRwDcVrmrRi+0ySh67ejvlTEr0ZU4h3Cad2Q9iHOw8oeOS026QyWXUk9H88igf5skoY9Uuk9c1HsK28EK1zGUoGOrySV1i5VHg1oZn8aGHXzGxRZK2TH+AcPU3s6njDHXow8uuiINgmSA1Jm5Rv4m+QJztARGPycmv4czLG3BUrjy7Oh3Yr0QnNeUL715jlJV+QL1PJ8ESpJIeLxXZ5yG9UrzfG4y3zSe87kDkEEDdPEB5ly1ovYWl64xhAT/iZbfTdjKBh0oEZvZaFOAfVgxaktue3xc5vyeo722VwOn4gNoXBdXRZmN1HtFSXV7bBp3RimsMGxUCfJeH44lZQFX6qTfYk5nrdWElCHHW55hs1WJ+EBSoKklh4jpNf1YFN6nhqoGvlTRZ6hIwz1FKUunkzHrTHJ+CGttf73vevSEvv3FW4SQRNPY0IL2VpJhz9SomvisqQrUIkuzEvhC729nRVnjB9UWLJzy0R+kVxJ1afEYxgF+vZ951kaLI6Jpv8VcUVulSac8LhF69xXmD2mLv6Z7WtUpjPYiJ0AzGgHVYE+fySimMYAVv7VZkqnCz0vr8Yb8Wmx/EGwgSbjjbr1lJCPP1Qdm0COxFoPEsDThkv9G5HRwdaB6EcVhBwDR1n6tSRu1HshcCX+aQ5zTZx30KlwO0P/PYYYyXKO8IIcvb2l3p/RYj7aN3RPy0AhJM7iXOyXmI70dXqCnGUQs3rTrfQK+5yfmV5lV2/01w6xxtrLYeRXOWURAsYpWb95EG6pCRwcEm6C4Y08TZ59MKSH4XKcpXXEwpOabXhjzdpOiXxircJthVosilWB6oOi2rnYRa8anmNfLIEXAeIbvpCr+vkBmTG/L+HZddvR3h2RP70IYBYn5bg3ns4L6F882+blY2iYtXsgKQcHQeM3ST4kThMf1FMm0r6eCOB7ntgl5kmvGc9YIMQepPK/YCD2vErDJWYnWdHt3BYhtPoxCgMhZZVDCzKx7Jh/7NSq/8oYCAJ7UacKbgyYhIyKNlqErmMtR82Gg40HH/vfqHn9fh3JbuAVVyF8Y+mFHkVcy5S2EZEsuFWJFYic/Awpz/qPGlAmXLDnENlhl4eehccZ2t6l3l42co8YrepDvX++bUfjdYcwbrHt3svnfH64LYSn/ZU4AWakQWoIcX1ejkZVrcQCiPBhM5NtAlcrf0DtZCDr+1rV6e1+v8feMPYjnQjHeD37mL7rmxLqAYWKUfefhmXdzqR+zdIFC8xRz7FiUAoxp6NgRLWg+NwZ9DyJ8lS5KF/kP3o2PvkbRc/q4e/9Mg9q6CivG6glhS4Au8PtEGKIE8Qxyr/iJFXwnnGP4LBcV8G9nt0+HLsCec7S1vrNjRiGnpWo6EC+5rQFyYsdyONeTEQs5xyiAH9EmpfV0rO/x57Nz6NfbWYHesACuuwx9Yp2Se6GOooZTOnwCpxUBrAhyggBxOBtBfmWrLvcnj874qVf/zCm8rF/PWX+h9f6/FHkF/i+dSNYzdgGW1W5nQuHqwZdMKLLkhGn+wQUZwPoOvcn8+JIAn4EYYrm2ljyEK+4r+bSJA08Up1MYcOMBMIVKtQrbVbMU5ztptsxo8rLXq1aOv7l7mOX7T8Ood/ds7zgqZTX7DVV89wxJ/gaUA+kmsMd7Cosb+n6aU51Ccw8hnRWV0eiR+0afKRJDdnIXz0rELXe2JMmxtkJjRt1wR4BXhQz13f3aIsSinCATXOLqWC3BCfbDbj81Gky6wEZmMtDjJVkyqsJT7F+p36Xki4T7U7z1q6wAw4XWnwAtz9CIKeUJ9yiDKWWntjiP9u8lImdAru4ePRvVX74/rTUYLwK4CQa3rOvWCL32V6ZrcdAGsN4oLoL009EBS2UXMKJAScWdLZ09RqikJQJb5FhFRyk/R5cZbMHRZDWQ3HeaDejnDae5/wcv9LqMHGh7tNOI2LyGpi61bSuMTI5cOWMkxtmq6ERmiwGbFcml0kffkBHMkWIApP+GCUUP5LduQAg6ZUlTT8u+UbRmC1uLvG8kp6Z90ftg1U2iLNDngVIOrL9/6HdWfqK+S5ydHtGwejN3FzS3FPW8rZNNauuFiNeVS+oQDpKyyHSuZE0dH1FCGpYyvGnDT+KZhzYyf8satO/j4RO2ja29d+JLyBFBRxexkeH3e/VfvYaUjZ6DGm4EAzW/8mlqZAekPDwKCjSO+fSxeu9IrRoapjjRaV8l3uRHKO2zt8I4m4btdSK9yHKXCHohTQjSCEWysEFRi1FjkCR1HJHV90/Gxhgdg8TRaC1jc0TPgc8deJUalUpMAmeSK86vVYdcN+bvTYqyVN+PATGKkNczBuSCbxnprCQ9HCsebxpjo/V2FbUocw/elZP+RCE6XZL/HSciGjyoJgQpZWPR4yV3NGdn1rmW7xuxA/nKfbJX1K9X3HVpr0QBDJuAyQETFKfTjVzVSLRpxiMPs9T+O4pzi71vKeZI1o7ysC9waGLEbWJYm2jX9czTWLoD4rEyB40QNOBTD9OvP8v6aFPfgbOGonFySLo53O2s5g/mmX+mVINwgMDdlBxjoUaZkv+qK/NyWm4OdJPYONfya2xYQnYeNeajdddHIofsK5ZISXKBpnp8WRviyh2u0iU4jeTeUTqiHpValbFssoRkeS7Aan7tYnJvkZlxUJFs4h29LpLFa1u9sJQB8pAqQPbYTbweZngPo1fS6DEzpri4OME5+Y8/8InAySgx9Q1Kz663nRAnnwo3OAtb6EvE9/PE/vhIgxEBfK87BVMIvcFsyEFN4FZb0UPDIo/9puEZ/fiV8v4yhGWSdPiaHXafMZlU7mdhgcT5oJP9d6F8LRThP4JnuQytuPadtuOWubnJEVW/lXYPOfHnWbVCB34J4kUIaHF9wy9LczAr4+VcOvMZxifEA8Fr6blAF/+LcAFJiP+yAmGWKjiG+MLYnsdfDptyjgoLdahpKuDTcmwgRJXw3UKLNNtW4GxW829t20LZJNwqCrkBIHMHB5OqcqdkDZWGlXjl396Fb6Olw9aljEer79ME4PmJFUWWBpwjtjx59zElQpquDAXHl2FyyWavc0Dajy58jl4t4YJCntd8FcP8aCadNUAKgIEt55TJ/nj1h2pt3mKZzh71G2qc1EXHvgLhOc2rwGV5giyYvX0JPcovIdIzXDb47SZOsYOuf6rPvQ03/XnGb6Ts/RdSYeQmaRvGlUjgVUd7ptYyqz7bUUG5e+jVS/63gCHF7GLIlGyk2tayozMUHbp3QrG/TPZ4CJI+3sEhaMuATNIx1KmCe4tpjTJId8s+Nmha8XC5WtzU6of/7au8+jPWp/fm9icngNO4YuReEQrLiNrs1cem7rBSrSLPFtBhJPvWL3VvQJi0gm6j5w7BQEkGSKI6Jpb16hTZkCYPIvKGgqYPR2lZS86CCC619SQ586KR42KkRvN1n1TbCfj2KNy2qxM66af32fwAZgOZ/YCuE3nt4iD427jJM6GzsMF7RYDsCff6s/Zn5tOJ7E9zc9+k777JJu7j2xGbE+2NcaFeauAgRySOCsYvpL4t0S9gf3WmgDt6/i4380zj4jXdSiFrNy40uxX7pqBGPTLXGBhaF58caXCDP2I9aSM6yecMcrw5DLvYGi1suQI4eHF9Hc9yBXYyk1bNpxw2DIflFBG2FkujiVlW/zUZXU+ljtcqWrWBFkNv+9nOJK+LRCed+IU5aXvfJw86+CEEqKxkpmuGvbCaprtIepuLbLpTe/KmgytE1fbCnUEQxjsSaEe7gt1eII+XW5BK1KuPMuDP8qiq9vvPMprPBpU/RdxrWhv5b9EOaSWu481s2LUbzphFD6enShrh03u1VI5iWtXSPnsPYF7jKYNrC/NSCeRRKDQMR3Wy5vjg5PjvlCTr2eNuFml13UZMn0Qr9N0dS2iIPd0h3l7Jd8UXA3hVz4DNNblJAO2WDJ6E/OC6fOb8YfR2MBAxIOOMSykCtOrI6IjCg1PVVEvYZU4MM5RkbzPZqfhBASDONLi3S68DYv3+IKPXjjM8aLRTDyLOAYVfy8DAFmAIDoE9iTOWHDN26EBOl4v3oY5+yOAgWVVMZEQhvueQolXBbuov4xRtv/7KaALsSzTdcsf3jXKvbILwsei6QskNA4wV9lwqlNZA4pHEKFP6sFyG77Pkbjoxif2+fdbfHvmi8Neh8nu7iEM3pSe5RdcxDHZvsRMeVv5QY12ycF0QdTGXuIwGVYI1ruguEV7ajjX94b7RoTRPSI0U+df9RVP9S+Ae6DE7EoXMWrQlE5yd+MFsf/SZNraVSuQX4mP95+4s/Us19qrCsS3/sdT/J/eZPuXpdOQ/doLxztQVvm3XJ4DxGeqvvJ0aynusz/nMrNCqC69xcGBYHhSNjx9rO5NHERuV1DZoxktL7/L7az1I88a+8hrsBOvdfDGkUS3UXgvJ4+2lvDuHM08oX0ZI7Yas2dV/30NTjHz9YkIXgpogpvJtcWZDTn/Vi7xYhkC2Jmcf3FLPb4tLqlRjdwOrWC9RKkiwkoYwnL0H78BC8jTq/JUunbHLVO+7InGhicqdzT5fI1do8Mp9bi8rbMkRncq1rmhsd1Rwde5d2+9tNNidHRF6FSFSW9FNTyxpIUVpTOognpBRNtdcgaO6FKmWraPkYFDNRbCWISUqJKs9QT/c/PjAuRMjJQemok0OAXDhcpn2bjgDnxN+JF7P102JZTihjGqJ0n/Ckj6ifVDHpiSC3mQj/9B7pC/dm9+XEmoQ3edTOZI1HfnXBSjmsmcYMBgGhpuj1nV8yElpcpHmNp2Rv5WYzXmrsZ8K3hDpRajRFduRtkQ2AazWqqmdSmaQ327g09wFaS5c9rD/juJJsUXcZVsT7E7gR5ht/nj/VtGqZ8FBp+HC5ARv7Z3mupnARsLlplRXmD/b+H+xm5wWzHLBDmsTR4IALf2g1GzOrXHjT8GvJG6vQGvEmQ0DczdFrGI84wSzLz2SENhy8cMUwMZ9Snei8UNBW4EMmF6xv5h0ukJsIMtHnlF/JE5E6OCwteVlKDUWrhW2tGm21hG6y/u73gKv7hTkkX5lCd5Xq+5Kyov/Ms+r83Ob2+MruwVpMEOaIkikhVpMv5JOkF+GoX+n22KTw/mOyTW8qj3WYBLKPYdVVdZehny1fW/w3rkK/l93Otlzbq5uYvvGG7fuDXdfl5Vh7Ug+Miv0m/vWS24bPecfONXGsN2fsznPecFkOFPrDWysSh9JGuIw7IW1qVjvzTZWgJmNwZ14zd/wcT87IqBOaJfy3tttk4raIxCvsIyfNBsJVzgDejXNnaFax8bsSB+9A+DgiME9juOZ87cb1k3LdJWdMfNU0LXopHiW/kaTzlByiWmriQl9Q9Y+Mf3Kr/Qqwkeh36nuxE/La3dRF6TlLvbrhmk21wsabyIjq5ZdSvboHox8rZuPxxY84OahawcMXCvDAZQpwNdR3Hj9WEDU5E0/AGXnaTooR9ekz0enNkDUSb1CVgmHk7n03S6FnJ9SRV0THWcygyWf0yuPrdyGixoQP68ieJCElvjv6p1P3o7f0eGfpK1N/8XWu0C5HvZ+quhVfw8n4HCpthBeh8p1rYRBTqHRKsg90GcRNpLGPsZNxczOcit482QmjuOytTROV3giHpj9K8kGG1wFPpVlln1hv27BC2RKufwTsX9PQ2gFxQkpFUVcrghVBwh4kkJuEL7m0hLWUbkMarFOjc+EjMPFtmvqpYQf4cnZj1OUFS4bVcLNNtrxFASKuUe9peMhAOrueZUf08pSS2GgyMTbPHRn7h4EIqbxFcLykh7PHOrOukrGnObje22k47uKL8Nh6VgmR97NKYMQmge3xKOrcgVfEYFyBEmGA7jF2Ngz4l9M1kxHPJtk2Zw6YUzxyiGtFRWy1ItrUc2DM/eqSDkjSn8W8kPQ6sULiG47nUBnn1N4fJwROgSnzUo7wIfodV+xcRGvucj+ujO5Z1DuCIZUKjhfF8tCOOB9DrAzxQDwyXgAKWaOLeblvPj3I30sL5jS6Qx210AbqfRoCy5zXsOr5Qo1b8xWv2CmMQgMBT4V7DJigBJWkhd0BMdKKHbWOpH9t3jmXGOHGuCaV2HKukQm4594ZZi4BIk0i3J/+rxwFTzWRxxQezeNQ1MmIz5KgByna2buZwThOenGmHmZLwgfeOGKiyRJY21E2JO0hbpMtAZD7qbto3XFCcKXMccKZU6b8ffA8AQ/QM+usKq8U6NRCOCXBLxcBtGF7TlZACU1128Ha1rsObb7xKVtpvpUPCbJ6oX5JRReyLo6EBLvv1w505CX8I7Whqt3jpfva7qKBXJdoOjME+w1ezkbxU9Ug9ap3rrlEKU2P1Ru95tIXwnOKCvK1jQgIOrRLGG/v04rIPeNZ99IJeEDLdwkxzZxns6DTacBCfxZQ3t1EYornBCfnIUeebvaCceft76kZ6DkMz8b9Zf6IaYfZ31M10LMfDgfZ74tGN2/dKVn1QkgJo0QbC8N/2iY0v+KdsE1IvLWtg2ADxcP4S/GzDNBDXukvUuGcKGGkeQgQAB/LJs7cbkJY1LzC49axgNmEdwoeeF1XzDeyvLN8HF0+ptYRtbgjZ1kaRZ2HN58BAy33NV1y00maQnfGX3TpV9l2ARTzvun1XOGfE6h6OzN+B4d624Y/fArunM2B9JMq+E9UCpCCwXKpdEv+MfzZK9Zps9dwdnpwzbvs/tfhl6zdw17ekGIb2m6MXUZxpu8vdK94e4X4gDk/J7t43dzoV+ZarxHD8RPD7A5BgRB8c6bcvKClXzferljBPaBUpU0TpOhSU8rcMpF4TKcAZofF+MLjd2OiCel+7CRJaFJzwaItFv3c9vT0xIFL064bWlfqwT5BJ1zoENq5xadaz3hkLB83qdqJ/KE+7efnw7N4bYFjdme77WPLEFQu7+4R8G9iPB9qf7NrhhNpk8+iwZ18oiWKh+BiHT37GMeLUIyvwaNupTPnfESD4JEHjU7T4W74dmVQhxFL3/8CCcH+na4OAXL+EE6os+QQ02uw335dRISPucOdeNBO/5flI+EnP9jeb6fyEINYfzTzWwJDetDO7PU7D1WTwV6xR+b2kzvDiaZssJrc7dDTctPH3cgAd7DOz2XoINToFW9nCQ/VnccCZdPh/d4Oivizd/69N8hy0no2ZOSUSDH0RsN6zPQs0bgaFCr+DCvCm0h3u4BdswVEj4JxncoPz/KPs3YGf6jnaaYoF9rvskDv476kXYIs9Yy6218C50LlsOFlltr2CMi9S9AkeY2Wn5YBN/cBvgHEhrBhRHEIzzk4KUpLAZVTxW+kDqZbF4+wXqklNCSq6jD5LrY7Vy5VIYpt0r8qOmbkWFFeCyQIXKzlvxzERGWU2Hjdk9coH3DaV1CREvxk4OUjmZMY+V3y40KETRcSLbtdkfcIzNn4PNaoQuE=
*/