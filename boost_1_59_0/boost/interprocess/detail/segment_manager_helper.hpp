//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SEGMENT_MANAGER_BASE_HPP
#define BOOST_INTERPROCESS_SEGMENT_MANAGER_BASE_HPP

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
#include <boost/interprocess/exceptions.hpp>
// interprocess/detail
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/in_place_interface.hpp>
// container/detail
#include <boost/container/detail/type_traits.hpp> //alignment_of
#include <boost/container/detail/minimal_char_traits_header.hpp>
// intrusive
#include <boost/intrusive/pointer_traits.hpp>
// move/detail
#include <boost/move/detail/type_traits.hpp> //make_unsigned
#include <boost/move/detail/force_ptr.hpp>
// other boost
#include <boost/assert.hpp>   //BOOST_ASSERT
#include <boost/core/no_exceptions_support.hpp>
// std
#include <cstddef>   //std::size_t

//!\file
//!Describes the object placed in a memory segment that provides
//!named object allocation capabilities.

namespace boost{
namespace interprocess{

template<class MemoryManager>
class segment_manager_base;

//!An integer that describes the type of the
//!instance constructed in memory
enum instance_type {   anonymous_type, named_type, unique_type, max_allocation_type };

namespace ipcdetail{

template<class MemoryAlgorithm>
class mem_algo_deallocator
{
   void *            m_ptr;
   MemoryAlgorithm & m_algo;

   public:
   mem_algo_deallocator(void *ptr, MemoryAlgorithm &algo)
      :  m_ptr(ptr), m_algo(algo)
   {}

   void release()
   {  m_ptr = 0;  }

   ~mem_algo_deallocator()
   {  if(m_ptr) m_algo.deallocate(m_ptr);  }
};

template<class size_type>
struct block_header
{
   size_type      m_value_bytes;
   unsigned short m_num_char;
   unsigned char  m_value_alignment;
   unsigned char  m_alloc_type_sizeof_char;

   block_header(size_type val_bytes
               ,size_type val_alignment
               ,unsigned char al_type
               ,std::size_t szof_char
               ,std::size_t num_char
               )
      :  m_value_bytes(val_bytes)
      ,  m_num_char((unsigned short)num_char)
      ,  m_value_alignment((unsigned char)val_alignment)
      ,  m_alloc_type_sizeof_char( (unsigned char)((al_type << 5u) | ((unsigned char)szof_char & 0x1F)) )
   {};

   template<class T>
   block_header &operator= (const T& )
   {  return *this;  }

   size_type total_size() const
   {
      if(alloc_type() != anonymous_type){
         return name_offset() + (m_num_char+1u)*sizeof_char();
      }
      else{
         return this->value_offset() + m_value_bytes;
      }
   }

   size_type value_bytes() const
   {  return m_value_bytes;   }

   template<class Header>
   size_type total_size_with_header() const
   {
      return get_rounded_size
               ( size_type(sizeof(Header))
            , size_type(::boost::container::dtl::alignment_of<block_header<size_type> >::value))
           + total_size();
   }

   unsigned char alloc_type() const
   {  return (m_alloc_type_sizeof_char >> 5u)&(unsigned char)0x7;  }

   unsigned char sizeof_char() const
   {  return m_alloc_type_sizeof_char & (unsigned char)0x1F;  }

   template<class CharType>
   CharType *name() const
   {
      return const_cast<CharType*>(move_detail::force_ptr<const CharType*>
         (reinterpret_cast<const char*>(this) + name_offset()));
   }

   unsigned short name_length() const
   {  return m_num_char;   }

   size_type name_offset() const
   {
      return this->value_offset() + get_rounded_size(size_type(m_value_bytes), size_type(sizeof_char()));
   }

   void *value() const
   {
      return const_cast<char*>((reinterpret_cast<const char*>(this) + this->value_offset()));
   }

   size_type value_offset() const
   {
      return get_rounded_size(size_type(sizeof(block_header<size_type>)), size_type(m_value_alignment));
   }

   template<class CharType>
   bool less_comp(const block_header<size_type> &b) const
   {
      return m_num_char < b.m_num_char ||
             (m_num_char < b.m_num_char &&
              std::char_traits<CharType>::compare(name<CharType>(), b.name<CharType>(), m_num_char) < 0);
   }

   template<class CharType>
   bool equal_comp(const block_header<size_type> &b) const
   {
      return m_num_char == b.m_num_char &&
             std::char_traits<CharType>::compare(name<CharType>(), b.name<CharType>(), m_num_char) == 0;
   }

   template<class T>
   static block_header<size_type> *block_header_from_value(T *value)
   {  return block_header_from_value(value, sizeof(T), ::boost::container::dtl::alignment_of<T>::value);  }

   static block_header<size_type> *block_header_from_value(const void *value, std::size_t sz, std::size_t algn)
   {
      block_header * hdr =
         const_cast<block_header*>
            (move_detail::force_ptr<const block_header*>(reinterpret_cast<const char*>(value) -
               get_rounded_size(sizeof(block_header), algn)));
      (void)sz;
      //Some sanity checks
      BOOST_ASSERT(hdr->m_value_alignment == algn);
      BOOST_ASSERT(hdr->m_value_bytes % sz == 0);
      return hdr;
   }

   template<class Header>
   static block_header<size_type> *from_first_header(Header *header)
   {
      block_header<size_type> * hdr =
         move_detail::force_ptr<block_header<size_type>*>(reinterpret_cast<char*>(header) +
       get_rounded_size( size_type(sizeof(Header))
                       , size_type(::boost::container::dtl::alignment_of<block_header<size_type> >::value)));
      //Some sanity checks
      return hdr;
   }

   template<class Header>
   static Header *to_first_header(block_header<size_type> *bheader)
   {
      Header * hdr =
         move_detail::force_ptr<Header*>(reinterpret_cast<char*>(bheader) -
       get_rounded_size( size_type(sizeof(Header))
                       , size_type(::boost::container::dtl::alignment_of<block_header<size_type> >::value)));
      //Some sanity checks
      return hdr;
   }
};

inline void array_construct(void *mem, std::size_t num, in_place_interface &table)
{
   //Try constructors
   std::size_t constructed = 0;
   BOOST_TRY{
      table.construct_n(mem, num, constructed);
   }
   //If there is an exception call destructors and erase index node
   BOOST_CATCH(...){
      std::size_t destroyed = 0;
      table.destroy_n(mem, constructed, destroyed);
      BOOST_RETHROW
   } BOOST_CATCH_END
}

template<class CharT>
struct intrusive_compare_key
{
   typedef CharT char_type;

   intrusive_compare_key(const CharT *str, std::size_t len)
      :  mp_str(str), m_len(len)
   {}

   const CharT *  mp_str;
   std::size_t    m_len;
};

//!This struct indicates an anonymous object creation
//!allocation
template<instance_type type>
class instance_t
{
   instance_t(){}
};

template<class T>
struct char_if_void
{
   typedef T type;
};

template<>
struct char_if_void<void>
{
   typedef char type;
};

typedef instance_t<anonymous_type>  anonymous_instance_t;
typedef instance_t<unique_type>     unique_instance_t;


template<class Hook, class CharType, class SizeType>
struct intrusive_value_type_impl
   :  public Hook
{
   private:
   //Non-copyable
   intrusive_value_type_impl(const intrusive_value_type_impl &);
   intrusive_value_type_impl& operator=(const intrusive_value_type_impl &);

   public:
   typedef CharType char_type;
   typedef SizeType size_type;

   intrusive_value_type_impl(){}

   enum  {  BlockHdrAlignment = ::boost::container::dtl::alignment_of<block_header<size_type> >::value  };

   block_header<size_type> *get_block_header() const
   {
      return const_cast<block_header<size_type>*>
         (move_detail::force_ptr<const block_header<size_type> *>(reinterpret_cast<const char*>(this) +
            get_rounded_size(size_type(sizeof(*this)), size_type(BlockHdrAlignment))));
   }

   bool operator <(const intrusive_value_type_impl<Hook, CharType, SizeType> & other) const
   {  return (this->get_block_header())->template less_comp<CharType>(*other.get_block_header());  }

   bool operator ==(const intrusive_value_type_impl<Hook, CharType, SizeType> & other) const
   {  return (this->get_block_header())->template equal_comp<CharType>(*other.get_block_header());  }

   static intrusive_value_type_impl *get_intrusive_value_type(block_header<size_type> *hdr)
   {
      return move_detail::force_ptr<intrusive_value_type_impl*>(reinterpret_cast<char*>(hdr) -
         get_rounded_size(size_type(sizeof(intrusive_value_type_impl)), size_type(BlockHdrAlignment)));
   }

   CharType *name() const
   {  return get_block_header()->template name<CharType>(); }

   unsigned short name_length() const
   {  return get_block_header()->name_length(); }

   void *value() const
   {  return get_block_header()->value(); }
};

template<class CharType>
class char_ptr_holder
{
   public:
   char_ptr_holder(const CharType *name)
      : m_name(name)
   {}

   char_ptr_holder(const anonymous_instance_t *)
      : m_name(static_cast<CharType*>(0))
   {}

   char_ptr_holder(const unique_instance_t *)
      : m_name(reinterpret_cast<CharType*>(-1))
   {}

   operator const CharType *()
   {  return m_name;  }

   const CharType *get() const
   {  return m_name;  }

   bool is_unique() const
   {  return m_name == reinterpret_cast<CharType*>(-1);  }

   bool is_anonymous() const
   {  return m_name == static_cast<CharType*>(0);  }

   private:
   const CharType *m_name;
};

//!The key of the the named allocation information index. Stores an offset pointer
//!to a null terminated string and the length of the string to speed up sorting
template<class CharT, class VoidPointer>
struct index_key
{
   typedef typename boost::intrusive::
      pointer_traits<VoidPointer>::template
         rebind_pointer<const CharT>::type               const_char_ptr_t;
   typedef CharT                                         char_type;
   typedef typename boost::intrusive::pointer_traits<const_char_ptr_t>::difference_type difference_type;
   typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;

   private:
   //Offset pointer to the object's name
   const_char_ptr_t  mp_str;
   //Length of the name buffer (null NOT included)
   size_type         m_len;
   public:

   //!Constructor of the key
   index_key (const char_type *nm, size_type length)
      : mp_str(nm), m_len(length)
   {}

   //!Less than function for index ordering
   bool operator < (const index_key & right) const
   {
      return (m_len < right.m_len) ||
               (m_len == right.m_len &&
                std::char_traits<char_type>::compare
                  (to_raw_pointer(mp_str),to_raw_pointer(right.mp_str), m_len) < 0);
   }

   //!Equal to function for index ordering
   bool operator == (const index_key & right) const
   {
      return   m_len == right.m_len &&
               std::char_traits<char_type>::compare
                  (to_raw_pointer(mp_str), to_raw_pointer(right.mp_str), m_len) == 0;
   }

   void name(const CharT *nm)
   {  mp_str = nm; }

   void name_length(size_type len)
   {  m_len = len; }

   const CharT *name() const
   {  return to_raw_pointer(mp_str); }

   size_type name_length() const
   {  return m_len; }
};

//!The index_data stores a pointer to a buffer and the element count needed
//!to know how many destructors must be called when calling destroy
template<class VoidPointer>
struct index_data
{
   typedef VoidPointer void_pointer;
   void_pointer    m_ptr;
   explicit index_data(void *ptr) : m_ptr(ptr){}

   void *value() const
   {  return static_cast<void*>(to_raw_pointer(m_ptr));  }
};

template<class MemoryAlgorithm>
struct segment_manager_base_type
{  typedef segment_manager_base<MemoryAlgorithm> type;   };

template<class CharT, class MemoryAlgorithm>
struct index_config
{
   typedef typename MemoryAlgorithm::void_pointer        void_pointer;
   typedef CharT                                         char_type;
   typedef index_key<CharT, void_pointer>        key_type;
   typedef index_data<void_pointer>              mapped_type;
   typedef typename segment_manager_base_type
      <MemoryAlgorithm>::type                            segment_manager_base;

   template<class HeaderBase>
   struct intrusive_value_type
   {  typedef intrusive_value_type_impl<HeaderBase, CharT, typename segment_manager_base::size_type>  type; };

   typedef intrusive_compare_key<CharT>            intrusive_compare_key_type;
};

template<class Iterator, bool intrusive>
class segment_manager_iterator_value_adaptor
{
   typedef typename Iterator::value_type        iterator_val_t;
   typedef typename iterator_val_t::char_type   char_type;

   public:
   segment_manager_iterator_value_adaptor(const typename Iterator::value_type &val)
      :  m_val(&val)
   {}

   const char_type *name() const
   {  return m_val->name(); }

   unsigned short name_length() const
   {  return m_val->name_length(); }

   const void *value() const
   {  return m_val->value(); }

   const typename Iterator::value_type *m_val;
};


template<class Iterator>
class segment_manager_iterator_value_adaptor<Iterator, false>
{
   typedef typename Iterator::value_type        iterator_val_t;
   typedef typename iterator_val_t::first_type  first_type;
   typedef typename iterator_val_t::second_type second_type;
   typedef typename first_type::char_type       char_type;
   typedef typename first_type::size_type       size_type;

   public:
   segment_manager_iterator_value_adaptor(const typename Iterator::value_type &val)
      :  m_val(&val)
   {}

   const char_type *name() const
   {  return m_val->first.name(); }

   size_type name_length() const
   {  return m_val->first.name_length(); }

   const void *value() const
   {
      return move_detail::force_ptr<block_header<size_type>*>
         (to_raw_pointer(m_val->second.m_ptr))->value();
   }

   const typename Iterator::value_type *m_val;
};

template<class Iterator, bool intrusive>
struct segment_manager_iterator_transform
{
   typedef segment_manager_iterator_value_adaptor<Iterator, intrusive> result_type;

   template <class T> result_type operator()(const T &arg) const
   {  return result_type(arg); }
};

}  //namespace ipcdetail {

//These pointers are the ones the user will use to
//indicate previous allocation types
static const ipcdetail::anonymous_instance_t   * anonymous_instance = 0;
static const ipcdetail::unique_instance_t      * unique_instance = 0;

namespace ipcdetail_really_deep_namespace {

//Otherwise, gcc issues a warning of previously defined
//anonymous_instance and unique_instance
struct dummy
{
   dummy()
   {
      (void)anonymous_instance;
      (void)unique_instance;
   }
};

}  //detail_really_deep_namespace

}} //namespace boost { namespace interprocess

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_SEGMENT_MANAGER_BASE_HPP


/* segment_manager_helper.hpp
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
*/