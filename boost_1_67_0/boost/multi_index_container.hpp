/* Multiply indexed container.
 *
 * Copyright 2003-2020 Joaquin M Lopez Munoz.
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
#include <boost/detail/no_exceptions_support.hpp>
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
    typename super::node_type
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

  typedef typename super::node_type node_type;

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
#if !defined(BOOST_NO_CXX17_IF_CONSTEXPR)
#define BOOST_MULTI_INDEX_IF_CONSTEXPR if constexpr
#else
#define BOOST_MULTI_INDEX_IF_CONSTEXPR if
#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4127) /* conditional expression is constant */
#endif
#endif

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

#undef BOOST_MULTI_INDEX_IF_CONSTEXPR 
#if defined(BOOST_NO_CXX17_IF_CONSTEXPR)&&defined(BOOST_MSVC)
#pragma warning(pop) /* C4127 */
#endif
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
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(
      it,static_cast<typename IteratorType::container_type&>(*this));

    return index_type::make_iterator(static_cast<node_type*>(it.get_node()));
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
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(
      it,static_cast<const typename IteratorType::container_type&>(*this));
    return index_type::make_iterator(static_cast<node_type*>(it.get_node()));
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
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(
      it,static_cast<typename IteratorType::container_type&>(*this));
    return index_type::make_iterator(static_cast<node_type*>(it.get_node()));
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
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(
      it,static_cast<const typename IteratorType::container_type&>(*this));
    return index_type::make_iterator(static_cast<node_type*>(it.get_node()));
  }
#endif

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  typedef typename super::copy_map_type copy_map_type;

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

  node_type* header()const
  {
    return &*bfm_header::member;
  }

  node_type* allocate_node()
  {
    return &*node_alloc_traits::allocate(bfm_allocator::member,1);
  }

  void deallocate_node(node_type* x)
  {
    node_alloc_traits::deallocate(
      bfm_allocator::member,static_cast<node_pointer>(x),1);
  }

  void construct_value(node_type* x,const Value& v)
  {
    node_alloc_traits::construct(
      bfm_allocator::member,boost::addressof(x->value()),v);
  }

  void construct_value(node_type* x,BOOST_RV_REF(Value) v)
  {
    node_alloc_traits::construct(
      bfm_allocator::member,boost::addressof(x->value()),boost::move(v));
  }

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(
    void,construct_value,vartempl_construct_value_impl,node_type*,x)

  void destroy_value(node_type* x)
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
  std::pair<node_type*,bool> insert_(const Value& v,Variant variant)
  {
    node_type* x=0;
    node_type* res=super::insert_(v,x,variant);
    if(res==x){
      ++node_count;
      return std::pair<node_type*,bool>(res,true);
    }
    else{
      return std::pair<node_type*,bool>(res,false);
    }
  }

  std::pair<node_type*,bool> insert_(const Value& v)
  {
    return insert_(v,detail::lvalue_tag());
  }

  std::pair<node_type*,bool> insert_rv_(const Value& v)
  {
    return insert_(v,detail::rvalue_tag());
  }

  template<typename T>
  std::pair<node_type*,bool> insert_ref_(T& t)
  {
    node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,t);
      BOOST_TRY{
        node_type* res=super::insert_(x->value(),x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<node_type*,bool>(res,true);
        }
        else{
          destroy_value(x);
          deallocate_node(x);
          return std::pair<node_type*,bool>(res,false);
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

  std::pair<node_type*,bool> insert_ref_(const value_type& x)
  {
    return insert_(x);
  }

  std::pair<node_type*,bool> insert_ref_(value_type& x)
  {
    return insert_(x);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<node_type*,bool> emplace_(
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
      BOOST_TRY{
        node_type* res=super::insert_(x->value(),x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<node_type*,bool>(res,true);
        }
        else{
          destroy_value(x);
          deallocate_node(x);
          return std::pair<node_type*,bool>(res,false);
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
  std::pair<node_type*,bool> insert_(
    const Value& v,node_type* position,Variant variant)
  {
    node_type* x=0;
    node_type* res=super::insert_(v,position,x,variant);
    if(res==x){
      ++node_count;
      return std::pair<node_type*,bool>(res,true);
    }
    else{
      return std::pair<node_type*,bool>(res,false);
    }
  }

  std::pair<node_type*,bool> insert_(const Value& v,node_type* position)
  {
    return insert_(v,position,detail::lvalue_tag());
  }

  std::pair<node_type*,bool> insert_rv_(const Value& v,node_type* position)
  {
    return insert_(v,position,detail::rvalue_tag());
  }

  template<typename T>
  std::pair<node_type*,bool> insert_ref_(
    T& t,node_type* position)
  {
    node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,t);
      BOOST_TRY{
        node_type* res=super::insert_(
          x->value(),position,x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<node_type*,bool>(res,true);
        }
        else{
          destroy_value(x);
          deallocate_node(x);
          return std::pair<node_type*,bool>(res,false);
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

  std::pair<node_type*,bool> insert_ref_(
    const value_type& x,node_type* position)
  {
    return insert_(x,position);
  }

  std::pair<node_type*,bool> insert_ref_(
    value_type& x,node_type* position)
  {
    return insert_(x,position);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<node_type*,bool> emplace_hint_(
    node_type* position,
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    node_type* x=allocate_node();
    BOOST_TRY{
      construct_value(x,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
      BOOST_TRY{
        node_type* res=super::insert_(
          x->value(),position,x,detail::emplaced_tag());
        if(res==x){
          ++node_count;
          return std::pair<node_type*,bool>(res,true);
        }
        else{
          destroy_value(x);
          deallocate_node(x);
          return std::pair<node_type*,bool>(res,false);
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

  void erase_(node_type* x)
  {
    --node_count;
    super::erase_(x);
    deallocate_node(x);
  }

  void delete_node_(node_type* x)
  {
    super::delete_node_(x);
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

  bool replace_(const Value& k,node_type* x)
  {
    return super::replace_(k,x,detail::lvalue_tag());
  }

  bool replace_rv_(const Value& k,node_type* x)
  {
    return super::replace_(k,x,detail::rvalue_tag());
  }

  template<typename Modifier>
  bool modify_(Modifier& mod,node_type* x)
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
        deallocate_node(x);
        --node_count;
        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      deallocate_node(x);
      --node_count;
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  template<typename Modifier,typename Rollback>
  bool modify_(Modifier& mod,Rollback& back_,node_type* x)
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
      std::pair<node_type*,bool> p=insert_rv_(
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
    node_type* x,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
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

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef detail::converter<
    multi_index_type,
    BOOST_DEDUCED_TYPENAME IteratorType::container_type> converter;
  BOOST_MULTI_INDEX_CHECK_IS_OWNER(it,converter::index(m));
#endif

  return detail::converter<multi_index_type,index_type>::iterator(
    m,static_cast<typename multi_index_type::node_type*>(it.get_node()));
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

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef detail::converter<
    multi_index_type,
    BOOST_DEDUCED_TYPENAME IteratorType::container_type> converter;
  BOOST_MULTI_INDEX_CHECK_IS_OWNER(it,converter::index(m));
#endif

  return detail::converter<multi_index_type,index_type>::const_iterator(
    m,static_cast<typename multi_index_type::node_type*>(it.get_node()));
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

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef detail::converter<
    multi_index_type,
    BOOST_DEDUCED_TYPENAME IteratorType::container_type> converter;
  BOOST_MULTI_INDEX_CHECK_IS_OWNER(it,converter::index(m));
#endif

  return detail::converter<multi_index_type,index_type>::iterator(
    m,static_cast<typename multi_index_type::node_type*>(it.get_node()));
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

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef detail::converter<
    multi_index_type,
    BOOST_DEDUCED_TYPENAME IteratorType::container_type> converter;
  BOOST_MULTI_INDEX_CHECK_IS_OWNER(it,converter::index(m));
#endif

  return detail::converter<multi_index_type,index_type>::const_iterator(
    m,static_cast<typename multi_index_type::node_type*>(it.get_node()));
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
NOPgKzm+fNkpGezsb5y40Qpy+x0ymPZLlEtC8EqBSAdD6R1K0MPDqtmzMq1qZmbdTv0bzSN2LdRHZ1uzl38owuLu/sI86UQ6FutbF8OHSbliRGuhaoFTXK5YGjNWCQZI80Pl3+PEGSRDiXfyzVhThJ/0/69tbO09muKng4ZU4GRzYL2jTQVs/2y28Pf22SQwZrEfujHvxZzmer3CmdJMuQm14UqfwANt+eoX/Vdg7S+XSnLwNNZU6mahlGMOpn3+/crQFN3mibECKSqTU/qsMqtDHEB45bW44XnOASeSqZ6j4WNFYfOkidPs9dhLGllWpLsF2/AYn/LSAEISGlYJJHQMfoIEeeSdseDKzO6yyvL+9GrNR6Fb4IkpKZ88pN3cTykiFG16Vj8OxlZgulYAyM37w2974F4zapg/J73KHhUjOWtlyfOgcGC+KmrxI+1XKdS+AelcoVRbpFsvSObQgVz0ItA5Hg2GIV1dO6WkAe14cy9wX37xJxI45pcvhHfQ2zwEBPQEnLyHWtxyZmiKBLIGkSWRzUVZb4yWBnfP4fnNiXO6p2xaI5cM41DPXTCsNIn/GXNwc/y4GRyDMceAL3iydIA2XOHL4y3d8Wkk3mCp1JD1vjOLcp7fun4Y/bYVeV/eh0vlEcDktX39wuFJdIBzaLpcQbmcVrTp1iega6c79eFrSWeoWF6cRHoikGtjt9tiPciWlaKGFifpN9yW1Hw6H9AP2Lg5soKiIRTff+kACndvHHK0L4pDuE/2hGGrRgfiRpCeuSiSiQjAxJChifFTjG6MumU0VyGbwBSegtS8mozhnpRYhgmDlsRDXf3DMtP2Gu4XhalRo3r25lHTajfmc24TLXDG5dhoiVGgsFHdeW4s3YMP+xNyM68XGYF3PJCrGCv3LM+nS9BCJfWCx1ABOWdRkVoYo7kT2Wa1RKQJ45GSmIgwkaArvOTZKYeFjKPlOJH4Js794pNhMa4UPGq2QRRxr2ImV6ihFEjosiBTrzMAesYMhlPKaeug+mgDwxwGH077tby5SM2EJECqtyTGlDol4xVjP2rqRgLZeifuq3lW0GBDFbtU1HqO6Di4SO82o5cvW4EaklNPv9dyO91Aw1v0/ODedNb+pHCkkMq/seeQdzwxuytdGYqVr+IjF7UqrjziZqkdMcxgPVw9FmHJKom8hqWYyvZ/dEe5qUWuoSY3Vj0AoD+ku3NMEkZ3zDvThOegGDe8gk6W9wuuwUx4EJLKIoizrtCPeBbHyCqr8gdujX5HP9SUD3dhp6wcyOGUFdqLCuqUGIboQAXamBs05g0u/iZVvMXFqsRCwtATSKqQxQwmBiiYoUWX7Jc6Oj3X281uM9PyedVQt3XEyJVmdvShlkEx+QYiiSDLYqmsueFMwxppbhJ4hxxWxhH9dOFL4iZmxYBBO8q798o1PYFrJ43qBC1/5Qoc4JRpre42WesmnUCdjXV9/Mq4+W/zi/lAAkmFuqIeylM+t8K3qyd/Le0kXn3pdaI6y4lCnWBwP6wnbWSiKNFooqg0lkj0ZaGmjs/ChSOPJNpoelcY0yF0Xye9n/3iy84+9usByfAz6bdbn6kyo1RyK2+EDZxMxPbFHotlIfOJLHtqnHO5pYUz1/v7J6kGbqyu6fJ+qlkcJflvOlIfVxCXvPPS9id/hT+d56C42CBbmgc96rpr3nhkj8ZV1XI0n6tBfVL9Pg867dKNHe+tvpz7tKU6CQXzSWh0M/RuI/KwyoF14kv7v4MISTmr8tMlwWiTbWD+N1pnguzF8ki0+dA05h+ph7yB2f0Ftesa7Cb6Y7fKJJrsOcQNq6b+QbkYO2D0iO5b1Sn+0ZiNV+vkpH3kUiarAFBhqUSfCkX+VVjguTOxlNZT85RE08nOY3OUl/hiYGPQZsce5nc4dAkLnUj1C//gi/iMl8qNtUWdrgdtL6Eg38Y+cnC2AqOCKzXvjFF1+8YSUBKzkm8/IkziiVfH+/acPpW9FtY6aZiWTewGOWbmiRExgrRYCaJxiYzMx7z7qxa7ugATzATfWLe+clhh/54mK6ZkWlh5dX7B0I2T7VViTNg4fAc/jwXohaHFJPQ5TpjsMCECfdoW9T8cFiKhBtVmGTPRxZdXyz3hT1vyHoevnNBeg7t6ZhJypJAU9mR/Yd0c5TLo2tSv1oFniMfBw02N2DcpUaYBIodkr+efBpuqjoBKbbVSvlacxY0ZOd2L326JDKKBY0iMQ51s94KDm/fXLq055/AhDYnnOR0vSGkpq/jBwjEEmcCfP1lXZBqMVy0mRM89dY+o9jBtUk9XI5yFFru6fTaqzfSQNPdtUi68AVsunDNVtTYJ51ATxGj5hIEvIowJF5zUJYMjqIVC8yWC6xTJK6xQNChRFx89phkOtolP/U4WGKEJhxMEaUUGPP3N6rcmhreiKGCeSjSqdUP/CNk0swXTaNmUZZdKwJL5IlkVEeH+aXz22MpLOihgcIJ5Mni5ffQF+IvSNTevw8lgHCyP/IxT3IbWUUIQDRH3WOtJtsgDC7R5881zs+FSmkwKe9+B6Orst5VNNhIolIiRC1FW1hSVPEiC75JO6vq/5kvZ0ufzeqCySx/NvsvvpSwphD6CRMBbPvWcWWtkVje+YLieZw4dXpIP7a6YbMaX7RTkpuJLgb0fLxmAycBUv93ssxnzgluAjjTMNFCq3LU5p7yzRVihOy76+XsIN+fMoS/huFuSPAfI/FU+VK2V+iYcITLg0gNtnu1U9iyKi/t1bmzGuZErwqsfGi0PVXn8L78LQQLCzpi0T9RhCGpqxios0eoJqnRJLPSVJVmb37zipz7efNjHoIAxqg/HHZdXgQoj5fxWMdEwHauDNvHgusx/Jr+nuK8oOwoeB72hz1AortwCOIZbaQp6YEZH5RsqvwN1fH/H3/EzIJnjTPI0fJPgaKtBvdLLbzkTIvZeJykmlvkNp51xZWA/BO6qHe/chEXv2S7IYo1w+38S6rDGEBPwBHaCpZcumXXcwQsYCWyL0sWL+QIhbXdkwYfCe196lijnUddTYOWtKnE88XUWozZ5TwefMQyyjy5ifqIFn99t2EDOe/R5bXbB6KHleRAwGDmWp+xwaAE7vGy7yUXxXbbk4VacmhSqtqSZzXI4pG43wtigNJV4QTmdB3wEZ+rmMlYtotXQ8AsNEDJweOhHDdkrvL6wsEBoE/xTulCd9UK5TMhEj2rN+yNSRQ198rA+uUh5DnNokUVb/Ah8r5GVjw8kbTo/qjuwsHiaZOxwaqnh0AFpcJLMltkxNveoheYd7SPqthjSgUcqKkLGJXPREVMIBDThbH+yKM87PypkA8xEHVIUTjDIcSLIKEyOMYFWzvL09AJ//F9RO7Zb8vn1LljjnQVlJWGdyQzxxUGEF25ZSxC4Ky6/TjsnpBTRiBQ9FE1D8BQ8d4SppOWULyr2M6MKm9CgDBrggwnLdUfwZKM0XnpFTbfAYtEzbZmHEF+fwfC4eDc372i1Vj7xtHNw9PDg2wrlUv1Cwqe/+TkrSaZr562kj8dy2rhVaDXSf2sFVlnwmKcnWa3K/lLJtXZCPMFUAPDTqOIgbBrm9ruA42R/b5szcA4AJbbVp5+/ReQxj/2BasYy5nH5XfXY+cwvf9rgZ7vowbmgcZyta4MYXicf0OqQuASEI40oCAinBvp71uibGaCZ3/YfEYudIDu2EqdhBtgnIoW+Z9LCcBsUqIcrYalEzcj6PgxRznV+IMIimSIgg6w/E8SmXIYF3UMP74tyk+Y74PowGsc8e08A37J8qej8LWrXJDM7bitSfvqU7r0cQunBgr6XlY2EoYUtzHsW5xJL3uyTrnYT9XOVSy/gJCKIf1b+nmVqmotlvc/+rOjxlJDRkOU9gswJySpqvGb2Bkj6cL/xrjfjSimwTaN+WN0xsvhFFXjLX4XkSrrR2JLmeKtexHw+eSvsChYyZhibLvItDp17vdF977kfj6ITEny0m6PHBn6y8cgGvaycAldCwp9l18JSgJNpA0W7P2jCQfHVMjz6Kff8z3VpKu+BZJDRs/pEz7dMLcClGp8+SyQ14ut/T7Vda6dwh0aLo7gm5KudyqE786AC2a5XdR0rAE7ERh8Pg9JNCp+3G1klVsYUoHZiPK8rp2HUEvOwjxASy7nNP7snQ2dcnCjSAGo/wTrvJBOTCnUFBVjp64PqUMX4gMWxEpHIPFbUu/0t7OJrZAh3z8J06+gBGOJnceBn/6geRal2UznxqbJDoaEn5slUAToBP4XO06+J8GbHyt2ihjFW/5SUXa3DD3HBKcaYTHBFNwxLHb5iOTB4hCAxEcdUuWdPbGXkxTLMi50EWG+K4RdiOLpgALIYXsxR9Ie39Ec8L9iNMkNRZSkfXG8PtQaEUiW3NUzRdyLi5KyofT/HjzP8xtMMCHUUHKOvdwC7phO6g6u9J2ViKAgFnACkgLGWZfPOzOOfjDaUVTyIUmunImf8ZYxhSB5E2q8Yub21yzQC7jkSeDgp39OZ+wRH3KzUnI2lTxDf4zn/N3tADIvXblWqQFUNZ9ao6j0QeFRol15NF3edq37H39uhAMCzDOpeOu3vDVKM1APatqNRtIIRt97PNZ4K/wPSdxs5SNfzX6H7bcfxkDquN/68F12T58maqZFwNkSH/cTRNULeor9WLY6ZOsH0TsExTzlFSm9o4UkLXxtavuf81lRx6m7nGOHlz1qVVUEgeu2BMv+qH54vjCtZ/8IKcdB1ic495RHG1q03pnRxJS59B8vd2TgH2xGB4D5fn0uvRRst8IPTbJLb6zdEXW4ichBTaQxliUw0GVjYrOwFc+ShNeXzAyAPWsxN2ROY08SNRlzgcUTYZlhDsYaKKcyNFawXrBhfwFPa7nWw+NCLclGz7T4fZ2E7yW8uEn5VptGVvP/3DIsLZvubF8U0Ur0AToafkuagGCA62aAbP9Usd475bT8VzQb76BE8tAsUVQ8R15ag8Cnz5r19WBs9hVLI1a7KQ7awgREfH9koJC55PejMZmU4Sv7a8dXjauLaDATEBIPgffY8Y1GM82jXEHupRu1vK7R2TWxGlnrgurcpB6gjDdEowH/91HE3pKP6TxzlPQD0ujmTRkWYEdSokmmtCP8N7BBWYdpmDX4oka9eH0/RJg0xQzmyzmJFwkrTMXELgpKXlHFlGsH8I33DC5jGVa1NeYlYFdYGa5o3rEy6v3KrDsRQAUWYcuRYZ0c+K8iQU5GPQsI8RUVlFSXUfes/FzWVcVQDK2X5GZdz/By6Y7r9VyvkMe8ao7JdI7uPBjHV6AcGdrly/BrD5RO+bPYE4Ihj4h95TAt2FtotLTRIhBbcfPUEea/VEApj+Ghj/D45sd+LBt4tL1qIszypWVV1jn44hwMxidTy2GR5BmIGJ2Bj8U0OfBL8Ujpi5TYQXc6ZMZN1C2l9UQ3Us+FiYT2cuhnOB066HbynCfdwfLhAqTMVBlzPdWkfDe4CL1D4OSqdYiI6Pv4ckppbkdu+Zi6PbCJ3KBSF+WAYgRZTr4ie7cKjw2c4hFOyHY34XjGI+2GqA5Ccq0vsOOCRDqy+RB2ClYoFVBaGfP29Te9CcCnPaD5jl2D9JrcLdwvb3NvX7rqPfDQaUlxy11FwQV+m1kg75E2bt7v2ctKCBU7jP8pHcmXrcXstUIiNQMbAqad7ye6SMlBUmcCSmDmKRGhAi6b6sIA6RYR0J2RGQ5Sc5pZ23bwvPiDFPjkMif2QUW1/lM80TTdwzwZKi1MH6PwJUEbizDvQ7D+984u84BsA2Rll/dGuk9nqYgub4cK7oc9Nbpnsc/EtxOD8aNU0R5ZVQclk8gtbwtnXbgGHXoDVOEYfk9UYg5M4wNN6/Rb6MElGGVofAQQj8XODS9Hhj+s7XQxMy5zrvvhQG1mqDwgamYfAy3dBZ+BYyaQG+XEjWNbwTgpJwqzCvjkP8EdMrGcapKqh7nWgHoy3QlHrf24YcIoUu3w7bObVNTVUZkuS+Vwq1D8X+HdVvxQVl9DucCb1mvWBdAV6Pom+EL+q1iJ/eCff4IKIPHQkknFUERUjVptekwdgprDoZZNhWqOIpjFNtOxb5iDhxKIs1NY8Rtp71U8ycegxmfuZEwaCCJ02XmmBGApaS8DXrcZwIMuAqEK64WhbJ+YdgAxWVQqXSicV5xhiAbdpVfviaw2f2phmDuPePGkUfBH7qqEp3N+RwGYuh9fhqaOyD9XZdRQJXm0jOemMX9MzHxXOsnd17+LYymLPapRWe08BocnqHxc26GEkD80enShNGrMnFFyV10ZlyzhFyxZ7o69N+GxFzB4ccv41HqVlowFHWsndrWVg3r51rAs/R4lLsQWH9xnRn9tqkZ/FL/4wQbiazalMrV5MTjhVC75//ILX+LgBJVvTZh1StSreu/Nc5DTiMNNmqY4XeXwsy8HHqtutDDodej4u5eherj/oUB639BWYwMG8mej3awtzYiHW5K4N81FXKH23FTpcIJVETBM/nmGybzqNVx8w7N+hkCab0iiK8H7JWBuxn6uAzmoibpZmqZUratUXvaUd0iuDvyFoY5FgI7kH6iHkU8LhE6dOpvgKAvoCg5SaawPH+znumbjR+zE4hIGTZVeo0yvndcjtz6xkuMXprXdrfRuBqFtElCwzm7P1OFQPDfDVJdTzVQB4HM9qMkjRTKRwn1d85US9gf8ndIQeMRhsx22AoUro/rqnO+zfe7gn8uXjovrtg72OzfQ/uo04n/LE+f44rctIs+3QSTnBuH0TUNRVCrrC5Mydl0gIaslAt6TDR034iO1SnOmpjyal9Jubp8tYkM1Kac2kg0DUZ4M+97dIAe4WR9QYnny7ZFh1R/f3CQa1lEfO9HcOOerHmAfPzNQKcy9ajqKrWvOBHkPi0E/pzbv/qZUOFyruExJDIqXHZjKOu0GWbmZxUQ9IBMMBFQMNuFcSpbJu7JImyKSLEzq2wBvyTQB7JoisnNKBTzYBvSGjvJJtZRkS/E+lM+ZpVaof6Oo/B1AdYh7ryqBPrZkpbMg9RLfEsQfbC1buzo8hF/GEgZPmCYCRyCyL/SHaWNuT8x4GRX0FJgODYYTQmr1v/fFe7B08+zI6+THv+ZYa+KLZSevN2nH5pIp02f8fAiIt8NJAcYJlQXYbpcOKpP+FZ/z0OUTFTdpfgrscKqdRfuAcR5A3hq5P0vFzAKnfRE84oZt+H4VIoknYO1NDaEt4COLG/L9tUIQEfuMqtpXlfi2zR09juzW4opM68jeXBcEv5YXxgYGEbCemmk8bDLUtVIR6cedrHuLYLwo244f5I3YNmNngstn4IcrzfUwSdW3rXizpbOAtfknNgjBjQaZk4pVEXKQ06cNOlRmbP9g6x2wFtxV83w7AZ0jx+QLyRUReaO9xFYeEztWNvxpMv64K24pPTv/rrHyzJx5evPPe7vMXJeCTMy98LSnNcHw3NwO9dip8RMrhBXQIcQhCaQkSrgqms8pdvJGarqDixaCmnHqUSvSOrjVLDDdaHKD1hKT3E8zG/GP08XzQOtGoXDO6COzOyqyLiLxMFrjUeWdeuAxpSBs+G1USAUWdOHrlB1a0Gk3aKXEPrxw09pTXAOT0pR5fXnAyAWHJ6EsNUaIuG9ZUwB3+M+CZZjQiiZ0686zKa4Crx0UOPnohwV69z0BRQNWwhTwi3ugDHd/zCcXWHKXy3MBb/Z1sx8GR7NuVCjbfoq2+aMWrwCrcAmvSM9I3IfjYjID3IWJqJXoAfXWwWDMCefzy13F+WYpYkFlqqB1rG5IVJGX7gBV+7+1v2MiYC7QuimWvAjZy93AZTXuIXJyqKv80O/N/paXSO7GKnl6bH1VB1SiYjFS4m0dADb3TE67qP8lU9Ill8HlhWl7lhEpNRqd3S3338Ae7N4AqM2KsdCdPpSbB0tUkAtqn9HVVpUK+J/tOGUn1+IuihZmscHrUiGMNNsTtQ8Xu2Zx+QzL1QtqeWKYt72aYYz0HAlp8c332OLvmH3Zu0BdOdgqZUTy6MxbchuWVBGxeboVRwU9ycHj6Rh4XChvDd6cUtezr0osXM4hyq+Fj3oS88WBiq9d0ZP0EbwTRwLQhhhMIgzU8d6dJLNcVRC/nVI3SQKl/kcT5GtWXRr4dxJX+A/bBRVji53sj9Jvan7cuLZ1SH+lIJfUlb55aGMXNcdFBvMUocTXYsI7ldKGntDoSTmZ8UjHxUpji7/ZVfQTLvHELV0ylxzlQ13Yeiz8N/Y4LP6A0pPTPqq3aqcoQ8Roib0lAZN5FLfMqSsF5bECQaR60JOONP/yLTiyxyrWx+pJ4wglC7Ymx1iAJ4zziQHHCBmd9abL2qxGAOKE375iN09Ss9/l5eAGaSE/czPuRMF/XwLL6McGTi0QY3uXjm3n7IH9c/Ed7VpGZ1SeTTmIg/bz6ASl6o7mKzXqZ6a8VJljnqqtcXEnwXklBfQXx6iUsb34OV6M6TsT3u2DUJgg7kEZ3y95ip1ztYhMbsY4eOaOlv6CEgBlP314bYrMUQ3uxylS4zvWzgeCyam4k2UcBXPLJv+xUPK1hB++GkH+yW7yaOwIXJ1yB7PPxarpweJsJevUB//zhQ0vTRXPb5FFtRpx0OFnk/+STC/5GRiTU1Uue2P9aA5sP82rLuDGk7XMq1zcBoqkFEEMcqbbLPxJnrZcMDFbckXb+UPIYK57MzCphTZeoFfn1FLegCRrUdfZTZpWWj13sua5jO7H2Z8zfxyWNTLuaEapdKEWg3LouKNsH7QXWKi33ZcfcN/qXJOB/N/L5GW5ttPqvki55hJdoQRWSbuw/09SrMFly/+Ofbsj+haOWEcbKBtaTHfeFkFaBzBd/tJzV3dUupZ1RTO8RAudeCv8Px1/2FWxhuhFzLUu8T/JmOLktQRoPo42nZhz1ULMjehrq0D67kEJWsAzxb/WTzvog6/YXwSAhToo27Uvx4nPGTqu/2HK2hgQRYsStSMsQMFZ6l88Foj5I3AJ+Jioy8nCboQJk7li7tbwyv0rz0XVLmyqEoPiovVWVLgTiXA9mL7wpxNQ91X0cnClqh3ByXMcdjvQTb4lTZD2mkORONHVZZggvTOUWL9gorMs3KxfTDGDOzF4+ghHGc8UR0vAE7Moz4Pl+DwQQXljXRcCG/CyXfHoII5DAjOE8n8FkXYsQuwLdrWJHJJkOAfAfKN0=
*/