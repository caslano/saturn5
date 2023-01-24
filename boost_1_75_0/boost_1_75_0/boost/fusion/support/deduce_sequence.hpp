/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/deduce.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/config.hpp>


namespace boost { namespace fusion { namespace traits
{
    template <class Sequence> struct deduce_sequence;

    namespace detail
    {
        struct deducer
        {
            template <typename Sig>
            struct result;

            template <class Self, typename T>
            struct result< Self(T) >
                : fusion::traits::deduce<T>
            { };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename T>
            BOOST_FUSION_GPU_ENABLED
            typename result< deducer(T) >::type
            operator()(T&&) const;
#endif
        };
    }

    template <class Sequence>
    struct deduce_sequence
        : result_of::as_vector<
            fusion::transform_view<Sequence, detail::deducer> >
    { };

}}}

#endif


/* deduce_sequence.hpp
iwySkTfTMGvi7s63ZaPw/qGym5dl8NpClRebA7S8oOwQ7N1JfXOLl+PzKtp1x40a2texwUu77rhEQ9sdUzTPRzhyMgtd9hnYVRPLx7P1JpbmFnm77CzmJC3K1P6Q3E+KOaW0m9rNssx9tK5b7+VZmWTcC6Qy6xUmhAyRFfI2JwwVckm1kAeWVhhYemFgybaw76BIF8MxO6Q6mVGD1OPKqcynjysaAZpoLObe2fF0Aaocu2BCk05eVJ27WSIK+Sn/6qVz1Wew1I+XlD6mTY8/YZdG3/B0+6yH8uw/4rMBwkH5Wad9szTivlMJejqzcnE9vaekp+/9RfTqlt6aNPUqzUVN/a9zXFNXxcP01a7u42H6PmI53UyM5WO9WNh6wd8VTcWyQIpl7DmdZUdF/zUxPH233Wy/sKt7sdF8JMF9tHZdS2MieDa0idR1H7POUrpamzSxtefQtuJFbvKK0Qmmo9XsnjDaNlvVfbT6K6Q2U+vR+7cWM1pzt0mPNR2tc8WZmJN4uY88Qq8ZKzNroxWEnR8VryVDZJrYUxPuPmY+j2LnDO6Xo/MHkjuhI3NnSe5YcktfknFEkdsiLXeFkztN8rd3VNbTTneh+Rg7I0j+7HIOPzwjuX07uj12e984R3O2GFQxZoNdGt6RZ4bdG91xt0HLSFmt6j45lwvS33nH+YL0MKHVFLcXpJu7sWP5ZrPC02k9xbDV2dzHrG7P
*/