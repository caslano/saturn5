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
85SYfBtTgdldohtV7rpeOz+xSHB4pzHuKYLAuHe2+ad6vEfm4JWnmxb/DHIFau8AF0epOt9J+FRkTZ4H7d16Kn8vtZgJ8V/wvfPqZS6gW6yrPZi5fztZaLCTEJVFglwoUMnVwg+f3c1D2noN2EcpZf4DZCTgV45OmnBQG5viC1Yx1uBEDQ+OmxLcOvYLSwPZugy1mif6S0Qy42WizLzZXVjVzSJ18TKTOViR2cOTSS2cb+17HOa4bwZE9Qem7PUQ4krUxP1CZjOUAMt8LvVJinpwYCAOKRqHXb3CMUf0znvuS3d3lH+I17juNAQg+mihiT4S0nR+ZpteYhAmRgg1Nge3RA92rhVFP7WHfh47U2O5EYYf0GcMuWPvuP8Tfk7csiX2dG1hV0eX/pifstLgxHz7YLz7sSC7AsUCq+KgvYB10A8lWfv3yjgqpSVHxguSKXgFXBCBgnJwkLgjbrRJbowpU+pXTH141/TQ8nfPPAiQIhU4hJp0+xZFde7UTGh29AhvY2m083gro0HYHHopEajpXYuu/mhEjixKvk1wG08qlfsYK7Z+/ay/80m/4VX9YLbBtXv6aNRn2Mk+9bCzFqEVIAZ6owdOzLHJ/njY+9bWO2TP2O3Uvd3D0b/C3ks/KO0M6nYnRlfR3xwrTBmfbry+vfJvr46hNJnVEq4lRcdzvEPf97Mm9p99pda7CuE2b7egqUq9vCretbhqtV18pFMBolUiH6xeOjnguQHViFpwhvk5jwb2Txgj2dTET7vSJWkYzWvCmqbbiu5oNn1kG690WOHSbm+3X+Mtpbq+wza+ElmjxPiqtVVWyxwRFe046qcDZpssLd987ZYXQbXFdyU4vm9pqXWaSh8dJZJhuYNS7uCKRjQtrea+zKEGjqCd5S6wid3HC4nQ9P7FXUHiPVHveGJEOxOWy6Lz+itzeVZ1BirMaKMpy6xN0mN4cdMOxgloc7LDPBGXvmWy+R43YoVlXpSWzDKWhEdkwMgoOOjULkK+b6NfBclJcT53hlB0DCZygjZHwyeDEhB9aXjamN+sOoUtaNx6yauoGjs9eoZeKKb8jl8YyPuwpKmy56x8km6U6tvP0n/sG6RjIdoMAnEBcWbuS0tWpdbtiOVmwSHYeY72OI5d53OsYU0sXPDl9GffFE1CGzbBBot8OUd5L7yG3DGl7s1flAXTO7Pvhf37NezdiMP+C0BB04HV6rE9Y6BVy8avQmxS4qMsLdypmEU54OQr/jzwGuaFc2UIF+BRqol7XtOr3jCFCzvWlF66Z9RbQTo0Fnk2RM+A86qCBwp2wAMEq5rl8qvtgGyExBTor54ytLsflY4LRccCazSi2wLWx5puu9QndOeHyfp3MSqEOi53e1UPZQXOW8O9pI+PsL3VNFp2uWzwjGqV6BIXkXJ4rB4hXOTxUgx7Ce0Hk+sWLCVcvvcyHueYkEGtqd3nu8lbszW6mNFCberc2Q0Jz7C/tLsTl2O04umLgd6A+wHwlcMnyxFwRHxLNJTwpJvkhqak5CP47Ez2tomUiAteEnaxyhZWQR5LKNOBLWZ6mxMW3uCLCziqyGhnApH8dzQIzGt4UR5HuO1Oa+2ZQBH+1hibbqwwi1VuRuMb8xCHwjFxmwuIxdiX2WMn8BEduyJ6QzoMV4mofmmOQUEPrWlXmDEQFQosYH4boY1RlB+d1YjSYFRHhzx/74tmaIvs/N/5c3UhbwK/3oEHW1NFIWAvpH0at0qIPMISbXLyheoqjuVYvw8DnvHmNm0jV93FTUq/H2RPbeMg/bJxARf7MasZ3YsG3AvtU040sRENA6uuksOEDJ6dxMdc0gUAfHJZkCLEpLyiMy3yJV5FrbL3Zkaj7/G/dgBk2q92xmC559Yu+GxbRdrCgnM33yzrJQy1929ssYrdYOBnR5QHvZvOuh8f6FqUqBSBMD4QfJ5/v+VsUudpGBxW8DjLJ1XQdN/Kef8sIYawr3MMeC/p47kwTgeiIeWBvW8h6nrSaRQX9bG99h1e3rWieEA1HvMIwSyyVNGCQIueZipDhnttf8HyrOsp7Au4j4HuecsrMChwWSuElvknrGJy5CB9v0s9rNOrLmwX5ykWZ68pxusdeFPZI8q/j1YI3BCemQjt2J3m6XqMD+m6MQr8kRwMTdRhP7MgWGoZJDwRzPx3Edejd0sS0j0gN2RI3SRuh8kc9IIzAVdNsHZSjDhHPbSAkFiAmqgJCwco9HbFW1HzR7X+iX17kFsS9hlZRDLEbizQMTYq6r2fmA0F7x9OLJW/NFVd0UP9labLFow3f+lO5WGoEu/yEWAv55K8XfRMUnbCorhPCNOL180yhxSSdhArDfbuH+8GkpX1c4U5KeG3SUAfcXm8NFi/hEnR12uhFTTYQDSp6yFbBzK02IB5XI7N2AU+1OvzbmXzQ5V7UvqPRTxi6GBA1VLjJXFMVOjpkrgDuhnOmckeEMRD0NHXU2jt/dNZh4i3qBCk3Q8Fmn6KcC2oih1n844X5kdE7dtWg8jaOl807wKBmNO7fJqdcWmkzysZfQ0hR5iXAG4tGuzqAMiAIEadNKNnezHdG0lYCXL/QPt29lM1WIIer5s5sXUFdRDiBytLjMPgkceOm9TWew5zy6bbSLLaiYpmCxFcll7y0GYTE4n4IWvL+Z0urEc3v8pVDuKbcfFHZR2uiciOVkZ7CWPA2XqLEBt25/0oIX+ajgy9jagtqJVwAFWUnODKP6EMIZo1d2O6AODdpcIUhJs3s3Vy/e1JyUGl0ecNx/SScs7BOIRMzXcaiRPZCpXkRlOCFJc1ncG0MdLzj6uOANRwbpOS0D+fcxVVSpHAcJRfWY2CnRGZLRCAFl+U4352M4SexVJlnMZVpNMakgTKIpRByp3fYwKOSfKpKIJaebQOsS6PudHI40gwtf/MTt5GvQjg0r6JTl8cSwtEoT8Q+ev8tJ0Efea7MQ7dl+gg+YOTzi46Ja2wtjFjqTk8HCWTE6YBvS0bU2Hs6gnQUpPPhzTYfDPQh7SPe6Ck18Q54WW2Iwgsyb1GNFFIT6Bs5Q11n2aa60gtc8OAHRLPbsFjumh21tyxvMo8kYEBYzb6DMh1hfaxWcGcTdEo4awImc3o3EB62V0vNSU/anxdTJ83V858f0B1kL/qgnafxFsLUhp1N3CeSnpuJV9waPzIrP4ep2Vy1l+P+0GRcQgaMxNTB4poY8SzxUQ103QHbt0JM+ZJ3VuEs1/eQa+UWnARDenibbHav+vbJEXcQCGjoxfgnsm+XAIQdaBraLR0RoE8Dwi4cQMEh55ZDTC0JeMWwqpYTJZ8Z4FElLvcq12gFH4qFAKgwO45/oj0l7w+wjDMEPAGru7essztlVroWUrJjd/NumaMOQUVomKKIfbq2ITmHK9Q7o9pNm946QmRIyPaluwpRWqVAH4VdHVERAheYPHxOp3IEU7JCYlDzm/h0zu5wlFE/5nfmoeZVwBOgBRnE2cL+0O0RXCb7Zj9M/RzrH3y7L7yL9K7o4bP8ubm25pMi5BNcBwqtbG80YhEfWYrN6j9oYbY8PSoUhO/A+nLuy5gX1M725jpSbUUZx4TbUNToYZ6DayweAoOPcHMiLY7Samo2lxPQ59fwwd0nY4y9EdeyswQz56McQXVWZ30iZooHVA4Yl/ErMCJpBRRPCdEcjMPHVeQzxAfjjiCT2MEDqNNWBQkC16fzye1tak9cCdFB9Tn/K5BwTK8RD3e9M/qxiVGoADEtaywEZLmM/0KX7cu8dcy4bG2Uo+Ya0yeYMu2xTcpOSkEJFTD4LnpLnMvkwIj90LiK1M7RvnI4WPAlauAh+92ZpqNkFaiIZFX21XT325tpT4lshGGz4lNoaf+qjIYgHHLdaf15W83ux+nh68tMpLkxsYR3Z7u95IB2+AlUrTNjvIsTj5iGyZtPh/sZa5/M/TW225unTH1qazUOinHjba8WNGZDwttXPA2hNHF+bVSKB4xFec0rCWZj0o/F16EzV5FjyILm63PbSLXm0He9W05gPrRmRiRA4lZe9KSUePS4xso96n63wsM7AflnBu8HbtLnA7QWaMNOi9lyePedn/kxmm4mtMiklnlUn0073PD7pIdmiZDZhIGRhWs0cGVlhr1u2cgpr2dpcbScYmu82bZNzDy2gdYuPn/sbjZvRXnQFgSyIhh3UsvHAZ/MPeJTgbMHXa1XvEmnkhA2sf2idaB+a7VFHe+CEFNeF/qbLNXbOg4ueviHZBYHoVRIEEXC07TPB1J1msLJmur13cQLE2wdz+JpbvjJMANjhSBQooEk8Z1x6WjQCa1nZm+cpuGS+3UJgja0kpB7J6fdr7qH9+sq3UIS0KNwU3fss9pgbZVBPuUlw+Dm3RibBQrNShST0UoEmUcEZVOwuKkLz1Mhu80os0sI3FonRVCA67zDmiam3VopthpdD9wsj/zZPZ02+ITRS8FGycsQnNiNWvwhs3Gtts1jLEePiy5/51uHQ1SSjkYQDxs1fZMNndjsOfyF0ovU94IZS5XWhRPJ8H2Foxnc4WY+SOZ/lml+/14K79xibRW9YFyyEcXWdQXR/ZmVFzMiJVROiwmHlcUXjlYeLotA37rg5N/njvwmHKZYIlev/P7APtVeBH9suyKbRP9SMJo2KTPCJys0YoaoKJGr4kkoGybdf51M/WmSQic/BtS/uPJF6v8x6V3iLD5qEHBvaotF+8SqD6BtvzVLYugl1sqbdKzGFLxZVVr3ZPU8AYMMW1il2R0X9wOxwDPuMG8Q7hZAdrlBLuSLhtWiI4IUaQAEXkmwugvY28CgsCYqDYeM2D4KPRmaHgqiG0AxcCw2E3Ulavs7ULhnWDEEKnuM7XdXaENkFkGqtid5t3jRxgUha3UkaqiHAPmyBsbH/Ib2xH5MuCAMyskTIVUOs/+xAs3Yxpdz597mbtpB45CDMgfk/QNM5f2zWKlsg+dOh2+uQqH7D8bcXdBa5TOYRqpw2lB2DoXF0zAvUCr4TxBzZWmyaug2stMI6Td9wnGQfjaieB9FE9eawRUzirvSp/l/J/1egT36/2LsrBGUlHcfJFzdWNonQ2EQ47LzYplnj4Yn5MsNI88mI8qSZRc4T2gI7wj7v6j+5iA5k3vmkGDaJ312O+DzmkyXUrY5UkX/Jie/cArEgvBn99Bx+0LLlsS+8Wg2R9+Y0JXCIEVtDYiUDGsV0kt0UvWdsd4aRrt+MfCF8bB0fiTaD1Tvmz541Lvy/ysgaL1w13aLRvBg00ygqUO2SJvTTWCLhYVKEPF/9phFn9eF7zCwIGVma+lPyI1DUDY1S6gJ6COyPWotYSKz9+PV5ljaNPY6NU2EzgkLOkuNnIrIXDbchzWzZQjF8r9DDpdVc6+smRKo41EIvOgCLJiLh0O8W5yOiEsOqsAAYxuDYrRLJaMGo1VACmaZ+7CfGN9EbF7kXiEg2TijB6Qbzbk9uREnhJQr5Nouz4oi2Y0Mb7yWTUKCVC7j0ZQ6zWJHOHH78Ey+Dz4WrpnkmOcAiWMzIid1Vq4WYYtKbtW5KSgMy1a9FWryNFBppMWfcySz1VB7YMuwXK8YNcA1Um9P4H+zlSE2fLzFC0croVPj9RrytV7oLtrCd3guRctbTDsEl9OzCHAYCNfUfzNYzsaGs6EbikMflNHJ7anYgL1ASYRTV/805CzrmUu4XZDMyepQi3OlaMPFjeEkbgea6A/EtRp1JAKZpQ1DzU2AV46jp8zaWMACDZwOObnTB3Qe7N9F1U/9E9FLEuTCwpVcdROLYq5DMCz1TfmbtsaUidD0FEd743GY+gd0gw9CbBd1mi+8m8/EuFGW/2aUBMO9RBN0wWLfy6rzNliXr8rCY+pEEko35gwZBCcfIs3a+jLm4qK3IkjfOGey+hjsiinGam/VD8ctDJj08Rk90BF7lBAUpUNwnjF9lhaUdlgF6RResTllllknUDTshjBHBr3ZkX09D8d5iUiwcX3uW4+jyTqmbIg3dxp+FEXBgbkrSFAf2ZyZDsFcJ/tneTvz7E+ESxBHYlTyX9bIDpD06MJTp7HKa9Byl3nZrA8NYU1ZioHohkTwu7xFdN5QvWUaF8iYJVbJ6hS/H0CKoEmFbr5gyLroHCauFmWDdBxWQFXA+8PdyAb/Ta8kbxUaKkAACz/0ypAI642po5SlkgkugmCf0Tn1HR5Lp6Jg9cCfPBMDsrpt37gHwnYTjueOxe+EP+ut07/kw5E1nu6Sr7b0k9awBoNs4K9Z7HoTCj0eTUCroFfceLhGX75d3sBBmwrkKq8eJmwbHe6JPU2qmrm0yc5aa1m/zAi3zg9J/c2CUseTaeaxGO34JEY1B8R99R7PVnABk3CwjuU4ZpCabInkz32eV5Q8l30ec9/VlmrwQgji9BFfA7Rlu8zUu0ZRTpMDEfNjpcmU3j4DaiDEDk240Q5wSpWtLYuq88dQEyBLWU8xOmNbxCalLnRRlGfXkFzpyOrXe07kl5CmOffH/SKbtB1nt2tlRCldTgxZXPXvgLqec1YFZAdKpHAG9C3DJ/ODVRxDvMmnHS3pDU/CIV7YzN2QwyqU+TQQ8zgFLdUy1/WE9FY63Gfz5/OZzUmJbrm70o/xs8YChwBCgGTUinE6Az8vfdqnYDCFr2KTXTZj7TjQEgupMPePg5T0hB+/PG+wG9eS2JSUWzmX2iqnsvbkye1N6OF/eg87MXRowInBC/rRs46j8BdALrh7NN6hNSE1/J1xXmAhBS5ZmZK+CwA7cpZmVI+XZgz05q8A/RjhgPM72mwvulPmyMfq+iJhDz+gDyXnH8Kb6LO2A05xkmRZUQ7APvGA7Unp9B2PnZrxg2nAJ0QR6cl1Yt9eY20ThZE8TN3GHsllHH3Xro+TUPFqG0SmUlKcJdyR/7CquRuqJwWMllTJPzwzmaWVcFswFM4n0e1YLZeQXytHxqUzi/JmUGu6mIEwl3k+sh6XsiCs8WeHMtUeJpWDCYRq7eKvyRif/nNMPEvijpEN8WD0hg+SMckXsanKOlMikNIsx+wJ+yUhMCPNqLOL6lo+p9DMlM98vwWxOE1zRXJHPZpu9N4mKSOrcRZAZH5ik7WGN/HIBLvwXvtBoJmeR168VB69qAqruqQxMuuWu/heNpeEokQGp551vQu//r4jCKLweT8B4HrCl+b3wc47GeKkYZkBuNBvmbJ5YSgpHHzdGTGun/1AQAhC/zJVfcgsOyV8uC47nGFCEcikxUzMQ8jjXG5rO9Obml+RuADG9gIzE+/HuVVovfnqiP51QafpEXIfD0alq6t3nrmiEqIrlajApP0jSNnTuZ19Q4NihJPZQcum1Jxb2UOsaGtxkrLgKYlJ1mMTAmtQ2JD1UqBMFtPU/pEyoBSRqdz3eR+z5TEUollZbNEWjZXe/8OZ+GI2hIqdEKDAoMmrq4BcpYKsrU9lCJQUeLzYLZL+vYZz2GnTKvKSGmA+OvO1uHgI6jX16sNDirzrna+srZyejDPES+tRcYQnb21kIBmBvrcNt/3LjZf/4aev3zD6DN3MPsFUWLWjZsikVVPdGePJRgiQ+qkqd07pUTHBa1rQOOs02evXoHN7pTUVhtfayDIeYfmvJ570wLvAEZ9xKmB74mDYWVCUYSCWvvBwajAauHsy9mDlEEMxDaN
*/