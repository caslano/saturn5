//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_CONDITION_ANY_ALGORITHM_HPP
#define BOOST_INTERPROCESS_DETAIL_CONDITION_ANY_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
// Condition variable 'any' (able to use any type of external mutex)
//
// The code is based on Howard E. Hinnant's ISO C++ N2406 paper.
// Many thanks to Howard for his support and comments.
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// Required interface for ConditionAnyMembers
// class ConditionAnyMembers
// {
//    typedef implementation_defined mutex_type;
//    typedef implementation_defined condvar_type;
//
//    condvar     &get_condvar()
//    mutex_type  &get_mutex()
// };
//
// Must be initialized as following
//
//    get_condvar()  [no threads blocked]
//    get_mutex()    [unlocked]

template<class ConditionAnyMembers>
class condition_any_algorithm
{
   private:
   condition_any_algorithm();
   ~condition_any_algorithm();
   condition_any_algorithm(const condition_any_algorithm &);
   condition_any_algorithm &operator=(const condition_any_algorithm &);

   typedef typename ConditionAnyMembers::mutex_type      mutex_type;
   typedef typename ConditionAnyMembers::condvar_type    condvar_type;

   public:
   template <class Lock>
   static void wait(ConditionAnyMembers& data, Lock& lock)
   {
      //lock internal before unlocking external to avoid race with a notifier
      scoped_lock<mutex_type> internal_lock(data.get_mutex());
      {
         lock_inverter<Lock> inverted_lock(lock);
         scoped_lock<lock_inverter<Lock> >   external_unlock(inverted_lock);
         {  //unlock internal first to avoid deadlock with near simultaneous waits
            scoped_lock<mutex_type>     internal_unlock;
            internal_lock.swap(internal_unlock);
            data.get_condvar().wait(internal_unlock);
         }
      }
   }

   template <class Lock, class TimePoint>
   static bool timed_wait(ConditionAnyMembers &data, Lock& lock, const TimePoint &abs_time)
   {
      //lock internal before unlocking external to avoid race with a notifier
      scoped_lock<mutex_type> internal_lock(data.get_mutex());
      {
         //Unlock external lock and program for relock
         lock_inverter<Lock> inverted_lock(lock);
         scoped_lock<lock_inverter<Lock> >   external_unlock(inverted_lock);
         {  //unlock internal first to avoid deadlock with near simultaneous waits
            scoped_lock<mutex_type> internal_unlock;
            internal_lock.swap(internal_unlock);
            return data.get_condvar().timed_wait(internal_unlock, abs_time);
         }
      }
   }

   static void signal(ConditionAnyMembers& data, bool broadcast)
   {
      scoped_lock<mutex_type> internal_lock(data.get_mutex());
      if(broadcast){
         data.get_condvar().notify_all();
      }
      else{
         data.get_condvar().notify_one();
      }
   }
};


template<class ConditionAnyMembers>
class condition_any_wrapper
{
   //Non-copyable
   condition_any_wrapper(const condition_any_wrapper &);
   condition_any_wrapper &operator=(const condition_any_wrapper &);

   ConditionAnyMembers m_data;
   typedef ipcdetail::condition_any_algorithm<ConditionAnyMembers> algo_type;

   public:

   condition_any_wrapper(){}

   ~condition_any_wrapper(){}

   ConditionAnyMembers & get_members()
   {  return m_data; }

   const ConditionAnyMembers & get_members() const
   {  return m_data; }

   void notify_one()
   {  algo_type::signal(m_data, false);  }

   void notify_all()
   {  algo_type::signal(m_data, true);  }

   template <typename Lock>
   void wait(Lock& lock)
   {
      if (!lock)
         throw lock_exception();
      algo_type::wait(m_data, lock);
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         algo_type::wait(m_data, lock);
   }

   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {
      if (!lock)
         throw lock_exception();
      return algo_type::timed_wait(m_data, lock, abs_time);
   }

   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {
      if (!lock)
            throw lock_exception();
      while (!pred()){
         if (!algo_type::timed_wait(m_data, lock, abs_time))
            return pred();
      }
      return true;
   }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_CONDITION_ANY_ALGORITHM_HPP

/* condition_any_algorithm.hpp
CICEN8Bx0sYq8bKQIUV6b/nsUOY/B4fcPMtxoABRITY4w817Qj1ijLYUxGSBSj+hGNMwiuBrIiUhfxTrlGs1OWfZ5fXN6dBUkZvGLbB/Ycs1o0MfMuKU21G2FoggOWwoFt6bOPZUU+UkJDZTjiCM8NcM5lZhgWqLAfZCKv9FBrNJi3MBi9bH6Zc2NYimU9idwDj3TK5FdDzFWyw6dW79/IzrkLegIvLOO/URiRVSgPTdvct14Hiq23lRNngZXMzhIx+Kx5rRY+TPUU/Ybtqo9jPNu9ShFfh6amlYTyZ2lIPS1Ugfrnmr4x5vpvU8joBy1a5e6SkYVAtlVqm0SJXlQq8NIQDUw/fdNoWwDTxCNj3i2xf9Io6+/yKAz/VUp7eCXxw0fo71uCzKd1sVAZVk07x+yi+cpKS5k/lhYsCJDxuJeRr7U4BmU7lncfXV5+OyVuecz5kCUjZkbPUcy2y1XcvPo6XUjd8DH5Gniy24r22fIe5WnQONg0EmE8y/x3V3/6tBZkLJjkkCGFsLgddl1246tfhREi7YigqlSPkXUN1CWtmqKJY0O+yA0u6CnDBlpW4Of6wql2yTQOYzulgQyqXVHmF/e374omKnxsIFmclr9MnFbBZOoGJymITQ+c7MLttop8hUHdlEnAoXbNxY9kw866hWVZ8Azb3bLu7/wmNADlvfhk0Oo6xazaorrQ3IdKGGlxFgn/MikOi3ovhk1HOnai+EaafvZ9qmmGdMysJrw9J4VklSuzE8KiQzK/sttQRgtK2dl9gFwkD2y0tCL93pEePHN9emuR4M9eNLLfzoBcgocFJ1rGRIkaCCNC1PU5p0dbfI2DILYILKRCgSA4RR+QvKkinP3sSA4xyuP/iZKtyZqkhCUDo1lwfqO7al82SaKCJPZvuMRENjokJ4KQNunZEtXHoJ71qJhT9ycE64k33foDR02g8nLdSygJ+7w4BV2nmoG4QNqnx2eanauG3qwvv13/4NnAOzGABFHFA9FUA07Rjz5ZVD6TRN8PbOa8VFqxXSzyWnpSAxwJxhRGUmbXG9NdCo7kBi9cGjJ0xiwQ3YrKmuJCvFoG107O7t/uEneeY/Utbo0M1nosenApfPMvvXUGPxptN63CBEdkXX/GXOj9yOt0aKycj0mq2PwfAA4L7EcsxPGT+dXgw4ILof+l/WVTClK+HEb/pullB7AB4K6CyX299g/Fvft+9ZFVBIgJhFO8+mElCdqom2gDblh99t7Xt8n8fxvhAQwY+Zuy8caLSE8YdBBslWgKjjzQRI+C/8YsK7MM1fEUDpHdPwNxRC2Zr1qexbncFwNGQanufEGJ5nUXK9ZB5CqRiakHtJJvB4+C+VJHYOpF0KGee1dsJjFsbggLhr0nRKFQx7PORoZValSLV4A84TJqeoD+53ryC/aoXxufXg6M8g2M7ovc2krdm9rPvzchaKId4mTsBjXkwNwF+vLhm2MNuLwunTYFeJSsjoLEnNyzhKLkkZOTWHvCOUkIAwhvfMyNN6P0yxUi/1oXmTGbrWLGy3+LI5nrJKsFkJGcbSk3D0m4wqHwqfs7sIsWOr8fE4fintzwgrTgYMpWaM4lYvVINpJevTiJ6tB1ISWpbBzjGjLfymtrLqt0xrHyQBq4/XMBxOpV/iSbXjI34U55V9vPXfokxdPxiWuNlGsn4o4IhbZUlnHYj4Cr9H18L3JMdTWytzbY3N2nZR6wFPj5Q5NvkDv/10EoHo54BB54aggWjpEkGKAoRi9y0x0nXvDULcyxfH9OIY+zMiWGNMdVMBRXU9FErRc5f1OKkH5C0I1zP9K84wb6tBSY1ldgWHDTCsLjAvmtAkeRzRxaPzWruBxSOZJHh30cewxrHOEXdlLIwMNNkwUssEusEp0uLBQdqQiBmg1eIxPtKQ6CmfW7Kk9kGpU6ojlfa4UvcqeI000nHGAp+wCzxW93QhFSNR/RbtMBTreGWm6AloVr3VjdVZpmLlNdZ6RZ8Nl5vKm58XEfLcljNwbqTGe/Bce41sWWZXXm8UPufBsL3obdFkdYdR1jG7rd5erCWwfJilbf/rfQiauN9R7EQBsKYuvm1b5Z9AmX+3hpqw27KTH87cMSPDjuLoCqoUokGJjKUHbDYgcaKxE+CYBsoxp271xyuCg/7VxOwX3LwIL25QPUsIjvjpnHzZv43sQFE1OtnBD/VXRfprtnmyHVvnlR/yFOrQ+PM6GaPS+LDYpWsj1p2R1a0xeMdArykz7m1At+qVo7pi5nwEZc3oqhRarumxhX0j5mg6gaJ+o+aJWsrDs9TQKUbX64qMCbY523XdUmCmnFEyj9Qui4yYHPdiGcT8kquU6XG7skmh7tpkrNzWAhCou+x3t+3wyReJhBMBXXXtOqQtm4OF9xF1qc75PZJ44cTjshdxNNOSlK3wDZ0FXLDOLOUaKhwXdhsjIg4Ragw3a8UnGujsHuDI0eySJeOej2HmMefaSzgHRPaQ4lLfJiZcM3P8kuyD0NJiTPsJ4M7Qbv5ydwTGb9DQutknOLNXFbStKrqO56bwTAGLWfqbojJ+/60otSYd7dzQw5sYOAj/139r5r1rcFdwP/1sIWwIJgzjzmbLTJyYB83fRG/vt1VhzR/3ji0KYICL2gZHVVRgCHrXT/6Asf4w20gp7ERIFKnPfFIu0K22NMpFf32n2BmAMyVIlN/imoo9TZyBVbx91IPaUNPMzFfK/UvEF7QvZdyh6r+/94+6QmGAUpwEV6eXXwtVFitbCRs6e4ZKx6KvXyYj5MXkboLG7P2Wx9DIgFuthnR72WnZJxGC9LGqm3vuv7jcIgJddnZuTvvaBOuRfNIOPy5z1F721FuUaUthI8WA0u9a4e/I321bcmMy/gsjJTvTb6mMK5aQluShsTDtDAMOp/3INHzgIm4y3oLPp3gB+LZxqwCMpvkKaRjQxVqLJILUpKhXb9XdlTcvxb1DveteRwzX4aGP+ilvJNCFRlHjqtNgvczH9MOsJ/qE9z20poskjxp95a4CswUM1SyDj3pMOpLYoezd2J85zEviQVKWXa72WOPOBK4vvtm6HOei79AuTrWveeGG/LazGA6LEfnekJ+A59D5q2ZYW+P/Oh/OcIo8J7AHDzIzupxSoGCQgs+/N46nSZ8jZNCoOl1iZIRW0nWU0UJLF7oFDH4TEWLEhcCC3xYP4hQJwBnSUA/MNc5zsHk1iPrIsgAZxKf45Pa8H6THuBmu4bcT+ij/rULs6kBnfnLY3qapZV5i7FpclLpCgZDCHPgS9sU8n+l4UmVQApG5TnWwOxa4FvxIvEE5ceIFQY//kJRoLdJYwB1fo7egqpn/R54Vr3vc+hP3FPLUifuPY48UgZATHP/hhXKpJp5DN8ZtJ9cR0BmGqVragmWWG7RJiAiJNR0ZzPpoydL8rPezjeq/PLLgzQo7wttlLwUXh+UPhzB9i6avQekMEgKp1P2tsHzEbKjAU19BOrc56I34wRZziCPDhTEoDSf0hfdOkX84EQjvHzppvSCy9UbuZhiEGbGYOlJa6iRQGdQvnznccB0awVJggF4MwIt2U6AAncqJrTUhTRy4/3mMVh7bnHnVgKV7bSYr77L407CPSGx85DpsI0IbxqkPBYTDwFHpz43QZ7G7I65TasgrlAPpWHVcfBmcy0KGw5mUPX2jnunRzVuQGitGhMZHnKQpVyHesx9WjxBNvWr+lGNN4fMXsz93FnLuaepk1l55hlayRXBdL6CsSApbUkycg0N9DKmc/AtcLy23gexpeHhSg+pOoaDHjA4cFi4CVD/QBkcWRm9hVETcwfME13fTEBOgt/toKytYdxJkXr0XrT9eBPkqGhzk36xiCHEteC9FHDp9IfsO08/czpmU13jXaDbPqmxmQ3fpxrVhnF9iWjg1Q9XRL0KRyn3e53LMF3lvoO6VhHb570l5QAyBW8/N3cK+LO0s+1hjVhyJvseDVjH5korRPX6c7fKf7IBp7FGlu012JMTk0bGVUUlBrNTr5cW/sgGLGDN6Hv4zY9QmVBA/KHS50dj3imzuESxTpHwuN0tQ58SXJDV8lqBXgsGDLQkzqHYiPvtXX1e0wYivf2cAV6noGpob6XuOxi29cnPfvcijDwJT5gzBUxdoTRlj/oESQzAsJliEYLi1dyi5lJQEgy2ZecT7/a9fEJQH6BYDnE5kkb5xbUJkl1bYpvdG0sM+iYS464va410a5MC7/dgOFU1GrEEN2QkPVzwz8QQ4r1pll2nXXrNhxsrhd/hWXLJUvy5yPY9DpQ5d6vJtZ63qoGuFUv2yu08mbYnD1zj5kA6KPiuusXflQ4xCppQWBnRKVtCy96fZNySeTaR2PI7TzKWUJF2Rl5YAkaopBSZiUxyaK0iEFkEqZNhLbUJB0Q/F7WAWe1VVuFA2UkgIVQWaGdqJQWUuhggIEgncGHWEmgpavYCIU32iUBMydOLkzei75C6iE9PptvowrXUlQq7UF871cPS6fQwx6G6wl5WRtnNo1K9I8kEGLqrrW1cPHVqtQdsNvlARER8WXexE7/hdO+PAABa53nVEBSQwYsYOpZvIdAVdsPdSlVyAzCzb08iEwwbnpjEmlQke3hgxmwxXJml8NBGqLPtM5KZlql2YrLUc2k35n8EDM9L9pfGAMATDQD+9ngk6SPC2G/BSfiEh8RcL6f5V2l0QH5BCHg5OrLyuACcAl1FaZMo5MPVKmVCWJtNENOzYdTK5tzBKPsCT5Uq/BJp6cewDoB7hUB0LZpMvYNgzaid1PW0rWtjh20T8WEVZfB40I2JiKiOF39rLbCcCc+sM06vZHFWHAnuHP5I+vRQFOXSVjzXWZCz/FmuFW51xZkI2GZgYD0sF7eeqFI+95I6bazUx9TqsfkNZitXdvB3qm/YPPmovoqcOQlsOteIwrU63s117cGcARFYN/82OvFdpOykrBlY4pkXMglLXl1kGHj1IfcYsXl6DeiQvj35d70NPH0KnYkCbREbJUe7yPUvFhshmr6TJ6BiefQ8KR1f/Vmje9nuxLwdYQtaGI2VVjwdOv9+chXw2Vxt2xaQUx3jBX9Xojuh2UA/y1HW12zU8J0ggcAnIU6LxI3NPJr5NX2Kic1E3BUvbBiGxuJBCIf4TzDRC64d70a9ovA6oF1hNl5WSeQ7yLNHE+I9gx7v62feRq2ro1yRbOLbRSzFj7TE6MQvuaoIDl4te/ud3lHeRei8R0EAppnuL1/qaUpRl7H2AJy5RWKXInnMJ1I4tPwiwIO5OOEh/+kfbmH6npYebKDVHRoE8N1fxyiFvca24O1tOP+mqHKHrbMFNoCr77Qyri3QtzUus7fWXx8LLZVzii3hZ0LQtmSOsYC4+uS5eAy46WF1usNYnxFLvvlHH+DfA/3Ay3HkmUfo2uWtZZmG6TsMhSy/hgEHi685cDluwBN48DfXyXnNOMXfTA+dxRzAsZg/NCwHyZunm5nC4btPfF4Zv2DHw9igja8zln8uD+Y8u2uOVixJPO0Anancl24umEr49mdYTxayU94shdn8WRhwIYGXLMEBmBNgbor9qnOTQ5lfGmR0h3Hp763Cs6jjThrCtfbdk862HV9g4kZFnYwWEiTeXQl0DAy0Q9365uBDp++RzO6H4HAqOkJxkIIA2IsOMMwClAFCb8tAJDkTbWhxLRx5cL8szv2jQg2vooeWPxREFJi2eB9BVTLhxyWuTzTHkmtarIPVkiUKD9wT/byOBvEjg6TJyGrKQYSaItXVpB0UOqaBWZKP4MW5cH7bZ6ViAilOZ2WGGwAuGa0V1WwCt/mvKlyeKcGZzgeu2pLpLAvnZCQzkjB4yXqisQOZ7ezMA1sgGNgNO++0tJZVZnRipPkI3dGURmlN6AbZ8Rc/gUlU6vqpzVDYWw48VSpLrPf1hEyb49gCxuGNH/LRD00bX9ZPe1Ne8IvIspPhnpij9rWIg+/KJl0XOChCMkcSHDMpncPO0ImX1xnnxMJA1jo4c8YMVyYe8LhCuse/6XUc2rUsP6Jm5LV8Bn4Pw6PUldOfI7pZtaW82eeUau+QIikyg62q26jVcZyHRb931qpGlEfPyz75WmWqU+wVEWEzAKQqYgZCh8TyUB2BBVwRG20Rs31iC09I3ai3iXgVYDs7dgWjruG3b+zBkNAdEQGjKpDA9TUwmPm57cq9V7L4/Ul2ywR2mT6qvz5I/rbEAJ9A3AEHArDNCpiPCTpChBwwOgB/mXn3MNHDgI1XaDq7JCMQvfy/C7yl6+u8kfWcfrY9RPi/6oQGVND7p/nNred3jy+8oLZUd7zyB2MPFgPFYHfByy30TCiKtPTSkPcBF/wTPigUxpKu4137nokoOFiL7LlAOiOQ+nLeYIODKkj59VLLwcq02SfLONZbZLT9Tr9q8rS3aFBHof403hv85UYKJ0AXdISI+0/law3aj6Znu3gsntuyYFcb6vwCCV9wGRQpvwHbZfxH8NC/QnlqlsM3Eej/SyJ5AZ9CcIxc/sAqhIiYjZzGxRTrw/mPNaDFDgtbMU7fhQM32UE4W76RCT8H4x1aUrGA0WfTUJGhMJMKFy8Yd0zx+dyBClLdGzmCEpmDLDThnL/CjfjJcal96ClX6MwlFKuDwhCSduZHKx1NX1qMOS2bMBXgWfIahwqVX05NvBuSVDAHgg+BTl/v7Mf+bfgzrJ/9xbKQEIVAgx8bsIrzHYy2ppdSpaaketk8PMWbMbAkdy9VFTJiaZNsmY+Ng7eg4rZ6c8WU3HsBH1BtAEpaP9p0mmJmzFbbs5vJfDQoaioUBIyGjoYYalxa82RQ6FX3CzpRUPr631ATBxWSI3p4dy7/Kq+a2aIi6prZ8tpUHoC+El6M2NPeaZzg+VmVmsvxFu6Lzh7xJbZHUPnNRA1LVY53ThNNm/Ixohet8Afn5JBAQHYuMVotS7BD3Yrt2R7L39utRUxkUcbJhnMz1RMy2GF+BiZlChUZC/qRuvY1Bv+wRlC7haGpuPYcma/yKHUNwLVEMI4dFfahy8p0L40CWNRhekzxW+5PjHT+Oij4C0HfAX8/zPf4vy5Pbf19sY7i/xVhhgP4wGs7eC2qLpuvHlQMIVwmBb+AnTahPpa2ePzanABlPw9Wl1SmbUVHnuxGT9sJYLv131yAcjTdNCiW2E8RHNF6txnBHcrMZ4UpQbUfDePmjefKQu9ljJA4YQW/yHoOC3iRtHMVm/6yL4nOfNkXnW5L4n8SIYhxJ36R1zhqdim6yv0JQ2OwhOXwT2ph7K2+gcr00Mug9IwgyfnQUhD2Q0EEiZb8RMMUVVga8zQ3WEPZ3lDnP8Do1bPyrBbcyqtoUDr1NJeVq/UBa3rt4b9+t+ztffx+15nFzB9X8hXLouiRJGSUcxiERnnoSWBvrc9I0916D7pU1GO/e4YbTuzu2jQfhUmnH9iCN8ECxifl/6M9tGVm4FQWMOQHfizmRJkFN2U52OtU5r+RK9opC+p+sEpsgIUhi23E4b59U8ui9EuSC/erFK0Vi1jzxw6Fw5TbWe2UCf196UfbovnOQ9QNI3VV+QOMnJjMPO7HZwqqxwZ5xRZbcx7ej0+CC/ukESJYEXVmNPdPcHKW8bYtzOv1kgaUIByuRD1J5UjgB4zJU2h9txsMb4/03Ga79
*/