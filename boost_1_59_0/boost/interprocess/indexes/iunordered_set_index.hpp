//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_IUNORDERED_SET_INDEX_HPP
#define BOOST_INTERPROCESS_IUNORDERED_SET_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/intrusive/unordered_set.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less
#include <boost/container/detail/minimal_char_traits_header.hpp>  //std::char_traits
#include <boost/container/detail/placement_new.hpp>

//!\file
//!Describes index adaptor of boost::intrusive::unordered_set container, to use it
//!as name/shared memory index

namespace boost { namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Helper class to define typedefs
//!from IndexTraits
template <class MapConfig>
struct iunordered_set_index_aux
{
   typedef typename
      MapConfig::segment_manager_base                 segment_manager_base;

   typedef typename
      segment_manager_base::void_pointer              void_pointer;

   typedef typename bi::make_unordered_set_base_hook
      < bi::void_pointer<void_pointer>
      >::type        derivation_hook;

   typedef typename MapConfig::template
      intrusive_value_type<derivation_hook>::type     value_type;

   typedef typename MapConfig::
      intrusive_compare_key_type                      intrusive_compare_key_type;

   typedef std::equal_to<value_type>                  value_equal;

   typedef typename MapConfig::char_type              char_type;

   struct equal_function
   {
      bool operator()(const intrusive_compare_key_type &i, const value_type &b) const
      {
         return (i.m_len == b.name_length()) &&
                  (std::char_traits<char_type>::compare
                     (i.mp_str, b.name(), i.m_len) == 0);
      }

      bool operator()(const value_type &b, const intrusive_compare_key_type &i) const
      {
         return (i.m_len == b.name_length()) &&
                  (std::char_traits<char_type>::compare
                     (i.mp_str, b.name(), i.m_len) == 0);
      }

      bool operator()(const value_type &b1, const value_type &b2) const
      {
         return (b1.name_length() == b2.name_length()) &&
                  (std::char_traits<char_type>::compare
                     (b1.name(), b2.name(), b1.name_length()) == 0);
      }
   };

    struct hash_function
    {
        typedef value_type argument_type;
        typedef std::size_t result_type;

        std::size_t operator()(const value_type &val) const
        {
            const char_type *beg = ipcdetail::to_raw_pointer(val.name()),
                            *end = beg + val.name_length();
            return boost::hash_range(beg, end);
        }

        std::size_t operator()(const intrusive_compare_key_type &i) const
        {
            const char_type *beg = i.mp_str,
                            *end = beg + i.m_len;
            return boost::hash_range(beg, end);
        }
    };

   typedef typename bi::make_unordered_set
      < value_type
      , bi::hash<hash_function>
      , bi::equal<equal_function>
     , bi::size_type<typename segment_manager_base::size_type>
      >::type                                         index_t;
   typedef typename index_t::bucket_type              bucket_type;
   typedef allocator
      <bucket_type, segment_manager_base>             allocator_type;

   struct allocator_holder
   {
      allocator_holder(segment_manager_base *mngr)
         :  alloc(mngr)
      {}
      allocator_type alloc;
      bucket_type init_bucket;
   };
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Index type based in boost::intrusive::set.
//!Just derives from boost::intrusive::set
//!and defines the interface needed by managed memory segments
template <class MapConfig>
class iunordered_set_index
      //Derive class from map specialization
   :  private iunordered_set_index_aux<MapConfig>::allocator_holder
   ,  public iunordered_set_index_aux<MapConfig>::index_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef iunordered_set_index_aux<MapConfig>           index_aux;
   typedef typename index_aux::index_t                   index_type;
   typedef typename MapConfig::
      intrusive_compare_key_type                         intrusive_compare_key_type;
   typedef typename index_aux::equal_function            equal_function;
   typedef typename index_aux::hash_function             hash_function;
   typedef typename MapConfig::char_type                 char_type;
   typedef typename
      iunordered_set_index_aux<MapConfig>::allocator_type      allocator_type;
   typedef typename
      iunordered_set_index_aux<MapConfig>::allocator_holder    allocator_holder;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef typename index_type::iterator                 iterator;
   typedef typename index_type::const_iterator           const_iterator;
   typedef typename index_type::insert_commit_data       insert_commit_data;
   typedef typename index_type::value_type               value_type;
   typedef typename index_type::bucket_ptr               bucket_ptr;
   typedef typename index_type::bucket_type              bucket_type;
   typedef typename index_type::bucket_traits            bucket_traits;
   typedef typename index_type::size_type                size_type;
   typedef typename index_type::difference_type          difference_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef typename index_aux::
      segment_manager_base             segment_manager_base;

   static const std::size_t InitBufferSize = 64;

   static bucket_ptr create_buckets(allocator_type &alloc, size_type num)
   {
      num = index_type::suggested_upper_bucket_count(num);
      bucket_ptr buckets = alloc.allocate(num);
      bucket_ptr buckets_init = buckets;
      for(size_type i = 0; i < num; ++i){
         ::new(to_raw_pointer(buckets_init++), boost_container_new_t())bucket_type();
      }
      return buckets;
   }

   static size_type shrink_buckets
      ( bucket_ptr buckets, size_type old_size
      , allocator_type &alloc, size_type new_size)
   {
      if(old_size <= new_size )
         return old_size;
      size_type received_size = new_size;
      if(!alloc.allocation_command
         (boost::interprocess::try_shrink_in_place | boost::interprocess::nothrow_allocation, old_size, received_size, buckets)){
         return old_size;
      }

      for( bucket_type *p = ipcdetail::to_raw_pointer(buckets) + received_size
         , *pend = ipcdetail::to_raw_pointer(buckets) + old_size
         ; p != pend
         ; ++p){
         p->~bucket_type();
      }

      bucket_ptr shunk_p = alloc.allocation_command
         (boost::interprocess::shrink_in_place | boost::interprocess::nothrow_allocation, received_size, received_size, buckets);
      BOOST_ASSERT(buckets == shunk_p); (void)shunk_p;

      bucket_ptr buckets_init = buckets + difference_type(received_size);
      for(size_type i = 0; i < (old_size - received_size); ++i){
         to_raw_pointer(buckets_init++)->~bucket_type();
      }
      return received_size;
   }

   static bucket_ptr expand_or_create_buckets
      ( bucket_ptr old_buckets, const size_type old_num
      , allocator_type &alloc,  const size_type new_num)
   {
      size_type received_size = new_num;
      bucket_ptr reuse(old_buckets);
      bucket_ptr ret = alloc.allocation_command
            (boost::interprocess::expand_fwd | boost::interprocess::allocate_new, new_num, received_size, reuse);
      if(ret == old_buckets){
         bucket_ptr buckets_init = old_buckets + difference_type(old_num);
         for(size_type i = 0; i < (new_num - old_num); ++i){
            ::new(to_raw_pointer(buckets_init++), boost_container_new_t())bucket_type();
         }
      }
      else{
         bucket_ptr buckets_init = ret;
         for(size_type i = 0; i < new_num; ++i){
            ::new(to_raw_pointer(buckets_init++), boost_container_new_t())bucket_type();
         }
      }
      return ret;
   }

   static void destroy_buckets
      (allocator_type &alloc, bucket_ptr buckets, size_type num)
   {
      bucket_ptr buckets_destroy = buckets;
      for(size_type i = 0; i < num; ++i){
         to_raw_pointer(buckets_destroy++)->~bucket_type();
      }
      alloc.deallocate(buckets, num);
   }

   iunordered_set_index<MapConfig>* get_this_pointer()
   {  return this;   }

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Takes a pointer to the
   //!segment manager. Can throw
   iunordered_set_index(segment_manager_base *mngr)
      :  allocator_holder(mngr)
      ,  index_type(bucket_traits(&get_this_pointer()->init_bucket, 1))
   {}

   ~iunordered_set_index()
   {
      index_type::clear();
      if(index_type::bucket_pointer() != bucket_ptr(&this->init_bucket)){
         destroy_buckets(this->alloc, index_type::bucket_pointer(), index_type::bucket_count());
      }
   }

   //!This reserves memory to optimize the insertion of n
   //!elements in the index
   void reserve(size_type new_n)
   {
      //Let's maintain a 1.0f load factor
      size_type old_n  = this->bucket_count();
      if(new_n <= old_n)
         return;
      bucket_ptr old_p = this->bucket_pointer();
      new_n = index_type::suggested_upper_bucket_count(new_n);
      bucket_ptr new_p;
      //This can throw
      BOOST_TRY{
         if(old_p != bucket_ptr(&this->init_bucket))
            new_p = expand_or_create_buckets(old_p, old_n, this->alloc, new_n);
         else
            new_p = create_buckets(this->alloc, new_n);
      }
      BOOST_CATCH(...){
         return;
      } BOOST_CATCH_END
      //Rehashing does not throw, since neither the hash nor the
      //comparison function can throw
      this->rehash(bucket_traits(new_p, new_n));
      if(new_p != old_p && old_p != bucket_ptr(&this->init_bucket)){
         destroy_buckets(this->alloc, old_p, old_n);
      }
   }

   //!This tries to free unused memory
   //!previously allocated.
   void shrink_to_fit()
   {
      size_type cur_size   = this->size();
      size_type cur_count  = this->bucket_count();
      bucket_ptr old_p = this->bucket_pointer();

      if(!this->size() && old_p != bucket_ptr(&this->init_bucket)){
         this->rehash(bucket_traits(bucket_ptr(&this->init_bucket), 1));
         destroy_buckets(this->alloc, old_p, cur_count);
      }
      else{
         size_type sug_count = 0; //gcc warning
         sug_count = index_type::suggested_upper_bucket_count(cur_size);

         if(sug_count >= cur_count)
            return;

         BOOST_TRY{
            shrink_buckets(old_p, cur_count, this->alloc, sug_count);
         }
         BOOST_CATCH(...){
            return;
         } BOOST_CATCH_END

         //Rehashing does not throw, since neither the hash nor the
         //comparison function can throw
         this->rehash(bucket_traits(old_p, sug_count));
      }
   }

   iterator find(const intrusive_compare_key_type &key)
   {  return index_type::find(key, hash_function(), equal_function());  }

   const_iterator find(const intrusive_compare_key_type &key) const
   {  return index_type::find(key, hash_function(), equal_function());  }

   std::pair<iterator, bool>insert_check
      (const intrusive_compare_key_type &key, insert_commit_data &commit_data)
   {  return index_type::insert_check(key, hash_function(), equal_function(), commit_data); }

   iterator insert_commit(value_type &val, insert_commit_data &commit_data)
   {
      iterator it = index_type::insert_commit(val, commit_data);
      size_type cur_size      = this->size();
      if(cur_size > this->bucket_count()){
         BOOST_TRY{
            this->reserve(cur_size);
         }
         BOOST_CATCH(...){
            //Strong guarantee: if something goes wrong
            //we should remove the insertion.
            //
            //We can use the iterator because the hash function
            //can't throw and this means that "reserve" will
            //throw only because of the memory allocation:
            //the iterator has not been invalidated.
            index_type::erase(it);
            BOOST_RETHROW
         } BOOST_CATCH_END
      }
      return it;
   }
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Trait class to detect if an index is an intrusive
//!index
template<class MapConfig>
struct is_intrusive_index
   <boost::interprocess::iunordered_set_index<MapConfig> >
{
   static const bool value = true;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}}   //namespace boost { namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_IUNORDERED_SET_INDEX_HPP

/* iunordered_set_index.hpp
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
*/