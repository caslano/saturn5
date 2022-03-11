//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_MULTI_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_MULTI_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/interprocess/detail/multi_segment_services.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/containers/list.hpp>//list
#include <boost/interprocess/mapped_region.hpp> //mapped_region
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp> //managed_open_or_create_impl
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/streams/vectorstream.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <string> //string
#include <new>    //bad_alloc
#include <ostream>//std::ends

#include <boost/assert.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>

//!\file
//!Describes a named shared memory object allocation user class.

namespace boost {

namespace interprocess {

//TODO: We must somehow obtain the permissions of the first segment
//to apply them to subsequent segments
//-Use GetSecurityInfo?
//-Change everything to use only a shared memory object expanded via truncate()?

//!A basic shared memory named object creation class. Initializes the
//!shared memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, MemoryAlgorithm, IndexType>
template
      <
         class CharType,
         class MemoryAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_multi_shared_memory
   :  public ipcdetail::basic_managed_memory_impl
         <CharType, MemoryAlgorithm, IndexType>
{

   typedef basic_managed_multi_shared_memory
               <CharType, MemoryAlgorithm, IndexType>    self_t;
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, MemoryAlgorithm, IndexType>             base_t;

   typedef typename MemoryAlgorithm::void_pointer        void_pointer;
   typedef typename ipcdetail::
      managed_open_or_create_impl<shared_memory_object, MemoryAlgorithm::Alignment, true, false>  managed_impl;
   typedef typename void_pointer::segment_group_id       segment_group_id;
   typedef typename base_t::size_type                   size_type;

   ////////////////////////////////////////////////////////////////////////
   //
   //               Some internal helper structs/functors
   //
   ////////////////////////////////////////////////////////////////////////
   //!This class defines an operator() that creates a shared memory
   //!of the requested size. The rest of the parameters are
   //!passed in the constructor. The class a template parameter
   //!to be used with create_from_file/create_from_istream functions
   //!of basic_named_object classes

//   class segment_creator
//   {
//      public:
//      segment_creator(shared_memory &shmem,
//                      const char *mem_name,
//                      const void *addr)
//      : m_shmem(shmem), m_mem_name(mem_name), m_addr(addr){}
//
//      void *operator()(size_type size)
//      {
//         if(!m_shmem.create(m_mem_name, size, m_addr))
//            return 0;
//         return m_shmem.get_address();
//      }
//      private:
//      shared_memory &m_shmem;
//      const char *m_mem_name;
//      const void *m_addr;
//   };

   class group_services
      :  public multi_segment_services
   {
      public:
      typedef std::pair<void *, size_type>                  result_type;
      typedef basic_managed_multi_shared_memory             frontend_t;
      typedef typename
         basic_managed_multi_shared_memory::void_pointer    void_pointer;
      typedef typename void_pointer::segment_group_id       segment_group_id;
      group_services(frontend_t *const frontend)
         :  mp_frontend(frontend), m_group(0), m_min_segment_size(0){}

      virtual std::pair<void *, size_type> create_new_segment(size_type alloc_size)
      {  (void)alloc_size;
         /*
         //We should allocate an extra byte so that the
         //[base_addr + alloc_size] byte belongs to this segment
         alloc_size += 1;

         //If requested size is less than minimum, update that
         alloc_size = (m_min_segment_size > alloc_size) ?
                       m_min_segment_size : alloc_size;
         if(mp_frontend->priv_new_segment(create_open_func::DoCreate,
                                          alloc_size, 0, permissions())){
            typename shmem_list_t::value_type &m_impl = *mp_frontend->m_shmem_list.rbegin();
            return result_type(m_impl.get_real_address(), m_impl.get_real_size()-1);
         }*/
         return result_type(static_cast<void *>(0), 0);
      }

      virtual bool update_segments ()
      {  return true;   }

      virtual ~group_services(){}

      void set_group(segment_group_id group)
         {  m_group = group;  }

      segment_group_id get_group() const
         {  return m_group;  }

      void set_min_segment_size(size_type min_segment_size)
         {  m_min_segment_size = min_segment_size;  }

      size_type get_min_segment_size() const
         {  return m_min_segment_size;  }

      private:

      frontend_t * const   mp_frontend;
      segment_group_id     m_group;
      size_type            m_min_segment_size;
   };

   //!Functor to execute atomically when opening or creating a shared memory
   //!segment.
   struct create_open_func
   {
      enum type_t {  DoCreate, DoOpen, DoOpenOrCreate  };
      typedef typename
         basic_managed_multi_shared_memory::void_pointer   void_pointer;

      create_open_func(self_t * const    frontend,
                       type_t type, size_type segment_number)
         : mp_frontend(frontend), m_type(type), m_segment_number(segment_number){}

      bool operator()(void *addr, size_type size, bool created) const
      {
         if(((m_type == DoOpen)   &&  created) ||
            ((m_type == DoCreate) && !created))
            return false;
         segment_group_id group = mp_frontend->m_group_services.get_group();
         bool mapped       = false;
         bool impl_done    = false;

         //Associate this newly created segment as the
         //segment id = 0 of this group
         void_pointer::insert_mapping
            ( group
            , static_cast<char*>(addr) - managed_impl::ManagedOpenOrCreateUserOffset
            , size + managed_impl::ManagedOpenOrCreateUserOffset);
         //Check if this is the master segment
         if(!m_segment_number){
            //Create or open the Interprocess machinery
            if((impl_done = created ?
               mp_frontend->create_impl(addr, size) : mp_frontend->open_impl(addr, size))){
               return true;
            }
         }
         else{
            return true;
         }

         //This is the cleanup part
         //---------------
         if(impl_done){
            mp_frontend->close_impl();
         }
         if(mapped){
            bool ret = void_pointer::erase_last_mapping(group);
            BOOST_ASSERT(ret);(void)ret;
         }
         return false;
      }

      static std::size_t get_min_size()
      {
         const size_type sz = self_t::segment_manager::get_min_size();
         if(sz > std::size_t(-1)){
            //The minimum size is not representable by std::size_t
            BOOST_ASSERT(false);
            return std::size_t(-1);
         }
         else{
            return static_cast<std::size_t>(sz);
         }
      }

      self_t * const    mp_frontend;
      type_t            m_type;
      size_type         m_segment_number;
   };

   //!Functor to execute atomically when closing a shared memory segment.
   struct close_func
   {
      typedef typename
         basic_managed_multi_shared_memory::void_pointer   void_pointer;

      close_func(self_t * const frontend)
         : mp_frontend(frontend){}

      void operator()(const mapped_region &region, bool last) const
      {
         if(last) mp_frontend->destroy_impl();
         else     mp_frontend->close_impl();
      }
      self_t * const    mp_frontend;
   };

   //Friend declarations
   friend struct basic_managed_multi_shared_memory::create_open_func;
   friend struct basic_managed_multi_shared_memory::close_func;
   friend class basic_managed_multi_shared_memory::group_services;

   typedef list<managed_impl> shmem_list_t;

   basic_managed_multi_shared_memory *get_this_pointer()
      {  return this;   }

 public:

   basic_managed_multi_shared_memory(create_only_t,
                                     const char *name,
                                     size_type size,
                                     const permissions &perm = permissions())
      :  m_group_services(get_this_pointer())
   {
      priv_open_or_create(create_open_func::DoCreate,name, size, perm);
   }

   basic_managed_multi_shared_memory(open_or_create_t,
                                     const char *name,
                                     size_type size,
                                     const permissions &perm = permissions())
      :  m_group_services(get_this_pointer())
   {
      priv_open_or_create(create_open_func::DoOpenOrCreate, name, size, perm);
   }

   basic_managed_multi_shared_memory(open_only_t, const char *name)
      :  m_group_services(get_this_pointer())
   {
      priv_open_or_create(create_open_func::DoOpen, name, 0, permissions());
   }

   ~basic_managed_multi_shared_memory()
      {  this->priv_close(); }

   private:
   bool  priv_open_or_create(typename create_open_func::type_t type,
                             const char *name,
                             size_type size,
                             const permissions &perm)
   {
      if(!m_shmem_list.empty())
         return false;
      typename void_pointer::segment_group_id group = 0;
      BOOST_TRY{
         m_root_name = name;
         //Insert multi segment services and get a group identifier
         group = void_pointer::new_segment_group(&m_group_services);
         size = void_pointer::round_size(size);
         m_group_services.set_group(group);
         m_group_services.set_min_segment_size(size);

         if(group){
            if(this->priv_new_segment(type, size, 0, perm)){
               return true;
            }
         }
      }
      BOOST_CATCH(const std::bad_alloc&){
      }
      BOOST_CATCH_END
      if(group){
         void_pointer::delete_group(group);
      }
      return false;
   }

   bool  priv_new_segment(typename create_open_func::type_t type,
                          size_type size,
                          const void *addr,
                          const permissions &perm)
   {
      BOOST_TRY{
         //Get the number of groups of this multi_segment group
         size_type segment_id  = m_shmem_list.size();
         //Format the name of the shared memory: append segment number.
         boost::interprocess::basic_ovectorstream<boost::interprocess::string> formatter;
         //Pre-reserve string size
         size_type str_size = m_root_name.length()+10;
         if(formatter.vector().size() < str_size){
            //This can throw.
            formatter.reserve(str_size);
         }
         //Format segment's name
         formatter << m_root_name
                   << static_cast<unsigned int>(segment_id) << std::ends;
         //This functor will be executed when constructing
         create_open_func func(this, type, segment_id);
         const char *name = formatter.vector().c_str();
         //This can throw.
         managed_impl mshm;

         switch(type){
            case create_open_func::DoCreate:
            {
               managed_impl shm(create_only, name, size, read_write, addr, func, perm);
               mshm = boost::move(shm);
            }
            break;

            case create_open_func::DoOpen:
            {
               managed_impl shm(open_only, name,read_write, addr, func);
               mshm = boost::move(shm);
            }
            break;

            case create_open_func::DoOpenOrCreate:
            {
               managed_impl shm(open_or_create, name, size, read_write, addr, func, perm);
               mshm = boost::move(shm);
            }
            break;

            default:
               return false;
            break;
         }

         //This can throw.
         m_shmem_list.push_back(boost::move(mshm));
         return true;
      }
      BOOST_CATCH(const std::bad_alloc&){
      }
      BOOST_CATCH_END
      return false;
   }

   //!Frees resources. Never throws.
   void priv_close()
   {
      if(!m_shmem_list.empty()){
         bool ret;
         //Obtain group identifier
         segment_group_id group = m_group_services.get_group();
         //Erase main segment and its resources
         //typename shmem_list_t::iterator  itbeg = m_shmem_list.begin(),
         //                        itend = m_shmem_list.end(),
         //                        it    = itbeg;
         //(*itbeg)->close_with_func(close_func(this));
         //Delete group. All mappings are erased too.
         ret = void_pointer::delete_group(group);
         (void)ret;
         BOOST_ASSERT(ret);
         m_shmem_list.clear();
      }
   }

   private:
   shmem_list_t   m_shmem_list;
   group_services m_group_services;
   std::string    m_root_name;
};

typedef basic_managed_multi_shared_memory
   < char
   , rbtree_best_fit<mutex_family, intersegment_ptr<void> >
   , iset_index>
   managed_multi_shared_memory;

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_MULTI_SHARED_MEMORY_HPP


/* managed_multi_shared_memory.hpp
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
*/