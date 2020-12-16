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
VUpNlaWmKqWmGktNNZQ6jftZn8VKve5eKLWISk2mUoU3D1nXlrL8JhYRA92bubmK5MIISdlgWbziSh1oitAOglShuzFjJlLskmeLyjmwOPyrPUZ5EooRsJskr5mSxaPTlQfQgSaB8wzXaVPJgaVb6w9vf4sbtWf3Ue//vEhKhJR9in3sXRPt3KdK5Fm/f4OOMA/KO0/W5ZVgpmObKku5qVx8zDJ6OK6Fmi/8CdwXR20PoZgmk535MeKBtcVNzK0zicVjSSy+a4acy5/Q7R+WM7G4LyJT8y9ItN6ZG4AqEjCeBJksJpJjXyPAxEQuMRMCYKr6Noe/zcGaF1QS9LPpB0pm9JFB6wq4P7PmmEbvMTmbVohGkCyvUBdoHzAF4qRaO0ksYhUCDyQznQ4hT6GeG8ampoFmh0M5xcpIOB4kHA1w1Z4lI5FMZqkTw/ynXEqJeVouSy9ka/BC4v0v0yx4f/pJGMcvYl7SmtTVXt9mOE/zdWd6I8IatZK05Bduckrrkd2zmPzdhO1hKanbJC5NkERAksBSouJORkW6kYoCpKKTWoNcbTmc66O038epekDk5iIe/OOMnvYQ9sLN7CbKGmJmQ5TLPIj02qKg8tJaoiUw1YKWo8uAlmdIwa97Q8E7EfQspXBxxSJNv8CfRvIQvQtcQEniYOw0MEqmmJHksNplQrUyKRhOptNXB+UN1jXT3KzL1JEnVSKJett5oOG07N23g89t3T7BvxFMa/zPw38GoJcAiAAqjZ1uwBEpkctrRT3Ua0WpTGOO7yk6jRTPtZgm5FEGXsr4/9r+F1h/dQWukFvaMifb5uPgWKAMjvepPXvdwwbHZBgj2mugleFQTj5HyRgG2uMzhTrt2DOMHVkgjJX8JYyd/UdZn7Y+T4tMdKGyPr1/px19Omv+yZSfriCZ1ps06ZZfX2/WGdcbvLxGycp6s0701hN6ANGOLuulwwC/vZm+dNxCtyGMAN25l/oCObjUt4n4luYXuVYYbzlmGdYTHg9VLgrfxyrLSZbcSR2GZBkdLVt7/J84YIpaYlIOJc1hSZPqycUhS7vrn3wZaOFUpnLXy8Gm8hwt/cnKU/npe/Sp3EtJd96lWuLz6bMdTZ+rJ8rpc6mcPtc8VkY+CmUdvNqh59hiFMZ07f6xqKhXGdm1qXkCkq9K4ZWykvguZ+YB2PSd1KBQ8+QssARvRdAKKVUM2uDn+KTjFo6liK4xU8WU8dJTbMpI+1Pu37j89xwNTV8Bl//Enawq73+vo0wbNyjjOcJnR958gWeduIHKG2anvMk8Uye1vMXj7ZTXg2f9cT2V992rPJeteIZso+ciFIp7ZQwHoDrxgbWXfPnUDjSh/SALD9yQfk/d6qZnFspOeuzCLVd9+lmMsxVZKaivo6cvZDe0YGHi7n2c9E5AD5TQxfwaryFa5Wu0e7v0brYWri6CtXALcJC7h8G0JAjrp21rRD0bsESgEbKKkco56tDLIbFFqwMTgdn451V4wWW3xmwnJT38cb+HTL4ZT68ITQg0R1XeF0cpOzK39h1IiDJBvXSaIsWlfWaQXMQnq0RTBcC1a8TvERlDmtbY9sc427PxMfXKMWvMvfInh41emaL0SnrGrFtFM1G3u485bID9FffA6BTvqKAHJLTa7ZJEt1tJ3W57Aet2v0yAbud9QVdVaIGZxjZ3GJudbKnai5dqH6JxEsT7+LluNOWAygFKP+lwXfowd2v+Y8xjeV39AORdlsJIjHPIwyenncMn9f7HKiqPR0fV473WEgFe8eE8JUxzQ0MQ5oidoYxB1QrqqtTXs8q6vqNOmut7zcmzqK/xFPDhlWqhE+k0sDMU5Ludb99yaPPco4ipV/s=
*/