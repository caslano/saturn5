/* Copyright 2003-2020 Joaquin M Lopez Munoz.
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
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/copy_map.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
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
  typedef index_node_base<Value,Allocator>    node_type;
  typedef typename multi_index_node_type<
    Value,IndexSpecifierList,Allocator>::type final_node_type;
  typedef multi_index_container<
    Value,IndexSpecifierList,Allocator>       final_type;
  typedef tuples::null_type                   ctor_args_list;
  typedef typename rebind_alloc_for<
    Allocator,typename Allocator::value_type
  >::type                                     final_allocator_type;
  typedef mpl::vector0<>                      index_type_list;
  typedef mpl::vector0<>                      iterator_type_list;
  typedef mpl::vector0<>                      const_iterator_type_list;
  typedef copy_map<
    final_node_type,
    final_allocator_type>                     copy_map_type;

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  typedef index_saver<
    node_type,
    final_allocator_type>                     index_saver_type;
  typedef index_loader<
    node_type,
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

  final_node_type* insert_(
    const value_type& v,node_type*,final_node_type*& x,lvalue_tag)
  {
    return insert_(v,x,lvalue_tag());
  }

  final_node_type* insert_(
    const value_type& v,node_type*,final_node_type*& x,rvalue_tag)
  {
    return insert_(v,x,rvalue_tag());
  }

  final_node_type* insert_(
    const value_type&,node_type*,final_node_type*& x,emplaced_tag)
  {
    return x;
  }

  void erase_(node_type* x)
  {
    final().destroy_value(static_cast<final_node_type*>(x));
  }

  void delete_node_(node_type* x)
  {
    final().destroy_value(static_cast<final_node_type*>(x));
  }

  void clear_(){}

  template<typename BoolConstant>
  void swap_(
    index_base<Value,IndexSpecifierList,Allocator>&,
    BoolConstant /* swap_allocators */)
  {}

  void swap_elements_(index_base<Value,IndexSpecifierList,Allocator>&){}

  bool replace_(const value_type& v,node_type* x,lvalue_tag)
  {
    x->value()=v;
    return true;
  }

  bool replace_(const value_type& v,node_type* x,rvalue_tag)
  {
    x->value()=boost::move(const_cast<value_type&>(v));
    return true;
  }

  bool modify_(node_type*){return true;}

  bool modify_rollback_(node_type*){return true;}

  bool check_rollback_(node_type*)const{return true;}

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

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<final_node_type*,bool> final_emplace_hint_(
    final_node_type* position,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    return final().emplace_hint_(
      position,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

  void final_erase_(final_node_type* x){final().erase_(x);}

  void final_delete_node_(final_node_type* x){final().delete_node_(x);}
  void final_delete_all_nodes_(){final().delete_all_nodes_();}
  void final_clear_(){final().clear_();}

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