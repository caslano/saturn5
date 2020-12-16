/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_1142)
#define FUSION_GREATER_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) > extension::as_const(*b) ||
                (!(extension::as_const(*b) > extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* greater.hpp
2svvZI4BHpC7HgQYGXTUp74ZKp3F1VJOsDqRHoQeLG1ninJsGxtPFjT3N+79vYU5qTWZDU0znvm++ecmHLlozPenZy4IvGb+ZLVU5g8It6kthIe3/bl4zB/xMwJP39+J/thefC/fi2z+GT+E11gX4c32CbzR4cF/Ke/vEm/tv+C9/KaE11gv7TM3q/CePwfv4RLvwn7gNcUa4Xsclfv3/4S/s0nl7t58Pp7W/et9dvEWc/GtWBkXBe7/GB9l6ZbA/R/io7zJxmP79v5bAf4/vGG81cazeDp4a4EzNzmQtpV4HL/bwOG8Db/L/9evmr0HdfWcpzWN9yB8txOpmfLODwSOOENsHP2+9iiW6wtvhN0cW5cIukmpsOjN7B+mbS4ClyMNX1HteZbf5CWz3MekbghdCEJ0Uhrdus315UdxW6t2iEcdpDgR6jh3KnwctGEX+cyxOoIojty4EG+D27NzOGysXC9XeR2dIEaMPQTvgylN4Z5YeVoTX9dNGpG+MMZLcJA4UNSXkX+pHoOmxc9BhPDHQ1KRCZrtM6vHDh8mIt2WxUezt5cY+SvaYVuQrGXLhK/bctDERyhrWPTkftgTBLtHlpaUVp6/bz2av28hFVnYhttjWctI5CjY2jY6bj+9bz2ax/du4wE0ycs+GK6NCt7dWHaUh4TVJ+75SFyDhGKCcGc8gv3c5onhdGtne3UY16JOf4P8QB/NYxG6mesm3bJjRgVrZSumODGc35548wtSv+z/4dmRSEk8XKO0XK0Z5f7j49b1Mji4dlKnIUWmQ37LtXGAr0CRwvy8ITWWo2IiXLxR0NBSkCKAtrFdPCLgNCsNlArni/DNOF/i8FTY60AxY8l872gdh2SI8j1hCy0Qp+HWmf7zt0Zr5bdnQN+Jk0p9o3uMg70kXjB54vYhlyw42YdQnAUOlzmaJfx8CbdTqZt3qeuEY7ZHw9f2WHBm4/IVC85jgX1vrwVf2yG4sMc14dQHJBt9xIJXvoG0UZBMIN4imnHluUN1Fjcz8ex+/YoF53Y3B/db8CnxNOY8XWnG1XcT4Ml7JfBo/opO1PY2t2AwGkOi1XDZGA1buSWDsbG7VMLEbDXnkO4H/1YKTvwz+JVG+DLVPbm1glP9RLv3NgKGVTGn7pcTnNdN9LcleGPdryQ41a1zzt3I72NeD4avbbyyz8/dR7LIqRv5e3uMbB9uHgX/ryyi7iafKfVzdsW0qRhz6ZeC9wUbt343OXkTiWeXqeX2eTjybkL3gAXglWNo4/J7CfBEf8/Fk35yeyq85/83vL3As3wSSWAlOfOyhWf7Lh7ZB5z/wXfxKw14UugmnOSmFo7l3/gDidP8zgfYzSy4JRt/r8RpTijJYr49ksdFyAoPiT5D58njKZJcidN/zdIpXHv4PhYHQuQ7COAtt2PTkJxz/mHs/O+CJWTYiZ3e8Jyw1NucIGjkiOyKtO/On826cgdynut2k8iBJr5ORef/W8264IKTd2JPBNLwXLsqij1h0ogg0xlSLuUBaGzmKLfew2o5kgIvQG69wnHPwGZtJDNYeOuwy5M9ov2ZDjxiH/dvQ3JWNCxxBppWUlKfkIxt1psgrWLSgWFb6sARbgifOjKbUfhLqMvAz5AxMovhdjUlfG6bfpW1CxeExEPGtw6MHiHYyVblZ/ADckNj9S/VNkfWR7kmO10vxyVgVZHnZzQpzxkJ4ZvbUcH+JfKzLjZZI//K0QiK/prdFqvTRacgJU8GRdeqpiMqY15eeGQtR1dSBEhS14Md/+bW81FViLHHIJ5IajmLH8HmZRvXll6BQD7bJZkgIpJDNOYPr/mwdXEJ6aSQoJHhf4SUZqjuqaPZ+tr24AWyY1w=
*/