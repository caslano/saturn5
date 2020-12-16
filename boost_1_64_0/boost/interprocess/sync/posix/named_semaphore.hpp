//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_POSIX_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/sync/posix/semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

namespace ipcdetail {

class posix_named_semaphore
{
   posix_named_semaphore();
   posix_named_semaphore(const posix_named_semaphore&);
   posix_named_semaphore &operator= (const posix_named_semaphore &);

   public:
   posix_named_semaphore
      (create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions())
   {  semaphore_open(mp_sem, DoCreate, name, initialCount, perm);   }

   posix_named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions())
   {  semaphore_open(mp_sem, DoOpenOrCreate, name, initialCount, perm);   }

   posix_named_semaphore(open_only_t, const char *name)
   {  semaphore_open(mp_sem, DoOpen, name);   }

   ~posix_named_semaphore()
   {
      if(mp_sem != BOOST_INTERPROCESS_POSIX_SEM_FAILED)
         semaphore_close(mp_sem);
   }

   void post()
   {  semaphore_post(mp_sem); }

   void wait()
   {  semaphore_wait(mp_sem); }

   bool try_wait()
   {  return semaphore_try_wait(mp_sem); }

   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(mp_sem, abs_time); }

   static bool remove(const char *name)
   {  return semaphore_unlink(name);   }

   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  mp_sem = BOOST_INTERPROCESS_POSIX_SEM_FAILED; }

   sem_t      *mp_sem;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_NAMED_CONDITION_HPP

/* named_semaphore.hpp
vBtJ9/O1oXDNc7bsX6nWGLYiv2Whnt/Qwui79LH1XZJY5lALowwYSG2TkgBtkyYs36ml8e3fZv32FWMYPOdC4Qo1vn/yY3RL4/svVe99ZrkFkPuV5jLG+8xlXCT77CT3nOnfaIVfI3hPMV1UJv0W1Jlx8huS89aGeYx3jpPz92bO33GaHFe/PAl+RtnyNzYqF43NLyvM8+RTvUjp1j+J9TtY0i2e3Eapz+GO8h1rPxZb81i7USbgWcYeaorDJRyHMj6/sT+3ry8VYcA3ml1NHEoLvUsf8/DJGnFZXZ/iMiFflBv83fYiP9prqAVU8eFn6LKNSXoY5Jm07aO83084zRiqvlHpR5KpJyZ/0qTJ1xqdgfySgkJln43d0TezJQN5JBPfTIyocxrIb8Y6fsl56Vgt+usiTRKMNLHmI45nE+onsb4ZRbit52xWtmadlw7hDn9gDN7TEu978g7STC4pw7OmUl4059A9WHZa4p0n4XLkBXKzR2+ANsmTWOPyKq4PcdnfEfsvx/foHWOdq9kPWEH3j+qGXoZnyFylN8WX1VN7WqGjRPoZa74ze3/2KMnM04ux0/Uf2mScHdVa8R6lX7Id7AnQ5vcEaPMXmP3DL8mvR3SchK1P0bPMtnwLN+l90Ieg3ToKp2ZEczt8F8k/p0u/PGb9stPrF/xJ0BbqsZbwFVA4ZD9H2nO4qc4V5e4MfJsVWUY7ZwA11Wb3d4dEoPRU9iPZzYYso73hsbdtWGYPy6At9nQgGXdrox1Wfm+gb2K3ZS61f5DtlETrXKrMn/yNsD3ns0TrNyLziV8bxqNow9D79mv/FCjaNZTu9K2142+trK034Ndxu2Umrq1CB3q0/NYKZ3jyS8ZqljEfYS31nfUj2eGqb4r90W3rsoy2RQe670GbxqEu86IDjyFFc/7rSTL9lN+M9fn76JseVzRpknq8imWrW5Pqo0cJaWEbzxZxTOA4qtd9yfEhEZ4EDo91PdGJjt6HvQj/45mxKP+28DuxVbIoScsKS0vyJ/nXtbJ+aVRPuL3G9Que87ODdNAgDoafs/TF2ktmWkh7XVnfJYoymu6P1qdra3juht0gtM867jH9Yntl3RfL+n8yKWyTnHu1dFPnTXOyy9IxFoA54z+b7/otso8z+5unyOyNj9t81gz9Jm29zAfWMMh1l4WCqZyH99L9Mle8Dl15ehjOJ2qP8chW2iznbnMN1Ul61nz065vr5+jd9CmO301dPAfI/b0uI44af9PGmMA3dP8x106EPUt3aa2cLmtb2zxz/iF6xp+coTjJp6V+SstyDNVucdyhne2caab90BghcwirpVaa6ZAaK/51mukwgPzJca3XOvi0v2N5jHcxuZqOWnEE/GB/yY82utGm+YWe01Y/V9vP+pGMNLjEEYOTjtrqR8hepk0Hhzdtjhl5gu3jHNAxp0eaOqVmaEkc31J65ma8oxAtGbPql+NeKofnCnJ7yvE09EWdQmw/0JtrLzlCtM2O5rZ4Bwifmc+vIvsWrpe0LtY+R4FmaY+GkY+htvtGepTQs37HWVH1tSbKPHEMKdBOo3wh/fBYn5EfJ+TDzbxvuBdralXjWDfSM0MC+vcwhTnWTI9v6d96GtVrKNt3nWe09ZrZ2npJLBOTgz6DkHHOQD9HjM4o+iss2wmyx2kMoPyE2xluyp2Q80UkNyqH+2X1yg/498uasMySHA6bazbGZiLcrvIPANWYhnz+ag4rztfGuIrbL5zS7/05Rp9vTgp1+tLQ6Qt4BjinQ3tjTHpOtvTXVyanvdHfnHttoHhNaG88e+4cevbsBnh49c9eZDw7bu7zgZ69sj33FWPmPmLrJ7LMNsOfsLn3BPLnKGQ=
*/