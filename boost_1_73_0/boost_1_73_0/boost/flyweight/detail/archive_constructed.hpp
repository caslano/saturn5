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
r8g6X7aR2FZnQKa5zA51xVORi3SfEbDHfRg3dc2lKXeOkuXOxoNtqy/PdQg4NilLN9WnxEpJbGx0OzaIqE3lMLmj+SxqanpLeOr9PXyKZZd4HXShCvODtgge4Bq7nGFzc8IyQp4RnlboxpUW6JponwPLP4peWN/tst3sydhtkgsk2hecHL7A6UI7dP4LdDsK4mDwZEgorW1bYX7p0bbR1DcGZyg8omB1k6Y4q3wIrZACwZIqefg3rxWcs7LhaLgsEQIdcsixvn0xjzleMH5H1uNgNYud+Wo2g8Fc7U0O7fYyXMSL8WIWOQHdCCiZ/BG8W84mtsmpTlj2/9HTX2kvfG40vPMPHre4wx7gOUqqGh3IB27YX7vXbb78voIeAr+v19K9Yvamf1emC+wT/tz53M4aOLDt9PLKvBFSmAGeFvmAhEMgJ2+NIxJ49w6bO0fKf0UjLnlW5yHK+PLA7X9kdL3hp2rr3tDGSx67Zzu4AzgtOZNN1W99dvxcWK4EJ8F0FryezqbxqRNkWftjqr287IFwEq/COZwEs9XEaZmsrWuTZPHWnnCjyQSCWbTAG+11+LWYwcUOAtf5F1BLAwQKAAAACAAtZ0pSKBSGRrwEAABzCgAAMwAJAGN1cmwtbWFzdGVyL2RvY3MvbGli
*/