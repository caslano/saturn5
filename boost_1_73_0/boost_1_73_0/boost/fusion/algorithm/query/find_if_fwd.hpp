/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

// Forward declaration of find_if algorithm
namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if;
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq);

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq);
}}

#endif

/* find_if_fwd.hpp
odorXADiAhDPSyLAS2VsYrPcl6E/4Cb/8kDlgXpJqU/GnRid8sE3gFg2KPIa7qD/G6nv9zD/UVr3SGNJr6aaSLOyjAVBkleBMqaLl8Zuo85yfVXbCz/zmUht0r3PQfuPpjqr54vZx0hB5gtpbnbQfVuWlt+4ZzbAAFgfEH1A/EUeidgxJEtJJ7zw8yEWAEFeausVT3ufkYPnpE26XQ7aB4wz1cYD6h3mviD6gvjMUvfnKsSFIC4E8ZUk+npZX94=
*/