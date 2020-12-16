/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
4KWX5PhjIjQu+3/xMCcKjFxXBOdxvt1RnM4X7eqJ0LTq9mpZLtcSku81HAJBpL+k5FZPZyFqH+wxTBUysLezWN5capbqoKEGTpqlO2jQwVzOZTppXLJ12Q481Szls1wHDbV10izfQYNOhTA/aFb4FQ3sGoPERrHMKwZ0RhtFfqVIXo9PK0fyenxaRfKZxFLB9r9qiNPtPxHidJqrKS5bSK8Obw8oVRuyjSeDXLmtuFSAw5Iwlw5w2DHYxt4ApzsG8atH8W0UYH9dI8jz2JAJ4NwOkFszyHm6PGuFOH95+kK8Kg+m3R/guTNhWbOSy67T14cOInzAxLGaCB80cTIA81ibcbndvQRrU1t8Xsr5Od/5Ne/n1Pm14MdFTtgX1lF4spBWI3A2le7VbXTdKI1oNMyvF8mX25JfP4rHUhO/QSTvqvraMIoXFjC/URSPFU62D0l+MFlYn/JF2zc2cWx0JQdecDJSKY56sh1tEtAwjfnaIa5WZRr5TUN83S0b8Yt+ngYW4rHcwyaP9lK5Sz7ciyx3OaTR+Tp+LlTuET8fKvdokNflxvJtpnioCNzJblY55eF20MixfvMOvNnHtwhp9NhYCXF6bKyGOD021sJca9uGg/VRl1xe2K3bb0Phsh6LjQa+nofS3NLPy7pArhnkcKE6peuFOKBg832Lx5SWj9f9oe3DPaM8xG+leHjdhXhZDE9UpV+3DvF6vNpGcwVzfrutxLmayHWw/53b7HaRfKniFGtqnNg+SiPsZn4HP4+xm8YYu2OQrzbQnp2CeL2hrlV29nPsJUpvlyDXpvR2VXh4nr6bnxOl76JEaV6xe5DHa7GRIrzVyR7Pov1+K8JvWd7bL/4dH36CGwfvEcQhDnGIQxziEIc4xCEOcYhDHOIQh39zmNCKQxziEIc4xCEOcYhDHOIQhzjEIQ7/9VAtelvIdQl7BNYJVOCd4q3NaI3BnpEcLXiaHvi9/LxaR7q3H+clkZTmPlGc7WxjMb9vBx5ep4h57ufnRWEwz/3DeJdM84AwZw9va2czKVorcWCI12slpK8WBt1Bv6ETi42lXw/2a8XSvXUKvcsid0iQ27ah1nUcGsGZa5EOk3xh6e7gOs3DQ5xei3REiNNrkY5UnLkul+r4KMnJxbiMHy1xvQAX8WN8eNkdGSH9sT5cr6U5zofrfI83cVFUxk8wcWodiJ/owz21luckiQcW1cr1tyebvKilUafmNOETH9s5ZfFBNlmeU1iH35URK34YP9WHa7tOM3BcW8T5nR7EbdG+66WW06KC8TqmMwI6n4bzPtOn0euyzvLhDfzynrNlG7Zb0Pqys328Xr94ThDvpjKf68c7lvm8kC6sOd+nadd8pWPNBawRL/oXXwhK9IXX9V0Y0vjX9V3UgSc3kV0XhzS6s1KhqX9conSFpO4GxF1qcLorUBkvC3HVBn7lz6Yx6/IAj/ZxXVwR4ORa5CsDuDk2XBXgzH0XVwc4c53yNT4uvPb8Ws33LmtUhcz3ujCv9htcH+L0fo8bJLduJp/xr95E/sYAH1zTflOAD45rNzMvlgfi0tJqvdyuUNq3GJz4OstwxWGa/H+r5Idr7EbCb1N4e4QJTO92xqn+oYPAd4rclthHVca2dofiYZdUK0LF6d9p+d9NLPd23WXiIw3E7lYY7NjyWojdozC9nv5exnhsg/xqUIoR5O4LcVstIce8+xUnuvLw5k6JxtoHJO72lM0yPmjg8nz9kBV4LzKX6eEgLhJi7pEQN6JsedTk2HBZ3sf8XLvBcR734c42WAzmnghw5l6DJwOcsEvGeyrAiVYny/G0j9PnhGdMXCTGaT0bxA1fPBfitC+e93E1mIoIAeX1go8=
*/