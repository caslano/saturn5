/* Multiply indexed container.
 *
 * Copyright 2003-2021 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_HPP
#define BOOST_MULTI_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/addressof.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/adl_swap.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/base_type.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/converter.hpp>
#include <boost/multi_index/detail/header_holder.hpp>
#include <boost/multi_index/detail/has_tag.hpp>
#include <boost/multi_index/detail/invalidate_iterators.hpp>
#include <boost/multi_index/detail/no_duplicate_tags.hpp>
#include <boost/multi_index/detail/safe_mode.hpp>
#include <boost/multi_index/detail/scope_guard.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/base_from_member.hpp>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/multi_index/detail/archive_constructed.hpp>
#include <boost/multi_index/detail/serialization_version.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/throw_exception.hpp> 
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
#include <boost/multi_index/detail/invariant_assert.hpp>
#define BOOST_MULTI_INDEX_CHECK_INVARIANT_OF(x)                              \
  detail::scope_guard BOOST_JOIN(check_invariant_,__LINE__)=                 \
    detail::make_obj_guard(x,&multi_index_container::check_invariant_);      \
  BOOST_JOIN(check_invariant_,__LINE__).touch();
#define BOOST_MULTI_INDEX_CHECK_INVARIANT                                    \
  BOOST_MULTI_INDEX_CHECK_INVARIANT_OF(*this)
#else
#define BOOST_MULTI_INDEX_CHECK_INVARIANT_OF(x)
#define BOOST_MULTI_INDEX_CHECK_INVARIANT
#endif

namespace boost{

namespace multi_index{

namespace detail{

struct unequal_alloc_move_ctor_tag{};

} /* namespace multi_index::detail */

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1500))
#pragma warning(push)
#pragma warning(disable:4522) /* spurious warning on multiple operator=()'s */
#endif

template<typename Value,typename IndexSpecifierList,typename Allocator>
class multi_index_container:
  private ::boost::base_from_member<
    typename detail::rebind_alloc_for<
      Allocator,
      typename detail::multi_index_node_type<
        Value,IndexSpecifierList,Allocator>::type
    >::type
  >,
  BOOST_MULTI_INDEX_PRIVATE_IF_MEMBER_TEMPLATE_FRIENDS detail::header_holder<
    typename detail::allocator_traits<
      typename detail::rebind_alloc_for<
        Allocator,
        typename detail::multi_index_node_type<
          Value,IndexSpecifierList,Allocator>::type
      >::type
    >::pointer,
    multi_index_container<Value,IndexSpecifierList,Allocator> >,
  public detail::multi_index_base_type<
    Value,IndexSpecifierList,Allocator>::type
{
#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
/* The "ISO C++ Template Parser" option in CW8.3 has a problem with the
 * lifetime of const references bound to temporaries --precisely what
 * scopeguards are.
 */

#pragma parse_mfunc_templ off
#endif

private:
  BOOST_COPYABLE_AND_MOVABLE(multi_index_container)

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  template <typename,typename,typename> friend class  detail::index_base;
  template <typename,typename>          friend struct detail::header_holder;
  template <typename,typename>          friend struct detail::converter;
#endif

  typedef typename detail::multi_index_base_type<
      Value,IndexSpecifierList,Allocator>::type    super;
  typedef typename detail::rebind_alloc_for<
    Allocator,
    typename super::index_node_type
  >::type                                          node_allocator;
  typedef detail::allocator_traits<node_allocator> node_alloc_traits;
  typedef typename node_alloc_traits::pointer      node_pointer;
  typedef ::boost::base_from_member<
    node_allocator>                                bfm_allocator;
  typedef detail::header_holder<
    node_pointer,
    multi_index_container>                         bfm_header;

public:
  /* All types are inherited from super, a few are explicitly
   * brought forward here to save us some typename's.
   */

  typedef typename super::ctor_args_list           ctor_args_list;
  typedef IndexSpecifierList                       index_specifier_type_list;
 
  typedef typename super::index_type_list          index_type_list;

  typedef typename super::iterator_type_list       iterator_type_list;
  typedef typename super::const_iterator_type_list const_iterator_type_list;
  typedef typename super::value_type               value_type;
  typedef typename super::final_allocator_type     allocator_type;
  typedef typename super::size_type                size_type;
  typedef typename super::iterator                 iterator;
  typedef typename super::const_iterator           const_iterator;

  BOOST_STATIC_ASSERT(
    detail::no_duplicate_tags_in_index_list<index_type_list>::value);

  /* global project() needs to see this publicly */

  typedef typename super::final_node_type         final_node_type;

  /* construct/copy/destroy */

  multi_index_container():
    bfm_allocator(allocator_type()),
    super(ctor_args_list(),bfm_allocator::member),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
  }

  explicit multi_index_container(
    const ctor_args_list& args_list,

#if BOOST_WORKAROUND(__IBMCPP__,<=600)
    /* VisualAge seems to have an ETI issue with the default value for
     * argument al.
     */

    const allocator_type& al=
      typename mpl::identity<multi_index_container>::type::
        allocator_type()):
#else
    const allocator_type& al=allocator_type()):
#endif

    bfm_allocator(al),
    super(args_list,bfm_allocator::member),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
  }

  explicit multi_index_container(const allocator_type& al):
    bfm_allocator(al),
    super(ctor_args_list(),bfm_allocator::member),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
  }
  
  template<typename InputIterator>
  multi_index_container(
    InputIterator first,InputIterator last,

#if BOOST_WORKAROUND(__IBMCPP__,<=600)
    /* VisualAge seems to have an ETI issue with the default values
     * for arguments args_list and al.
     */

    const ctor_args_list& args_list=
      typename mpl::identity<multi_index_container>::type::
        ctor_args_list(),
    const allocator_type& al=
      typename mpl::identity<multi_index_container>::type::
        allocator_type()):
#else
    const ctor_args_list& args_list=ctor_args_list(),
    const allocator_type& al=allocator_type()):
#endif

    bfm_allocator(al),
    super(args_list,bfm_allocator::member),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
    BOOST_TRY{
      iterator hint=super::end();
      for(;first!=last;++first){
        hint=super::make_iterator(
          insert_ref_(*first,hint.get_node()).first);
        ++hint;
      }
    }
    BOOST_CATCH(...){
      clear_();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  multi_index_container(
    std::initializer_list<Value> list,
    const ctor_args_list& args_list=ctor_args_list(),
    const allocator_type& al=allocator_type()):
    bfm_allocator(al),
    super(args_list,bfm_allocator::member),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
    BOOST_TRY{
      typedef const Value* init_iterator;

      iterator hint=super::end();
      for(init_iterator first=list.begin(),last=list.end();
          first!=last;++first){
        hint=super::make_iterator(insert_(*first,hint.get_node()).first);
        ++hint;
      }
    }
    BOOST_CATCH(...){
      clear_();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }
#endif

  multi_index_container(
    const multi_index_container<Value,IndexSpecifierList,Allocator>& x):
    bfm_allocator(
      node_alloc_traits::select_on_container_copy_construction(
        x.bfm_allocator::member)),
    bfm_header(),
    super(x),
    node_count(0)
  {
    copy_construct_from(x);
  }

  multi_index_container(BOOST_RV_REF(multi_index_container) x):
    bfm_allocator(boost::move(x.bfm_allocator::member)),
    bfm_header(),
    super(x,detail::do_not_copy_elements_tag()),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
    BOOST_MULTI_INDEX_CHECK_INVARIANT_OF(x);
    swap_elements_(x);
  }

  multi_index_container(
    const multi_index_container<Value,IndexSpecifierList,Allocator>& x,
    const allocator_type& al):
    bfm_allocator(al),
    bfm_header(),
    super(x),
    node_count(0)
  {
    copy_construct_from(x);
  }

  multi_index_container(
    BOOST_RV_REF(multi_index_container) x,const allocator_type& al):
    bfm_allocator(al),
    bfm_header(),
    super(x,detail::do_not_copy_elements_tag()),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
    BOOST_MULTI_INDEX_CHECK_INVARIANT_OF(x);

    if(al==x.get_allocator()){
      swap_elements_(x);
    }
    else{
      multi_index_container y(x,al,detail::unequal_alloc_move_ctor_tag());
      swap_elements_(y);
    }
  }

  ~multi_index_container()
  {
    delete_all_nodes_();
  }

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  /* As per http://www.boost.org/doc/html/move/emulation_limitations.html
   * #move.emulation_limitations.assignment_operator
   */

  multi_index_container<Value,IndexSpecifierList,Allocator>& operator=(
    const multi_index_container<Value,IndexSpecifierList,Allocator>& x)
  {
    multi_index_container y(
      x,
      node_alloc_traits::propagate_on_container_copy_assignment::value?
        x.get_allocator():this->get_allocator());
    swap_(y,boost::true_type() /* swap_allocators */);
    return *this;
  }
#endif

  multi_index_container<Value,IndexSpecifierList,Allocator>& operator=(
    BOOST_COPY_ASSIGN_REF(multi_index_container) x)
  {
    multi_index_container y(
      x,
      node_alloc_traits::propagate_on_container_copy_assignment::value?
        x.get_allocator():this->get_allocator());
    swap_(y,boost::true_type() /* swap_allocators */);
    return *this;
  }

  multi_index_container<Value,IndexSpecifierList,Allocator>& operator=(
    BOOST_RV_REF(multi_index_container) x)
  {
#include <boost/multi_index/detail/define_if_constexpr_macro.hpp>

    BOOST_MULTI_INDEX_IF_CONSTEXPR(
      node_alloc_traits::propagate_on_container_move_assignment::value){
      swap_(x,boost::true_type() /* swap_allocators */);
    }
    else if(this->get_allocator()==x.get_allocator()){
      swap_(x,boost::false_type() /* swap_allocators */);
    }
    else{
      multi_index_container y(boost::move(x),this->get_allocator());
      swap_(y,boost::false_type() /* swap_allocators */);
    }
    return *this;

#include <boost/multi_index/detail/undef_if_constexpr_macro.hpp>
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  multi_index_container<Value,IndexSpecifierList,Allocator>& operator=(
    std::initializer_list<Value> list)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
    typedef const Value* init_iterator;

    multi_index_container x(*this,detail::do_not_copy_elements_tag());    
    iterator hint=x.end();
    for(init_iterator first=list.begin(),last=list.end();
        first!=last;++first){
      hint=x.make_iterator(x.insert_(*first,hint.get_node()).first);
      ++hint;
    }
    x.swap_elements_(*this);
    return*this;
  }
#endif

  allocator_type get_allocator()const BOOST_NOEXCEPT
  {
    return allocator_type(bfm_allocator::member);
  }

  /* retrieval of indices by number */

#if !defined(BOOST_NO_MEMBER_TEMPLATES)
  template<int N>
  struct nth_index
  {
    BOOST_STATIC_ASSERT(N>=0&&N<mpl::size<index_type_list>::type::value);
    typedef typename mpl::at_c<index_type_list,N>::type type;
  };

  template<int N>
  typename nth_index<N>::type& get()BOOST_NOEXCEPT
  {
    BOOST_STATIC_ASSERT(N>=0&&N<mpl::size<index_type_list>::type::value);
    return *this;
  }

  template<int N>
  const typename nth_index<N>::type& get()const BOOST_NOEXCEPT
  {
    BOOST_STATIC_ASSERT(N>=0&&N<mpl::size<index_type_list>::type::value);
    return *this;
  }
#endif

  /* retrieval of indices by tag */

#if !defined(BOOST_NO_MEMBER_TEMPLATES)
  template<typename Tag>
  struct index
  {
    typedef typename mpl::find_if<
      index_type_list,
      detail::has_tag<Tag>
    >::type                                    iter;

    BOOST_STATIC_CONSTANT(
      bool,index_found=!(is_same<iter,typename mpl::end<index_type_list>::type >::value));
    BOOST_STATIC_ASSERT(index_found);

    typedef typename mpl::deref<iter>::type    type;
  };

  template<typename Tag>
  typename index<Tag>::type& get()BOOST_NOEXCEPT
  {
    return *this;
  }

  template<typename Tag>
  const typename index<Tag>::type& get()const BOOST_NOEXCEPT
  {
    return *this;
  }
#endif

  /* projection of iterators by number */

#if !defined(BOOST_NO_MEMBER_TEMPLATES)
  template<int N>
  struct nth_index_iterator
  {
    typedef typename nth_index<N>::type::iterator type;
  };

  template<int N>
  struct nth_index_const_iterator
  {
    typedef typename nth_index<N>::type::const_iterator type;
  };

  template<int N,typename IteratorType>
  typename nth_index_iterator<N>::type project(IteratorType it)
  {
    typedef typename nth_index<N>::type index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* fails in Sun C++ 5.7 */
    BOOST_STATIC_ASSERT(
      (mpl::contains<iterator_type_list,IteratorType>::value));
#endif

    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
    BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,*this);
    return index_type::make_iterator(
      static_cast<final_node_type*>(it.get_node()));
  }

  template<int N,typename IteratorType>
  typename nth_index_const_iterator<N>::type project(IteratorType it)const
  {
    typedef typename nth_index<N>::type index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* fails in Sun C++ 5.7 */
    BOOST_STATIC_ASSERT((
      mpl::contains<iterator_type_list,IteratorType>::value||
      mpl::contains<const_iterator_type_list,IteratorType>::value));
#endif

    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
    BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,*this);
    return index_type::make_iterator(
      static_cast<final_node_type*>(it.get_node()));
  }
#endif

  /* projection of iterators by tag */

#if !defined(BOOST_NO_MEMBER_TEMPLATES)
  template<typename Tag>
  struct index_iterator
  {
    typedef typename index<Tag>::type::iterator type;
  };

  template<typename Tag>
  struct index_const_iterator
  {
    typedef typename index<Tag>::type::const_iterator type;
  };

  template<typename Tag,typename IteratorType>
  typename index_iterator<Tag>::type project(IteratorType it)
  {
    typedef typename index<Tag>::type index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* fails in Sun C++ 5.7 */
    BOOST_STATIC_ASSERT(
      (mpl::contains<iterator_type_list,IteratorType>::value));
#endif

    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
    BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,*this);
    return index_type::make_iterator(
      static_cast<final_node_type*>(it.get_node()));
  }

  template<typename Tag,typename IteratorType>
  typename index_const_iterator<Tag>::type project(IteratorType it)const
  {
    typedef typename index<Tag>::type index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* fails in Sun C++ 5.7 */
    BOOST_STATIC_ASSERT((
      mpl::contains<iterator_type_list,IteratorType>::value||
      mpl::contains<const_iterator_type_list,IteratorType>::value));
#endif

    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
    BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,*this);
    return index_type::make_iterator(
      static_cast<final_node_type*>(it.get_node()));
  }
#endif

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  typedef typename super::final_node_handle_type final_node_handle_type;
  typedef typename super::copy_map_type          copy_map_type;

  multi_index_container(
    multi_index_container<Value,IndexSpecifierList,Allocator>& x,
    const allocator_type& al,
    detail::unequal_alloc_move_ctor_tag):
    bfm_allocator(al),
    bfm_header(),
    super(x),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT_OF(x);
    BOOST_TRY{
      copy_map_type map(bfm_allocator::member,x.size(),x.header(),header());
      for(const_iterator it=x.begin(),it_end=x.end();it!=it_end;++it){
        map.move_clone(it.get_node());
      }
      super::copy_(x,map);
      map.release();
      node_count=x.size();
      x.clear();
    }
    BOOST_CATCH(...){
      x.clear();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END

    /* Not until this point are the indices required to be consistent,
     * hence the position of the invariant checker.
     */

    BOOST_MULTI_INDEX_CHECK_INVARIANT;
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  multi_index_container(
    const multi_index_container<Value,IndexSpecifierList,Allocator>& x,
    detail::do_not_copy_elements_tag):
    bfm_allocator(x.bfm_allocator::member),
    bfm_header(),
    super(x,detail::do_not_copy_elements_tag()),
    node_count(0)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;
  }
#endif

  void copy_construct_from(
    const multi_index_container<Value,IndexSpecifierList,Allocator>& x)
  {
    copy_map_type map(bfm_allocator::member,x.size(),x.header(),header());
    for(const_iterator it=x.begin(),it_end=x.end();it!=it_end;++it){
      map.copy_clone(it.get_node());
    }
    super::copy_(x,map);
    map.release();
    node_count=x.size();

    /* Not until this point are the indices required to be consistent,
     * hence the position of the invariant checker.
     */

    BOOST_MULTI_INDEX_CHECK_INVARIANT;
  }

  final_node_type* header()const
  {
    return &*bfm_header::member;
  }

  final_node_type* allocate_node()
  {
    return &*node_alloc_traits::allocate(bfm_allocator::member,1);
  }

  void deallocate_node(final_node_type* x)
  {
    node_alloc_traits::deallocate(
      bfm_allocator::member,static_cast<node_pointer>(x),1);
  }

  void construct_value(final_node_type* x,const Value& v)
  {
    node_alloc_traits::construct(
      bfm_allocator::member,boost::addressof(x->value()),v);
  }

  void construct_value(final_node_type* x,BOOST_RV_REF(Value) v)
  {
    node_alloc_traits::construct(
      bfm_allocator::member,boost::addressof(x->value()),boost::move(v));
  }

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(
    void,construct_value,vartempl_construct_value_impl,final_node_type*,x)

  void destroy_value(final_node_type* x)
  {
    node_alloc_traits::destroy(
      bfm_allocator::member,boost::addressof(x->value()));
  }

  bool empty_()const
  {
    return node_count==0;
  }

  size_type size_()const
  {
    return node_count;
  }

  size_type max_size_()const
  {
    return static_cast<size_type>(-1);
  }

  template<typename Variant>
  std::pair<final_node_type*,bool> insert_(const Value& v,Variant variant)
  {
    final_node_type* x=0;
    final_node_type* res=super::insert_(v,x,variant);
    if(res==x){
      ++node_count;
      return std::pair<final_node_type*,bool>(res,true);
    }
    else{
      return std::pair<final_node_type*,bool>(res,false);
    }
  }

  std::pair<final_node_type*,bool> insert_(const Value& v)
  {
    return insert_(v,detail::lvalue_tag());
  }

  std::pair<final_node_type*,bool> insert_rv_(const Value& v)
  {
    return insert_(v,detail::rvalue_tag());
  }

  template<typename T>
  std::pair<final_node_type*,bool> insert_ref_(T& t)
  {
    final_node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,t);
      BOOST_TRY{
        final_node_type* res=super::insert_(
          x->value(),x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<final_node_type*,bool>(res,true);
        }
        else{
          delete_node_(x);
          return std::pair<final_node_type*,bool>(res,false);
        }
      }
      BOOST_CATCH(...){
        destroy_value(x);
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }
    BOOST_CATCH(...){
      deallocate_node(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  std::pair<final_node_type*,bool> insert_ref_(const value_type& x)
  {
    return insert_(x);
  }

  std::pair<final_node_type*,bool> insert_ref_(value_type& x)
  {
    return insert_(x);
  }

  std::pair<final_node_type*,bool> insert_nh_(final_node_handle_type& nh)
  {
    if(!nh)return std::pair<final_node_type*,bool>(header(),false);
    else{
      final_node_type* x=nh.node;
      final_node_type* res=super::insert_(
        x->value(),x,detail::emplaced_tag());
      if(res==x){
        nh.release_node();
        ++node_count;
        return std::pair<final_node_type*,bool>(res,true);
      }
      else return std::pair<final_node_type*,bool>(res,false);
    }
  }

  template<typename Index>
  std::pair<final_node_type*,bool> transfer_(Index& x,final_node_type* n)
  {
    final_node_type* res=super::insert_(n->value(),n,&super::final(x));
    if(res==n){
      ++node_count;
      return std::pair<final_node_type*,bool>(res,true);
    }
    else{
      return std::pair<final_node_type*,bool>(res,false);
    }
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<final_node_type*,bool> emplace_(
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    final_node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
      BOOST_TRY{
        final_node_type* res=super::insert_(
          x->value(),x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<final_node_type*,bool>(res,true);
        }
        else{
          delete_node_(x);
          return std::pair<final_node_type*,bool>(res,false);
        }
      }
      BOOST_CATCH(...){
        destroy_value(x);
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }
    BOOST_CATCH(...){
      deallocate_node(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  template<typename Variant>
  std::pair<final_node_type*,bool> insert_(
    const Value& v,final_node_type* position,Variant variant)
  {
    final_node_type* x=0;
    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x){
      ++node_count;
      return std::pair<final_node_type*,bool>(res,true);
    }
    else{
      return std::pair<final_node_type*,bool>(res,false);
    }
  }

  std::pair<final_node_type*,bool> insert_(
    const Value& v,final_node_type* position)
  {
    return insert_(v,position,detail::lvalue_tag());
  }

  std::pair<final_node_type*,bool> insert_rv_(
    const Value& v,final_node_type* position)
  {
    return insert_(v,position,detail::rvalue_tag());
  }

  template<typename T>
  std::pair<final_node_type*,bool> insert_ref_(
    T& t,final_node_type* position)
  {
    final_node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,t);
      BOOST_TRY{
        final_node_type* res=super::insert_(
          x->value(),position,x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<final_node_type*,bool>(res,true);
        }
        else{
          delete_node_(x);
          return std::pair<final_node_type*,bool>(res,false);
        }
      }
      BOOST_CATCH(...){
        destroy_value(x);
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }
    BOOST_CATCH(...){
      deallocate_node(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  std::pair<final_node_type*,bool> insert_ref_(
    const value_type& x,final_node_type* position)
  {
    return insert_(x,position);
  }

  std::pair<final_node_type*,bool> insert_ref_(
    value_type& x,final_node_type* position)
  {
    return insert_(x,position);
  }

  std::pair<final_node_type*,bool> insert_nh_(
    final_node_handle_type& nh,final_node_type* position)
  {
    if(!nh)return std::pair<final_node_type*,bool>(header(),false);
    else{
      final_node_type* x=nh.node;
      final_node_type* res=super::insert_(
        x->value(),position,x,detail::emplaced_tag());
      if(res==x){
        nh.release_node();
        ++node_count;
        return std::pair<final_node_type*,bool>(res,true);
      }
      else return std::pair<final_node_type*,bool>(res,false);
    }
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<final_node_type*,bool> emplace_hint_(
    final_node_type* position,
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    final_node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
      BOOST_TRY{
        final_node_type* res=super::insert_(
          x->value(),position,x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<final_node_type*,bool>(res,true);
        }
        else{
          delete_node_(x);
          return std::pair<final_node_type*,bool>(res,false);
        }
      }
      BOOST_CATCH(...){
        destroy_value(x);
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }
    BOOST_CATCH(...){
      deallocate_node(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  final_node_handle_type extract_(final_node_type* x)
  {
    --node_count;
    super::extract_(x,detail::invalidate_iterators());
    return final_node_handle_type(x,get_allocator());
  }

  template<typename Dst>
  void extract_for_transfer_(final_node_type* x,Dst dst)
  {
    --node_count;
    super::extract_(x,dst);
  }

  void erase_(final_node_type* x)
  {
    --node_count;
    super::extract_(x,detail::invalidate_iterators());
    delete_node_(x);
  }

  void delete_node_(final_node_type* x)
  {
    destroy_value(x);
    deallocate_node(x);
  }

  void delete_all_nodes_()
  {
    super::delete_all_nodes_();
  }

  void clear_()
  {
    delete_all_nodes_();
    super::clear_();
    node_count=0;
  }

  template<typename Index>
  void transfer_range_(
    Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    while(first!=last){
      transfer_(x,static_cast<final_node_type*>((first++).get_node()));
    }
  }

  void swap_(multi_index_container<Value,IndexSpecifierList,Allocator>& x)
  {
    swap_(
      x,
      boost::integral_constant<
        bool,node_alloc_traits::propagate_on_container_swap::value>());
  }

  void swap_(
    multi_index_container<Value,IndexSpecifierList,Allocator>& x,
    boost::true_type swap_allocators)
  {
    detail::adl_swap(bfm_allocator::member,x.bfm_allocator::member);
    std::swap(bfm_header::member,x.bfm_header::member);
    super::swap_(x,swap_allocators);
    std::swap(node_count,x.node_count);
  }

  void swap_(
    multi_index_container<Value,IndexSpecifierList,Allocator>& x,
    boost::false_type swap_allocators)
  {
    std::swap(bfm_header::member,x.bfm_header::member);
    super::swap_(x,swap_allocators);
    std::swap(node_count,x.node_count);
  }

  void swap_elements_(
    multi_index_container<Value,IndexSpecifierList,Allocator>& x)
  {
    std::swap(bfm_header::member,x.bfm_header::member);
    super::swap_elements_(x);
    std::swap(node_count,x.node_count);
  }

  bool replace_(const Value& k,final_node_type* x)
  {
    return super::replace_(k,x,detail::lvalue_tag());
  }

  bool replace_rv_(const Value& k,final_node_type* x)
  {
    return super::replace_(k,x,detail::rvalue_tag());
  }

  template<typename Modifier>
  bool modify_(Modifier& mod,final_node_type* x)
  {
    BOOST_TRY{
      mod(const_cast<value_type&>(x->value()));
    }
    BOOST_CATCH(...){
      this->erase_(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END

    BOOST_TRY{
      if(!super::modify_(x)){
        delete_node_(x);
        --node_count;
        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      delete_node_(x);
      --node_count;
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  template<typename Modifier,typename Rollback>
  bool modify_(Modifier& mod,Rollback& back_,final_node_type* x)
  {
    BOOST_TRY{
      mod(const_cast<value_type&>(x->value()));
    }
    BOOST_CATCH(...){
      this->erase_(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END

    bool b;
    BOOST_TRY{
      b=super::modify_rollback_(x);
    }
    BOOST_CATCH(...){
      BOOST_TRY{
        back_(const_cast<value_type&>(x->value()));
        if(!super::check_rollback_(x))this->erase_(x);
        BOOST_RETHROW;
      }
      BOOST_CATCH(...){
        this->erase_(x);
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }
    BOOST_CATCH_END

    BOOST_TRY{
      if(!b){
        back_(const_cast<value_type&>(x->value()));
        if(!super::check_rollback_(x))this->erase_(x);
        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      this->erase_(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* serialization */

  friend class boost::serialization::access;

  BOOST_SERIALIZATION_SPLIT_MEMBER()

  typedef typename super::index_saver_type        index_saver_type;
  typedef typename super::index_loader_type       index_loader_type;

  template<class Archive>
  void save(Archive& ar,const unsigned int version)const
  {
    const serialization::collection_size_type       s(size_());
    const detail::serialization_version<value_type> value_version;
    ar<<serialization::make_nvp("count",s);
    ar<<serialization::make_nvp("value_version",value_version);

    index_saver_type sm(bfm_allocator::member,s);

    for(iterator it=super::begin(),it_end=super::end();it!=it_end;++it){
      serialization::save_construct_data_adl(
        ar,boost::addressof(*it),value_version);
      ar<<serialization::make_nvp("item",*it);
      sm.add(it.get_node(),ar,version);
    }
    sm.add_track(header(),ar,version);

    super::save_(ar,version,sm);
  }

  template<class Archive>
  void load(Archive& ar,const unsigned int version)
  {
    BOOST_MULTI_INDEX_CHECK_INVARIANT;

    clear_(); 
    serialization::collection_size_type       s;
    detail::serialization_version<value_type> value_version;
    if(version<1){
      std::size_t sz;
      ar>>serialization::make_nvp("count",sz);
      s=static_cast<serialization::collection_size_type>(sz);
    }
    else{
      ar>>serialization::make_nvp("count",s);
    }
    if(version<2){
      value_version=0;
    }
    else{
      ar>>serialization::make_nvp("value_version",value_version);
    }

    index_loader_type lm(bfm_allocator::member,s);

    for(std::size_t n=0;n<s;++n){
      detail::archive_constructed<Value> value("item",ar,value_version);
      std::pair<final_node_type*,bool> p=insert_rv_(
        value.get(),super::end().get_node());
      if(!p.second)throw_exception(
        archive::archive_exception(
          archive::archive_exception::other_exception));
      ar.reset_object_address(
        boost::addressof(p.first->value()),boost::addressof(value.get()));
      lm.add(p.first,ar,version);
    }
    lm.add_track(header(),ar,version);

    super::load_(ar,version,lm);
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const
  {
    return super::invariant_();
  }

  void check_invariant_()const
  {
    BOOST_MULTI_INDEX_INVARIANT_ASSERT(invariant_());
  }
#endif

private:
  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  void vartempl_construct_value_impl(
    final_node_type* x,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    node_alloc_traits::construct(
      bfm_allocator::member,boost::addressof(x->value()),
      BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

  size_type node_count;

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif
};

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1500))
#pragma warning(pop) /* C4522 */
#endif

/* retrieval of indices by number */

template<typename MultiIndexContainer,int N>
struct nth_index
{
  BOOST_STATIC_CONSTANT(
    int,
    M=mpl::size<typename MultiIndexContainer::index_type_list>::type::value);
  BOOST_STATIC_ASSERT(N>=0&&N<M);
  typedef typename mpl::at_c<
    typename MultiIndexContainer::index_type_list,N>::type type;
};

template<int N,typename Value,typename IndexSpecifierList,typename Allocator>
typename nth_index<
  multi_index_container<Value,IndexSpecifierList,Allocator>,N>::type&
get(
  multi_index_container<Value,IndexSpecifierList,Allocator>& m)BOOST_NOEXCEPT
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>    multi_index_type;
  typedef typename nth_index<
    multi_index_container<
      Value,IndexSpecifierList,Allocator>,
    N
  >::type                                  index_type;

  BOOST_STATIC_ASSERT(N>=0&&
    N<
    mpl::size<
      BOOST_DEDUCED_TYPENAME multi_index_type::index_type_list
    >::type::value);

  return detail::converter<multi_index_type,index_type>::index(m);
}

template<int N,typename Value,typename IndexSpecifierList,typename Allocator>
const typename nth_index<
  multi_index_container<Value,IndexSpecifierList,Allocator>,N>::type&
get(
  const multi_index_container<Value,IndexSpecifierList,Allocator>& m
)BOOST_NOEXCEPT
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>    multi_index_type;
  typedef typename nth_index<
    multi_index_container<
      Value,IndexSpecifierList,Allocator>,
    N
  >::type                                  index_type;

  BOOST_STATIC_ASSERT(N>=0&&
    N<
    mpl::size<
      BOOST_DEDUCED_TYPENAME multi_index_type::index_type_list
    >::type::value);

  return detail::converter<multi_index_type,index_type>::index(m);
}

/* retrieval of indices by tag */

template<typename MultiIndexContainer,typename Tag>
struct index
{
  typedef typename MultiIndexContainer::index_type_list index_type_list;

  typedef typename mpl::find_if<
    index_type_list,
    detail::has_tag<Tag>
  >::type                                      iter;

  BOOST_STATIC_CONSTANT(
    bool,index_found=!(is_same<iter,typename mpl::end<index_type_list>::type >::value));
  BOOST_STATIC_ASSERT(index_found);

  typedef typename mpl::deref<iter>::type       type;
};

template<
  typename Tag,typename Value,typename IndexSpecifierList,typename Allocator
>
typename ::boost::multi_index::index<
  multi_index_container<Value,IndexSpecifierList,Allocator>,Tag>::type&
get(
  multi_index_container<Value,IndexSpecifierList,Allocator>& m)BOOST_NOEXCEPT
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>         multi_index_type;
  typedef typename ::boost::multi_index::index<
    multi_index_container<
      Value,IndexSpecifierList,Allocator>,
    Tag
  >::type                                       index_type;

  return detail::converter<multi_index_type,index_type>::index(m);
}

template<
  typename Tag,typename Value,typename IndexSpecifierList,typename Allocator
>
const typename ::boost::multi_index::index<
  multi_index_container<Value,IndexSpecifierList,Allocator>,Tag>::type&
get(
  const multi_index_container<Value,IndexSpecifierList,Allocator>& m
)BOOST_NOEXCEPT
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>         multi_index_type;
  typedef typename ::boost::multi_index::index<
    multi_index_container<
      Value,IndexSpecifierList,Allocator>,
    Tag
  >::type                                       index_type;

  return detail::converter<multi_index_type,index_type>::index(m);
}

/* projection of iterators by number */

template<typename MultiIndexContainer,int N>
struct nth_index_iterator
{
  typedef typename nth_index<MultiIndexContainer,N>::type::iterator type;
};

template<typename MultiIndexContainer,int N>
struct nth_index_const_iterator
{
  typedef typename nth_index<MultiIndexContainer,N>::type::const_iterator type;
};

template<
  int N,typename IteratorType,
  typename Value,typename IndexSpecifierList,typename Allocator>
typename nth_index_iterator<
  multi_index_container<Value,IndexSpecifierList,Allocator>,N>::type
project(
  multi_index_container<Value,IndexSpecifierList,Allocator>& m,
  IteratorType it)
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>                multi_index_type;
  typedef typename nth_index<multi_index_type,N>::type index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* Sun C++ 5.7 fails */
  BOOST_STATIC_ASSERT((
    mpl::contains<
      BOOST_DEDUCED_TYPENAME multi_index_type::iterator_type_list,
      IteratorType>::value));
#endif

  BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
  BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,m);
  return detail::converter<multi_index_type,index_type>::iterator(
    m,static_cast<typename multi_index_type::final_node_type*>(it.get_node()));
}

template<
  int N,typename IteratorType,
  typename Value,typename IndexSpecifierList,typename Allocator>
typename nth_index_const_iterator<
  multi_index_container<Value,IndexSpecifierList,Allocator>,N>::type
project(
  const multi_index_container<Value,IndexSpecifierList,Allocator>& m,
  IteratorType it)
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>                multi_index_type;
  typedef typename nth_index<multi_index_type,N>::type index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* Sun C++ 5.7 fails */
  BOOST_STATIC_ASSERT((
    mpl::contains<
      BOOST_DEDUCED_TYPENAME multi_index_type::iterator_type_list,
      IteratorType>::value||
    mpl::contains<
      BOOST_DEDUCED_TYPENAME multi_index_type::const_iterator_type_list,
      IteratorType>::value));
#endif

  BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
  BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,m);
  return detail::converter<multi_index_type,index_type>::const_iterator(
    m,static_cast<typename multi_index_type::final_node_type*>(it.get_node()));
}

/* projection of iterators by tag */

template<typename MultiIndexContainer,typename Tag>
struct index_iterator
{
  typedef typename ::boost::multi_index::index<
    MultiIndexContainer,Tag>::type::iterator    type;
};

template<typename MultiIndexContainer,typename Tag>
struct index_const_iterator
{
  typedef typename ::boost::multi_index::index<
    MultiIndexContainer,Tag>::type::const_iterator type;
};

template<
  typename Tag,typename IteratorType,
  typename Value,typename IndexSpecifierList,typename Allocator>
typename index_iterator<
  multi_index_container<Value,IndexSpecifierList,Allocator>,Tag>::type
project(
  multi_index_container<Value,IndexSpecifierList,Allocator>& m,
  IteratorType it)
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>         multi_index_type;
  typedef typename ::boost::multi_index::index<
    multi_index_type,Tag>::type                 index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* Sun C++ 5.7 fails */
  BOOST_STATIC_ASSERT((
    mpl::contains<
      BOOST_DEDUCED_TYPENAME multi_index_type::iterator_type_list,
      IteratorType>::value));
#endif

  BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
  BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,m);
  return detail::converter<multi_index_type,index_type>::iterator(
    m,static_cast<typename multi_index_type::final_node_type*>(it.get_node()));
}

template<
  typename Tag,typename IteratorType,
  typename Value,typename IndexSpecifierList,typename Allocator>
typename index_const_iterator<
  multi_index_container<Value,IndexSpecifierList,Allocator>,Tag>::type
project(
  const multi_index_container<Value,IndexSpecifierList,Allocator>& m,
  IteratorType it)
{
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>         multi_index_type;
  typedef typename ::boost::multi_index::index<
    multi_index_type,Tag>::type                 index_type;

#if !defined(__SUNPRO_CC)||!(__SUNPRO_CC<0x580) /* Sun C++ 5.7 fails */
  BOOST_STATIC_ASSERT((
    mpl::contains<
      BOOST_DEDUCED_TYPENAME multi_index_type::iterator_type_list,
      IteratorType>::value||
    mpl::contains<
      BOOST_DEDUCED_TYPENAME multi_index_type::const_iterator_type_list,
      IteratorType>::value));
#endif

  BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(it);
  BOOST_MULTI_INDEX_CHECK_BELONGS_IN_SOME_INDEX(it,m);
  return detail::converter<multi_index_type,index_type>::const_iterator(
    m,static_cast<typename multi_index_type::final_node_type*>(it.get_node()));
}

/* Comparison. Simple forward to first index. */

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator==(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y)
{
  return get<0>(x)==get<0>(y);
}

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator<(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y)
{
  return get<0>(x)<get<0>(y);
}

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator!=(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y)
{
  return get<0>(x)!=get<0>(y);
}

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator>(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y)
{
  return get<0>(x)>get<0>(y);
}

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator>=(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y)
{
  return get<0>(x)>=get<0>(y);
}

template<
  typename Value1,typename IndexSpecifierList1,typename Allocator1,
  typename Value2,typename IndexSpecifierList2,typename Allocator2
>
bool operator<=(
  const multi_index_container<Value1,IndexSpecifierList1,Allocator1>& x,
  const multi_index_container<Value2,IndexSpecifierList2,Allocator2>& y)
{
  return get<0>(x)<=get<0>(y);
}

/*  specialized algorithms */

template<typename Value,typename IndexSpecifierList,typename Allocator>
void swap(
  multi_index_container<Value,IndexSpecifierList,Allocator>& x,
  multi_index_container<Value,IndexSpecifierList,Allocator>& y)
{
  x.swap(y);
}

} /* namespace multi_index */

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
/* class version = 1 : we now serialize the size through
 * boost::serialization::collection_size_type.
 * class version = 2 : proper use of {save|load}_construct_data.
 */

namespace serialization {
template<typename Value,typename IndexSpecifierList,typename Allocator>
struct version<
  boost::multi_index_container<Value,IndexSpecifierList,Allocator>
>
{
  BOOST_STATIC_CONSTANT(int,value=2);
};
} /* namespace serialization */
#endif

/* Associated global functions are promoted to namespace boost, except
 * comparison operators and swap, which are meant to be Koenig looked-up.
 */

using multi_index::get;
using multi_index::project;

} /* namespace boost */

#undef BOOST_MULTI_INDEX_CHECK_INVARIANT
#undef BOOST_MULTI_INDEX_CHECK_INVARIANT_OF

#endif

/* multi_index_container.hpp
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
*/