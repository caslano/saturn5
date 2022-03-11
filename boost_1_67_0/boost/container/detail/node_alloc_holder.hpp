//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_NODE_ALLOC_HPP_
#define BOOST_CONTAINER_DETAIL_NODE_ALLOC_HPP_

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// container
#include <boost/container/allocator_traits.hpp>
// container/detail
#include <boost/container/detail/addressof.hpp>
#include <boost/container/detail/alloc_helpers.hpp>
#include <boost/container/detail/allocator_version_traits.hpp>
#include <boost/container/detail/construct_in_place.hpp>
#include <boost/container/detail/destroyers.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/placement_new.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/version_type.hpp>
// intrusive
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/options.hpp>
// move
#include <boost/move/utility_core.hpp>
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
// other
#include <boost/core/no_exceptions_support.hpp>


namespace boost {
namespace container {
namespace dtl {

BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(key_compare)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(key_equal)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(hasher)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(predicate_type)

template<class Allocator, class ICont>
struct node_alloc_holder
   : public allocator_traits<Allocator>::template
            portable_rebind_alloc<typename ICont::value_type>::type   //NodeAlloc
{
   //If the intrusive container is an associative container, obtain the predicate, which will
   //be of type node_compare<>. If not an associative container val_compare will be a "nat" type.
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      ( boost::container::dtl::
      , ICont, key_compare, dtl::nat)                 intrusive_val_compare;
   //In that case obtain the value predicate from the node predicate via predicate_type
   //if intrusive_val_compare is node_compare<>, nat otherwise
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      ( boost::container::dtl::
      , intrusive_val_compare
      , predicate_type, dtl::nat)                    val_compare;

   //If the intrusive container is a hash container, obtain the predicate, which will
   //be of type node_compare<>. If not an associative container val_equal will be a "nat" type.
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      (boost::container::dtl::
         , ICont, key_equal, dtl::nat2)              intrusive_val_equal;
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
   (boost::container::dtl::
      , ICont, hasher, dtl::nat3)                     intrusive_val_hasher;
   //In that case obtain the value predicate from the node predicate via predicate_type
   //if intrusive_val_compare is node_compare<>, nat otherwise
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
   (boost::container::dtl::
      , intrusive_val_equal
      , predicate_type, dtl::nat2)                    val_equal;
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
   (boost::container::dtl::
      , intrusive_val_hasher
      , predicate_type, dtl::nat3)                    val_hasher;

   typedef allocator_traits<Allocator>                            allocator_traits_type;
   typedef typename allocator_traits_type::value_type             val_type;
   typedef ICont                                                  intrusive_container;
   typedef typename ICont::value_type                             Node;
   typedef typename allocator_traits_type::template
      portable_rebind_alloc<Node>::type                           NodeAlloc;
   typedef allocator_traits<NodeAlloc>                            node_allocator_traits_type;
   typedef dtl::allocator_version_traits<NodeAlloc>  node_allocator_version_traits_type;
   typedef Allocator                                              ValAlloc;
   typedef typename node_allocator_traits_type::pointer           NodePtr;
   typedef dtl::scoped_deallocator<NodeAlloc>        Deallocator;
   typedef typename node_allocator_traits_type::size_type         size_type;
   typedef typename node_allocator_traits_type::difference_type   difference_type;
   typedef dtl::integral_constant<unsigned,
      boost::container::dtl::
         version<NodeAlloc>::value>                               alloc_version;
   typedef typename ICont::iterator                               icont_iterator;
   typedef typename ICont::const_iterator                         icont_citerator;
   typedef allocator_destroyer<NodeAlloc>                         Destroyer;
   typedef allocator_traits<NodeAlloc>                            NodeAllocTraits;
   typedef allocator_version_traits<NodeAlloc>                    AllocVersionTraits;

   private:
   BOOST_COPYABLE_AND_MOVABLE(node_alloc_holder)

   public:

   //Constructors for sequence containers
   node_alloc_holder()
   {}

   explicit node_alloc_holder(const ValAlloc &a)
      : NodeAlloc(a)
   {}

   //Constructors for associative containers
   node_alloc_holder(const val_compare &c, const ValAlloc &a)
      : NodeAlloc(a), m_icont(typename ICont::key_compare(c))
   {}

   node_alloc_holder(const val_hasher &hf, const val_equal &eql, const ValAlloc &a)
      : NodeAlloc(a)
      , m_icont(typename ICont::bucket_traits()
         , typename ICont::hasher(hf)
         , typename ICont::key_equal(eql))
   {}

   node_alloc_holder(const val_hasher &hf, const ValAlloc &a)
      : NodeAlloc(a)
      , m_icont(typename ICont::bucket_traits()
         , typename ICont::hasher(hf)
         , typename ICont::key_equal())
   {}

   node_alloc_holder(const val_hasher &hf)
      : m_icont(typename ICont::bucket_traits()
         , typename ICont::hasher(hf)
         , typename ICont::key_equal())
   {}

   explicit node_alloc_holder(const node_alloc_holder &x)
      : NodeAlloc(NodeAllocTraits::select_on_container_copy_construction(x.node_alloc()))
   {}

   node_alloc_holder(const node_alloc_holder &x, const val_compare &c)
      : NodeAlloc(NodeAllocTraits::select_on_container_copy_construction(x.node_alloc()))
      , m_icont(typename ICont::key_compare(c))
   {}

   node_alloc_holder(const node_alloc_holder &x, const val_hasher &hf, const val_equal &eql)
      : NodeAlloc(NodeAllocTraits::select_on_container_copy_construction(x.node_alloc()))
      , m_icont( typename ICont::bucket_traits()
               , typename ICont::hasher(hf)
               , typename ICont::key_equal(eql))
   {}

   node_alloc_holder(const val_hasher &hf, const val_equal &eql)
      : m_icont(typename ICont::bucket_traits()
         , typename ICont::hasher(hf)
         , typename ICont::key_equal(eql))
   {}

   explicit node_alloc_holder(BOOST_RV_REF(node_alloc_holder) x)
      : NodeAlloc(boost::move(x.node_alloc()))
   {  this->icont().swap(x.icont());  }

   explicit node_alloc_holder(const val_compare &c)
      : m_icont(typename ICont::key_compare(c))
   {}

   //helpers for move assignments
   explicit node_alloc_holder(BOOST_RV_REF(node_alloc_holder) x, const val_compare &c)
      : NodeAlloc(boost::move(x.node_alloc())), m_icont(typename ICont::key_compare(c))
   {  this->icont().swap(x.icont());  }

   explicit node_alloc_holder(BOOST_RV_REF(node_alloc_holder) x, const val_hasher &hf, const val_equal &eql)
      : NodeAlloc(boost::move(x.node_alloc()))
      , m_icont( typename ICont::bucket_traits()
               , typename ICont::hasher(hf)
               , typename ICont::key_equal(eql))
   {  this->icont().swap(x.icont());   }

   void copy_assign_alloc(const node_alloc_holder &x)
   {
      dtl::bool_<allocator_traits_type::propagate_on_container_copy_assignment::value> flag;
      dtl::assign_alloc( static_cast<NodeAlloc &>(*this)
                       , static_cast<const NodeAlloc &>(x), flag);
   }

   void move_assign_alloc( node_alloc_holder &x)
   {
      dtl::bool_<allocator_traits_type::propagate_on_container_move_assignment::value> flag;
      dtl::move_alloc( static_cast<NodeAlloc &>(*this)
                     , static_cast<NodeAlloc &>(x), flag);
   }

   ~node_alloc_holder()
   {  this->clear(alloc_version()); }

   size_type max_size() const
   {  return allocator_traits_type::max_size(this->node_alloc());  }

   NodePtr allocate_one()
   {  return AllocVersionTraits::allocate_one(this->node_alloc());   }

   void deallocate_one(const NodePtr &p)
   {  AllocVersionTraits::deallocate_one(this->node_alloc(), p);  }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template<class ...Args>
   NodePtr create_node(Args &&...args)
   {
      NodePtr p = this->allocate_one();
      BOOST_TRY{
         ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t()) Node;
         allocator_traits<NodeAlloc>::construct
            (this->node_alloc()
            , p->get_real_data_ptr(), boost::forward<Args>(args)...);
      }
      BOOST_CATCH(...) {
         p->destroy_header();
         this->node_alloc().deallocate(p, 1);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      return (p);
   }

   #else //defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_NODE_ALLOC_HOLDER_CONSTRUCT_IMPL(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   NodePtr create_node(BOOST_MOVE_UREF##N)\
   {\
      NodePtr p = this->allocate_one();\
      BOOST_TRY{\
         ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t()) Node;\
         allocator_traits<NodeAlloc>::construct\
            ( this->node_alloc()\
            , p->get_real_data_ptr()\
             BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      }\
      BOOST_CATCH(...) {\
         p->destroy_header();\
         this->node_alloc().deallocate(p, 1);\
         BOOST_RETHROW\
      }\
      BOOST_CATCH_END\
      return (p);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_NODE_ALLOC_HOLDER_CONSTRUCT_IMPL)
   #undef BOOST_CONTAINER_NODE_ALLOC_HOLDER_CONSTRUCT_IMPL

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template<class It>
   NodePtr create_node_from_it(const It &it)
   {
      NodePtr p = this->allocate_one();
      BOOST_TRY{
         ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t()) Node;
         ::boost::container::construct_in_place(this->node_alloc(), p->get_real_data_ptr(), it);
      }
      BOOST_CATCH(...) {
         p->destroy_header();
         this->node_alloc().deallocate(p, 1);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      return (p);
   }

   template<class KeyConvertible>
   NodePtr create_node_from_key(BOOST_FWD_REF(KeyConvertible) key)
   {
      NodePtr p = this->allocate_one();
      BOOST_TRY{
         ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t()) Node;
         NodeAlloc &na = this->node_alloc();
         node_allocator_traits_type::construct
            (na, dtl::addressof(p->get_real_data().first), boost::forward<KeyConvertible>(key));
         BOOST_TRY{
            node_allocator_traits_type::construct(na, dtl::addressof(p->get_real_data().second));
         }
         BOOST_CATCH(...){
            node_allocator_traits_type::destroy(na, dtl::addressof(p->get_real_data().first));
            BOOST_RETHROW;
         }
         BOOST_CATCH_END
      }
      BOOST_CATCH(...) {
         p->destroy_header();
         this->node_alloc().deallocate(p, 1);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      return (p);
   }

   void destroy_node(const NodePtr &nodep)
   {
      allocator_traits<NodeAlloc>::destroy(this->node_alloc(), boost::movelib::to_raw_pointer(nodep));
      this->deallocate_one(nodep);
   }

   void swap(node_alloc_holder &x)
   {
      this->icont().swap(x.icont());
      dtl::bool_<allocator_traits_type::propagate_on_container_swap::value> flag;
      dtl::swap_alloc(this->node_alloc(), x.node_alloc(), flag);
   }

   template<class FwdIterator, class Inserter>
   void allocate_many_and_construct
      (FwdIterator beg, difference_type n, Inserter inserter)
   {
      if(n){
         typedef typename node_allocator_version_traits_type::multiallocation_chain multiallocation_chain_t;

         //Try to allocate memory in a single block
         typedef typename multiallocation_chain_t::iterator multialloc_iterator_t;
         multiallocation_chain_t chain;
         NodeAlloc &nalloc = this->node_alloc();
         node_allocator_version_traits_type::allocate_individual(nalloc, n, chain);
         multialloc_iterator_t itbeg  = chain.begin();
         multialloc_iterator_t itlast = chain.last();
         chain.clear();

         Node *p = 0;
            BOOST_TRY{
            Deallocator node_deallocator(NodePtr(), nalloc);
            dtl::scoped_destructor<NodeAlloc> sdestructor(nalloc, 0);
            while(n){
               --n;
               p = boost::movelib::iterator_to_raw_pointer(itbeg);
               ++itbeg; //Increment iterator before overwriting pointed memory
               //This does not throw
               p = ::new(p, boost_container_new_t()) Node;
               node_deallocator.set(p);
               //This can throw
               boost::container::construct_in_place(nalloc, p->get_real_data_ptr(), beg);
               sdestructor.set(p);
               ++beg;
               //This can throw in some containers (predicate might throw).
               //(sdestructor will destruct the node and node_deallocator will deallocate it in case of exception)
               inserter(*p);
               sdestructor.set(0);
            }
            sdestructor.release();
            node_deallocator.release();
         }
         BOOST_CATCH(...){
            p->destroy_header();
            chain.incorporate_after(chain.last(), &*itbeg, &*itlast, n);
            node_allocator_version_traits_type::deallocate_individual(this->node_alloc(), chain);
            BOOST_RETHROW
         }
         BOOST_CATCH_END
      }
   }

   void clear(version_1)
   {  this->icont().clear_and_dispose(Destroyer(this->node_alloc()));   }

   void clear(version_2)
   {
      typename NodeAlloc::multiallocation_chain chain;
      allocator_destroyer_and_chain_builder<NodeAlloc> builder(this->node_alloc(), chain);
      this->icont().clear_and_dispose(builder);
      //BOOST_STATIC_ASSERT((::boost::has_move_emulation_enabled<typename NodeAlloc::multiallocation_chain>::value == true));
      if(!chain.empty())
         this->node_alloc().deallocate_individual(chain);
   }

   icont_iterator erase_range(const icont_iterator &first, const icont_iterator &last, version_1)
   {  return this->icont().erase_and_dispose(first, last, Destroyer(this->node_alloc())); }

   icont_iterator erase_range(const icont_iterator &first, const icont_iterator &last, version_2)
   {
      typedef typename NodeAlloc::multiallocation_chain multiallocation_chain;
      NodeAlloc & nalloc = this->node_alloc();
      multiallocation_chain chain;
      allocator_destroyer_and_chain_builder<NodeAlloc> chain_builder(nalloc, chain);
      icont_iterator ret_it = this->icont().erase_and_dispose(first, last, chain_builder);
      nalloc.deallocate_individual(chain);
      return ret_it;
   }

   template<class Key, class Comparator>
   size_type erase_key(const Key& k, const Comparator &comp, version_1)
   {  return this->icont().erase_and_dispose(k, comp, Destroyer(this->node_alloc())); }

   template<class Key, class Comparator>
   size_type erase_key(const Key& k, const Comparator &comp, version_2)
   {
      allocator_multialloc_chain_node_deallocator<NodeAlloc> chain_holder(this->node_alloc());
      return this->icont().erase_and_dispose(k, comp, chain_holder.get_chain_builder());
   }

   protected:
   struct cloner
   {
      explicit cloner(node_alloc_holder &holder)
         :  m_holder(holder)
      {}

      NodePtr operator()(const Node &other) const
      {  return m_holder.create_node(other.get_real_data());  }

      node_alloc_holder &m_holder;
   };

   struct move_cloner
   {
      move_cloner(node_alloc_holder &holder)
         :  m_holder(holder)
      {}

      NodePtr operator()(Node &other)
      {  //Use get_real_data() instead of get_real_data to allow moving const key in [multi]map
         return m_holder.create_node(::boost::move(other.get_real_data()));
      }

      node_alloc_holder &m_holder;
   };

   ICont &non_const_icont() const
   {  return const_cast<ICont&>(this->m_icont);   }

   NodeAlloc &node_alloc()
   {  return static_cast<NodeAlloc &>(*this);   }

   const NodeAlloc &node_alloc() const
   {  return static_cast<const NodeAlloc &>(*this);   }

   public:
   ICont &icont()
   {  return this->m_icont;   }

   const ICont &icont() const
   {  return this->m_icont;   }

   private:
   //The intrusive container
   ICont m_icont;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif // BOOST_CONTAINER_DETAIL_NODE_ALLOC_HPP_

/* node_alloc_holder.hpp
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
*/