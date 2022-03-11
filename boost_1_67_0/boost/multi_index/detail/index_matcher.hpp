/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_INDEX_MATCHER_HPP
#define BOOST_MULTI_INDEX_DETAIL_INDEX_MATCHER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/noncopyable.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <cstddef>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

/* index_matcher compares a sequence of elements against a
 * base sequence, identifying those elements that belong to the
 * longest subsequence which is ordered with respect to the base.
 * For instance, if the base sequence is:
 *
 *   0 1 2 3 4 5 6 7 8 9
 *
 * and the compared sequence (not necesarilly the same length):
 *
 *   1 4 2 3 0 7 8 9
 *
 * the elements of the longest ordered subsequence are:
 *
 *   1 2 3 7 8 9
 * 
 * The algorithm for obtaining such a subsequence is called
 * Patience Sorting, described in ch. 1 of:
 *   Aldous, D., Diaconis, P.: "Longest increasing subsequences: from
 *   patience sorting to the Baik-Deift-Johansson Theorem", Bulletin
 *   of the American Mathematical Society, vol. 36, no 4, pp. 413-432,
 *   July 1999.
 *   http://www.ams.org/bull/1999-36-04/S0273-0979-99-00796-X/
 *   S0273-0979-99-00796-X.pdf
 *
 * This implementation is not fully generic since it assumes that
 * the sequences given are pointed to by index iterators (having a
 * get_node() memfun.)
 */

namespace index_matcher{

/* The algorithm stores the nodes of the base sequence and a number
 * of "piles" that are dynamically updated during the calculation
 * stage. From a logical point of view, nodes form an independent
 * sequence from piles. They are stored together so as to minimize
 * allocated memory.
 */

struct entry
{
  entry(void* node_,std::size_t pos_=0):node(node_),pos(pos_){}

  /* node stuff */

  void*       node;
  std::size_t pos;
  entry*      previous;
  bool        ordered;

  struct less_by_node
  {
    bool operator()(
      const entry& x,const entry& y)const
    {
      return std::less<void*>()(x.node,y.node);
    }
  };

  /* pile stuff */

  std::size_t pile_top;
  entry*      pile_top_entry;

  struct less_by_pile_top
  {
    bool operator()(
      const entry& x,const entry& y)const
    {
      return x.pile_top<y.pile_top;
    }
  };
};

/* common code operating on void *'s */

template<typename Allocator>
class algorithm_base:private noncopyable
{
protected:
  algorithm_base(const Allocator& al,std::size_t size):
    spc(al,size),size_(size),n_(0),sorted(false)
  {
  }

  void add(void* node)
  {
    entries()[n_]=entry(node,n_);
    ++n_;
  }

  void begin_algorithm()const
  {
    if(!sorted){
      std::sort(entries(),entries()+size_,entry::less_by_node());
      sorted=true;
    }
    num_piles=0;
  }

  void add_node_to_algorithm(void* node)const
  {
    entry* ent=
      std::lower_bound(
        entries(),entries()+size_,
        entry(node),entry::less_by_node()); /* localize entry */
    ent->ordered=false;
    std::size_t n=ent->pos;                 /* get its position */

    entry dummy(0);
    dummy.pile_top=n;

    entry* pile_ent=                        /* find the first available pile */
      std::lower_bound(                     /* to stack the entry            */
        entries(),entries()+num_piles,
        dummy,entry::less_by_pile_top());

    pile_ent->pile_top=n;                   /* stack the entry */
    pile_ent->pile_top_entry=ent;        

    /* if not the first pile, link entry to top of the preceding pile */
    if(pile_ent>&entries()[0]){ 
      ent->previous=(pile_ent-1)->pile_top_entry;
    }

    if(pile_ent==&entries()[num_piles]){    /* new pile? */
      ++num_piles;
    }
  }

  void finish_algorithm()const
  {
    if(num_piles>0){
      /* Mark those elements which are in their correct position, i.e. those
       * belonging to the longest increasing subsequence. These are those
       * elements linked from the top of the last pile.
       */

      entry* ent=entries()[num_piles-1].pile_top_entry;
      for(std::size_t n=num_piles;n--;){
        ent->ordered=true;
        ent=ent->previous;
      }
    }
  }

  bool is_ordered(void * node)const
  {
    return std::lower_bound(
      entries(),entries()+size_,
      entry(node),entry::less_by_node())->ordered;
  }

private:
  entry* entries()const{return raw_ptr<entry*>(spc.data());}

  auto_space<entry,Allocator> spc;
  std::size_t                 size_;
  std::size_t                 n_;
  mutable bool                sorted;
  mutable std::size_t         num_piles;
};

/* The algorithm has three phases:
 *   - Initialization, during which the nodes of the base sequence are added.
 *   - Execution.
 *   - Results querying, through the is_ordered memfun.
 */

template<typename Node,typename Allocator>
class algorithm:private algorithm_base<Allocator>
{
  typedef algorithm_base<Allocator> super;

public:
  algorithm(const Allocator& al,std::size_t size):super(al,size){}

  void add(Node* node)
  {
    super::add(node);
  }

  template<typename IndexIterator>
  void execute(IndexIterator first,IndexIterator last)const
  {
    super::begin_algorithm();

    for(IndexIterator it=first;it!=last;++it){
      add_node_to_algorithm(get_node(it));
    }

    super::finish_algorithm();
  }

  bool is_ordered(Node* node)const
  {
    return super::is_ordered(node);
  }

private:
  void add_node_to_algorithm(Node* node)const
  {
    super::add_node_to_algorithm(node);
  }

  template<typename IndexIterator>
  static Node* get_node(IndexIterator it)
  {
    return static_cast<Node*>(it.get_node());
  }
};

} /* namespace multi_index::detail::index_matcher */

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* index_matcher.hpp
+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
*/