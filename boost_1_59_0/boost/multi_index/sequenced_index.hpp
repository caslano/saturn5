/* Copyright 2003-2021 Joaquin M Lopez Munoz.
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
#include <boost/core/no_exceptions_support.hpp>
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
#include <boost/multi_index/detail/node_handle.hpp>
#include <boost/multi_index/detail/safe_mode.hpp>
#include <boost/multi_index/detail/scope_guard.hpp>
#include <boost/multi_index/detail/seq_index_node.hpp>
#include <boost/multi_index/detail/seq_index_ops.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/multi_index/sequenced_index_fwd.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>
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

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4355) /* this used in base member initializer list */
#endif
  
template<typename SuperMeta,typename TagList>
class sequenced_index:
  BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS SuperMeta::type
{ 
#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
/* The "ISO C++ Template Parser" option in CW8.3 has a problem with the
 * lifetime of const references bound to temporaries --precisely what
 * scopeguards are.
 */

#pragma parse_mfunc_templ off
#endif

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  /* cross-index access */

  template <typename,typename,typename> friend class index_base;
#endif

  typedef typename SuperMeta::type               super;

protected:
  typedef sequenced_index_node<
    typename super::index_node_type>             index_node_type;

private:
  typedef typename index_node_type::impl_type    node_impl_type;
 
public:
  /* types */

  typedef typename index_node_type::value_type   value_type;
  typedef tuples::null_type                      ctor_args;
  typedef typename super::final_allocator_type   allocator_type;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_iterator<
    bidir_node_iterator<index_node_type> >       iterator;
#else
  typedef bidir_node_iterator<index_node_type>   iterator;
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
  typedef typename super::final_node_handle_type node_type;
  typedef detail::insert_return_type<
    iterator,node_type>                          insert_return_type;
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
  typedef safe_mode::safe_container<iterator> safe_container;
#endif

  typedef typename call_traits<value_type>::param_type value_param_type;

  /* needed to avoid commas in some macros */

  typedef std::pair<iterator,bool>                     pair_return_type;

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
    {return make_iterator(index_node_type::from_impl(header()->next()));}
  const_iterator begin()const BOOST_NOEXCEPT
    {return make_iterator(index_node_type::from_impl(header()->next()));}
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
    return make_iterator(
      node_from_value<index_node_type>(boost::addressof(x)));
  }

  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(
      node_from_value<index_node_type>(boost::addressof(x)));
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
    pair_return_type,emplace_front,emplace_front_impl)

  std::pair<iterator,bool> push_front(const value_type& x)
                             {return insert(begin(),x);}
  std::pair<iterator,bool> push_front(BOOST_RV_REF(value_type) x)
                             {return insert(begin(),boost::move(x));}
  void                     pop_front(){erase(begin());}

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(
    pair_return_type,emplace_back,emplace_back_impl)

  std::pair<iterator,bool> push_back(const value_type& x)
                             {return insert(end(),x);}
  std::pair<iterator,bool> push_back(BOOST_RV_REF(value_type) x)
                             {return insert(end(),boost::move(x));}
  void                     pop_back(){erase(--end());}

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(
    pair_return_type,emplace,emplace_impl,iterator,position)

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

  insert_return_type insert(const_iterator position,BOOST_RV_REF(node_type) nh)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    if(nh)BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,nh);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_nh_(nh);
    if(p.second&&position.get_node()!=header()){
      relink(position.get_node(),p.first);
    }
    return insert_return_type(make_iterator(p.first),p.second,boost::move(nh));
  }

  node_type extract(const_iterator position)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    return this->final_extract_(
      static_cast<final_node_type*>(position.get_node()));
  }

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

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(sequenced_index,Index,void)
  splice(iterator position,Index& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()==this->header()){ /* same container */
      BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(
        position==end(),safe_mode::inside_range);
    }
    else{
      external_splice(
        position,x,x.begin(),x.end(),
        boost::is_copy_constructible<value_type>());
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(sequenced_index,Index,void)
  splice(iterator position,BOOST_RV_REF(Index) x)
  {
    splice(position,static_cast<Index&>(x));
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(
    sequenced_index,Index,pair_return_type)
  splice(
    iterator position,Index& x,BOOST_DEDUCED_TYPENAME Index::iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,x);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()==this->header()){ /* same container */
      index_node_type* pn=position.get_node();
      index_node_type* in=static_cast<index_node_type*>(i.get_node());
      if(pn!=in)relink(pn,in);
      return std::pair<iterator,bool>(make_iterator(in),true);
    }
    else{
      std::pair<final_node_type*,bool> p=
        external_splice(
          position,x,i,boost::is_copy_constructible<value_type>());
      return std::pair<iterator,bool>(make_iterator(p.first),p.second);
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(
    sequenced_index,Index,pair_return_type)
  splice(
    iterator position,BOOST_RV_REF(Index) x,
    BOOST_DEDUCED_TYPENAME Index::iterator i)
  {
    return splice(position,static_cast<Index&>(x),i);
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(sequenced_index,Index,void)
  splice(
    iterator position,Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,x);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,x);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()==this->header()){ /* same container */
      BOOST_MULTI_INDEX_CHECK_OUTSIDE_RANGE(position,first,last);
      internal_splice(position,first,last);
    }
    else{
      external_splice(
        position,x,first,last,boost::is_copy_constructible<value_type>());
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(sequenced_index,Index,void)
  splice(
    iterator position,BOOST_RV_REF(Index) x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    splice(position,static_cast<Index&>(x),first,last);
  }

  void remove(value_param_type value)
  {
    sequenced_index_remove(
      *this,
      ::boost::bind<bool>(
        std::equal_to<value_type>(),::boost::arg<1>(),value));
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
    index_node_type* pos=header();
    for(size_type s=size();s--;){
      const value_type& v=*first++;
      relink(pos,node_from_value<index_node_type>(&v));
    }
  }

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  sequenced_index(const ctor_args_list& args_list,const allocator_type& al):
    super(args_list.get_tail(),al)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    empty_initialize();
  }

  sequenced_index(const sequenced_index<SuperMeta,TagList>& x):
    super(x)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    /* the actual copying takes place in subsequent call to copy_() */
  }

  sequenced_index(
    const sequenced_index<SuperMeta,TagList>& x,do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag())

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    empty_initialize();
  }

  ~sequenced_index()
  {
    /* the container is guaranteed to be empty by now */
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  iterator       make_iterator(index_node_type* node)
    {return iterator(node,&safe);}
  const_iterator make_iterator(index_node_type* node)const
    {return const_iterator(node,const_cast<safe_container*>(&safe));}
#else
  iterator       make_iterator(index_node_type* node){return iterator(node);}
  const_iterator make_iterator(index_node_type* node)const
                   {return const_iterator(node);}
#endif

  void copy_(
    const sequenced_index<SuperMeta,TagList>& x,const copy_map_type& map)
  {
    index_node_type* org=x.header();
    index_node_type* cpy=header();
    do{
      index_node_type* next_org=index_node_type::from_impl(org->next());
      index_node_type* next_cpy=map.find(
        static_cast<final_node_type*>(next_org));
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
    if(res==x)link(static_cast<index_node_type*>(x));
    return res;
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,index_node_type* position,
    final_node_type*& x,Variant variant)
  {
    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x)link(static_cast<index_node_type*>(x));
    return res;
  }

  template<typename Dst>
  void extract_(index_node_type* x,Dst dst)
  {
    unlink(x);
    super::extract_(x,dst.next());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    transfer_iterators(dst.get(),x);
#endif
  }

  void delete_all_nodes_()
  {
    for(index_node_type* x=index_node_type::from_impl(header()->next());
        x!=header();){
      index_node_type* y=index_node_type::from_impl(x->next());
      this->final_delete_node_(static_cast<final_node_type*>(x));
      x=y;
    }
  }

  void clear_()
  {
    super::clear_();
    empty_initialize();

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.detach_dereferenceable_iterators();
#endif
  }

  template<typename BoolConstant>
  void swap_(
    sequenced_index<SuperMeta,TagList>& x,BoolConstant swap_allocators)
  {
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.swap(x.safe);
#endif

    super::swap_(x,swap_allocators);
  }

  void swap_elements_(sequenced_index<SuperMeta,TagList>& x)
  {
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.swap(x.safe);
#endif

    super::swap_elements_(x);
  }

  template<typename Variant>
  bool replace_(value_param_type v,index_node_type* x,Variant variant)
  {
    return super::replace_(v,x,variant);
  }

  bool modify_(index_node_type* x)
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

  bool modify_rollback_(index_node_type* x)
  {
    return super::modify_rollback_(x);
  }

  bool check_rollback_(index_node_type* x)const
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
  index_node_type* header()const{return this->final_header();}

  void empty_initialize()
  {
    header()->prior()=header()->next()=header()->impl();
  }

  void link(index_node_type* x)
  {
    node_impl_type::link(x->impl(),header()->impl());
  }

  static void unlink(index_node_type* x)
  {
    node_impl_type::unlink(x->impl());
  }

  static void relink(index_node_type* position,index_node_type* x)
  {
    node_impl_type::relink(position->impl(),x->impl());
  }

  static void relink(
    index_node_type* position,index_node_type* first,index_node_type* last)
  {
    node_impl_type::relink(
      position->impl(),first->impl(),last->impl());
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  void rearranger(index_node_type* position,index_node_type *x)
  {
    if(!position)position=header();
    index_node_type::increment(position);
    if(position!=x)relink(position,x);
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  void detach_iterators(index_node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::detach_equivalent_iterators(it);
  }

  template<typename Dst>
  void transfer_iterators(Dst& dst,index_node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::transfer_equivalent_iterators(dst,it);
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

  template<typename Index>
  std::pair<final_node_type*,bool> external_splice(
    iterator position,Index& x,BOOST_DEDUCED_TYPENAME Index::iterator i,
    boost::true_type /* copy-constructible value */)
  {
    if(get_allocator()==x.get_allocator()){
      return external_splice(position,x,i,boost::false_type());
    }
    else{
      /* backwards compatibility with old, non-transfer-based splice */

      std::pair<iterator,bool> p=insert(position,*i);
      if(p.second)x.erase(i);
      return std::pair<final_node_type*,bool>(
        static_cast<final_node_type*>(p.first.get_node()),p.second);
    }
  }

  template<typename Index>
  std::pair<final_node_type*,bool> external_splice(
    iterator position,Index& x,BOOST_DEDUCED_TYPENAME Index::iterator i,
    boost::false_type /* copy-constructible value */)
  {
    BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,x);
    std::pair<final_node_type*,bool> p=this->final_transfer_(
      x,static_cast<final_node_type*>(i.get_node()));
    if(p.second&&position.get_node()!=header()){
      relink(position.get_node(),p.first);
    }
    return p;
  }

  template<typename Iterator>
  void internal_splice(iterator position,Iterator first,Iterator last)
  {
    index_node_type* pn=position.get_node();
    while(first!=last){
      relink(pn,static_cast<index_node_type*>((first++).get_node()));
    }
  }

  void internal_splice(iterator position,iterator first,iterator last)
  {
    index_node_type* pn=position.get_node();
    index_node_type* fn=static_cast<index_node_type*>(first.get_node());
    index_node_type* ln=static_cast<index_node_type*>(last.get_node());
    if(pn!=ln)relink(pn,fn,ln);
  }

  template<typename Index>
  void external_splice(
    iterator position,Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last,
    boost::true_type /* copy-constructible value */)
  {
    if(get_allocator()==x.get_allocator()){
      external_splice(position,x,first,last,boost::false_type());
    }
    else{
      /* backwards compatibility with old, non-transfer-based splice */

      while(first!=last){
        if(insert(position,*first).second)first=x.erase(first);
        else ++first;
      }
    }
  }

  template<typename Index>
  void external_splice(
    iterator position,Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last,
    boost::false_type /* copy-constructible value */)
  {
    BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,x);
    if(position==end()){
      this->final_transfer_range_(x,first,last);
    }
    else{
      iterator first_to_relink=end();
      --first_to_relink;
      BOOST_TRY{
        this->final_transfer_range_(x,first,last);
      }
      BOOST_CATCH(...){
        ++first_to_relink;
        relink(position.get_node(),first_to_relink.get_node(),header());
      }
      BOOST_CATCH_END
      ++first_to_relink;
      relink(position.get_node(),first_to_relink.get_node(),header());
    }
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  safe_container safe;
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif
};

#if defined(BOOST_MSVC)
#pragma warning(pop) /* C4355 */
#endif

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
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
*/