/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_SAFE_MODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_SAFE_MODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

/* Safe mode machinery, in the spirit of Cay Hortmann's "Safe STL"
 * (http://www.horstmann.com/safestl.html).
 * In this mode, containers of type Container are derived from
 * safe_container<Container>, and their corresponding iterators
 * are wrapped with safe_iterator. These classes provide
 * an internal record of which iterators are at a given moment associated
 * to a given container, and properly mark the iterators as invalid
 * when the container gets destroyed.
 * Iterators are chained in a single attached list, whose header is
 * kept by the container. More elaborate data structures would yield better
 * performance, but I decided to keep complexity to a minimum since
 * speed is not an issue here.
 * Safe mode iterators automatically check that only proper operations
 * are performed on them: for instance, an invalid iterator cannot be
 * dereferenced. Additionally, a set of utilty macros and functions are
 * provided that serve to implement preconditions and cooperate with
 * the framework within the container.
 * Iterators can also be unchecked, i.e. they do not have info about
 * which container they belong in. This situation arises when the iterator
 * is restored from a serialization archive: only information on the node
 * is available, and it is not possible to determine to which container
 * the iterator is associated to. The only sensible policy is to assume
 * unchecked iterators are valid, though this can certainly generate false
 * positive safe mode checks.
 * This is not a full-fledged safe mode framework, and is only intended
 * for use within the limits of Boost.MultiIndex.
 */

/* Assertion macros. These resolve to no-ops if
 * !defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE).
 */

#if !defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
#undef BOOST_MULTI_INDEX_SAFE_MODE_ASSERT
#define BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(expr,error_code) ((void)0)
#else
#if !defined(BOOST_MULTI_INDEX_SAFE_MODE_ASSERT)
#include <boost/assert.hpp>
#define BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(expr,error_code) BOOST_ASSERT(expr)
#endif
#endif

#define BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it)                           \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_valid_iterator(it),                                     \
    safe_mode::invalid_iterator);

#define BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(it)                 \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_dereferenceable_iterator(it),                           \
    safe_mode::not_dereferenceable_iterator);

#define BOOST_MULTI_INDEX_CHECK_INCREMENTABLE_ITERATOR(it)                   \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_incrementable_iterator(it),                             \
    safe_mode::not_incrementable_iterator);

#define BOOST_MULTI_INDEX_CHECK_DECREMENTABLE_ITERATOR(it)                   \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_decrementable_iterator(it),                             \
    safe_mode::not_decrementable_iterator);

#define BOOST_MULTI_INDEX_CHECK_IS_OWNER(it,cont)                            \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_is_owner(it,cont),                                      \
    safe_mode::not_owner);

#define BOOST_MULTI_INDEX_CHECK_SAME_OWNER(it0,it1)                          \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_same_owner(it0,it1),                                    \
    safe_mode::not_same_owner);

#define BOOST_MULTI_INDEX_CHECK_VALID_RANGE(it0,it1)                         \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_valid_range(it0,it1),                                   \
    safe_mode::invalid_range);

#define BOOST_MULTI_INDEX_CHECK_OUTSIDE_RANGE(it,it0,it1)                    \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_outside_range(it,it0,it1),                              \
    safe_mode::inside_range);

#define BOOST_MULTI_INDEX_CHECK_IN_BOUNDS(it,n)                              \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_in_bounds(it,n),                                        \
    safe_mode::out_of_bounds);

#define BOOST_MULTI_INDEX_CHECK_DIFFERENT_CONTAINER(cont0,cont1)             \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_different_container(cont0,cont1),                       \
    safe_mode::same_container);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/detail/iterator.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/iter_adaptor.hpp>
#include <boost/multi_index/safe_mode_errors.hpp>
#include <boost/noncopyable.hpp>

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#endif

#if defined(BOOST_HAS_THREADS)
#include <boost/detail/lightweight_mutex.hpp>
#endif

namespace boost{

namespace multi_index{

namespace safe_mode{

/* Checking routines. Assume the best for unchecked iterators
 * (i.e. they pass the checking when there is not enough info
 * to know.)
 */

template<typename Iterator>
inline bool check_valid_iterator(const Iterator& it)
{
  return it.valid()||it.unchecked();
}

template<typename Iterator>
inline bool check_dereferenceable_iterator(const Iterator& it)
{
  return (it.valid()&&it!=it.owner()->end())||it.unchecked();
}

template<typename Iterator>
inline bool check_incrementable_iterator(const Iterator& it)
{
  return (it.valid()&&it!=it.owner()->end())||it.unchecked();
}

template<typename Iterator>
inline bool check_decrementable_iterator(const Iterator& it)
{
  return (it.valid()&&it!=it.owner()->begin())||it.unchecked();
}

template<typename Iterator>
inline bool check_is_owner(
  const Iterator& it,const typename Iterator::container_type& cont)
{
  return (it.valid()&&it.owner()==&cont)||it.unchecked();
}

template<typename Iterator>
inline bool check_same_owner(const Iterator& it0,const Iterator& it1)
{
  return (it0.valid()&&it1.valid()&&it0.owner()==it1.owner())||
         it0.unchecked()||it1.unchecked();
}

template<typename Iterator>
inline bool check_valid_range(const Iterator& it0,const Iterator& it1)
{
  if(!check_same_owner(it0,it1))return false;

  if(it0.valid()){
    Iterator last=it0.owner()->end();
    if(it1==last)return true;

    for(Iterator first=it0;first!=last;++first){
      if(first==it1)return true;
    }
    return false;
  }
  return true;
}

template<typename Iterator>
inline bool check_outside_range(
  const Iterator& it,const Iterator& it0,const Iterator& it1)
{
  if(!check_same_owner(it0,it1))return false;

  if(it0.valid()){
    Iterator last=it0.owner()->end();
    bool found=false;

    Iterator first=it0;
    for(;first!=last;++first){
      if(first==it1)break;
    
      /* crucial that this check goes after previous break */
    
      if(first==it)found=true;
    }
    if(first!=it1)return false;
    return !found;
  }
  return true;
}

template<typename Iterator,typename Difference>
inline bool check_in_bounds(const Iterator& it,Difference n)
{
  if(it.unchecked())return true;
  if(!it.valid())   return false;
  if(n>0)           return it.owner()->end()-it>=n;
  else              return it.owner()->begin()-it<=n;
}

template<typename Container>
inline bool check_different_container(
  const Container& cont0,const Container& cont1)
{
  return &cont0!=&cont1;
}

/* Invalidates all iterators equivalent to that given. Safe containers
 * must call this when deleting elements: the safe mode framework cannot
 * perform this operation automatically without outside help.
 */

template<typename Iterator>
inline void detach_equivalent_iterators(Iterator& it)
{
  if(it.valid()){
    {
#if defined(BOOST_HAS_THREADS)
      boost::detail::lightweight_mutex::scoped_lock lock(it.cont->mutex);
#endif

      Iterator *prev_,*next_;
      for(
        prev_=static_cast<Iterator*>(&it.cont->header);
        (next_=static_cast<Iterator*>(prev_->next))!=0;){
        if(next_!=&it&&*next_==it){
          prev_->next=next_->next;
          next_->cont=0;
        }
        else prev_=next_;
      }
    }
    it.detach();
  }
}

template<typename Container> class safe_container; /* fwd decl. */

} /* namespace multi_index::safe_mode */

namespace detail{

class safe_container_base;                 /* fwd decl. */

class safe_iterator_base
{
public:
  bool valid()const{return cont!=0;}
  bool unchecked()const{return unchecked_;}

  inline void detach();

  void uncheck()
  {
    detach();
    unchecked_=true;
  }

protected:
  safe_iterator_base():cont(0),next(0),unchecked_(false){}

  explicit safe_iterator_base(safe_container_base* cont_):
    unchecked_(false)
  {
    attach(cont_);
  }

  safe_iterator_base(const safe_iterator_base& it):
    unchecked_(it.unchecked_)
  {
    attach(it.cont);
  }

  safe_iterator_base& operator=(const safe_iterator_base& it)
  {
    unchecked_=it.unchecked_;
    safe_container_base* new_cont=it.cont;
    if(cont!=new_cont){
      detach();
      attach(new_cont);
    }
    return *this;
  }

  ~safe_iterator_base()
  {
    detach();
  }

  const safe_container_base* owner()const{return cont;}

BOOST_MULTI_INDEX_PRIVATE_IF_MEMBER_TEMPLATE_FRIENDS:
  friend class safe_container_base;

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  template<typename>          friend class safe_mode::safe_container;
  template<typename Iterator> friend
    void safe_mode::detach_equivalent_iterators(Iterator&);
#endif

  inline void attach(safe_container_base* cont_);

  safe_container_base* cont;
  safe_iterator_base*  next;
  bool                 unchecked_;
};

class safe_container_base:private noncopyable
{
public:
  safe_container_base(){}

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  friend class safe_iterator_base;

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  template<typename Iterator> friend
    void safe_mode::detach_equivalent_iterators(Iterator&);
#endif

  ~safe_container_base()
  {
    /* Detaches all remaining iterators, which by now will
     * be those pointing to the end of the container.
     */

    for(safe_iterator_base* it=header.next;it;it=it->next)it->cont=0;
    header.next=0;
  }

  void swap(safe_container_base& x)
  {
    for(safe_iterator_base* it0=header.next;it0;it0=it0->next)it0->cont=&x;
    for(safe_iterator_base* it1=x.header.next;it1;it1=it1->next)it1->cont=this;
    std::swap(header.cont,x.header.cont);
    std::swap(header.next,x.header.next);
  }

  safe_iterator_base header;

#if defined(BOOST_HAS_THREADS)
  boost::detail::lightweight_mutex mutex;
#endif
};

void safe_iterator_base::attach(safe_container_base* cont_)
{
  cont=cont_;
  if(cont){
#if defined(BOOST_HAS_THREADS)
    boost::detail::lightweight_mutex::scoped_lock lock(cont->mutex);
#endif

    next=cont->header.next;
    cont->header.next=this;
  }
}

void safe_iterator_base::detach()
{
  if(cont){
#if defined(BOOST_HAS_THREADS)
    boost::detail::lightweight_mutex::scoped_lock lock(cont->mutex);
#endif

    safe_iterator_base *prev_,*next_;
    for(prev_=&cont->header;(next_=prev_->next)!=this;prev_=next_){}
    prev_->next=next;
    cont=0;
  }
}

} /* namespace multi_index::detail */

namespace safe_mode{

/* In order to enable safe mode on a container:
 *   - The container must derive from safe_container<container_type>,
 *   - iterators must be generated via safe_iterator, which adapts a
 *     preexistent unsafe iterator class.
 */
 
template<typename Container>
class safe_container;

template<typename Iterator,typename Container>
class safe_iterator:
  public detail::iter_adaptor<safe_iterator<Iterator,Container>,Iterator>,
  public detail::safe_iterator_base
{
  typedef detail::iter_adaptor<safe_iterator,Iterator> super;
  typedef detail::safe_iterator_base                   safe_super;

public:
  typedef Container                                    container_type;
  typedef typename Iterator::reference                 reference;
  typedef typename Iterator::difference_type           difference_type;

  safe_iterator(){}
  explicit safe_iterator(safe_container<container_type>* cont_):
    safe_super(cont_){}
  template<typename T0>
  safe_iterator(const T0& t0,safe_container<container_type>* cont_):
    super(Iterator(t0)),safe_super(cont_){}
  template<typename T0,typename T1>
  safe_iterator(
    const T0& t0,const T1& t1,safe_container<container_type>* cont_):
    super(Iterator(t0,t1)),safe_super(cont_){}
  safe_iterator(const safe_iterator& x):super(x),safe_super(x){}

  safe_iterator& operator=(const safe_iterator& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(x);
    this->base_reference()=x.base_reference();
    safe_super::operator=(x);
    return *this;
  }

  const container_type* owner()const
  {
    return
      static_cast<const container_type*>(
        static_cast<const safe_container<container_type>*>(
          this->safe_super::owner()));
  }

  /* get_node is not to be used by the user */

  typedef typename Iterator::node_type node_type;

  node_type* get_node()const{return this->base_reference().get_node();}

private:
  friend class boost::multi_index::detail::iter_adaptor_access;

  reference dereference()const
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(*this);
    return *(this->base_reference());
  }

  bool equal(const safe_iterator& x)const
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(x);
    BOOST_MULTI_INDEX_CHECK_SAME_OWNER(*this,x);
    return this->base_reference()==x.base_reference();
  }

  void increment()
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    BOOST_MULTI_INDEX_CHECK_INCREMENTABLE_ITERATOR(*this);
    ++(this->base_reference());
  }

  void decrement()
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    BOOST_MULTI_INDEX_CHECK_DECREMENTABLE_ITERATOR(*this);
    --(this->base_reference());
  }

  void advance(difference_type n)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    BOOST_MULTI_INDEX_CHECK_IN_BOUNDS(*this,n);
    this->base_reference()+=n;
  }

  difference_type distance_to(const safe_iterator& x)const
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(x);
    BOOST_MULTI_INDEX_CHECK_SAME_OWNER(*this,x);
    return x.base_reference()-this->base_reference();
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* Serialization. Note that Iterator::save and Iterator:load
   * are assumed to be defined and public: at first sight it seems
   * like we could have resorted to the public serialization interface
   * for doing the forwarding to the adapted iterator class:
   *   ar<<base_reference();
   *   ar>>base_reference();
   * but this would cause incompatibilities if a saving
   * program is in safe mode and the loading program is not, or
   * viceversa --in safe mode, the archived iterator data is one layer
   * deeper, this is especially relevant with XML archives.
   * It'd be nice if Boost.Serialization provided some forwarding
   * facility for use by adaptor classes.
   */ 

  friend class boost::serialization::access;

  BOOST_SERIALIZATION_SPLIT_MEMBER()

  template<class Archive>
  void save(Archive& ar,const unsigned int version)const
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(*this);
    this->base_reference().save(ar,version);
  }

  template<class Archive>
  void load(Archive& ar,const unsigned int version)
  {
    this->base_reference().load(ar,version);
    safe_super::uncheck();
  }
#endif
};

template<typename Container>
class safe_container:public detail::safe_container_base
{
  typedef detail::safe_container_base super;

public:
  void detach_dereferenceable_iterators()
  {
    typedef typename Container::iterator iterator;

    iterator end_=static_cast<Container*>(this)->end();
    iterator *prev_,*next_;
    for(
      prev_=static_cast<iterator*>(&this->header);
      (next_=static_cast<iterator*>(prev_->next))!=0;){
      if(*next_!=end_){
        prev_->next=next_->next;
        next_->cont=0;
      }
      else prev_=next_;
    }
  }

  void swap(safe_container<Container>& x)
  {
    super::swap(x);
  }
};

} /* namespace multi_index::safe_mode */

} /* namespace multi_index */

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
namespace serialization{
template<typename Iterator,typename Container>
struct version<
  boost::multi_index::safe_mode::safe_iterator<Iterator,Container>
>
{
  BOOST_STATIC_CONSTANT(
    int,value=boost::serialization::version<Iterator>::value);
};
} /* namespace serialization */
#endif

} /* namespace boost */

#endif /* BOOST_MULTI_INDEX_ENABLE_SAFE_MODE */

#endif

/* safe_mode.hpp
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
*/