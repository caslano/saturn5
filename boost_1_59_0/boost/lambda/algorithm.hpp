// -- algorithm.hpp -- Boost Lambda Library -----------------------------------
// Copyright (C) 2002 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2002 Gary Powell (gwpowell@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org

#ifndef BOOST_LAMBDA_ALGORITHM_HPP
#define BOOST_LAMBDA_ALGORITHM_HPP

#include "boost/lambda/core.hpp"

#include <algorithm>
#include <iterator>  // for iterator_traits
#include <utility> // for std::pair

namespace boost {
  namespace lambda {

namespace ll {

// for_each ---------------------------------

struct for_each {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::for_each(a, b, c); }
};

// find  ---------------------------------

struct find {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, const C& c) const
  { return ::std::find(a, b, c); }
};


// find_if  ---------------------------------

struct find_if {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::find_if(a, b, c); }
};

// find_end  ---------------------------------

struct find_end {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, C c, C d) const
  { return ::std::find_end(a, b, c, d); }

  template <class A, class C, class E>
  A
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::find_end(a, b, c, d, e); }

};

// find_first_of  ---------------------------------

struct find_first_of {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, C c, C d) const
  { return ::std::find_first_of(a, b, c, d); }

  template <class A, class C, class E>
  A
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::find_first_of(a, b, c, d, e); }

};

// adjacent_find  ---------------------------------

struct adjacent_find {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::adjacent_find(a, b); }

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::adjacent_find(a, b, c); }

};

// count  ---------------------------------

struct count {

  template <class Args>
  struct sig { 
    typedef typename ::std::iterator_traits<
      typename boost::remove_const<
           typename boost::tuples::element<1, Args>::type
      >::type 
    >::difference_type type;
  };

  template <class A, class C >
  typename ::std::iterator_traits<A>::difference_type
  operator()(A a, A b, const C& c) const
  { return ::std::count(a, b, c); }
};

// count_if  ---------------------------------

struct count_if {

  template <class Args>
  struct sig { 
    typedef typename ::std::iterator_traits<
     typename boost::remove_const<
           typename boost::tuples::element<1, Args>::type
       >::type
    >::difference_type type;
  };

  template <class A, class C >
  typename ::std::iterator_traits<A>::difference_type
  operator()(A a, A b, C c) const
  { return ::std::count_if(a, b, c); }
};


// mismatch  ---------------------------------

struct mismatch {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type
     >::type element1_type; 

    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type
     >::type element2_type; 

    typedef ::std::pair< element1_type, element2_type > type;
   };

  template <class A, class C >
  ::std::pair<A,C>
  operator()(A a, A b, C c) const
  { return ::std::mismatch(a, b, c); }

  template <class A, class C, class D>
  ::std::pair<A,C>
  operator()(A a, A b, C c, D d) const
  { return ::std::mismatch(a, b, c, d); }

};

// equal  ---------------------------------

struct equal {

  template <class Args>
  struct sig { 
    typedef bool type;
  };

  template <class A, class C >
  bool
  operator()(A a, A b, C c) const
  { return ::std::equal(a, b, c); }

  template <class A, class C, class D>
  bool
  operator()(A a, A b, C c, D d) const
  { return ::std::equal(a, b, c, d); }

};

// search --------------------------------

struct search {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, C c, C d) const
  { return std::search(a, b, c, d);}

  template <class A, class C, class E>
  A
  operator()(A a, A b, C c, C d, E e) const
  { return std::search(a, b, c, d, e);}

};

// copy  ---------------------------------

struct copy {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::copy(a, b, c); }

};

// copy_backward  ---------------------------------

struct copy_backward {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::copy_backward(a, b, c); }

};

// swap  ---------------------------------

struct swap {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::swap(a, b); }

};

// swap_ranges  ---------------------------------

struct swap_ranges {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::swap_ranges(a, b, c); }

};

// iter_swap  ---------------------------------

struct iter_swap {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A>
  void 
  operator()(A a, A b) const
  { ::std::iter_swap(a, b); }

};


// transform --------------------------------

struct transform {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<
          boost::tuples::length<Args>::value - 2, 
          Args
      >::type
     >::type type; 
  };

  template <class A, class C, class D>
  C
  operator()(A a, A b, C c, D d) const
  { return std::transform(a, b, c, d);}

  template <class A, class C, class D, class E>
  D
  operator()(A a, A b, C c, D d, E e) const
  { return std::transform(a, b, c, d, e);}

};

// replace  ---------------------------------

struct replace {

  template <class Args>
  struct sig {
    typedef void type;
  };

  template <class A, class C>
  void
  operator()(A a, A b, const C& c, const C& d) const
  { ::std::replace(a, b, c, d); }

};

// replace_if  ---------------------------------

struct replace_if {

  template <class Args>
  struct sig {
    typedef void type;
  };

  template <class A, class C, class D>
  void
  operator()(A a, A b, C c, const D& d) const
  { ::std::replace_if(a, b, c, d); }

};

// replace_copy  ---------------------------------

struct replace_copy {

 template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C, class D>
  C
  operator()(A a, A b, C c, const D& d, const D& e) const
  { return ::std::replace_copy(a, b, c, d, e); }

};

// replace_copy_if  ---------------------------------

struct replace_copy_if {

 template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C, class D, class E>
  C
  operator()(A a, A b, C c, D d, const E& e) const
  { return ::std::replace_copy_if(a, b, c, d, e); }

};

// fill  ---------------------------------

struct fill {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A, class C>
  void 
  operator()(A a, A b, const C& c) const
  { ::std::fill(a, b, c); }

};

// fill_n  ---------------------------------

struct fill_n {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A, class B, class C>
  void 
  operator()(A a, B b, const C& c) const
  { ::std::fill_n(a, b, c); }

};

// generate  ---------------------------------

struct generate {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A, class C>
  void 
  operator()(A a, A b, C c) const
  { ::std::generate(a, b, c); }

};

// generate_n  ---------------------------------

struct generate_n {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A, class B, class C>
  void 
  operator()(A a, B b, C c) const
  { ::std::generate_n(a, b, c); }

};

// remove  ---------------------------------

struct remove {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C >
  A
  operator()(A a, A b, const C& c) const
  { return ::std::remove(a, b, c); }
};

// remove_if  ---------------------------------

struct remove_if {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
       typename boost::tuples::element<1, Args>::type
     >::type type; 
  };

  template <class A, class C >
  A
  operator()(A a, A b, C c) const
  { return ::std::remove_if(a, b, c); }
};

// remove_copy  ---------------------------------

struct remove_copy {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
       typename boost::tuples::element<3, Args>::type
     >::type type; 
  };

  template <class A, class C, class D >
  C
  operator()(A a, A b, C c, const D& d) const
  { return ::std::remove_copy(a, b, c, d); }
};

// remove_copy_if  ---------------------------------

struct remove_copy_if {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
       typename boost::tuples::element<3, Args>::type
     >::type type; 
  };

  template <class A, class C, class D >
  C
  operator()(A a, A b, C c, D d) const
  { return ::std::remove_copy_if(a, b, c, d); }
};

// unique  ---------------------------------

struct unique {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::unique(a, b); }

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::unique(a, b, c); }

};

// unique_copy  ---------------------------------

struct unique_copy {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C >
  C
  operator()(A a, A b, C c) const
  { return ::std::unique_copy(a, b, c); }

  template <class A, class C, class D>
  C
  operator()(A a, A b, C c, D d) const
  { return ::std::unique_copy(a, b, c, d); }

};

// reverse  ---------------------------------

struct reverse {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::reverse(a, b); }

};

// reverse_copy  ---------------------------------

struct reverse_copy {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class C >
  C
  operator()(A a, A b, C c) const
  { return ::std::reverse_copy(a, b, c); }

};

// rotate  ---------------------------------

struct rotate {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b, A c) const
  { ::std::rotate(a, b, c); }

};

// rotate_copy  ---------------------------------

struct rotate_copy {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class D>
  D
  operator()(A a, A b, A c, D d) const
  { return ::std::rotate_copy(a, b, c, d); }

};

// random_shuffle  ---------------------------------

#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE

struct random_shuffle {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::random_shuffle(a, b); }

  template <class A, class C>
  void
  operator()(A a, A b, const C& c) const
  { ::std::random_shuffle(a, b, c); }

};

#endif

// partition  ---------------------------------

struct partition {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::partition(a, b, c); }

};

// stable_partition  ---------------------------------

struct stable_partition {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::stable_partition(a, b, c); }

};

// sort  ---------------------------------

struct sort {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A>
  void 
  operator()(A a, A b) const
  { ::std::sort(a, b); }

  template <class A, class C>
  void 
  operator()(A a, A b, C c) const
  { ::std::sort(a, b, c); }

};

// stable_sort  ---------------------------------

struct stable_sort {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A>
  void 
  operator()(A a, A b) const
  { ::std::stable_sort(a, b); }

  template <class A, class C>
  void 
  operator()(A a, A b, C c) const
  { ::std::stable_sort(a, b, c); }

};

// partial_sort  ---------------------------------

struct partial_sort {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A>
  void 
  operator()(A a, A b, A c) const
  { ::std::partial_sort(a, b, c); }

  template <class A, class D>
  void 
  operator()(A a, A b, A c, D d) const
  { ::std::partial_sort(a, b, c, d); }

};

// partial_sort_copy  ---------------------------------

struct partial_sort_copy {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
       typename boost::tuples::element<3, Args>::type
     >::type type; 
  };

  template <class A, class C>
  C
  operator()(A a, A b, C c, C d) const
  { return ::std::partial_sort_copy(a, b, c, d); }

  template <class A, class C, class E >
  C
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::partial_sort_copy(a, b, c, d, e); }
};

// nth_element  ---------------------------------

struct nth_element {

  template <class Args>
  struct sig { 
     typedef void type; 
  };

  template <class A>
  void 
  operator()(A a, A b, A c) const
  { ::std::nth_element(a, b, c); }

  template <class A, class D>
  void 
  operator()(A a, A b, A c, D d) const
  { ::std::nth_element(a, b, c, d); }

};

// lower_bound  ---------------------------------

struct lower_bound {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, const C& c) const
  { return ::std::lower_bound(a, b, c); }

  template <class A, class C, class D>
  A
  operator()(A a, A b, const C& c, D d) const
  { return ::std::lower_bound(a, b, c, d); }

};

// upper_bound  ---------------------------------

struct upper_bound {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A, class C>
  A
  operator()(A a, A b, const C& c) const
  { return ::std::upper_bound(a, b, c); }

  template <class A, class C, class D>
  A
  operator()(A a, A b, const C& c, D d) const
  { return ::std::upper_bound(a, b, c, d); }

};

// equal_range  ---------------------------------

struct equal_range {

 template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type
     >::type element_type; 

    typedef ::std::pair< element_type, element_type > type;
   };

  template <class A, class C>
  ::std::pair<A,A>
  operator()(A a, A b, const C& c) const
  { return ::std::equal_range(a, b, c); }

  template <class A, class C, class D>
  ::std::pair<A,A>
  operator()(A a, A b, const C& c, D d) const
  { return ::std::equal_range(a, b, c, d); }

};

// binary_search  ---------------------------------

struct binary_search {

  template <class Args>
  struct sig { 
    typedef bool type;
  };

  template <class A, class C >
  bool
  operator()(A a, A b, const C& c) const
  { return ::std::binary_search(a, b, c); }

  template <class A, class C, class D>
  bool
  operator()(A a, A b, const C& c, D d) const
  { return ::std::binary_search(a, b, c, d); }

};

// merge --------------------------------

struct merge {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<5, Args>::type 
     >::type type; 
  };

  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::merge(a, b, c, d, e);}

  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::merge(a, b, c, d, e, f);}

};

// inplace_merge  ---------------------------------

struct inplace_merge {

  template <class Args>
  struct sig {
    typedef void type;
  };

  template <class A>
  void
  operator()(A a, A b, A c) const
  { ::std::inplace_merge(a, b, c); }

  template <class A, class D>
  void
  operator()(A a, A b, A c, D d) const
  { ::std::inplace_merge(a, b, c, d); }

};

// includes  ---------------------------------

struct includes {

  template <class Args>
  struct sig { 
    typedef bool type;
  };

  template <class A, class C>
  bool
  operator()(A a, A b, C c, C d) const
  { return ::std::includes(a, b, c, d); }

  template <class A, class C, class E>
  bool
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::includes(a, b, c, d, e); }

};

// set_union --------------------------------

struct set_union {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<5, Args>::type 
     >::type type; 
  };

  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_union(a, b, c, d, e);}

  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::set_union(a, b, c, d, e, f);}

};

// set_intersection --------------------------------

struct set_intersection {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<5, Args>::type 
     >::type type; 
  };

  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_intersection(a, b, c, d, e);}

  template <class A, class C, class E, class F>
  E
  operator()(A a,  A b, C c, C d, E e, F f) const
  { return std::set_intersection(a, b, c, d, e, f);}

};

// set_difference --------------------------------

struct set_difference {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<5, Args>::type 
     >::type type; 
  };

  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_difference(a, b, c, d, e);}

  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::set_difference(a, b, c, d, e, f);}

};


// set_symmetric_difference --------------------------------

struct set_symmetric_difference {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<5, Args>::type 
     >::type type; 
  };

  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_symmetric_difference(a, b, c, d, e);}

  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::set_symmetric_difference(a, b, c, d, e, f);}

};

// push_heap  ---------------------------------

struct push_heap {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::push_heap(a, b); }

  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::push_heap(a, b, c); }

};

// pop_heap  ---------------------------------

struct pop_heap {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::pop_heap(a, b); }

  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::pop_heap(a, b, c); }

};


// make_heap  ---------------------------------

struct make_heap {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::make_heap(a, b); }

  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::make_heap(a, b, c); }

};

// sort_heap  ---------------------------------

struct sort_heap {

  template <class Args>
  struct sig { 
    typedef void type; 
  };

  template <class A>
  void
  operator()(A a, A b) const
  { ::std::sort_heap(a, b); }

  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::sort_heap(a, b, c); }

};

// min  ---------------------------------

struct min {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A>
  A
  operator()(const A& a, const A& b) const
  { return (::std::min)(a, b); }

  template <class A, class C>
  A
  operator()(const A& a, const A& b, C c) const
  { return (::std::min)(a, b, c); }

};

// max  ---------------------------------

struct max {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A>
  A
  operator()(const A& a, const A& b) const
  { return (::std::max)(a, b); }

  template <class A, class C>
  A
  operator()(const A& a, const A& b, C c) const
  { return (::std::max)(a, b, c); }

};

struct min_element {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::min_element(a, b); }

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::min_element(a, b, c); }

};

// max_element  ---------------------------------

struct max_element {

  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<1, Args>::type 
     >::type type; 
  };

  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::max_element(a, b); }

  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::max_element(a, b, c); }

};


// lexicographical_compare  ---------------------------------

struct lexicographical_compare {

  template <class Args>
  struct sig { 
    typedef bool type;
  };

  template <class A, class C>
  bool
  operator()(A a, A b, C c, C d) const
  { return ::std::lexicographical_compare(a, b, c, d); }

  template <class A, class C, class E>
  bool
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::lexicographical_compare(a, b, c, d, e); }

};

// next_permutation  ---------------------------------

struct next_permutation {

  template <class Args>
  struct sig { 
    typedef bool type;
  };

  template <class A>
  bool
  operator()(A a, A b) const
  { return ::std::next_permutation(a, b); }

  template <class A, class C >
  bool
  operator()(A a, A b, C c) const
  { return ::std::next_permutation(a, b, c); }

};

// prev_permutation  ---------------------------------

struct prev_permutation {

  template <class Args>
  struct sig { 
    typedef bool type;
  };

  template <class A>
  bool
  operator()(A a, A b) const
  { return ::std::prev_permutation(a, b); }

  template <class A, class C >
  bool
  operator()(A a, A b, C c) const
  { return ::std::prev_permutation(a, b, c); }

};





} // end of ll namespace

// There is no good way to call an overloaded member function in a 
// lambda expression. 
// The macro below defines a function object class for calling a
// const_iterator returning member function of a container.

#define CALL_MEMBER(X)                                     \
struct call_##X {                                          \
template <class Args>                                      \
  struct sig {                                             \
    typedef typename boost::remove_const<                  \
        typename boost::tuples::element<1, Args>::type     \
     >::type::const_iterator type;                         \
  };                                                       \
                                                           \
  template<class T>                                        \
  typename T::const_iterator                               \
  operator()(const T& t) const                             \
  {                                                        \
    return t.X();                                          \
  }                                                        \
};

// create call_begin and call_end classes
CALL_MEMBER(begin)
CALL_MEMBER(end)

#undef CALL_MEMBER

} // end of lambda namespace
} // end of boost namespace



#endif

/* algorithm.hpp
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
*/