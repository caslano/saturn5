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