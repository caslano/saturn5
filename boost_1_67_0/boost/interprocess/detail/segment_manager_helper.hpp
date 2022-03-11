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
      ,  m_alloc_type_sizeof_char( (al_type << 5u) | ((unsigned char)szof_char & 0x1F) )
   {};

   template<class T>
   block_header &operator= (const T& )
   {  return *this;  }

   size_type total_size() const
   {
      if(alloc_type() != anonymous_type){
         return name_offset() + (m_num_char+1)*sizeof_char();
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
      return const_cast<CharType*>(reinterpret_cast<const CharType*>
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
            (reinterpret_cast<const block_header*>(reinterpret_cast<const char*>(value) -
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
         reinterpret_cast<block_header<size_type>*>(reinterpret_cast<char*>(header) +
       get_rounded_size( size_type(sizeof(Header))
                       , size_type(::boost::container::dtl::alignment_of<block_header<size_type> >::value)));
      //Some sanity checks
      return hdr;
   }

   template<class Header>
   static Header *to_first_header(block_header<size_type> *bheader)
   {
      Header * hdr =
         reinterpret_cast<Header*>(reinterpret_cast<char*>(bheader) -
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
   }
   BOOST_CATCH_END
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
         (reinterpret_cast<const block_header<size_type> *>(reinterpret_cast<const char*>(this) +
            get_rounded_size(size_type(sizeof(*this)), size_type(BlockHdrAlignment))));
   }

   bool operator <(const intrusive_value_type_impl<Hook, CharType, SizeType> & other) const
   {  return (this->get_block_header())->template less_comp<CharType>(*other.get_block_header());  }

   bool operator ==(const intrusive_value_type_impl<Hook, CharType, SizeType> & other) const
   {  return (this->get_block_header())->template equal_comp<CharType>(*other.get_block_header());  }

   static intrusive_value_type_impl *get_intrusive_value_type(block_header<size_type> *hdr)
   {
      return reinterpret_cast<intrusive_value_type_impl *>(reinterpret_cast<char*>(hdr) -
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
      return reinterpret_cast<block_header<size_type>*>
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