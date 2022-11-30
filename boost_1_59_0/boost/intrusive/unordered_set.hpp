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
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::hash_function()const
   hasher hash_function() const;

   //! @copydoc ::boost::intrusive::hashtable::key_eq()const
   key_equal key_eq() const;

   //! @copydoc ::boost::intrusive::hashtable::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::size()const
   size_type size() const BOOST_NOEXCEPT;

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
      (const KeyType &key, KeyHasher hash_func, KeyEqual key_value_equal, insert_commit_data &commit_data)
   {  return table_type::insert_unique_check(key, hash_func, key_value_equal, commit_data); }

   //! @copydoc ::boost::intrusive::hashtable::insert_unique_commit
   BOOST_INTRUSIVE_FORCEINLINE iterator insert_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {  return table_type::insert_unique_commit(value, commit_data); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::hashtable::erase(const_iterator)
   void erase(const_iterator i);

   //! @copydoc ::boost::intrusive::hashtable::erase(const_iterator,const_iterator)
   void erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::erase(const KeyType&,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   size_type erase(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   BOOST_INTRUSIVE_DOC1ST(void
      , typename detail::disable_if_convertible<Disposer BOOST_INTRUSIVE_I const_iterator>::type)
      erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   void erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const key_type &,Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const KeyType&,KeyHasher,KeyEqual,Disposer)
   template<class KeyType, class KeyHasher, class KeyEqual, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

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
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(reference)
   static local_iterator s_local_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(const_reference)
   static const_local_iterator s_local_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(reference)
   local_iterator local_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(const_reference)
   const_local_iterator local_iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::bucket_count
   size_type bucket_count() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::bucket_size
   size_type bucket_size(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const key_type&)const
   size_type bucket(const key_type& k) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const KeyType&,KeyHasher)const
   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k,  KeyHasher hash_func) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_pointer
   bucket_ptr bucket_pointer() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)
   local_iterator begin(size_type n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)const
   const_local_iterator begin(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cbegin(size_type)const
   const_local_iterator cbegin(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)
   local_iterator end(size_type n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)const
   const_local_iterator end(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cend(size_type)const
   const_local_iterator cend(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::rehash(const bucket_traits &)
   void rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::full_rehash
   void full_rehash();

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(bool)
   bool incremental_rehash(bool grow = true);

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(const bucket_traits &)
   bool incremental_rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::split_count
   size_type split_count() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::suggested_upper_bucket_count
   static size_type suggested_upper_bucket_count(size_type n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::suggested_lower_bucket_count
   static size_type suggested_lower_bucket_count(size_type n) BOOST_NOEXCEPT;

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
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::hash_function()const
   hasher hash_function() const;

   //! @copydoc ::boost::intrusive::hashtable::key_eq()const
   key_equal key_eq() const;

   //! @copydoc ::boost::intrusive::hashtable::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::size()const
   size_type size() const BOOST_NOEXCEPT;

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
   void erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::hashtable::erase(const KeyType&,KeyHasher,KeyEqual)
   template<class KeyType, class KeyHasher, class KeyEqual>
   size_type erase(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   BOOST_INTRUSIVE_DOC1ST(void
      , typename detail::disable_if_convertible<Disposer BOOST_INTRUSIVE_I const_iterator>::type)
      erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   void erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const key_type &,Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::erase_and_dispose(const KeyType&,KeyHasher,KeyEqual,Disposer)
   template<class KeyType, class KeyHasher, class KeyEqual, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyHasher hash_func, KeyEqual equal_func, Disposer disposer);

   //! @copydoc ::boost::intrusive::hashtable::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

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
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(reference)
   static local_iterator s_local_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::s_local_iterator_to(const_reference)
   static const_local_iterator s_local_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(reference)
   local_iterator local_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::local_iterator_to(const_reference)
   const_local_iterator local_iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::bucket_count
   size_type bucket_count() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::bucket_size
   size_type bucket_size(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const key_type&)const
   size_type bucket(const key_type& k) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket(const KeyType&,KeyHasher)const
   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k, KeyHasher hash_func) const;

   //! @copydoc ::boost::intrusive::hashtable::bucket_pointer
   bucket_ptr bucket_pointer() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)
   local_iterator begin(size_type n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::begin(size_type)const
   const_local_iterator begin(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cbegin(size_type)const
   const_local_iterator cbegin(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)
   local_iterator end(size_type n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::end(size_type)const
   const_local_iterator end(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::cend(size_type)const
   const_local_iterator cend(size_type n) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::rehash(const bucket_traits &)
   void rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::full_rehash
   void full_rehash();

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(bool)
   bool incremental_rehash(bool grow = true);

   //! @copydoc ::boost::intrusive::hashtable::incremental_rehash(const bucket_traits &)
   bool incremental_rehash(const bucket_traits &new_bucket_traits);

   //! @copydoc ::boost::intrusive::hashtable::split_count
   size_type split_count() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::suggested_upper_bucket_count
   static size_type suggested_upper_bucket_count(size_type n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::hashtable::suggested_lower_bucket_count
   static size_type suggested_lower_bucket_count(size_type n) BOOST_NOEXCEPT;

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