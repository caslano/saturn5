/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM)
#define BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/container/vector.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::deref<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_of_impl.hpp
dkXoMCduBBg2ku761EhbpGQmtxSrehErnX0GFQCq3Aq2QjYaI2OWx83Ppld5PV+VVN+p2j3ohGQflbg1/uaVys7nkSnfsAoXd/XBL7l/sc+qcBKe6DU7zKvGsZaQv6GfMH1qHL+95P9PDXa7yS3kAFA9dSX0FwrNpFvRp6OZYK85vyRguTfAWaa81+juBh85XVu0ftc/FsX3ZBltz+/+8zABOGqFfF5umLOFej2O8SBlZhzOWgmg7EeXB3CZ36bnHQsidnOfs44CYK7z5/5fWturq7RIr+82ZCBrbW73bnaPMxd5blZKk0glSm8xin2ORaqnrhXB+RuZxB5s6jrCyajOZ/39HHz5YgZgvsn2V8oZ6vyLNqdRb5xr3eLAwsuhnUo+z3NpbiZWfsiWB6JkaLehomHnRLLDW3GveemrqIX7QjfCd88hSTOuT/8u6xK60aB5FloUNdeOzqtAytO9aBE65iTiSyZemYcZuQXn4OcPWVJ3/UaH7URRXD1u3I7jRSKTmVF8Gx48Gx5nxDNOsZt8DYLwlakbKMcd9/JN+uf3Fa/7nrqis48JxLjIPhl7UUItXuAZVBI4zhlWr2qMXd+cWWO4mp0lXAoo4mLrgH/8O/swHT7NnOPIXrRh0UHlfRk30q9o3IXz3U75/Y4F2vB27N83NHXQKId98L3RLM8DgEr0qcTY3pgDUj9OZ1NHh214gjauNSftQD3O
*/