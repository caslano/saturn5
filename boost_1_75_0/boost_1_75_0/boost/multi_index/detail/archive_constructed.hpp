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
yHidAWusKlWgbi+rxWKg6O0Iju7wWwXTkswvfPwpTkOyjRE2kq92ncZXaedJ73ZDO7WyNhu2ggV/WPPaIed6Fe7WXc1P9Bb9LDSgaqL/gm4uTDWhReP70M0hcb9eu1+va1xwPmbNsjJqDKb8X1/zFq+E9qMPGD6CWM9uDNLXETlsOz33MJpTieyffpiLy92aw4hzBM53rOVEJN6r/e7r4Vp8N0o5YsqBNucn1hdFFN2rI1M+UWKRBs1IuvRbftONn651yRLJfahuSm0+Ko5+Q052A3Gymnx2ucDpDZCS5HNVUj/NTr5shK8eDsgTqEp1xE7n7Rb08R48oqe7Ia1Yjod2a3Cm7dXSUPUldmpjF2s7tbqprdipDcjnXWAEqV9a6PfVF7V+n2tNv4emcL9rLH/T7w8vaP2mtKbfedRv/iP6zvLxKULagLGaM+Vvdpn5uKoK9rPkQJuLOVtw3onsKPNOoIagWgnLpm3mubH05/exIt9chtlADJRnJSyaTKYu6XdrlEfCvHPpSIX9GeUcbCEXkSaEYqrloipxnAXHWrpP2P4Vadk+pcSzLvkCxwfGi3BBkFh/dMk/o55VoxoJZEALeBNUR8FkG5cadpBEM36yscZ6024LG2VP1jNEdTF2WtiNL4mq/fmqUJIEaCej2j0BqOARVLs7kQQCS4GPCXjLlRen0Bx1AYpTBRTnCE3TTjLdQCNvubb/98Es
*/