/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HASH_INDEX_NODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_HASH_INDEX_NODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <utility>

namespace boost{

namespace multi_index{

namespace detail{

/* Certain C++ requirements on unordered associative containers (see LWG issue
 * #579) imply a data structure where nodes are linked in a single list, which
 * in its turn forces implementors to add additional overhed per node to
 * associate each with its corresponding bucket. Others resort to storing hash
 * values, we use an alternative structure providing unconditional O(1)
 * manipulation, even in situations of unfair hash distribution, plus some
 * lookup speedups. For unique indices we maintain a doubly linked list of
 * nodes except that if N is the first node of a bucket its associated
 * bucket node is embedded between N and the preceding node in the following
 * manner:
 *
 *        +---+   +---+       +---+   +---+
 *     <--+   |<--+   |    <--+   |<--+   |
 *   ...  | B0|   | B1|  ...  | B1|   | B2|  ...
 *        |   |-+ |   +-->    |   |-+ |   +-->
 *        +-+-+ | +---+       +-+-+ | +---+
 *              |   ^               |   ^
 *              |   |               |   |
 *              | +-+               | +-+
 *              | |                 | |
 *              v |                 v |  
 *       --+---+---+---+--   --+---+---+---+--
 *     ... |   | B1|   |  ...  |   | B2|   | ...
 *       --+---+---+---+--   --+---+---+---+--
 *
 *
 * The fist and last nodes of buckets can be checked with
 *
 *   first node of a bucket: Npn != N
 *   last node of a bucket:  Nnp != N
 *
 * (n and p short for ->next(), ->prior(), bucket nodes have prior pointers
 * only). Pure insert and erase (without lookup) can be unconditionally done
 * in O(1).
 * For non-unique indices we add the following additional complexity: when
 * there is a group of 3 or more equivalent elements, they are linked as
 * follows:
 *
 *         +-----------------------+
 *         |                       v
 *   +---+ | +---+       +---+   +---+
 *   |   | +-+   |       |   |<--+   |
 *   | F |   | S |  ...  | P |   | L |
 *   |   +-->|   |       |   +-+ |   |
 *   +---+   +---+       +---+ | +---+
 *     ^                       |
 *     +-----------------------+
 * 
 * F, S, P and L are the first, second, penultimate and last node in the
 * group, respectively (S and P can coincide if the group has size 3.) This
 * arrangement is used to skip equivalent elements in O(1) when doing lookup,
 * while preserving O(1) insert/erase. The following invariants identify
 * special positions (some of the operations have to be carefully implemented
 * as Xnn is not valid if Xn points to a bucket):
 *
 *   first node of a bucket: Npnp  == N
 *   last node of a bucket:  Nnpp  == N
 *   first node of a group:  Nnp != N && Nnppn == N
 *   second node of a group: Npn != N && Nppnn == N
 *   n-1 node of a group:    Nnp != N && Nnnpp == N
 *   last node of a group:   Npn != N && Npnnp == N
 * 
 * The memory overhead is one pointer per bucket plus two pointers per node,
 * probably unbeatable. The resulting structure is bidirectonally traversable,
 * though currently we are just providing forward iteration.
 */

template<typename Allocator>
struct hashed_index_node_impl;

/* half-header (only prior() pointer) to use for the bucket array */

template<typename Allocator>
struct hashed_index_base_node_impl
{
  typedef typename rebind_alloc_for<
    Allocator,hashed_index_base_node_impl
  >::type                                             base_allocator;
  typedef typename rebind_alloc_for<
    Allocator,hashed_index_node_impl<Allocator>
  >::type                                             node_allocator;
  typedef allocator_traits<base_allocator>            base_alloc_traits;
  typedef allocator_traits<node_allocator>            node_alloc_traits;
  typedef typename base_alloc_traits::pointer         base_pointer;
  typedef typename base_alloc_traits::const_pointer   const_base_pointer;
  typedef typename node_alloc_traits::pointer         pointer;
  typedef typename node_alloc_traits::const_pointer   const_pointer;
  typedef typename node_alloc_traits::difference_type difference_type;

  pointer& prior(){return prior_;}
  pointer  prior()const{return prior_;}

private:
  pointer prior_;
};

/* full header (prior() and next()) for the nodes */

template<typename Allocator>
struct hashed_index_node_impl:hashed_index_base_node_impl<Allocator>
{
private:
  typedef hashed_index_base_node_impl<Allocator> super;

public:  
  typedef typename super::base_pointer           base_pointer;
  typedef typename super::const_base_pointer     const_base_pointer;
  typedef typename super::pointer                pointer;
  typedef typename super::const_pointer          const_pointer;

  base_pointer& next(){return next_;}
  base_pointer  next()const{return next_;}

  static pointer pointer_from(base_pointer x)
  {
    return static_cast<pointer>(
      static_cast<hashed_index_node_impl*>(
        raw_ptr<super*>(x)));
  }

  static base_pointer base_pointer_from(pointer x)
  {
    return static_cast<base_pointer>(
      raw_ptr<hashed_index_node_impl*>(x));
  }

private:
  base_pointer next_;
};

/* Boost.MultiIndex requires machinery to reverse unlink operations. A simple
 * way to make a pointer-manipulation function undoable is to templatize
 * its internal pointer assignments with a functor that, besides doing the
 * assignment, keeps track of the original pointer values and can later undo
 * the operations in reverse order.
 */

struct default_assigner
{
  template<typename T> void operator()(T& x,const T& val){x=val;}
};

template<typename Node>
struct unlink_undo_assigner
{
  typedef typename Node::base_pointer base_pointer;
  typedef typename Node::pointer      pointer;

  unlink_undo_assigner():pointer_track_count(0),base_pointer_track_count(0){}

  void operator()(pointer& x,pointer val)
  {
    pointer_tracks[pointer_track_count].x=&x;
    pointer_tracks[pointer_track_count++].val=x;
    x=val;
  }

  void operator()(base_pointer& x,base_pointer val)
  {
    base_pointer_tracks[base_pointer_track_count].x=&x;
    base_pointer_tracks[base_pointer_track_count++].val=x;
    x=val;
  }

  void operator()() /* undo op */
  {
    /* in the absence of aliasing, restitution order is immaterial */

    while(pointer_track_count--){
      *(pointer_tracks[pointer_track_count].x)=
        pointer_tracks[pointer_track_count].val;
    }
    while(base_pointer_track_count--){
      *(base_pointer_tracks[base_pointer_track_count].x)=
        base_pointer_tracks[base_pointer_track_count].val;
    }
  }

  struct pointer_track     {pointer*      x; pointer      val;};
  struct base_pointer_track{base_pointer* x; base_pointer val;};

  /* We know the maximum number of pointer and base pointer assignments that
   * the two unlink versions do, so we can statically reserve the needed
   * storage.
   */

  pointer_track      pointer_tracks[3];
  int                pointer_track_count;
  base_pointer_track base_pointer_tracks[2];
  int                base_pointer_track_count;
};

/* algorithmic stuff for unique and non-unique variants */

struct hashed_unique_tag{};
struct hashed_non_unique_tag{};

template<typename Node,typename Category>
struct hashed_index_node_alg;

template<typename Node>
struct hashed_index_node_alg<Node,hashed_unique_tag>
{
  typedef typename Node::base_pointer       base_pointer;
  typedef typename Node::const_base_pointer const_base_pointer;
  typedef typename Node::pointer            pointer;
  typedef typename Node::const_pointer      const_pointer;

  static bool is_first_of_bucket(pointer x)
  {
    return x->prior()->next()!=base_pointer_from(x);
  }

  static pointer after(pointer x)
  {
    return is_last_of_bucket(x)?x->next()->prior():pointer_from(x->next());
  }

  static pointer after_local(pointer x)
  {
    return is_last_of_bucket(x)?pointer(0):pointer_from(x->next());
  }

  static pointer next_to_inspect(pointer x)
  {
    return is_last_of_bucket(x)?pointer(0):pointer_from(x->next());
  }

  static void link(pointer x,base_pointer buc,pointer end)
  {
    if(buc->prior()==pointer(0)){ /* empty bucket */
      x->prior()=end->prior();
      x->next()=end->prior()->next();
      x->prior()->next()=buc;
      buc->prior()=x;
      end->prior()=x;
    }
    else{
      x->prior()=buc->prior()->prior();
      x->next()=base_pointer_from(buc->prior());
      buc->prior()=x;
      x->next()->prior()=x;
    }
  }

  static void unlink(pointer x)
  {
    default_assigner assign;
    unlink(x,assign);
  }

  typedef unlink_undo_assigner<Node> unlink_undo;

  template<typename Assigner>
  static void unlink(pointer x,Assigner& assign)
  {
    if(is_first_of_bucket(x)){
      if(is_last_of_bucket(x)){
        assign(x->prior()->next()->prior(),pointer(0));
        assign(x->prior()->next(),x->next());
        assign(x->next()->prior()->prior(),x->prior());
      }
      else{
        assign(x->prior()->next()->prior(),pointer_from(x->next()));
        assign(x->next()->prior(),x->prior());
      }
    }
    else if(is_last_of_bucket(x)){
      assign(x->prior()->next(),x->next());
      assign(x->next()->prior()->prior(),x->prior());
    }
    else{
      assign(x->prior()->next(),x->next());
      assign(x->next()->prior(),x->prior());
    }
  }

  /* used only at rehashing */

  static void append(pointer x,pointer end)
  {
    x->prior()=end->prior();
    x->next()=end->prior()->next();
    x->prior()->next()=base_pointer_from(x);
    end->prior()=x;
  }

  static bool unlink_last(pointer end)
  {
    /* returns true iff bucket is emptied */

    pointer x=end->prior();
    if(x->prior()->next()==base_pointer_from(x)){
      x->prior()->next()=x->next();
      end->prior()=x->prior();
      return false;
    }
    else{
      x->prior()->next()->prior()=pointer(0);
      x->prior()->next()=x->next();
      end->prior()=x->prior();
      return true;
    }
  }

private:
  static pointer pointer_from(base_pointer x)
  {
    return Node::pointer_from(x);
  }

  static base_pointer base_pointer_from(pointer x)
  {
    return Node::base_pointer_from(x);
  }

  static bool is_last_of_bucket(pointer x)
  {
    return x->next()->prior()!=x;
  }
};

template<typename Node>
struct hashed_index_node_alg<Node,hashed_non_unique_tag>
{
  typedef typename Node::base_pointer       base_pointer;
  typedef typename Node::const_base_pointer const_base_pointer;
  typedef typename Node::pointer            pointer;
  typedef typename Node::const_pointer      const_pointer;

  static bool is_first_of_bucket(pointer x)
  {
    return x->prior()->next()->prior()==x;
  }

  static bool is_first_of_group(pointer x)
  {
    return
      x->next()->prior()!=x&&
      x->next()->prior()->prior()->next()==base_pointer_from(x);
  }

  static pointer after(pointer x)
  {
    if(x->next()->prior()==x)return pointer_from(x->next());
    if(x->next()->prior()->prior()==x)return x->next()->prior();
    if(x->next()->prior()->prior()->next()==base_pointer_from(x))
      return pointer_from(x->next());
    return pointer_from(x->next())->next()->prior();
  }

  static pointer after_local(pointer x)
  {
    if(x->next()->prior()==x)return pointer_from(x->next());
    if(x->next()->prior()->prior()==x)return pointer(0);
    if(x->next()->prior()->prior()->next()==base_pointer_from(x))
      return pointer_from(x->next());
    return pointer_from(x->next())->next()->prior();
  }

  static pointer next_to_inspect(pointer x)
  {
    if(x->next()->prior()==x)return pointer_from(x->next());
    if(x->next()->prior()->prior()==x)return pointer(0);
    if(x->next()->prior()->next()->prior()!=x->next()->prior())
      return pointer(0);
    return pointer_from(x->next()->prior()->next());
  }

  static void link(pointer x,base_pointer buc,pointer end)
  {
    if(buc->prior()==pointer(0)){ /* empty bucket */
      x->prior()=end->prior();
      x->next()=end->prior()->next();
      x->prior()->next()=buc;
      buc->prior()=x;
      end->prior()=x;
    }
    else{
      x->prior()=buc->prior()->prior();
      x->next()=base_pointer_from(buc->prior());
      buc->prior()=x;
      x->next()->prior()=x;
    }
  }

  static void link(pointer x,pointer first,pointer last)
  {
    x->prior()=first->prior();
    x->next()=base_pointer_from(first);
    if(is_first_of_bucket(first)){
      x->prior()->next()->prior()=x;
    }
    else{
      x->prior()->next()=base_pointer_from(x);
    }

    if(first==last){
      last->prior()=x;
    }
    else if(first->next()==base_pointer_from(last)){
      first->prior()=last;
      first->next()=base_pointer_from(x);
    }
    else{
      pointer second=pointer_from(first->next()),
              lastbutone=last->prior();
      second->prior()=first;
      first->prior()=last;
      lastbutone->next()=base_pointer_from(x);
    }
  }

  static void unlink(pointer x)
  {
    default_assigner assign;
    unlink(x,assign);
  }

  typedef unlink_undo_assigner<Node> unlink_undo;

  template<typename Assigner>
  static void unlink(pointer x,Assigner& assign)
  {
    if(x->prior()->next()==base_pointer_from(x)){
      if(x->next()->prior()==x){
        left_unlink(x,assign);
        right_unlink(x,assign);
      }
      else if(x->next()->prior()->prior()==x){           /* last of bucket */
        left_unlink(x,assign);
        right_unlink_last_of_bucket(x,assign);
      }
      else if(x->next()->prior()->prior()->next()==
              base_pointer_from(x)){                /* first of group size */
        left_unlink(x,assign);
        right_unlink_first_of_group(x,assign);
      }
      else{                                                /* n-1 of group */
        unlink_last_but_one_of_group(x,assign);
      }
    }
    else if(x->prior()->next()->prior()==x){            /* first of bucket */
      if(x->next()->prior()==x){
        left_unlink_first_of_bucket(x,assign);
        right_unlink(x,assign);
      }
      else if(x->next()->prior()->prior()==x){           /* last of bucket */
        assign(x->prior()->next()->prior(),pointer(0));
        assign(x->prior()->next(),x->next());
        assign(x->next()->prior()->prior(),x->prior());
      }
      else{                                              /* first of group */
        left_unlink_first_of_bucket(x,assign);
        right_unlink_first_of_group(x,assign);
      }
    }
    else if(x->next()->prior()->prior()==x){   /* last of group and bucket */
      left_unlink_last_of_group(x,assign);
      right_unlink_last_of_bucket(x,assign);
    }
    else if(pointer_from(x->prior()->prior()->next())
            ->next()==base_pointer_from(x)){            /* second of group */
      unlink_second_of_group(x,assign);
    }
    else{                              /* last of group, ~(last of bucket) */
      left_unlink_last_of_group(x,assign);
      right_unlink(x,assign);
    }
  }

  /* used only at rehashing */

  static void link_range(
    pointer first,pointer last,base_pointer buc,pointer cend)
  {
    if(buc->prior()==pointer(0)){ /* empty bucket */
      first->prior()=cend->prior();
      last->next()=cend->prior()->next();
      first->prior()->next()=buc;
      buc->prior()=first;
      cend->prior()=last;
    }
    else{
      first->prior()=buc->prior()->prior();
      last->next()=base_pointer_from(buc->prior());
      buc->prior()=first;
      last->next()->prior()=last;
    }
  }

  static void append_range(pointer first,pointer last,pointer cend)
  {
    first->prior()=cend->prior();
    last->next()=cend->prior()->next();
    first->prior()->next()=base_pointer_from(first);
    cend->prior()=last;
  }

  static std::pair<pointer,bool> unlink_last_group(pointer end)
  {
    /* returns first of group true iff bucket is emptied */

    pointer x=end->prior();
    if(x->prior()->next()==base_pointer_from(x)){
      x->prior()->next()=x->next();
      end->prior()=x->prior();
      return std::make_pair(x,false);
    }
    else if(x->prior()->next()->prior()==x){
      x->prior()->next()->prior()=pointer(0);
      x->prior()->next()=x->next();
      end->prior()=x->prior();
      return std::make_pair(x,true);
    }
    else{
      pointer y=pointer_from(x->prior()->next());

      if(y->prior()->next()==base_pointer_from(y)){
        y->prior()->next()=x->next();
        end->prior()=y->prior();
        return std::make_pair(y,false);
      }
      else{
        y->prior()->next()->prior()=pointer(0);
        y->prior()->next()=x->next();
        end->prior()=y->prior();
        return std::make_pair(y,true);
      }
    }
  }

  static void unlink_range(pointer first,pointer last)
  {
    if(is_first_of_bucket(first)){
      if(is_last_of_bucket(last)){
        first->prior()->next()->prior()=pointer(0);
        first->prior()->next()=last->next();
        last->next()->prior()->prior()=first->prior();
      }
      else{
        first->prior()->next()->prior()=pointer_from(last->next());
        last->next()->prior()=first->prior();
      }
    }
    else if(is_last_of_bucket(last)){
      first->prior()->next()=last->next();
      last->next()->prior()->prior()=first->prior();
    }
    else{
      first->prior()->next()=last->next();
      last->next()->prior()=first->prior();
    }
  }

private:
  static pointer pointer_from(base_pointer x)
  {
    return Node::pointer_from(x);
  }

  static base_pointer base_pointer_from(pointer x)
  {
    return Node::base_pointer_from(x);
  }

  static bool is_last_of_bucket(pointer x)
  {
    return x->next()->prior()->prior()==x;
  }

  template<typename Assigner>
  static void left_unlink(pointer x,Assigner& assign)
  {
    assign(x->prior()->next(),x->next());
  }
  
  template<typename Assigner>
  static void right_unlink(pointer x,Assigner& assign)
  {
    assign(x->next()->prior(),x->prior());
  }

  template<typename Assigner>
  static void left_unlink_first_of_bucket(pointer x,Assigner& assign)
  {
    assign(x->prior()->next()->prior(),pointer_from(x->next()));
  }

  template<typename Assigner>
  static void right_unlink_last_of_bucket(pointer x,Assigner& assign)
  {
    assign(x->next()->prior()->prior(),x->prior());
  }

  template<typename Assigner>
  static void right_unlink_first_of_group(pointer x,Assigner& assign)
  {
    pointer second=pointer_from(x->next()),
            last=second->prior(),
            lastbutone=last->prior();
    if(second==lastbutone){
      assign(second->next(),base_pointer_from(last));
      assign(second->prior(),x->prior());
    }
    else{
      assign(lastbutone->next(),base_pointer_from(second));
      assign(second->next()->prior(),last);
      assign(second->prior(),x->prior());
    }
  }

  template<typename Assigner>
  static void left_unlink_last_of_group(pointer x,Assigner& assign)
  {
    pointer lastbutone=x->prior(),
            first=pointer_from(lastbutone->next()),
            second=pointer_from(first->next());
    if(lastbutone==second){
      assign(lastbutone->prior(),first);
      assign(lastbutone->next(),x->next());
    }
    else{
      assign(second->prior(),lastbutone);
      assign(lastbutone->prior()->next(),base_pointer_from(first));
      assign(lastbutone->next(),x->next());
    }
  }

  template<typename Assigner>
  static void unlink_last_but_one_of_group(pointer x,Assigner& assign)
  {
    pointer first=pointer_from(x->next()),
            second=pointer_from(first->next()),
            last=second->prior();
    if(second==x){
      assign(last->prior(),first);
      assign(first->next(),base_pointer_from(last));
    }
    else{
      assign(last->prior(),x->prior());
      assign(x->prior()->next(),base_pointer_from(first));
    }
  }

  template<typename Assigner>
  static void unlink_second_of_group(pointer x,Assigner& assign)
  {
    pointer last=x->prior(),
            lastbutone=last->prior(),
            first=pointer_from(lastbutone->next());
    if(lastbutone==x){
      assign(first->next(),base_pointer_from(last));
      assign(last->prior(),first);
    }
    else{
      assign(first->next(),x->next());
      assign(x->next()->prior(),last);
    }
  }
};

template<typename Super>
struct hashed_index_node_trampoline:
  hashed_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,char
    >::type
  >
{
  typedef typename rebind_alloc_for<
    typename Super::allocator_type,char
  >::type                                             impl_allocator_type;
  typedef hashed_index_node_impl<impl_allocator_type> impl_type;
};

template<typename Super,typename Category>
struct hashed_index_node:
  Super,hashed_index_node_trampoline<Super>
{
private:
  typedef hashed_index_node_trampoline<Super> trampoline;

public:
  typedef typename trampoline::impl_type          impl_type;
  typedef hashed_index_node_alg<
    impl_type,Category>                           node_alg;
  typedef typename trampoline::base_pointer       impl_base_pointer;
  typedef typename trampoline::const_base_pointer const_impl_base_pointer;
  typedef typename trampoline::pointer            impl_pointer;
  typedef typename trampoline::const_pointer      const_impl_pointer;
  typedef typename trampoline::difference_type    difference_type;

  impl_pointer&      prior(){return trampoline::prior();}
  impl_pointer       prior()const{return trampoline::prior();}
  impl_base_pointer& next(){return trampoline::next();}
  impl_base_pointer  next()const{return trampoline::next();}

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

  static hashed_index_node* from_impl(impl_pointer x)
  {
    return
      static_cast<hashed_index_node*>(
        static_cast<trampoline*>(
          raw_ptr<impl_type*>(x)));
  }

  static const hashed_index_node* from_impl(const_impl_pointer x)
  {
    return 
      static_cast<const hashed_index_node*>(
        static_cast<const trampoline*>(
          raw_ptr<const impl_type*>(x)));
  }

  /* interoperability with hashed_index_iterator */

  static void increment(hashed_index_node*& x)
  {
    x=from_impl(node_alg::after(x->impl()));
  }

  static void increment_local(hashed_index_node*& x)
  {
    x=from_impl(node_alg::after_local(x->impl()));
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* hash_index_node.hpp
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
*/