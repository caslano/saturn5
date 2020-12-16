//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_CONDITION_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/windows/semaphore.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>
#include <boost/interprocess/sync/detail/condition_algorithm_8a.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_condition
{
   windows_condition(const windows_condition &);
   windows_condition &operator=(const windows_condition &);

   public:
   windows_condition()
      : m_condition_data()
   {}

   ~windows_condition()
   {
      //Notify all waiting threads
      //to allow POSIX semantics on condition destruction
      this->notify_all();
   }

   void notify_one()
   {  m_condition_data.notify_one();   }

   void notify_all()
   {  m_condition_data.notify_all();   }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_condition_data.timed_wait(lock, abs_time);   }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_condition_data.timed_wait(lock, abs_time, pred);   }

   template <typename L>
   void wait(L& lock)
   {  m_condition_data.wait(lock);   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_condition_data.wait(lock, pred);   }

   private:

   struct condition_data
   {
      typedef boost::int32_t     integer_type;
      typedef windows_semaphore  semaphore_type;
      typedef windows_mutex      mutex_type;

      condition_data()
         : m_nwaiters_blocked(0)
         , m_nwaiters_gone(0)
         , m_nwaiters_to_unblock(0)
         , m_sem_block_queue(0)
         , m_sem_block_lock(1)
         , m_mtx_unblock_lock()
      {}

      integer_type    &get_nwaiters_blocked()
      {  return m_nwaiters_blocked;  }

      integer_type    &get_nwaiters_gone()
      {  return m_nwaiters_gone;  }

      integer_type    &get_nwaiters_to_unblock()
      {  return m_nwaiters_to_unblock;  }

      semaphore_type  &get_sem_block_queue()
      {  return m_sem_block_queue;  }

      semaphore_type  &get_sem_block_lock()
      {  return m_sem_block_lock;  }

      mutex_type      &get_mtx_unblock_lock()
      {  return m_mtx_unblock_lock;  }

      boost::int32_t    m_nwaiters_blocked;
      boost::int32_t    m_nwaiters_gone;
      boost::int32_t    m_nwaiters_to_unblock;
      windows_semaphore m_sem_block_queue;
      windows_semaphore m_sem_block_lock;
      windows_mutex     m_mtx_unblock_lock;
   };

   ipcdetail::condition_8a_wrapper<condition_data> m_condition_data;
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_CONDITION_HPP

/* condition.hpp
bez/JK5XZT7aWNaNNkIGzzaqfjozCKpYmd82h9FPx+gc//Uz66b78tMxWpP30zFak/fTMVqT99NReaEHbGYzbD+dsJwvMPrTT2cZhOnog7kzF+fS+ilxgRPGqP5L/W62jsbd7ev2I/sE7apcTD8yuhtPmLDr9ltPnDDGDnHsP8ZxZ/zbv96nR+/b4e3To/cB8u+7M2pf8/itSwbNf22FvJWPPvGya8fNHRL67/vu6H2z/n0+PT3pu0NjlnG7EHx74G8rbmKrRzxbxjUlH+7rvePZbqTwlbO8fgnKi8Spd7TC1xKHb2ubD/eW3vKVKXytLvn05bWTrzABn7GYfHHbi0S+ggTllbn43OWVW3M3rkeu+J123M8S0H70IyhgXM/BoCNAixjHcxj3WT/nSpk7YSsx9cNuYuNjLjgJ37qQvPwD3sc54+RU+AnE+gXAJwDf4eLGzIQ/QRA3M4ib6e+7+L81bmbjycnHztzsnsTxM+PFzizGeBuNVI00F2kB0iKkV5C+Q8o6JdUoRRqHVIs095Tge3SwBVuwBVuwBVuwBVuwBVuwdW8LIdX95d//I01TsXCquAD0kA9AbaH1jb584tY7jpnc+QlffACGDsB7VNd5fsbnd/w6Ja7ffM13/DK8eKm8i98l7ULkU21f81tHvuc3EeTz9Z02BouNcl3f8N/n9/R6ftOIIG0F+Zrd8iFUF8qy5IPSiYfPAT1V+KcB95OB710jdLKjTPtbw2QNJvhyOb+SkQUJV8O3hgt7db5fn51rxsPpm54e7l2QXpCan7lj5lrpKeE+ZrnR9WEj4GmGFg4AdZbfj+UvlfJLTNkk9o4dKwecmlg5IW3MN+qR7Vd12cbH6Arqcm/qMutunS5LHbq049oNFf6VdTpEWVodWm3S6IPt0tuHvl1yTMpDHTiGOhyx3ZbyA8uWLGgLpCoouUXf1opIVX0VcGjybWyfAZ3xFPaXCHl2u8+SvDm6dqNcV/yo/dW8V8n5bO23M+S14zCEWDc+z2q/nznqquiUtUqtazHO46z2exrzKn2L+Yl5c0Hny/kNJW+ekjdP8iYXezD6Dc3UY76tR2espv3tWE1cl5rtVr+joX0SqzB6LM+yA8jtsO+N0vU+He3uPsfHusTzUtSv44ZC7zigC9Ldfh1jMKY63HXiS17Svj47OOPmzeD360uRehGnN9Ycu/e46mmIrvW7bVGnv08B42vkC+8Fstbvvkja8QseZfyKHWPAMX4Prhty/mDg9VJ0tsz8tn0Z0s/2HLqWnD/G2NlI7YwpBv1d0RuRQCRWC9ZqDqs6Ykwx8i0DX2OuxBQ7xbq+OHg+j/KEdzAsHkeMkHqZexLHAMpB7LGL7onGHptdbyjXKug2Ji6MzEOiK5Nn4+xtJR/iF4BPnZfm9eV3LiSRDWlH8LTr+tGelxzj1dbnJ5Jvb2OAvj9RrnM91iq5E9H0HXidsRQjjQdHarRzkMqbGrJ8A7RzjspbLLy4hZpmx6tKv9c8v4l2zkFeNUYN89q+MwMV/oEKf7SvmyTmk7uvM+JeO6Fj17qyojfHuuyiH8c3f9s3IM+KDSXtlbluoJ2X7Yi1j1GZ7pik4837sXtjY9fytrJi6szGBix464ojaxZWLXkydHaB8pKbyzVxSe17M8aEO4Hf9uYh7QJZm1E2fapG77YVzZn+NDsXiQ1a9zyfCu8AnYwoRxuT0YpFdKycP8aoxO/hSIxryHwFVlk85hWXUWvfat1oODZoW4m3+LycXxvn01zxFgvw1+Nyfj2JbLWuGZMqs3PN/gPBFw71ylwtc/3MYZmjMldBoLXszNHY3yBzGG4aQxnpoXAozZq7DlLvFzG/IMqSNfbvkTo=
*/