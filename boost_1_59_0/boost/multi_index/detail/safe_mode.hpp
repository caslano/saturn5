/* Copyright 2003-2022 Joaquin M Lopez Munoz.
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
 * In this mode, containers have to redefine their iterators as
 * safe_iterator<base_iterator> and keep a tracking object member of
 * type safe_container<safe_iterator<base_iterator> >. These classes provide
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

#define BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,cont)               \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_belongs_in_some_index(it,cont),                         \
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

#define BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(cont0,cont1)                 \
  BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(                                        \
    safe_mode::check_equal_allocators(cont0,cont1),                           \
    safe_mode::unequal_allocators);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/addressof.hpp>
  #include <boost/core/noncopyable.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/any_container_view.hpp>
#include <boost/multi_index/detail/iter_adaptor.hpp>
#include <boost/multi_index/safe_mode_errors.hpp>
#include <boost/type_traits/is_same.hpp>

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#endif

#if defined(BOOST_HAS_THREADS)
#include <boost/detail/lightweight_mutex.hpp>
#include <boost/multi_index/detail/scoped_bilock.hpp>
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

template<typename Iterator,typename Container>
inline bool check_is_owner(
  const Iterator& it,const Container& cont)
{
  return (it.valid()&&
            it.owner()->container()==cont.end().owner()->container())
         ||it.unchecked();
}

template<typename Iterator,typename MultiIndexContainer>
inline bool check_belongs_in_some_index(
  const Iterator& it,const MultiIndexContainer& cont)
{
  return (it.valid()&&it.owner()->end().get_node()==cont.end().get_node())
         ||it.unchecked();
} 

template<typename Iterator>
inline bool check_same_owner(const Iterator& it0,const Iterator& it1)
{
  return (it0.valid()&&it1.valid()&&
            it0.owner()->container()==it1.owner()->container())
         ||it0.unchecked()||it1.unchecked();
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

template<typename Iterator1,typename Iterator2>
inline bool check_outside_range(
  const Iterator1& it,const Iterator2& it0,const Iterator2& it1)
{
  if(it.valid()&&it!=it.owner()->end()&&it0.valid()){
    Iterator2 last=it0.owner()->end();
    bool found=false;

    Iterator2 first=it0;
    for(;first!=last;++first){
      if(first==it1)break;
    
      /* crucial that this check goes after previous break */
    
      if(boost::addressof(*first)==boost::addressof(*it))found=true;
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

template<typename Container1,typename Container2>
inline bool check_different_container(const Container1&,const Container2&)
{
  return true;
}

template<typename Container0,typename Container1>
inline bool check_equal_allocators(
  const Container0& cont0,const Container1& cont1)
{
  return cont0.get_allocator()==cont1.get_allocator();
}

/* fwd decls */

template<typename Container> class safe_container;
template<typename Iterator> void detach_equivalent_iterators(Iterator&);

namespace safe_mode_detail{

/* fwd decls */

class safe_container_base;
template<typename Dst,typename Iterator>
void transfer_equivalent_iterators(Dst&,Iterator,boost::true_type);
template<typename Dst,typename Iterator>
inline void transfer_equivalent_iterators(Dst&,Iterator&,boost::false_type);

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

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  friend class safe_container_base;
  template<typename>
  friend class safe_mode::safe_container;
  template<typename Iterator>
  friend void safe_mode::detach_equivalent_iterators(Iterator&);
  template<typename Dst,typename Iterator>
  friend void safe_mode_detail::transfer_equivalent_iterators(
    Dst&,Iterator,boost::true_type);
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

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  friend class safe_iterator_base;
  template<typename Iterator>
  friend void safe_mode::detach_equivalent_iterators(Iterator&);
  template<typename Dst,typename Iterator>
  friend void safe_mode_detail::transfer_equivalent_iterators(
    Dst&,Iterator,boost::true_type);
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

} /* namespace multi_index::safe_mode::safe_mode_detail */

/* In order to enable safe mode on a container:
 *   - The container must keep a member of type safe_container<iterator>,
 *   - iterators must be generated via safe_iterator, which adapts a
 *     preexistent unsafe iterator class. safe_iterators are passed the
 *     address of the previous safe_container member at construction time.
 */
 
template<typename Iterator>
class safe_iterator:
  public detail::iter_adaptor<safe_iterator<Iterator>,Iterator>,
  public safe_mode_detail::safe_iterator_base
{
  typedef detail::iter_adaptor<safe_iterator,Iterator> super;
  typedef safe_mode_detail::safe_iterator_base         safe_super;

public:
  typedef typename Iterator::reference                 reference;
  typedef typename Iterator::difference_type           difference_type;

  safe_iterator(){}
  explicit safe_iterator(safe_container<safe_iterator>* cont_):
    safe_super(cont_){}
  template<typename T0>
  safe_iterator(const T0& t0,safe_container<safe_iterator>* cont_):
    super(Iterator(t0)),safe_super(cont_){}
  template<typename T0,typename T1>
  safe_iterator(
    const T0& t0,const T1& t1,safe_container<safe_iterator>* cont_):
    super(Iterator(t0,t1)),safe_super(cont_){}
  safe_iterator(const safe_iterator& x):super(x),safe_super(x){}

  safe_iterator& operator=(const safe_iterator& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(x);
    this->base_reference()=x.base_reference();
    safe_super::operator=(x);
    return *this;
  }

  const safe_container<safe_iterator>* owner()const
  {
    return
      static_cast<const safe_container<safe_iterator>*>(
        this->safe_super::owner());
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

template<typename Iterator>
class safe_container:public safe_mode_detail::safe_container_base
{
  typedef safe_mode_detail::safe_container_base super;

  detail::any_container_view<Iterator> view;

public:
  template<typename Container>
  safe_container(const Container& c):view(c){}

  const void* container()const{return view.container();}
  Iterator    begin()const{return view.begin();}
  Iterator    end()const{return view.end();}

  void detach_dereferenceable_iterators()
  {
    Iterator end_=view.end();
    Iterator *prev_,*next_;
    for(
      prev_=static_cast<Iterator*>(&this->header);
      (next_=static_cast<Iterator*>(prev_->next))!=0;){
      if(*next_!=end_){
        prev_->next=next_->next;
        next_->cont=0;
      }
      else prev_=next_;
    }
  }

  void swap(safe_container<Iterator>& x)
  {
    super::swap(x);
  }
};

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

/* Transfers iterators equivalent to that given to Dst, if that container has
 * the same iterator type; otherwise, detaches them.
 */

template<typename Dst,typename Iterator>
inline void transfer_equivalent_iterators(Dst& dst,Iterator& i)
{
  safe_mode_detail::transfer_equivalent_iterators(
    dst,i,boost::is_same<Iterator,typename Dst::iterator>());
}

namespace safe_mode_detail{

template<typename Dst,typename Iterator>
inline void transfer_equivalent_iterators(
  Dst& dst,Iterator it,boost::true_type /* same iterator type */)
{
  if(it.valid()){
    {
      safe_container_base* cont_=dst.end().cont;

#if defined(BOOST_HAS_THREADS)
      detail::scoped_bilock<boost::detail::lightweight_mutex>
      scoped_bilock(it.cont->mutex,cont_->mutex);
#endif

      Iterator *prev_,*next_;
      for(
        prev_=static_cast<Iterator*>(&it.cont->header);
        (next_=static_cast<Iterator*>(prev_->next))!=0;){
        if(next_!=&it&&*next_==it){
          prev_->next=next_->next;
          next_->cont=cont_;
          next_->next=cont_->header.next;
          cont_->header.next=next_;
        }
        else prev_=next_;
      }
    }
    /* nothing to do with it, was passed by value and will die now */
  }
}

template<typename Dst,typename Iterator>
inline void transfer_equivalent_iterators(
  Dst&,Iterator& it,boost::false_type /* same iterator type */)
{
  detach_equivalent_iterators(it);
}

} /* namespace multi_index::safe_mode::safe_mode_detail */

} /* namespace multi_index::safe_mode */

} /* namespace multi_index */

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
namespace serialization{
template<typename Iterator>
struct version<
  boost::multi_index::safe_mode::safe_iterator<Iterator>
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