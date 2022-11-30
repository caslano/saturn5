/* Copyright 2003-2022 Joaquin M Lopez Munoz.
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
#include <boost/core/noncopyable.hpp>
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
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
*/