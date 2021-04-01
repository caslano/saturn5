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
EafDWfaUFycJFObPhqDuBzV43mGi7XSP0sr/rk1j38r6a6UP8tbUj+MKAUi4Psc3eqjVa8f1dMRj1lgzd6rHbrJR9fbiplJk7dju1kbo0SD0C3wKhLoZObC1G+z+tnD/qUvFKv0wOz1rw/Ddae66BfFGLgUvrf/wMd70l/zxO/vj71urpwPwTbpbKUdbMoN+V1udfUcGdagzDO+wDfGhvP31HrpWiWY44RrFl9Gbjt0QlJ95tQMe/2NAU2vJ2UT5biV9uXctlvALi/pXbvLQSpCzg4DntBo90sGUZCeiixV6ekDuE1o9VrzNgXm+5scUkp9ChI6l5OkVM1tiCE+AAnE7Qnlof4YEemgIajtAvy+cBvrpdshqGpNnipy1f4Gp4r2V/mr+eZT+r1iatHPD3gFAuIswuV0Qr7ZckXmD46SHG589dh2LotDs/eW8G9ssdBPi99VNlN6nkPdnv1n0RssrI/fBW1iPCw9vM65ddYY5CxyDBZn1HjcsXeHEwgPC9qJMVrGC1yizJTQEOG4GMRuwK9j2m+KHCjjS6U2urxh975BcCDfqLbVjPg==
*/