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

      virtual std::pair<void *, size_type> create_new_segment(size_type alloc_size) BOOST_OVERRIDE
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

      virtual bool update_segments BOOST_OVERRIDE ()
      {  return true;   }

      virtual ~group_services() BOOST_OVERRIDE{}

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