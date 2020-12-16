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
cuicHbtv6ZvW/uMez8o7zPj9UJ/L0qa1Xrb0L0k9l9Xd9+NB3FuRNXPKc3OWHm8+assNMwb+ceEzf9gZ+Npev1b3t7Y/fWv4ayQ/x/f+NXz1NfNWDHj32/ziMS33nb61/QbJzxuzd+/46cjywzOXNG74+NIxiPsnSbf/kIKUj0cdbl+3PG3ftd2OPusloyztKgk4hzLKGZ55C/trks+b0U9TpuqvQAf1o3rCxdQQbh3DPcxwGxiutRqLMQ4ynMP2DvqNDHeXzX9GDf6n0P8cW75615CvkfSfx3zl28Ll1BDuYoYbynDDbOHyagjnYrgihptsC1deQ7iNDLeJ4f7EcFkefkL+l+QjUzePMuXXARtS9jaVey5tuefSgbK4S609gPMdRhHsKtidsMdhM7D+Hwu7ErYFaPt+wBrYp2C3w+7l/kA89gRaw2bCDoe17xds5p5BJPYL0mB7wmbDjoV1wy6FfZD7CQdgj8K27wV/sHNhN8Juhd0He8hnv8ENuxR2DewjsNthD8Om9UYcsC5YN+wC2JW2fYnDsM5LEBdsBmxv2BLYubD2PYs02PawvWGHe2T5YJ+C3Q6712dPIxO2HHYu7ArYrbC7YPfBDsdexxzY9bDbYb+AjZ8aZvSELYFdMTW4FxI0vw5zFtb/rgmTTs/6fz/Gu/M4b8zSrKs/T4QM92D7vNFKHlexSgzb3A4iCfp5PsIGNm/nHN2KT821WjsCnwMEOnd6SeZs3affc/+1Vx4cueWBLZOzFy9t6G+OF/hcTj+38T+n2izfe3GTwm+vHjupXcj0SRFzPi/cjb1s+f3tmz/e0aew+J5538ya8Fizh+r4n8stCLF+/+3IF531Fx57tNmmt5q1vntgr8Dnivo5m/851U75/YXIBptzu3Z9vleddudPTe+X6m9uGfgc0s8cj3M2tju25Tz73IHy7xbO4NxhM3CNaZxwnO9tG+vTON7PPUtjfnyvn8f9vFMY+529fx7/szVzgPUBzAM2w75Ti/nAqhPMCUb5zAvW+cwNNgXH/qAJmqAJmqAJmqAJmqD5BZuzsP4vKKk49fV/Ck5QvsMZ14Eu1voI0UIfU+7EaXwDMDv2U9vewCZTyW6JiYdNBLGram/gspx+Q4YNy0a+CvNLKwtrd5aNsDq5VL0O0gD3EXRn0kreknK/H3CNiDKwyUj6X6MekT2CJsevzcv8JrFd8uTHk6d1+rLz6TsX0a/JT9+5iH6PwO+an2tplj0wQbMP35Br6SRgPDCZMnJ7pob5yMnBTg2rtaxcbeXknBXBtWHQBE3QBE3QBE3QBE3QBE3Q/O+ME3bCGV3/n/raH5qI5ex+j6z9LRnQ3+QWTKt0l00R2VjZGziGdfE74u4ReJ1SXkK343DbK24VhXbHRLj9ALd94mYJtouDSq/3TOv3AgRR0smFE6ZNkv2GA7Z3CLtSCGEAZVj7w96OReehgV53a1E+FRSft+85VHLdTz3AEuYS3BMzdfsQjNP0lYFV90h/GOj3/SeE1crE6nWAD9TKxOp1gNOv9bZYT+ts2lElkx+SGuqIjIoJTYmsF2PJunpkX/8YY5X9MCn7wakmIlVlr+7Ixwyy4mwGf3VqrQ9Z9lGkPLmPopGbjdTIzcZ4y83KfksLSR/lSR3w7UlHx3jLL2+nfPQnrPv9sD8hTM6g6nXP1let7tNZ9yMkzAdGK/zNhC2EvU7fDhi/id887aCsxJXrrU9iq/ipRHjtWzmIQ9+W0lkHc8V9KcqlrtEVPTcHoaYbdXTtBXFp2pa+vcCvtm1p71fDr17emnn8VtzrKP0I0dlV7SYKv1jvtPRA30yrUyVvHVEX7TE2JtQZ0iA0LTI+3F+ctzE=
*/