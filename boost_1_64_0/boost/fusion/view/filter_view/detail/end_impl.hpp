/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_0906)
#define FUSION_END_IMPL_05062005_0906

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category,last_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
9Z85ni89+SaTcDltGnN+1ubo5QHSKQ+2OZvDk/CL86XvdAwfOqXthZETiso2qOm366LJtUMRhEUYBHYpqArtNMrdKA+oqaSiy1P41hu1v2HysSii2LYTi8nXrzZU0/QqBtizz10y5QOR5KVb2K7H5Nd58vBhyGQtkft+4Xq+b8rCqN3wPy6YnCsiTz4JmWVMrro22PKvdsKUfZif505pUdIw6qkFVjV/jfHTwnUiz3UEjH00Hz6jG2VKgjQt4ywSjalbLSd0Oq8z5VKRFkFWho7MmL4Dym2kznF+EXlxkQax5qPW4EvT5OciCtPES0pNJ0U03nyDHpoyR1PPtd3Yz0RlKFj7Ssfb9CY3E5njZ6GbxcKwKmzF/2MWvxe6rnxTT1SDVx0/fJw32twtLTcObVu0ly9oc/jR52VP3Zg0PMqEuZNUCyG9ue9yvY6ioAxJO8VE00Lub/DeTNanvKalbxeBaJvXQIHgy9WUzUSY5nYSlo4wZgnwO4g3iLUMfOdlSR5QphvTt+a7koOGnBfmNrVAKBrTLS0Hn8FMLhSe74V2Rso3eWqF9oAPTiafijh240J6K9t7atb2wdnIu+P5ZRT6keDTKS3YxVsMTM4WTkF6mqRuQ073hi78BptyD3P9JE7K0BIwUNZ+huGv7Hs8ncSy8iD3HNGYCtSCyN8hLYdyRYljZZZofFZ1ueB/k8klIksTK6dRQez52W68w8HkfZGHReClDtJln/OGD9szjTxnvuvGQaJl8Zlv6t/rmJwjIiuJ4zBxRevzz8eyD5pypShj16KS2oLPDLnvvy+xtGIR5LkXJG4s9ppONr5zl5m8J0IniPPYDcWEoyxdTow/JMv8M3tO4mVIGtpG1GfgHY/vm/oWuZajTvxxyKu/H3osvYXJP5rRV9C27VzyMbhh3D1kch/qp1SOxFOthRkG6nre5BYiCFLH9ajPMwvnSgR5FyzvpMFeVLgCdvkt/7+lyc9JfVLXs0jCXP3XQs/QZXgaL4OfWbHjq0R26XSPl2HA43cjmqNkvi/ocOHIsYWN0bEF+tuDG/6FTZlSOEEeB0VeiJM0ni2M7dxRFrwZ8v3GWOynWSHHxsqq7NjCaHub0tzeOs3TO8/Tsx27tGmuKuRubC00JPsFJAifs99vzN9i+RS7L1aI26esyq3LYwt0tZHsYEnZdjd2h63v42/MODJhp36cOk4o5Fd+4eR1xxbk7LWSWsC7ITy/JX0cvYQYyh0JXQ+kNHd2tjFu7/r6vPAHhpxU0MRSL/4I9RGnDEuD3Wq/iNKu60w+pNToj4ssHkfEruemeegI2nLdpRbd2h7JdlrdXcHb+3jXpfwBr+vQ8ks79EmUNoHXKQ/0HOPp0VrbT/UPeF8oEhrnsnIsZ3QGLXOmIRM6bhlHRlpGl8BbNaZMLnI3jmwnF6pIPZKgj+KOntlifmfKpII6aRT7XiC2SHEwIDba/UumTCYKmjU4XlkoGfr87krr6eZ649IPGvOijCrBiUIxoNuVcsK9QDeTtZb3dnR1jHTdX+F1HzklJemWYkDZHNbNRlHpz9NpzMd+yMffonRyLw4coVLa7G1Rous0/1MOdGoV9/V4x2RzQYOFG1l2aMqSW8nB9k5vh/76LHJMI41/VSz67PZhd6Ax4bbqrmyOq7S1ffbDCSvpBxiu0Rpvs9HPs4x7tDmu0RpvFH6nsRcQZ3mZX/2V62orgO8F7Nb3elRe6vuShy6adq6ra+pC5OGj9I7qmLO4F+f0mFPuxXnmmLPW4KhLk2Q2aqZ1dg+Omdab9uCYaZ2fxCETVDOti3twzLQu78WhtG5X7wkf/JrksLoD9romdrrCHkLYny9yTMe5IOP8usQ=
*/