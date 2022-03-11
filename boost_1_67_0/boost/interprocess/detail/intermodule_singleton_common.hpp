//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_INTERMODULE_SINGLETON_COMMON_HPP
#define BOOST_INTERPROCESS_INTERMODULE_SINGLETON_COMMON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/container/detail/type_traits.hpp>  //alignment_of, aligned_storage
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/sync/spin/wait.hpp>
#include <boost/assert.hpp>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>

namespace boost{
namespace interprocess{
namespace ipcdetail{

namespace intermodule_singleton_helpers {

inline void get_pid_creation_time_str(std::string &s)
{
   std::stringstream stream;
   stream << get_current_process_id() << '_';
   stream.precision(6);
   stream << std::fixed << get_current_process_creation_time();
   s = stream.str();
}

inline const char *get_map_base_name()
{  return "bip.gmem.map.";  }

inline void get_map_name(std::string &map_name)
{
   get_pid_creation_time_str(map_name);
   map_name.insert(0, get_map_base_name());
}

inline std::size_t get_map_size()
{  return 65536;  }

template<class ThreadSafeGlobalMap>
struct thread_safe_global_map_dependant;

}  //namespace intermodule_singleton_helpers {

//This class contains common code for all singleton types, so that we instantiate this
//code just once per module. This class also holds a thread soafe global map
//to be used by all instances protected with a reference count
template<class ThreadSafeGlobalMap>
class intermodule_singleton_common
{
   public:
   typedef void*(singleton_constructor_t)(ThreadSafeGlobalMap &);
   typedef void (singleton_destructor_t)(void *, ThreadSafeGlobalMap &);

   static const ::boost::uint32_t Uninitialized       = 0u;
   static const ::boost::uint32_t Initializing        = 1u;
   static const ::boost::uint32_t Initialized         = 2u;
   static const ::boost::uint32_t Broken              = 3u;
   static const ::boost::uint32_t Destroyed           = 4u;

   //Initialize this_module_singleton_ptr, creates the global map if needed and also creates an unique
   //opaque type in global map through a singleton_constructor_t function call,
   //initializing the passed pointer to that unique instance.
   //
   //We have two concurrency types here. a)the global map/singleton creation must
   //be safe between threads of this process but in different modules/dlls. b)
   //the pointer to the singleton is per-module, so we have to protect this
   //initization between threads of the same module.
   //
   //All static variables declared here are shared between inside a module
   //so atomic operations will synchronize only threads of the same module.
   static void initialize_singleton_logic
      (void *&ptr, volatile boost::uint32_t &this_module_singleton_initialized, singleton_constructor_t constructor, bool phoenix)
   {
      //If current module is not initialized enter to lock free logic
      if(atomic_read32(&this_module_singleton_initialized) != Initialized){
         //Now a single thread of the module will succeed in this CAS.
         //trying to pass from Uninitialized to Initializing
         ::boost::uint32_t previous_module_singleton_initialized = atomic_cas32
            (&this_module_singleton_initialized, Initializing, Uninitialized);
         //If the thread succeeded the CAS (winner) it will compete with other
         //winner threads from other modules to create the global map
         if(previous_module_singleton_initialized == Destroyed){
            //Trying to resurrect a dead Phoenix singleton. Just try to
            //mark it as uninitialized and start again
            if(phoenix){
               atomic_cas32(&this_module_singleton_initialized, Uninitialized, Destroyed);
               previous_module_singleton_initialized = atomic_cas32
                  (&this_module_singleton_initialized, Initializing, Uninitialized);
            }
            //Trying to resurrect a non-Phoenix dead singleton is an error
            else{
               throw interprocess_exception("Boost.Interprocess: Dead reference on non-Phoenix singleton of type");
            }
         }
         if(previous_module_singleton_initialized == Uninitialized){
            try{
               //Now initialize the global map, this function must solve concurrency
               //issues between threads of several modules
               initialize_global_map_handle();
               //Now try to create the singleton in global map.
               //This function solves concurrency issues
               //between threads of several modules
               ThreadSafeGlobalMap *const pmap = get_map_ptr();
               void *tmp = constructor(*pmap);
               //Increment the module reference count that reflects how many
               //singletons this module holds, so that we can safely destroy
               //module global map object when no singleton is left
               atomic_inc32(&this_module_singleton_count);
               //Insert a barrier before assigning the pointer to
               //make sure this assignment comes after the initialization
               atomic_write32(&this_module_singleton_initialized, Initializing);
               //Assign the singleton address to the module-local pointer
               ptr = tmp;
               //Memory barrier inserted, all previous operations should complete
               //before this one. Now marked as initialized
               atomic_write32(&this_module_singleton_initialized, Initialized);
            }
            catch(...){
               //Mark singleton failed to initialize
               atomic_write32(&this_module_singleton_initialized, Broken);
               throw;
            }
         }
         //If previous state was initializing, this means that another winner thread is
         //trying to initialize the singleton. Just wait until completes its work.
         else if(previous_module_singleton_initialized == Initializing){
            spin_wait swait;
            while(1){
               previous_module_singleton_initialized = atomic_read32(&this_module_singleton_initialized);
               if(previous_module_singleton_initialized >= Initialized){
                  //Already initialized, or exception thrown by initializer thread
                  break;
               }
               else if(previous_module_singleton_initialized == Initializing){
                  swait.yield();
               }
               else{
                  //This can't be happening!
                  BOOST_ASSERT(0);
               }
            }
         }
         else if(previous_module_singleton_initialized == Initialized){
            //Nothing to do here, the singleton is ready
         }
         //If previous state was greater than initialized, then memory is broken
         //trying to initialize the singleton.
         else{//(previous_module_singleton_initialized > Initialized)
            throw interprocess_exception("boost::interprocess::intermodule_singleton initialization failed");
         }
      }
      BOOST_ASSERT(ptr != 0);
   }

   static void finalize_singleton_logic(void *&ptr, volatile boost::uint32_t &this_module_singleton_initialized, singleton_destructor_t destructor)
   {
      //Protect destruction against lazy singletons not initialized in this execution
      if(ptr){
         //Note: this destructor might provoke a Phoenix singleton
         //resurrection. This means that this_module_singleton_count
         //might change after this call.
         ThreadSafeGlobalMap * const pmap = get_map_ptr();
         destructor(ptr, *pmap);
         ptr = 0;

         //Memory barrier to make sure pointer is nulled.
         //Mark this singleton as destroyed.
         atomic_write32(&this_module_singleton_initialized, Destroyed);

         //If this is the last singleton of this module
         //apply map destruction.
         //Note: singletons are destroyed when the module is unloaded
         //so no threads should be executing or holding references
         //to this module
         if(1 == atomic_dec32(&this_module_singleton_count)){
            destroy_global_map_handle();
         }
      }
   }

   private:
   static ThreadSafeGlobalMap *get_map_ptr()
   {
      return static_cast<ThreadSafeGlobalMap *>(static_cast<void*>(mem_holder.map_mem));
   }

   static void initialize_global_map_handle()
   {
      //Obtain unique map name and size
      spin_wait swait;
      while(1){
         //Try to pass map state to initializing
         ::boost::uint32_t tmp = atomic_cas32(&this_module_map_initialized, Initializing, Uninitialized);
         if(tmp == Initialized || tmp == Broken){
            break;
         }
         else if(tmp == Destroyed){
            tmp = atomic_cas32(&this_module_map_initialized, Uninitialized, Destroyed);
            continue;
         }
         //If some other thread is doing the work wait
         else if(tmp == Initializing){
            swait.yield();
         }
         else{ //(tmp == Uninitialized)
            //If not initialized try it again?
            try{
               //Remove old global map from the system
               intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::remove_old_gmem();
               //in-place construction of the global map class
               ThreadSafeGlobalMap * const pmap = get_map_ptr();
               intermodule_singleton_helpers::thread_safe_global_map_dependant
                  <ThreadSafeGlobalMap>::construct_map(static_cast<void*>(pmap));
               //Use global map's internal lock to initialize the lock file
               //that will mark this gmem as "in use".
               typename intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::
                  lock_file_logic f(*pmap);
               //If function failed (maybe a competing process has erased the shared
               //memory between creation and file locking), retry with a new instance.
               if(f.retry()){
                  pmap->~ThreadSafeGlobalMap();
                  atomic_write32(&this_module_map_initialized, Destroyed);
               }
               else{
                  //Locking succeeded, so this global map module-instance is ready
                  atomic_write32(&this_module_map_initialized, Initialized);
                  break;
               }
            }
            catch(...){
               //
               throw;
            }
         }
      }
   }

   static void destroy_global_map_handle()
   {
      if(!atomic_read32(&this_module_singleton_count)){
         //This module is being unloaded, so destroy
         //the global map object of this module
         //and unlink the global map if it's the last
         ThreadSafeGlobalMap * const pmap = get_map_ptr();
         typename intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::
            unlink_map_logic f(*pmap);
         pmap->~ThreadSafeGlobalMap();
         atomic_write32(&this_module_map_initialized, Destroyed);
         //Do some cleanup for other processes old gmem instances
         intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::remove_old_gmem();
      }
   }

   //Static data, zero-initalized without any dependencies
   //this_module_singleton_count is the number of singletons used by this module
   static volatile boost::uint32_t this_module_singleton_count;

   //this_module_map_initialized is the state of this module's map class object.
   //Values: Uninitialized, Initializing, Initialized, Broken
   static volatile boost::uint32_t this_module_map_initialized;

   //Raw memory to construct the global map manager
   static union mem_holder_t
   {
      unsigned char map_mem [sizeof(ThreadSafeGlobalMap)];
      ::boost::container::dtl::max_align_t aligner;
   } mem_holder;
};

template<class ThreadSafeGlobalMap>
volatile boost::uint32_t intermodule_singleton_common<ThreadSafeGlobalMap>::this_module_singleton_count;

template<class ThreadSafeGlobalMap>
volatile boost::uint32_t intermodule_singleton_common<ThreadSafeGlobalMap>::this_module_map_initialized;

template<class ThreadSafeGlobalMap>
typename intermodule_singleton_common<ThreadSafeGlobalMap>::mem_holder_t
   intermodule_singleton_common<ThreadSafeGlobalMap>::mem_holder;

//A reference count to be stored in global map holding the number
//of singletons (one per module) attached to the instance pointed by
//the internal ptr.
struct ref_count_ptr
{
   ref_count_ptr(void *p, boost::uint32_t count)
      : ptr(p), singleton_ref_count(count)
   {}
   void *ptr;
   //This reference count serves to count the number of attached
   //modules to this singleton
   volatile boost::uint32_t singleton_ref_count;
};


//Now this class is a singleton, initializing the singleton in
//the first get() function call if LazyInit is true. If false
//then the singleton will be initialized when loading the module.
template<typename C, bool LazyInit, bool Phoenix, class ThreadSafeGlobalMap>
class intermodule_singleton_impl
{
   public:

   static C& get()   //Let's make inlining easy
   {
      if(!this_module_singleton_ptr){
         if(lifetime.dummy_function()){  //This forces lifetime instantiation, for reference counted destruction
            atentry_work();
         }
      }
      return *static_cast<C*>(this_module_singleton_ptr);
   }

   private:

   static void atentry_work()
   {
      intermodule_singleton_common<ThreadSafeGlobalMap>::initialize_singleton_logic
         (this_module_singleton_ptr, this_module_singleton_initialized, singleton_constructor, Phoenix);
   }

   static void atexit_work()
   {
      intermodule_singleton_common<ThreadSafeGlobalMap>::finalize_singleton_logic
         (this_module_singleton_ptr, this_module_singleton_initialized, singleton_destructor);
   }

   //These statics will be zero-initialized without any constructor call dependency
   //this_module_singleton_ptr will be a module-local pointer to the singleton
   static void*                      this_module_singleton_ptr;

   //this_module_singleton_count will be used to synchronize threads of the same module
   //for access to a singleton instance, and to flag the state of the
   //singleton.
   static volatile boost::uint32_t   this_module_singleton_initialized;

   //This class destructor will trigger singleton destruction
   struct lifetime_type_lazy
   {
      bool dummy_function()
      {  return m_dummy == 0; }

      ~lifetime_type_lazy()
      {
         //if(!Phoenix){
            //atexit_work();
         //}
      }

      //Dummy volatile so that the compiler can't resolve its value at compile-time
      //and can't avoid lifetime_type instantiation if dummy_function() is called.
      static volatile int m_dummy;
   };

   struct lifetime_type_static
      : public lifetime_type_lazy
   {
      lifetime_type_static()
      {  atentry_work();  }
   };

   typedef typename if_c
      <LazyInit, lifetime_type_lazy, lifetime_type_static>::type lifetime_type;

   static lifetime_type lifetime;

   //A functor to be executed inside global map lock that just
   //searches for the singleton in map and if not present creates a new one.
   //If singleton constructor throws, the exception is propagated
   struct init_atomic_func
   {
      init_atomic_func(ThreadSafeGlobalMap &m)
         : m_map(m), ret_ptr()
      {}

      void operator()()
      {
         ref_count_ptr *rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
            <ThreadSafeGlobalMap>::find(m_map, typeid(C).name());
         if(!rcount){
            C *p = new C;
            try{
               ref_count_ptr val(p, 0u);
               rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
                           <ThreadSafeGlobalMap>::insert(m_map, typeid(C).name(), val);
            }
            catch(...){
               intermodule_singleton_helpers::thread_safe_global_map_dependant
                           <ThreadSafeGlobalMap>::erase(m_map, typeid(C).name());
               delete p;
               throw;
            }
         }
         //if(Phoenix){
            std::atexit(&atexit_work);
         //}
         atomic_inc32(&rcount->singleton_ref_count);
         ret_ptr = rcount->ptr;
      }
      void *data() const
         { return ret_ptr;  }

      private:
      ThreadSafeGlobalMap &m_map;
      void *ret_ptr;
   };

   //A functor to be executed inside global map lock that just
   //deletes the singleton in map if the attached count reaches to zero
   struct fini_atomic_func
   {
      fini_atomic_func(ThreadSafeGlobalMap &m)
         : m_map(m)
      {}

      void operator()()
      {
         ref_count_ptr *rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
            <ThreadSafeGlobalMap>::find(m_map, typeid(C).name());
            //The object must exist
         BOOST_ASSERT(rcount);
         BOOST_ASSERT(rcount->singleton_ref_count > 0);
         //Check if last reference
         if(atomic_dec32(&rcount->singleton_ref_count) == 1){
            //If last, destroy the object
            BOOST_ASSERT(rcount->ptr != 0);
            C *pc = static_cast<C*>(rcount->ptr);
            //Now destroy map entry
            bool destroyed = intermodule_singleton_helpers::thread_safe_global_map_dependant
                        <ThreadSafeGlobalMap>::erase(m_map, typeid(C).name());
            (void)destroyed;  BOOST_ASSERT(destroyed == true);
            delete pc;
         }
      }

      private:
      ThreadSafeGlobalMap &m_map;
   };

   //A wrapper to execute init_atomic_func
   static void *singleton_constructor(ThreadSafeGlobalMap &map)
   {
      init_atomic_func f(map);
      intermodule_singleton_helpers::thread_safe_global_map_dependant
                  <ThreadSafeGlobalMap>::atomic_func(map, f);
      return f.data();
   }

   //A wrapper to execute fini_atomic_func
   static void singleton_destructor(void *p, ThreadSafeGlobalMap &map)
   {  (void)p;
      fini_atomic_func f(map);
      intermodule_singleton_helpers::thread_safe_global_map_dependant
                  <ThreadSafeGlobalMap>::atomic_func(map, f);
   }
};

template <typename C, bool L, bool P, class ThreadSafeGlobalMap>
volatile int intermodule_singleton_impl<C, L, P, ThreadSafeGlobalMap>::lifetime_type_lazy::m_dummy = 0;

//These will be zero-initialized by the loader
template <typename C, bool L, bool P, class ThreadSafeGlobalMap>
void *intermodule_singleton_impl<C, L, P, ThreadSafeGlobalMap>::this_module_singleton_ptr = 0;

template <typename C, bool L, bool P, class ThreadSafeGlobalMap>
volatile boost::uint32_t intermodule_singleton_impl<C, L, P, ThreadSafeGlobalMap>::this_module_singleton_initialized = 0;

template <typename C, bool L, bool P, class ThreadSafeGlobalMap>
typename intermodule_singleton_impl<C, L, P, ThreadSafeGlobalMap>::lifetime_type
   intermodule_singleton_impl<C, L, P, ThreadSafeGlobalMap>::lifetime;

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_INTERMODULE_SINGLETON_COMMON_HPP

/* intermodule_singleton_common.hpp
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
*/