/* Copyright 2003-2021 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_HASHED_INDEX_HPP
#define BOOST_MULTI_INDEX_HASHED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/call_traits.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/foreach_fwd.hpp>
#include <boost/limits.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/adl_swap.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/bucket_array.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/hash_index_iterator.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/invalidate_iterators.hpp>
#include <boost/multi_index/detail/modify_key_adaptor.hpp>
#include <boost/multi_index/detail/node_handle.hpp>
#include <boost/multi_index/detail/promotes_arg.hpp>
#include <boost/multi_index/detail/safe_mode.hpp>
#include <boost/multi_index/detail/scope_guard.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/multi_index/hashed_index_fwd.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/serialization/nvp.hpp>
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
#define BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT_OF(x)                 \
  detail::scope_guard BOOST_JOIN(check_invariant_,__LINE__)=                 \
    detail::make_obj_guard(x,&hashed_index::check_invariant_);               \
  BOOST_JOIN(check_invariant_,__LINE__).touch();
#define BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT                       \
  BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT_OF(*this)
#else
#define BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT_OF(x)
#define BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* hashed_index adds a layer of hashed indexing to a given Super */

/* Most of the implementation of unique and non-unique indices is
 * shared. We tell from one another on instantiation time by using
 * Category tags defined in hash_index_node.hpp.
 */

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4355) /* this used in base member initializer list */
#endif

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
class hashed_index:
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
  typedef hashed_index_node<
    typename super::index_node_type>             index_node_type;

private:
  typedef typename index_node_type::
    template node_alg<Category>::type            node_alg;
  typedef typename index_node_type::impl_type    node_impl_type;
  typedef typename node_impl_type::pointer       node_impl_pointer;
  typedef typename node_impl_type::base_pointer  node_impl_base_pointer;
  typedef bucket_array<
    typename super::final_allocator_type>        bucket_array_type;

public:
  /* types */

  typedef typename KeyFromValue::result_type     key_type;
  typedef typename index_node_type::value_type   value_type;
  typedef KeyFromValue                           key_from_value;
  typedef Hash                                   hasher;
  typedef Pred                                   key_equal;
  typedef typename super::final_allocator_type   allocator_type;

private:
  typedef allocator_traits<allocator_type>       alloc_traits;

public:
  typedef typename alloc_traits::pointer         pointer;
  typedef typename alloc_traits::const_pointer   const_pointer;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;
  typedef typename alloc_traits::size_type       size_type;
  typedef typename alloc_traits::difference_type difference_type;
  typedef tuple<size_type,
    key_from_value,hasher,key_equal>             ctor_args;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_iterator<
    hashed_index_iterator<
      index_node_type,bucket_array_type,
      Category,
      hashed_index_global_iterator_tag> >        iterator;
#else
  typedef hashed_index_iterator<
    index_node_type,bucket_array_type,
    Category,hashed_index_global_iterator_tag>   iterator;
#endif

  typedef iterator                               const_iterator;

  typedef hashed_index_iterator<
    index_node_type,bucket_array_type,
    Category,hashed_index_local_iterator_tag>    local_iterator;
  typedef local_iterator                         const_local_iterator;

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
    hashed_index>::type                       index_type_list;
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
  typedef typename call_traits<
    key_type>::param_type                              key_param_type;

  /* needed to avoid commas in some macros */

  typedef std::pair<iterator,bool>                     pair_return_type;

public:

  /* construct/destroy/copy
   * Default and copy ctors are in the protected section as indices are
   * not supposed to be created on their own. No range ctor either.
   */

  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& operator=(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x)
  {
    this->final()=x.final();
    return *this;
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& operator=(
    std::initializer_list<value_type> list)
  {
    this->final()=list;
    return *this;
  }
#endif

  allocator_type get_allocator()const BOOST_NOEXCEPT
  {
    return this->final().get_allocator();
  }

  /* size and capacity */

  bool      empty()const BOOST_NOEXCEPT{return this->final_empty_();}
  size_type size()const BOOST_NOEXCEPT{return this->final_size_();}
  size_type max_size()const BOOST_NOEXCEPT{return this->final_max_size_();}

  /* iterators */

  iterator begin()BOOST_NOEXCEPT
  {
    return make_iterator(
      index_node_type::from_impl(header()->next()->prior()));
  
  }
  const_iterator begin()const BOOST_NOEXCEPT
  {
    return make_iterator(
      index_node_type::from_impl(header()->next()->prior()));
  }

  iterator       end()BOOST_NOEXCEPT{return make_iterator(header());}
  const_iterator end()const BOOST_NOEXCEPT{return make_iterator(header());}
  const_iterator cbegin()const BOOST_NOEXCEPT{return begin();}
  const_iterator cend()const BOOST_NOEXCEPT{return end();}

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

  /* modifiers */

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(
    pair_return_type,emplace,emplace_impl)

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(
    iterator,emplace_hint,emplace_hint_impl,iterator,position)

  std::pair<iterator,bool> insert(const value_type& x)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_(x);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  std::pair<iterator,bool> insert(BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_rv_(x);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  iterator insert(iterator position,const value_type& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_(
      x,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }
    
  iterator insert(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_rv_(
      x,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }

  template<typename InputIterator>
  void insert(InputIterator first,InputIterator last)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    for(;first!=last;++first)this->final_insert_ref_(*first);
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  void insert(std::initializer_list<value_type> list)
  {
    insert(list.begin(),list.end());
  }
#endif

  insert_return_type insert(BOOST_RV_REF(node_type) nh)
  {
    if(nh)BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,nh);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_nh_(nh);
    return insert_return_type(make_iterator(p.first),p.second,boost::move(nh));
  }

  iterator insert(const_iterator position,BOOST_RV_REF(node_type) nh)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    if(nh)BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,nh);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_nh_(
      nh,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }

  node_type extract(const_iterator position)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    return this->final_extract_(
      static_cast<final_node_type*>(position.get_node()));
  }

  node_type extract(key_param_type x)
  {
    iterator position=find(x);
    if(position==end())return node_type();
    else return extract(position);
  }

  iterator erase(iterator position)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    this->final_erase_(static_cast<final_node_type*>(position++.get_node()));
    return position;
  }

  size_type erase(key_param_type k)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;

    std::size_t buc=buckets.position(hash_(k));
    for(node_impl_pointer x=buckets.at(buc)->prior();
        x!=node_impl_pointer(0);x=node_alg::next_to_inspect(x)){
      if(eq_(k,key(index_node_type::from_impl(x)->value()))){
        node_impl_pointer y=end_of_range(x);
        size_type         s=0;
        do{
          node_impl_pointer z=node_alg::after(x);
          this->final_erase_(
            static_cast<final_node_type*>(index_node_type::from_impl(x)));
          x=z;
          ++s;
        }while(x!=y);
        return s;
      }
    }
    return 0;
  }

  iterator erase(iterator first,iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,*this);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
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
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    return this->final_replace_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  bool replace(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    return this->final_replace_rv_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier>
  bool modify(iterator position,Modifier mod)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;

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
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;

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

  template<typename Modifier>
  bool modify_key(iterator position,Modifier mod)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    return modify(
      position,modify_key_adaptor<Modifier,value_type,KeyFromValue>(mod,key));
  }

  template<typename Modifier,typename Rollback>
  bool modify_key(iterator position,Modifier mod,Rollback back_)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    return modify(
      position,
      modify_key_adaptor<Modifier,value_type,KeyFromValue>(mod,key),
      modify_key_adaptor<Rollback,value_type,KeyFromValue>(back_,key));
  }

  void clear()BOOST_NOEXCEPT
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    this->final_clear_();
  }

  void swap(hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT_OF(x);
    this->final_swap_(x.final());
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(hashed_index,Index,void)
  merge(Index& x)
  {
    merge(x,x.begin(),x.end());
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(hashed_index,Index,void)
  merge(BOOST_RV_REF(Index) x){merge(static_cast<Index&>(x));}

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(hashed_index,Index,pair_return_type)
  merge(Index& x,BOOST_DEDUCED_TYPENAME Index::iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,x);
    BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,x);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()==this->header()){ /* same container */
      return std::pair<iterator,bool>(
        make_iterator(static_cast<final_node_type*>(i.get_node())),true);
    }
    else{
      std::pair<final_node_type*,bool> p=this->final_transfer_(
        x,static_cast<final_node_type*>(i.get_node()));
      return std::pair<iterator,bool>(make_iterator(p.first),p.second);
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(hashed_index,Index,pair_return_type)
  merge(BOOST_RV_REF(Index) x,BOOST_DEDUCED_TYPENAME Index::iterator i)
  {
    return merge(static_cast<Index&>(x),i);
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(hashed_index,Index,void)
  merge(
    Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,x);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,x);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,x);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()!=this->header()){ /* different containers */
      this->final_transfer_range_(x,first,last);
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(hashed_index,Index,void)
  merge(
    BOOST_RV_REF(Index) x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    merge(static_cast<Index&>(x),first,last);
  }

  /* observers */

  key_from_value key_extractor()const{return key;}
  hasher         hash_function()const{return hash_;}
  key_equal      key_eq()const{return eq_;}
  
  /* lookup */

  /* Internally, these ops rely on const_iterator being the same
   * type as iterator.
   */

  /* Implementation note: When CompatibleKey is consistently promoted to
   * KeyFromValue::result_type for equality comparison, the promotion is made
   * once in advance to increase efficiency.
   */

  template<typename CompatibleKey>
  iterator find(const CompatibleKey& k)const
  {
    return find(k,hash_,eq_);
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  iterator find(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq)const
  {
    return find(
      k,hash,eq,promotes_1st_arg<CompatiblePred,CompatibleKey,key_type>());
  }

  template<typename CompatibleKey>
  size_type count(const CompatibleKey& k)const
  {
    return count(k,hash_,eq_);
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  size_type count(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq)const
  {
    return count(
      k,hash,eq,promotes_1st_arg<CompatiblePred,CompatibleKey,key_type>());
  }

  template<typename CompatibleKey>
  bool contains(const CompatibleKey& k)const
  {
    return contains(k,hash_,eq_);
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  bool contains(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq)const
  {
    return find(k,hash,eq)!=end();
  }

  template<typename CompatibleKey>
  std::pair<iterator,iterator> equal_range(const CompatibleKey& k)const
  {
    return equal_range(k,hash_,eq_);
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  std::pair<iterator,iterator> equal_range(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq)const
  {
    return equal_range(
      k,hash,eq,promotes_1st_arg<CompatiblePred,CompatibleKey,key_type>());
  }

  /* bucket interface */

  size_type bucket_count()const BOOST_NOEXCEPT
  {
    return static_cast<size_type>(buckets.size());
  }

  size_type max_bucket_count()const BOOST_NOEXCEPT{return static_cast<size_type>(-1);}

  size_type bucket_size(size_type n)const
  {
    size_type res=0;
    for(node_impl_pointer x=buckets.at(n)->prior();
        x!=node_impl_pointer(0);x=node_alg::after_local(x)){
      ++res;
    }
    return res;
  }

  size_type bucket(key_param_type k)const
  {
    return static_cast<size_type>(buckets.position(hash_(k)));
  }

  local_iterator begin(size_type n)
  {
    return const_cast<const hashed_index*>(this)->begin(n);
  }

  const_local_iterator begin(size_type n)const
  {
    node_impl_pointer x=buckets.at(n)->prior();
    if(x==node_impl_pointer(0))return end(n);
    return make_local_iterator(index_node_type::from_impl(x));
  }

  local_iterator end(size_type n)
  {
    return const_cast<const hashed_index*>(this)->end(n);
  }

  const_local_iterator end(size_type)const
  {
    return make_local_iterator(0);
  }

  const_local_iterator cbegin(size_type n)const{return begin(n);}
  const_local_iterator cend(size_type n)const{return end(n);}

  local_iterator local_iterator_to(const value_type& x)
  {
    return make_local_iterator(
      node_from_value<index_node_type>(boost::addressof(x)));
  }

  const_local_iterator local_iterator_to(const value_type& x)const
  {
    return make_local_iterator(
      node_from_value<index_node_type>(boost::addressof(x)));
  }

  /* hash policy */

  float load_factor()const BOOST_NOEXCEPT
    {return static_cast<float>(size())/bucket_count();}
  float max_load_factor()const BOOST_NOEXCEPT{return mlf;}
  void  max_load_factor(float z){mlf=z;calculate_max_load();}

  void rehash(size_type n)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    if(size()<=max_load&&n<=bucket_count())return;

    size_type bc =(std::numeric_limits<size_type>::max)();
    float     fbc=1.0f+static_cast<float>(size())/mlf;
    if(bc>fbc){
      bc=static_cast<size_type>(fbc);
      if(bc<n)bc=n;
    }
    unchecked_rehash(bc);
  }

  void reserve(size_type n)
  {
    rehash(static_cast<size_type>(std::ceil(static_cast<float>(n)/mlf)));
  }

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  hashed_index(const ctor_args_list& args_list,const allocator_type& al):
    super(args_list.get_tail(),al),
    key(tuples::get<1>(args_list.get_head())),
    hash_(tuples::get<2>(args_list.get_head())),
    eq_(tuples::get<3>(args_list.get_head())),
    buckets(al,header()->impl(),tuples::get<0>(args_list.get_head())),
    mlf(1.0f)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    calculate_max_load();
  }

  hashed_index(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x):
    super(x),
    key(x.key),
    hash_(x.hash_),
    eq_(x.eq_),
    buckets(x.get_allocator(),header()->impl(),x.buckets.size()),
    mlf(x.mlf),
    max_load(x.max_load)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    /* Copy ctor just takes the internal configuration objects from x. The rest
     * is done in subsequent call to copy_().
     */
  }

  hashed_index(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
    do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag()),
    key(x.key),
    hash_(x.hash_),
    eq_(x.eq_),
    buckets(x.get_allocator(),header()->impl(),0),
    mlf(1.0f)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
     calculate_max_load();
  }

  ~hashed_index()
  {
    /* the container is guaranteed to be empty by now */
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  iterator make_iterator(index_node_type* node)
  {
    return iterator(node,&safe);
  }

  const_iterator make_iterator(index_node_type* node)const
  {
    return const_iterator(node,const_cast<safe_container*>(&safe));
  }
#else
  iterator make_iterator(index_node_type* node)
  {
    return iterator(node);
  }

  const_iterator make_iterator(index_node_type* node)const
  {
    return const_iterator(node);
  }
#endif

  local_iterator make_local_iterator(index_node_type* node)
  {
    return local_iterator(node);
  }

  const_local_iterator make_local_iterator(index_node_type* node)const
  {
    return const_local_iterator(node);
  }

  void copy_(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
    const copy_map_type& map)
  {
    copy_(x,map,Category());
  }

  void copy_(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
    const copy_map_type& map,hashed_unique_tag)
  {
    if(x.size()!=0){
      node_impl_pointer end_org=x.header()->impl(),
                        org=end_org,
                        cpy=header()->impl();
      do{
        node_impl_pointer prev_org=org->prior(),
                          prev_cpy=
          static_cast<index_node_type*>(map.find(static_cast<final_node_type*>(
            index_node_type::from_impl(prev_org))))->impl();
        cpy->prior()=prev_cpy;
        if(node_alg::is_first_of_bucket(org)){
          node_impl_base_pointer buc_org=prev_org->next(),
                                 buc_cpy=
            buckets.begin()+(buc_org-x.buckets.begin());
          prev_cpy->next()=buc_cpy;
          buc_cpy->prior()=cpy;
        }
        else{
          prev_cpy->next()=node_impl_type::base_pointer_from(cpy);
        }
        org=prev_org;
        cpy=prev_cpy;
      }while(org!=end_org);
    }

    super::copy_(x,map);
  }
  
  void copy_(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
    const copy_map_type& map,hashed_non_unique_tag)
  {
    if(x.size()!=0){
      node_impl_pointer end_org=x.header()->impl(),
                        org=end_org,
                        cpy=header()->impl();
      do{
        node_impl_pointer next_org=node_alg::after(org),
                          next_cpy=
          static_cast<index_node_type*>(map.find(static_cast<final_node_type*>(
            index_node_type::from_impl(next_org))))->impl();
        if(node_alg::is_first_of_bucket(next_org)){
          node_impl_base_pointer buc_org=org->next(),
                                 buc_cpy=
            buckets.begin()+(buc_org-x.buckets.begin());
          cpy->next()=buc_cpy;
          buc_cpy->prior()=next_cpy;
          next_cpy->prior()=cpy;
        }
        else{
          if(org->next()==node_impl_type::base_pointer_from(next_org)){
            cpy->next()=node_impl_type::base_pointer_from(next_cpy);
          }
          else{
            cpy->next()=
              node_impl_type::base_pointer_from(
                static_cast<index_node_type*>(
                  map.find(static_cast<final_node_type*>(
                    index_node_type::from_impl(
                      node_impl_type::pointer_from(org->next())))))->impl());
          }

          if(next_org->prior()!=org){
            next_cpy->prior()=
              static_cast<index_node_type*>(
                map.find(static_cast<final_node_type*>(
                  index_node_type::from_impl(next_org->prior()))))->impl();
          }
          else{
            next_cpy->prior()=cpy;
          }
        }
        org=next_org;
        cpy=next_cpy;
      }while(org!=end_org);
    }

    super::copy_(x,map);
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,final_node_type*& x,Variant variant)
  {
    reserve_for_insert(size()+1);

    std::size_t buc=find_bucket(v);
    link_info   pos(buckets.at(buc));
    if(!link_point(v,pos)){
      return static_cast<final_node_type*>(
        index_node_type::from_impl(node_impl_type::pointer_from(pos)));
    }

    final_node_type* res=super::insert_(v,x,variant);
    if(res==x)link(static_cast<index_node_type*>(x),pos);
    return res;
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,index_node_type* position,
    final_node_type*& x,Variant variant)
  {
    reserve_for_insert(size()+1);

    std::size_t buc=find_bucket(v);
    link_info   pos(buckets.at(buc));
    if(!link_point(v,pos)){
      return static_cast<final_node_type*>(
        index_node_type::from_impl(node_impl_type::pointer_from(pos)));
    }

    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x)link(static_cast<index_node_type*>(x),pos);
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
    delete_all_nodes_(Category());
  }

  void delete_all_nodes_(hashed_unique_tag)
  {
    for(node_impl_pointer x_end=header()->impl(),x=x_end->prior();x!=x_end;){
      node_impl_pointer y=x->prior();
      this->final_delete_node_(
        static_cast<final_node_type*>(index_node_type::from_impl(x)));
      x=y;
    }
  }

  void delete_all_nodes_(hashed_non_unique_tag)
  {
    for(node_impl_pointer x_end=header()->impl(),x=x_end->prior();x!=x_end;){
      node_impl_pointer y=x->prior();
      if(y->next()!=node_impl_type::base_pointer_from(x)&&
         y->next()->prior()!=x){ /* n-1 of group */
        /* Make the second node prior() pointer back-linked so that it won't
         * refer to a deleted node when the time for its own destruction comes.
         */

        node_impl_pointer first=node_impl_type::pointer_from(y->next());
        first->next()->prior()=first;
      }
      this->final_delete_node_(
        static_cast<final_node_type*>(index_node_type::from_impl(x)));
      x=y;
    }
  }

  void clear_()
  {
    super::clear_();
    buckets.clear(header()->impl());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.detach_dereferenceable_iterators();
#endif
  }

  template<typename BoolConstant>
  void swap_(
    hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
    BoolConstant swap_allocators)
  {
    adl_swap(key,x.key);
    adl_swap(hash_,x.hash_);
    adl_swap(eq_,x.eq_);
    buckets.swap(x.buckets,swap_allocators);
    std::swap(mlf,x.mlf);
    std::swap(max_load,x.max_load);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.swap(x.safe);
#endif

    super::swap_(x,swap_allocators);
  }

  void swap_elements_(
    hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x)
  {
    buckets.swap(x.buckets);
    std::swap(mlf,x.mlf);
    std::swap(max_load,x.max_load);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.swap(x.safe);
#endif

    super::swap_elements_(x);
  }

  template<typename Variant>
  bool replace_(value_param_type v,index_node_type* x,Variant variant)
  {
    if(eq_(key(v),key(x->value()))){
      return super::replace_(v,x,variant);
    }
      
    unlink_undo undo;
    unlink(x,undo);

    BOOST_TRY{
      std::size_t  buc=find_bucket(v);
      link_info    pos(buckets.at(buc));
      if(link_point(v,pos)&&super::replace_(v,x,variant)){
        link(x,pos);
        return true;
      }
      undo();
      return false;
    }
    BOOST_CATCH(...){
      undo();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool modify_(index_node_type* x)
  {
    std::size_t buc;
    bool        b; 
    BOOST_TRY{
      buc=find_bucket(x->value());
      b=in_place(x->impl(),key(x->value()),buc);
    }
    BOOST_CATCH(...){
      extract_(x,invalidate_iterators());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    if(!b){
      unlink(x);
      BOOST_TRY{
        link_info pos(buckets.at(buc));
        if(!link_point(x->value(),pos)){
          super::extract_(x,invalidate_iterators());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
          detach_iterators(x);
#endif
          return false;
        }
        link(x,pos);
      }
      BOOST_CATCH(...){
        super::extract_(x,invalidate_iterators());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
      detach_iterators(x);
#endif

        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }

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
    std::size_t buc=find_bucket(x->value());
    if(in_place(x->impl(),key(x->value()),buc)){
      return super::modify_rollback_(x);
    }

    unlink_undo undo;
    unlink(x,undo);

    BOOST_TRY{
      link_info pos(buckets.at(buc));
      if(link_point(x->value(),pos)&&super::modify_rollback_(x)){
        link(x,pos);
        return true;
      }
      undo();
      return false;
    }
    BOOST_CATCH(...){
      undo();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool check_rollback_(index_node_type* x)const
  {
    std::size_t buc=find_bucket(x->value());
    return in_place(x->impl(),key(x->value()),buc)&&super::check_rollback_(x);
  }

  /* comparison */

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  /* defect macro refers to class, not function, templates, but anyway */

  template<typename K,typename H,typename P,typename S,typename T,typename C>
  friend bool operator==(
    const hashed_index<K,H,P,S,T,C>&,const hashed_index<K,H,P,S,T,C>& y);
#endif

  bool equals(const hashed_index& x)const{return equals(x,Category());}

  bool equals(const hashed_index& x,hashed_unique_tag)const
  {
    if(size()!=x.size())return false;
    for(const_iterator it=begin(),it_end=end(),it2_end=x.end();
        it!=it_end;++it){
      const_iterator it2=x.find(key(*it));
      if(it2==it2_end||!(*it==*it2))return false;
    }
    return true;
  }

  bool equals(const hashed_index& x,hashed_non_unique_tag)const
  {
    if(size()!=x.size())return false;
    for(const_iterator it=begin(),it_end=end();it!=it_end;){
      const_iterator it2,it2_last;
      boost::tie(it2,it2_last)=x.equal_range(key(*it));
      if(it2==it2_last)return false;

      const_iterator it_last=make_iterator(
        index_node_type::from_impl(end_of_range(it.get_node()->impl())));
      if(std::distance(it,it_last)!=std::distance(it2,it2_last))return false;

      /* From is_permutation code in
       * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2010/n3068.pdf
       */

      for(;it!=it_last;++it,++it2){
        if(!(*it==*it2))break;
      }
      if(it!=it_last){
        for(const_iterator scan=it;scan!=it_last;++scan){
          if(std::find(it,scan,*scan)!=scan)continue;
          difference_type matches=std::count(it2,it2_last,*scan);
          if(matches==0||matches!=std::count(scan,it_last,*scan))return false;
        }
        it=it_last;
      }
    }
    return true;
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* serialization */

  template<typename Archive>
  void save_(
    Archive& ar,const unsigned int version,const index_saver_type& sm)const
  {
    ar<<serialization::make_nvp("position",buckets);
    super::save_(ar,version,sm);
  }

  template<typename Archive>
  void load_(Archive& ar,const unsigned int version,const index_loader_type& lm)
  {
    ar>>serialization::make_nvp("position",buckets);
    super::load_(ar,version,lm);
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const
  {
    if(size()==0||begin()==end()){
      if(size()!=0||begin()!=end())return false;
    }
    else{
      size_type s0=0;
      for(const_iterator it=begin(),it_end=end();it!=it_end;++it,++s0){}
      if(s0!=size())return false;

      size_type s1=0;
      for(size_type buc=0;buc<bucket_count();++buc){
        size_type ss1=0;
        for(const_local_iterator it=begin(buc),it_end=end(buc);
            it!=it_end;++it,++ss1){
          if(find_bucket(*it)!=buc)return false;
        }
        if(ss1!=bucket_size(buc))return false;
        s1+=ss1;
      }
      if(s1!=size())return false;
    }

    return super::invariant_();
  }

  /* This forwarding function eases things for the boost::mem_fn construct
   * in BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT. Actually,
   * final_check_invariant is already an inherited member function of index.
   */
  void check_invariant_()const{this->final_check_invariant_();}
#endif

private:
  index_node_type* header()const{return this->final_header();}

  std::size_t find_bucket(value_param_type v)const
  {
    return bucket(key(v));
  }

  struct link_info_non_unique
  {
    link_info_non_unique(node_impl_base_pointer pos):
      first(pos),last(node_impl_base_pointer(0)){}

    operator const node_impl_base_pointer&()const{return this->first;}

    node_impl_base_pointer first,last;
  };

  typedef typename mpl::if_<
    is_same<Category,hashed_unique_tag>,
    node_impl_base_pointer,
    link_info_non_unique
  >::type                                link_info;

  bool link_point(value_param_type v,link_info& pos)
  {
    return link_point(v,pos,Category());
  }

  bool link_point(
    value_param_type v,node_impl_base_pointer& pos,hashed_unique_tag)
  {
    for(node_impl_pointer x=pos->prior();x!=node_impl_pointer(0);
        x=node_alg::after_local(x)){
      if(eq_(key(v),key(index_node_type::from_impl(x)->value()))){
        pos=node_impl_type::base_pointer_from(x);
        return false;
      }
    }
    return true;
  }

  bool link_point(
    value_param_type v,link_info_non_unique& pos,hashed_non_unique_tag)
  {
    for(node_impl_pointer x=pos.first->prior();x!=node_impl_pointer(0);
        x=node_alg::next_to_inspect(x)){
      if(eq_(key(v),key(index_node_type::from_impl(x)->value()))){
        pos.first=node_impl_type::base_pointer_from(x);
        pos.last=node_impl_type::base_pointer_from(last_of_range(x));
        return true;
      }
    }
    return true;
  }

  node_impl_pointer last_of_range(node_impl_pointer x)const
  {
    return last_of_range(x,Category());
  }

  node_impl_pointer last_of_range(node_impl_pointer x,hashed_unique_tag)const
  {
    return x;
  }

  node_impl_pointer last_of_range(
    node_impl_pointer x,hashed_non_unique_tag)const
  {
    node_impl_base_pointer y=x->next();
    node_impl_pointer      z=y->prior();
    if(z==x){                      /* range of size 1 or 2 */
      node_impl_pointer yy=node_impl_type::pointer_from(y);
      return
        eq_(
          key(index_node_type::from_impl(x)->value()),
          key(index_node_type::from_impl(yy)->value()))?yy:x;
    }
    else if(z->prior()==x)               /* last of bucket */
      return x;
    else                                /* group of size>2 */        
      return z;
  }

  node_impl_pointer end_of_range(node_impl_pointer x)const
  {
    return end_of_range(x,Category());
  }

  node_impl_pointer end_of_range(node_impl_pointer x,hashed_unique_tag)const
  {
    return node_alg::after(last_of_range(x));
  }

  node_impl_pointer end_of_range(
    node_impl_pointer x,hashed_non_unique_tag)const
  {
    node_impl_base_pointer y=x->next();
    node_impl_pointer      z=y->prior();
    if(z==x){                      /* range of size 1 or 2 */
      node_impl_pointer yy=node_impl_type::pointer_from(y);
      if(!eq_(
           key(index_node_type::from_impl(x)->value()),
           key(index_node_type::from_impl(yy)->value())))yy=x;
      return yy->next()->prior()==yy?
               node_impl_type::pointer_from(yy->next()):
               yy->next()->prior();
    }
    else if(z->prior()==x)               /* last of bucket */
      return z;
    else                                /* group of size>2 */        
      return z->next()->prior()==z?
               node_impl_type::pointer_from(z->next()):
               z->next()->prior();
  }

  void link(index_node_type* x,const link_info& pos)
  {
    link(x,pos,Category());
  }

  void link(index_node_type* x,node_impl_base_pointer pos,hashed_unique_tag)
  {
    node_alg::link(x->impl(),pos,header()->impl());
  }

  void link(
    index_node_type* x,const link_info_non_unique& pos,hashed_non_unique_tag)
  {
    if(pos.last==node_impl_base_pointer(0)){
      node_alg::link(x->impl(),pos.first,header()->impl());
    }
    else{
      node_alg::link(
        x->impl(),
        node_impl_type::pointer_from(pos.first),
        node_impl_type::pointer_from(pos.last));
    }
  }

  void unlink(index_node_type* x)
  {
    node_alg::unlink(x->impl());
  }

  typedef typename node_alg::unlink_undo unlink_undo;

  void unlink(index_node_type* x,unlink_undo& undo)
  {
    node_alg::unlink(x->impl(),undo);
  }

  void calculate_max_load()
  {
    float fml=mlf*static_cast<float>(bucket_count());
    max_load=(std::numeric_limits<size_type>::max)();
    if(max_load>fml)max_load=static_cast<size_type>(fml);
  }

  void reserve_for_insert(size_type n)
  {
    if(n>max_load){
      size_type bc =(std::numeric_limits<size_type>::max)();
      float     fbc=1.0f+static_cast<float>(n)/mlf;
      if(bc>fbc)bc =static_cast<size_type>(fbc);
      unchecked_rehash(bc);
    }
  }

  void unchecked_rehash(size_type n){unchecked_rehash(n,Category());}

  void unchecked_rehash(size_type n,hashed_unique_tag)
  {
    node_impl_type    cpy_end_node;
    node_impl_pointer cpy_end=node_impl_pointer(&cpy_end_node),
                      end_=header()->impl();
    bucket_array_type buckets_cpy(get_allocator(),cpy_end,n);

    if(size()!=0){
      auto_space<
        std::size_t,allocator_type>       hashes(get_allocator(),size());
      auto_space<
        node_impl_pointer,allocator_type> node_ptrs(get_allocator(),size());
      std::size_t                         i=0,size_=size();
      bool                                within_bucket=false;
      BOOST_TRY{
        for(;i!=size_;++i){
          node_impl_pointer x=end_->prior();

          /* only this can possibly throw */
          std::size_t h=hash_(key(index_node_type::from_impl(x)->value()));

          hashes.data()[i]=h;
          node_ptrs.data()[i]=x;
          within_bucket=!node_alg::unlink_last(end_);
          node_alg::link(x,buckets_cpy.at(buckets_cpy.position(h)),cpy_end);
        }
      }
      BOOST_CATCH(...){
        if(i!=0){
          std::size_t prev_buc=buckets.position(hashes.data()[i-1]);
          if(!within_bucket)prev_buc=~prev_buc;

          for(std::size_t j=i;j--;){
            std::size_t       buc=buckets.position(hashes.data()[j]);
            node_impl_pointer x=node_ptrs.data()[j];
            if(buc==prev_buc)node_alg::append(x,end_);
            else node_alg::link(x,buckets.at(buc),end_);
            prev_buc=buc;
          }
        }
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }

    end_->prior()=cpy_end->prior()!=cpy_end?cpy_end->prior():end_;
    end_->next()=cpy_end->next();
    end_->prior()->next()->prior()=end_->next()->prior()->prior()=end_;
    buckets.swap(buckets_cpy);
    calculate_max_load();
  }

  void unchecked_rehash(size_type n,hashed_non_unique_tag)
  {
    node_impl_type    cpy_end_node;
    node_impl_pointer cpy_end=node_impl_pointer(&cpy_end_node),
                      end_=header()->impl();
    bucket_array_type buckets_cpy(get_allocator(),cpy_end,n);

    if(size()!=0){
      auto_space<
        std::size_t,allocator_type>       hashes(get_allocator(),size());
      auto_space<
        node_impl_pointer,allocator_type> node_ptrs(get_allocator(),size());
      std::size_t                         i=0;
      bool                                within_bucket=false;
      BOOST_TRY{
        for(;;++i){
          node_impl_pointer x=end_->prior();
          if(x==end_)break;

          /* only this can possibly throw */
          std::size_t h=hash_(key(index_node_type::from_impl(x)->value()));

          hashes.data()[i]=h;
          node_ptrs.data()[i]=x;
          std::pair<node_impl_pointer,bool> p=
            node_alg::unlink_last_group(end_);
          node_alg::link_range(
            p.first,x,buckets_cpy.at(buckets_cpy.position(h)),cpy_end);
          within_bucket=!(p.second);
        }
      }
      BOOST_CATCH(...){
        if(i!=0){
          std::size_t prev_buc=buckets.position(hashes.data()[i-1]);
          if(!within_bucket)prev_buc=~prev_buc;

          for(std::size_t j=i;j--;){
            std::size_t       buc=buckets.position(hashes.data()[j]);
            node_impl_pointer x=node_ptrs.data()[j],
                              y=
              x->prior()->next()!=node_impl_type::base_pointer_from(x)&&
              x->prior()->next()->prior()!=x?
                node_impl_type::pointer_from(x->prior()->next()):x;
            node_alg::unlink_range(y,x);
            if(buc==prev_buc)node_alg::append_range(y,x,end_);
            else node_alg::link_range(y,x,buckets.at(buc),end_);
            prev_buc=buc;
          }
        }
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }

    end_->prior()=cpy_end->prior()!=cpy_end?cpy_end->prior():end_;
    end_->next()=cpy_end->next();
    end_->prior()->next()->prior()=end_->next()->prior()->prior()=end_;
    buckets.swap(buckets_cpy);
    calculate_max_load();
  }

  bool in_place(node_impl_pointer x,key_param_type k,std::size_t buc)const
  {
    return in_place(x,k,buc,Category());
  }

  bool in_place(
    node_impl_pointer x,key_param_type k,std::size_t buc,
    hashed_unique_tag)const
  {
    bool found=false;
    for(node_impl_pointer y=buckets.at(buc)->prior();
        y!=node_impl_pointer(0);y=node_alg::after_local(y)){
      if(y==x)found=true;
      else if(eq_(k,key(index_node_type::from_impl(y)->value())))return false;
    }
    return found;
  }

  bool in_place(
    node_impl_pointer x,key_param_type k,std::size_t buc,
    hashed_non_unique_tag)const
  {
    bool found=false;
    int  range_size=0;
    for(node_impl_pointer y=buckets.at(buc)->prior();y!=node_impl_pointer(0);){
      if(node_alg::is_first_of_group(y)){ /* group of 3 or more */
        if(y==x){
          /* in place <-> equal to some other member of the group */
          return eq_(
            k,
            key(index_node_type::from_impl(
              node_impl_type::pointer_from(y->next()))->value()));
        }
        else{
          node_impl_pointer z=
            node_alg::after_local(y->next()->prior()); /* end of range */
          if(eq_(k,key(index_node_type::from_impl(y)->value()))){
            if(found)return false; /* x lies outside */
            do{
              if(y==x)return true;
              y=node_alg::after_local(y);
            }while(y!=z);
            return false; /* x not found */
          }
          else{
            if(range_size==1&&!found)return false;
            if(range_size==2)return found;
            range_size=0;
            y=z; /* skip range (and potentially x, too, which is fine) */
          }
        }
      }
      else{ /* group of 1 or 2 */
        if(y==x){
          if(range_size==1)return true;
          range_size=1;
          found=true;
        }
        else if(eq_(k,key(index_node_type::from_impl(y)->value()))){
          if(range_size==0&&found)return false;
          if(range_size==1&&!found)return false;
          if(range_size==2)return false;
          ++range_size;
        }
        else{
          if(range_size==1&&!found)return false;
          if(range_size==2)return found;
          range_size=0;
        }
        y=node_alg::after_local(y);
      }
    }
    return found;
  }

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

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<iterator,bool> emplace_impl(BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool>p=
      this->final_emplace_(BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  iterator emplace_hint_impl(
    iterator position,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool>p=
      this->final_emplace_hint_(
        static_cast<final_node_type*>(position.get_node()),
        BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
    return make_iterator(p.first);
  }

  template<
    typename CompatibleHash,typename CompatiblePred
  >
  iterator find(
    const key_type& k,
    const CompatibleHash& hash,const CompatiblePred& eq,mpl::true_)const
  {
    return find(k,hash,eq,mpl::false_());
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  iterator find(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq,mpl::false_)const
  {
    std::size_t buc=buckets.position(hash(k));
    for(node_impl_pointer x=buckets.at(buc)->prior();
        x!=node_impl_pointer(0);x=node_alg::next_to_inspect(x)){
      if(eq(k,key(index_node_type::from_impl(x)->value()))){
        return make_iterator(index_node_type::from_impl(x));
      }
    }
    return end();
  }

  template<
    typename CompatibleHash,typename CompatiblePred
  >
  size_type count(
    const key_type& k,
    const CompatibleHash& hash,const CompatiblePred& eq,mpl::true_)const
  {
    return count(k,hash,eq,mpl::false_());
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  size_type count(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq,mpl::false_)const
  {
    std::size_t buc=buckets.position(hash(k));
    for(node_impl_pointer x=buckets.at(buc)->prior();
        x!=node_impl_pointer(0);x=node_alg::next_to_inspect(x)){
      if(eq(k,key(index_node_type::from_impl(x)->value()))){
        size_type         res=0;
        node_impl_pointer y=end_of_range(x);
        do{
          ++res;
          x=node_alg::after(x);
        }while(x!=y);
        return res;
      }
    }
    return 0;
  }

  template<
    typename CompatibleHash,typename CompatiblePred
  >
  std::pair<iterator,iterator> equal_range(
    const key_type& k,
    const CompatibleHash& hash,const CompatiblePred& eq,mpl::true_)const
  {
    return equal_range(k,hash,eq,mpl::false_());
  }

  template<
    typename CompatibleKey,typename CompatibleHash,typename CompatiblePred
  >
  std::pair<iterator,iterator> equal_range(
    const CompatibleKey& k,
    const CompatibleHash& hash,const CompatiblePred& eq,mpl::false_)const
  {
    std::size_t buc=buckets.position(hash(k));
    for(node_impl_pointer x=buckets.at(buc)->prior();
        x!=node_impl_pointer(0);x=node_alg::next_to_inspect(x)){
      if(eq(k,key(index_node_type::from_impl(x)->value()))){
        return std::pair<iterator,iterator>(
          make_iterator(index_node_type::from_impl(x)),
          make_iterator(index_node_type::from_impl(end_of_range(x))));
      }
    }
    return std::pair<iterator,iterator>(end(),end());
  }

  key_from_value               key;
  hasher                       hash_;
  key_equal                    eq_;
  bucket_array_type            buckets;
  float                        mlf;
  size_type                    max_load;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  safe_container               safe;
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
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
bool operator==(
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y)
{
  return x.equals(y);
}

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
bool operator!=(
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y)
{
  return !(x==y);
}

/*  specialized algorithms */

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
void swap(
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

/* hashed index specifiers */

template<typename Arg1,typename Arg2,typename Arg3,typename Arg4>
struct hashed_unique
{
  typedef typename detail::hashed_index_args<
    Arg1,Arg2,Arg3,Arg4>                           index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::hash_type           hash_type;
  typedef typename index_args::pred_type           pred_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::hashed_index_node<Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::hashed_index<
      key_from_value_type,hash_type,pred_type,
      SuperMeta,tag_list_type,detail::hashed_unique_tag> type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3,typename Arg4>
struct hashed_non_unique
{
  typedef typename detail::hashed_index_args<
    Arg1,Arg2,Arg3,Arg4>                           index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::hash_type           hash_type;
  typedef typename index_args::pred_type           pred_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::hashed_index_node<Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::hashed_index<
      key_from_value_type,hash_type,pred_type,
      SuperMeta,tag_list_type,detail::hashed_non_unique_tag> type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

/* Boost.Foreach compatibility */

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::hashed_index<
    KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>*&,
  boost_foreach_argument_dependent_lookup_hack)
{
  return 0;
}

#undef BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT
#undef BOOST_MULTI_INDEX_HASHED_INDEX_CHECK_INVARIANT_OF

#endif

/* hashed_index.hpp
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
*/