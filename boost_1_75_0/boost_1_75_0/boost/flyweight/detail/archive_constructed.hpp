/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_ARCHIVE_CONSTRUCTED_HPP
#define BOOST_FLYWEIGHT_DETAIL_ARCHIVE_CONSTRUCTED_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp> 

namespace boost{

namespace flyweights{

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

  T& get(){return *static_cast<T*>(static_cast<void*>(&space));}

private:
  typename aligned_storage<sizeof(T),alignment_of<T>::value>::type space;
};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* archive_constructed.hpp
vsLdunyN65ewmjV/zV1sc8j9p+etEH/2fQQ0QX/dh/lP9mku3+g7hU63GgxLiv/qd8nVF0lmX9dqX9eKr4XD73r+dS19Tbg2F7MafIQuvxtiKAtyrEJcG/zpsz6SKVB5LLW1ehLUIAbVGlyQLgsB68ILBCg5olB4TKBnbizg2VB2G7kzcD/h3hz6KNMjq6E3NxLqEvT0FeBsJWCYfEOOK9a7V4Nb5SFxlsVe/6xJ+CXeeSINm6OZfanSOpvHRSZMIDyIeT1rGeiQadghjzeArDiDVNUnZZNvV4WoLHiZVYKPV4Xm41XFfbwIx8SGtcOj8TPM6nmqjzDXWBX3C9Kgl/DNLI3nY3xodpdq7RYrOKvhWFxl5k7GOpbnc5ZfYDawPJgD5BEAEyzs02nj/fKkSaWsc4MmMVj1T6zKNBkQgCyir6p8VjFNhnctQ/8f+KQlqVB+n9eNuxvr3Rw57hAbpo4aOnfyDlYh4NQx+D/sTkO33zv4NY1JfvXciqiZ1u/kjf4/9lHKHw7Qde8+lFff0By8iT/9jG7b8mw/PBBGn9pQEFGW/frp2fSpG7k+Vf9pNFLr6upwUmvytxH1qc4FkfUp+6eh9akbA/WpG0PrUxsi6lM36vWpDWfTp978JBp96nJPWH2qbBcy76ZdOn0qm2P3Q2Nk5utDLhzCOKqBJ41yPwmchRw+CFy43f8rWxYaJ2UHd3vjRDq8c1Id
*/