//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_FILE_WRAPPER_HPP
#define BOOST_INTERPROCESS_XSI_SHARED_MEMORY_FILE_WRAPPER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/detail/workaround.hpp>

#if !defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)
#error "This header can't be used in operating systems without XSI (System V) shared memory support"
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>

#include <boost/interprocess/xsi_shared_memory.hpp>

//!\file
//!Describes a class representing a pseudo-file implemented on top of xsi shared memory.

namespace boost {
namespace interprocess {

class xsi_shared_memory_file_wrapper
   : public xsi_shared_memory
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   BOOST_MOVABLE_BUT_NOT_COPYABLE(xsi_shared_memory_file_wrapper)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   xsi_shared_memory_file_wrapper() : xsi_shared_memory() {}

   xsi_shared_memory_file_wrapper(create_only_t, const xsi_key &key, mode_t , std::size_t size, const permissions& perm = permissions())
      : xsi_shared_memory(create_only_t(), key, size, perm.get_permissions())
   {}

   xsi_shared_memory_file_wrapper(open_or_create_t, const xsi_key &key, mode_t , std::size_t size, const permissions& perm = permissions())
      : xsi_shared_memory(open_or_create_t(), key, size, perm.get_permissions())
   {}

   xsi_shared_memory_file_wrapper(open_only_t, const xsi_key &key, mode_t, const permissions& = permissions())
      : xsi_shared_memory(open_only_t(), key)
   {}

   xsi_shared_memory_file_wrapper(BOOST_RV_REF(xsi_shared_memory_file_wrapper) moved)
   {  this->swap(moved);   }

   xsi_shared_memory_file_wrapper &operator=(BOOST_RV_REF(xsi_shared_memory_file_wrapper) moved)
   {
      xsi_shared_memory_file_wrapper tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps two xsi_shared_memory_file_wrapper. Does not throw
   void swap(xsi_shared_memory_file_wrapper &other)
   {  this->xsi_shared_memory::swap(other);  }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_XSI_SHARED_MEMORY_FILE_WRAPPER_HPP

/* xsi_shared_memory_file_wrapper.hpp
X5G7nYkvW/Q2uFlxN8d/I2MT0WcON+f2E+3NiQpEXRzahCq1IedacFeyCUl7ot+6TbWsxX25SJO2F7m3MSpTlLOtjX2r2xg9X1ZfP4fK63UttR5kih60HjwZMVabw4tycuCs7/Tj97jbjGOq180nkH83o5XbfEmHt5dvGPczBssG6QuWg5vuS2UxMUaXRegdUyNk0LoHZIq83AqeTVIWxcXqNsS8rK5SFg9qfdbK3/PEew2slHXc1yxjKq9ZkoJp6S/3kv8UI9qtfHR43f4Rntq/hDdilX9f9KMIy/6ZoNzottZmpFuvR51vbsUNLjpqlnPfg/DsB0+64jnvsiAPUmLnOQ6eQcTT2uIZXEmm3iN20iGuOql7PT6o9Xb7GiSXl+0OtC1tOYIik88+KgTuRfhiyndFThHPOuWDKvQxvV5s3Rl/FfFmm18iBtMM4P4NZT9OQ1okHsT+s5Gr61Lc7Wv32QXFmWoXj7b130Y8bxttIA8zjKXOOqV4dJ2O5DXKeeVZ+U5dhXjDtw8EeetafXGG09bjGucM2330r5J/fecd+hLW3a6k5zq9GyieVta4someL6D4kkLiS6L4HGvs80PvSFtI/rmoJ2gOJjQ1EMsl0vP5fjCpt0J6z1ypn6A/shbSX4uJJxvav9/SS94kN4+1Pjo0lhvnUJLj4duTZc3cvndCtxFrHj6S2jrVubutk+1gIsdmEE9ikIfrit6R5LCVVZaLWdb9aU9QOdK76XlNA/0c2rf2dOSMPW3yHT5PAm8BT2rDYN9aYJl1wrGnUTiHLVXvU3uY/KOc/UTCutvStM6ygHgWozzSqGw5zO+NkUjZdUZDKz7t5+hL1jxxHPnfZ6q4Yiz++yDb8Q0VSPc1HVeCJQuoSKSmtb1wFPGtNzKNttZd7e3j2I7g7JsSr3v/cuuPml+3+fwyToVVJrcQT7FZF2PCUCPCvgdU+kV8HN9FuMi40OoX35Gbj/LI/KVZhZnFJbmluYVlIeufcyn+20yHbUN0ryiKZwM/W/H6LflncF+w2sR+ik+vk37ekG0j52FEC9bN7eQ22/RgTaq/ERMiP7IL83K0LFpD73LkidJ+EmnPbkhpM+3yR9ffQuKfB3nendNnxVFXxUFrd6UUx02mvv9c1ZfO/73EP8o1/+8FyyukT7Qh/wbW+7LouY7oELIXKIT/efJPIH9/A3p/rhHiv4f8A7RPaWtbjJUdDGM42Tsq3iCDxwi1W9Zw3y8rYY4hzAiyeVR8HO2Nctg92uE5UuweI0GjxC41GpgBGiPuo0UniA7VicOwhfw76wqNRZ6KPNb9VOJJdMhRu56Y34kTd6fiB/0eNELpG/EkE6nx4ubv0lx6f3DdoDirrAyxhYw91xH/MNp/EWyPb5NbTzfZifi1jEF+dJyZlFlLniwmvkEuMlTHodNV+i/2rgQwquIMv5dsDtgFEshFCBAuCUcgcoZDCJBwGSAkAQOiIRckEJJtDoyCGBAVlSpt0aKlgoqVtralLVZasVLFllZsaUWLihoVW1TappUqraj95p9/3+zLm002gPYi+vPtm/nn/Oeef2bqi1eUlWj1oZxhKn4KU6273UZ86/B2n0s/FonVt7XONk/xjhFvpqP/OZyGewFpb9gI7+YJ7xLeNTQiPNzjCneHuS8Jj/SEe8IjQyPozVJxJbAVV8OWP6oOryP/Z2KuEyLNrHxPR60awnnj595QY6GbiG88lfG2xgG85sN7K8qvRFl+uUza48jlmN0o2ST6l2OHDFCe7WXcVl4bRvL4GBQCquLymhGnyqu1zm2ViyJrrnxVnGyv0gyXvk+PaynbokL/dZzpZL/c6ADuWUaIplwqP1T4xdbacAE=
*/