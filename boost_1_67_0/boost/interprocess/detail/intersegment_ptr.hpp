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
wF5mu8l6Yh4L41g6LgaS8cHGeP6OMgX056XTlWaXw+aIub45ILcx6+gVSaCgOlcrX2nX8JS0UTTwtjcAmfBIMAJGLbmmWQbe9XdbUVkkojJyKJlYVBHU8sYtxSEvxzFUBMXx4Ovyf4dMiBKmUe2WF6mB8+fOQMqDsJo2S7cbzYSjUND0UcSAyF7XtynU1lL1o86JziHt06q/TWN0BLAXOae8gVp/LOe51NGppX8d/BTVci6pjlZYPfnzj+FCpzd8XzJ5FUr1BH0NiSneELC2PHH36tEtcxq51prDphQkaL5RbxPl8ipSPKRU24uFLTS0KU/Vdnmb3C5JdbKf6YQg8U04pPttvfyL76SO92eb9b3fxlnZdvRyHev4JNltVnf1/Wahrt2s7uR71A51Xh1wlazuXM+yLXZmi76tqOrEOodF4KsbX7hWdprEpHVGFk9dHIHEcVtY0Zp+SA90WCPDx/u8zKioUQR3PaKc70PyMsmNl5/My+Y1ffb8txgcJPKMXuA/9iVqjmSyiNH+7XgA1UKf7yTXM8HmWpa5ez9N4Py4dDpu/Wtn7bD5WiVt84llKf+ikFwdMCm3At6QZFuxNI3co15p4yPGBsE0hjyRfNeWAxMKaQn66c6R738y1GzGV9yyovEMXlXRGEPJ6kte+g0Uh+gEZk9nKZi8zH8VpSxkK/7+z9Hut8+LIsR5KMnkJmVN3kUF48uswbChC5tkAKnnX523qkG3l3AG+mXakFZpmVEJxSnpYtJlWpnGKPMxZwnFKkweBY5LwfEqg3B7DMWEcyC5RO4kIZm3OyrNuSQ4gripdFe41Flt7j8JQmAhowcum57+W8b/hEh7DR9+dXzY5OVtl1wJKuCQbKsUWNE4EssmgwXZw8mdBAbjrrfVmdY7Z7sRNZtcY7ki+oJ2wFgi5oSoEhSYmSirA82k5FJ/rJQHjJDrSj9omLKM51OMaXbzaVCMy6Vsuria45u4qrztyeWEM1DU+cLymNmNiutjKGacqZDD0z8xswffWd3dUSpd8wGaCMUdsorqFqG3RJwDXq6vp9r6gZvnxsNKni4jNL+SFTSnPrMfWgWTrjWh+Q4mpa9ser2YyBN2EP3Oica8I2stk2AmKF8hg/wee2Jeb85u5zkmEcIA5R0ZjzMtqU2/igGPo2p9uagZuTWs4JR0em2NPE4hvjfl4+ub9FVrCBhBiCOlqoFJDi66qDW+ZLtvu8ZA8x9N+Bwfkn5eeqfnMh/SjdT7iSdHJ+PocVjJ4vyumYAxxOsQWmcK5k810DJ/ahBtWz2Pq+3cOdr/lXyR4UmEXWPoWZaxU8M68BcIvwoMmlCYceDLz4MUugWkZdDB0iPOrvm9gxQgOcMWClHKIcDY9JHXIHP2qOoghkGiy49X1hAOeOZuvVVjBBJYWWHOtvHkaZngylODeUyW+Qb7xveSVPtyw2tTIbJHJ5LhP9Y7blqL5+mxQ6t4h/z4kOgEWNxzK8tBm6D6X5WchMOEIYKyX1+ao1HkkXkc0oLlHB4yiUbBMHTcILk/1bXyRvpc6w/p6kJLv+QU+LR8CYQnPg5B0loaQZwhi8HhnB0Jqwxu9AL2w2HJWkxSoalZ1x8IKUwYrsI2wlmMctB6NGCrl928MfnVxaKajmwrDRQWX0Om9TNY1o16ETKRzC/4i+eTlcDJzgqS6zpCRbAAJ1K6jCyzzEdMNbgdMHv3C2iaivtTAgIE/An8E/Qn+E/In9A/YX/C/0T8ifwT9Sf6T8yf2D9xf+L/JPxJ/JP0J/lPyp/UP2l/0v9k/Mn8k/Un+0/On9w/eX/y/xT8KfxT9Kf4T8mf0j9lf8r/VPyp/FP1p/pPzZ/aP3V/6v80/Gn80/Sn+U/Ln9Y/bX/a/3T86fzT9af7T8+f3j99f/r/DPwZ/DP0Z/jPyJ/RP2N/xv9M/Jn8M/Vn+s/Mn9k/c3/m/yz8Wfyz9Gf5z8qf1T9rf9b/bPzZ/LP1Z/vPzp/dP3t/9v8c/Dn8c/Tn+M/Jn9M/Z3/O/1z8ufxz9ef6z82f2z93f+7/PPx5/PP05/nPy5/XP29/3v98/Pn88/Xn+8/Pn98/gFSAAPCWpSYEKDolVwJd3iL3A+4by0KulWuAYcq0ZNyw8w0RXcLpoQtD9qevmeFyM+i2pdX13l5Ae15+/VC+p/QyY9L8H189EJkzZbCqbTNaZcysNFL6VSVMxEZk5UnE9EPvvbIq0qJarNPqm9Bs6TNNGye8UToUSjgHZK31LcDJ1vW1XXFgl2SwTXVKMV2hZmkg+d/l6fhNnlTgDKpR3k4U4B8DHMcDHCS5+A2srrFibN/nIiHZb9RFkL7pEBRwSBj2XTdjg4JHAeDp2sQa+MvkMrVciLy6yFx7L+hxYN5XA5CjVt7+kyV0eeeDcZ+LOP0d3fte8ok331Wkwl5EGhlcYZbtCYiRgdO+4hTF7ebIXEe9SN+xdvssNYZrrULRk5/rCZLC9YubJzZu/2R5x6ytf7iNRZbkI/mjIzm6L9P0VKCQbgQkvqJ+3ueWWst3n3hFjSCup7MHWwfqdzaldm1krP3V8qs5l9Mui3ifW9pUTxRs7YNzuj9BDjJRuOzBVdXwdEGPu5e6n9SuJrcDL0RwJu/fe9iwWSVIVremJ7y9VWPkD+kjtEWCHXMyFOzbrDRWnLuXnNuFCDzRuCpDQ6WsqhL+yywBorXK2d+Iq+tGpwespxBCM00ZTV0W2oCfGNKYMkXZeqL+sJVmEnOr1otLkfZ7iOzQVj9WHUuc5UKclyKDhRbzUjtTY7EA0rxYD9ARnPVXbOhBpF53jcvcFK0qTif/vUOUpqvHuecc+Ezkp0V8gdgBZiksgDMRJfpUT+dx9LWoZHiE50E4ntmqL791z90SbCeymWyJ42EJ4wq3OWRBO9Gap9+mU/ophTijrBFOJff7jFSXhj77dGwHVrOmfipJm498eG9N2bo/TfAgqISO+5rVG3YnXN9vOmPqOvPi2CEUZXFy7zU8B2+pt0Jwsa/z7wEYfX0QIjVbRVBOvJRkI1xv7/FZUV8cuEMI/s80i4piCRAoYUByIjXbY+vmkqF22m/PJdfr9DzRBF6sGUJ/lewF9IjsNZc1mE9yjUoay5HBCR6EXBz2iZzn2GqeUiYTYk/i/df+0zyOOqouxRDKmNUGiOn7HQ8dZvwW8Rk9OeA1XPOpB0sGRptpk2mxnMMhk0tRITPc9mB1x7VSccizAFcQvnpshsahpMRjt4a30uZ2kH49P5jIJY8sUN63c4JAdWdn0ghIfnSYTNbfySx1Vpk/ZtfmTQt7ZQQa2YCvCO35CUinLoxsyF8d8uUBP9kjs7lJATNXRlQde02AP2bPuk+VvPaznDRYhMzXnouQazyGj3jT/f7gwafSGBHuMU5RJnTmi4DsCToSx+GNDbiqKY2yFvOwGjRKyCiIXm+JBLtZDF/1m1D/No0PfV4V+6TcU4xDoZVLz7Xgc0Ph2ZMLm9AhzPCiQcO4VlUUr2OV5dTm0Mc2IL22d7nwMFOS8YDprmdXgzRswvVKUM4kawTHG02hTYyqmqxmd0jDuqgM/MFZXLI+EXR0WFHoPqlNqVkH1DJASZnZro5UtJocru94CoH+a3vt0SOoFtilw+SNvAvUG3KTRY7QK1QoOgSml2T48LIcQ+Z6LvODp6fmQsoYZwjWzFxFZyaww1ywumOPAI2F7CR3OFrtH/iNoWlgVOeNDuixlf7KgfO0s7GzyXJslxfSO8H8ipmZCtG0SShgOuO1DtCNZ8MJMrwmu/bzz+bzOUbJjh9sif42xSYaaWKIkgf5scslsKrcu6rmsW7JBDjCgUVS645po3T0jLh0vcQ3vY0XgSos7SzlFSbllCWKCjzVlPDzMIFuE71+MielyjIwft8SRl3jYxB1GJqWhCdMQcnU9Sv3qHFqyipO+Udwqi0h1JADy5HlMyYh8Mx9ULZfhjztfwcA8SL+wiJtubihiXhEzC7xlAUehsFqPZL5cEXhx/fbsdbAXt9rRFqs75+5o3PNz6CwmvQ7c5Hl+WjqMDyzmCgXDcL6F4yVxrl5h7df7tw6FEiipXUkLK8ZVrcl2lVilTCsy9Jh3NS6V6AB+EMqZJp0O9vu4l/CScPZGmA8ZukXckwT4zJOTE3u4v0WcfvsRW100w2NSR3hxXeLyi/xT5jS4afVEhOQu6U6s5dbA10dOxWVXV447cjabdysGTUwkMFkdpr1HrreYv1DE3bk8xtF6vL82SzjF1Xh9EWtpCKczuoBlZmgUhlqp994oDyZMylFZEYqXXoxAsAMQNbrMF3zqGkiNBCel4apPrMe/aZtI65DE79qxinLaAsy6bgNgWcrBz7KD8meB4+a84518Q7BdAiypkCNV90Z9s6elRNdtyI2KM8Y5muiKm4myWY7407cXzQMkqRy2jVNFw7iXbTGDx8aKJq8Kpktb4Rxq9BfDg5sOiLF2+bJLlwfNPJ53/VDXVxR0GUm08tJ+5h0uqI1YcpN8ZQS7t81AOyG3amuMMTlPnQqoXwqPr8XM4UPNc2UdsZeVAr1pjvqE9IRtZeCKonYFtq7Ohx16gRIx4Rq0ze4TCo+sMl8m5S9zOXOm6mkGqu4tjicbKsW28MVzidC6HLcZ0m1WWLMldMVoV9nN7c2tWeL/1bIGpEu31L+A3ZCr16nyO349DxlK9nirozb26Nopec9PmDp1bJu13qcrLIPL9aFkWpTW+YbYLWRHnc83KUFZZBXsSviPnMP6f1l2kBH83jnZNRdenhlWolgs9sIBy8543PcKFCUtnV9o9aQ3unJUDocldHYxr0dH2s+YOAFNwUJMgTGCTAw8XWSkIhIUKDF0C6SqNYBB9YnmTrMA6ZCkzOGpx618FVcRkGttot/K/74MfyYLVl7ykXZgFzOvIh9RrOb2XTBzZRp75VUparFi4M7tqpGETTzx1CiF4EOLb7ZvJ27JSkAYhhMWBtB3xNEDQxmmGDAOn0a4LRu9VwXSvPDZuawQ8aH4s58e7Pm9xDz0gHwz8sRzgXyz6PKMA1cJfMHFQv9HgAZ5N065MIUV+4nj1RuuagWQujLutRm/eG80FmZQsO5MdZb6ErqH+0RcglzJs2vmW3EiFlypZO6oxZSvXotai+sEpOSweVdeM/D9ka7F+6JyfBMUk14lvikSEasVk/jdyRIuY4rVatM58bXfluc8ZJPqpYs0OsgfFOgdcalDh1q+jewWshWCv/IFjDWCHCMId1uIhWxSfX7PZ5GBYElXzDeUpcgQp+tuap0iGxYzjxh1F3TvqQB8y60cLI7rQBq2oS7LV+f6K9+DbenIJPx+03LfFDXQ/OTP6PnXufophBo9oUCzuqGaoYHRVojUVFCRUmlgE2GcF5IRyMnv6MsffI3/mGkPBPUs4EfduB7fwNofVGBFhC0pzp2TS65iXO7Hn27Qrk/115vCIpdc+zhMJTChEO6E5tafa2swWiRETMW3wjQ00ZzDQubgJAO7q5DbKsR1qteYRYZn3oQNMJ3UqtRzr054L7lbjPr3jJQdxspre4fRY5QiB4aENwZLjxZ/cYyvh9o/V6EdaB1q6/Cc5Jzs8D/rdf/AtxRwFd302i0Bif8m2a9Yy90Ye1P9BO6t75rCboFINkVG27D6mmuN32R7epBI1IM+nUXsZAfsVL24wvnTUN+pWPwIAqurY+byLNalh7NS2Y6seENeYN2eJqVmUO0qdquPpKUzmqlSEEjlbA+jFm6UbFyB++9hkCGcdsGOeoSEOrdzLudaZE6LINbAZ+623h+gEP6WPeZXS27zeBPbpe//VTpTIgXfubtPFn5VBhIhfp1OSdDrWaCQpUgApS+1elEmgcxkSqgkLDluzJl6lMTreFIRW8cM0HYAQji89sBGJzpvuIYkdupMYrd8dbQSPeirN19+pHEKu1SoUTFQIGaXvbrlR7bH5JzQ4oIHDkQXqEa+TpU7Tw+3yUVYDjTdgfGVsxiwAhH4EhaM9gd0WFika112BgoVFbnmOjxHQvuaZnJp+lhDQZnPikyD9k0iJHFjtFj7sIxPRoNQtgXNGC2nb5eoZFai3wU0vcxjglcV2q52wCHoovJHaId/XGhSiIQki8nGK2a4y+F2l7NrpBAKBTkmDIYhvzP203keJRjBEuVhKMahtNQS4IVl97rc1ifIcNQQ1hjmoz0wenlDTY41N3LmjIOWXr2QYisP/a/ZgXk42rRr8l4bl9lQcNrqNZUxeUf12rDoFncC6o30CuETo5rz1IHDoPGXigANp6hwgvpXcwluKcmlJ2buoShUq7tpr0QTEWcEaVShmUSjYNvO2vgj/6IYnAkKExd6/CdMHx6EzkuWZNWBTLpWSTvds339bSW6TgY1V9kuFYDiRda0/T247NYiOl6CDArPW6eWNjYpDjpnflBMyfVGBwxGU0gVoNRA8JId5QJ/qN+TbPTjs9V+8l8NILi6lFScOABH7JbbJbVlfQbFN39p618mRO6NT2ATqLDdAXnEPXdzP0w64TPgyBU092hdfvbmB8uU/D+5+719LMNNGsxWUOUDbn38TQfKLVIFoucT5lFGiMdq31n0F2XMs3Qr2OGPONr2WbCIqv9rjh9ppONtEM5YoGX6Zdc87Zs3vjr9JEbIdWTQdyLnUyZNIeB2vyZdHo2e9KFKhKTN/a0fWcvLSlIxGm0pweYNHheJ9Lq4Xj/Y6y0o/tnOoz4tuJ23SIF1dsSpO3y2xm62A8PIIfvUGaDsME5XYTsA+wJ4pyvWo5/Goms9MfjFt7rsXSzTT1Xsb7qvlBLJTRZhaIf03cQxwd2SIFHL0T8O3Iv0CzAHPjmhsru1jkkhXJFxV0uMoiHCIapww5OGk4oPtPLyi7DQbS90wo4VQdQPrz4xvixLbWVSpxUCHyYaIZlNL4xlz3MGJRO76kpApb0eDSi39nXUbThnhQlPuNVT+R2dXZQ/xGrlXIQDUag65sDVT3wfZU2TAh0OBXvpMevp1fcMhzmNrhJyQYrdmouPTZoVqRswxcOrKujQq8Xr8MkSXVIHyQ/UHsQkMk49Qky9B+1zFZyFbQfwXzitMiUWn2e/0vssVgyLFfd4u0buzoVBxP97XKuwy2i8sxbxGGVI10kwgm/tkdWs0uJsBQMr+58wSNtdNU8SyI+Ub970H6BAysz4MFqnbtbBHN9OlZqm8QxbrLpb7h2MuoOjqBXE4O4+SxDfYBAxvvBEAB0JEOWJ9u6OL4cU4rUy11TmysyssOBQLu9ZPXiEVfoYo7L3hLNqv6Q9tYIKX9UnTb0Bcxu1Ge9pHdY5BbGYDZZZOxedNiadBl9VheRDyGfUK/97AiDO7cP8xaRL7kyMTO8egm5LUuwon2379qGibTPuKn+6E69JeoNZ0CjGrKgzswka0WmdDfWi5BQ+N6pJ5wy+5argHzxwRg0/y/hH30Xam5UOPLreC+eKf4gJ9iGLyJGly7FJ+cdC4BqkWdIKXJBMl9nfFhDMKoxt66VorO6T+Nr5ZgQD6H1TTLZfylTSTq00zig9qWqtk78LoOAt74KVh9FyqcyrRZB5OkOja/bYYYN8oygtd2Z7I6CcQQcx4AVxqdfQI173t9+HMuPRcPtPbc69+xbRrlKn54wh8qV610aSwVbW+OKEl00y7D3yWef9RKq3aFrq5KGWxvT4dwxMCb7yMtUt86PHZZ57nlngQKVi3sPH6DNoZgV2/mkRMVUq5UN1hp7nsipqPKctCVX7zOVd+4MPAryLxjP5L/ytWYJcjKHi+wfP19Fx+IFb9svQwICeyDuXm7cYJ0Pm2amvTB614FdNkxeoRpe1dgPOxUMo273z3AQdwllTlHIMkodccdPONSlr85FZz2F5R/djMK9rZP5ViepA3zsF7bJ5rzsWvTQFV+HsR7SkZjUABVpGqFIXWSVt4qDCO2aMKDL6CuI1EDpiIdxm9zxrOjPreDH2nwGqaFlfSbT807WlIl7eTErwMK8rRrSyam3RYv3X2TpXckzD28EwX1TcrbYMain4AWLD8cpl24wWMIy8leMEVqUQkyJaDfKufQIfvqMbnVhUGG8GdVjyqZOG0L6sSmyWfrr4simGMLqBezb5BKqH+iC5j9OcoCAwtBjuluCQX6wjAR6/awz7eBv4/Azgbhxvu9Q8WDPnxyRHg5s0v1qh4Wyh7XPw2rgQrkjuxgjtvzLlaojtuwRwt4ymBX+uvJ8BDDYVfmHtYwtBoeNwzo2Vke883mwZxqkIHpQjL6YZswH+9RDGL661kyW8dfNNG9YTRo5bjYYQWn7PWUAzcD9+9O5iw1g/23X9ih1f6GPfrrvsdqVtIyMM5l1pdSacGWWuwewKrBSwVvWXwsylP4u0+r6SO5nOlp1HFBn0uyKkK0YXzTIxdMGz59j0MvPl5pmK593mTl5nIIm091gJe+km9tTy9UZFcupSKitg6NUMuWK5OqwHgc6/s6GO900swfK51Y2ROqAa0Qw0QGyPZL1i3DElYAWLGo3uBBucg7OnUSGW71TrVargE23jMgylvPU1gL5sDxuDJ2NUDea9fB4s0hPPUeu0Y5RUD2W5RV4yS8ISjlv72RgnaV1THtaiOv585ZfLNi5jOEKlVDtr6sl3VZfhEfZ9d6UHXSxbSNOci17Vni4WomElM0CYfBv54goJ5pXKptF51mfKbhfYBpHzbKuYlRiQ3euXa9DNAu4ISN4QutR1bZnNN9mJ+pfKqTNvqycotXFDlhxkgqminxv3ylnvNOx/zpddnZOHrcqMeO8NFLA3BcIHvsDhXzp9Ei4D3NgverTefYAGnklTJT3RaGagkfhdOlYYItENxavDZ9qSqfIJ9osGY3sYaIgx/dXyvMOT9mV3JnK33J2gbOkyuse+B2C+bmsodKMesbtNM1lguVtUlpp7hd6sw7KXRYAUvVvPsiZ0JepmPL7bNthgmhl1BPVmxhQuM1PtLhBdkUGxsOqbnzKnrg4l/gwNl4i6a6OjiqRH2c+iZl4vGnxJCTj4krPLpcij61L9i86dRiZHjrLtDxj7srXpi5e6jl5+JxRH+ZzHcFsAkYdfFd1cGsYwdVx/D55vZ8IeED+8EdBI/puyA6RhLlMQlcFiRRDExDEP7E5ekprDdF7tn7j80Y21vrXwju6jKBaEYEd9rbYEWvjxuBEo+fjVJX8KCZ1Zxt0rfckA7sxFfBYNkQ=
*/