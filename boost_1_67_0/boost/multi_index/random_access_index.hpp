/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_RANDOM_ACCESS_INDEX_HPP
#define BOOST_MULTI_INDEX_RANDOM_ACCESS_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
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
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/rnd_node_iterator.hpp>
#include <boost/multi_index/detail/rnd_index_node.hpp>
#include <boost/multi_index/detail/rnd_index_ops.hpp>
#include <boost/multi_index/detail/rnd_index_ptr_array.hpp>
#include <boost/multi_index/detail/safe_mode.hpp>
#include <boost/multi_index/detail/scope_guard.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/multi_index/random_access_index_fwd.hpp>
#include <boost/throw_exception.hpp> 
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <functional>
#include <stdexcept> 
#include <utility>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include<initializer_list>
#endif

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/multi_index/detail/rnd_index_loader.hpp>
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
#define BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT_OF(x)                    \
  detail::scope_guard BOOST_JOIN(check_invariant_,__LINE__)=                 \
    detail::make_obj_guard(x,&random_access_index::check_invariant_);        \
  BOOST_JOIN(check_invariant_,__LINE__).touch();
#define BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT                          \
  BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT_OF(*this)
#else
#define BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT_OF(x)
#define BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* random_access_index adds a layer of random access indexing
 * to a given Super
 */

template<typename SuperMeta,typename TagList>
class random_access_index:
  BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS SuperMeta::type

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  ,public safe_mode::safe_container<
    random_access_index<SuperMeta,TagList> >
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
  typedef random_access_index_node<
    typename super::node_type>                   node_type;

private:
  typedef typename node_type::impl_type          node_impl_type;
  typedef random_access_index_ptr_array<
    typename super::final_allocator_type>        ptr_array;
  typedef typename ptr_array::pointer            node_impl_ptr_pointer;

public:
  /* types */

  typedef typename node_type::value_type         value_type;
  typedef tuples::null_type                      ctor_args;
  typedef typename super::final_allocator_type   allocator_type;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_iterator<
    rnd_node_iterator<node_type>,
    random_access_index>                         iterator;
#else
  typedef rnd_node_iterator<node_type>           iterator;
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
    random_access_index>::type                index_type_list;
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
    random_access_index>                      safe_super;
#endif

  typedef typename call_traits<
    value_type>::param_type                   value_param_type;

  /* Needed to avoid commas in BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL
   * expansion.
   */

  typedef std::pair<iterator,bool>            emplace_return_type;

public:

  /* construct/copy/destroy
   * Default and copy ctors are in the protected section as indices are
   * not supposed to be created on their own. No range ctor either.
   */

  random_access_index<SuperMeta,TagList>& operator=(
    const random_access_index<SuperMeta,TagList>& x)
  {
    this->final()=x.final();
    return *this;
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  random_access_index<SuperMeta,TagList>& operator=(
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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    clear();
    for(size_type i=0;i<n;++i)push_back(value);
  }
    
  allocator_type get_allocator()const BOOST_NOEXCEPT
  {
    return this->final().get_allocator();
  }

  /* iterators */

  iterator begin()BOOST_NOEXCEPT
    {return make_iterator(node_type::from_impl(*ptrs.begin()));}
  const_iterator begin()const BOOST_NOEXCEPT
    {return make_iterator(node_type::from_impl(*ptrs.begin()));}
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
  size_type capacity()const BOOST_NOEXCEPT{return ptrs.capacity();}

  void reserve(size_type n)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    ptrs.reserve(n);
  }
  
  void shrink_to_fit()
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    ptrs.shrink_to_fit();
  }

  void resize(size_type n)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(n>size())
      for(size_type m=n-size();m--;)
        this->final_emplace_(BOOST_MULTI_INDEX_NULL_PARAM_PACK);
    else if(n<size())erase(begin()+n,end());
  }

  void resize(size_type n,value_param_type x)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(n>size())for(size_type m=n-size();m--;)this->final_insert_(x); 
    else if(n<size())erase(begin()+n,end());
  }

  /* access: no non-const versions provided as random_access_index
   * handles const elements.
   */

  const_reference operator[](size_type n)const
  {
    BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(n<size(),safe_mode::out_of_bounds);
    return node_type::from_impl(*ptrs.at(n))->value();
  }

  const_reference at(size_type n)const
  {
    if(n>=size())throw_exception(std::out_of_range("random access index"));
    return node_type::from_impl(*ptrs.at(n))->value();
  }

  const_reference front()const{return operator[](0);}
  const_reference back()const{return operator[](size()-1);}

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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_(x);
    if(p.second&&position.get_node()!=header()){
      relocate(position.get_node(),p.first);
    }
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  std::pair<iterator,bool> insert(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_rv_(x);
    if(p.second&&position.get_node()!=header()){
      relocate(position.get_node(),p.first);
    }
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  void insert(iterator position,size_type n,value_param_type x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    size_type s=0;
    BOOST_TRY{
      while(n--){
        if(push_back(x).second)++s;
      }
    }
    BOOST_CATCH(...){
      relocate(position,end()-s,end());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    relocate(position,end()-s,end());
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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    difference_type n=static_cast<difference_type>(last-first);
    relocate(end(),first,last);
    while(n--)pop_back();
    return last;
  }

  bool replace(iterator position,const value_type& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    return this->final_replace_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  bool replace(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    return this->final_replace_rv_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier>
  bool modify(iterator position,Modifier mod)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;

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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;

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

  void swap(random_access_index<SuperMeta,TagList>& x)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT_OF(x);
    this->final_swap_(x.final());
  }

  void clear()BOOST_NOEXCEPT
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    this->final_clear_();
  }

  /* list operations */

  void splice(iterator position,random_access_index<SuperMeta,TagList>& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_DIFFERENT_CONTAINER(*this,x);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    iterator  first=x.begin(),last=x.end();
    size_type n=0;
    BOOST_TRY{
      while(first!=last){
        if(push_back(*first).second){
          first=x.erase(first);
          ++n;
        }
        else ++first;
      }
    }
    BOOST_CATCH(...){
      relocate(position,end()-n,end());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    relocate(position,end()-n,end());
  }

  void splice(
    iterator position,random_access_index<SuperMeta,TagList>& x,iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,x);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(&x==this)relocate(position,i);
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
    iterator position,random_access_index<SuperMeta,TagList>& x,
    iterator first,iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,x);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,x);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(&x==this)relocate(position,first,last);
    else{
      size_type n=0;
      BOOST_TRY{
        while(first!=last){
          if(push_back(*first).second){
            first=x.erase(first);
            ++n;
          }
          else ++first;
        }
      }
      BOOST_CATCH(...){
        relocate(position,end()-n,end());
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
      relocate(position,end()-n,end());
    }
  }

  void remove(value_param_type value)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    difference_type n=
      end()-make_iterator(
        random_access_index_remove<node_type>(
          ptrs,
          ::boost::bind(std::equal_to<value_type>(),::boost::arg<1>(),value)));
    while(n--)pop_back();
  }

  template<typename Predicate>
  void remove_if(Predicate pred)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    difference_type n=
      end()-make_iterator(random_access_index_remove<node_type>(ptrs,pred));
    while(n--)pop_back();
  }

  void unique()
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    difference_type n=
      end()-make_iterator(
        random_access_index_unique<node_type>(
          ptrs,std::equal_to<value_type>()));
    while(n--)pop_back();
  }

  template <class BinaryPredicate>
  void unique(BinaryPredicate binary_pred)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    difference_type n=
      end()-make_iterator(
        random_access_index_unique<node_type>(ptrs,binary_pred));
    while(n--)pop_back();
  }

  void merge(random_access_index<SuperMeta,TagList>& x)
  {
    if(this!=&x){
      BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
      size_type s=size();
      splice(end(),x);
      random_access_index_inplace_merge<node_type>(
        get_allocator(),ptrs,ptrs.at(s),std::less<value_type>());
    }
  }

  template <typename Compare>
  void merge(random_access_index<SuperMeta,TagList>& x,Compare comp)
  {
    if(this!=&x){
      BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
      size_type s=size();
      splice(end(),x);
      random_access_index_inplace_merge<node_type>(
        get_allocator(),ptrs,ptrs.at(s),comp);
    }
  }

  void sort()
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    random_access_index_sort<node_type>(
      get_allocator(),ptrs,std::less<value_type>());
  }

  template <typename Compare>
  void sort(Compare comp)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    random_access_index_sort<node_type>(
      get_allocator(),ptrs,comp);
  }

  void reverse()BOOST_NOEXCEPT
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    node_impl_type::reverse(ptrs.begin(),ptrs.end());
  }

  /* rearrange operations */

  void relocate(iterator position,iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(position!=i)relocate(position.get_node(),i.get_node());
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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(position!=last)relocate(
      position.get_node(),first.get_node(),last.get_node());
  }

  template<typename InputIterator>
  void rearrange(InputIterator first)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    for(node_impl_ptr_pointer p0=ptrs.begin(),p0_end=ptrs.end();
        p0!=p0_end;++first,++p0){
      const value_type& v1=*first;
      node_impl_ptr_pointer p1=node_from_value<node_type>(&v1)->up();

      std::swap(*p0,*p1);
      (*p0)->up()=p0;
      (*p1)->up()=p1;
    }
  }
    
BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  random_access_index(
    const ctor_args_list& args_list,const allocator_type& al):
    super(args_list.get_tail(),al),
    ptrs(al,header()->impl(),0)
  {
  }

  random_access_index(const random_access_index<SuperMeta,TagList>& x):
    super(x),

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super(),
#endif

    ptrs(x.get_allocator(),header()->impl(),x.size())
  {
    /* The actual copying takes place in subsequent call to copy_().
     */
  }

  random_access_index(
    const random_access_index<SuperMeta,TagList>& x,do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag()),

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super(),
#endif

    ptrs(x.get_allocator(),header()->impl(),0)
  {
  }

  ~random_access_index()
  {
    /* the container is guaranteed to be empty by now */
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  iterator       make_iterator(node_type* node){return iterator(node,this);}
  const_iterator make_iterator(node_type* node)const
    {return const_iterator(node,const_cast<random_access_index*>(this));}
#else
  iterator       make_iterator(node_type* node){return iterator(node);}
  const_iterator make_iterator(node_type* node)const
                   {return const_iterator(node);}
#endif

  void copy_(
    const random_access_index<SuperMeta,TagList>& x,const copy_map_type& map)
  {
    for(node_impl_ptr_pointer begin_org=x.ptrs.begin(),
                              begin_cpy=ptrs.begin(),
                              end_org=x.ptrs.end();
        begin_org!=end_org;++begin_org,++begin_cpy){
      *begin_cpy=
         static_cast<node_type*>(
           map.find(
             static_cast<final_node_type*>(
               node_type::from_impl(*begin_org))))->impl();
      (*begin_cpy)->up()=begin_cpy;
    }

    super::copy_(x,map);
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,final_node_type*& x,Variant variant)
  {
    ptrs.room_for_one();
    final_node_type* res=super::insert_(v,x,variant);
    if(res==x)ptrs.push_back(static_cast<node_type*>(x)->impl());
    return res;
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,node_type* position,final_node_type*& x,Variant variant)
  {
    ptrs.room_for_one();
    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x)ptrs.push_back(static_cast<node_type*>(x)->impl());
    return res;
  }

  void erase_(node_type* x)
  {
    ptrs.erase(x->impl());
    super::erase_(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    detach_iterators(x);
#endif
  }

  void delete_all_nodes_()
  {
    for(node_impl_ptr_pointer x=ptrs.begin(),x_end=ptrs.end();x!=x_end;++x){
      this->final_delete_node_(
        static_cast<final_node_type*>(node_type::from_impl(*x)));
    }
  }

  void clear_()
  {
    super::clear_();
    ptrs.clear();

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super::detach_dereferenceable_iterators();
#endif
  }

  template<typename BoolConstant>
  void swap_(
    random_access_index<SuperMeta,TagList>& x,BoolConstant swap_allocators)
  {
    ptrs.swap(x.ptrs,swap_allocators);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super::swap(x);
#endif

    super::swap_(x,swap_allocators);
  }

  void swap_elements_(random_access_index<SuperMeta,TagList>& x)
  {
    ptrs.swap(x.ptrs);

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
        ptrs.erase(x->impl());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
        detach_iterators(x);
#endif

        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      ptrs.erase(x->impl());

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
    {
      typedef random_access_index_loader<node_type,allocator_type> loader;

      loader ld(get_allocator(),ptrs);
      lm.load(
        ::boost::bind(
          &loader::rearrange,&ld,::boost::arg<1>(),::boost::arg<2>()),
        ar,version);
    } /* exit scope so that ld frees its resources */
    super::load_(ar,version,lm);
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const
  {
    if(size()>capacity())return false;
    if(size()==0||begin()==end()){
      if(size()!=0||begin()!=end())return false;
    }
    else{
      size_type s=0;
      for(const_iterator it=begin(),it_end=end();;++it,++s){
        if(*(it.get_node()->up())!=it.get_node()->impl())return false;
        if(it==it_end)break;
      }
      if(s!=size())return false;
    }

    return super::invariant_();
  }

  /* This forwarding function eases things for the boost::mem_fn construct
   * in BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT. Actually,
   * final_check_invariant is already an inherited member function of index.
   */
  void check_invariant_()const{this->final_check_invariant_();}
#endif

private:
  node_type* header()const{return this->final_header();}

  static void relocate(node_type* position,node_type* x)
  {
    node_impl_type::relocate(position->up(),x->up());
  }

  static void relocate(node_type* position,node_type* first,node_type* last)
  {
    node_impl_type::relocate(
      position->up(),first->up(),last->up());
  }

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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    clear();
    for(;first!=last;++first)this->final_insert_ref_(*first);
  }

  void assign_iter(size_type n,value_param_type value,mpl::false_)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    clear();
    for(size_type i=0;i<n;++i)push_back(value);
  }

  template<typename InputIterator>
  void insert_iter(
    iterator position,InputIterator first,InputIterator last,mpl::true_)
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    size_type s=0;
    BOOST_TRY{
      for(;first!=last;++first){
        if(this->final_insert_ref_(*first).second)++s;
      }
    }
    BOOST_CATCH(...){
      relocate(position,end()-s,end());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    relocate(position,end()-s,end());
  }

  void insert_iter(
    iterator position,size_type n,value_param_type x,mpl::false_)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    size_type  s=0;
    BOOST_TRY{
      while(n--){
        if(push_back(x).second)++s;
      }
    }
    BOOST_CATCH(...){
      relocate(position,end()-s,end());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    relocate(position,end()-s,end());
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
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=
      this->final_emplace_(BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
    if(p.second&&position.get_node()!=header()){
      relocate(position.get_node(),p.first);
    }
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  ptr_array ptrs;

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
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return !(x==y);
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return y<x;
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return !(x<y);
}

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return !(x>y);
}

/*  specialized algorithms */

template<typename SuperMeta,typename TagList>
void swap(
  random_access_index<SuperMeta,TagList>& x,
  random_access_index<SuperMeta,TagList>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

/* random access index specifier */

template <typename TagList>
struct random_access
{
  BOOST_STATIC_ASSERT(detail::is_tag<TagList>::value);

  template<typename Super>
  struct node_class
  {
    typedef detail::random_access_index_node<Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::random_access_index<
      SuperMeta,typename TagList::type>  type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

/* Boost.Foreach compatibility */

template<typename SuperMeta,typename TagList>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::random_access_index<SuperMeta,TagList>*&,
  boost_foreach_argument_dependent_lookup_hack)
{
  return 0;
}

#undef BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT
#undef BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT_OF

#endif

/* random_access_index.hpp
qrd9stfi+ZCLLz/vI+lZ/F0ntwgz8GRGzI4emXIGGzhc5x6qEDOnYuaiSYb67IO0GigpNxDDw/LZ1bYKMsXnDNsGOLIDAqmV93Q9yk/WKnqyKTWKgnhxjrgoX2JiC6uMGP7h322DPuyJjfrKvS2eY/ZAZ/vhMNTOP7qQSD58ixTs3dDpICUGxIoi4/aTfCOLI5GCf37NGVlW9uXligv6SQiiwN7fpHPwp/bxQgX77pApYeL/3E1M1wotwyhEexab5O0Rwz8w8785vSzJ5XjU9Vl+WmILtUsDdNYi+9wsmz1QGIG+L3Dqiqstq9CmKk12Pkw/euLKZixtszZIHNKE6CMIbSnA59RSl1T+lk69KPqhoNkA/Rb7q8zSPpjq3E9R57oPM9S4nyLNdB+mqXI9Rpjq3u2uGNH/9mifhtr5BoelPymRccfkVKZaRLPgIcH3r4oOEGnN2KFYuAOUiiXycplIcd9RUr0GfbC/mncdpG5HzR8HjK+nH3qhXRDUfMmisO1tBdDhJEGAGjDlvLxmkIvl6YOAZAsV8KwibIO3Exto51v2BzUyQtDKYfTdClzoiAX58K34c2N5053VoYQ0exkz2StZyAT4gW90708hiTO025mGhWNTDBiETfeJ3/K5RCCA1rf5hum5FtvqAOCaSGA6vg2Li9wMsPt7Xp3QZhB+nxWjojJB2Dl8Uw+rxiZFDzQBIz8EBMMnB3uQ64eJjtDlEEBDC+UYrKGn3JVeUR42sZ1gkBiJ8t1Fr/YCaeMAl7QYHWW4jrTng/BxIBymPSIYmiqYniaTUMREaQxRBp1OwZr12pV6a87lnZB86dvIUrovNwLFKFTiA3u1J1EOePAF0C9TL6FdN0XXkdBHYu2iEPkVllWyEeoygAlngE2wU1aBSNAVp2Fiq8aBoN0ERgGXFyv9MOnjr5v5GwwyNO2VCDVT4bloxA+bRFa6KIEDzsNiLLaDsA1P6C2q60k7C4rxH5xpI5/3lHWKdrZvB1db60hEH7oeDkLTDUhNeYOZ9V1NrhkhqHlo13kCTPC+DRV3QJc66vFk1DcDDkbeyPAazqdFSMOJyXHb7Yno68mVjpmwxFRtNpH825pKk026AVvvSz3yU3ONbXfGhKAuONY49leuUG9CPYhuqp0NLysuLk+nKIHUiYahoXbjTSEGswAU38BOEXH1RyCVwOd/JTeGWf8WHk8+z9CsTEsjyejR6zg0UemViBJmsJfa+iuX4egppRP/TnffOjUopviXjRh2fxY+4PhWjRYg2y1Xd89CXAvdiZzQulJ7AuDFgpjcC3p+Ym5kS2cogUoSPABfAkZre9SLtgG7Rmt8JKPAF7rEfyMAUSm6zlmiNrme6u9FjtY1HFzzfLv7a7XAAsCr9ZGTp/ZGkYbQjxbmDkPiAOMWybHImy2kd9IR0yEYgtX5TQ92n3ffxxp8EHorJPzBVU8JfdlGsZCJLGi+7RWlDnIqif6JjvJUncmbBoYlk5Y4trXtnbCIzAZ4Z3kymbS80WY9UkWyk1cTE/RA49qrdCRNJL2gGcn4ULoTeyHXYPdxuSYJqHteTotKJ9pH3IyLMARgEB3hZUA8hBY2bSkG30W4uJ3TE/b3slM/7SU+durqfva+SrywvBv1ztE4713MUUWus+0+ML9ismCO32BU9jJ2sM72sG7umaKXxy2uM0IzrDjwuEYPFiNdDaVdSKHvr+203AcGMT16mvuDRKFpnTC9uFvlvk+VDt/l5yExQzoBclgVCtj5UnU2tqZ2AV9iI03GiWIuYrB9Sf7xd+8duTCjyKGKvYHWUfVCE6WMEQM1zOE3Nut7NrgXeLZy18uoyXryh4AFQ2D7pf17GiVdoNf2qWP15wXYAiIJ9Im4CyhjFPWjL3KScJLgqb+sKhyU7nNqTJpyXlauuZqK76FCGv7CA2ckhYLlBNlEGkSrCGIOOh9w3v/75ulP2Di7lmWGgisBdAUEHYrxlhlVe/KvA073ee9xztJfKwZzTkwVXEVY7c2jzHxHelXCJ8gwwHdp17BjUgE7SthYLtzpw6DvFbQBhV6kx+3x3dXMXbLIRbpFucPzcBzcY4qKH8IcZyZfXX78p8a6esYPUrxaIownYEsAL5gOxULkLrQgAsWjLkLd6ShoJJgf/ZH6/pu0BYn/CnuUg1vo9WPF2vA07i/+rsUehlw67Y1qzvj5o1n7D7TtnLrdZ6n4U/GFUj49RpaSgn/fbjf7UsRpvYj10shoguXBxDPAuFXn6fysd4gTMkCTrD+tXD00bsNS+JA+0nqEWggQEvUMU8PdhRWOf2XWxSviQ/ApDX2B1DYXyOSc+KarzCl65G0VV6Y1vydX7tlkMBRwtrslzNsyr71CVnkJkxOSAUFTgqizmsR1F9fERTngFd6v5oe28mdq5e59FSgee+vZY+XHTeTYpxWgJbs22qhMvYD/R49O7pZKlgGpOSMMvpgZlPTwA8J2rDxWpnfBLnkxSxzVpEJvE2y/9keqlsqYFW58RsVMn61qyIOfb2naKTe2vL7XKpWy8w+k3RhHpBKqoor7azgvY5wJ2cOUaE76OCOCmynBjOxxWjg3Y9zPKK/97u8hoouBygcvlVwo+i80Jc1J6Us7mnvmk1hD5S0GJlx3lmoJ2Jlg7bU2d9ybwTcnHZUM+a97SdgEAGS4W9f0Ua/0sjbMqmJsS0Lmb+tJxftRrPwkwS3ShLIDrrH3vqoG5n3ygdtl3NdS4+eaD7vi2RDZJZMB5Tsc6qzSF/wEzJ7Dgw7LMagdknmlqj3uG09a5812LlKpDGBPU+hIxba7Zz9dPN5OrJxosoepFIa6jhN1Cb27x4FC3ywGnhxA5ez2by0shvSCa+2vOv9k/zi4KpeN1RmQC4yV857Q5XdAzvtlmc26Q0xT6uIeFzjHe55PE7XwccOxebZfyY5Z4pX0GRmdjr3q5oaAhX4CMw0sr9vuSkyWH/XnxBPM0n9uhvZmM1c/vhV8LojYL+t7SNXeuD8PfeoQNFiOenBXF9vdHtNmR4PVvLHAGEseo/6rTavM/UwmgMEBVU2i/2AqaTfKTcpHcqzOtQ1kvSFBD1/aYV+HcdXmUind4W9XXhyMeW+AfEUHHy1m+XuB24F1Mw2cVpHlSeAjw4q1rSttIAHv/iHR2Yg8w2nu3MDDBt7ed4GdRbHbKITBWeQjjFx64B/vcZn65hHp2hX00WEAm9W+6GLMwO4zWjL7SHGQUG1s3jJAH0VL7UnglaBvxFoJGYJx7d/RzeXSxfrSzUbxxFFPBEhi705jw8CC8UWBXQfSzKl4kB2S41wXAjREvl1mUYZVkMngZVa0KTsCLfLf5V9+HMvG0seXzw/+9c6JGvLv3tjDwDlCMaJAxYJOYbNkDNZ/wcgq2Nmb3I8AiFjMRZp8m5ztzC6fSUGAC4fDA+K756Sz9nN165IzdDPHd/+efcZxp7ZtOR79U9s2yyKHrWCTVmVSjWArfzAY9lSplmAHmlbH+FW0RZNVuK++t1F1wnx3vXRvYdS/DEmC9TRZ58KKP7+A19y1fl0FuyiAxarwYbu9OUZbt71x9vx6pXvmm+I4DLh+41iyAoDWo/TRzY0ZiQn9ODSTd6qEVudW3orrApx/gbrP6fTWhTK5TiNl3hoH4MAIq5QhBfHTrdpVHTMLCoKvdn3VB69OXUdp+FHpyDD8PaXFYvyPPrl0O+9dzjovUBbVnbxCZIs9quPMyS5IZvDjR2ayUKtb8LcARSmnXr+oeFoq8oQMaa0TbbOEgiomoIkKi4TOnPVS5ShdNXURk9C1WWsroym/xijJiVgDJyfVQh6hqypuJiYyE0IZ0L4Qpz3Qm1fWuiF0BSHH5SM0ApQI8hleZmimG1wuDxY3TyEZH7kmNOcwE2vyLO/HdusEealuoJ+P+6Sl8S2HufLTHsYkefSY8l+gCKg1A8Owyv5mrGqKulyNccQAR7dxxQLh1068HAX8076CE8BT5qGt8MVFW82ZMYbN4lt4g9RN/ww/0ESqXx7O/2DbHmNFh9510a9p27Zt27Zt2/aatr2mbdu2bdvWmeeee2/O3v+dJ783o2+a9kOTdoymTfIm7GZW3qcPdTZsmhZ2LNxQ4iAmObNXM8snaAinPaY3fb2srCq3OqSOIHZYTfRL4Yr/+0l5OYSTJqx4hH+UEbgU/15yBflPY/LAmwUO4qrlOQit2y/N7L5iVqJvEAy6qBLZk4yXDsJhERaLNV5VJpbvsJXn7PBgKbZbVchjSrVjClUh8upCDYpYRWFFEfy6VO96oLY+FPeQSVZidr6OgQhrALosR9BThT3jbolwrELY3YwIaYM0G4XwoDVugdsKBi0faynU+fbu2pAFKfu6zXc4pEjPOzoOWgKeMWwR6+mS5bBeMGAgsJUyjXFUjdkgyw8r/JshTOjgwW/48+EmUXxbNDO50kZeMDRef0oyJONPUbH/G2G8ZL513OABdpnQd2gHFrVwrJQMDUVHOzSKpYkrF9iEQMkixwfAWAkuRVJUR4kqa3XOzQYLDeiCnNh7FI/ku9AXm7KXohec4rp1kv9rmDTT8roFhL1QOrzhHnloTPhPnMVfs+ofFxgOWnrrsErWujnR+tQ6Ap3VG1Q0Pd8U0H2J16+7JZgUFFlDM/CxVOxO0fFGEB1TGycehBBOqnwqeQd4CtxcGb1yde0NhRLwnePIg2mPR2LXhYLD+H94p3lZWolOlos+MQtX1LOE9no+7L2DiENy97DPcdQhdo6Tkt4FFK/6iXn4l4ZtkyDxKgz847frkKSozFxNATOCI8azEj8mwlspIgHqcJmBWvuhXU2V3H/dlCYKlEW6rMzoLbNLaZqI1RinIbUSK1OjbkrCN7FNMc0OR5rC0ebzY2TLZpU+TqxazdHiaYgNmhAVXHbPpCCy5mVg3X9KsvPB0ooaP/XdDYz/3r4qvn/UQAinJ80rHsndgvEDIXniAMR+HY6xwiLEgPwZDca5kmAYBuc8J+dP3Bf+0MSjxImMolOuzjOQlNiV9T9P7x86YCbFqXv52mCf3gFOy4Ypoq/lcGJsi8oE6/LPLW2QOgZ+wrRa9UjMGDuPSu00aEggcZRR/TOIApzVFtmZYh2Hyp+vnJ7RHbtqVFkjY+YBqS8XdzFNBDsXUfaZQGOFx34BPejYQOSR2CvhJkEOc10VeqEK8fYoV7yuutM36Bk32H+5OUigLbvPL2AuilNmZf3sfSUFSL1xuq0nYsKM347hTkM9TIRkSHvtLMn3t6WgVYVvU0JrNKac7dY1NbpXk6x2S4d9UjwZ1TV9SkYa5a79j6NRE76VmBLvfNJsPyh7OG6W277ri+7RiegMK3B5pQ3NHYxd+UAq++nnC10+L1YAV3gZC2BUUnl6cKVzOLEV0S420+lLW0cy9AjaAZJwV19LY6vc+RNg0HLo+JaNyQWESlWRuUaka+/I2y2bgcnrUs8NYVllzpKx53IjL2zTR8g9D8ybBcwiQwzIbLkVb4zTo/y5iNEZkMYl9ACuZTBz4mnioPBdCvMYwnkLDMDUp9DwnRDFeAzHG/BhAHR9aUvgRcwsE7yb/T3umBnzPGIwk9CXOgV/l8wpSWVHfAIcNv9G75+Vp+yOgshOLufz5psGFoH7EtKOTgX9MzLKe1HDWHZOmZkC6h6GmpxdHqo/KhP5g+9PfRi3ZxcSnlnLYVke8MmpfxGVbY+xtgrQAfwJlp5wy7qkTz64iHbqRnSqklvEV6KQgER8Yjwyu8PNuO1RcdGuKhpXZm2fPx1R+XnrrqVt6D4LVWP7lawD7e4/oI5x8dHJb/NFO7jdAlC8uI43CY+AXqdqVDsOw+skxzdES0PnbA+uoFO27xZeTNAihEhN3ImIYEQurOvzDJD/OIDdQy4rZqfuaGGLPQUgTm6lf4mET4a/DKsdv3OEUxO0fgTY+7KBUjmvT5asQxQktXxd1PC3TaYyxhT7UV3oGQ9x1dfUmNn5VXe47LSHEQVqOi9DWC/nKl8l63Jaxb+s4wO4uPekpXPqLXIWCysK5cLoGDYKKaSN7Iz5qeGIdAGNahBx0cHgBmqN+jny1iM7tQUmIAE0IwPVhy5cCrZxcKInOaA6jbqt5qo+cSM9YjMAJjkgSFiSgxiu7z/A1NmkKYJtAsSD3M3DAza3u5ijn5cAmtCW3AbO4NPwFEwVaWbcfWQIDPq9/1G7J7peNx57KdCO4BaZTCwoRdKTFf2IoysZY5motrZDMSiBUzCBMnbK2ZGuSZ9dOsEJ7+OuIDD2GHC8u5DUW4jiu3iPqO0ZQ10uQZqgtsKzkhcuPAai3rWeQiU9WvQ69ytu1Ck1jksXdNa2BIzm/ElTl6/Wgw+p5XKVaJa2kklEW0Pgmb/RUdIO89T9ie3rq+JG3znZzzUKIBY/66kykHSD328grLHrc5/RkF3yxxF08mNOtC80/VxiIRzgjVF4Doz3d6HEteVApeCiOzAQ63ptyXgOnuYSynjWz7npAqBEgNZQTdwiz4H+XGqw1KTGsfQPj3UPdisBzGrUb9PKSq3rvVJixhnUSrbpE1OU4PNnxerSqbT7R+ZLjJPQmzZCaPdQuMUuZelM0cqvo5V5wBKOvaYOtgVWFS3s2YLSF7OYS0wtd/hs6dqwGx/a0K8EhDJWQ895CPCJHkY28VDSel716T25Mcx+oytzV7cKun4S1dE/IB7qCYEtEvCWRqYsB8bAkRBu+idZoHIzz9z2NsEK7qMQUUMPBesClDvsTVjRs9BP1gFsLY0B2VpLcQImGqNlGS42krrMCRhG6fkwPGZWz6AoF1YyBI3yJ31YKJscDBnq+4J+PlvhZYsZ/eTPMnBhiFFOWbF/Tl9k9Aj9bEFsxjyy6+bzdLOoa0wtZxknVJyGT5g5xVaX8pqO4JjhyB77xqK/JqbgCTIv3xZ9UbSC15jUHfFmQQmP+9zEqwk6GDTyv+EQs6/xniJOU4BJqcQXPVv9ZrJrLnhGDSsOWMWZq49kOJGAQNo70tB30Uok3/K3N1ReghgGKlSNTGMmDJGMuCcDKo40S3tPw070kOX0jndoaz8NedIjbC0JLT0TBv6F6PBQGGEoUn6pIkg/b4zS0iSzVjb77MKdHbDBZZ8kSiSL1hfwoA8K6LYPl9dsbGnDHmG5ZnDF0AK8IilbrHffQW/ZqaMm1FHcu5izeoMZ4mxZqt8JgkbWl9AiIPDguduwAqlV2dISd7czodVo8YlVvuX8m8kNwdtO2/20SkYSh3GHxBBWGoebPVbxl2wZBfrxZ9YegR5+t1cNwydh2Qy3oGAD101dRhkmnmwil1BuTnpI52kV6/z7VxwyKFo1SyVwbu3nct3nxdboVZ2lTqL2LY9GV0ZqJrGBCCwVfQnOo7rz5afKnpnqaYe7JCu8KLMOS5ufPkB7DvyjMwzMABxeJ/+ZMHvK09Y2qGqEMB9Gsl04U22xxbi/tw2OuXf//ghskkohBgNTsEP/i87RzQy/7N6QyDHJ7kk6pAIMgiusLyfOnL+ni6T+ZcPQ4aIwomaZaBqe7sEUnLcDwSBZV0DI00Wv3SqG1+TVYMlA7nG4FaEEyE791jSr+0VFWSbyS/PmoUXfS5fH1ZInkW2J2qDa0UF7iL6d+qacrMzsn0btdZ1vFd3djdlGAW34dGlmqMboayRU4orMsNxHmjmySRzn83jk6sWXR+ivcuvTSkf86a1S3ESSC/WRyiDR5IU3jg3FikdCrwV42q+oGhfpUJ1eVHOyTrDl1Ilg2o33jXKnKLF43Y3Dx/yQEdekVTPWtujlfO7qBwrfhXU3Xo3lOy8uWD1mSiyoAdyQLve7+0qmMNSCNnlss35zQj0mWT2vwKWVw0V9jKE/lxU8wLn1HxMMflk/qlGpjmrgH93MWo4tgk1bb5QVq57TlzFeQCphS2NEDaVPPHdrF2x2mFiZ/RudcZfNLB0g/zaa5WUGiStWrZ7n9e87u5ZBgAcih0cxlTzIXcwS74Gs4BPs2f274JHKdqYo76fJH7DKeELI1To0AkSzZ0MuXNVgjYT0onz5Wle9J/RZzlFWtKpwj6C0u/wxdNtDdad1M9FwVmSBZXeeQoFrMUA2sERzW4dXHM40oaev9ck66kUK3U3hVGpqUGs4sMjop4zPz58pZysqJs9M2q0zGfo7mW20Xhj2b+4qr3IPdJhyqY+8JynQrnez/TIcc4TfRHJNk38gWvFyXe4VnQJB99AEtNa2tZyslwStcICdOX4aaFNRPtRoXp0dIe5d9EL4eZuO3m/8Wlpirzxa/VbFzPeMCV7nlh3PqEVjpThqOLkOJL/7Ak8k2bQ5Dt8qBUs2rozOTfysnA7sPwzxStjpMM3CzyXMYSmGjuhclhJVqVDSHdS9Kqqb+jXGlmnL0S7vvbdzh2gInMzc8q5UciVZqvIi1xh4L3lYyZDNraEhtv5W3Lu9K6isPaOo4Uu98YWdmPDWlo1NSb8XDbwz9F7jTa5e4HePKQxPhVzil3RcnPKxvKW3jrT7QQzdVtxfi/G2K3ss/Q3tmXQMNGt5Poic1wp0eL46n7zigyyrVNgILslNgXQeHU762kgWRN0kPqPhiVEXfAgJq3bzxPK7NdmF5Wtuq0Jto4vXXUdq1q7pdnTVs36rcFNCCiT8+fpCAueLSTkEX0Yqx9i45g7shql1fZJfQ0XcmP2wKMXpfBGIbLP02mja0bDy5T3YdlRwe7zzZhs+mSR0VupvW0AR+4i1eh4aY4HXTzwITareEd60jtlhHsosdl9AtsvYl1HqtIhgk7krpthmHvoZwQo7+9lC/sBXVNYjPktUCJKwXNnpxsBlys2cPD2jJmkWQdYUnEc6hoy/QS/gY4S81YD25Ozm/XHyoN0+GJQd5DxGcI2zHdfJooKtOJ1hRdOiL0mC3VsrxhlZ4dDY/pC5RWKlX1m2uH4du80MH1umuhfi8KXMeQxuy1nk52J77/ixo6xOmTMjt3l8vCMpU0hY/xZDwLFp5OI/UJaLcU1LO/dr63NuYPM1usKy2lH/GF5nW+6ue45usqv0Mbr6aVjefsvtugvm9EF0ySiRKsHILYMmTQuuJPD/kT4CnBhRFBN9Cmfg0s15I/gUjdUpnamqttz4QTL9EXKRRVtaWrlmf3g/PCmXa5H7kYnOUp287dMij3hpFoV4sLFCGRbbSCejT/L5fHsCk+tdiaVGaobgNFlKrVnboko=
*/