/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_NEXT_IMPL_05052005_0331)
#define BOOST_FUSION_SINGLE_VIEW_NEXT_IMPL_05052005_0331

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/next.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::next<typename Iterator::position>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    // Workaround for ICE on GCC 4.0.0.
                    // see https://svn.boost.org/trac/boost/ticket/5808
                    typedef typename type::position position;
                    BOOST_STATIC_ASSERT((position::value < 2));
                    return type(i.view);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
TpOLVkFzDcGkpwzt2VSZ2noTHPVC1ytRS5sCafarlEa9ANYZi1FXPwhIHzMrtkqjaaAXeCElHmtaW8kISkkxKwUCwaFehokVNdNUUU+ThJ1V2QU8EU/NlCeFAgbjEkynOsI/gOuwGsD/CcVdyQ0aoembxFGZqH60HiDvVVwT+txZRwBiuJYD3TZUXhNt57fBs7PeeSAoHwBMH5xr98Hz20AU7R3F6xgWS0XWKoksDRG1XFB5KVpZk6sByV1qQKNOjRQ+EIfoc72SKMbwdEoJikbFMldv50E6jhYpWotRwG1VfZbsRI0F216iIbMKg2A2W0b6HxUjxfU7LzTpwREZ5QN0f7Xtnvg7KBgy+TXvqHXqQyPWgACsSVpjiAnMUTIFI22NXEnUa5hDoxXJxE7a44YazJ59AgCt20Xi0tNn99QnR9GGzk0vlcN+A0G/kH9qzWd7ay7C+uqYdvdjeyYrGIioFT13aZ1S1AP5FwUAQzh49HqCAWmaSRiIzh4HAjUmSau4QFeUAgtCSU+MwkSK1/tHl+fDi9PjX4YejmomSN7epkKviD7R4QAjV+daGjda07rXArsaIy+O0zKeIXe8jWCfym+A5gRlW6DrHB6Su58kZ2X8ChRqMLy9lKASVDUjAgjbkSzR5c77bliT
*/