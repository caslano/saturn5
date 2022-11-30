//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONDITION_HPP
#define BOOST_INTERPROCESS_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/sync/cv_status.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/limits.hpp>
#include <boost/assert.hpp>

#if   !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)
   #include <boost/interprocess/sync/posix/condition.hpp>
   #define BOOST_INTERPROCESS_CONDITION_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/condition.hpp>
   #define BOOST_INTERPROCESS_CONDITION_USE_WINAPI
#else
   //spin_condition is used
   #include <boost/interprocess/sync/spin/condition.hpp>
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes process-shared variables interprocess_condition class

namespace boost {
namespace interprocess {

class named_condition;

//!This class is a condition variable that can be placed in shared memory or
//!memory mapped files.
//!Destroys the object of type std::condition_variable_any
//!
//!Unlike std::condition_variable in C++11, it is NOT safe to invoke the destructor if all
//!threads have been only notified. It is required that they have exited their respective wait
//!functions.
class interprocess_condition
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_condition(const interprocess_condition &);
   interprocess_condition &operator=(const interprocess_condition &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs a interprocess_condition. On error throws interprocess_exception.
   interprocess_condition()
   {}

   //!Destroys *this
   //!liberating system resources.
   ~interprocess_condition()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one()
   {  m_condition.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_condition.notify_all();  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock);
   }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock, pred);
   }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L, class TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time);
   }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, class TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time, pred);
   }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface.
   template <typename L, class TimePoint>
   cv_status wait_until(L& lock, const TimePoint &abs_time)
   {  return this->timed_wait(lock, abs_time) ? cv_status::no_timeout : cv_status::timeout; }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface.
   template <typename L, class TimePoint, typename Pr>
   bool wait_until(L& lock, const TimePoint &abs_time, Pr pred)
   {  return this->timed_wait(lock, abs_time, pred); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface and uses relative timeouts.
   template <typename L, class Duration>
   cv_status wait_for(L& lock, const Duration &dur)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur)); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface and uses relative timeouts
   template <typename L, class Duration, typename Pr>
   bool wait_for(L& lock, const Duration &dur, Pr pred)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur), pred); }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   private:
   #if defined(BOOST_INTERPROCESS_CONDITION_USE_POSIX)
      ipcdetail::posix_condition m_condition;
   #elif defined(BOOST_INTERPROCESS_CONDITION_USE_WINAPI)
      ipcdetail::winapi_condition m_condition;
   #else
      ipcdetail::spin_condition m_condition;
   #endif

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_CONDITION_HPP

/* interprocess_condition.hpp
MvLmVQFoNKVC+9oJwI1eI8O0NzR5tkolqaZVjDNIInCXxiFdqCMzYJKRwmaA14fGh5HoyW5BGuwrOAj7ypV3yO7lLiQbuhuxP14ovlg0wvyXmnNiw87yICG+aQ4HVAvf0SYd3p9rBcUjO8pxNOGk16StvRvhEakU/aa9nV+YlKIwqV7I/yxiFOSv36In0I1H+Z0y2xmli5gTicwYpg880gJcQ0sMTv1O94SPuXn9j+iLGQ3OsIgXqmmRmCLrej9b2L+rTwsdyruGU/XuGHOSZrjYIr8nAS+QObQ1yueYJ4sfX4RstM4slMXwpBPk6fS/DH+uNt7JSBvA4D/H3C2IjxXYOHGHBtP4OWz3MAOIBBixoYaxa8FOXzMevPqjlfXjRJm5FqlQzvzfjE+bNW+6AnusGQiX04N/iEVXEGcemFWZrYA8RFu5apkE1UVyHoIav0PxnRJtfCSlINdYTYgscaCeFXAOJYFJS2U/zhbzoZqnu7DhpTHT06z9KpdjtoRDEA42jqR13VcXB0nXw8iDprLGCHNUBErrFRZShMTdkd2A2ZspIzzO3fHYjU2xZo+IMql4h3rId/vLdnKjJKiPrNBgt5m/H0o+N3G5b0s1+PdM4Fq9qAV+6iGbejRUHTfE6z3TFIFkYojjpdue8jXb4SlhznJ3tGy3j1W1cUjlH9kdbMFs81Dqj9/SYpVd3CFjihelqTNKW0ltijP7P04xjyIeTgF7lKXSQyA6SKDhP+JTdwA8/zrv/sOZ4gg356PviMvznobXymYy1GcRrUVo1xC0pUxMsP7nwDKh82fTZlI4OzRl+/rxuXEWJmfz+UG+mTNnhoXBEVg0fh/FVDpU5mINq2I4nlTSvcQvbrDeTvjPFNRRGGQxriAUrB5vyd2Hlnp5mkfn9ebAQwBwFkrZpYZ9vtPb79xSxlFAYufkkogkS0jE7pPjALik/Vyc7L8kSgs0drCyT1mJpCGyILU0T6v0iYalxvsGNppd3HEiTy0QTfxGP4Aq2PqWWIKd4IFWVVlJUIerEnybHfNeHfWtIbpk4DqMvO6WdnE1UdssyWgnPfaeiv2WLVG/FQ6tGpIAAyz8016Q9qoYwDHsYC1dQ4yI351VW3ceYxuXKlSW7Sv9ZvZVDiuJEDJt86eJdxs7nvGsCJaozKfsJ852jMsJ7TVGB2+4yW7UqHzgIjIvg0THJ0Go7mUa4W1D7eqUNIj/r2JMUvzMrBZ6CKVdVmpO9FvT0+ZRUyVNrDBGpLW3cnaEn3li3PMxWWZgHoUzO+laraWh+njMLfVqmdB6Sg7yznS8XsOz7UL1DOMx+DRluVg1v8+fFrK//r1JoonNagJ+HHFeY8ZbXN8Ls6HN8LF1pT9dTYiX+Gy2aMGSitb1jwbF8ablmh61OK58W+nkxaA6AdXcUc6Nlg5yeGwcC7b4pNeLBHZT0yO6nH24lB61Qhl4Mm3uBNz/uCW1P0ITLVKGDVRP5U29LmlYEYaoC4bqC1D8f05Ni0bMLiQB+9afLsPHDqx7aNWGm2kw6+L6+s8SRqbQSAse1W5aggwHlkLXfF7BNvPcZDvAsXK8+fQRoYiUy5j2tIuarbZWC1YcsupQbsbgzQWzukLcQlu4f0zdAau6595tQ3DcXnVQES0+6Ve1GcbefAQ6mejIuUO9KzwfoqaNb1L8xzRG4LTx4timncisGIbbWyQ6Zsh37VNKJZAb4gzch/Sqi7OhL+KsclweOjyuF4Grh0bI5HQjCM6n+TVURnRfaCycxGIA84zY4NRqztrPPNVlQTU5zVfWm7ZccIv+CLda349TshkHIGBBVq8PtmNW8/dsya+sAENzuOEm4JQH6LRu6yBRKkwCTP7BPBcbXy8c+xSKJbxPtrA6r6HimmMRJZIZuL0cpZLiedLqO1z88LcczMfzsURI5FfZcyPIu9Y9k0C1WWUL7g1jjSHlUWU2UGz95hQyemFxnXsN26Vhk6QmzafVwOBzuj8TCdXc1LnfA+/y0h40CQMCwnBkomogO22bhKWVEKFf6aRX9+tJlcNvHwhAa779QwxZf9JBuxGZgMFhnL3vEGELoz8uqWQSaVe/ALOcdu135Q7ZvupF5aENVCxMeyea+kaXUQFkuiWbKNkpttm/tGYaLuSPyW81XXdtiG1S/Ok/HNhGctxWgYCWHPPl6iu690cic3Yhpqc23aHq/d0vkaNHA3QdHjztybSw8DJDLwj5cefxXMM9LZkjJFv6j6z4YsOLCEidB676Be0SkHvE1PIt5Sb30RkXA8JaJe9je+2ZCj6f6TdzpfOYvmVNu/6/ymtz0eeDrPTGQMDI2Qj6VVXGU5eqrK56OyWYMkww3VW6AkhZFwby4Ti/SMvnZ5LigKIXC+g7XT0rTESv8k5BOoe4pD/j0LcKitiK04VnsAiQh89VHeN8pdfrMLD8WDzbgpFnhtDQ7vjJcsvyNrUvVQHY6EDZdOG91QZU3Lfd/vgqPwksdR0EnFvWbB3zGq0fTpyEuGCxeD3xA6+q6HTdmzpHS+PVknfAF5yudyMdGsGKcTk1ZYrC0/Jyqzrgmy0A3g36AZTgQr1GtQIoHodNOKfJfw/DkudjzqSrOmXPsOXneg0Mp6isqOu6+GY05IFDw5w3HkeMY1r12EPFVKoUkUGIt1RYHJDJezjAmNIghtBgketi7sYn+Ad3F9zBHB+gsTn2/JWhtI91zbjPNNxF/C8aX6kneFo8SCrv9YS/EputmFFBntwhgeGGa6nlemAyrzb1ATHNIMFzTssHmCWphygH2+Rob5SYYR3Xy7h3gzCzei4Quaz5sD0av0mmAVhjkRYKSc7mFVjgSMwjepYsG1bfyvexmdkZjGVYaEAEPPP6cW0ZdSc5XqWSSx+azpoZejep6T/EiutF/V5C7+CxtTFOVtoTl9hqax6Q35rCwNc4+gFrUWPguwfJR+NXBxBcKICfK8zZ0OzPvKGRDnbZTyq4FQUp6G7Io7C3DhsjysXIYfKwV21E4KoYan1ec68dX/AvT9IFzRrgNIYTwEmJ8rQ9lHY5kciNy7T1ktsag6o1IjFLu3dwRkkZJDoV85E2Qvtaux5fnEUCw/zJRe8+bizKutgOTsfsKl2fV3KO6vQIlqNDOuZrHyRDRpBD3LRwWuLq5p4YL7CStJFG9jCfDC1/bPP88/Qxe9UnvNVcYBIitpCEDtOlGTAyzokjyHwOHaOZN3jhsjKpoKQQLCGqTx+rPkXyi6G1EHNc36dJ+dyItcyVRqKNSyPurSiJw8WkvAiIEuhy15q5wnY6gF+Uzo34BxLMd4nIHTMlX6gH94HBPDcSU5oeVaPRX2NY2AuptGvWffkFXEbiAB0srWH7EuxMd4bvsfdyyoYWFWFQ54kdbGu4NSA3VN7ZzxiOde1QIvizTF9s2Fwajp8QdCUiLeLG/4183xJ05eeGMFaN7dgN/K33Uy+IM0Toa/NGLu30hMa6QxTswIuJF4eFWApXQig7q35Gcoy/rb6S8xAX16buYONt8UGfdjmbO6ZrfNpTW1gdk02/j5fXpOWoG7kzZB0Y6gOF8V66Umrf6QSuh+RHzLVMemOGy2RmSqN7sOBY/I5MOrDebEMd4LGpFew3EkCEvGm02jYnkrtw+/BFoIMwfKiaA/o3q9msdUuDG5l4PTC5kMpyWaGCUG2sLQl+mlHn6yy2UbiuCq5udG4RlNbFEaSaKg21rRJYGykNH+Qybrxm2Wly5R3cPzyMTJ3t7fGN9yJOf45EEaKoQyxaCNlGuHpJt9r6eqhafS7WBFe3TjlbaO8jWVM9nKkldBeGCly7cz8kRIJrx7nxCEyBf1SINp0j05QF18qtHQ1HO7heTV4Hp/YPzqCaCo2/yUYlY3SWBVIh88ctTNafJ4Zg3uauOVCATdo6+jnND+iRSTPMvbgZYpjkA+gsojIj0NdwNUv/8dvlC+bFS0JuGmusP9vLTa0XmohjkD5t/DBB+OImzn3h6Alrf6Keqw3ljWoeKiGSILQ2cGlxaT19D30RVvdda6OB++hBJE77tRBwaKOujOLp7KxczFk/SuHjSj/T01+0145OUbpJaTmTLgjW3PH7U35Ja3hwYd7CJU932ol2JnFecN+rU52V9ZpLGkfna5x0lRQ25z7ZJ9On/KZFBPiPi+Ghg8kQVW+r7lk6xMsob+zTuwKX81rUhv1cKYJwpJbsgmj3Usbul2QZ27+HmtDV9yX09jH5VlH0MgxA/K5TWTL+q7Rje5iWBMCqzBd7a0fQmTaWjuZ8aUhJ+yo7Gqi/DoOQeX7vi4b17CG0SJHRiV2FloX8GjxUXH8pQpwYxjZsYVAD68ufLo5AEvURNTStrQhjJJ/XMG3LIccTQTQKkUO/+KtajdHwFIL5jzx/Ouv6JLP4dWw5RA9ba3vIr7tXLRJH6K/FPR4+oz/XbTiEcQncf2CXTIf1mRYppeOxO2DVy5UKt4EweHiiGW3VpztqDlvUoYfoxf5aracLlDZLgkwjsenFjYsvQozk+0duEzAIg0PjA7JnTvI0ZC520zr0ONeiRm74vH0hrZAEU+kpd9Kk/uxAuyJh9t38dbgkk/PHoyjaNEZ7aQkdlSmasPw8zJraqphLFuSjjVLV6cOcs+98tOfvYj7JDkrDCJxzWsxjMyx62UaMHLuajndPB7lGxIBDdacdyXk1qiQic2LzBHyWClvA+U5tjyQS8oq/nxQTIMt9uffSnK+C7si6L6gqKImrrkNtKyJlMBE4h7piZa1kUcbHbbsJivgK1YKPyxpvfQSrhrU1T5ReLVFtgRBO3NYtTFFunvpGaip/OiQcqFpKwajpFYhgRnIXn4DaSY9rP9cSsG2YUD41fRGV80nzdkwgLvxMhHggnclbYTlxkfrX6Fmz7Pmk8j4awbrwV2No4AlIPvcO7Zv0aaHg6pLPpdGo1x/icXgBwTRD55b8pbYS2cDDeqZA5Q58j3+MO9dWovKPPIIc78ETwDu22dxNKpF/rtNto0ENGL5lTuabkUKyN8uy5XWDm5GItHYa3IlKTWXOnZbrQPHnj/usc/P824BYYbSI0upbh3yjobngqpKGF27A2vaEJg2Tg9kbzQocZ00/F9mInw2mrcJDRJ77YJrjtzFIzbiLtmMgjLehmDTYtg4McILd4MYYXvQX+G25dR+faVIh0djIIcdEPntK7NCnwTILmaC4HFkkYljwaqhCbBzRDVjDdBWjdRfx7rwhW9wwGirBRN4A2Xz5AFQvKst4+4jiVpbpTJtkFwpXLiis6evZx2QxXGqMLmctyBZYUydBz05BUpkw5OsHJilN5xx7M2CJ4+xG063gkbX+ki5V8dxNS6ACedPJcHSGyVoLCOZLVOmucWqxpxTSvxA1D7uS3MJH0nW3BM407MytnyYcs0cxb7Rxg8lzVe/GvSsLRUB6sbJDM99o8qKX0gJpbLRAL0dQ0Vmth4+c0lM9zgtt8/1oIyTfOSfkYNGLR9USibcS5QOMCrHykMaXhswGFBlcTnVFOuZL0Tz1IillMm57SLDitActQOsbkWV278ug7iWmkNgoHwJOQovEwj7ez4ouXCiLMT43DAjgFg3lIRzXMTQzTLloT8O9qcuHBQH+cjnL7G/rgJQ3h1Ro3NXJocMdoQLiNdty1VuU7wb6aoxrcSm7jMY4L2Ert62LicyaPYYa1ZlFcXqb5lWlDfow49Wh+gYUstX2w76QdojKGveO8+ZWCZkXQk+DrJXtZaICz5CEoHEIyyK6u6uwmkBW2kp/V6RrrNkAHkeJSJ65ErSJOtomDHuKDcKR24W/zmp0nva1kGYZ4N30gW/+Q1/yvt9FaSslzSdK8u5zhTrCX65JZrzD8Tjd7V3quPVdFsaT7SEh46cXRUb1+a748aC3/LN7bcmY+nL1XRBzIfG4b4vIk6BAkdAnBpRh3uGqrqOlztv5yKDAhmG7kngqV/w6MonO5vyhxkwLgcDeD/KCmulCMH/t0uw01Avgzp/28iMkWOMoiELSYIWtKNyGBUz++XI50pBWVdWBuyd70LtyuNePpEFfv2sQ/jWDJQ9jxfXFDNfAv+Mn/NGkqUlIrCW5PQxZYwDJCi8BjS9htpmGIvVbNunFX8XhsRQ7V504Cp3evS2IRyBJnMPc7INbLeTcbV/e2qaYQONh3GOVmmqDkNlbY2yTY2yyQd7ntSLH+CGrcnFZcsJxtDl8eNvcklEc382ZGQgsyChc3+2XWdtUXSuqjgfCmYbJ+NAIFoKU7EQch7GhAsZnv3OnBLB/QNX9MujNLCMR4lAfnqW8Eo2CzbPw06tkrVs6KyxezstUipuoadYtM+fZcMszbdwGTwuNDfwpqGWZQwlOL3xVPqR7CzTiYomth77YW/RxQDjZNdwFdNtob5IuP2ZL6s1opZ16zMdP7q06MFMKbXiMuhHT4sf4molqUDa409FiZDZ/1Kq5C/dzCJj3xP0JpOT64IVJ2MkECr0A6615nMyq2jnWWlJWphJdM5NJLIpK1yEp2QKnxM/oQOhTMr76+GhtBsM2cdNX0kfwWIfU6xoER6YyAgz7LIp9o85VrydHGaAzAwOIObtftiFyunG1MtEnHJH0lN2UcJrABomPTHh5IxVtqjnCQOGT0FGTTPINzhSWPLcJGOiP2XszqlY4JgTsBI3Xb3DiIiVM8XSy08RlgkZwJy9wsu78m/0UTCtnRdYj5+zw0zu774wUEAnbCJfJeIuuUdf+voi/zP1JnslBhL4TH2Bz0qaB30UKaaq16+2yuDS6kj5IhzdC0LAkjO03CX+vUEVzximAAef6gyaUR5BSJaQ506GOk8pfBEGk8vwPgo4GY+YH3fZwjk01gYIkmVjXveIeSF4VxjAJ+cunMu4FDzTeZcm5Wea2cad/MqzfvoPSTASZvGVCNY2dadBm2qqzPCxitNoQ48MNjoTZ5Jo3zGRnk4i2Mrk6PbK3g6cTLHwr/ywlFSjP5EyWE8+1dkQl7QC7b4CuJf7cZNEew1h/Dz+MNijBZE2s3NcTG2bbxpV746hL2sAuQMnCZtmROTvMDMbBaw6LUMmmiEIMuIpN94zeiEt43jh86C6tGnflUXnktiF7fCGglymi/N4VuO9noM1LclWEOIxnOWS9JbIBsX7BLFdaRM1k7t+TyDYn6QpJPd2qXjcdnk00BJ/bbcP+9KgZ1lcm5+dKbDaAuDfnBXhwZSpmnuwdwTcLSBw84L5wLvDWM4Nl+cxI+F7uJAaRzrLWxWVv0XpHhGGtOjqmhZ3h+P2w3bmwMWNkUPvy4swPDqZkX9G/vGr4Pqepf/wCXWmpg0hlqFDV6esKmRPJbxReKznD8l7o1hf99Z0Ty3WBSVQgzJmRo6Z5ysxhGGOQ4rWNbpwEKCtMt9NrPiaw2gTcffBOYgstzWiGTy7WT3p43JG0jT9VOBA1FY+BHClHwecQf4leqB9IyWbrDhsWKYlFjUKq4MTsNvlxR/eIKELhQBGbtRmMcMu41W+P/rYvvyMhKmFJOhAOyDlrtGZ7mkA1vHhO9dyrQZ+raTQW756pQviJknqQFU/ckKb5hog0d1HeX63nmP1J9p59BwX3B/AXkgIE8P/xmxgFIALdzfMoZyX+SZBMkZCbB3VphjjzfZtBn705SWobt8wcVfomiQrc
*/