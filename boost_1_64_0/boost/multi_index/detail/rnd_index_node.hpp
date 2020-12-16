/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_INDEX_NODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_INDEX_NODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/integer/common_factor_rt.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <cstddef>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Allocator>
struct random_access_index_node_impl
{
  typedef typename rebind_alloc_for<
    Allocator,random_access_index_node_impl
  >::type                                             node_allocator;
  typedef allocator_traits<node_allocator>            node_alloc_traits;
  typedef typename node_alloc_traits::pointer         pointer;
  typedef typename node_alloc_traits::const_pointer   const_pointer;
  typedef typename node_alloc_traits::difference_type difference_type;
  typedef typename rebind_alloc_for<
    Allocator,pointer
  >::type                                             ptr_allocator;
  typedef allocator_traits<ptr_allocator>             ptr_alloc_traits;
  typedef typename ptr_alloc_traits::pointer          ptr_pointer;

  ptr_pointer& up(){return up_;}
  ptr_pointer  up()const{return up_;}

  /* interoperability with rnd_node_iterator */

  static void increment(pointer& x)
  {
    x=*(x->up()+1);
  }

  static void decrement(pointer& x)
  {
    x=*(x->up()-1);
  }

  static void advance(pointer& x,difference_type n)
  {
    x=*(x->up()+n);
  }

  static difference_type distance(pointer x,pointer y)
  {
    return static_cast<difference_type>(y->up()-x->up());
  }

  /* algorithmic stuff */

  static void relocate(ptr_pointer pos,ptr_pointer x)
  {
    pointer n=*x;
    if(x<pos){
      extract(x,pos);
      *(pos-1)=n;
      n->up()=pos-1;
    }
    else{
      while(x!=pos){
        *x=*(x-1);
        (*x)->up()=x;
        --x;
      }
      *pos=n;
      n->up()=pos;
    }
  };

  static void relocate(ptr_pointer pos,ptr_pointer first,ptr_pointer last)
  {
    ptr_pointer begin,middle,end;
    if(pos<first){
      begin=pos;
      middle=first;
      end=last;
    }
    else{
      begin=first;
      middle=last;
      end=pos;
    }

    std::ptrdiff_t n=end-begin;
    std::ptrdiff_t m=middle-begin;
    std::ptrdiff_t n_m=n-m;
    std::ptrdiff_t p=integer::gcd(n,m);

    for(std::ptrdiff_t i=0;i<p;++i){
      pointer tmp=begin[i];
      for(std::ptrdiff_t j=i,k;;){
        if(j<n_m)k=j+m;
        else     k=j-n_m;
        if(k==i){
          *(begin+j)=tmp;
          (*(begin+j))->up()=begin+j;
          break;
        }
        else{
          *(begin+j)=*(begin+k);
          (*(begin+j))->up()=begin+j;
        }

        if(k<n_m)j=k+m;
        else     j=k-n_m;
        if(j==i){
          *(begin+k)=tmp;
          (*(begin+k))->up()=begin+k;
          break;
        }
        else{
          *(begin+k)=*(begin+j);
          (*(begin+k))->up()=begin+k;
        }
      }
    }
  };

  static void extract(ptr_pointer x,ptr_pointer pend)
  {
    --pend;
    while(x!=pend){
      *x=*(x+1);
      (*x)->up()=x;
      ++x;
    }
  }

  static void transfer(
    ptr_pointer pbegin0,ptr_pointer pend0,ptr_pointer pbegin1)
  {
    while(pbegin0!=pend0){
      *pbegin1=*pbegin0++;
      (*pbegin1)->up()=pbegin1;
      ++pbegin1;
    }
  }

  static void reverse(ptr_pointer pbegin,ptr_pointer pend)
  {
    std::ptrdiff_t d=(pend-pbegin)/2;
    for(std::ptrdiff_t i=0;i<d;++i){
      std::swap(*pbegin,*--pend);
      (*pbegin)->up()=pbegin;
      (*pend)->up()=pend;
      ++pbegin;
    }
  }

private:
  ptr_pointer up_;
};

template<typename Super>
struct random_access_index_node_trampoline:
  random_access_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  >
{
  typedef random_access_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  > impl_type;
};

template<typename Super>
struct random_access_index_node:
  Super,random_access_index_node_trampoline<Super>
{
private:
  typedef random_access_index_node_trampoline<Super> trampoline;

public:
  typedef typename trampoline::impl_type         impl_type;
  typedef typename trampoline::pointer           impl_pointer;
  typedef typename trampoline::const_pointer     const_impl_pointer;
  typedef typename trampoline::difference_type   difference_type;
  typedef typename trampoline::ptr_pointer       impl_ptr_pointer;

  impl_ptr_pointer& up(){return trampoline::up();}
  impl_ptr_pointer  up()const{return trampoline::up();}

  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }

  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }

  static random_access_index_node* from_impl(impl_pointer x)
  {
    return
      static_cast<random_access_index_node*>(
        static_cast<trampoline*>(
          raw_ptr<impl_type*>(x)));
  }

  static const random_access_index_node* from_impl(const_impl_pointer x)
  {
    return
      static_cast<const random_access_index_node*>(
        static_cast<const trampoline*>(
          raw_ptr<const impl_type*>(x)));
  }

  /* interoperability with rnd_node_iterator */

  static void increment(random_access_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }

  static void decrement(random_access_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }

  static void advance(random_access_index_node*& x,difference_type n)
  {
    impl_pointer xi=x->impl();
    trampoline::advance(xi,n);
    x=from_impl(xi);
  }

  static difference_type distance(
    random_access_index_node* x,random_access_index_node* y)
  {
    return trampoline::distance(x->impl(),y->impl());
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_index_node.hpp
De4MdV/i56VthS5/ujYTcvFIXjs/POz2aO/MFxIN/81ePMnmkL/9CbGO2S4/d7fZQ6QP1f7h7ywe3tnD2l1zq+PuFOgUcc8S5B+qr9n2E61DrI+/IMvlsBUUekKiUVU/2ZBAxoA+4xgh981dCLbiKZm3OTlK6NPtZKj14e7UdP433+YMlaEI3uaeZscCP3Jd62ljVch10my50+ZyjnJ4Q9SRqtbnyxNkbAxPI0tuoVvhPT3DEuPB71hN6FT8RrMQ+1IL/U6X0z8yNOoIv+PeBBIN+kzQ5q8zh0OOw6lsYuAuEQp2MuS2XBujuMkrzAzRG4I1Oh93O0Ns50Ttbohzed8J9FmWAXv1DSPFO8qYg/SO+NDry/O7Q2MhhF4lu/X9nEeVte3z7NZG8OM/7+f06dn/rp59Q7N5kufwFjhcl7yn81zQPUTUigF3m/fo3E1SuHuBWSP/lTv+OgbdNfD2O3u275R8q1bP//xKecspLNAObdkvkbNpbFoQzlAqBFwN3Ktz9bjC1UvsTOK/cqV16kwbH+7/3/vsnNxFe59aKdJGXCpnLwZtZ6gV07iDz7whhHCaMp5UuJvOYnMuvul6nD9undjXWcAbb2JrQtoub3fqomVdQhzKP8fpwDorCFZ2ESx4/BPovJyQKQas48r7qbTFvISECB2j1225XtZzEyEHo3UsYe2Er4LFnAWPyYPxbB8hraJ1LGZ1nWnB4hmDxXsGj4cF38I3f8eCxxPD974lZIwBe7Ns2nkZl8+xRgas4y8PtJDvnWN+qmN5U94rlN87TMgHBqxa8wGPyO8dJWSeAVt8cuQ9weO/Yc+LYw8bsDZbuh6UOhwnJN+ADTq5/XrJJ8ceMmCOeY82l7ycIGSfRcduXZw+K3hMPrTBU4Q8YcCOHP1sRvCzDPDeTxMy1YDVczX8Jfg5EMD4b9UhOuZ6Ym+K5IVjd1t0zOF/SpZZek6cqwxgAyv3fSDfA8f8BqzG6NtbyjJ/I6RhhI61+bYyIfi5HZBHKBltwPY6CzpJriklKw1YHl18Sq57GRXvCLCr8umzwc9JgQ2xUNLAgB3L2N1L1sWE7YzvlSz7LccaG7CSOyfIPkYi/rnMRI45DdiVz3TKkfI4VsuAbXzwTd2ecSzLgNVf8r3OS6QqL3+s9+4A5gmCTVUwVb/SSFW/p2tcFyP5DILFR/2zvGQFU3lJVTFVB45VGLCXTrf0y7YUDfmWAPt+xJYT8ntWSu4wYJO3dV0t+eTYIwbsk0favi7bbgwVtg6wqc3PnZH1rEbJAgMW233YbKlfdUoyDVhanzkTJZ8cm2PAEic99bCUF0vJbVTHdqx/ur9sLzU41was/4x79up3lFOy14ANHXT2iHxHtSh5xSCPPba+p6xLbUpmUh0rPbvkgLQ9dSm5muhYn1FPpMp2XY/zSXXssR+3HpfvoT4l9xEdu61005VShwaUjDRgS2aPnxv8HCeMVRyriNCxddVbHpVlXk7JtUTHEo7dLW2Bh2ODDdiKpvU9kheOPW7A7nB8Ol7y2RRy8wAW+7uNyrpw7CoD1m1Xt0XyvSdScrMBe/2rrrfJMjn2sAF7/7eILfJ7zSjpYsDWrMjOlW2CYwOojkV8HqGvCVtQsoHo2Dstb1kW/Hww1IVjSw2Yo+nqkVJeK+AMsB6/P3NS6s6xYRE6NtdbaJdcX03JPKZjHf/sJ8fGsnZUjGOAvTx7dlc9Dz0lLamO1arRvZ18t+0peZXo2C0DthXJurQH2wNYzsH3Dwc/Hw7jA8dqSUy1rRkcayQxmKMEPXcPdenIyzRg6d4ln0o70ZmSDgbs57uatw6ezwDeUVdKrrfo2C+DTkqbVXw9JVYD1r/VzG8=
*/