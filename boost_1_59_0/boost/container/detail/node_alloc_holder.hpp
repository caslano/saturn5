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
#include <boost/container/detail/is_pair.hpp>
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

//This trait is used to type-pun std::pair because in C++03
//compilers std::pair is useless for C++11 features
template<class T, bool = dtl::is_pair<T>::value >
struct node_internal_data_type
{
   typedef T type;
};

template<class T>
struct node_internal_data_type< T, true>
{
   typedef dtl::pair< typename dtl::remove_const<typename T::first_type>::type
                     , typename T::second_type>
                     type;
};

template <class T, class HookDefiner>
struct base_node
   :  public HookDefiner::type
{
   public:
   typedef T value_type;
   typedef typename node_internal_data_type<T>::type internal_type;
   typedef typename HookDefiner::type hook_type;

   typedef typename dtl::aligned_storage<sizeof(T), dtl::alignment_of<T>::value>::type storage_t;
   storage_t m_storage;

   #if defined(BOOST_GCC) && (BOOST_GCC >= 40600) && (BOOST_GCC < 80000)
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wstrict-aliasing"
      #define BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif
   public:

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template<class Alloc, class ...Args>
   explicit base_node(Alloc &a, Args &&...args)
      : hook_type()
   {
      ::boost::container::allocator_traits<Alloc>::construct
         (a, &this->get_real_data(), ::boost::forward<Args>(args)...);
   }

   #else //defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_BASE_NODE_CONSTRUCT_IMPL(N) \
   template< class Alloc BOOST_MOVE_I##N BOOST_MOVE_CLASS##N > \
   explicit base_node(Alloc &a BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
      : hook_type()\
   {\
      ::boost::container::allocator_traits<Alloc>::construct\
         (a, &this->get_real_data() BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_BASE_NODE_CONSTRUCT_IMPL)
   #undef BOOST_CONTAINER_BASE_NODE_CONSTRUCT_IMPL

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template<class Alloc, class It>
   explicit base_node(iterator_arg_t, Alloc &a, It it)
      : hook_type()
   {
      ::boost::container::construct_in_place(a, &this->get_real_data(), it);
   }

   BOOST_CONTAINER_FORCEINLINE T &get_data()
   {  return *move_detail::force_ptr<T*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const T &get_data() const
   {  return *move_detail::force_ptr<const T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE internal_type &get_real_data()
   {  return *move_detail::force_ptr<internal_type*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const internal_type &get_real_data() const
   {  return *move_detail::force_ptr<const internal_type*>(this->m_storage.data);  }

   #if defined(BOOST_CONTAINER_DISABLE_ALIASING_WARNING)
      #pragma GCC diagnostic pop
      #undef BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   template<class Alloc>
   void destructor(Alloc &a) BOOST_NOEXCEPT
   {
      allocator_traits<Alloc>::destroy
         (a, &this->get_real_data());
      this->~base_node();
   }

   template<class Pair>
   BOOST_CONTAINER_FORCEINLINE
   typename dtl::enable_if< dtl::is_pair<Pair>, void >::type
      do_assign(const Pair &p)
   {
      typedef typename Pair::first_type first_type;
      const_cast<typename dtl::remove_const<first_type>::type &>(this->get_real_data().first) = p.first;
      this->get_real_data().second  = p.second;
   }

   template<class V>
   BOOST_CONTAINER_FORCEINLINE 
   typename dtl::disable_if< dtl::is_pair<V>, void >::type
      do_assign(const V &v)
   {  this->get_real_data() = v; }

   template<class Pair>
   BOOST_CONTAINER_FORCEINLINE 
   typename dtl::enable_if< dtl::is_pair<Pair>, void >::type
      do_move_assign(Pair &p)
   {
      typedef typename Pair::first_type first_type;
      const_cast<first_type&>(this->get_real_data().first) = ::boost::move(p.first);
      this->get_real_data().second = ::boost::move(p.second);
   }

   template<class V>
   BOOST_CONTAINER_FORCEINLINE 
   typename dtl::disable_if< dtl::is_pair<V>, void >::type
      do_move_assign(V &v)
   {  this->get_real_data() = ::boost::move(v); }

   private:
   base_node();

   BOOST_CONTAINER_FORCEINLINE ~base_node()
   { }
};


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
   typedef allocator_node_destroyer<NodeAlloc>                         Destroyer;
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
      : NodeAlloc(boost::move(BOOST_MOVE_TO_LV(x).node_alloc()))
   {  this->icont().swap(x.icont());  }

   explicit node_alloc_holder(const val_compare &c)
      : m_icont(typename ICont::key_compare(c))
   {}

   //helpers for move assignments
   explicit node_alloc_holder(BOOST_RV_REF(node_alloc_holder) x, const val_compare &c)
      : NodeAlloc(boost::move(BOOST_MOVE_TO_LV(x).node_alloc())), m_icont(typename ICont::key_compare(c))
   {  this->icont().swap(x.icont());  }

   explicit node_alloc_holder(BOOST_RV_REF(node_alloc_holder) x, const val_hasher &hf, const val_equal &eql)
      : NodeAlloc(boost::move(BOOST_MOVE_TO_LV(x).node_alloc()))
      , m_icont( typename ICont::bucket_traits()
               , typename ICont::hasher(hf)
               , typename ICont::key_equal(eql))
   {  this->icont().swap(BOOST_MOVE_TO_LV(x).icont());   }

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
      NodeAlloc &nalloc = this->node_alloc();
      Deallocator node_deallocator(p, nalloc);
      ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t())
         Node(nalloc, boost::forward<Args>(args)...);
      node_deallocator.release();
      return (p);
   }

   #else //defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_NODE_ALLOC_HOLDER_CONSTRUCT_IMPL(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   NodePtr create_node(BOOST_MOVE_UREF##N)\
   {\
      NodePtr p = this->allocate_one();\
      NodeAlloc &nalloc = this->node_alloc();\
      Deallocator node_deallocator(p, nalloc);\
      ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t())\
         Node(nalloc BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      node_deallocator.release();\
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
      NodeAlloc &nalloc = this->node_alloc();
      Deallocator node_deallocator(p, nalloc);
      ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t())
         Node(iterator_arg_t(), nalloc, it);
      node_deallocator.release();
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
      boost::movelib::to_raw_pointer(nodep)->destructor(this->node_alloc());
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
      (FwdIterator beg, size_type n, Inserter inserter)
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
            dtl::scoped_node_destructor<NodeAlloc> sdestructor(nalloc, 0);
            while(n){
               --n;
               p = boost::movelib::iterator_to_raw_pointer(itbeg);
               ++itbeg; //Increment iterator before overwriting pointed memory
               //This does not throw
               ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t())
                  Node(iterator_arg_t(), nalloc, beg);
               sdestructor.set(p);
               ++beg;
               //This can throw in some containers (predicate might throw).
               //(sdestructor will destruct the node and node_deallocator will deallocate it in case of exception)
               inserter(*p);
               sdestructor.release();
            }
            sdestructor.release();
            node_deallocator.release();
         }
         BOOST_CATCH(...){
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
      allocator_node_destroyer_and_chain_builder<NodeAlloc> builder(this->node_alloc(), chain);
      this->icont().clear_and_dispose(builder);
      //BOOST_STATIC_ASSERT((::boost::has_move_emulation_enabled<typename NodeAlloc::multiallocation_chain>::value == true));
      if(!chain.empty())
         this->node_alloc().deallocate_individual(chain);
   }

   icont_iterator erase_range(const icont_iterator &first, const icont_iterator &last, version_1)
   {  return this->icont().erase_and_dispose(first, last, Destroyer(this->node_alloc())); }

   icont_iterator erase_range(const icont_iterator &first, const icont_iterator &last, version_2)
   {
      NodeAlloc & nalloc = this->node_alloc();
      typename NodeAlloc::multiallocation_chain chain;
      allocator_node_destroyer_and_chain_builder<NodeAlloc> chain_builder(nalloc, chain);
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