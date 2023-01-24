/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_20060124_2147)
#define FUSION_VALUE_OF_IMPL_20060124_2147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config.hpp>

namespace boost { namespace fusion
{
    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_value_of
        {
            template<typename T>
            struct result;

            template<typename It>
            struct result<poly_value_of(It)>
                : mpl::eval_if<is_same<It, unused_type>,
                               mpl::identity<unused_type>,
                               result_of::value_of<It> >
            {};

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename It>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_value_of(It)>::type
            operator()(It&&) const;
#endif
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename result_of::transform<
                    typename Iterator::iterators,
                    detail::poly_value_of>::type values;

                typedef typename result_of::as_vector<values>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
8lF3w/KAzynD8yuGLCvkbgmkppONKk0+X2gMIlW66MhPMouS/aUTmBwSeGA6XclvUy/Ysvwfe0TtvJYHAD/np4uPQGM3ynHZF3C9uw/zr226PeZLbeRFMT25vsjXBT26QxhbYT5zM10Qz3gmK70vROdMR8vvLxjmPdz1i3ffyn+hk9URFPkmTh11argb8/0FHFx1WJRPF1URkBBEQNolRUJpkVwpEZZupKUERLoXlhAQBKRLGgnpbnZBpJulu7tzi92P3/f3OzN35t6555z73GfeSqLIn750UlFld1qNbUZWmv7GioRNo/35rCfCVMa5JT0aJ3jAFGVBRqPO5kFOUT+kLf0WviYcfmJB4paUgXZ4EaF/G4Jdd3JXnE75qj6jr46x4/CvV8J1fjHD5+W5tPVKA//4iqayoXaGbEwFOM8D+wNOGZ0F0kMbxNbNPnGeH414ufKBMqW9Qy5uC06eko0qXOdDtm7LW3yy3YG7vGwfF6+wLfzSQ0LBq/k50o8j70+qF4ncfGm//Q486z0LOr6QM5qIy26DhUi+8G4sLsoAJx9vih8x7DaacD7j/bAMUVtuHI94GcMpfpGwstDGinLqnEuwkE5bMr/g4PyMpQFDNkAy7ldzvrqTLXQFrr/cO1JPbJKkDTxW3gnGqv5lYM132/Yy2sMYYkmkdHpKXCCd87Hl5WSwFV5nMYBk1NhuoDIST+hsGX0zmID2
*/