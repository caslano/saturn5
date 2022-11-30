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
#include <typeinfo>
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
            BOOST_TRY{
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
            BOOST_CATCH(...){
               //Mark singleton failed to initialize
               atomic_write32(&this_module_singleton_initialized, Broken);
               BOOST_RETHROW
            } BOOST_CATCH_END
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
            BOOST_TRY{
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
            BOOST_CATCH(...){
               //
               BOOST_RETHROW
            } BOOST_CATCH_END
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
            BOOST_TRY{
               ref_count_ptr val(p, 0u);
               rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
                           <ThreadSafeGlobalMap>::insert(m_map, typeid(C).name(), val);
            }
            BOOST_CATCH(...){
               intermodule_singleton_helpers::thread_safe_global_map_dependant
                           <ThreadSafeGlobalMap>::erase(m_map, typeid(C).name());
               delete p;
               BOOST_RETHROW
            } BOOST_CATCH_END
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