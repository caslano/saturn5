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

      bucket_ptr buckets_init = buckets + received_size;
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
         bucket_ptr buckets_init = old_buckets + old_num;
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
      try{
         if(old_p != bucket_ptr(&this->init_bucket))
            new_p = expand_or_create_buckets(old_p, old_n, this->alloc, new_n);
         else
            new_p = create_buckets(this->alloc, new_n);
      }
      catch(...){
         return;
      }
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

         try{
            shrink_buckets(old_p, cur_count, this->alloc, sug_count);
         }
         catch(...){
            return;
         }

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
         try{
            this->reserve(cur_size);
         }
         catch(...){
            //Strong guarantee: if something goes wrong
            //we should remove the insertion.
            //
            //We can use the iterator because the hash function
            //can't throw and this means that "reserve" will
            //throw only because of the memory allocation:
            //the iterator has not been invalidated.
            index_type::erase(it);
            throw;
         }
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
ux3Znel/h5m1pplFdn0Rfrw0w1cOmQ0VZdjPjddaV/OQ/WqjO3zvB8KuZ9BrujLN6s6ZWPIL6+hx8jtffdvyJKNQejYclknAVOARUd5lnmBMXFFaKNWSlL6r31nYM8TXQV/2+7ZsW+ztwrtkH2rtt/2UvhPMocbVxjP6czXwM/j7UMCr16/itvUg2ceZUWao37pjaXVdreQRTg4QT2/zacNlnRk5RGbxptKxVWdRniW7zma4Ge68a47b1N9YPP7ryOCoKrXW+M1+Uo85xAiz9BSbyN1ZmL1kvE/1X7kVKavza0+bibdAfuPX78m/iDb1R5SOb4v21bGP6Lzj6vp+LdapuYw1F8sATrFc3gP9Djxp/amM+bQLC9HClJTbdAy5V9W2EdK96n8Uv2zq1Tm8ccT3ptEF/w4HvaI/rwr/nLqFyyh8VWbvJZ5YZ3lzxIfdq/hYsh1FfHmQxghnv0r+tK3jmEs8A7AvGOrULSQ/Wh8bOM9jsRtn3dKcfVS8HVWfbo03Igbw2Sv6Rrkl3jHGQJgNRVsRZ7mxRI+ir9K2hvi304n6OL+zYZXV1xSuQldYwbKNA04i3peRly7sw+HtMfxKdPrP1UONierJ3cpAcbT24POD1I2361pyuXXqWqry6dS15LLm1LVc1sJNTAD9zIRWxjxJmvr6s/72+nqa3xZYR28Vnj3+VOQ969ZvmfHSB0UVVw5oovf7YN48dV5Sfcodm3+aMPGODk2fvGsYnxL/9LkliW8VnB7awZvUdMPoM08GfrNR/zZj+98kDPRm40cuYZ74s7Wbz/YreOKWhtnfv/nx7x3G2gC9/XjzpF0jG8YaK74yMeXEY2kJ07DnQ/y/W/P8Lz/9+52nr729d/wPN18ZHvgtSv2bkIHfotS/CRn4Dcm7Kdxv7ngo80ZX6CdTS8Z+q+rNsUUYE5F5zxdL3JVXX37jax1u9vYflPMAxmiU/w99dVnuXtefXn3iwUs+vXfrpgexzkD8pzYnfy31YNXZ9X/b9eMNu3p/B2fZTGHuPbLq5r83D/zl81+eljT0rfQnA79RmR0pzEMerOjbf90H4xLPJEbH/qj4ZYyjQoX5/Qt/7up080ff7bv3xb4p982e1P63KC/UG5gfGKwkZMjxcDJ+Xx8p39dYCrPeoL5+v4eo33T3+TG+f3GAn3l/9ZsUJiLh51fFvF79pvuXGoDfBE1Qv+mO0C3APNDlbP4QKNvv92gO93goxmB+5tP9/M/0+30Z8cu7gmfy7zfxO5d/f2jKtzqP+d5NAd7P3wmgw7577V3yivsbgRHAjcAOwG8D3cCbgX2AtwBTgZuAacDNwHTgHcAZ/D0fuBWYC7wLWAD8GvBK4A7gVcCdwKUiLsAi4APAEuCDwDLgLuAGDvcrwG8B7+H4fB34MHAnf4v07bTe40DecfqiRTzUXU6UvkHAFCFr4HQg0kLxGQ6sBV4KvBY4ArgWOBJ4A3AU8E7gGOA24GWGjE868NvAccB9QvbAZ4ATgC8AJwJfYf6/SX5+GwLlkOPpAg3leOZxPPMNKYcFwBjgQnafAWpk94nsPoziJ/+uZPdL2P1V7P5qIL39wP54rTcBYMD+uEGl7M9e9mcfMBL4Y2An4JPAKH67NY/fbr2CzKWc9wOXAZ8ArgH+lPPvSQ4Xec/31CPeHG4IKInDncLhTmX+HEHMP4P5RboymX8m+ORd4rK8Xg5MAGYDBwLnAEcD57K857G/m6x71Omud/K3M2gt+/uUyGbgM8Bo4GHgfDC/INIDixeBtwN/D9wCfA34JeBzwK8Dfw18gM0fBL4M3Ac8DnwJ+CrwVbKX8Snw3UMOnM3pjKR0yL83OJ0nOH1vA8cB/wA=
*/