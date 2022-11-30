//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>

#if defined(BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)
   #include <boost/interprocess/sync/posix/named_mutex.hpp>
   #define BOOST_INTERPROCESS_NAMED_MUTEX_USE_POSIX
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_mutex.hpp>
   #define BOOST_INTERPROCESS_NAMED_MUTEX_USE_WINAPI
#else
   #include <boost/interprocess/sync/shm/named_mutex.hpp>
#endif

//!\file
//!Describes a named mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

class named_condition;

//!A mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named_mutex.
class named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   named_mutex();
   named_mutex(const named_mutex &);
   named_mutex &operator=(const named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global mutex with a name.
   //!Throws interprocess_exception on error.
   named_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!named_mutex(open_only_t, ... )
   //!Does not throw
   named_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_mutex(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global mutex with a name.
   //!Throws interprocess_exception on error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!named_mutex(open_only_t, ... )
   //!Does not throw
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_mutex(open_only_t, const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_mutex();

   //!Unlocks a previously locked
   //!mutex.
   void unlock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Locks the mutex, sleeps when the mutex is already locked.
   //!Throws interprocess_exception if a severe error is found
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Tries to lock the mutex, returns false when the mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Tries to lock the the mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(ipcdetail::duration_to_ustime(dur)); }

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   public:
   #if defined(BOOST_INTERPROCESS_NAMED_MUTEX_USE_POSIX)
      typedef ipcdetail::posix_named_mutex      internal_mutex_type;
   #elif defined(BOOST_INTERPROCESS_NAMED_MUTEX_USE_WINAPI)
      typedef ipcdetail::winapi_named_mutex    internal_mutex_type;
   #else
      typedef ipcdetail::shm_named_mutex        internal_mutex_type;
   #endif
   internal_mutex_type &internal_mutex()
   {  return m_mut; }

   internal_mutex_type m_mut;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_mutex::named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_mut(create_only_t(), name, perm)
{}

inline named_mutex::named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_mut(open_or_create_t(), name, perm)
{}

inline named_mutex::named_mutex(open_only_t, const char *name)
   :  m_mut(open_only_t(), name)
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_mutex::named_mutex(create_only_t, const wchar_t *name, const permissions &perm)
   :  m_mut(create_only_t(), name, perm)
{}

inline named_mutex::named_mutex(open_or_create_t, const wchar_t *name, const permissions &perm)
   :  m_mut(open_or_create_t(), name, perm)
{}

inline named_mutex::named_mutex(open_only_t, const wchar_t *name)
   :  m_mut(open_only_t(), name)
{}

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut); }

inline named_mutex::~named_mutex()
{}

inline void named_mutex::lock()
{  m_mut.lock();  }

inline void named_mutex::unlock()
{  m_mut.unlock();  }

inline bool named_mutex::try_lock()
{  return m_mut.try_lock();  }

template<class TimePoint>
inline bool named_mutex::timed_lock(const TimePoint &abs_time)
{  return m_mut.timed_lock(abs_time);  }

inline bool named_mutex::remove(const char *name)
{  return internal_mutex_type::remove(name);   }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool named_mutex::remove(const wchar_t *name)
{  return internal_mutex_type::remove(name);   }

#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_MUTEX_HPP

/* named_mutex.hpp
u0NoiJmBMr9oGj7/w9YE3zcwVOLlLuyKI923aDmnTSEvWFTrArxStiL4mGmyRljsR/HZ6Vxy/HhJ+QqKgBPz0G7T9JT76CpNVSF/hXgEog0zG0SrFe4nCLJMVG9Iy/MBm5UoaT+RwI/Q2Fel9NBpyyB0WdRznmlxAaBX1wTUtnK4odOep+/6erU/OM5y1kj8dWjGjr3fG4FcC9bywI1sOYSmqSVw3et2TNnVDCmEkDwIlJPnsanlfb0E+5YRj7yietIqvYbhoTGyhyU0qNXScm8INE6jak0baLPz4UWB3Y8HEXUDPNhFmDatbRpUgQCKCtHUExnd/pL+vSY7MAPgxU4vwFvufn6bNRWCHsBM3Sgg9HYvYHJtflSalECltBnQnn2Q69bDx49J4H248Qovmxhcq6MAA1xIH2K57Pwnrin/KIJZ1bFiIi0bMEF1WCYZIIzTsNcoFaIw9NnsVj9IPpseerdaIsQNPFiMj66vCEIynp3ZCbab53qf8uq/Knw4Pf9hRJTsZcrHhMT+NAVIREcQyU9ndM+2JWjVQ4QhwMG2Y1Fo5kAAP2lAxVH4F2fzTOtbgIK8xUp/2d9FUf8Ih29WNJpjH5CbATixqYe6CNf9CLwN2u9/33zf3egNOWJi/b0sWzY5o5FF+Rm4Dv5BT1QYSOORrJCEG9iI7RMfMcj4GYc3pHsHPVbhIfL1+4J7jZCajiuaC+uBAaMF1wJEmXIR/8nE1BFDXgFq53UNwzpt8CJoJCozmr6S65BX3SyGyuJmFFIJgSIgVSXxd6yokrX6QhqHT307Ncoa6/boOBicEX7tyh2aQ5IBsglI+8lT1AAiNTLRuU8tZ2mE2v5D6qBZg+sZX6n+lv4EPSAnW67U5cjNhKZAT2wqfEKpEaaTEdTPE/pO8G8yoQGforUB2Z8wdvmAj9TcH41QJDgW22Pxsg2ix5qz/9xCNpzQXcN7cp0mqDKa5aRf6FiXum8jZexurXE0lxG9Yxt7jVb+RhJoWBlL1qvw0sg8A0BV8NFr9JtI81668k7hCGpCB3mde9PW7TbuU7+3Dz+PmR6hPRMJ+zlf+EiKAOujetnygf+FY8jYpVRxkePDBFduKcmNKLUYJZQwYf9oGYR3SOTZeTatpMwFaHpU58NXdYIvz6uQGHVjljrL9VF4Yg3CeKC9zsqdBQqTJq4TnHtl3XyeBjl0FlFqCEX7SGBPB+zAbNoX/N7i+4AmlkUIywjqrKcOJaA9Ibmyoz/o8j6z3IGq8I8ZBD1NgKOfL6Tvlv7ty/lzR+BkQ6Xj0xpAbGhzln644cnP9TATOFl4SvpK0Qo9P+sPomYZEgjY62B9mkNvFWp0u6JJSc1Av2Zx6CVb49uEYo3X6o3rcoiwUGRYUQ2Qisr3op5dffA5DlWdwc3kS1GQaHHVG9z7K8l6Ss84hEneDCfnxRAu3VgTZy1+E7+JuUKpZ9Z6a8N2wUXS5Q+ZJ3coIP6ul9aNQ1PbOTLHJf9xhN5qDna0tTI1WGmXn0/ncbLpwJh0nTafqIGsBtiS7pdPqdJKxZUVszxM1BxTv59ApMFcoagibPam6gONFIroaHJNSTCsd8VWnYNy2jEYRnCGSuqH5vBWD8dh93rRzoExBqesiJ/nqsOhxKHLYWtXdcUThEMGoUHLwRpAFBBwDegLlyqpq0zKe/r9exKx8MNHtlKBYPyOdvYEphZ79MLJkqdZCsaGNinKKZOGUC3eDWyoghsbFTahatkb43lD8RklewZQojfqyK36+0psHof4RPzcyvWMJxYokS9srLupg7WX/46ACfJO5k8N+/MWmPVK5kORSUZkvWJg0OJAO5aO3KUuDU0m7x8Qd/48RChHEltjXsepYEEw+xJpiEfy0jvLFFdxAgzJAYZmGUnFuyltw0XwUn+c07LMOgu8oS+CywmNGfKBgo+cHya6dPqKh2GDwN1TyS3cwn9EtYW63zgG2NkDaWJhs+nrOB9wZLIoR+uW7nQNxWuVUtOA+yhjTiNJVTQuKRm3J6Z+RbI3Th4Sl8cdxHUPtQEgAe0gBcnpvfyTRM7tU4TUqZGfXSwQ43dBgXgCcLTSQMIcfwe4WKLzsWkR8CAUFemfwqo2RWB2x5WZuJX79vLwSakjjAa36P+YeVl+7wuGBRKWa5joRYa6a3Fgnb+wlEUYaEtFr7Mzf9ijCzQcRHgunCJ4kcQALx0nI3th+238G/h2ttw5h562np51klmrJXRGHiyAvoNqvCfjiwwFQwWPAANTszCHQ+0J70Hc2C9q5W8dKVyeYaRorXCGhp1dHgXIczelUQBnu1WToCsZHwVYUddZdkNNxt1La1pHhQxoSTbND5btt5NKfaJrGzCbmTl36aQroE+hOLK4kaG6uIrR8QqAREMwoIpFHkG8kWZvPox+SXhhSqQ6Hsac3Zds8WaaUqXUqQ3lEvRvpywVtPX7OSQZ3ISMViXFZF4Sq95NhaubaHB8lvAtOWuRInrTMut+7Q99ojAQc4te+mboPEt/2yvJnPJT0AXX+07Dutlc+etXttU9OH29g7pTyNnwQEIq79/41TX1PEFRmGwccOKpSbVbaIpiRxlMbyigPzOjFOsWCX9V5HD+4CWk861J0vs3U7G8XWd8h8tTj/ci3zAlp7JsywNWYHqnbXuV/jvWvDK2f8n3COkYhdsypgTgTSdBHz0xppf2IqYLuEv26l6qCuW00G/9KrHjpDSvCPTPCgHL33qmRNhqyQU9qDb1zzZ6VVTCHNNXqdXJJgNt6uZH0SpEl3/ll4PA92R/z3J7Co31e3qABgKknDe/VXgpWk0hGjzgoFq1eh8AwZs74t8376cYczzJRB5Riwq09hE6y5z+pMFaY/dsCgdas5Hz16jR9O+D9g0PkY5TlQ+4ZfJlzwWAQrOXT/cmCltkIaz5IEXcCc2UpIEAGR9swXBZTir4elLDqy2CWGUzTI8K4/+QG7xiOttE6IpfMT3ldJxO6k38KLT/9FNgvh9g3mK0lcIYfVsCoN9w9MoJYI7DcJ3Olo47aHq5+3UrnigBytL8lNZNghHvo/LpQYNzaXqIfaOS0WTYzCtbiDRFGRE9CSpSTyd/sE2DrH7+9d6lsKc1ClhCQLuB4lxzEyBUyQ7yuL/6yijDVerYrJuU7Oi1cvzbKf5znk3coi+4lwl9PRbbLbEkpTKBKVxjzZJ/GInjafM3GGHVWhZnoE+s83anLvuy1X4ShtUsYWOjARZpwbbPASq4HcX7WF+BPX9/itHYTXVmMJfBQ4RF6JBmfQK0GjD6VbdTDWy05zi3Bl+LQ4oZzYc0M660cMlZGEU3ZNqOFymjrgaTMum2QVBHNCj+tZRd2b5UOiQ9P1r8/Fg7Evr42x0LSxv8PVIhAoghnooaD3dIKJVleXLkfUg86j34Oj1qGxD5PlzwA/SUpVKkIQhx3nX9XkHiwTrIMVUR8o5cyrPUhVCkL0J/Jppknb79SUZlWn/ULAxvmKjWO6ofH9wDMMU43dFyNX7L5XEzjTu6Hd6II18JXAzYZ5m8agFk/OIDE+68AhlYoPbLctkEULvFJUcBvqEXn9mWw8BezB9nvq3q8wCUvMtWv8eTQMJfqZRZLONMKKe99KnTI5f/z8lnoJ02ymdnhHMmL5ttzqgnbNE+oQuYJe5grCkunvGLGam3ZYtMu5jqjwkRC1JDm76F1/28E2u7fHF62kX2Km7bjaxS8txhY8fvvpj58bDRjNbo/cMnPlNKvpMdnKMxu6mNZdFpmJAAy77qLkWxvDIzOrT5gKZigmls8W35zw6ANn24zGcNEk0+IOW+lHezAEgXTrT3fZLGaeflYTdBt3O44wqI9sHTfDBmda/otYJZKo/tK6Mn6zKOs0NNO/vHPFKX7Iq2S3yytK8da2nU7t/aKkhl7g83nglHOuMHiAljEZrH9RXRKbo1G7Lz9SuCZNArb9Sz2ub9gwqY1KuZKxWgD/0G8lx17/UlLnzD3YlgdLUvPLTtKM4DEVsto4YDzC/dx9oTDOZMg5342wOEehDOmnIpUcI936j2BTt5WdXhl7IflKSsrA/9U4oSBKIRfkBnszEo4BlRWAQz1D93iDIZ7qN/+OSDYTO0XRzUIBkmWEUHRHK3Z+WSdR2o9+Tk42qEgLEfb0WwXe4vrkMkj3QqB7HHPTNWQbyHOPXwT0RsbkQOGLCizhy6Af4RaSpkTaFtHdb9CZ/rsuVfEuDmHihArJ81OLF9MmJswSP4lvd63Tj7Jw+l9RwrdqNgU0KClKMzQV9v4CUtcebs5QJ6YTcsxM/8THUNAml7QXsJgX9QZgfWA2V8QXhfJz4XKTmveW33A3wzoHCZNi4sk6miZTOKSZmSLtmy9WaRLbxAnAnrPeg9ZGiHc3Sk2K6Wx+6NBiTNZrMnIxoB5uIRwguL2YtK+DfP0YJSeF7meWryudHbTSkmRuDDgeaEWyxzT+ufFFJziCGR7UlsqVITWBfdKZ550Hpgl/7Y4hR0qMp9Yxl2KtzRIxnOaDe05GD3ISvIJJhnM+2J27mRD1dqOx21SizmlMsHOJ01iR8cXfcOqP0hTgc/X7QdsG0yT+x2OmoZC3zkf/c/XvXDBCDy/yvlxAraaoq44Cd7rNPMV4b0PyYXwO4oilP4UfTf7kin61NCf/twnwJ0KMPr0qMrxVkKgPLBB20EPF2xAhJAuU4n6fE4sA7EFr7TfMcVHZdrOHI9s8AuIMairTRTSCIZMxVJtuzP2RynTMKSHvHwRKt6VQ36p/IB6XeEh5BGkpiIDk8d7BJIcaPDx4jVgB5VZ+yKw1C0ux+AY+QSf3e9zfpsdsQ0vqL1d7RFlTZwIWKO4Xj2CiwVM+IoFKbDiJm58db7ssZhRwy6pZjdf0Vptk9AnAWvExAIXDe3H06Gxis03fzrJ6HixoNq4ZkMUr528VWDYmrojBhiCqkBGJrSkzjYeUdv/1W3pQOiLA6FAqIPOExgF+0dJHFpLtqv5M9sblfFbYJjuI2IlV5nvXk13H+Xi3bDDPzWbZgKBULI/UQcY5nOrDAChULMs1hXu9ACpQv5y+2gi9ECw4ud0h5PWtNXQhEZJLG5VAtRakwOdVk+7bEwSqb1c1xmdVxw3uyKfLBVDOlzC67IGiU4vkbcHeUAEOorpmF5vmsaL8voOAACgqRQy8RsVFim9gfUAGASoUOFakZN0y1V5dBMYGdcHjBSU74kP4ckIWiZ+SXhFvNGaYg2O9wo1RrWuqsG+x2fyl1KSzdEMOyCfxGOqfGTWSq2vnT8gqK1MhFkH8po9zC1VRQLDZg+b37b/SuGJEitGcbZpkDOh/nUEqKKDHpAjZrSuzgAdTQ4+0OV3IbbCZpqWRumqDDLLF2Ion4xnIDrXLsVKs4c6LdqEOpOuFLmoLDFEQTgsn8+GMee3dXvwOgnAJfZB9e7AACAYwGzYUSKVXrEJAjj32SnhfyHNmAKhV5HQw7plZ8fn/raKC80xtqrnGienJpiLCIrGPpNmTCTM5SEU+sxR2TJ9LAJayLetB+ChUy3o0uSojoH9bI9KFD6H1cTEv3rvM0u624XCubzIzsD1c4Bm9+2FmbRN8VHGWMI1ZYjROt7xIYCwefUDj2AY2uEue7fupnVNdKn+TAYn4v7JBoYkWX3mZOdjD1aiwBvTg3CMrFhn8+cGICgbtPxXqVJ6OxxdVe0j/bXaFoqbvkPcdtc5Yu5SUW3CkOFw4cjOu2ulgfqsAD0IiPa1334TurJAdq8/EoKWgPLcIA5HDzdrmEW9JsZJCFNGTVFKo8cUte79eVQtZ/FU4WQpQmtnjyOGSezeLXPubOd7ckwPJRM007GvcHob9BMSunQNPCFSW4A/BjIr8Of1gfSBKBGzb2475Ht55efw5JGMrB8eZDEigSL1rwYl78Eau0l1XFYaVLku3qWERkrXHTR/aWxYxshS6ERGmtj5jFHfXAIzF/8Mu337yYyaUy1vvCt3AiSn+ha20csbcluKgL62ZsBsXGDDs6kZ6bmlcr1VvhFheTVxZ9U0Dk3s7xdiHitwyOJhm8nIumkNgc2Sa/V4ACqwcBuYSY2V8OexGI3gcC2i2/4k75ff6whVB7tyOIctyqJwCzfHuca7pvQsCO6J8w+lixQ89g/Qjamp3gmFbrEYycJm6XMhVnUKEAOnvCkIrg1rZEOwcsCLZSrykggSjtSlhCKuy3lZPzWRbYWL7En8KZt8S70Q1iqnAc6Oh2R7Kk+kcDD8Gj14oCiCJoPmtquFyXtxk5hxhK2dWRlUCWGp0dLzzjY+0RobYu1XHSOA0S0YM8n+gy2Jg2byKtU3GU4X9L8ZTO2ah3mIuOZ9U1CGYUBP2wwssy1CpXOfVTPK12O0BwHv8uC1jSp6zqtsKtTZbFoGxPIR6Pxbkq5DS4XhUgVjD93OKRPElVs//Xzhpku3iN5cLYfK4NKFCC6e0/taQ3MLPkSjcOOYcyaDPBoXTxg540yj3GjiI+CoJAJnXZVivtKlZfSDcwpyk29lTjq0DY5vntuONIkBmrfF/hKmpXBlWn8m5or2c9Y1WDdd9DUwC3is/eQvjAiEgTPrnoVKQZEVCs+ruWmVRGOVRdQWnNLWPHinUE+KwNaaWQeEIWACQGqhszgEUoNfPQjp9DrowaQdaKKjHD978XzV37ScABjkjwbtIhtgbjGdNpQ+ySRn7xxp4nBxvgD1OIfKXorbHAlmWdZQdJyGIdSr2ZgBjC8y6lgLSvbfBO9lx965JeugDvjI5zdio9EoxrS2jkQzxQFL92Tox3V7J7FDrmd7gngzVpSFw3XNzMynW7OoL9ETlbfcob2Q3TV3qnA/gqMfgAAQAvWdUWCovcvfWQ+ypd3C4dj3UnitxIL26Yo+Z+c9R35s3csci59DioVulEUNrh1KfyJsEgnFNiKAPz5+bm5oPKtGQtoCDBZ/9af9UaLNaj+OkCQAaqbS4UcpyBKdDXctFIZhZ0jmkt4rE8GnYUYPs2bWj539O9kUIuJ+vAcHiRhISbyEywtkeLtjx5RH5tlEuIcb17azULSAOC66gOM8V1VTAMklULg3TMHZKQTYqHCNqeCGhCs+rljdcWbaM8l8KOA8GWMb8kE9doa/SHdKLv8o6/oXy4/D//lmoePRy8zRITD1/MppOtoddxADr9froP+d3F52CD33BxXXf/+5I8oskrz+Mzfv2dBhDLSpuHrF+GRwjr/uqMK+0oIcpXio+kckEm5pZUk3PDWuQUlh4MS8CUIgw3MgGBIgpj/agYlzEE6NOD7klYp7WdrwATR9yHZ0dgtbwdwkOk7uGped0w6vDKK19kbHnoQqvoUr6RBboMFAOXuT5vNgFy0ZR7Wdeg6uMhrck9vy+Btm9VYO5mADjKDCiUDmwhCwfSp14+x+2Mb+0u7LSyq6Llavi78PJ6eZEd466SpXRyx+zkmihaX+w/CGP8FTbfWBWEKAgDspQE9adEuZZVbGc9tM4LZKXMd4i2lmNPwzaB5+M2Brd8ckPjNAVoyAEvqQZHu9BETSmS3HqQNO/Xr5X04HJxqOsyt5fyHihDJkxeG1KPLVaRd4bQkcWNmgqhP4QAPLPDTqDox3fLawzgFYQp9FFrTHHN/DnRUZzF3fEOfCqQUlaEt7UzPlKripkuC5cEv
*/