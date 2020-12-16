/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_FACADE_09252006_1011)
#define FUSION_ITERATOR_FACADE_09252006_1011

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/iterator/detail/advance.hpp>
#include <boost/fusion/iterator/detail/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    template <typename Derived, typename Category>
    struct iterator_facade : iterator_base<Derived>
    {
        typedef iterator_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;

        // default implementation
        template <typename I1, typename I2>
        struct equal_to // default implementation
            : is_same<
                typename I1::derived_type
              , typename I2::derived_type
            >
        {};

        // default implementation
        template <typename Iterator, typename N>
        struct advance :
            mpl::if_c<
                (N::value > 0)
              , advance_detail::forward<Iterator, N::value>
              , advance_detail::backward<Iterator, N::value>
            >::type
        {
            BOOST_MPL_ASSERT_NOT((traits::is_random_access<Iterator>));
        };

        // default implementation
        template <typename First, typename Last>
        struct distance :
            distance_detail::linear_distance<First, Last>
        {};
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Derived, typename Category>
    struct iterator_traits< ::boost::fusion::iterator_facade<Derived, Category> >
    { };
}
#endif

#endif

/* iterator_facade.hpp
1NlzuXpjknlas9qYcao0f0o9MMI0dZo+7TikGaVCuEKdc5ABJpijcci2pBlhmkWSV4p3+hhjhoarpM9h8swQv1q9M8gEizQPa1sGKVIndY0YIUeZyGcci17yzNP6WXHHJGHEPnQxTJnI59QHafLMEr1W/ulnigWar7Mfw5RYIpWTJwaYInK9/ehninCD9qKfaRpuFH/0M0Vk1Pb0MsYcLTfJL5Ms0X6ztmWSOi23yCt5aiTz8kWOWeKf1x4MUyH2BXXOAJMs0fpFx2CMeVrGpEmBeZq/pF4ZZY6WW8UcY1Rp/LL4YIAiS7QWHJMRSkRuk3e6yVEi3K6uyTBGjfhXHIsBplhkcFxemSfxVe+TY5o68a85Nt0MM80iya/blgEmmaNxQh3TQ44Si7R8QxnJUmSOxDfFHTlqNN+hLhlgikVSk47FGDPE7pQmg0yzSPu3bEOeWRLfdhwGmGCOeFEs0EueKtHveI0+asTvkh8yjDNH093ihwnmSUxJnwEmSX5XWgxSZIHm74kRRqmS+L6yk6dGctr+v4qEDo+9jFKl6R7HZoAi4QfamcMMMUWd5A/1AwaZJpS0Mz3kmCXyI3VHN8Ms0vJj+zHABDViP1FmMkwwT7Isv2SZYonUT+3LMNMs0nyv1xhimnCf/JJmjDmSFfXDENMs0voz2zBGjfj9YoY+Jpgj/oC6YJASsRn5pI88dRIP2oYBplig+efyxAglwkPOCXSTo0xkVszQyzgLtD4sT4xRJf4L/ZgBpgi/VMf0Mk6dlqq2IccMsV/JIwNMsUTbr7ULBeZp/o3YIEeVRE1dk2OW+CPSZZBpwm/llT7Gmaf5UccgxyxNc+qYIco0PGYfehmnTsvv7EOOGRp/Lx0GKRGd1xfIMMkCrX9wDCao0/JHeSXHDNE/SYc0BeZI1tU/w8zQ+Gd1Qj9TRP5iH/ooskDL4+qIAnMkFxyDLCWif5U3+imyRNsT2pQ8NRJ/sw8jzBBfFBtkqRD9uxijn0nmafqHeqOfAnMk/6lNGaNGckk9MUyJ8C/1wmFGKBP5t/zQTY4KDf/xGocZZpoQ3AMhTZ4KDSu8RhfDVGl6kntGDFJkkbaV7vmQZ5amiG3IMkVklW3oZZQySzQf4Z4PGcaYIf5k943oYZR54g3u+5AmR5lwpHtSdJKlSJ3EUdImQ4EqsaPd2yJNjjIhan86yVKkTmK1/clQoErsKfYnTY4yYY396SRLkTqJmP3JUKBKbK39SZOjTFinTAxQIrZeXTDMLIlG9U6eeZo2uHfHICUiG93/IsMYNfZvUt+0xdUfBeZp3uxY5JglvkVaZCnRsFX+6GOCBVJN7o+Rp0Zim/t7DFMhtl16DDBF2OFeGr2MMkc8oX4YpERspzLQzySRXcpAmhGmiO/2nByLJJLqk37GqdH4VK+RoUCVpqfJDxkKzNP0dNuRYZJFEs3KQZ4u34ud9Zh4hnzQzzhzxI7RPvQySY3kM9UZdbpalIsSkWNtSzd5aiSeJR36Sfh+XtHjAs3P9jpDTBNJaS/6KDBH4jm2YYgidZLP1Wb0M06NluNsR54ZOlrVIyVafEZymGEiJ8gfPVSIPU97080IMzS0uadNFyOUSD1f+5GlxBJtJzoueWZofIFj0884dRJ77McAZRbZ+0LpM8ki7S/ynEnqdL/Y/syRarc/eWZIvETZGGaaxpfanwEmibxM7DFB2Ksc9FFgkdRJ2pECi7Se7H3iL1cWGo8yhtPLKFViRxuT6aHBPfjhI42lRxir435jU/ddWQaYZI7mP68Kh8gyxRKpv6wKnQxTIjzufj+dDDHNEqkF98MZpkTkr74zTDc5KkSfWBXaOMy+rOt0j2Ua/mZbuhk=
*/