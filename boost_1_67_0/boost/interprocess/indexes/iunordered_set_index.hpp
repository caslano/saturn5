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
7Y0LHsPd08Nyz/bGNbsZZMbVrQyf6DzoGeN25PuyeieUzhxwMPm4x2WvzY9Q1IytznkwcPxs07H8afk+b7hzVb5PJ5iYDFe9T4uVb2T1ntnnKGOd+3NvdoXjw84jngkQZMCRhGNjjp91T8r3iYmGG6TGxcTEbM+SOxPTPN7uZIoPAIp97uR+Ngxq/saScGcgbCmOcoRpkiKmeVydRHv9yqMue71or6XMOe7JMsy8gzo9dcnWsuz2bpJoQFVC6dXtzux6nSNs7HsbMZ9ZNaAD4m49ld1BSaPtrP9AnfKXoug5wHbCLTSIVfRpK0+craSoKBIscbYq6eKcX0dJ6tFRnRAPHv+ZpKIqp/tjWn3Tt2KGxz3rbZ+YINb0OUI2MX2/SIJGCXWuBFE4cfx8wOZxZnsMLqFu1XHRl6UvO6932/2PDqix1q4yiYNdjteQnvNe8+mcsnHiSlkcCoEnu8drMitdzSxbrSIRJfeAgzxZqTRQuPm38z2q/4NsyhQrtNl0nmfTZGeNZzwimHBsQI2aTYPdSV2sLUuM1hvIA3ZMpiuRei/e3pRdvZSsWhKWELBeoZxqCVtqSAhMcA0Wj6Ss/IF6Byx77jCItloEnd2Bcqo1f8QOmymC7tFK/NxTwoLp/X8gubP0CadnyFPREjC5rD030K953Ye6YK3anmvHmG+OWMYl1hSQ/xPlo+c2EtDAxCQjk10uZ2B+ufN96Mb8J8SsgZjnNWKeFO0ecZXbJx7pU8OFvEQ+UdQnh2f2CZL4+M+qpNl1q2r/M5ImlM5GMWXJevycaK9qOtW9mnQeCRR1SuywhbyjMnzO68lCB9F+WEy75pppdHXytndejxPCycfVjRvzj0kXSzXTPP8lFOqO/w8VarGiUHf836ZQd/y/rlBL/osq1BKmUIv+qyvUUqZQi9oo1NL/wgq15PcV6p7/vEJ9+yuNQl3VRqEmVKcnNLpsBaItevx0l229O5v01jqXsNFl3+Gyb3PZt7jsm132TS57scu+IdHeV+gq+auDpvNt3bHYQk7CJjq2SaYHgACAQ0sBAID/f9w0iyutqFCfFOeITmrnMCW1dxiTOgiGMV7v1M/jC/VjnNejzGt76NmR4F/usFjcKUdyrpuWR1Dpnuj9UbT3FduJLnb/Y7sRYUJ4VvhMb7V5b6lTGuDomZLi6IBL1vJXoaTVeIvZjdLroP+9W5zz1+no3fsWcXQJ24jpsu2h7HD60qdJAxx3Jg1y9BpR7vgqaaz5xfuIWZJtdfuB85LCzGvvwG7XCK9rYlaUN48LZ35hDuvdtuFlzsPOhBHlfGxcTCuSMZFLAXv/kJS45g/O7B3dlrYP2HbcU14QOcFrCNiKKfIjyrPP3sIHax5JphdJpkIZA+xEC0YuYYtwlzciYOeUjkZvLHH+hnGOUjmrX7MbvF/dU04kSe3Ma58mJllGeTtGVye2uOxFSiJHZrWTX8epTjw94yg9LSw90XvPMskvY9TevjGQFTlTnkLurEh5NT1cwmavgctwfeDgJNOykoneuzjLZR+PKPfuc2bH6RwTOFf3xAAF6DhAvHeIR53Z26jZW++ymPNwRHxW7IxE245llpzspvBVhhZb08OULi7bDsTY/ML3hPDOzGo/c6Lzentz/hHclbWXAk+o9najmMctqm5v3utzTxpcm3s9NUanW9OOR/2cN3zXlBjYAJu8UUmJ5pcycGAq+3RZnoIJHPsOCufhnFE6xzW37UBqQNjBzlzb0xmN8qaEY9SBT0zbmK1vqjPYihPTNgsGgy02MW2LYBhg6zESYZlfuoOkG1nsxdbiQeTcVYVxIHmuy1aEqwolKtHZHZrqdvVP7GIhP/qSmBYjROBiI9uBxLQic97XOASKqmQejswrKssuMjjLpjk9kS57Hjhsos+LSqPdPcL4AV2JhiUdxavu7BKyPQL23e6MEjGtBmfNUYLB2nDZ6s07x7YXfQlCzS5YO32O9inLPQ9ath7dHW1xCevNO6szrd+anXE4jtxaaXZ2Jce+3/bh7Yh5LVrxvftG8bH5DuBeReLKHbBpuDHTelLoPbrJdhgKUeicKFQJlkThgBDFIlUj/4IzXa0Vwh2jm8aaGKZr4lKjcFtigtDRJRx2CVUu4YB8gFWLje7sukrbtnBmBm0U07YZSl1pm/KPrX7EPS78gMu2xT3W5LJtFul/2hbzztvIhnPOp0Lx6X5xerN7iJ6aSKPVh3Z0B9pRVkWWNzsMmYFIp22L3vnUZn3AvsmZvUm35itnpT5g2xiwb0PpW7M+t0xfSoLmV69+QMyuzw+sGCAKdaLtxNH5J8qk3uJJQ2OUr+yX3m7jqKj9uWVs8b2A1CWKNTX4sXNfcq4cI5Y11Zl3+gw1jbYTYRhyLMb6wOw6Ma3u6FP1ZZ7eRy9F+Yl52dneR6Wo/ZMxxWU7IRxNFIod4ZlO+wk1d20nlncS007knsW1WLk3dDlhOmGIM/tkQCBD7iRF8LuA0MM5/zvdbhZ2YtoPQiSl+g+jvR0zA7YfvKaA7TuolZMlAX7Q3JI+CaUJ1cR4PWWieUMZ5eODvJ3ILdPlBNaQxey1Zoq2k1H29SiTIopQBUnvsh3MdNlrvL0oW/MbzRtKnfOrdCn9QBkOQuf8AzqX7bAzu0hHmgKXwNnI9rYfEIUKMe1gmWTx3ldp28CmCXolNDJxdoM4oZq82UnXZnIg1xKqsVo+oVHMLoiyrct0mTNdE9qLtg2u5XrX9IjgrtlrO9BQuR/UvfmJxXKB/h741GJZSH8f099P9Hed/h4ptlhG0t9u+vuU/mYXK9cwOC84Wts2806cW5Jm2YVE71M2VczoQaXMPTqQ3qc205m9WTfdlbGp0laLNQuVthP8UXf48M1R1K6wheARFWP1g7xG+o3DSbbZpsz8Y8IDlE75OMU8P2DOr2RGTmaifXOmy2B+rbSlqm8HY1zBWH1m5VhDWHzF2HAcLSNHmZBNteZ8jBFSD4b8CI9p+hxrlRDBlih0b8IlP8nC7QtLbTEW71R1t8Wc26mBPUaFYLMjhh2BXypEY0h+0MIS4DoSgzvx3nNhMb27xxqzuqRKsdXq5ExJxVhDuLf7wm2tH29WqR/foo+kpuRFkdiFdlA89US1xc5O05Biy7wmt3HsolK7O88U/e89F8r8lJooZS67x7yvTtWBTadJh2e60n5xCedd2Wdd9o1cneWfXmkugUJ0SgyzEYvBndiqb9s4TTxUdtPgPBNpzlsAzVcdbbBvFMtc9j27eAUxLekkUtfrwNatpLJJA1a4bHswP1lCnTx05+x+dADFowlpv+xlnb2zrB+Ytk1M+6XPyT417iGdzDtb9vLacdLs/DvTgDVm5zvQeVwDtpjXrm/VgC3LLWQFCZJLaHAJHhn3vChKcEKTTVKVYAOUoEdRgr/IRUwJ1gi3T2hK5kqwXeJio2BMjHfsuEMocgvXKm2lTO3Zi8S0UkO1K62Y1F6ae1IHj7PU5LJTdd1ATaR5p4lqAqk9Mb3Z/GmVc/4WndvY3rqf1F4Z1N4Wrva26FzjmdqLcNrWk9rbQGqv2JldTGpPtO3BRYC2ooC91Jldqlvjzq3kmi+w2tpkw2K1HGEQzgGy+47O94m1htIyuXdUGTud1E8a0FBKCpDvPrL5iWrNQfzYuRc5SftVQvuVGvyNNh/TfiWi3S8K18jsPPqUv+xM76MXoy4Te2g/OepgikugfPKR9rOVMO3nC2o/H2k/uy/3DNN+11Xtd4VpvysUz0am/Rp1u7j2s99g2u/GBKb9bkD7NUL7XVG0n9/8/N9ZNWQacJvL1sA0oCdEA0oJjdYfzPnZUGJ2qUy27MYAgcLjoPn5d3HwRMZ3ZFwlHKN8cqX5XGRQp/nFtO8STvWp6lObew7yu4e0d2VQK9WI6xSdk/S8YjtxlEUJL1g+89qheOMFy7f8IXZILAkkJ+rZEpErUdnbMtlGimsu21kRNyCdz3Rl/8Jm/ikajZmJwjbSxRo97LJJ8p9/Y1eoUn3vOV4tk7cn2hqEjok2j9COlcjvWImsFWIJUccQ9PEEFUtbrTkPp9CTeeLODhZLW5FoL6XW2F5CLeRDbnsdGfzUJntE+zbzTqru7Zzz91A7fBDtcI/21u+oQJ5CgdzDC+QenWuO0g4/tQ2HQQXsJc7sEt2afawZDhbGv+VW8MLYiGbYz5rh3yuKwZa4IlgQG9EMN1JBrOAFsZEKYgUviD61IBajIGZrCuKlqOvagpitFsTi/z0Fcfx/UBB9wWZ4y39YCFkzfCVK2HJrARB+4c3wadYMN7Rthj3YXtNoiw0T0zaJth1idkymS++I32ig1FzzR+gjvRqrzZmVY6jtaW2NxugrxoTr5KXYBBbovNqQ1XmOKEhlFy25F1tGsfaLig5lqokVCY+Y0SDaG47O95CFZDgdReYS1RYoiLKAfY8rowH7fOooI+5v+iH3POZYVvcniEL1lAQ7yAsqD7JCiiqbzGg8lIt17glh7keNrgyqEDtw7zA7OCyN0qHBLXiYvt9K4YrZHoROhSFaF3VQTJNEX9lF7JA8KZa5h7QjsdzRt4lpB8ou9Y6qonCimtxJequfDbbEuseHJRyzViwJd/oxqHJsjOjLP+YIGy3aqtwx8a60PdaTBKxdGjbaYD8MxVcdddA9ZBQpfVHY44JiiDU05pTFi5UUTpSvIGos9SB4r6yhwualzsBD7EqGgNOrTxqa3ZEqkHdcjjVRaFdhiH/ImlG69Ap1K/A0js0M6FoM99TleA3mvYcKZhgqxoUZKYXXBRewRBTB2smxxgvhD1HNagTlqaX/oubeZdnNszNtc0WyIcz82v6WgzlnO+TsjytI1VeQZZFMOfpeEzRCY7nFEZbcWI6D2auMjeU4sb3K1FiOA9urLI3lYXjGNZWzq/LIqRcP7Wan1h9M38sOre9DZZ8qtKOLtcYRZT0o3N6BHeEezc5u94azI9vFQyjIBp0jGjYIVZSIqAqvPmr/bPA16hyEsuh05STNfosjvIRE101Nn/4V+DfuNzn0UeWN+40Ozqtxvx4uE1xhCuU+SNC0n8moj6oUD+5lItY4eluPkGCHSLAaCDaXC5bMBYujvhhGb+b0OTr7MXb7UpijC3vqHe2tRwVzByRiubMqubxDMlzqgfAkG44mzhQzmhOOsSTKsjzKk+6giSflQSMSlp76xvI4PMOQpBG5ByGjeechsWwvO/a9Yh8kdfTlZ7935We/m6hrdFvUt96OBGfn/9KTItjniMNC6YeJW3whL/aFPMw7yz9EOvAAqJRk49BkanNr++zvcwTaMRodxU9QYeqkSHY8My7PO/WUnyLiFzP8/+vx6FPh6M+l765eglAhdMGtTyR5SAyoFCC2/0EsqDBo4uBKixb3JzQmDsXBy+Y8HNGd+3Nvg8ngyr5g/gRHDfrySleSxLM/ZOXQ4KwxsXlsuIwfMlHIpecJQ66wD1k5jcitgexi1VcoDn0OOe4haagoOHrQM5nJf4jkr1Hkr1HkrwHxPhSDPpVOKdnRY1ApqW2MKiUzNEWEoak8MTRFCIdC1/axmZqO9TkZVUvWYKRYIWMxnXQ7rjemJkv629ZAYCbFhpqzawnH8qoRn0fJlOcROmgiJ4/RQSM5eZQO6snJ43QwbC/Eyq9Rc4SyoxyFKY5nB49OuXCbkh3tlezQR53sc8QpJzt65spKNORklmk8GgeVaBxk0dgvViXYo6Ns0U1llP6stlLT0roWzXmhRzrbTNMg6fdjSauF+jv5pQ69Kz6/Uegrmb4MjvfdGRkI5GT7sJ3GdoFv/5I9WEKZHUOS0q9+VS399l1zkG3FszdMLeyF/fzOXfyMh67YbW7+sjzLlCqdXABbrIEfM/EyOwrjy3LzTuMYpwcb6cILe0/wVubcHEQ9JHus3huec3OAYCBP0RZDrUcBW02NBRfjmaOv+SUsoaFuzT05N+Md7SptMe3RAx1WGJm0wtEhaQbzQiPn7UMOthSuvdNvEToTXLAwlDFphhBROCeM7BdnFXW7moQY8R8QjAxB85eHzDujJ4tHnWeNDhNpdKcc7+2We8aAMhnvfujdnOvdyHe5wSnHOcuqrfaYpX8guU2JtuYl/YVwq92/7A56N+L0D6GPaIt9eJtJiGNngRiouiO5vI+JadQDSIsxHHWlNSP6hXthxW0zCt23hQkjnR69o11uNjac5CxvRzEdkCg0L7tLWki9ZhgHfNWQg5KrOeA1k48+SzeDDAFDBRvrtbAsHQ5/h6Epo7lNPoq2Zm+siokPyeLWxTUJ2FKnrFhMDMeRG0LkwgvxXSzesFTp09/aLv21TFU2Ehbtw/kyloTTVDNvb7t5UN6uwypVk3CX9N7nwWL2lZEveVZx7BRLOUfHDxL+Jp0li7Vm2W3Sk61ELxhxghgO9ZxhwsLKmCnKEo7HI/ilg8MCi43woz/TwjAqAYHF0Wwdu44B4rDFTxuqWOE1O0tbtGu026zfVFdudghodw3i0sSExuniSOxJcAnNYqS1wjFf7InVrbghPSuQmp4eOI7dthWOaVmUbi9F8iUmzeQxlr4J/tSsQOABoCg7hrnZ8UQjIvnNiis7UaY7KNxm6donLYGZFIKz0ohAhPfY1sTqcqxlaQTgOABeHxMrU0zryG4mEKsy+xxFL2FQcO2j8d1AIAVLLVMc0SnKlRhZeq8+yzgjo5wdYZ9RjrsT+IQrhkF6qjcT8NGLjhgcwyKj9U4pJ6OcXW6g3Dcilj0bzb9Rp5f4wt0P3eVwaL4MdqxEloH+L8T4x8IqqpqBznE7Olnex3K7cnXRHSkXf4sjUjlcXS1hKLFsk2OlrXkyKUtXrGuG0TXDhLXtL2AtdkK1K8OCwQQJ87hH3UntmGHZHYalxTnfohOviqdc2X7VwhT8hmoYlkfE6y67nxmakqGxzNs76pDhpCvetcLoSjGRDRluTZPQFbLwrpBF57I47iZqsCR1Z20JTsC2IlYYHcbRRC4KFxisxwPWH8kY/aEtaoaCMth9zvl+nXjTUC1eYSJBxtMk5Q/0lQ2D4NYel4UozHsHu6PvdwmS9SAxrAFDP2fo17lMjr7uqWHU/T1OMt2AVdw4XvwOZ4w0OtpTr2mMK83iSjUF7NGUJAGbyZkdDSnIy7x2P1aGn0Z9ukdMNYqmXFuzD9tcboiXqQNRdtZSdskSdbLsjAXnnZisNx31uFpqhampEgVFiBdTjGIsEbG9MZfF44hCgJvdLdS5OEj5lWJ0qXjH8UxmG2e6Utq3tk0DtfNVuMeKej+UZ2wjd35g9SjxyIM5w8nmSs6vFn51VmMl14Ayg99FKCGW+pz3iDXi/t+D+FxCrLeTMxDIPkl6CEPazpbAqmtsli+7h04wiQa+XTY/4MBesnzsabS2CNgSI3+FwnV6rPXq6kixXMZFeNabq9n1HzjcGDtRO5v4etD3SchBzmxJv+RMTvZFndt20VFXmBqWd8xxVLTXF7YbYVpiHHFw2UfUgSYhhQbvbhJ6CCPYqhJs4gSviXYPIzCNOGh+AXf0KkQeGUt4+bZeLK6cHhDqs9rxjbx1rowTGH2LJcQ+WCOrk7M8CcdmNF11+vVLhrjHdTdZK5ffLk2VSUkfIIE1O3pbPmxhx6e17uhtc3SYOa+8hV0/18BWstcHd/Sa817S4cBIZZW7JyhL/mnHitWjNOEnBMM/Lt0a/upbwueXKVCODJ46XeEd3EbcFV4nmDTQy4HOyWyHRd10adflq4GZ9EEqJodoq5vpnl8V3FW85p3f2VV8vYTtKhbTegSEOPLQrtaX/sIautjfPYeqtdX7klhQlaJW7/gtrd7OYKu3vSjYgH39W8vvtHrrQlq9k9TqLWslWk9E3oew/SrFQs1rZzRojygN01cl2Ktj8Y4KLDaRP7wfUdu+KalSO9ZuodnrLvUNcvzPtoDKNjzvHdPZIebn/eqwcgcxotAYmTTS0TOv1NFN3Ul3SqwYEA6CMr++qQ6LT1vflSZqynTRn1AqHqHcnZQY6WjnLDMmOxN1QlN6Mm5NWaijIu6biRaPzFJTVjupEO2bGImjQQe0pEoz9Tg3BwEaH8AC538776L+dvPs1oPPYviWftxQUC50lu7bHkzGB5tb2BrQp9PF+OkUgvWqY2rWyHQpEqfr+inQ7Auk3pKtTY6khNLhc8JwxLLN/x4iYA03Yjtie+kBSs/3mU+5MBdZ1jexJ9uY2EM6S311EnOitOcjNUgKjbXWiRl+cz52NGUZ2QmlMxUWjh9csZxeuJ0+9WOfTPxTuSuWp75L8JGkOwZkN6O9n4fdOv6Z1purHkns5ZjsHrI3MEyq+YAIKRChO6WFC9vGXLEylrrgZB569U1wDylJ7CX42Ia3UUuzsozTA4y5tD7A9npRgGneyUxODGdZb2brm350T9BbK83rhhEN5pBHmZ0DsJ8jy6jQTlNpzXm3sWnyZnd0iauTa6YRrVY3Fkmk0VOi0JwVli713YlDiEr1qVJOSwtiQdFwkKUkRakfpkvJxWoZewSDfpUDKgy2CwWxyVgY0XS0T9WU6YHOA/lJh2an/VpAmvyhuoloulSxlaeDoyOSqmQrOjqmmdgVdI3tRsIRalOlS9dR75uljcHvVFuntSh73ajsoNZi5+mf0rFpVHrqS+XcpeNbglJjl2T6dOmVT1VpjWKlN5rzf+k61iG3HkLG9YUF+uKFHSxI0hflQpz06rZg2fz4elu9QKEvTheFa4mzTcIIdtABJpZmzvSONH95tHHc/T2Njj8kF1pGHHeMMO+sNn95rOyMKeogdnNEpXi7mXceTUyLdrRLNn9pwl4s6tZU41tHBNFVqeXejm0DbGP3Mt3yJ6Y8ojUnLfF/7jGBx8rdW/qSRDr3vL66hNLCcX1NOGPNgyOTTE37cWKSo3Nhe+f+sBGHHEfyqh1TuKfgjaqbLpaXnbOkR9WJ7fcFWlpWi2ViU8Ihg89w3Xk54PQFEo4kVOD2ozO6sLBcoUc/PBzH8QgTTLnn2UzHgdlzHksoLRfHNI8odwwjJXRpxDnH3XkNjp/LJAt5dSavevKKIK8T3tdnz+Eyj2khOnr8xh/NeAT6zaXyFOjn+BK/i9nv8BL8DmG/8fTLTtOCjnO0T5Xmvk/F/i4dO07LmcmP06LuQPqUQOdUfrVBF76pz1qxuj3buUCd8cgc0SdWMKh4OSvWPT4mS5c=
*/