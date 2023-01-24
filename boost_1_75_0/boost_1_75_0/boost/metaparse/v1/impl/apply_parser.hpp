#ifndef BOOST_METAPARSE_V1_IMPL_APPLY_PARSER_HPP
#define BOOST_METAPARSE_V1_IMPL_APPLY_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/unless_error.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct apply_parser
        {
        private:
          template <class ListToAppend>
          struct do_append
          {
            template <class Item>
            struct apply : boost::mpl::push_back<ListToAppend, Item> {};
          };

          template <class Accum, class S, class Pos, class Parser>
          struct apply_unchecked :
            transform<Parser,do_append<typename Accum::type> >::template apply<
              typename S::type,
              typename Pos::type
            >
          {};
          
        public:
          template <class State, class Parser>
          struct apply :
            unless_error<
              State,
              apply_unchecked<
                get_result<State>,
                get_remaining<State>,
                get_position<State>,
                Parser
              >
            >
          {};
        };
      }
    }
  }
}

#endif


/* apply_parser.hpp
IUmd+/LWBlk6yr5HLsf9dxzB8puEcXzmyfX/02t7tAPBIsATgF8ClidRPAS4E/ANwCzADEBfwCGAasB4QPaKmk7dUkBfQI/p3Hh3pnHdIZOoezKgDnAxYC7gWsBNgAcAzwIOA/wVkImh6ALYAbAXoBQwDHAyYDLgXMC+QO86YHfAv2cC/VRufbZrqXsN4ELABMAwQCmgBLAzoAugAPBuCuQPeA6wCHA74FrAFWw8SJ8K7smAYYDDAf0AuwK6AAoB7yZT1ANeBSwF3Ae4EjAVcDSgHNAf0BewHaAA8PYMihcBiwE3Af4M/L4GeAKwCHAH4DrAxYA6wJeBTirgREApoDegC+BdkO/vAB3Zdp8I5QH8EvAsYBHgFsDVgIsBUwFHAwYB+gJ6AToC/j2B4k3Aq4C3oX1rAYsAHaG+XoC9AeWAUYA3IH4Z0CsC3AS4DnAxYBLgaMCt0G5ScPsAugDWgL5ZCHKUMJPbTyRzoL9mUPwQMAOwF+DPsyluAIwAdAQ8OwvaF1AOKAQ8mg7hgB0Ar+qgnoCTATsDXk+jWAAYBTgAcFA8tz5lFDIFgKcAWwJuAnwH8DVAEaA9oCMbz4biWnB3AHQGdAHcDOgJ2BFQCOgOdA6A2w6QLfdl0MdHeXp55VSQB8C5gMmAkwEjAHcmUBwGbl/AzoBtAAWAd6ZQ/BHwGuBRCC8C907AAsDVgIsB5wImA04GHA04HLA3
*/