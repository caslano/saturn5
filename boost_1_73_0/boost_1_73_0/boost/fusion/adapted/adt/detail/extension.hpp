/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_DETAIL_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_ADT_DETAIL_EXTENSION_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/as_const.hpp>
#include <boost/fusion/adapted/struct/detail/extension.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename T, typename Dummy>
        struct get_identity
          : remove_const<typename remove_reference<T>::type>
        {};
    }

    namespace extension
    {
        // Overload as_const() to unwrap adt_attribute_proxy.
        template <typename T, int N, bool Const>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename adt_attribute_proxy<T, N, Const>::type as_const(const adt_attribute_proxy<T, N, Const>& proxy)
        {
            return proxy.get();
        }
    }
}}

#endif

/* extension.hpp
zDD0rlIvvBw6EFNqIB1LllR4T0Su3eHyUbgCpNPn/8VdBIkVLoLACGbzKImmURBbPVYLve/ut1ngWU5dWF05TM+cPCkWq5kaIamsGGnhGP62XuW+T+IT3m7zOXmikJKmoXU+0vHYMEhMqicbdbC/Pxi/BervELeIvflJwfmKiA72n67Sgl034YGoroC4D+kdwRmlTsbXk3fhn3fjNkiDFDgJT4nChaaL3rH03HRWUVK3zYurLsVCUJqSqhrtbP9jOQUz9XEvXT9wP/uBnywtt+L1TdeqT0o495LFPIRLN1h41pwqXJjShO+l0QWwotfVa69vOpp3i7hTWoQXYXQVpl2OGlBz1fXQIPY8cIM4whXxef7IyXmSzM4998ybw2B0OEZ+H6/+XESJt5Va/wJQSwMECgAAAAgALWdKUnV5JGggBAAAyAgAADQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RGVFBfQkxLU0laRS4zVVQFAAG2SCRgrVVtU+M2EP7uX7GTfgHGOLzkDujRm5pcKC4hzsQGjk5mPIq9xuoplseSgbT0v3clm7crHfhwzjiy5N3nWe0+K3vzHmz8sMvxDBy8eSX2Tuii8cFpWss/MdWvOyTJPbQ/cpzT
*/