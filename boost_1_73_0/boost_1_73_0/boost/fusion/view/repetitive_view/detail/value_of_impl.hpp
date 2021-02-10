/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_VALUE_OF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_VALUE_OF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
                : result_of::value_of<typename Iterator::pos_type>
            { };
        };
    }
}}

#endif


/* value_of_impl.hpp
Xs0SVcZBIw0ulUajrIBSJgnxQjolSyO2hFOrnoCmQY4SK01fZZaWtNRVnC1aE1GPxGVeFSkuhHrASVGGag6gSiNZ8GTeuVvC6pQVvNE0jbwRZCkKAzsvTuHkdAdmolRlAH+enL15//EM/nzx4cOLd2ef4P3v8OLdJ2L295N3L9H0ChcrQF7nhSxx8QLUIk+UjOyaP+4a9XoPVRomVSRhh6w3LaWu8v14x3txRC+MbePnPkEsypimNiMJmky3h5jrQi6yYslsR7vsUYkoNdSz2GOtb87kM0DBGg5IHMlZdc7kpRZahXCZqahH609lIhcy1dNIZ0WfhmEXnaoIwNzb14Pev3sAaJgKUeaYRCJi2I1hAv314QE5ZjHuIHHrIecu0ub1AOztuIds1Lwv957nuhgACQIQ7z1nie3omAfNA/J99/HtWxq6JVocvZDLaSJTfHPA7OaFlH2JVLes0JNUaSUS9Q2jQQBvwQhWFeyn8AGtWqRwSA4piyJD9RyQr85VWjvyrxVy0bLUz+DwbweP14ee9MguKtW9ZrsKJ3ToLw56K1CJZFAmmS7X3jCfeZWGBDcQ093anDBb5M0cehKFQPWtTWwkI+0CfRjTowEe8PpwcwMPeBW+a3jh4wOeby1UWJ2NATU8R7RDZZIC
*/