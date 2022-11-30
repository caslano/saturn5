//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_INTERSEGMENT_PTR_HPP
#define BOOST_INTERPROCESS_INTERSEGMENT_PTR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
// interprocess
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/containers/flat_map.hpp>
#include <boost/interprocess/containers/vector.hpp>   //vector
#include <boost/interprocess/containers/set.hpp>      //set
// interprocess/detail
#include <boost/interprocess/detail/multi_segment_services.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/math_functions.hpp>
#include <boost/interprocess/detail/cast_tags.hpp>
#include <boost/interprocess/detail/mpl.hpp>
// other boost
#include <boost/core/no_exceptions_support.hpp>
#include <boost/static_assert.hpp>  //BOOST_STATIC_ASSERT
#include <boost/integer/static_log2.hpp>
#include <boost/assert.hpp>   //BOOST_ASSERT
// std
#include <climits>   //CHAR_BIT

//!\file
//!
namespace boost {

//Predeclarations
template <class T>
struct has_trivial_constructor;

template <class T>
struct has_trivial_destructor;

namespace interprocess {

template <class T>
struct is_multisegment_ptr;

struct intersegment_base
{
   typedef intersegment_base  self_t;
   BOOST_STATIC_ASSERT((sizeof(std::size_t) == sizeof(void*)));
   BOOST_STATIC_ASSERT((sizeof(void*)*CHAR_BIT == 32 || sizeof(void*)*CHAR_BIT == 64));
   static const std::size_t size_t_bits = (sizeof(void*)*CHAR_BIT == 32) ? 32 : 64;
   static const std::size_t ctrl_bits = 2;
   static const std::size_t align_bits = 12;
   static const std::size_t align      = std::size_t(1) << align_bits;
   static const std::size_t max_segment_size_bits = size_t_bits - 2;
   static const std::size_t max_segment_size = std::size_t(1) << max_segment_size_bits;

   static const std::size_t begin_bits             = max_segment_size_bits - align_bits;
   static const std::size_t pow_size_bits_helper = static_log2<max_segment_size_bits>::value;
   static const std::size_t pow_size_bits =
      (max_segment_size_bits == (std::size_t(1) << pow_size_bits_helper)) ?
      pow_size_bits_helper : pow_size_bits_helper + 1;
   static const std::size_t frc_size_bits =
      size_t_bits - ctrl_bits - begin_bits - pow_size_bits;

   BOOST_STATIC_ASSERT(((size_t_bits - pow_size_bits - frc_size_bits) >= ctrl_bits ));

   static const std::size_t relative_size_bits =
      size_t_bits - max_segment_size_bits - ctrl_bits;

   static const std::size_t is_pointee_outside  = 0;
   static const std::size_t is_in_stack         = 1;
   static const std::size_t is_relative         = 2;
   static const std::size_t is_segmented        = 3;
   static const std::size_t is_max_mode         = 4;

   intersegment_base()
   {
      this->set_mode(is_pointee_outside);
      this->set_null();
   }

   struct relative_addressing
   {
      std::size_t ctrl     :  2;
      std::size_t pow      :  pow_size_bits;
      std::size_t frc      :  frc_size_bits;
      std::size_t beg      :  begin_bits;
      std::ptrdiff_t off   :  sizeof(std::ptrdiff_t)*CHAR_BIT - 2;
      std::ptrdiff_t bits  :  2;
   };

   struct direct_addressing
   {
      std::size_t ctrl     :  2;
      std::size_t dummy    :  sizeof(std::size_t)*CHAR_BIT - 2;
      void * addr;
   };

   struct segmented_addressing
   {
      std::size_t ctrl     :  2;
      std::size_t segment  :  sizeof(std::size_t)*CHAR_BIT - 2;
      std::size_t off      :  sizeof(std::size_t)*CHAR_BIT - 2;
      std::size_t bits     :  2;
   };

   union members_t{
      relative_addressing  relative;
      direct_addressing    direct;
      segmented_addressing segmented;
   } members;

   BOOST_STATIC_ASSERT(sizeof(members_t) == 2*sizeof(std::size_t));

   void *relative_calculate_begin_addr() const
   {
      const std::size_t mask = ~(align - 1);
      std::size_t beg = this->members.relative.beg;
      return reinterpret_cast<void*>((((std::size_t)this) & mask) - (beg << align_bits));
   }

   void relative_set_begin_from_base(void *addr)
   {
      BOOST_ASSERT(addr < static_cast<void*>(this));
      std::size_t off = reinterpret_cast<char*>(this) - reinterpret_cast<char*>(addr);
      members.relative.beg = off >> align_bits;
   }

   //!Obtains the address pointed by the
   //!object
   std::size_t relative_size() const
   {
      std::size_t pow  = members.relative.pow;
      std::size_t size = (std::size_t(1u) << pow);
      BOOST_ASSERT(pow >= frc_size_bits);
      size |= members.relative.frc << (pow - frc_size_bits);
      return size;
   }

   static std::size_t calculate_size(std::size_t orig_size, std::size_t &pow, std::size_t &frc)
   {
      if(orig_size < align)
         orig_size = align;
      orig_size = ipcdetail::get_rounded_size_po2(orig_size, align);
      pow = ipcdetail::floor_log2(orig_size);
      std::size_t low_size = (std::size_t(1) << pow);
      std::size_t diff = orig_size - low_size;
      BOOST_ASSERT(pow >= frc_size_bits);
      std::size_t rounded = ipcdetail::get_rounded_size_po2
                              (diff, (std::size_t)(1u << (pow - frc_size_bits)));
      if(rounded == low_size){
         ++pow;
         frc = 0;
         rounded  = 0;
      }
      else{
         frc = rounded >> (pow - frc_size_bits);
      }
      BOOST_ASSERT(((frc << (pow - frc_size_bits)) & (align-1))==0);
      return low_size + rounded;
   }

   std::size_t get_mode()const
   {  return members.direct.ctrl;   }

   void set_mode(std::size_t mode)
   {
      BOOST_ASSERT(mode < is_max_mode);
      members.direct.ctrl = mode;
   }

   //!Returns true if object represents
   //!null pointer
   bool is_null() const
   {
      return   (this->get_mode() < is_relative) &&
               !members.direct.dummy &&
               !members.direct.addr;
   }

   //!Sets the object to represent
   //!the null pointer
   void set_null()
   {
      if(this->get_mode() >= is_relative){
         this->set_mode(is_pointee_outside);
      }
      members.direct.dummy = 0;
      members.direct.addr  = 0;
   }

   static std::size_t round_size(std::size_t orig_size)
   {
      std::size_t pow, frc;
      return calculate_size(orig_size, pow, frc);
   }
};



//!Configures intersegment_ptr with the capability to address:
//!2^(sizeof(std::size_t)*CHAR_BIT/2) segment groups
//!2^(sizeof(std::size_t)*CHAR_BIT/2) segments per group.
//!2^(sizeof(std::size_t)*CHAR_BIT/2)-1 bytes maximum per segment.
//!The mapping is implemented through flat_maps synchronized with mutexes.
template <class Mutex>
struct flat_map_intersegment
   :  public intersegment_base
{
   typedef flat_map_intersegment<Mutex>   self_t;

   void set_from_pointer(const volatile void *ptr)
   {  this->set_from_pointer(const_cast<const void *>(ptr));  }

   //!Obtains the address pointed
   //!by the object
   void *to_raw_pointer() const
   {
      if(is_null()){
         return 0;
      }
      switch(this->get_mode()){
         case is_relative:
            return const_cast<char*>(reinterpret_cast<const char*>(this)) + members.relative.off;
         break;
         case is_segmented:
            {
            segment_info_t segment_info;
            std::size_t offset;
            void *this_base;
            get_segment_info_and_offset(this, segment_info, offset, this_base);
            char *base  = static_cast<char*>(segment_info.group->address_of(this->members.segmented.segment));
            return base + this->members.segmented.off;
            }
         break;
         case is_in_stack:
         case is_pointee_outside:
            return members.direct.addr;
         break;
         default:
         return 0;
         break;
      }
   }

   //!Calculates the distance between two basic_intersegment_ptr-s.
   //!This only works with two basic_intersegment_ptr pointing
   //!to the same segment. Otherwise undefined
   std::ptrdiff_t diff(const self_t &other) const
   {  return static_cast<char*>(this->to_raw_pointer()) - static_cast<char*>(other.to_raw_pointer());   }

   //!Returns true if both point to
   //!the same object
   bool equal(const self_t &y) const
   {  return this->to_raw_pointer() == y.to_raw_pointer();  }

   //!Returns true if *this is less than other.
   //!This only works with two basic_intersegment_ptr pointing
   //!to the same segment group. Otherwise undefined. Never throws
   bool less(const self_t &y) const
   {  return this->to_raw_pointer() < y.to_raw_pointer(); }

   void swap(self_t &other)
   {
      void *ptr_this  = this->to_raw_pointer();
      void *ptr_other = other.to_raw_pointer();
      other.set_from_pointer(ptr_this);
      this->set_from_pointer(ptr_other);
   }

   //!Sets the object internals to represent the
   //!address pointed by ptr
   void set_from_pointer(const void *ptr)
   {
      if(!ptr){
         this->set_null();
         return;
      }

      std::size_t mode = this->get_mode();
      if(mode == is_in_stack){
         members.direct.addr = const_cast<void*>(ptr);
         return;
      }
      if(mode == is_relative){
         char *beg_addr = static_cast<char*>(this->relative_calculate_begin_addr());
         std::size_t seg_size = this->relative_size();
         if(ptr >= beg_addr && ptr < (beg_addr + seg_size)){
            members.relative.off = static_cast<const char*>(ptr) - reinterpret_cast<const char*>(this);
            return;
         }
      }
      std::size_t ptr_offset;
      std::size_t this_offset;
      segment_info_t ptr_info;
      segment_info_t this_info;
      void *ptr_base;
      void *this_base;
      get_segment_info_and_offset(this, this_info, this_offset, this_base);

      if(!this_info.group){
         this->set_mode(is_in_stack);
         this->members.direct.addr = const_cast<void*>(ptr);
      }
      else{
         get_segment_info_and_offset(ptr, ptr_info, ptr_offset, ptr_base);

         if(ptr_info.group != this_info.group){
            this->set_mode(is_pointee_outside);
            this->members.direct.addr =  const_cast<void*>(ptr);
         }
         else if(ptr_info.id == this_info.id){
            this->set_mode(is_relative);
            members.relative.off = (static_cast<const char*>(ptr) - reinterpret_cast<const char*>(this));
            this->relative_set_begin_from_base(this_base);
            std::size_t pow, frc;
            std::size_t s = calculate_size(this_info.size, pow, frc);
            (void)s;
            BOOST_ASSERT(this_info.size == s);
            this->members.relative.pow = pow;
            this->members.relative.frc = frc;
         }
         else{
            this->set_mode(is_segmented);
            this->members.segmented.segment = ptr_info.id;
            this->members.segmented.off     = ptr_offset;
         }
      }
   }

   //!Sets the object internals to represent the address pointed
   //!by another flat_map_intersegment
   void set_from_other(const self_t &other)
   {
      this->set_from_pointer(other.to_raw_pointer());
   }

   //!Increments internal
   //!offset
   void inc_offset(std::ptrdiff_t bytes)
   {
      this->set_from_pointer(static_cast<char*>(this->to_raw_pointer()) + bytes);
   }

   //!Decrements internal
   //!offset
   void dec_offset(std::ptrdiff_t bytes)
   {
      this->set_from_pointer(static_cast<char*>(this->to_raw_pointer()) - bytes);
   }

   //////////////////////////////////////
   //////////////////////////////////////
   //////////////////////////////////////

   flat_map_intersegment()
      :  intersegment_base()
   {}

   ~flat_map_intersegment()
   {}

   private:

   class segment_group_t
   {
      struct segment_data
      {
         void *addr;
         std::size_t size;
      };
      vector<segment_data> m_segments;
      multi_segment_services &m_ms_services;

      public:
      segment_group_t(multi_segment_services &ms_services)
         :  m_ms_services(ms_services)
      {}

      void push_back(void *addr, std::size_t size)
      {
         segment_data d = { addr, size };
         m_segments.push_back(d);
      }

      void pop_back()
      {
         BOOST_ASSERT(!m_segments.empty());
         m_segments.erase(--m_segments.end());
      }


      void *address_of(std::size_t segment_id)
      {
         BOOST_ASSERT(segment_id < (std::size_t)m_segments.size());
         return m_segments[segment_id].addr;
      }

      void clear_segments()
      {  m_segments.clear();  }

      std::size_t get_size() const
      {  return m_segments.size();  }

      multi_segment_services &get_multi_segment_services() const
      {  return m_ms_services;   }

      friend bool operator< (const segment_group_t&l, const segment_group_t &r)
      {  return &l.m_ms_services < &r.m_ms_services;   }
   };

   struct segment_info_t
   {
      std::size_t size;
      std::size_t id;
      segment_group_t *group;
      segment_info_t()
         :  size(0), id(0), group(0)
      {}
   };

   typedef set<segment_group_t>  segment_groups_t;

   typedef boost::interprocess::flat_map
      <const void *
      ,segment_info_t
      ,std::less<const void *> >          ptr_to_segment_info_t;

   struct mappings_t : Mutex
   {
      //!Mutex to preserve integrity in multi-threaded
      //!enviroments
      typedef Mutex        mutex_type;
      //!Maps base addresses and segment information
      //!(size and segment group and id)*

      ptr_to_segment_info_t      m_ptr_to_segment_info;

      ~mappings_t()
      {
         //Check that all mappings have been erased
         BOOST_ASSERT(m_ptr_to_segment_info.empty());
      }
   };

   //Static members
   static mappings_t       s_map;
   static segment_groups_t s_groups;
   public:

   typedef segment_group_t*      segment_group_id;

   //!Returns the segment and offset
   //!of an address
   static void get_segment_info_and_offset(const void *ptr, segment_info_t &segment, std::size_t &offset, void *&base)
   {
      //------------------------------------------------------------------
      boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
      //------------------------------------------------------------------
      base = 0;
      if(s_map.m_ptr_to_segment_info.empty()){
         segment = segment_info_t();
         offset  = reinterpret_cast<const char*>(ptr) - static_cast<const char*>(0);
         return;
      }
      //Find the first base address greater than ptr
      typename ptr_to_segment_info_t::iterator it
         = s_map.m_ptr_to_segment_info.upper_bound(ptr);
      if(it == s_map.m_ptr_to_segment_info.begin()){
         segment = segment_info_t();
         offset  = reinterpret_cast<const char*>(ptr) - static_cast<const char *>(0);
      }
      //Go to the previous one
      --it;
      char *      segment_base = const_cast<char*>(reinterpret_cast<const char*>(it->first));
      std::size_t segment_size = it->second.size;

      if(segment_base <= reinterpret_cast<const char*>(ptr) &&
         (segment_base + segment_size) >= reinterpret_cast<const char*>(ptr)){
         segment = it->second;
         offset  = reinterpret_cast<const char*>(ptr) - segment_base;
         base = segment_base;
      }
      else{
         segment = segment_info_t();
         offset  = reinterpret_cast<const char*>(ptr) - static_cast<const char*>(0);
      }
   }

   //!Associates a segment defined by group/id with a base address and size.
   //!Returns false if the group is not found or there is an error
   static void insert_mapping(segment_group_id group_id, void *ptr, std::size_t size)
   {
      //------------------------------------------------------------------
      boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
      //------------------------------------------------------------------

      typedef typename ptr_to_segment_info_t::value_type value_type;
      typedef typename ptr_to_segment_info_t::iterator   iterator;
      typedef std::pair<iterator, bool>                  it_b_t;

      segment_info_t info;
      info.group = group_id;
      info.size  = size;
      info.id    = group_id->get_size();

      it_b_t ret = s_map.m_ptr_to_segment_info.insert(value_type(ptr, info));
      BOOST_ASSERT(ret.second);

      value_eraser<ptr_to_segment_info_t> v_eraser(s_map.m_ptr_to_segment_info, ret.first);
      group_id->push_back(ptr, size);
      v_eraser.release();
   }

   static bool erase_last_mapping(segment_group_id group_id)
   {
      //------------------------------------------------------------------
      boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
      //------------------------------------------------------------------
      if(!group_id->get_size()){
         return false;
      }
      else{
         void *addr = group_id->address_of(group_id->get_size()-1);
         group_id->pop_back();
         std::size_t erased = s_map.m_ptr_to_segment_info.erase(addr);
         (void)erased;
         BOOST_ASSERT(erased);
         return true;
      }
   }

   static segment_group_id new_segment_group(multi_segment_services *services)
   {
      {  //------------------------------------------------------------------
         boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
         //------------------------------------------------------------------
         typedef typename segment_groups_t::iterator iterator;
         std::pair<iterator, bool> ret =
            s_groups.insert(segment_group_t(*services));
         BOOST_ASSERT(ret.second);
         return &*ret.first;
      }
   }

   static bool delete_group(segment_group_id id)
   {
      {  //------------------------------------------------------------------
         boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
         //------------------------------------------------------------------
         bool success = 1u == s_groups.erase(segment_group_t(*id));
         if(success){
            typedef typename ptr_to_segment_info_t::iterator ptr_to_segment_info_it;
            ptr_to_segment_info_it it(s_map.m_ptr_to_segment_info.begin());
            while(it != s_map.m_ptr_to_segment_info.end()){
               if(it->second.group == id){
                  it = s_map.m_ptr_to_segment_info.erase(it);
               }
               else{
                  ++it;
               }
            }
         }
         return success;
      }
   }
};

//!Static map-segment_info associated with
//!flat_map_intersegment<>
template <class Mutex>
typename flat_map_intersegment<Mutex>::mappings_t
   flat_map_intersegment<Mutex>::s_map;

//!Static segment group container associated with
//!flat_map_intersegment<>
template <class Mutex>
typename flat_map_intersegment<Mutex>::segment_groups_t
   flat_map_intersegment<Mutex>::s_groups;

//!A smart pointer that can point to a pointee that resides in another memory
//!memory mapped or shared memory segment.
template <class T>
class intersegment_ptr : public flat_map_intersegment<interprocess_mutex>
{
   typedef flat_map_intersegment<interprocess_mutex> PT;
   typedef intersegment_ptr<T>                  self_t;
   typedef PT                                      base_t;

   void unspecified_bool_type_func() const {}
   typedef void (self_t::*unspecified_bool_type)() const;

   public:
   typedef T *                                     pointer;
   typedef typename ipcdetail::add_reference<T>::type reference;
   typedef T                                       value_type;
   typedef std::ptrdiff_t                          difference_type;
   typedef std::random_access_iterator_tag         iterator_category;

   public:   //Public Functions

   //!Constructor from raw pointer (allows "0" pointer conversion).
   //!Never throws.
   intersegment_ptr(pointer ptr = 0)
   {  base_t::set_from_pointer(ptr);   }

   //!Constructor from other pointer.
   //!Never throws.
   template <class U>
   intersegment_ptr(U *ptr){  base_t::set_from_pointer(pointer(ptr)); }

   //!Constructor from other intersegment_ptr
   //!Never throws
   intersegment_ptr(const intersegment_ptr& ptr)
   {  base_t::set_from_other(ptr);   }

   //!Constructor from other intersegment_ptr. If pointers of pointee types are
   //!convertible, intersegment_ptrs will be convertibles. Never throws.
   template<class T2>
   intersegment_ptr(const intersegment_ptr<T2> &ptr)
   {  pointer p(ptr.get());   (void)p; base_t::set_from_other(ptr); }

   //!Emulates static_cast operator.
   //!Never throws.
   template<class U>
   intersegment_ptr(const intersegment_ptr<U> &r, ipcdetail::static_cast_tag)
   {  base_t::set_from_pointer(static_cast<T*>(r.get())); }

   //!Emulates const_cast operator.
   //!Never throws.
   template<class U>
   intersegment_ptr(const intersegment_ptr<U> &r, ipcdetail::const_cast_tag)
   {  base_t::set_from_pointer(const_cast<T*>(r.get())); }

   //!Emulates dynamic_cast operator.
   //!Never throws.
   template<class U>
   intersegment_ptr(const intersegment_ptr<U> &r, ipcdetail::dynamic_cast_tag)
   {  base_t::set_from_pointer(dynamic_cast<T*>(r.get())); }

   //!Emulates reinterpret_cast operator.
   //!Never throws.
   template<class U>
   intersegment_ptr(const intersegment_ptr<U> &r, ipcdetail::reinterpret_cast_tag)
   {  base_t::set_from_pointer(reinterpret_cast<T*>(r.get())); }

   //!Obtains raw pointer from offset.
   //!Never throws.
   pointer get()const
   {  return static_cast<pointer>(base_t::to_raw_pointer());   }

   //!Pointer-like -> operator. It can return 0 pointer.
   //!Never throws.
   pointer operator->() const
   {  return self_t::get(); }

   //!Dereferencing operator, if it is a null intersegment_ptr behavior
   //!is undefined. Never throws.
   reference operator* () const
   {  return *(self_t::get());   }

   //!Indexing operator.
   //!Never throws.
   reference operator[](std::ptrdiff_t idx) const
   {  return self_t::get()[idx];  }

   //!Assignment from pointer (saves extra conversion).
   //!Never throws.
   intersegment_ptr& operator= (pointer from)
   {  base_t::set_from_pointer(from); return *this;  }

   //!Assignment from other intersegment_ptr.
   //!Never throws.
   intersegment_ptr& operator= (const intersegment_ptr &ptr)
   {  base_t::set_from_other(ptr);  return *this;  }

   //!Assignment from related intersegment_ptr. If pointers of pointee types
   //!are assignable, intersegment_ptrs will be assignable. Never throws.
   template <class T2>
   intersegment_ptr& operator= (const intersegment_ptr<T2> & ptr)
   {
      pointer p(ptr.get());   (void)p;
      base_t::set_from_other(ptr); return *this;
   }

   //!intersegment_ptr + std::ptrdiff_t.
   //!Never throws.
   intersegment_ptr operator+ (std::ptrdiff_t idx) const
   {
      intersegment_ptr result (*this);
      result.inc_offset(idx*sizeof(T));
      return result;
   }

   //!intersegment_ptr - std::ptrdiff_t.
   //!Never throws.
   intersegment_ptr operator- (std::ptrdiff_t idx) const
   {
      intersegment_ptr result (*this);
      result.dec_offset(idx*sizeof(T));
      return result;
   }

   //!intersegment_ptr += std::ptrdiff_t.
   //!Never throws.
   intersegment_ptr &operator+= (std::ptrdiff_t offset)
   {  base_t::inc_offset(offset*sizeof(T));  return *this;  }

   //!intersegment_ptr -= std::ptrdiff_t.
   //!Never throws.
   intersegment_ptr &operator-= (std::ptrdiff_t offset)
   {  base_t::dec_offset(offset*sizeof(T));  return *this;  }

   //!++intersegment_ptr.
   //!Never throws.
   intersegment_ptr& operator++ (void)
   {  base_t::inc_offset(sizeof(T));   return *this;  }

   //!intersegment_ptr++.
   //!Never throws.
   intersegment_ptr operator++ (int)
   {  intersegment_ptr temp(*this); ++*this; return temp; }

   //!--intersegment_ptr.
   //!Never throws.
   intersegment_ptr& operator-- (void)
   {  base_t::dec_offset(sizeof(T));   return *this;  }

   //!intersegment_ptr--.
   //!Never throws.
   intersegment_ptr operator-- (int)
   {  intersegment_ptr temp(*this); --*this; return temp; }

   //!Safe bool conversion operator.
   //!Never throws.
   operator unspecified_bool_type() const
   {  return base_t::is_null()? 0 : &self_t::unspecified_bool_type_func;   }

   //!Not operator. Not needed in theory, but improves portability.
   //!Never throws.
   bool operator! () const
   {  return base_t::is_null();   }

   //!Swaps two intersegment_ptr-s. More efficient than standard swap.
   //!Never throws.
   void swap(intersegment_ptr &other)
   {  base_t::swap(other);   }

   //!Calculates the distance between two intersegment_ptr-s.
   //!This only works with two basic_intersegment_ptr pointing
   //!to the same segment. Otherwise undefined
   template <class T2>
   std::ptrdiff_t _diff(const intersegment_ptr<T2> &other) const
   {  return base_t::diff(other);   }

   //!Returns true if both point to the
   //!same object
   template <class T2>
   bool _equal(const intersegment_ptr<T2>&other) const
   {  return base_t::equal(other);   }

   //!Returns true if *this is less than other.
   //!This only works with two basic_intersegment_ptr pointing
   //!to the same segment group. Otherwise undefined. Never throws
   template <class T2>
   bool _less(const intersegment_ptr<T2> &other) const
   {  return base_t::less(other);   }
};

//!Compares the equality of two intersegment_ptr-s.
//!Never throws.
template <class T1, class T2> inline
bool operator ==(const intersegment_ptr<T1> &left,
                 const intersegment_ptr<T2> &right)
{
   //Make sure both pointers can be compared
   bool e = typename intersegment_ptr<T1>::pointer(0) ==
            typename intersegment_ptr<T2>::pointer(0);
   (void)e;
   return left._equal(right);
}

//!Returns true if *this is less than other.
//!This only works with two basic_intersegment_ptr pointing
//!to the same segment group. Otherwise undefined. Never throws
template <class T1, class T2> inline
bool operator <(const intersegment_ptr<T1> &left,
                const intersegment_ptr<T2> &right)
{
   //Make sure both pointers can be compared
   bool e = typename intersegment_ptr<T1>::pointer(0) <
            typename intersegment_ptr<T2>::pointer(0);
   (void)e;
   return left._less(right);
}

template<class T1, class T2> inline
bool operator!= (const intersegment_ptr<T1> &pt1,
                 const intersegment_ptr<T2> &pt2)
{  return !(pt1 ==pt2);  }

//!intersegment_ptr<T1> <= intersegment_ptr<T2>.
//!Never throws.
template<class T1, class T2> inline
bool operator<= (const intersegment_ptr<T1> &pt1,
                 const intersegment_ptr<T2> &pt2)
{  return !(pt1 > pt2);  }

//!intersegment_ptr<T1> > intersegment_ptr<T2>.
//!Never throws.
template<class T1, class T2> inline
bool operator> (const intersegment_ptr<T1> &pt1,
                       const intersegment_ptr<T2> &pt2)
{  return (pt2 < pt1);  }

//!intersegment_ptr<T1> >= intersegment_ptr<T2>.
//!Never throws.
template<class T1, class T2> inline
bool operator>= (const intersegment_ptr<T1> &pt1,
                 const intersegment_ptr<T2> &pt2)
{  return !(pt1 < pt2);  }

//!operator<<
template<class E, class T, class U> inline
std::basic_ostream<E, T> & operator<<
   (std::basic_ostream<E, T> & os, const intersegment_ptr<U> & p)
{  return os << p.get();   }

//!operator>>
template<class E, class T, class U> inline
std::basic_istream<E, T> & operator>>
   (std::basic_istream<E, T> & os, intersegment_ptr<U> & p)
{  U * tmp; return os >> tmp; p = tmp;   }

//!std::ptrdiff_t + intersegment_ptr.
//!The result is another pointer of the same segment
template<class T> inline
intersegment_ptr<T> operator+
   (std::ptrdiff_t diff, const intersegment_ptr<T>& right)
{  return right + diff;  }

//!intersegment_ptr - intersegment_ptr.
//!This only works with two intersegment_ptr-s that point to the
//!same segment
template <class T, class T2> inline
std::ptrdiff_t operator- (const intersegment_ptr<T> &pt,
                          const intersegment_ptr<T2> &pt2)
{  return pt._diff(pt2)/sizeof(T);  }

//! swap specialization
template<class T> inline
void swap (boost::interprocess::intersegment_ptr<T> &pt,
           boost::interprocess::intersegment_ptr<T> &pt2)
{  pt.swap(pt2);  }

//!to_raw_pointer() enables boost::mem_fn to recognize intersegment_ptr.
//!Never throws.
template<class T> inline
T * to_raw_pointer(boost::interprocess::intersegment_ptr<T> const & p)
{  return p.get();   }

//!Simulation of static_cast between pointers.
//!Never throws.
template<class T, class U> inline
boost::interprocess::intersegment_ptr<T> static_pointer_cast(const boost::interprocess::intersegment_ptr<U> &r)
{  return boost::interprocess::intersegment_ptr<T>(r, boost::interprocess::ipcdetail::static_cast_tag());  }

//!Simulation of const_cast between pointers.
//!Never throws.
template<class T, class U> inline
boost::interprocess::intersegment_ptr<T> const_pointer_cast(const boost::interprocess::intersegment_ptr<U> &r)
{  return boost::interprocess::intersegment_ptr<T>(r, boost::interprocess::ipcdetail::const_cast_tag());  }

//!Simulation of dynamic_cast between pointers.
//!Never throws.
template<class T, class U> inline
boost::interprocess::intersegment_ptr<T> dynamic_pointer_cast(const boost::interprocess::intersegment_ptr<U> &r)
{  return boost::interprocess::intersegment_ptr<T>(r, boost::interprocess::ipcdetail::dynamic_cast_tag());  }

//!Simulation of reinterpret_cast between pointers.
//!Never throws.
template<class T, class U> inline
boost::interprocess::intersegment_ptr<T> reinterpret_pointer_cast(const boost::interprocess::intersegment_ptr<U> &r)
{  return boost::interprocess::intersegment_ptr<T>(r, boost::interprocess::ipcdetail::reinterpret_cast_tag());  }

//!Trait class to detect if an smart pointer has
//!multi-segment addressing capabilities.
template <class T>
struct is_multisegment_ptr
   <boost::interprocess::intersegment_ptr<T> >
{
   static const bool value = true;
};

}  //namespace interprocess {

#if defined(_MSC_VER) && (_MSC_VER < 1400)
//!to_raw_pointer() enables boost::mem_fn to recognize intersegment_ptr.
//!Never throws.
template<class T> inline
T * to_raw_pointer(boost::interprocess::intersegment_ptr<T> const & p)
{  return p.get();   }
#endif

//!has_trivial_constructor<> == true_type specialization
//!for optimizations
template <class T>
struct has_trivial_constructor
   < boost::interprocess::intersegment_ptr<T> >
   : public true_type{};

//!has_trivial_destructor<> == true_type specialization
//!for optimizations
template <class T>
struct has_trivial_destructor
   < boost::interprocess::intersegment_ptr<T> >
   : public true_type{};

}  //namespace boost {

#if 0

//bits
//-> is_segmented
//-> is_relative
//-> is_in_stack
//-> is_pointee_outside

//Data




//segmented:
//
// std::size_t ctrl    : CTRL_BITS;
// std::size_t segment : MAX_SEGMENT_BITS;
// std::size_t offset;

//RELATIVE_SIZE_BITS =  SIZE_T_BITS -
//                      MAX_SEGMENT_BITS -
//                      CTRL_BITS                  10    10
//MAX_SEGMENT_SIZE   = SIZE_T_BITS - ALIGN_BITS    20    52

//SIZE_T_BITS - 1 - ALIGN_BITS                     19    51
//POW_SIZE_BITS = upper_log2
// (SIZE_T_BITS - 1 - ALIGN_BITS)                  5     6
//FRC_SIZE_BITS = SIZE_T_BITS - CTRL_BITS
//  MAX_SEGMENT_SIZE_ALIGNBITS - POW_SIZE_BITS     6     5

//relative:
//
// std::size_t ctrl     : CTRL_BITS;               2     2
// std::size_t size_pow : POW_SIZE_BITS            5     6
// std::size_t size_frc : FRC_SIZE_BITS;           6     5
// std::size_t start    : MAX_SEGMENT_SIZE_ALIGNBITS;19    51
// std::ptrdiff_t distance : SIZE_T_BITS;          32    64

//direct:
//
// std::size_t ctrl     : CTRL_BITS;               2     2
// std::size_t dummy    : SIZE_T_BITS - CTRL_BITS  30    62
// void *addr           : SIZE_T_BITS;             32    64

//32 bits systems:
//Page alignment: 2**12
//

//!Obtains the address pointed by the
//!object
void *to_raw_pointer() const
{
   if(this->is_pointee_outside() || this->is_in_stack()){
      return raw_address();
   }
   else if(this->is_relative()){
      return (const_cast<char*>(reinterpret_cast<const char*>(this))) + this->relative_pointee_offset();
   }
   else{
      group_manager *m     = get_segment_group_manager(addr);
      char *base  = static_cast<char*>(m->get_id_address(this->segmented_id()));
      return base + this->segmented_offset();
   }
}

void set_from_pointer(const void *ptr)
{
   if(!ptr){
      this->set_pointee_outside();
      this->raw_address(ptr);
   }
   else if(this->is_in_stack()){
      this->raw_address(ptr);
   }
   else if(this->is_relative() &&
            (  (ptr >= this->relative_start())
            &&(ptr <  this->relative_start() + this->relative_size()))
            ){
      this->relative_offset(ptr - this);
   }
   else{
      segment_info_t ptr_info  = get_id_from_addr(ptr);
      segment_info_t this_info = get_id_from_addr(this);
      if(ptr_info.segment_group != this_info.segment_group){
         if(!ptr_info.segment_group){
            this->set_in_stack();
         }
         else{
            this->set_pointee_outside();
         }
      }
      else if(ptr_info.segment_id == this_info.segment_id){
         set_relative();
         this->relative_size  (ptr_info.size);
         this->relative_offset(static_cast<const char*>(ptr) - reinterpret_cast<const char*>(this));
         this->relative_start (ptr_info.base);
      }
   }
}

void set_from_other(const self_t &other)
{  this->set_from_pointer(other.to_raw_pointer()); }

#endif

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_INTERSEGMENT_PTR_HPP

/* intersegment_ptr.hpp
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
*/