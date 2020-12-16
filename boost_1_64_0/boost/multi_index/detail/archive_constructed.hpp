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
wiBU+Tadb+nNO33Ha6zPWd3otmslAo6lLyLO12HPm8Bwtg5r7MRwtt5axHC+3vozhvP11ld2YXi3V+ur0N7lRojhWuwBer3+Grr+9ZIiipzMEXYEHm5bK7hnwbuLwKd73agIgvSan0/X3Rt1y08k8R3yPVFEiWN70f++j74VEigaI0/QugRaHtsTmW3ZaWSlAgWv5rFI/fUGVKOmfR3pc7VejsbvWCKJ48gurJLEfxQP5LFm8Gfzn89B4/DTtW3/a2kZC+FnYRS4ti+2S7D5LxZeLiterfsfTRt83tlelltBeS1pY8Vg0JZq/X8hY9aj9PqW1YkjoiIuraz0BWakjZ2yx+0mhtpL6PJ2jPL6aRKGeXYN8RqK/OutH34+gOXVZyhvpfnyCmHbvpXlvnvd7bChmgB/uijFSuOk1b9wiC6r5sPsnfzniy4aukyN19EzlEKUjpXnZRH/h8p0fdkcTKWL09DTUQDXO5v6zhUtk50Jz05938tDcW01mfMsDu10mOwx3WdZmpYoEyfNLM+6BnukATukZ+q9JYuzELkbxo4bh+I/Orwb7ku1Po6m73iiSDIn9GNHXOPw2abNr7tpP6zXhayvOlDHdpG67nXmR4+rf2Y2ua586+/93tcbtgllGHlRWLXjU1U2MI4extG89lGFJeJ97d9aGLkMfb6e91/P+0WS2lEQRqlQOcbcLZtDmi8j/vkuiuPj9ca6IAkKx7evOR//XOqNu79e3y1n6SeiCB3P8qJrTv5aBq+bX1feptf1fojmzU6Eb0Vu6iaOGNIKh/75yri7Tq/xBp5eWTpJWQTRsPSm/oX09BrhwBv4GqGIkzDx/Oy6v1sm96qVz8tC1whaF/uLV9M9pVz6d5SOBnXgf4N9mNomgXpC7Wfkj3rSvf/25IjJq/YwzRNb8thcnqqQdxzOMy6oHsxYif+4UcnFfSJoomC309fhumOIV/ss7eeVh0+ys+VxxFQemZ8rA5ukNpc7NKZqCfd631HhMkSVp78HPb1bhy/KQm1uPE3lnfhUu5HG+dnc5I11OGgnKyE8m0WMn50t78Fwtt8sb6LDST1ofdJNEcN6wLPbm3FskqT1xL0a4+d038Bwfk63fAsdrqJCnckZqv8oRGoFRZD6MeqGWgsL7U6tGrqrXs9SvZDa2VdsqZ0+mWvOq03dTuFZcZBc7+ZX61yeyMaHyhWoXFDnMmLqXGa9Y48iOpcRqnMBzDumZL+A+pjZwkmaoGJp1npZpZP5sta/OI5XzvX71TfUuQYiWvWCuBjhuHmP6D0aB6AuT4PpXjSuS9uP+9kKay10esP1KgfGEGd6lcfvwHCmV/kWhnO9SjqB4Uyv8gMM53qVszsxfECvsrobMezn+L6W8mWrJpbe0zrtZn2H4Wa5vo9u9CXwdhUUyXXrCeGdzLFxnR5PDubhW8C5O8fUofl9an+6n1SYfKCMwc0NmSwowpu0ff8MRg+q/U60VbXWbwihDf6IxqFPq/bAufkKwyACrmNj90RGTW598Ybk5SeDHBUN+k4bM3E9WZK3rgc5cIqEuDtu4tBnyFvbDMdvGObhfjsG8IHvwlsZByqV+JKbYFj3anX2FZPL6wzP+ziH19l3DHxYnS3u4hyzzn5h4Gad9XZz3KyzP5s4HVtal3oj4Jh9tn/+cJHhvE+zdzXfqnT59YcSHOWoIxz0W7f3cYjDbFS9rrzVASdAOM4Xz+A4X93YOClRNfSa6HvtVVxfmru257qxc73j/E5qnOv0zOQkTu6/jUL9GV0FfZ+NIA6nTNqtLtb/vlHEwcnnevtUDw/EcL2CHBU1xt0Zo+FNWSjw0kB85HP8qZqAd2PGNb4oC7aw3CI+r/c=
*/