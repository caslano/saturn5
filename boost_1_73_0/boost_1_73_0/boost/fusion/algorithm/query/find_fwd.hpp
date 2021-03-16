/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find;
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq);

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq);
}}

#endif

/* find_fwd.hpp
RLxlS7hAuEDstSUSQCSAeN+WSASRCGK/hShQCDcIN4hPLcQAhUgCkQTisIVQrwEPCA+IY7ZEMohkEKdtz8MLwgsiIc3uPFJApIDwSiLO/Qt1hS4VZCrI83okowqZBjINZLZxlNpot04hfCB8IHpLQmnZ1LXWdBDpIPINQqv96t1TPwg/iIsteafWswCIAIjBtkQGiAwQxZKIGXNcrlCZoDJBXWFJJ0dNB1dyBq7k0bZEJohMEONsiSwQWSAm2RI=
*/