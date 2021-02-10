/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<reverse_view_iterator_tag>
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
gg5VB8CTcli9tYCxHCFstshNSMsC50kaVm9HuPQ0RqSFBlqQuqkLemnrBIejzr8RAphQohSoEiViuUovhBeYBEgqb9fgm9Klmazg5AzOfD34dkTBcqVMxqlxlKI0do6s4cxM6rvQfhqbGG7UPYm9KhC16V+gPOy79aCZxCb3cPRiLAn2BIsP7cSCGEJYM6ul70bMRctzyXh0daMW6Ckqt53rRYlEhTeyH8ocg1gU+mqR53k0itWGSzdy2C5VCPeUkhzp8uKNcIiy6VMls+8RlFeArMVVVWr+kiu4PePEQdsjsknbF4JsG7a3PTTXfliuLGam1r5bYCvE27sTcrC36RV+s3hron5th5ApwfUbRNkMD1CG30S4IWRd/s/gI5W7aPYtGS0GsdBkYeUI2uw+myU6uGLn0joKAjASbzpdC3aQbp0ZbTXsOBC2z4IN7pzHj8Cmi0SLF+87uHq+JyX0RCE+11STzmpOi4dly9lyZBtzM5DKyojecy1pWebUUJYHIMF29oXGb9Jwrm39bKI2/B9QSwMECgAAAAgALWdKUmMy/nWyBgAAWxQAABYACQBjdXJsLW1hc3Rlci9saWIvaG1hYy5jVVQFAAG2SCRgrVd5b9s2FP/fn+ItBQbZVuLEW4c1SYt5TtMEaQ7k
*/