/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_UNORDERED_SET_HPP
#define BOOST_INTRUSIVE_UNORDERED_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/hashtable.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! The class template unordered_set is an intrusive container, that mimics most of
//! the interface of std::tr1::unordered_set as described in the C++ TR1.
//!
//! unordered_set is a semi-intrusive container: each object to be stored in the
//! container must contain a proper hook, but the container also needs
//! additional auxiliary memory to work: unordered_set needs a pointer to an array
//! of type `bucket_type` to be passed in the constructor. This bucket array must
//! have at least the same lifetime as the container. This makes the use of
//! unordered_set more complicated than purely intrusive containers.
//! `bucket_type` is default-constructible, copyable and assignable
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<>, \c size_type<>, \c hash<> and \c equal<>
//! \c bucket_traits<>, \c power_2_buckets<> and \c cache_begin<>.
//!
//! unordered_set only provides forward iterators but it provides 4 iterator types:
//! iterator and const_iterator to navigate through the whole container and
//! local_iterator and const_local_iterator to navigate through the values
//! stored in a single bucket. Local iterators are faster and smaller.
//!
//! It's not recommended to use non constant-time size unordered_sets because several
//! key functions, like "empty()", become non-constant time functions. Non
//! constant-time size unordered_sets are mainly provided to support auto-unlink hooks.
//!
//! unordered_set, unlike std::unordered_set, does not make automatic rehashings nor
//! offers functions related to a load factor. Rehashing can be explicitly requested
//! and the user must provide a new bucket array that will be used from that moment.
//!
//! Since no automatic rehashing is done, iterators are never invalidated when
//! inserting or erasing elements. Iterators are only invalidated when rehasing.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyHash, class VoidOrKeyEqual, class SizeType, class BucketTraits, std::size_t BoolFlags>
#endif
class unordered_set_impl
   : public hashtable_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyHash, VoidOrKeyEqual, BucketTraits, SizeType, BoolFlags|hash_bool_flags::unique_keys_pos>
{
   /// @cond
   private:
   typedef hashtable_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyHash, VoidOrKeyEqual, BucketTraits, SizeType, BoolFlags|hash_bool_flags::unique_keys_pos> table_type;

   template<class Iterator, class MaybeConstThis, class KeyType, class KeyHasher, class KeyEqual>
   static std::pair<Iterator,Iterator> priv_equal_range(MaybeConstThis &c, const KeyType& key, KeyHasher hash_func, KeyEqual equal_func)
   {
      Iterator const it = c.find(key, hash_func, equal_func);
      std::pair<Iterator,Iterator> ret(it, it);      
      if(it != c.end())
         ++ret.second;
      return ret;
   }

   //! This class is
   //! movable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(unordered_set_impl)

   typedef table_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type                  value_type;
   typedef typename implementation_defined::key_type                    key_type;
   typedef typename implementation_defined::key_of_value                key_of_value;
   typedef typename implementation_defined::value_traits                value_traits;
   typedef typename implementation_defined::bucket_traits               bucket_traits;
   typedef typename implementation_defined::pointer                     pointer;
   typedef typename implementation_defined::const_pointer               const_pointer;
   typedef typename implementation_defined::reference                   reference;
   typedef typename implementation_defined::const_reference             const_reference;
   typedef typename implementation_defined::difference_type             difference_type;
   typedef typename implementation_defined::size_type                   size_type;
   typedef typename implementation_defined::key_equal                   key_equal;
   typedef typename implementation_defined::hasher                      hasher;
   typedef typename implementation_defined::bucket_type                 bucket_type;
   typedef typename implementation_defined::bucket_ptr                  bucket_ptr;
   typedef typename implementation_defined::iterator                    iterator;
   typedef typename implementation_defined::const_iterator              const_iterator;
   typedef typename implementation_defined::insert_commit_data          insert_commit_data;
   typedef typename implementation_defined::local_iterator              local_iterator;
   typedef typename implementation_defined::const_local_iterator        const_local_iterator;
   typedef typename implementation_defined::node_traits                 node_traits;
   typedef typename implementation_defined::node                        node;
   typedef typename implementation_defined::node_ptr                    node_ptr;
   typedef typename implementation_defined::const_node_ptr              const_node_ptr;
   typedef typename implementation_defined::node_algorithms             node_algorithms;

   public:

   //! @copydoc ::boost::intrusive::hashtable::hashtable(const bucket_traits &,const hasher &,const key_equal &,const value_traits &)
   BOOST_INTRUSIVE_FORCEINLINE explicit unordered_set_impl( const bucket_traits &b_traits
                              , const hasher & hash_func = hasher()
                              , const key_equal &equal_func = key_equal()
                              , const value_traits &v_traits = value_traits())
      :  table_type(b_traits, hash_func, equal_func, v_traits)
   {}

   //! @copydoc ::boost::intrusive::hashtable::hashtable(bool,Iterator,Iterator,const bucket_traits &,const hasher &,const key_equal &,const value_traits &)
   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE unordered_set_impl( Iterator b
                     , Iterator e
                     , const bucket_traits &b_traits
                     , const hasher & hash_func = hasher()
                     , const key_equal &equal_func = key_equal()
                     , const value_traits &v_traits = value_traits())
      :  table_type(true, b, e, b_traits, hash_func, equal_func, v_traits)
   {}

   //! @copydoc ::boost::intrusive::hashtable::hashtable(hashtable&&)
   BOOST_INTRUSIVE_FORCEINLINE unordered_set_impl(BOOST_RV_REF(unordered_set_impl) x)
      :  table_type(BOOST_MOVE_BASE(table_type, x))
   {}

   //! @copydoc ::boost::intrusive::hashtable::operator=(hashtable&&)
   BOOST_INTRUSIVE_FORCEINLINE unordered_set_impl& operator=(BOOST_RV_REF(unordered_set_impl) x)
   {  return static_cast<unordered_set_impl&>(table_type::operator=(BOOST_MOVE_BASE(table_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::hashtable::~hashtable()
   ~unordered_set_impl();

   //! @copydoc ::boost::intrusive::hashtable::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::hashtable::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::hashtable::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::hashtable::end()
   iterator end();

   //! @copydoc ::boost::intrusive::hashtable::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::hashtable::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::hashtable::hash_function()const
   hasher hash_function() const;

   //! @copydoc ::boost::intrusive::hashtable::key_eq()const
   key_equal key_eq() const;

   //! @copydoc ::boost::intrusive::hashtable::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::hashtable::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::hashtable::hashtable
   void swap(unordered_set_impl& other);

   //! @copydoc ::boost::intrusive::hashtable::clone_from(const hashtable&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const unordered_set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using table_type::clone_from;

   #endif //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::hashtable::clone_from(hashtable&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(unordered_set_impl) src, Cloner cloner, Disposer disposer)
   {  table_type::clone_from(BOOST_MOVE_BASE(table_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::hashtable::insert_unique(reference)
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator, bool> insert(reference value)
   {  return table_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::hashtable::insert_unique(Iterator,Iterator)
   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE void insert(Iterator b, Iterator e)
   {  table_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::hashtable::insert_unique_check(const key_type&,insert_commit_data&)
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator, bool> insert_check(const key_type &key, insert_commit_data &commit_data)
   {  return table_type::insert_unique_check(key, commit_data); }

   //! @copydoc ::boost::intrusive::hashtable::insert_unique_check(const KeyType&,KeyHasher,KeyEqual,insert_commit_data&)
   template<class KeyType, class KeyHasher, class KeyEqual>
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyHasher hasher, KeyEqual key_value_equal, insert_commit_data &commit_data)
   {  return table_type::insert_unique_check(key, hasher, key_value_equal, commit_data); }

   //! @copydoc ::boost::intrusive::hashtable::insert_unique_commit
   BOOST_INTRUSIVE_FORCEINLINE iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return table_type::insert_unique_commit(value, commit_data); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::hashtable::erase(const_iterator)
   void erase(const_iterator i);

   //! @copydoc ::boost::intrusive::hashtable::erase(const_iterator,const_iterator)
   void erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::hashtable::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::erase(const KeyType&,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   size_type erase(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   BOOST_INTRUSIVE_DOC1ST(void
      , typename detail::disable_if_convertible<Disposer BOOST_INTRUSIVE_I const_iterator>::type)
      erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   void erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const key_type &,Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const KeyType&,KeyHasher,KeyEqual,Disposer)
   template<class KeyType, class KeyHasher, class KeyEqual, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::clear
   void clear();

   //! @copydoc ::boost::intrusive::hashtable::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::hashtable::count(const KeyType&,KeyHasher,KeyEqual)const
   template<class KeyType, class KeyHasher, class KeyEqual>
   size_type count(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func) const;

   //! @copydoc ::boost::intrusive::hashtable::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::find(const KeyType &,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   iterator find(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::count(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::hashtable::find(const KeyType &,KeyHasher,KeyEqual)const
   template<class KeyType, class KeyHasher, class KeyEqual>
   const_iterator find(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func) const;
   #endif

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const key_type&)
   std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->equal_range(key, this->hash_function(), this->key_eq());  }

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const KeyType &,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func)
   {  return this->priv_equal_range<iterator>(*this, key, hash_func, equal_func); }

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const key_type&)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->equal_range(key, this->hash_function(), this->key_eq());  }

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const KeyType &,KeyHasher,KeyEqual)const
   template<class KeyType, class KeyHasher, class KeyEqual>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func) const
   {  return this->priv_equal_range<const_iterator>(*this, key, hash_func, equal_func); }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   //! @copydoc ::boost::intrusive::hashtable::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::hashtable::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(reference)
   static local_iterator s_local_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(const_reference)
   static const_local_iterator s_local_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(reference)
   local_iterator local_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(const_reference)
   const_local_iterator local_iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_count
   size_type bucket_count() const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_size
   size_type bucket_size(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const key_type&)const
   size_type bucket(const key_type& k) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const KeyType&,KeyHasher)const
   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k,  KeyHasher hash_func) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_pointer
   bucket_ptr bucket_pointer() const;

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)
   local_iterator begin(size_type n);

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)const
   const_local_iterator begin(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::cbegin(size_type)const
   const_local_iterator cbegin(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)
   local_iterator end(size_type n);

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)const
   const_local_iterator end(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::cend(size_type)const
   const_local_iterator cend(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::rehash(const bucket_traits &)
   void rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::full_rehash
   void full_rehash();

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(bool)
   bool incremental_rehash(bool grow = true);

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(const bucket_traits &)
   bool incremental_rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::split_count
   size_type split_count() const;

   //! @copydoc ::boost::intrusive::hashtable::suggested_upper_bucket_count
   static size_type suggested_upper_bucket_count(size_type n);

   //! @copydoc ::boost::intrusive::hashtable::suggested_lower_bucket_count
   static size_type suggested_lower_bucket_count(size_type n);

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   friend bool operator==(const unordered_set_impl &x, const unordered_set_impl &y)
   {
      if(table_type::constant_time_size && x.size() != y.size()){
         return false;
      }
      //Find each element of x in y
      for (const_iterator ix = x.cbegin(), ex = x.cend(), ey = y.cend(); ix != ex; ++ix){
         const_iterator iy = y.find(key_of_value()(*ix));
         if (iy == ey || !(*ix == *iy))
            return false;
      }
      return true;
   }

   friend bool operator!=(const unordered_set_impl &x, const unordered_set_impl &y)
   {  return !(x == y); }

   friend bool operator<(const unordered_set_impl &x, const unordered_set_impl &y)
   {  return ::boost::intrusive::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   friend bool operator>(const unordered_set_impl &x, const unordered_set_impl &y)
   {  return y < x;  }

   friend bool operator<=(const unordered_set_impl &x, const unordered_set_impl &y)
   {  return !(y < x);  }

   friend bool operator>=(const unordered_set_impl &x, const unordered_set_impl &y)
   {  return !(x < y);  }
};

//! Helper metafunction to define an \c unordered_set that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void
                , class O7 = void, class O8 = void
                , class O9 = void, class O10= void
                >
#endif
struct make_unordered_set
{
   /// @cond
   typedef typename pack_options
      < hashtable_defaults,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4, O5, O6, O7, O8, O9, O10
         #else
         Options...
         #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef typename make_bucket_traits
            <T, true, packed_options>::type bucket_traits;

   typedef unordered_set_impl
      < value_traits
      , typename packed_options::key_of_value
      , typename packed_options::hash
      , typename packed_options::equal
      , typename packed_options::size_type
      , bucket_traits
      ,  (std::size_t(true)*hash_bool_flags::unique_keys_pos)
      |  (std::size_t(packed_options::constant_time_size)*hash_bool_flags::constant_time_size_pos)
      |  (std::size_t(packed_options::power_2_buckets)*hash_bool_flags::power_2_buckets_pos)
      |  (std::size_t(packed_options::cache_begin)*hash_bool_flags::cache_begin_pos)
      |  (std::size_t(packed_options::compare_hash)*hash_bool_flags::compare_hash_pos)
      |  (std::size_t(packed_options::incremental)*hash_bool_flags::incremental_pos)
      > implementation_defined;

   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6, class O7, class O8, class O9, class O10>
#else
template<class T, class ...Options>
#endif
class unordered_set
   :  public make_unordered_set<T,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4, O5, O6, O7, O8, O9, O10
         #else
         Options...
         #endif
      >::type
{
   typedef typename make_unordered_set
      <T,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4, O5, O6, O7, O8, O9, O10
         #else
         Options...
         #endif
      >::type   Base;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename Base::value_traits::value_type, T>::value));
   BOOST_MOVABLE_BUT_NOT_COPYABLE(unordered_set)

   public:
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::bucket_traits      bucket_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::bucket_ptr         bucket_ptr;
   typedef typename Base::size_type          size_type;
   typedef typename Base::hasher             hasher;
   typedef typename Base::key_equal          key_equal;

   BOOST_INTRUSIVE_FORCEINLINE
   explicit unordered_set  ( const bucket_traits &b_traits
                           , const hasher & hash_func = hasher()
                           , const key_equal &equal_func = key_equal()
                           , const value_traits &v_traits = value_traits())
      :  Base(b_traits, hash_func, equal_func, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE
   unordered_set
                  ( Iterator b, Iterator e
                  , const bucket_traits &b_traits
                  , const hasher & hash_func = hasher()
                  , const key_equal &equal_func = key_equal()
                  , const value_traits &v_traits = value_traits())
      :  Base(b, e, b_traits, hash_func, equal_func, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE unordered_set(BOOST_RV_REF(unordered_set) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE unordered_set& operator=(BOOST_RV_REF(unordered_set) x)
   {  return static_cast<unordered_set&>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const unordered_set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(unordered_set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }
};

#endif


//! The class template unordered_multiset is an intrusive container, that mimics most of
//! the interface of std::tr1::unordered_multiset as described in the C++ TR1.
//!
//! unordered_multiset is a semi-intrusive container: each object to be stored in the
//! container must contain a proper hook, but the container also needs
//! additional auxiliary memory to work: unordered_multiset needs a pointer to an array
//! of type `bucket_type` to be passed in the constructor. This bucket array must
//! have at least the same lifetime as the container. This makes the use of
//! unordered_multiset more complicated than purely intrusive containers.
//! `bucket_type` is default-constructible, copyable and assignable
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<>, \c size_type<>, \c hash<> and \c equal<>
//! \c bucket_traits<>, \c power_2_buckets<> and \c cache_begin<>.
//!
//! unordered_multiset only provides forward iterators but it provides 4 iterator types:
//! iterator and const_iterator to navigate through the whole container and
//! local_iterator and const_local_iterator to navigate through the values
//! stored in a single bucket. Local iterators are faster and smaller.
//!
//! It's not recommended to use non constant-time size unordered_multisets because several
//! key functions, like "empty()", become non-constant time functions. Non
//! constant-time size unordered_multisets are mainly provided to support auto-unlink hooks.
//!
//! unordered_multiset, unlike std::unordered_set, does not make automatic rehashings nor
//! offers functions related to a load factor. Rehashing can be explicitly requested
//! and the user must provide a new bucket array that will be used from that moment.
//!
//! Since no automatic rehashing is done, iterators are never invalidated when
//! inserting or erasing elements. Iterators are only invalidated when rehasing.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyHash, class VoidOrKeyEqual, class SizeType, class BucketTraits, std::size_t BoolFlags>
#endif
class unordered_multiset_impl
   : public hashtable_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyHash, VoidOrKeyEqual, BucketTraits, SizeType, BoolFlags>
{
   /// @cond
   private:
   typedef hashtable_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyHash, VoidOrKeyEqual, BucketTraits, SizeType, BoolFlags> table_type;
   /// @endcond

   //Movable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(unordered_multiset_impl)

   typedef table_type implementation_defined;

   public:
   typedef typename implementation_defined::value_type                  value_type;
   typedef typename implementation_defined::key_type                    key_type;
   typedef typename implementation_defined::value_traits                value_traits;
   typedef typename implementation_defined::bucket_traits               bucket_traits;
   typedef typename implementation_defined::pointer                     pointer;
   typedef typename implementation_defined::const_pointer               const_pointer;
   typedef typename implementation_defined::reference                   reference;
   typedef typename implementation_defined::const_reference             const_reference;
   typedef typename implementation_defined::difference_type             difference_type;
   typedef typename implementation_defined::size_type                   size_type;
   typedef typename implementation_defined::key_equal                   key_equal;
   typedef typename implementation_defined::hasher                      hasher;
   typedef typename implementation_defined::bucket_type                 bucket_type;
   typedef typename implementation_defined::bucket_ptr                  bucket_ptr;
   typedef typename implementation_defined::iterator                    iterator;
   typedef typename implementation_defined::const_iterator              const_iterator;
   typedef typename implementation_defined::insert_commit_data          insert_commit_data;
   typedef typename implementation_defined::local_iterator              local_iterator;
   typedef typename implementation_defined::const_local_iterator        const_local_iterator;
   typedef typename implementation_defined::node_traits                 node_traits;
   typedef typename implementation_defined::node                        node;
   typedef typename implementation_defined::node_ptr                    node_ptr;
   typedef typename implementation_defined::const_node_ptr              const_node_ptr;
   typedef typename implementation_defined::node_algorithms             node_algorithms;

   public:

   //! @copydoc ::boost::intrusive::hashtable::hashtable(const bucket_traits &,const hasher &,const key_equal &,const value_traits &)
   BOOST_INTRUSIVE_FORCEINLINE explicit unordered_multiset_impl ( const bucket_traits &b_traits
                                    , const hasher & hash_func = hasher()
                                    , const key_equal &equal_func = key_equal()
                                    , const value_traits &v_traits = value_traits())
      :  table_type(b_traits, hash_func, equal_func, v_traits)
   {}

   //! @copydoc ::boost::intrusive::hashtable::hashtable(bool,Iterator,Iterator,const bucket_traits &,const hasher &,const key_equal &,const value_traits &)
   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE unordered_multiset_impl ( Iterator b
                           , Iterator e
                           , const bucket_traits &b_traits
                           , const hasher & hash_func = hasher()
                           , const key_equal &equal_func = key_equal()
                           , const value_traits &v_traits = value_traits())
      :  table_type(false, b, e, b_traits, hash_func, equal_func, v_traits)
   {}

   //! <b>Effects</b>: to-do
   //!
   BOOST_INTRUSIVE_FORCEINLINE unordered_multiset_impl(BOOST_RV_REF(unordered_multiset_impl) x)
      :  table_type(BOOST_MOVE_BASE(table_type, x))
   {}

   //! <b>Effects</b>: to-do
   //!
   BOOST_INTRUSIVE_FORCEINLINE unordered_multiset_impl& operator=(BOOST_RV_REF(unordered_multiset_impl) x)
   {  return static_cast<unordered_multiset_impl&>(table_type::operator=(BOOST_MOVE_BASE(table_type, x)));  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::hashtable::~hashtable()
   ~unordered_multiset_impl();

   //! @copydoc ::boost::intrusive::hashtable::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::hashtable::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::hashtable::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::hashtable::end()
   iterator end();

   //! @copydoc ::boost::intrusive::hashtable::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::hashtable::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::hashtable::hash_function()const
   hasher hash_function() const;

   //! @copydoc ::boost::intrusive::hashtable::key_eq()const
   key_equal key_eq() const;

   //! @copydoc ::boost::intrusive::hashtable::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::hashtable::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::hashtable::hashtable
   void swap(unordered_multiset_impl& other);

   //! @copydoc ::boost::intrusive::hashtable::clone_from(const hashtable&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const unordered_multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using table_type::clone_from;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::hashtable::clone_from(hashtable&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(unordered_multiset_impl) src, Cloner cloner, Disposer disposer)
   {  table_type::clone_from(BOOST_MOVE_BASE(table_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::hashtable::insert_equal(reference)
   BOOST_INTRUSIVE_FORCEINLINE iterator insert(reference value)
   {  return table_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::hashtable::insert_equal(Iterator,Iterator)
   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE void insert(Iterator b, Iterator e)
   {  table_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::hashtable::erase(const_iterator)
   void erase(const_iterator i);

   //! @copydoc ::boost::intrusive::hashtable::erase(const_iterator,const_iterator)
   void erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::hashtable::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::erase(const KeyType&,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   size_type erase(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   BOOST_INTRUSIVE_DOC1ST(void
      , typename detail::disable_if_convertible<Disposer BOOST_INTRUSIVE_I const_iterator>::type)
      erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   void erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const key_type &,Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const KeyType&,KeyHasher,KeyEqual,Disposer)
   template<class KeyType, class KeyHasher, class KeyEqual, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::clear
   void clear();

   //! @copydoc ::boost::intrusive::hashtable::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::hashtable::count(const KeyType&,KeyHasher,KeyEqual)const
   template<class KeyType, class KeyHasher, class KeyEqual>
   size_type count(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func) const;

   //! @copydoc ::boost::intrusive::hashtable::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::find(const KeyType &,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   iterator find(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::count(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::hashtable::find(const KeyType &,KeyHasher,KeyEqual)const
   template<class KeyType, class KeyHasher, class KeyEqual>
   const_iterator find(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func) const;

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const key_type&)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const KeyType &,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const key_type&)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::hashtable::equal_range(const KeyType &,KeyHasher,KeyEqual)const
   template<class KeyType, class KeyHasher, class KeyEqual>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func) const;

   //! @copydoc ::boost::intrusive::hashtable::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::hashtable::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(reference)
   static local_iterator s_local_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(const_reference)
   static const_local_iterator s_local_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(reference)
   local_iterator local_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(const_reference)
   const_local_iterator local_iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_count
   size_type bucket_count() const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_size
   size_type bucket_size(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const key_type&)const
   size_type bucket(const key_type& k) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const KeyType&,KeyHasher)const
   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k, KeyHasher hash_func) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_pointer
   bucket_ptr bucket_pointer() const;

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)
   local_iterator begin(size_type n);

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)const
   const_local_iterator begin(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::cbegin(size_type)const
   const_local_iterator cbegin(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)
   local_iterator end(size_type n);

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)const
   const_local_iterator end(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::cend(size_type)const
   const_local_iterator cend(size_type n) const;

   //! @copydoc ::boost::intrusive::hashtable::rehash(const bucket_traits &)
   void rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::full_rehash
   void full_rehash();

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(bool)
   bool incremental_rehash(bool grow = true);

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(const bucket_traits &)
   bool incremental_rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::split_count
   size_type split_count() const;

   //! @copydoc ::boost::intrusive::hashtable::suggested_upper_bucket_count
   static size_type suggested_upper_bucket_count(size_type n);

   //! @copydoc ::boost::intrusive::hashtable::suggested_lower_bucket_count
   static size_type suggested_lower_bucket_count(size_type n);

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

//! Helper metafunction to define an \c unordered_multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void
                , class O7 = void, class O8 = void
                , class O9 = void, class O10= void
                >
#endif
struct make_unordered_multiset
{
   /// @cond
   typedef typename pack_options
      < hashtable_defaults,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4, O5, O6, O7, O8, O9, O10
         #else
         Options...
         #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef typename make_bucket_traits
            <T, true, packed_options>::type bucket_traits;

   typedef unordered_multiset_impl
      < value_traits
      , typename packed_options::key_of_value
      , typename packed_options::hash
      , typename packed_options::equal
      , typename packed_options::size_type
      , bucket_traits
      ,  (std::size_t(false)*hash_bool_flags::unique_keys_pos)
      |  (std::size_t(packed_options::constant_time_size)*hash_bool_flags::constant_time_size_pos)
      |  (std::size_t(packed_options::power_2_buckets)*hash_bool_flags::power_2_buckets_pos)
      |  (std::size_t(packed_options::cache_begin)*hash_bool_flags::cache_begin_pos)
      |  (std::size_t(packed_options::compare_hash)*hash_bool_flags::compare_hash_pos)
      |  (std::size_t(packed_options::incremental)*hash_bool_flags::incremental_pos)
      > implementation_defined;

   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6, class O7, class O8, class O9, class O10>
#else
template<class T, class ...Options>
#endif
class unordered_multiset
   :  public make_unordered_multiset<T,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4, O5, O6, O7, O8, O9, O10
         #else
         Options...
         #endif
      >::type
{
   typedef typename make_unordered_multiset
      <T,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4, O5, O6, O7, O8, O9, O10
         #else
         Options...
         #endif
      >::type   Base;
   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename Base::value_traits::value_type, T>::value));
   BOOST_MOVABLE_BUT_NOT_COPYABLE(unordered_multiset)

   public:
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::bucket_traits      bucket_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::bucket_ptr         bucket_ptr;
   typedef typename Base::size_type          size_type;
   typedef typename Base::hasher             hasher;
   typedef typename Base::key_equal          key_equal;

   BOOST_INTRUSIVE_FORCEINLINE
   explicit unordered_multiset( const bucket_traits &b_traits
                              , const hasher & hash_func = hasher()
                              , const key_equal &equal_func = key_equal()
                              , const value_traits &v_traits = value_traits())
      :  Base(b_traits, hash_func, equal_func, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE
   unordered_multiset( Iterator b
                     , Iterator e
                     , const bucket_traits &b_traits
                     , const hasher & hash_func = hasher()
                     , const key_equal &equal_func = key_equal()
                     , const value_traits &v_traits = value_traits())
      :  Base(b, e, b_traits, hash_func, equal_func, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE unordered_multiset(BOOST_RV_REF(unordered_multiset) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE unordered_multiset& operator=(BOOST_RV_REF(unordered_multiset) x)
   {  return static_cast<unordered_multiset&>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const unordered_multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(unordered_multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_UNORDERED_SET_HPP

/* unordered_set.hpp
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
*/