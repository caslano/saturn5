/* Copyright 2003-2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ARCHIVE_CONSTRUCTED_HPP
#define BOOST_MULTI_INDEX_DETAIL_ARCHIVE_CONSTRUCTED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp> 

namespace boost{

namespace multi_index{

namespace detail{

/* constructs a stack-based object from a serialization archive */

template<typename T>
struct archive_constructed:private noncopyable
{
  template<class Archive>
  archive_constructed(Archive& ar,const unsigned int version)
  {
    serialization::load_construct_data_adl(ar,&get(),version);
    BOOST_TRY{
      ar>>get();
    }
    BOOST_CATCH(...){
      (&get())->~T();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  template<class Archive>
  archive_constructed(const char* name,Archive& ar,const unsigned int version)
  {
    serialization::load_construct_data_adl(ar,&get(),version);
    BOOST_TRY{
      ar>>serialization::make_nvp(name,get());
    }
    BOOST_CATCH(...){
      (&get())->~T();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  ~archive_constructed()
  {
    (&get())->~T();
  }

#include <boost/multi_index/detail/ignore_wstrict_aliasing.hpp>

  T& get(){return *reinterpret_cast<T*>(&space);}

#include <boost/multi_index/detail/restore_wstrict_aliasing.hpp>

private:
  typename aligned_storage<sizeof(T),alignment_of<T>::value>::type space;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* archive_constructed.hpp
sjv4Sb1SjXJ70Y12MajkUJ4i9wdSrW7Qu/SxHuW6pznbmwBVJ4e5YuJgVRhE8cgwFdpDjWi5kvfJdIHijzjq26fPcKjofgGs4d9zEf2mY7+HB0vBrbpmQ/hI9xPhdBatZr4WHDbMb2c33SNruPMpcNTF84/fzU7ZmBq7wA35hiCIdS9NgDRhseledtrNY0dVu6cymtvf9z+f0bQsLnDHwut7Gc0yU3aux2jNJFgC9/OS4FsN/NY9WIBbuGm+buDacF9P0afC/Yd7cBWjf3MPFhsW9Ut1+a7oYdvNfxH8b+ZIuI05DqI4oBl9341hkx6t7Ee6TV9CnIB6FtxE3INNnMtjWmqWqN8Z9NFUc14tf83W1Gji4wODcODFCw1klgqssG3ukqDuxkohDrtqXa30MGNMFDLquwbZD5vUsq20K2v+hQ+P2/TmWPMtTge1+fFCjX94hMDzZhTTrwoYcXvJ4NPeL68/K3tmViF/Y7z9Vk8iL+aCbf4Gu/tQrWknzCxLE0X7YhZx6xD2SGQkwnGMtAaGZqDDEWWvpgXlDbFRfZWULVC2z8CYBEEOcASTeKQytMOy0RlvVmrZipWF4duas1X/hFa+RCtXweji82wxwlO2Qfnl9m5VXeV9SHPWhPbl2dkK1YVjwrwF9FMa
*/