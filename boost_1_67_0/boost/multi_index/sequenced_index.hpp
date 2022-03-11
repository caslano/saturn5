/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_SEQUENCED_INDEX_HPP
#define BOOST_MULTI_INDEX_SEQUENCED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/bind/bind.hpp>
#include <boost/call_traits.hpp>
#include <boost/core/addressof.hpp>
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/foreach_fwd.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/bidir_node_iterator.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/safe_mode.hpp>
#include <boost/multi_index/detail/scope_guard.hpp>
#include <boost/multi_index/detail/seq_index_node.hpp>
#include <boost/multi_index/detail/seq_index_ops.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/multi_index/sequenced_index_fwd.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <functional>
#include <utility>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include<initializer_list>
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
#define BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT_OF(x)                    \
  detail::scope_guard BOOST_JOIN(check_invariant_,__LINE__)=                 \
    detail::make_obj_guard(x,&sequenced_index::check_invariant_);            \
  BOOST_JOIN(check_invariant_,__LINE__).touch();
#define BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT                          \
  BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT_OF(*this)
#else
#define BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT_OF(x)
#define BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* sequenced_index adds a layer of sequenced indexing to a given Super */

template<typename SuperMeta,typename TagList>
class sequenced_index:
  BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS SuperMeta::type

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  ,public safe_mode::safe_container<
    sequenced_index<SuperMeta,TagList> >
#endif

{ 
#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
/* The "ISO C++ Template Parser" option in CW8.3 has a problem with the
 * lifetime of const references bound to temporaries --precisely what
 * scopeguards are.
 */

#pragma parse_mfunc_templ off
#endif

  typedef typename SuperMeta::type               super;

protected:
  typedef sequenced_index_node<
    typename super::node_type>                   node_type;

private:
  typedef typename node_type::impl_type          node_impl_type;
 
public:
  /* types */

  typedef typename node_type::value_type         value_type;
  typedef tuples::null_type                      ctor_args;
  typedef typename super::final_allocator_type   allocator_type;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_iterator<
    bidir_node_iterator<node_type>,
    sequenced_index>                             iterator;
#else
  typedef bidir_node_iterator<node_type>         iterator;
#endif

  typedef iterator                               const_iterator;

private:
  typedef allocator_traits<allocator_type>       alloc_traits;

public:
  typedef typename alloc_traits::pointer         pointer;
  typedef typename alloc_traits::const_pointer   const_pointer;
  typedef typename alloc_traits::size_type       size_type;
  typedef typename alloc_traits::difference_type difference_type;
  typedef typename
    boost::reverse_iterator<iterator>            reverse_iterator;
  typedef typename
    boost::reverse_iterator<const_iterator>      const_reverse_iterator;
  typedef TagList                                tag_list;

protected:
  typedef typename super::final_node_type     final_node_type;
  typedef tuples::cons<
    ctor_args, 
    typename super::ctor_args_list>           ctor_args_list;
  typedef typename mpl::push_front<
    typename super::index_type_list,
    sequenced_index>::type                    index_type_list;
  typedef typename mpl::push_front<
    typename super::iterator_type_list,
    iterator>::type                           iterator_type_list;
  typedef typename mpl::push_front<
    typename super::const_iterator_type_list,
    const_iterator>::type                     const_iterator_type_list;
  typedef typename super::copy_map_type       copy_map_type;

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  typedef typename super::index_saver_type    index_saver_type;
  typedef typename super::index_loader_type   index_loader_type;
#endif

private:
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_container<
    sequenced_index>                          safe_super;
#endif

  typedef typename call_traits<value_type>::param_type value_param_type;

  /* Needed to avoid commas in BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL
   * expansion.
   */

  typedef std::pair<iterator,bool>                     emplace_return_type;

public:

  /* construct/copy/destroy
   * Default and copy ctors are in the protected section as indices are
   * not supposed to be created on their own. No range ctor either.
   */

  sequenced_index<SuperMeta,TagList>& operator=(
    const sequenced_index<SuperMeta,TagList>& x)
  {
    this->final()=x.final();
    return *this;
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  sequenced_index<SuperMeta,TagList>& operator=(
    std::initializer_list<value_type> list)
  {
    this->final()=list;
    return *this;
  }
#endif

  template <class InputIterator>
  void assign(InputIterator first,InputIterator last)
  {
    assign_iter(first,last,mpl::not_<is_integral<InputIterator> >());
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  void assign(std::initializer_list<value_type> list)
  {
    assign(list.begin(),list.end());
  }
#endif

  void assign(size_type n,value_param_type value)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    clear();
    for(size_type i=0;i<n;++i)push_back(value);
  }
    
  allocator_type get_allocator()const BOOST_NOEXCEPT
  {
    return this->final().get_allocator();
  }

  /* iterators */

  iterator  begin()BOOST_NOEXCEPT
    {return make_iterator(node_type::from_impl(header()->next()));}
  const_iterator begin()const BOOST_NOEXCEPT
    {return make_iterator(node_type::from_impl(header()->next()));}
  iterator
    end()BOOST_NOEXCEPT{return make_iterator(header());}
  const_iterator
    end()const BOOST_NOEXCEPT{return make_iterator(header());}
  reverse_iterator
    rbegin()BOOST_NOEXCEPT{return boost::make_reverse_iterator(end());}
  const_reverse_iterator
    rbegin()const BOOST_NOEXCEPT{return boost::make_reverse_iterator(end());}
  reverse_iterator
    rend()BOOST_NOEXCEPT{return boost::make_reverse_iterator(begin());}
  const_reverse_iterator
    rend()const BOOST_NOEXCEPT{return boost::make_reverse_iterator(begin());}
  const_iterator
    cbegin()const BOOST_NOEXCEPT{return begin();}
  const_iterator
    cend()const BOOST_NOEXCEPT{return end();}
  const_reverse_iterator
    crbegin()const BOOST_NOEXCEPT{return rbegin();}
  const_reverse_iterator
    crend()const BOOST_NOEXCEPT{return rend();}

  iterator iterator_to(const value_type& x)
  {
    return make_iterator(node_from_value<node_type>(boost::addressof(x)));
  }

  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(node_from_value<node_type>(boost::addressof(x)));
  }

  /* capacity */

  bool      empty()const BOOST_NOEXCEPT{return this->final_empty_();}
  size_type size()const BOOST_NOEXCEPT{return this->final_size_();}
  size_type max_size()const BOOST_NOEXCEPT{return this->final_max_size_();}

  void resize(size_type n)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(n>size()){
      for(size_type m=n-size();m--;)
        this->final_emplace_(BOOST_MULTI_INDEX_NULL_PARAM_PACK);
    }
    else if(n<size()){for(size_type m=size()-n;m--;)pop_back();}
  }

  void resize(size_type n,value_param_type x)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(n>size())insert(end(),static_cast<size_type>(n-size()),x);
    else if(n<size())for(size_type m=size()-n;m--;)pop_back();
  }

  /* access: no non-const versions provided as sequenced_index
   * handles const elements.
   */

  const_reference front()const{return *begin();}
  const_reference back()const{return *--end();}

  /* modifiers */

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(
    emplace_return_type,emplace_front,emplace_front_impl)

  std::pair<iterator,bool> push_front(const value_type& x)
                             {return insert(begin(),x);}
  std::pair<iterator,bool> push_front(BOOST_RV_REF(value_type) x)
                             {return insert(begin(),boost::move(x));}
  void                     pop_front(){erase(begin());}

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(
    emplace_return_type,emplace_back,emplace_back_impl)

  std::pair<iterator,bool> push_back(const value_type& x)
                             {return insert(end(),x);}
  std::pair<iterator,bool> push_back(BOOST_RV_REF(value_type) x)
                             {return insert(end(),boost::move(x));}
  void                     pop_back(){erase(--end());}

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(
    emplace_return_type,emplace,emplace_impl,iterator,position)

  std::pair<iterator,bool> insert(iterator position,const value_type& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_(x);
    if(p.second&&position.get_node()!=header()){
      relink(position.get_node(),p.first);
    }
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  std::pair<iterator,bool> insert(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_rv_(x);
    if(p.second&&position.get_node()!=header()){
      relink(position.get_node(),p.first);
    }
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  void insert(iterator position,size_type n,value_param_type x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    for(size_type i=0;i<n;++i)insert(position,x);
  }
 
  template<typename InputIterator>
  void insert(iterator position,InputIterator first,InputIterator last)
  {
    insert_iter(position,first,last,mpl::not_<is_integral<InputIterator> >());
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  void insert(iterator position,std::initializer_list<value_type> list)
  {
    insert(position,list.begin(),list.end());
  }
#endif

  iterator erase(iterator position)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    this->final_erase_(static_cast<final_node_type*>(position++.get_node()));
    return position;
  }
  
  iterator erase(iterator first,iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,*this);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    while(first!=last){
      first=erase(first);
    }
    return first;
  }

  bool replace(iterator position,const value_type& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    return this->final_replace_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  bool replace(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    return this->final_replace_rv_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier>
  bool modify(iterator position,Modifier mod)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer on safe mode code chokes if this
     * this is not added. Left it for all compilers as it does no
     * harm.
     */

    position.detach();
#endif

    return this->final_modify_(
      mod,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier,typename Rollback>
  bool modify(iterator position,Modifier mod,Rollback back_)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer on safe mode code chokes if this
     * this is not added. Left it for all compilers as it does no
     * harm.
     */

    position.detach();
#endif

    return this->final_modify_(
      mod,back_,static_cast<final_node_type*>(position.get_node()));
  }

  void swap(sequenced_index<SuperMeta,TagList>& x)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT_OF(x);
    this->final_swap_(x.final());
  }

  void clear()BOOST_NOEXCEPT
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    this->final_clear_();
  }

  /* list operations */

  void splice(iterator position,sequenced_index<SuperMeta,TagList>& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_DIFFERENT_CONTAINER(*this,x);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    iterator first=x.begin(),last=x.end();
    while(first!=last){
      if(insert(position,*first).second)first=x.erase(first);
      else ++first;
    }
  }

  void splice(iterator position,sequenced_index<SuperMeta,TagList>& x,iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,x);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(&x==this){
      if(position!=i)relink(position.get_node(),i.get_node());
    }
    else{
      if(insert(position,*i).second){

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer has a hard time with safe mode, and the following
     * workaround is needed. Left it for all compilers as it does no
     * harm.
     */
        i.detach();
        x.erase(x.make_iterator(i.get_node()));
#else
        x.erase(i);
#endif

      }
    }
  }

  void splice(
    iterator position,sequenced_index<SuperMeta,TagList>& x,
    iterator first,iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,x);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,x);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(&x==this){
      BOOST_MULTI_INDEX_CHECK_OUTSIDE_RANGE(position,first,last);
      if(position!=last)relink(
        position.get_node(),first.get_node(),last.get_node());
    }
    else{
      while(first!=last){
        if(insert(position,*first).second)first=x.erase(first);
        else ++first;
      }
    }
  }

  void remove(value_param_type value)
  {
    sequenced_index_remove(
      *this,
      ::boost::bind(std::equal_to<value_type>(),::boost::arg<1>(),value));
  }

  template<typename Predicate>
  void remove_if(Predicate pred)
  {
    sequenced_index_remove(*this,pred);
  }

  void unique()
  {
    sequenced_index_unique(*this,std::equal_to<value_type>());
  }

  template <class BinaryPredicate>
  void unique(BinaryPredicate binary_pred)
  {
    sequenced_index_unique(*this,binary_pred);
  }

  void merge(sequenced_index<SuperMeta,TagList>& x)
  {
    sequenced_index_merge(*this,x,std::less<value_type>());
  }

  template <typename Compare>
  void merge(sequenced_index<SuperMeta,TagList>& x,Compare comp)
  {
    sequenced_index_merge(*this,x,comp);
  }

  void sort()
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    sequenced_index_sort(header(),std::less<value_type>());
  }

  template <typename Compare>
  void sort(Compare comp)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    sequenced_index_sort(header(),comp);
  }

  void reverse()BOOST_NOEXCEPT
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    node_impl_type::reverse(header()->impl());
  }

  /* rearrange operations */

  void relocate(iterator position,iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(position!=i)relink(position.get_node(),i.get_node());
  }

  void relocate(iterator position,iterator first,iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,*this);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_CHECK_OUTSIDE_RANGE(position,first,last);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(position!=last)relink(
      position.get_node(),first.get_node(),last.get_node());
  }
    
  template<typename InputIterator>
  void rearrange(InputIterator first)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    node_type* pos=header();
    for(size_type s=size();s--;){
      const value_type& v=*first++;
      relink(pos,node_from_value<node_type>(&v));
    }
  }

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  sequenced_index(const ctor_args_list& args_list,const allocator_type& al):
    super(args_list.get_tail(),al)
  {
    empty_initialize();
  }

  sequenced_index(const sequenced_index<SuperMeta,TagList>& x):
    super(x)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe_super()
#endif

  {
    /* the actual copying takes place in subsequent call to copy_() */
  }

  sequenced_index(
    const sequenced_index<SuperMeta,TagList>& x,do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag())

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe_super()
#endif

  {
    empty_initialize();
  }

  ~sequenced_index()
  {
    /* the container is guaranteed to be empty by now */
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  iterator       make_iterator(node_type* node){return iterator(node,this);}
  const_iterator make_iterator(node_type* node)const
    {return const_iterator(node,const_cast<sequenced_index*>(this));}
#else
  iterator       make_iterator(node_type* node){return iterator(node);}
  const_iterator make_iterator(node_type* node)const
                   {return const_iterator(node);}
#endif

  void copy_(
    const sequenced_index<SuperMeta,TagList>& x,const copy_map_type& map)
  {
    node_type* org=x.header();
    node_type* cpy=header();
    do{
      node_type* next_org=node_type::from_impl(org->next());
      node_type* next_cpy=map.find(static_cast<final_node_type*>(next_org));
      cpy->next()=next_cpy->impl();
      next_cpy->prior()=cpy->impl();
      org=next_org;
      cpy=next_cpy;
    }while(org!=x.header());

    super::copy_(x,map);
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,final_node_type*& x,Variant variant)
  {
    final_node_type* res=super::insert_(v,x,variant);
    if(res==x)link(static_cast<node_type*>(x));
    return res;
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,node_type* position,final_node_type*& x,Variant variant)
  {
    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x)link(static_cast<node_type*>(x));
    return res;
  }

  void erase_(node_type* x)
  {
    unlink(x);
    super::erase_(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    detach_iterators(x);
#endif
  }

  void delete_all_nodes_()
  {
    for(node_type* x=node_type::from_impl(header()->next());x!=header();){
      node_type* y=node_type::from_impl(x->next());
      this->final_delete_node_(static_cast<final_node_type*>(x));
      x=y;
    }
  }

  void clear_()
  {
    super::clear_();
    empty_initialize();

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super::detach_dereferenceable_iterators();
#endif
  }

  template<typename BoolConstant>
  void swap_(
    sequenced_index<SuperMeta,TagList>& x,BoolConstant swap_allocators)
  {
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super::swap(x);
#endif

    super::swap_(x,swap_allocators);
  }

  void swap_elements_(sequenced_index<SuperMeta,TagList>& x)
  {
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super::swap(x);
#endif

    super::swap_elements_(x);
  }

  template<typename Variant>
  bool replace_(value_param_type v,node_type* x,Variant variant)
  {
    return super::replace_(v,x,variant);
  }

  bool modify_(node_type* x)
  {
    BOOST_TRY{
      if(!super::modify_(x)){
        unlink(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
        detach_iterators(x);
#endif

        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      unlink(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
      detach_iterators(x);
#endif

      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool modify_rollback_(node_type* x)
  {
    return super::modify_rollback_(x);
  }

  bool check_rollback_(node_type* x)const
  {
    return super::check_rollback_(x);
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* serialization */

  template<typename Archive>
  void save_(
    Archive& ar,const unsigned int version,const index_saver_type& sm)const
  {
    sm.save(begin(),end(),ar,version);
    super::save_(ar,version,sm);
  }

  template<typename Archive>
  void load_(
    Archive& ar,const unsigned int version,const index_loader_type& lm)
  {
    lm.load(
      ::boost::bind(
        &sequenced_index::rearranger,this,::boost::arg<1>(),::boost::arg<2>()),
      ar,version);
    super::load_(ar,version,lm);
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const
  {
    if(size()==0||begin()==end()){
      if(size()!=0||begin()!=end()||
         header()->next()!=header()->impl()||
         header()->prior()!=header()->impl())return false;
    }
    else{
      size_type s=0;
      for(const_iterator it=begin(),it_end=end();it!=it_end;++it,++s){
        if(it.get_node()->next()->prior()!=it.get_node()->impl())return false;
        if(it.get_node()->prior()->next()!=it.get_node()->impl())return false;
      }
      if(s!=size())return false;
    }

    return super::invariant_();
  }

  /* This forwarding function eases things for the boost::mem_fn construct
   * in BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT. Actually,
   * final_check_invariant is already an inherited member function of index.
   */
  void check_invariant_()const{this->final_check_invariant_();}
#endif

private:
  node_type* header()const{return this->final_header();}

  void empty_initialize()
  {
    header()->prior()=header()->next()=header()->impl();
  }

  void link(node_type* x)
  {
    node_impl_type::link(x->impl(),header()->impl());
  }

  static void unlink(node_type* x)
  {
    node_impl_type::unlink(x->impl());
  }

  static void relink(node_type* position,node_type* x)
  {
    node_impl_type::relink(position->impl(),x->impl());
  }

  static void relink(node_type* position,node_type* first,node_type* last)
  {
    node_impl_type::relink(
      position->impl(),first->impl(),last->impl());
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  void rearranger(node_type* position,node_type *x)
  {
    if(!position)position=header();
    node_type::increment(position);
    if(position!=x)relink(position,x);
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  void detach_iterators(node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::detach_equivalent_iterators(it);
  }
#endif

  template <class InputIterator>
  void assign_iter(InputIterator first,InputIterator last,mpl::true_)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    clear();
    for(;first!=last;++first)this->final_insert_ref_(*first);
  }

  void assign_iter(size_type n,value_param_type value,mpl::false_)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    clear();
    for(size_type i=0;i<n;++i)push_back(value);
  }

  template<typename InputIterator>
  void insert_iter(
    iterator position,InputIterator first,InputIterator last,mpl::true_)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    for(;first!=last;++first){
      std::pair<final_node_type*,bool> p=
        this->final_insert_ref_(*first);
      if(p.second&&position.get_node()!=header()){
        relink(position.get_node(),p.first);
      }
    }
  }

  void insert_iter(
    iterator position,size_type n,value_param_type x,mpl::false_)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    for(size_type i=0;i<n;++i)insert(position,x);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<iterator,bool> emplace_front_impl(
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    return emplace_impl(begin(),BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<iterator,bool> emplace_back_impl(
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    return emplace_impl(end(),BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<iterator,bool> emplace_impl(
    iterator position,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=
      this->final_emplace_(BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
    if(p.second&&position.get_node()!=header()){
      relink(position.get_node(),p.first);
    }
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif
};

/* comparison */

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return !(x==y);
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return y<x;
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return !(x<y);
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return !(x>y);
}

/*  specialized algorithms */

template<typename SuperMeta,typename TagList>
void swap(
  sequenced_index<SuperMeta,TagList>& x,
  sequenced_index<SuperMeta,TagList>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

/* sequenced index specifier */

template <typename TagList>
struct sequenced
{
  BOOST_STATIC_ASSERT(detail::is_tag<TagList>::value);

  template<typename Super>
  struct node_class
  {
    typedef detail::sequenced_index_node<Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::sequenced_index<SuperMeta,typename TagList::type> type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

/* Boost.Foreach compatibility */

template<typename SuperMeta,typename TagList>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::sequenced_index<SuperMeta,TagList>*&,
  boost_foreach_argument_dependent_lookup_hack)
{
  return 0;
}

#undef BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT
#undef BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT_OF

#endif

/* sequenced_index.hpp
djXWxHUJ7TZazPJnEMj0VsxckP2tkbcheBpR0Bsvr3DhdMqLPlrVBxLBwVM15yWuzero2Gr1vvGS3E15biYrNHJEadYcrLqvaLvuRfrP9FSR9f9ooG1UrlNK4fgy7nkX9fa1rWSIpMDjto873SD1cdMhtkm9gy9hjVl+WiaEWTSmPoRH1yj3HEAOp9uwURQa+F6vWZaYW8SV1PQeRBJgRzELW5IobhTQpq63rCJxJnluMaHI2EcevsiynhlYCnr4LLmXpkR0n5tuPwjLA25rQbG8S92iteP2P5paJppJqUQFdlnZjDfTZdY7iaDaZNQ6nZ2Q5x9vN05fer/2Zlumttah0vL5vW+So8hjm0GoXLDS/KS1vAtJrYVz1fpcKJDpYTiUdmT86HBitXBEMhB6StmGBvWtLvAxxkcdBrClqGMxbJxrRsCpYm9hNddjg41QgtSszowierHHRgZzx2LRvKoKSaz0Zyvg6Mgn75k8l5ssSQX3BrCOG4Lr+r6C2tFeMepZNv7IpNNBdsyTZKlgQtYkfntnJzU4lbxmC/Na+7jvGEgzUqfqmGzbvFRqcd2AWI5y+A+Ob87e6bQudFt5ujgjdtibI37IXK/nVaX0kwm1l8OV/ssVSh4r/JTz8TOBSlhgu9Frrm128QO3BviP3GGt7V/vNI9KfW+gutqlcBzyocXZpvcLJXvExY6zmkJ0C+Pg01wL3Zae0MMEIw8vfDezBLhXETc4yaiykMBs9V9nSKv+jZK2idPj4bBUr2Ase+rAi+l/2s8/CRG/wIc7e5sGBooQCH0ORcf1RBGKrcPUYLX9qGu4JFWXBN+/T07mkDGxukfWOQb3wAuKvaieM3vxQEkrlHxIA9Eqaj/Ub9vUyck8g44KUExHyN2NjzLJ1HrOKDyRmDQ/zNQv3TNLbG2hQjQu+is7qcgoVgyFuJLqaZsAzVCpZwuDhl2t2rL4dE1BadTAp9ypYUW27OQ7K+me/xdthyFH9Amrk52/aV9Vxu28QKAI94wF50S2uiuEz0/t9OGhLBpxifeJ8oTG+yd4eumwrTF1J8xZlWaKphmdGIYVBM7MrJniKlGxQQbcGAXaPorvzYZM9tN3sMR956iMyNviH6EPGTcUSPYM3fLs2crHt/+S6t8/7QPRfmy2wvgHfridoNAA/yV3N5j7PX/+ZjJFIEL+nxdOHuyLH7i9d3igRhaYHafGEpPqodYk0JJR+cGCaXGyy6N5IfQh46PzxlAmY4rN1hpW6KnWeRRSOBsK5khlSAhqMR/cL7wzPjnXei/O11+TD5856W8HLx8HLysXXx8+aObg5mE/pkLqNV25YVZudsSQotRu8jjCMycqj077/ckcbUF20j74Od3Uleq2czgqst0SB9/RI5LSQ/zXMRVt4hF0PZxyubQAXLzFfvNydvtHdGTO+SM3TOUZlF9IhOddR7WTuSV/4TK7OHGyPQv7q7vyirSAmZ5XCyDDoZyMa2MxHIkSuL9QDB6J0Da0WTI8NXUYjXHUeWnG6G2GIio1ipZiUO7lKKs3VD6zpG76vnaPbzv+bnhMw2YsILTbledNL8fXQJMSiIwNCsnQiljUm2towTOpcp7KUrQ+dtpvbrpuWzyrh75wbaENzJhUq1xvsuxGzNA8eQ9DS09OR4gNqVKzphSQjx9pWXZJN9lsIHqXqV1xKsXaesst+MjTGRgpNY6yMFUwaVVWJnwVu2Une2svSy8wWCJTBT6i5Lwkr+P/aBp2RovuyxLbxEs/5Iuw6RWVFm1hZuOx81aFnB5Gw+osW8H+2FJ5Z5JRt69D0gC5qJuD/Ne47/ypugWaRiKt8T5OSRUyTlLS3Dgqtw0OCakLc2ZFQNBlcKVMXuddSGSRhB+AH1xenqRQoTevsaQp+4BbngSACgrp69c3qKVXR6eGRgX93fzBo5lsdgSv1lw1JmBEWY4F/u+7/PCjyn4P9EdkK/pC5+OXl7Ax9IogY3Xg5wUXLJjgtsCQOA2941a6cbM1vfWZTRuUYDViz9XdYmtDuTwnTJi0l3OsQ3bhexrgPb/oEwulVeLhay+xchdESZs3kPdk6rWVkSuln2M3lGCiiD5r2r1oyC7bwcohpLS+lGKvvF+kb1liil15PxOX0E9AqTjdAeXY0Xol0D8/O0SZDM5w33p45v8vNt4xVtigWbB9t23btm3btm3btm3btm3btr33/c4gmZlzs5JK1er+9aTzpNLpbtEFtzGDe28u1Z4cPXjyL7m5XIw92FTUPG61e1Z3rG6YXVC7oLaBrX2b/5Rfcw+vEXzdMjEM6miS8MyYqV2eASmB5UlzVOayYYRkksjsxnH2zQ1PWJaXK1bYfq73nodyXRpJmXgNi113PD4KTVAdgkiVXqkHT7Nc8QnjXkh7B7zpEp18TiJs7rMeDTtKRtq+0sXWYVsrpe2KYxs6BOjGTwY5ggGWihN9jJ5nfQ7Me20O2FWxqeRo02Fnq/vm9szsmNgwsaBiQUUDC/vneOMLwy0dcTiKggVfwBc7ugxSkqSgyhDMdCACRbC9d++e5oJM0i46Z73RcBvrY2gSxfy+KRwcZc9DVkEcsamNID35Zn0gaEFRAyP7hvYM7eja0LSg/yn/1F6BUFJP9usbGg7oWVlP41NSfl5npE4qtHKlYLuQR2V8Ebf2I3SP7ovhxezMjRLArsEg/8fi+D8Wwm9VXZxbTdIwPmSomw65eIJqT9WuLpG6fcLh3wIrufPY78FoZJNDTQwiaRYxTvRORupaz1HV12AI+afxVNtt3Hbi76oju8UAWgvLlNRCUpxMd17tnnNfZ+/qqNr0TfMyI5uX52rU6sJvSt/FhYUpwdBBI7Y3KCCoXScsugf67qJ50zRlvBoy69SfzDypQLHzobXzU5d/nraclMtl1NwOekme92FevkhDxxAmawBXVW9CZkqXVs+gz8lYz4YN8cbCfed73cXVjmASDOf4EW/AYrV3lp0zzk97+HnzE3T3HwVzxjrBxbeTqXPeOxDN3bDV6OpYVSS3+eXSJMvjEhZfBYieFkdWWMsCBo2InL7eO7d68Fze5USGcvKmBxmth9CJyenzMUX2ZL5tm/jyVU8rbw0d3zWLrU9CC0n71FWRF61SCrHrZf5iq2vCeVbeLDu2PFPL0NwVgSgKFJr2+G1aHxctlibAf+MgzAakr0X1XMcmJFwhT8zrmMWm9qy9Cl4BdN3IEbmGwc5k+2yG2QNMeai2rmXcd+48mRKpjUph0A1lOM1GNhEPsfQIzHWcPW9+u2FCcGb8sb3QtYS7KdLi91jZ+3HNM0yAqzYUllFQNm9TnvWgj2Z/OCUDOYEOT5fNSMZuAw2SR4K24nTGbIdrjX5t73C50dHS0DBvx3esEzSrqM3K22IDiXC0zY50+3W3vWRGtPym9eBhQBSvzagI5ICFoEJCA7p1QKoHmNRTON/Jx3QDIPZ5kSePhjAGxrDM1RPBUo5JtLWlD+Wl1rnRDTzN2+TTpHaKZH+lAo6cYlnkWRY5dyoxeMhsHtoOUpE4QsP7+Bv38C6qGyBz9bC3eTkue7RBjrnadsVvMVWwPlTALrfEbOy8lXPigG76omVV9JaWqqpvhLwi12pB5YP9o4RNdVEVAEXynhuprg05KbnVrZX27kk9cjzgPQXK2h79NqUG153sKRcmgTusQKQiNNnPTm/ODqegbxPhE+QBaR7hv8M3/55V0hIr3i4liHEvSv20qcfpbPozvkQQJxSraA65IdIy9dFjj5dJyLFMTx/n0OflcM+rE0eAVOheogu+oh+TwoErByc5KjbM7X3xPbXkGGZKgzbTTLY67f/RVpv+7kNWBUyfgBWLfgZjTsp55HrTlvnRjk5nDzs12PEAjAPhwyPja9+3yTt6B++3HZ2aqlY4SQSFeqOnAcgBJpZWedL+nT40kvWdq9mtiRe2Yd2/1x1rTe1JkTSUycBsgouMN9l6HOQxNGTGTzCKdYM9YOZtkdxgpkD7qMEKYZMxg8mSIr5ij7JGrHkWUfK8cyW2Tr9JNESClLv1hLTXfG0Gk8g/DygTbO0qA0fPk44rDVcKthR0MfCs7/mf8pfuy7b/Ca/0jpAhfH08vnHz+/dRUqkLRPgTObV0SkQBQ0lT7mtaTGpduMA+k6dGxzf7iGTnbs9wOCnDqtrwg4tMKEHN0Mp2mubuMN758mj9eiys9ZS4BXmxqHpZPLqBmijs0LIRC4CgHFqpJgcxtr4jPJXiNccOH3xSm+ryqR9iu0ojrUHBgvNR3q/oPlEJwtd71K8L8GvBI0fpK+u4rO7N+/J5UGzWWBea9nSIqZwhI1x8uSzIxECMcDZ7a0t9FNm9jOC22WU7k+kZs1NAIMVlmq/pfXrNp5IUKhZwRgLxKGoXFVp35vX8vPlmWPT2VvSAQHtxV9myqZhZE5OGxIMgedROYtBmIl9h1F71MV3So+C6yr2zWqYm0VdmZQt8AprJZqTi8Yl0PdfQia2te3vYa+kYPkrzTi/QJ1bF7lOFL1AlFDk0elkdCbdWVydnZGbVIZLpogRDqp8JyK8GfxuV0EpK8x8rehC50yochxudiY+fLu01BzAMwP/BQxnb8B4AO4x3wQvq/3hzZ8dMHsmrr/8huBBfRxhQOBO5QlA+0h9ZBN6CMNyZ+xkVBRyCvCfC318yQhlK/J9FAbrn2HxCbDChDj6zUL9/R+5TttdZb4eT7u7Z7A4a11+GTwMT19fp18bftyuA0L/Q97xXEOO/3KkXIXxWnayBXy2m1jw+NjY2O6UKZZ4sM3gdofGTLyTz+b2jdvRNL0GSgQeZv2dcHHP9/IAAUFBM9P8r+etjuc/7++t4UwPKqzOF+LDbMzv+fvoXpGsm6P/fJv9X8u5XEmAB9rvSf2MxaivvZK62lMsuWNG9CTJEe+OD67X4xqqV3PoLjJZTNhsLXmmvAngy8VpDNGdQ1joCdcXNjYlQ+1XK2C0pEArCOBvSkJg57XKGhQDhOSHLWivPQzyxwrN+VzX2tiWjwZpq81KNTUd1g8MMiiJQeAflN1VkI0o5sAcWmoKJvt0FiHnQhJv4SH3Mg/bz6tnukcmBM7Ba6nM6A9YZEI4f8ELxCGzJZWYr9jB+T64f0gI91RHz74T0YY+boTc2fh2fiN9WRbUUSesKv0P7be9qte46X1Q1fuxMiS+oXYMBy/hpn5MdnRHH0QAWyFP80pWW/JrUJw4HTMZHi7wxvqZB7UjfNulrvyuw4r4rvYsV55+RLRLCKSlm8ZHatpup/hGoGlhz/5cha4eMxTLbOZEnvZMTqlFyK7y4X28erM4nURR6CcAeG/8tLm2/FUPx9rDpYYmbTZRu56gk5erBQJiVIQg7RPLNkFtbNd/AV/9dBqbcqjccXK2VYdOnkFfXb3EemIFZ14NyvbuwAqzjBC41Gi4n/oui+/62DDqQYNJK3CCcCaRTcMHx+Ttb/1o/adOz0Ubd5qDZja7MriZcz2LsukwcrlfM3WBpDIL+GlGO/u0AGE0DURzefZOnz+Cs5BwcHLNqDo/X6xTe14doNmNor/aHqNbG8CpCbpvUoPbHzxpM/HBIrbFhDM8faaa6pmd3stzHeM0UwGvaYnnRaK2nEMEm3zf3yx10qmoTIevuHIi5faXuKiYcxQL0ewWj8Kuf3nv9bCblP84YuB3LH3PzuGLw243CwFBZSG285vRN3VYebf1Pljp0vdP0cxKQDPY7zOXxZt1c4s/FrN5vJOc/+Vbd7YqAXouKYQMzvEHaevT2/LEXI6nTymvoP9y/duynXa7jp2+MF36YpE8vtdzPzTLkq7MedKCQyTs36xfi6On2TYo7XwcutvB57D6f5qFdPGd0g1iGL0RSDB++HC98LXTTP4LZlffW/LkXpowtd8j26MuzyJzvFxEdERPFAP+mCzbiu7uvv3Pf3nzS6MdX04ge3NwnjkujJ6Ly1OTk5AmMHJub4VcFuNpHr2lvb2+ayG6IhZROmZLmTLy7XmuY1jWE+nq6LI5uJ10iHcqG/rPAgRcdkXAjK1kJR8axEuihKtoHdg4xC60N5oy6lbCTy++IWHBgNQMDq5a3Ktwz9g/lwgyFzF5zuZY37v8oLiaJqffHyZs9NXUubujwJD4D9m3ojtf2NlDsF2aIO2f7mIwYGiMDA4CgoQp/rxz9rr67kcUeVX8U5DHBR52U+O4XuD0ZkGhIdBR6Sn3l/nJ/BYAiQNH/Ei97K+XMK3+MlnaZDWRlqMSkwFWRE+Z5kbntpoyFeG4BBPZy9HcU7ZRuLUZRPkbYdh2RePDVrmPL4pmLUhoikH0s1NfK0AKUNNt4r5kZwl3Z5d/OevIyNbmC13yRrcrK8v2LzSMLrHcqKji7v0cI3cUo2VyS0m33fGsmToMPoiBktLy8VktcuyvpR9ZzaYuRRJiKQ6rEU8qKowIaKD9x/KO+9aVa+xgS2+VhwUybaMPwtRQLSRJVGzHiFecy0LjsPYCZTk4MGrK0o+JfnbzVWWBQlMDjrd2PuaM8pkZ8YftbNNPmjTHbipw1r5i5BJcKKTshJxxxucVYUFfn/+Zo5MUnrDZg5JCfrdBfSyx6b184nN7fINKFc4Nm3FH0uPKFG/fZ9qBb3KkjICnn0oSo+IrGZ5nv989MwPZbT2xaYuFFY3TBFjMn6HLlM5fkpKlP4IfFD8LDSnHflrooeYmryoxhfUSd+vELjLBR4mRM2OtQjSNvW0nB6d3FZ0QaJXY5yPkZKIvO+VzM4PJ0xLok6WC15I2+mTHpqobAgSowO60GyO12kXhNw3qior0iP1DMNlQNOB5YMCkzFKUTcOB2Y6LYE8UPTZY4d6DO6DXvM/9xfIqoybagIQikc44CJoO7ULogVJ0xpYqKxhJj4mGzMiJNulS177rFJjcrrZKFwczjKm6l2ZIWCSPupDG1OtH52tORbnZZ8H5Iuv2Wl7qyGe7wUgt8N49SvQAwDG644EboHR/w2treztC1JlKwPV5ZG7ushf+6TFHY/Kejbe8SEeQAshaNklWEtpF4AA6s0SYbovej1huEaAmwgnEdXRG6z0R+ud2bg+OyWIWpypjcUH6cUVuIbyQz149UKlzX8d5ND7ZV4KauS/VGd2WjYiSbMHsCbtqBf7s5kmW80XvU2P15HGk++qQDkSfUVDd+GJWL8tuk634rG/ttRCdR2MOqR9dn6Df0H/kXBYAKRA2qDv0f0eBX9CO40mc2t3TNU3AaPwuvhiZiOJteqNaT6xySJFk9obzyZTk68Zx2EQTh3vCsRI0+wonNlXMgU1WnhzjlxMzn1LQWh3At72HK+Ky4ijZnjxH61IvvjjBP6SoLyZhFuIr0Xs5Rih7S83sT4sGsaeA/NMmkpTrI8WGdEGN9uMBOK/kV4zSR+P77thNpS6b2Oo/0+/trsoshcXtwHX9OXyBejHYX0fYICMFJSbBSEqUDU1ygppq3bFiVMJO+pKrcKTnv0YkV/65SqG1IDkbziqB9NjOYsTMyHXX8w60nYUnDk+0rdOpfyPWQFJazE6Qa6ZFb0Ch0z0xQdeOboWOuqEx3cEjweXVtfXGh3ml5xyVSBOIWZQovmCCpRW3jeL0JWzfCysYWJSWpeMTnPJ6KikYv0xkmJcV+Fx2jWbr8Mc5HbIur6noWPJ7Vv5eurW9iSmsfKDPoKV+KpXIFKHLiPq2dZ/OaM0ROPDMp3Tni9rNRcNrrJF+eYdFGWrm00NZsPq6/UbzWmvYL0ODVWd2VkObguXk3Odbfz48pRrV0aweBIXnK93UsBRe2ZajLgmsMeV/VkfNpLY83MiWmSigXovXyGqKVl13lNf8+Y36DmnCp9D1OGFPzPSz+Ccpi6zg2myt+EIsxMgFbB6agTaSSQCDF9NWWeXK2iQXEZ+/Y8YxH44UIBpbUa2fryh0YiIyCcqeh1cc0ok3YM2Cod0kjmxtc9kztIM4OxxOo6xsDOkNTS2FcaC/NaizThgem2AHYJkWTK98l0xUScdamHv0ovYeVcOc22ykhO61tvkMGfOCcViTW50qAZ6SZfokisf8aHd+Qdzy2VZwegGdRUcEmK2Kx97qdbLAlYMLrN7vJ2bdjeI/A1KurrSn50U/fjz2RlXIrr4Y1guK1EW/0/HXFfPDTXgUB7dGlFYogtPCLS7QcZPhmZvIQ/+youa3eY6ENL8bFQbbNWX4cPd9rUdzQ2QUH7ZNDYC2wAQXbF+nNWpDch3FlV5Wlfy1thTOwF1yGKr3W8j7pnQCtECwYDyR7BO5EjNhxq5F6ZHqQEXgXxjvEVBIhVq0t4S84da+aS+FJqOo3rJjAy+BCRyEO/1KdB7rlXv3Ndz0DgAvMDe4Of4+/L9Af5A8GAAf4H/FudzVw//eYn9XC0SxlZFKqSF1A/YG45QD8LbWdDQRA+ByG0V2EumbRi0jgjv9WXJieO7md0eN1qpGqMDygIzFLBh9aiCsifOOcRxD0nZOu6T3IRtZb8XZEEUmgFDXFl0SrNhnKzjIPVV7SwsKvARKYB69i2MoeGBiIGyPzvgGJXV3c18PfEqw3QelBvCRENJ4lH/gavC2+bxQDwAdsUhm8PpF9IItqEr1sPE8YkEGbzfFSOeYxGUGm+BQSHh5PKlTkOE+Rs7UnLluF2gjiBjQrGSn5xfi63jx0eEuzUAwmPQAsKMLCY/4QXdqpwmOMLrdjjliSwmTkXLLJteci8KOvSX/bvFELoUvlj+cr3bQmLMXEssIo9xZgEalv/x3Es9HAI5MsMX4UchuDReThUQg6xFrEI1Ufy5eYp91Ct2jY/pMuIR7LMSidOMWLMok5hL5UeuZxbTGNGEKoEpNVtYtztbs3c2pGMstZRWiWN0f5526ld9KueGiiNrnDrIVZnmpjG2TGc+439Puv8nq+mV1OQUH12dKxkFAda3bd/miIGUcx29C6TQtcMBMEYoV4sEYf3nI6b70cCk4sg4RfRIOMU4KchRPz/sS457W+fvN+sduAba10JIUQygqz2BMID2LvEadjEqgG3WMdQfjF94CrBOm7wsFXDy7DpCLpy6Oephi7Y0exvV0RaVNUvNB4xi9r9qipYQv0KWRWOCk8qQ5bIbl3cKQWcqBwsA3NNTQ0VDlNpz6VlpY2L83bePkHPtwDD9v86x5CJ3jVZDd49kWJCQV8BdQlEOJUMblPjUerIdY3F4y9bOmc4DKr4ICdgho=
*/