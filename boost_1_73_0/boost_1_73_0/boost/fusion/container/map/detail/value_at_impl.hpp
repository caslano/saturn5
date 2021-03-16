/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get_val(index()))
                type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
R1L9DO+jRl8+uJGot0LJI6n+hl+9ZTaWCiXqWih5JDXA8E+5RlSp7URFhZFHUgMNP9fURh+wp4DmYeSR1CCkSru+bpkF2TwqPYw8khpseL8xPzPjT6J2hJFHUimGn+tqwFX2eV0NI4+khhjeGjuf/fw+UcXCySOpoUh5Tzerj38XRVTrcPJIapjhCR983fR9osaFk0dSww1v+XOFTrF1m23h5JHUCMOvqNxT++Yh6kI4eSQ10vCWP/DrQDarDCs=
*/