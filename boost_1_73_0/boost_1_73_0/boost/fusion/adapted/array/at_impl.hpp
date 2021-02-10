/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template<>
    struct at_impl<po_array_tag>
    {
        template<typename Seq, typename N>
        struct apply
        {
            typedef typename
                add_reference<typename remove_extent<Seq>::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return seq[N::value];
            }
        };
    };
}}}

#endif

/* at_impl.hpp
+A6qPjx53Sfr8C6ve1izXknHdWiek+QddHMTpPnrG+d5Yh5ppfXs/IeyWtX8utCwNlyH7YODfdiEna3tPRe+sJKjgEhjucD62oXDzK78WrC7O0/hZxdQAxPeC8C44AqUzPUtqxHoWfAUS4UZMAUZqrTmC5rwEnSBkHOBMAynV8HkNxduC54WHc5KNqAK2YgMCnaDUGOK/KaFqVitQeaEQPgZV5owG81l6RE9gsZ6qToYEwQTSgK7YVywBdExDYXWlfq530+bWtBO+plMVT99SIVX6OV3u7qiaJZsBbLSoCU0Cl0w9i4sZcZzM1KKaLFqFoKrwn0KiwjLrC9rUChEB0euHFW7BYSoy5ZrLKGi6Lk2g5KlMmy3hVy+MKS0dkB5U5dER2khu0xS4l1oygxra28T8cDSZdmm/I2SPcWegSwpKuj5EQRRDxZMceXCZRCfhOcxXPqzmT+JryA8Bn9y1eGdBpMvpA1OrDXgXVWjoihq4MtKcMxekP/QTne8+ASG57NxOI2T+DieJkfj0yj4YwS70Ns+gN+b0mh70IOe4AtTfNjzdve8LVowswSZWiUKtSkz3aQoRaDRCUz8s5HzKvJ8E8wcFkKm30Dxv9A6RFeTcBoFkfMTL1PRZAiHhqFVXPHZsWCppPXvidfM
*/