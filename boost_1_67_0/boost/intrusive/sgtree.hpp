/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//
// The option that yields to non-floating point 1/sqrt(2) alpha is taken
// from the scapegoat tree implementation of the PSPP library.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_SGTREE_HPP
#define BOOST_INTRUSIVE_SGTREE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/intrusive/bs_set_hook.hpp>
#include <boost/intrusive/bstree.hpp>
#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/math.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/sgtree_algorithms.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>
#include <boost/intrusive/link_mode.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>

#include <cstddef>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //std::pair
#include <cmath>
#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

namespace detail{

/////////////////////////////////////////////////////////////
//
//       Halpha for fixed floating_point<false> option
//
/////////////////////////////////////////////////////////////

//! Returns floor(log2(n)/log2(sqrt(2))) -> floor(2*log2(n))
//! Undefined if N is 0.
//!
//! This function does not use float point operations.
inline std::size_t calculate_h_sqrt2 (std::size_t n)
{
   std::size_t f_log2 = detail::floor_log2(n);
   return (2*f_log2) + static_cast<std::size_t>(n >= detail::sqrt2_pow_2xplus1(f_log2));
}

struct h_alpha_sqrt2_t
{
   h_alpha_sqrt2_t(void){}
   std::size_t operator()(std::size_t n) const
   {  return calculate_h_sqrt2(n);  }
};

struct alpha_0_75_by_max_size_t
{
   alpha_0_75_by_max_size_t(void){}

   std::size_t operator()(std::size_t max_tree_size) const
   {
      const std::size_t max_tree_size_limit = ((~std::size_t(0))/std::size_t(3));
      return max_tree_size > max_tree_size_limit ? max_tree_size/4*3 : max_tree_size*3/4;
   }
};

/////////////////////////////////////////////////////////////
//
//       Halpha for fixed floating_point<true> option
//
/////////////////////////////////////////////////////////////

struct h_alpha_t
{
   explicit h_alpha_t(float inv_minus_logalpha)
      :  inv_minus_logalpha_(inv_minus_logalpha)
   {}

   std::size_t operator()(std::size_t n) const
   {
      ////////////////////////////////////////////////////////////
      // This function must return "floor(log2(1/alpha(n)))" ->
      //    floor(log2(n)/log(1/alpha)) ->
      //    floor(log2(n)/-log2(alpha))
      //    floor(log2(n)*(1/-log2(alpha)))
      ////////////////////////////////////////////////////////////
      return static_cast<std::size_t>(detail::fast_log2(float(n))*inv_minus_logalpha_);
   }

   private:
   //Since the function will be repeatedly called
   //precalculate constant data to avoid repeated
   //calls to log and division.
   //This will store 1/(-std::log2(alpha_))
   float inv_minus_logalpha_;
};

struct alpha_by_max_size_t
{
   explicit alpha_by_max_size_t(float alpha)
      :  alpha_(alpha)
   {}

   float operator()(std::size_t max_tree_size) const
   {  return float(max_tree_size)*alpha_;   }

   private:
   float alpha_;
};

template<bool Activate, class SizeType>
struct alpha_holder
{
   typedef boost::intrusive::detail::h_alpha_t           h_alpha_t;
   typedef boost::intrusive::detail::alpha_by_max_size_t multiply_by_alpha_t;

   alpha_holder()
      : max_tree_size_()
   {  set_alpha(0.70711f);   } // ~1/sqrt(2)

   float get_alpha() const
   {  return alpha_;  }

   void set_alpha(float alpha)
   {
      alpha_ = alpha;
      inv_minus_logalpha_ = 1/(-detail::fast_log2(alpha));
   }

   h_alpha_t get_h_alpha_t() const
   {  return h_alpha_t(inv_minus_logalpha_);  }

   multiply_by_alpha_t get_multiply_by_alpha_t() const
   {  return multiply_by_alpha_t(alpha_);  }

   SizeType &get_max_tree_size()
   {  return max_tree_size_;  }

   protected:
   float alpha_;
   float inv_minus_logalpha_;
   SizeType max_tree_size_;
};

template<class SizeType>
struct alpha_holder<false, SizeType>
{
   //This specialization uses alpha = 1/sqrt(2)
   //without using floating point operations
   //Downside: alpha CAN't be changed.
   typedef boost::intrusive::detail::h_alpha_sqrt2_t           h_alpha_t;
   typedef boost::intrusive::detail::alpha_0_75_by_max_size_t  multiply_by_alpha_t;

   alpha_holder()
      : max_tree_size_()
   {}

   float get_alpha() const
   {  return 0.70710677f;  }

   void set_alpha(float)
   {  //alpha CAN't be changed.
      BOOST_INTRUSIVE_INVARIANT_ASSERT(0);
   }

   h_alpha_t get_h_alpha_t() const
   {  return h_alpha_t();  }

   multiply_by_alpha_t get_multiply_by_alpha_t() const
   {  return multiply_by_alpha_t();  }

   SizeType &get_max_tree_size()
   {  return max_tree_size_;  }

   protected:
   SizeType max_tree_size_;
};

}  //namespace detail{

struct sgtree_defaults
   : bstree_defaults
{
   static const bool floating_point = true;
};

/// @endcond

//! The class template sgtree is an intrusive scapegoat tree container, that
//! is used to construct intrusive sg_set and sg_multiset containers.
//! The no-throw guarantee holds only, if the value_compare object
//! doesn't throw.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c floating_point<>, \c size_type<> and
//! \c compare<>.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class SizeType, bool FloatingPoint, typename HeaderHolder>
#endif
class sgtree_impl
   /// @cond
   :  public bstree_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType, true, SgTreeAlgorithms, HeaderHolder>
   ,  public detail::alpha_holder<FloatingPoint, SizeType>
   /// @endcond
{
   public:
   typedef ValueTraits                                               value_traits;
   /// @cond
   typedef bstree_impl< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType
                      , true, SgTreeAlgorithms, HeaderHolder>        tree_type;
   typedef tree_type                                                 implementation_defined;

   /// @endcond

   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
   typedef typename implementation_defined::reference                reference;
   typedef typename implementation_defined::const_reference          const_reference;
   typedef typename implementation_defined::difference_type          difference_type;
   typedef typename implementation_defined::size_type                size_type;
   typedef typename implementation_defined::value_compare            value_compare;
   typedef typename implementation_defined::key_compare              key_compare;
   typedef typename implementation_defined::iterator                 iterator;
   typedef typename implementation_defined::const_iterator           const_iterator;
   typedef typename implementation_defined::reverse_iterator         reverse_iterator;
   typedef typename implementation_defined::const_reverse_iterator   const_reverse_iterator;
   typedef typename implementation_defined::node_traits              node_traits;
   typedef typename implementation_defined::node                     node;
   typedef typename implementation_defined::node_ptr                 node_ptr;
   typedef typename implementation_defined::const_node_ptr           const_node_ptr;
   typedef BOOST_INTRUSIVE_IMPDEF(sgtree_algorithms<node_traits>)    node_algorithms;

   static const bool constant_time_size      = implementation_defined::constant_time_size;
   static const bool floating_point          = FloatingPoint;
   static const bool stateful_value_traits   = implementation_defined::stateful_value_traits;

   /// @cond
   private:

   //noncopyable
   typedef detail::alpha_holder<FloatingPoint, SizeType>    alpha_traits;
   typedef typename alpha_traits::h_alpha_t                 h_alpha_t;
   typedef typename alpha_traits::multiply_by_alpha_t       multiply_by_alpha_t;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(sgtree_impl)
   BOOST_STATIC_ASSERT(((int)value_traits::link_mode != (int)auto_unlink));

   enum { safemode_or_autounlink  =
            (int)value_traits::link_mode == (int)auto_unlink   ||
            (int)value_traits::link_mode == (int)safe_link     };

   /// @endcond

   public:

   typedef BOOST_INTRUSIVE_IMPDEF(typename node_algorithms::insert_commit_data) insert_commit_data;

   //! @copydoc ::boost::intrusive::bstree::bstree()
   sgtree_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(const key_compare &,const value_traits &)
   explicit sgtree_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   sgtree_impl( bool unique, Iterator b, Iterator e
              , const key_compare &cmp     = key_compare()
              , const value_traits &v_traits = value_traits())
      : tree_type(cmp, v_traits)
   {
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   sgtree_impl(BOOST_RV_REF(sgtree_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x)), alpha_traits(x.get_alpha_traits())
   {  ::boost::adl_move_swap(this->get_alpha_traits(), x.get_alpha_traits());   }

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   sgtree_impl& operator=(BOOST_RV_REF(sgtree_impl) x)
   {
      this->get_alpha_traits() = x.get_alpha_traits();
      return static_cast<sgtree_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x)));
   }

   /// @cond
   private:

   const alpha_traits &get_alpha_traits() const
   {  return *this;  }

   alpha_traits &get_alpha_traits()
   {  return *this;  }

   h_alpha_t get_h_alpha_func() const
   {  return this->get_alpha_traits().get_h_alpha_t();  }

   multiply_by_alpha_t get_alpha_by_max_size_func() const
   {  return this->get_alpha_traits().get_multiply_by_alpha_t(); }

   /// @endcond

   public:

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~sgtree_impl();

   //! @copydoc ::boost::intrusive::bstree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::bstree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::bstree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::bstree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::bstree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::bstree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::bstree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::bstree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::bstree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::bstree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::bstree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::bstree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::bstree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::bstree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::bstree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(iterator)
   static sgtree_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const sgtree_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static sgtree_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const sgtree_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::swap
   void swap(sgtree_impl& other)
   {
      //This can throw
      this->tree_type::swap(static_cast<tree_type&>(other));
      ::boost::adl_move_swap(this->get_alpha_traits(), other.get_alpha_traits());
   }

   //! @copydoc ::boost::intrusive::bstree::clone_from(const bstree&,Cloner,Disposer)
   //! Additional notes: it also copies the alpha factor from the source container.
   template <class Cloner, class Disposer>
   void clone_from(const sgtree_impl &src, Cloner cloner, Disposer disposer)
   {
      tree_type::clone_from(src, cloner, disposer);
      this->get_alpha_traits() = src.get_alpha_traits();
   }

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   //! Additional notes: it also copies the alpha factor from the source container.
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(sgtree_impl) src, Cloner cloner, Disposer disposer)
   {
      tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);
      this->get_alpha_traits() = ::boost::move(src.get_alpha_traits());
   }

   //! @copydoc ::boost::intrusive::bstree::insert_equal(reference)
   iterator insert_equal(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)this->max_tree_size_;
      node_ptr p = node_algorithms::insert_equal_upper_bound
         (this->tree_type::header_ptr(), to_insert, this->key_node_comp(this->key_comp())
         , (size_type)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->tree_type::sz_traits().increment();
      this->max_tree_size_ = (size_type)max_tree_size;
      return iterator(p, this->priv_value_traits_ptr());
   }

   //! @copydoc ::boost::intrusive::bstree::insert_equal(const_iterator,reference)
   iterator insert_equal(const_iterator hint, reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)this->max_tree_size_;
      node_ptr p = node_algorithms::insert_equal
         ( this->tree_type::header_ptr(), hint.pointed_node(), to_insert, this->key_node_comp(this->key_comp())
         , (std::size_t)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->tree_type::sz_traits().increment();
      this->max_tree_size_ = (size_type)max_tree_size;
      return iterator(p, this->priv_value_traits_ptr());
   }

   //! @copydoc ::boost::intrusive::bstree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique(reference)
   std::pair<iterator, bool> insert_unique(reference value)
   {
      insert_commit_data commit_data;
      std::pair<iterator, bool> ret = this->insert_unique_check
         (key_of_value()(value), this->key_comp(), commit_data);
      if(!ret.second)
         return ret;
      return std::pair<iterator, bool> (this->insert_unique_commit(value, commit_data), true);
   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique(const_iterator,reference)
   iterator insert_unique(const_iterator hint, reference value)
   {
      insert_commit_data commit_data;
      std::pair<iterator, bool> ret = this->insert_unique_check
         (hint, key_of_value()(value), this->key_comp(), commit_data);
      if(!ret.second)
         return ret.first;
      return this->insert_unique_commit(value, commit_data);
   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   BOOST_INTRUSIVE_DOC1ST(std::pair<iterator BOOST_INTRUSIVE_I bool>
      , typename detail::disable_if_convertible
         <KeyType BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I 
         std::pair<iterator BOOST_INTRUSIVE_I bool> >::type)
      insert_unique_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> ret =
         node_algorithms::insert_unique_check
            (this->tree_type::header_ptr(), key, this->key_node_comp(comp), commit_data);
      return std::pair<iterator, bool>(iterator(ret.first, this->priv_value_traits_ptr()), ret.second);
   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> ret =
         node_algorithms::insert_unique_check
            (this->tree_type::header_ptr(), hint.pointed_node(), key, this->key_node_comp(comp), commit_data);
      return std::pair<iterator, bool>(iterator(ret.first, this->priv_value_traits_ptr()), ret.second);
   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_unique_check
      (const key_type &key, insert_commit_data &commit_data)
   {  return this->insert_unique_check(key, this->key_comp(), commit_data);   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const key_type &key, insert_commit_data &commit_data)
   {  return this->insert_unique_check(hint, key, this->key_comp(), commit_data);   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_commit
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)this->max_tree_size_;
      node_algorithms::insert_unique_commit
         ( this->tree_type::header_ptr(), to_insert, commit_data
         , (std::size_t)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->tree_type::sz_traits().increment();
      this->max_tree_size_ = (size_type)max_tree_size;
      return iterator(to_insert, this->priv_value_traits_ptr());
   }

   //! @copydoc ::boost::intrusive::bstree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e)
   {
      if(this->empty()){
         iterator iend(this->end());
         for (; b != e; ++b)
            this->insert_unique(iend, *b);
      }
      else{
         for (; b != e; ++b)
            this->insert_unique(*b);
      }
   }

   //! @copydoc ::boost::intrusive::bstree::insert_before
   iterator insert_before(const_iterator pos, reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)this->max_tree_size_;
      node_ptr p = node_algorithms::insert_before
         ( this->tree_type::header_ptr(), pos.pointed_node(), to_insert
         , (size_type)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->tree_type::sz_traits().increment();
      this->max_tree_size_ = (size_type)max_tree_size;
      return iterator(p, this->priv_value_traits_ptr());
   }

   //! @copydoc ::boost::intrusive::bstree::push_back
   void push_back(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)this->max_tree_size_;
      node_algorithms::push_back
         ( this->tree_type::header_ptr(), to_insert
         , (size_type)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->tree_type::sz_traits().increment();
      this->max_tree_size_ = (size_type)max_tree_size;
   }

   //! @copydoc ::boost::intrusive::bstree::push_front
   void push_front(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)this->max_tree_size_;
      node_algorithms::push_front
         ( this->tree_type::header_ptr(), to_insert
         , (size_type)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->tree_type::sz_traits().increment();
      this->max_tree_size_ = (size_type)max_tree_size;
   }


   //! @copydoc ::boost::intrusive::bstree::erase(const_iterator)
   iterator erase(const_iterator i)
   {
      const_iterator ret(i);
      ++ret;
      node_ptr to_erase(i.pointed_node());
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!node_algorithms::unique(to_erase));
      std::size_t max_tree_size = this->max_tree_size_;
      node_algorithms::erase
         ( this->tree_type::header_ptr(), to_erase, (std::size_t)this->size()
         , max_tree_size, this->get_alpha_by_max_size_func());
      this->max_tree_size_ = (size_type)max_tree_size;
      this->tree_type::sz_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      return ret.unconst();
   }

   //! @copydoc ::boost::intrusive::bstree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e)
   {  size_type n;   return private_erase(b, e, n);   }

   //! @copydoc ::boost::intrusive::bstree::erase(const key_type &)
   size_type erase(const key_type &key)
   {  return this->erase(key, this->key_comp());   }

   //! @copydoc ::boost::intrusive::bstree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   BOOST_INTRUSIVE_DOC1ST(size_type
      , typename detail::disable_if_convertible<KeyTypeKeyCompare BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I size_type>::type)
      erase(const KeyType& key, KeyTypeKeyCompare comp)
   {
      std::pair<iterator,iterator> p = this->equal_range(key, comp);
      size_type n;
      private_erase(p.first, p.second, n);
      return n;
   }

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {
      node_ptr to_erase(i.pointed_node());
      iterator ret(this->erase(i));
      disposer(this->get_value_traits().to_value_ptr(to_erase));
      return ret;
   }

   #if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   template<class Disposer>
   iterator erase_and_dispose(iterator i, Disposer disposer)
   {  return this->erase_and_dispose(const_iterator(i), disposer);   }
   #endif

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  size_type n;   return private_erase(b, e, n, disposer);   }

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer)
   {
      std::pair<iterator,iterator> p = this->equal_range(key);
      size_type n;
      private_erase(p.first, p.second, n, disposer);
      return n;
   }

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   BOOST_INTRUSIVE_DOC1ST(size_type
      , typename detail::disable_if_convertible<KeyTypeKeyCompare BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I size_type>::type)
      erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer)
   {
      std::pair<iterator,iterator> p = this->equal_range(key, comp);
      size_type n;
      private_erase(p.first, p.second, n, disposer);
      return n;
   }

   //! @copydoc ::boost::intrusive::bstree::clear
   void clear()
   {
      tree_type::clear();
      this->max_tree_size_ = 0;
   }

   //! @copydoc ::boost::intrusive::bstree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {
      tree_type::clear_and_dispose(disposer);
      this->max_tree_size_ = 0;
   }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   //! @copydoc ::boost::intrusive::bstree::merge_unique
   template<class T, class ...Options2> void merge_unique(sgtree<T, Options2...> &);
   #else
   template<class Compare2>
   void merge_unique(sgtree_impl
      <ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, FloatingPoint, HeaderHolder> &source)
   #endif
   {
      node_ptr it   (node_algorithms::begin_node(source.header_ptr()))
             , itend(node_algorithms::end_node  (source.header_ptr()));

      while(it != itend){
         node_ptr const p(it);
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(p));
         it = node_algorithms::next_node(it);

         std::size_t max_tree1_size = this->max_tree_size_;
         std::size_t max_tree2_size = source.get_max_tree_size();
         if( node_algorithms::transfer_unique
               ( this->header_ptr(), this->key_node_comp(this->key_comp()), this->size(), max_tree1_size
               , source.header_ptr(), p, source.size(), max_tree2_size
               , this->get_h_alpha_func(), this->get_alpha_by_max_size_func()) ){
            this->max_tree_size_  = (size_type)max_tree1_size;
            this->sz_traits().increment();
            source.get_max_tree_size() = (size_type)max_tree2_size;
            source.sz_traits().decrement();
         }
      }
   }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   //! @copydoc ::boost::intrusive::bstree::merge_equal
   template<class T, class ...Options2> void merge_equal(sgtree<T, Options2...> &);
   #else
   template<class Compare2>
   void merge_equal(sgtree_impl
      <ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, FloatingPoint, HeaderHolder> &source)
   #endif
   {
      node_ptr it   (node_algorithms::begin_node(source.header_ptr()))
             , itend(node_algorithms::end_node  (source.header_ptr()));

      while(it != itend){
         node_ptr const p(it);
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(p));
         it = node_algorithms::next_node(it);
         std::size_t max_tree1_size = this->max_tree_size_;
         std::size_t max_tree2_size = source.get_max_tree_size();
         node_algorithms::transfer_equal
            ( this->header_ptr(), this->key_node_comp(this->key_comp()), this->size(), max_tree1_size
            , source.header_ptr(), p, source.size(), max_tree2_size
            , this->get_h_alpha_func(), this->get_alpha_by_max_size_func());
         this->max_tree_size_  = (size_type)max_tree1_size;
         this->sz_traits().increment();
         source.get_max_tree_size() = (size_type)max_tree2_size;
         source.sz_traits().decrement();
      }
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::bstree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::bstree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::bstree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::bstree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::bstree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::bstree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::bstree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::bstree::rebalance
   void rebalance();

   //! @copydoc ::boost::intrusive::bstree::rebalance_subtree
   iterator rebalance_subtree(iterator root);

   friend bool operator< (const sgtree_impl &x, const sgtree_impl &y);

   friend bool operator==(const sgtree_impl &x, const sgtree_impl &y);

   friend bool operator!= (const sgtree_impl &x, const sgtree_impl &y);

   friend bool operator>(const sgtree_impl &x, const sgtree_impl &y);

   friend bool operator<=(const sgtree_impl &x, const sgtree_impl &y);

   friend bool operator>=(const sgtree_impl &x, const sgtree_impl &y);

   friend void swap(sgtree_impl &x, sgtree_impl &y);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Returns</b>: The balance factor (alpha) used in this tree
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   float balance_factor() const
   {  return this->get_alpha_traits().get_alpha(); }

   //! <b>Requires</b>: new_alpha must be a value between 0.5 and 1.0
   //!
   //! <b>Effects</b>: Establishes a new balance factor (alpha) and rebalances
   //!   the tree if the new balance factor is stricter (less) than the old factor.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the elements in the subtree.
   void balance_factor(float new_alpha)
   {
      //The alpha factor CAN't be changed if the fixed, floating operation-less
      //1/sqrt(2) alpha factor option is activated
      BOOST_STATIC_ASSERT((floating_point));
      BOOST_INTRUSIVE_INVARIANT_ASSERT((new_alpha > 0.5f && new_alpha < 1.0f));
      if(new_alpha >= 0.5f && new_alpha < 1.0f){
         float old_alpha = this->get_alpha_traits().get_alpha();
         this->get_alpha_traits().set_alpha(new_alpha);
         if(new_alpha < old_alpha){
            this->max_tree_size_ = this->size();
            this->rebalance();
         }
      }
   }

   /// @cond
   private:
   template<class Disposer>
   iterator private_erase(const_iterator b, const_iterator e, size_type &n, Disposer disposer)
   {
      for(n = 0; b != e; ++n)
        this->erase_and_dispose(b++, disposer);
      return b.unconst();
   }

   iterator private_erase(const_iterator b, const_iterator e, size_type &n)
   {
      for(n = 0; b != e; ++n)
        this->erase(b++);
      return b.unconst();
   }
   /// @endcond
};


//! Helper metafunction to define a \c sgtree that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_sgtree
{
   /// @cond
   typedef typename pack_options
      < sgtree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef sgtree_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::size_type
         , packed_options::floating_point
         , typename packed_options::header_holder_type
         > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};


#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6>
#else
template<class T, class ...Options>
#endif
class sgtree
   :  public make_sgtree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_sgtree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(sgtree)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::reverse_iterator           reverse_iterator;
   typedef typename Base::const_reverse_iterator     const_reverse_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE sgtree()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit sgtree(const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE sgtree( bool unique, Iterator b, Iterator e
         , const key_compare &cmp = key_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(unique, b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE sgtree(BOOST_RV_REF(sgtree) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE sgtree& operator=(BOOST_RV_REF(sgtree) x)
   {  return static_cast<sgtree &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const sgtree &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(sgtree) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static sgtree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<sgtree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sgtree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const sgtree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static sgtree &container_from_iterator(iterator it)
   {  return static_cast<sgtree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sgtree &container_from_iterator(const_iterator it)
   {  return static_cast<const sgtree &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SGTREE_HPP

/* sgtree.hpp
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
*/