/* Copyright 2003-2021 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_INDEX_BASE_HPP
#define BOOST_MULTI_INDEX_DETAIL_INDEX_BASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/core/addressof.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/copy_map.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/index_access_sequence.hpp>
#include <boost/multi_index/detail/node_handle.hpp>
#include <boost/multi_index/detail/node_type.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <boost/tuple/tuple.hpp>
#include <utility>

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/multi_index/detail/index_loader.hpp>
#include <boost/multi_index/detail/index_saver.hpp>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* The role of this class is threefold:
 *   - tops the linear hierarchy of indices.
 *   - terminates some cascading backbone function calls (insert_, etc.),
 *   - grants access to the backbone functions of the final
 *     multi_index_container class (for access restriction reasons, these
 *     cannot be called directly from the index classes.)
 */

struct lvalue_tag{};
struct rvalue_tag{};
struct emplaced_tag{};

template<typename Value,typename IndexSpecifierList,typename Allocator>
class index_base
{
protected:
  typedef index_node_base<Value,Allocator>    index_node_type;
  typedef typename multi_index_node_type<
    Value,IndexSpecifierList,Allocator>::type final_node_type;
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>       final_type;
  typedef tuples::null_type                   ctor_args_list;
  typedef typename rebind_alloc_for<
    Allocator,typename Allocator::value_type
  >::type                                     final_allocator_type;
  typedef node_handle<
    final_node_type,final_allocator_type>     final_node_handle_type;
  typedef mpl::vector0<>                      index_type_list;
  typedef mpl::vector0<>                      iterator_type_list;
  typedef mpl::vector0<>                      const_iterator_type_list;
  typedef copy_map<
    final_node_type,
    final_allocator_type>                     copy_map_type;

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  typedef index_saver<
    index_node_type,
    final_allocator_type>                     index_saver_type;
  typedef index_loader<
    index_node_type,
    final_node_type,
    final_allocator_type>                     index_loader_type;
#endif

private:
  typedef Value                               value_type;
  typedef allocator_traits<Allocator>         alloc_traits;
  typedef typename alloc_traits::size_type    size_type;

protected:
  explicit index_base(const ctor_args_list&,const Allocator&){}

  index_base(
    const index_base<Value,IndexSpecifierList,Allocator>&,
    do_not_copy_elements_tag)
  {}

  void copy_(
    const index_base<Value,IndexSpecifierList,Allocator>&,const copy_map_type&)
  {}

  final_node_type* insert_(const value_type& v,final_node_type*& x,lvalue_tag)
  {
    x=final().allocate_node();
    BOOST_TRY{
      final().construct_value(x,v);
    }
    BOOST_CATCH(...){
      final().deallocate_node(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return x;
  }

  final_node_type* insert_(const value_type& v,final_node_type*& x,rvalue_tag)
  {
    x=final().allocate_node();
    BOOST_TRY{
      final().construct_value(x,boost::move(const_cast<value_type&>(v)));
    }
    BOOST_CATCH(...){
      final().deallocate_node(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return x;
  }

  final_node_type* insert_(const value_type&,final_node_type*& x,emplaced_tag)
  {
    return x;
  }

  template<typename MultiIndexContainer>
  final_node_type* insert_(
    const value_type&,final_node_type*& x,MultiIndexContainer* p)
  {
    p->final_extract_for_transfer_(
      x,index_access_sequence<final_type>(&final()));
    return x;
  }

  final_node_type* insert_(
    const value_type& v,index_node_type*,final_node_type*& x,lvalue_tag)
  {
    return insert_(v,x,lvalue_tag());
  }

  final_node_type* insert_(
    const value_type& v,index_node_type*,final_node_type*& x,rvalue_tag)
  {
    return insert_(v,x,rvalue_tag());
  }

  final_node_type* insert_(
    const value_type&,index_node_type*,final_node_type*& x,emplaced_tag)
  {
    return x;
  }

  template<typename Dst>
  void extract_(index_node_type*,Dst){}

  void clear_(){}

  template<typename BoolConstant>
  void swap_(
    index_base<Value,IndexSpecifierList,Allocator>&,
    BoolConstant /* swap_allocators */)
  {}

  void swap_elements_(index_base<Value,IndexSpecifierList,Allocator>&){}

  bool replace_(const value_type& v,index_node_type* x,lvalue_tag)
  {
    x->value()=v;
    return true;
  }

  bool replace_(const value_type& v,index_node_type* x,rvalue_tag)
  {
    x->value()=boost::move(const_cast<value_type&>(v));
    return true;
  }

  bool modify_(index_node_type*){return true;}

  bool modify_rollback_(index_node_type*){return true;}

  bool check_rollback_(index_node_type*)const{return true;}

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* serialization */

  template<typename Archive>
  void save_(Archive&,const unsigned int,const index_saver_type&)const{}

  template<typename Archive>
  void load_(Archive&,const unsigned int,const index_loader_type&){}
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const{return true;}
#endif

  /* access to backbone memfuns of Final class */

  final_type&       final(){return *static_cast<final_type*>(this);}
  const final_type& final()const{return *static_cast<const final_type*>(this);}

  template<typename Index>
  static typename Index::final_type& final(Index& x) /* cross-index access */
    {return static_cast<typename Index::final_type&>(x);}

  final_node_type* final_header()const{return final().header();}

  bool      final_empty_()const{return final().empty_();}
  size_type final_size_()const{return final().size_();}
  size_type final_max_size_()const{return final().max_size_();}

  std::pair<final_node_type*,bool> final_insert_(const value_type& x)
    {return final().insert_(x);}
  std::pair<final_node_type*,bool> final_insert_rv_(const value_type& x)
    {return final().insert_rv_(x);}
  template<typename T>
  std::pair<final_node_type*,bool> final_insert_ref_(const T& t)
    {return final().insert_ref_(t);}
  template<typename T>
  std::pair<final_node_type*,bool> final_insert_ref_(T& t)
    {return final().insert_ref_(t);}
  std::pair<final_node_type*,bool> final_insert_nh_(final_node_handle_type& nh)
    {return final().insert_nh_(nh);}

  template<typename Index>
  std::pair<final_node_type*,bool> final_transfer_(Index& x,final_node_type* n)
    {return final().transfer_(x,n);}

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<final_node_type*,bool> final_emplace_(
    BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    return final().emplace_(BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

  std::pair<final_node_type*,bool> final_insert_(
    const value_type& x,final_node_type* position)
    {return final().insert_(x,position);}
  std::pair<final_node_type*,bool> final_insert_rv_(
    const value_type& x,final_node_type* position)
    {return final().insert_rv_(x,position);}
  template<typename T>
  std::pair<final_node_type*,bool> final_insert_ref_(
    const T& t,final_node_type* position)
    {return final().insert_ref_(t,position);}
  template<typename T>
  std::pair<final_node_type*,bool> final_insert_ref_(
    T& t,final_node_type* position)
    {return final().insert_ref_(t,position);}
  std::pair<final_node_type*,bool> final_insert_nh_(
    final_node_handle_type& nh,final_node_type* position)
    {return final().insert_nh_(nh,position);}

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<final_node_type*,bool> final_emplace_hint_(
    final_node_type* position,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    return final().emplace_hint_(
      position,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

  final_node_handle_type final_extract_(final_node_type* x)
  {
    return final().extract_(x);
  } 

  template<typename Dst>
  void final_extract_for_transfer_(final_node_type* x,Dst dst)
  {
    final().extract_for_transfer_(x,dst);
  } 

  void final_erase_(final_node_type* x){final().erase_(x);}

  void final_delete_node_(final_node_type* x){final().delete_node_(x);}
  void final_delete_all_nodes_(){final().delete_all_nodes_();}
  void final_clear_(){final().clear_();}

  template<typename Index>
  void final_transfer_range_(
    Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
    {final().transfer_range_(x,first,last);}

  void final_swap_(final_type& x){final().swap_(x);}

  bool final_replace_(
    const value_type& k,final_node_type* x)
    {return final().replace_(k,x);}
  bool final_replace_rv_(
    const value_type& k,final_node_type* x)
    {return final().replace_rv_(k,x);}

  template<typename Modifier>
  bool final_modify_(Modifier& mod,final_node_type* x)
    {return final().modify_(mod,x);}

  template<typename Modifier,typename Rollback>
  bool final_modify_(Modifier& mod,Rollback& back,final_node_type* x)
    {return final().modify_(mod,back,x);}

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  void final_check_invariant_()const{final().check_invariant_();}
#endif
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* index_base.hpp
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
*/