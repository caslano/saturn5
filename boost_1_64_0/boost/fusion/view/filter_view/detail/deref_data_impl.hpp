/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
hxdi6T2jeQp9uH+Ni9iFgxTj2P9OaAg4g8bHm3srwEDGlCNphzaQcyA5nAjn6ON2IXgyoCA7Tc27R7YSWVn3sHqNgk/Ha4GzzC9LzXH+eF+ACy2I/zoBz7cqJE23AkW7XN3qPAloHjMdEwRvSwKeV1CV5/ZJjQ/u5XxE2CgZjzJhL4O4p//bAy5f1+lhLShC/E+q00MXdWSoytPRCmZI+Q8Q/DEFVeom4L5xgMsp71wbEVOfs4TL7te0YiYFnfjLrNQrvzddVhvNhGnaCednYCpVZRstmchAXTecYL982rzXRjqXzzTBrOstI9kIkutwYjK0KKb0dhqQ9DxHnuzA1psfteCkjeNR3yENP9tktNZgSDn7v8KNBpI58YYfpylEUWOHYWQAz81X9r8t+C6IWRO3ELFDFH56nFHOGhNgJ88TWZE+Dn2wOBcGh30SDiXuBbKlmgnMY+9U01LN7FPtsZo+kJH6PmasTE8JnDLt9xrlFetwq0Soe7XCom9WI7A9s3y/zo/PhHCQd2D2iYTWKVbUVogkSotlP3G4JjsdmS8ekJupOkpOPwcx1w==
*/