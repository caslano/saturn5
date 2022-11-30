 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP

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
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>

#if defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES)
#include <boost/interprocess/sync/posix/named_semaphore.hpp>
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_semaphore.hpp>
   #define BOOST_INTERPROCESS_NAMED_SEMAPHORE_USE_WINAPI
#else
   #include <boost/interprocess/sync/shm/named_semaphore.hpp>
#endif

//!\file
//!Describes a named semaphore class for inter-process synchronization

namespace boost {
namespace interprocess {

//!A semaphore with a global name, so it can be found from different
//!processes. Allows several resource sharing patterns and efficient
//!acknowledgment mechanisms.
class named_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   named_semaphore();
   named_semaphore(const named_semaphore &);
   named_semaphore &operator=(const named_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global semaphore with a name, and an initial count.
   //!If the semaphore can't be created throws interprocess_exception
   named_semaphore(create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens or creates a global semaphore with a name, and an initial count.
   //!If the semaphore is created, this call is equivalent to
   //!named_semaphore(create_only_t, ...)
   //!If the semaphore is already created, this call is equivalent to
   //!named_semaphore(open_only_t, ... )
   //!and initialCount is ignored.
   named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens a global semaphore with a name if that semaphore is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_semaphore(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global semaphore with a name, and an initial count.
   //!If the semaphore can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_semaphore(create_only_t, const wchar_t *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens or creates a global semaphore with a name, and an initial count.
   //!If the semaphore is created, this call is equivalent to
   //!named_semaphore(create_only_t, ...)
   //!If the semaphore is already created, this call is equivalent to
   //!named_semaphore(open_only_t, ... )
   //!and initialCount is ignored.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_semaphore(open_or_create_t, const wchar_t *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens a global semaphore with a name if that semaphore is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_semaphore(open_only_t, const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_semaphore();

   //!Increments the semaphore count. If there are processes/threads blocked waiting
   //!for the semaphore, then one of these processes will return successfully from
   //!its wait function. If there is an error an interprocess_exception exception is thrown.
   void post();

   //!Decrements the semaphore. If the semaphore value is not greater than zero,
   //!then the calling process/thread blocks until it can decrement the counter.
   //!If there is an error an interprocess_exception exception is thrown.
   void wait();

   //!Decrements the semaphore if the semaphore's value is greater than zero
   //!and returns true. If the value is not greater than zero returns false.
   //!If there is an error an interprocess_exception exception is thrown.
   bool try_wait();

   //!Decrements the semaphore if the semaphore's value is greater
   //!than zero and returns true. Otherwise, waits for the semaphore
   //!to the posted or the timeout expires. If the timeout expires, the
   //!function returns false. If the semaphore is posted the function
   //!returns true. If there is an error throws sem_exception
   template<class TimePoint>
   bool timed_wait(const TimePoint &abs_time);

   //!Erases a named semaphore from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named semaphore from the system.
   //!Returns false on error. Never throws.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   #if defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES)
      typedef ipcdetail::posix_named_semaphore   impl_t;
   #elif defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USE_WINAPI)
      typedef ipcdetail::winapi_named_semaphore impl_t;
   #else
      typedef ipcdetail::shm_named_semaphore     impl_t;
   #endif
   impl_t m_sem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_semaphore::named_semaphore
   (create_only_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(create_only, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore
   (open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(open_or_create, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore(open_only_t, const char *name)
   :  m_sem(open_only, name)
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_semaphore::named_semaphore
   (create_only_t, const wchar_t *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(create_only, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore
   (open_or_create_t, const wchar_t *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(open_or_create, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore(open_only_t, const wchar_t *name)
   :  m_sem(open_only, name)
{}

#endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_semaphore::~named_semaphore()
{}

inline void named_semaphore::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_sem);  }

inline void named_semaphore::wait()
{  m_sem.wait();  }

inline void named_semaphore::post()
{  m_sem.post();  }

inline bool named_semaphore::try_wait()
{  return m_sem.try_wait();  }

template<class TimePoint>
inline bool named_semaphore::timed_wait(const TimePoint &abs_time)
{  return m_sem.timed_wait(abs_time);  }

inline bool named_semaphore::remove(const char *name)
{  return impl_t::remove(name);   }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool named_semaphore::remove(const wchar_t *name)
{  return impl_t::remove(name);   }

#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
vVwNru5w1B/iB1lHtXtH3khGT86gyOJV1LY3geZXzCd7y59uoAclAK7vzoAVgAV0vImVUpLNrNKXd2ZYAYNaVa2qPqBsxY9o4TFBZNZustOr4WaCsyGXs56nUXxp2ds2TALNJ4zipeWjzz+2fuFA9veIqL1Dtyvu8gHWjs4+8kkuQwpPZMltt+Us8z5i1apf589gjkVxnQPTjyq4rpaPA7Fv1hqTIGI89E42iU01dW1ojDXzscYilEmSb42RtPMEyACNsaKmbwYr9azLCd1MMVIzlhQXNCbiGH+NxXvhkU/doX1tNgDTfzSqFS1YF0VivH0hboD5wXpwJdXpLoLfqX2UUQt4SV5UNkMvNmF49l8pOpIRRHKzTpNlbqFgXJxSFIiMyHsceutdCYd0mA1TnjFyK9pdFhWFB8D/1ijECU8v0eXqryYEvKkEssLmGA8gAqYz7p+Gz7JkQIyMsCKK5Q7iO8EvjhPx26ON3n2KO9+50FSxbyOIoOeyNbKs8IkRNe7uc2G9ogKaCoytll74Z9ETXRLcgF6zlQl6fFxb+M02ijAMicMwtKfgFGfJ1on8FLraC61KfhYXhlC7lxznLU/7xL+MMyzrerG2V9QHfu1Kje+h9C9yxGrLq6ZIDTu/o7EYip0pCyxr4vypwJbBezp0q4ru7bhrY5NjRB3kmlqpgPKE6qjvEKf+quJAbhCSNJx6IFhZey8xAiNovHWmDuO8dlq105WoySFVBZCqa3a38OdSSKW6cAwKCdmo3b67HwZNxo3kmwJ+W+IOVvnasQtn03TkFjeloFDt/If9dUZYUHgbuLVGdvZLbJQK7t6+1PmunfgZSSemHjOW1yVnHTEkYl64iFF3uz8GMOgKMGRCYACfOwU3BX2KGGD0eCqvKgmtddoqF/KsrAcN1qkPNbaIxgpStzp059YAgRR9MbJxxJ2clOgCWVr4r8R85YqOLGDEEQCOTKoLEofmgVerXbjGzHnU51LY0oQqk1I2orfCIlPESCLXiljFLn5nL8BOXzjpH5WJSsvdB63Qz+ZS7yuxq2PPVAYDbRM84GsCfbzvi0KpjcvTSFFF50pkreA9BslPcEW0MOlczyRuQB/r3qmdB+r01tG7q6uzvHApBmr8MEQ3Ryx7BAjseDFA9CHNbD0FkSF47LlMAdBi/sxU5vU0Gau3mn8W2KUkQzIfUvdunumH2ghUTU1XbhALiSqIQJiqm5Kd8Tr6IdKkj7XXXjb5GMGbyOjBLfUeSnnor2qC8c5WivT0rXHTC+aoR59l7HefOAqqPoayRFJcxM4pTp0xE3OmgU6RiD9LidrsA4IJDphVFrucF8J+qPfh0u8ViRP74PkZEiHyM6aYwJhv4/NsOYG7mom8wylopqPsNniIMcObFhyJtNIXpXRu8Tx71e6R39cDYdQr31daXIOa6uUUuf2ZPGJ4RCFPXUoyc5PUYkn4CdsoKX+iar/oq9vh3CQcyHd70LDKaw5LCHxEBX5mtQY4dfcATCiUGY9sVJKB+PHFUE69w6jbiwm7oHVyzFRQbyai874Z3tFFmZOagfSA5q4KzW2vd2uTaK+XBPKmcdUkxjJmZjJdOmCt8Ui1ovETvjs6eOCxG2ASiiA2fChVS5JQuRMqBGH3k0eHebKpcgTxS7NYx3YpZu1i5ocvA/LGV+45wG1tHHSqfGSnV1IAnRVAOVBzWB35V1OgWl9iJZsl82IrZpuYDcZWiwyPE1WcgFWAcIEuOsjtRvuALI6xNYL/vMtKi0hcfPXCrVfbqoYgg4KSWEOlmZsuCDuU4fg6o5s5YiREW23j3d57D2/4NL2NH6PMu5FPaQ4kURQ5UAaLRGxUpa3aXfCtRE7TTzFvwzP5f3VFZiFTtTAI5+dz1blZSRylAYpzBlp81UCaqpnlOnH1vYHBBZ5NR4EX36pFc9FzwEKvYbJ0xMNyuL/6yht7ahjLHt6TyIOsrSsvmcOILhsdKsfF7QHYodlz8v3UREqJRk6hsUQXKCKpjODHrEn++wKIig5Huo6rEaEdZvFOdLoIVQFJLhbOzChCujt+ZbnexciQDM6wEA1sRoMbbfCEwNf/FwdKoIkEaImRhbGO1fUYASytmJ/0026Kchz3rhvPXgVx+so4HSNOLZP7gRFfkSKAqoqOVpJU5M25ZTWHZYwkl1cmG00DUsK78p7EiLKGdCXLPEBY8gO76yF+ybwH180FfoBvXQ6dICsxZ0oA3A8Cx6yDw0jEKjFIzmUGcglml3sFIgBYJdU0itc2oAgdlx5ymEycZYchOIZ6goDWyOSJIzBihugQfpBLmNINIAYITFyrSYzsLioLq8i9ufqWtCj0ZU2sR83Es7BLpPLX/sDqeN+C4CHKrc3CxQaJPd3AVUAs6LDLXZjcZ1FxflrV81wdmBiSKzJvVB2+DNr1ZowGRxo9MudfhtwKIP7aM5f1RBVwhPFE3ITj9juDiTt6H7vjRa7T0GsEbaomszxYkTz2RNDOVGR2um/HgOGJoD4bGbjlDfBiPRtWexYKEPMcZny240URI06QdLT1RJYw1S1DfXADk2pdGDjuzLE6VD7bBMtkaxmrKYdg8KBr/jx7C8r8kNPh4ItlgcxP6XyOwtSmQR9Io5sK890jDMSB6mwZkiLTN9hJGfjPd83/ACaA2X9Y9kLHQYPC0koX7Qbf11i/8YkAqv90JM+9p0d6YT2gtVk/5TaVRu5zKffe4D4DIfEpUgkG2j/bsB0/y3jkufRktNRdJRKYxm63oYgoUG5qIVapvRd1qEnAfyvZGGJFoYTfur8WbfbMZuVCZgdwwUK67gQLqlSHklywyDkgivmeMOXg36H3bQpuk/w/jgOY7m36dfj/f1T/y2DNgODJ7pcuhTaH6bOdDzLw4wYlMbsTU0TiJV6+VuHwG6M1J2iimHRs6cWpCLSszgwfoUcPCu7Z7vQMVFwDoN1nroAdauMm48dtEZXyQf0+2+nJXGtQMtRVTpUEVGQvSie6W2Yw5Xxcpm2EShy7RucI7J+RSngZNOWBrQmDd0Da8duHwFs5IOMmQJitUs3CW2RZW1KvW2rK2r1Rva3fYtJ/3PxX3z1/Zs0nPvDDMA7azvZwubhjGv/u1GmSGhDM8k3NP9JWaQ43ygS2MrN8H0uPFtOvv2k5TM3/s+5nqM02kFdvhDLh4l3qN74bOmL+NFkFCRlXYrC7hPA035565shk5tcoEGneNe8r2PZGlE2OrtvlZxCmQMwPNl8vhEEBa9nTJfetWq+erf6Ymn+Ak8RIsCzNdtgOr0a97GDB64G0GrpV/fzdUuriWuZl4YBWMVZe3PDXpVYUYJDsuDHJDBVJZ6fjIxgRrawu9n2X68w/W7R2drML7Gu3EZRdjIODuXAll0l9nxrr1Ek1yA9QbXhOmykdrt4+ouPFNp0ZrMxpowcSsGc+UQnTObqAuluTDKbUPzoxJLNtcNRoe2LePf7ueSwpNbYgr6DXK44U3KOB2zD/N/gVeHa7M91ZYxO+SJhei3IJT5V49qgc8C9w0/ATKywIjvrotWKYpqDi0xPq1/ChXsh0jBFhx3QknzqscSkOfIYJ2ZcXpdm1FsOguusy0KopsArorZY77aoHyWGA/RNnbHzQ3zrO1NHiZjjphvH405aZeZIIrrzN9DFrQkTXhC2im/fr+uJMVZfKGz2k0eJ8fJlO3ENbQCCkYyAJLwGWZxBuX4VxqYhvmc1FhzmYKV6uiaewxtANj90EB74CPaaWUwfBlEzviPaaxkuEJc4dtF5Fzo3HbqKtvNZDr9UIljaYyuClznnu13JfRBNt6s0fHg0n+swIo3zZJF2CKCuc+KQ4wgxOtW8+D42rMMF42bU399vv1Bs4koIJElR27RbM7gfvPmhxOO3xNw1qFawbLUd9Vx9S4+UPsCTcZ9v15P8eRGXXq2EBvRx7hVswybvius8h9bf9iy68NAPgGIcY0TzVbfoq1pXmUIdPsa/xl8fMQ0nPF2x8YfLOD8FuMI5f/Rt/T5hxWKw1uKeq1C0l8lHY3G7y74FhVzmOcjuZL+ALdH26xa7XGuc8H69A5o1RsuHqvz/66FaCTNpg1tQJiN4xbTp6tIjhIuX3K9wf/0ykdtK5GUC9TwFOchjYoGkxAlGjOxEnCSlPKQSXyhpKY2Oum62iJ510y1jL1o3TmGww+Afi3iZSIbrQ370fgqjrEJEuwrxkv74wSDK6Ehm0M5vzkEu3viylY5swbccyRdVzCQRfMtGzNXjB4LGh9LkfKp06jorzi446Ofwv0polkgqCYGJzUgKEB7dEbcwsVxUlQFOIgPkukgjSrjJ7NYkFsCEaVL25BxBBMNBCFvhIbGOVXUJmaFoIoByYhkl79h7C9s1w/XTIaR/TVpiSC8FZIzQAUMzZGsmFKrHN+2OS2k3WMS2iWFlwSlAKShgAa9emxWmGL2gIZndRhdtqKyjy9MXd8jb59jEw7vr+H8ki2oWPM3BeW9iPEMV8rJkbPW+xVbCr4kMvb1G2KmbGHVEPYrSkhqJnHl42EJ9O/2DpUSOZKPFUGpVBJozZs5TNzYW2oQ49xwpklnKqj0EKNHJjaO1ZKHLhmUVEkyQFSacQKAA2BQiYEpLxLko51NKz4qKG/wg+lNvSqM3W5d6rxealilNzWTSmc2MNfiTkl0t9pjfNrFbVwKmTVF61OOU5NeANFEB0qp5KcvNeSkQSkrDwIVVgK6fdd483K5Nf/V8W5I4hGlS1uiSIEL3eeFFVM0qG9qNElaRiwt4qySU3b0NRxjH/gbF0ZTFVcGOto5IaP91HhhqEwVmecCBM64Cc1zcHzPfeNuP2xQk4c78JeYO8hXLs+8nWaXn6yU3GYWtEhVvHHI3i4jd6NoVGhDFfQxko6kqoqTVavJpbnxEt6wIEpxrkI9XtLSos0G7qbHPdWJtXBZvBc5oEBn0w0jnQk5R35s4toG9JaVCoZ0oTjziRPT3XTcCqZD826okF2uMwUyFIMgujHkpohfGUeGIWER1c7h23qLDYWD8q1P3bIMlEbh0m53ge7e/KYml5zgMIJhCa+FfFmzUOstGBXD8OX3zjE5L3qebaInFhHLja1z/N5MAJYBUhChpLVzqRsW8VZJKJvpx0JVXHHLQOI850sMt35Pp+McHV8BxPAAADEgGeDlWmdv+/yqR6Ez8DpeY/M1CVZoWK6Ulnl+xFu5Q4XBZowhfbx1YyuHN3RgFseeZ1TT50quFdfBiTUNU4ftPH4wArxdKgbxxk4NF7GgCWEOdEVzcGH1WFmy4qQ/+glekPFg7FaIAFCuZIgiG1oDRKvAnd2kkYdaHjr5LhufiMVc3vsLNnzQSO089Ncyn3As0zXoLBlKLl/ovABXp1msZj5SEABXM0fSMyDeTbEwVEIJdgQx8Wi3FledOeySbdKywRF75OIErr1nzhAwkuunRD8s3ypkO3H9q7F8xx2VXyNrg5c+rKzxMLKbLWp2D9gJ9oDf+LeD4uFfdzPaekuiEwpMQs81AJzyThTNHDUkm+ds2wVIimHPMUUfTHkJ3+GBAaA1deYEiYpEdvepEMSnLlaMNOnXME5Sl9CAS9rJaUutaL1jE95Y06H7pq8406d5k4j4cumXlAn6+ikfW7kqxWo76l2qkI6HYzaOZO+cGe2kP/ecQ8HO46sirUcimrU1COA2JOGfdOjoL3e0Qa/DslGnR3oh4yg4eOdl9vHb+PKtQwT1r4mNjU65DOFr6ZGsLlMUgASI7J27UCBJvqiiflHF4B6nJfM+Vy4/Q/qsor15JVgeOVx7LuTp84kanJ2NqYQ45DmKYLxZVRZTDYvk//rfjYn6Nt7Qy1PLjOK8sJzE3Pg8wjXYI8Gy0x+ogppRce8NRalQ1xWoxCGe3JRc9Ub7jH5WGL8pgthr3yZWFH4WdD9MqzeQcctQP7KRZhz/JP5ceHEv82enNEAvxv1Ynk49yh6KyvAnZjcrOjKvJikS5ToZV2tcIgQu/yvnMmUCHCfB/tGQLPFuItYm91K/N49qqxN2ZjBkzfu9k0VGukNbmqp1bChHkoymYWAfkfwYm409LUe74Hp4HCF24spX2Z0JlYnKB3jWDbOyjPBOmqkFUP98xWKpNAc+7CwCtbpBu5zAji1B1G7vMHqA7IoDbQC71UZhw2cr/ml7dZ53qO9pMI6hc81J8NoDcWCoArSfd2fZa2vOtRd0aVJuqPpmaRtSEaFJ2mowVhoQhBFVF1Mq7kAWiCtgKCDaxew5/DLoyYW3Y77/5h4xSdl45niBSS761blZTU8l4mBWs1Mrg4kiad9BrJJ0GiQZa5SOKrKXpksDFLlIV2Urchu1iapNo6/S5yCdVnCJSYMaZJHxxwr4aKMz0c5OeFfWTOAZKhj3kAp5WwSd58DpISUk44aSnQZ1TU+DizWUH6MWAYGQheKessHnMutAlKSv0YQUio9EMEDcll5hRtMCFcmTkzYhZJUwWZa1iMpqlVeb/Mu6Vtcb6+13DBwpATK3UqObA4D3YG9clzuJgTrpo7m5hE6JaZI0vTSNDblcyZG4nQTvWVSOmS2JfYQ+hSgaAZxqPAVoZCFCIA23XsACfF+/G0ekSrmhrjARhgRIDKYO0Tz9lL5m3F2ZbIAAaroAXIlQuK37vQyQKDnZcDfOLTqsKlDyEaVK2qJUNjKQQSvIErfFXVypBmsm1Aeb8+ODz/igmVVnIukUM1cq6zcF4wCwFrBCzMhr2txV2/Wtf9Nv/a0HJ/Wd8Hl1OJN+x5+3VDutvj+0hImbC9cXDmDLnWzFZzLluuQw6v5/ft6+1n2baV9gA33XoE44XjJHymCo2KAmOnlZWACQAGIQegOWhQmTAiszvP00k45azFjQRLkSJFQx92bU6NfX02M2C0NDFySWRRdBVSEzh8g3OQ4i2fAWHR2vIbRC2vndPJVzON5kY1/fqB8L6kUURIynK8SySrJius0y8sr+y2emq6cghDsUwiKAhSn6spxtLJDzG6ASVDvtnR61a4Ve2YohIQRsWM1yaaxnj383Cqrf2JzNalOuNpc4ViFsylCeWtAAjwFaIOo0KIwaAKEFWsAQ8V9nxomyM4qOaL1U6NY7TFyiwFPoJ3bwwhmgmKvJZwFKJiMncA6kXPBnHsK75taux/DQVXqazwKVNWdUvBmXBbIMe6xupNKTBQbVadAABUtmWIgBwAH2+6V0VWm2BbIRED33XZAcA991JGfebhecw3/pG3e2VxGKTelCVAeYseZETFrXVfDKpzyYq4kRQeJzF0P6fcstW0+/zrfTvQQ8CRtuCmSbqPX0QwnIVqGoxxX2iGowKN2fvhA9434BDG1vvZu5e9TTRRZ9274sbQ8ceYZATe+WhqjNh9OqtVIVaPGFZvmbexCn5YpnwABiz503MQBDyiAtQXkoX6hBLlb/6o0KcpERtHrFJdP3o1mvn3CDDoHgWP3Ped4HIV1SqW4vGLyu9GxwX4N0rIwuRxCQzAClXWMKuyDGL7TtABoyj+CRXFNqb1XUek4b/8/4pHXlhwEuH/gGkfr+s2nGos+nQsybyFf0nW4zeIaH0TF+ICKP3z3HKTuPoyQLNVZcE7/6/4yQJxMbI4kER48KRQ9SPyQU/Uvmfd11z1uvDIjNXuPPgtwNlz7dqf
*/