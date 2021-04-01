/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09272006_0725)
#define BOOST_FUSION_IS_VIEW_IMPL_09272006_0725

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
0f1mBzfp04G0R3Nj92iBETv6OLbgfugBRGrD4Z2FyMBt8q/NCKfUexmidP/3Y8a1Dy97+9A0M+v6lAagsyIeP9wBh/H4hnLP73t+XYitKqOzSVjd4kFJ0nz/KPWuuy0dM/ipDwlpWH2gX1NTG50bcpoNDs9e/D54lwW3HKpwZCM4Qwtr13gooPg8jk7JSZcxunbUlEawMqkSXC3Jf1LWIYejsrn5yOjVWNoX1mCnJGhFIf+o2Mb24k1ZgebFrm5E3Enqx0wZrbuJolOMhdycxiF+uvfoiqMvmifMfNb721eusUtcrpFPniRiEmwTw4yiM61Ee7nESFWpv/sSJWSYVb5nCRCxOR91NtI4fu97rFWV6raB0U0GoaaXZy0RlUImfmKK5qk51AmoC3Hv//A2ezPHurXcNpoXmlaknIxkBaxamISu5O5YfOqifJDgHcPTSTXAhPOf+la4bKNYl+2lnONp/RLB8BcCPXJ04/O9QSuK1h51Qk2F+Xc+eGHiVoEa3nhMjDAkx4lY6TtLbsSeM4QKEeYPXEP+8ZkIqStOwsFTS5p+73biSbIKAw==
*/