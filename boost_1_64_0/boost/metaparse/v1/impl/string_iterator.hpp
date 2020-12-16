#ifndef BOOST_METAPARSE_V1_IMPL_STRING_ITERATOR_HPP
#define BOOST_METAPARSE_V1_IMPL_STRING_ITERATOR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/string_iterator_tag.hpp>
#include <boost/metaparse/v1/impl/at_c.hpp>


#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        // string_iterator
        template <class S, int N>
        struct string_iterator
        {
          typedef string_iterator type;
          typedef string_iterator_tag tag;
          typedef boost::mpl::random_access_iterator_tag category;
        };

        // advance_c

        template <class S, int N>
        struct advance_c;

        template <class S, int N, int P>
        struct advance_c<string_iterator<S, N>, P> :
          string_iterator<S, N + P>
        {};

        // distance

        template <class A, class B>
        struct distance;

        template <class S, int A, int B>
        struct distance<string_iterator<S, A>, string_iterator<S, B> > :
          boost::mpl::int_<B - A>
        {};
      }
    }
  }
}

namespace boost
{
  namespace mpl
  {
    // advance
    template <class S>
    struct advance_impl;

    template <>
    struct advance_impl<boost::metaparse::v1::impl::string_iterator_tag>
    {
      typedef advance_impl type;

      template <class S, class N>
      struct apply :
        boost::metaparse::v1::impl::advance_c<
          typename S::type, N::type::value
        >
      {};
    };

    // distance
    template <class S>
    struct distance_impl;

    template <>
    struct distance_impl<boost::metaparse::v1::impl::string_iterator_tag>
    {
      typedef distance_impl type;

      template <class A, class B>
      struct apply :
        boost::metaparse::v1::impl::distance<
          typename A::type,
          typename B::type
        >
      {};
    };

    // next
    template <class S>
    struct next;

    template <class S, int N>
    struct next<boost::metaparse::v1::impl::string_iterator<S, N> > :
      boost::metaparse::v1::impl::string_iterator<S, N + 1>
    {};

    // prior
    template <class S>
    struct prior;

    template <class S, int N>
    struct prior<boost::metaparse::v1::impl::string_iterator<S, N> > :
      boost::metaparse::v1::impl::string_iterator<S, N - 1>
    {};

    // deref
    template <class S>
    struct deref;

    template <class S, int N>
    struct deref<boost::metaparse::v1::impl::string_iterator<S, N> > :
      boost::metaparse::v1::impl::at_c<S, N>
    {};

    // equal_to
    template <class A, class B>
    struct equal_to_impl;

    template <>
    struct equal_to_impl<
      boost::metaparse::v1::impl::string_iterator_tag,
      boost::metaparse::v1::impl::string_iterator_tag
    >
    {
      typedef equal_to_impl type;

      template <class A, class B>
      struct apply : is_same<typename A::type, typename B::type> {};
    };

    template <class T>
    struct equal_to_impl<boost::metaparse::v1::impl::string_iterator_tag, T>
    {
      typedef equal_to_impl type;
      
      template <class, class>
      struct apply : false_ {};
    };
    
    template <class T>
    struct equal_to_impl<T, boost::metaparse::v1::impl::string_iterator_tag> :
      equal_to_impl<boost::metaparse::v1::impl::string_iterator_tag, T>
    {};
  }
}

#endif


/* string_iterator.hpp
W3WUdn+OcGE87pujr5iOmUO7Z+aTamdPauBgiJt1hsunH6aMr6bZqDYghq0m5TQKBrczYPrFmY7deYrUlokI5NmJahnJkLzeAghtS40h4vdmMVnrDdClajr63yN7bgfZPsvVfyMhsZ0M077jUbpCFk2W/ooeU5sgX8E0pDqyHcQZTakrR0g5bKOsRAz9cvUEDHJchVXJqTCIyaCfj6nrRl+irOhxsBMcYPXKgDIJg0mlJFggn/p5WhDEa6xQId96G9bbA9qdHAuijqo1H0gbw27ANHIv2B9q/HpXuAQlQrIlgNRpLZeMnwb674r2F62KStJorPQ962mHfF2g67HcDX6BdM7eKaR6OoGwVeesXwvnOR6A/l+ZQ9WkQtt+yHf3ON3ZuQGpXi+RqtU9akTVga63I4vk3n3KbmXQ5Lo/IOSO+7Q22s2T+dIZpX3SSF2YA7+EDTB4uJNOLDMOMawk6RC11t0MWfr9INtQvXGpGR2RZytc3MuBPfaMxvO+hoFFBKP1oDfg1XXKTotV23VkDWrDKoBqHzfAqmw7U+Szh1V7f1KOu7T/HSVbRcve2AyweR+6fdmMfEGr4VJrnR36HkaF+ntAeKuHim+l7Mo0Ug5xtPZ8DAx654XVOCuk//281scTWiu/k7l73pPGs+/Bb5U2nlpaFdW6AjI8UeHu77Ca5g5xJembtQ7iswUAhWeRfavFaVNY+4GIj22FS2was2n4QQYlZzWw0d7ar7TEgy/TEa+LeyDfFgRfcw5i38kgcgus/UhZckvqbqoEWOeq9bYWxG3TnIbsxv4IdPkTsrwSttMZ6gYngY17BuLGMJ0fJmiZtlPnx2NSZvtpqMdQd/iJpJEQ4wdTFrCZah21ha/qCKL/XsoyfVHhoeiOCFgdpMxVTY7dBquojm7wO0yNFctpd8YBxDBXtR1TAL8d0Hz+nYaOL2BK/dyq86g/Ss+9iUYtnxjQVwdVg4IIfjRF81miVZ4O2J4Kv5rH6Pa940il28L5th2gqDo25zcQM4cyZJYj4VdwLGVl7MGGFvVkvgSSOirifgJDBVaIQZhAo/00Od5N80V0633IOovklQ1g/zMr+OlQavkH+uXZWWSe1x59s3wQ8sANE/aX3xnQe3lhcE413Asj+P0e1PAbBp2H2niQRN1o7VIjpqLMrgsQL/viDr/rMBiyijaM1kN88ylgT3M4+5tQo+R8ZDHXBL6vrht9imoe2+EyaAwK9i8DSTEbSOZepNrFVfAb+caS+RzPAMy65AS/IKoV9qRGRFtISg5GlmHhiNv6EXVHa/592QTWeSN1S0vS01Jhl8BdZc9opVRSNt9x7feHAG6yI/L7oGBNiRYTAHaliPNOA9F4HGBQUzgfnkTjU3fqvLShtW4pkk+sGnhTN0sqRNVheHrvB+GvageFNT9oynyeZCx7A906rkDwVV/QvEU9qk31B1G/JSn7r4z5jT5U69UUuu4nYHVWG+iecZA4qtrvHmy0ny9qf9bZEz4RRNUUrd8PZEtbs1xC3iKkiaaj4QLY0D8gQbuO2v9Wkm32xRp+MnvqfDQg3yHaMP+dyVpgOiTn52p9fAaR8ywkr26TKvYJfi5fSNU+CnbRPMCa1jBNkyxRsTRUeRxlPRbDKmwPdH1OAHZ81XrLoEtOZUKc87sN/Nqbwk8bQLBqtGxDG7mWkDV9of3+DXTfbbU+7M3ov3mIa5Os/fmsLfxuU3fzMmpMGeKOvtPs4edH9nQfsBNDoGs5i157NoCOveJFXznMlr5LYfppBXTjQmGweDQC7dWKT//mwHmknXp9aRqv4Ai/FmpyhBgEf4N4WSkQTb+QaiCLcVZDpoB1dbCf3CB+uwuwqQM=
*/