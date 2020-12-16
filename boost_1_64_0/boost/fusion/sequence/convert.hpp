/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_10022005_1442)
#define FUSION_CONVERT_10022005_1442

#include <boost/fusion/support/config.hpp>
#if BOOST_WORKAROUND(BOOST_GCC, < 30500)
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#define BOOST_FUSION_WA_GCC34(type1, type2) \
    boost::lazy_disable_if<boost::is_const<Sequence>, type1, type2>
#else
#define BOOST_FUSION_WA_GCC34(type1, type2) type1, type2
#endif

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct convert_impl;
    }

    namespace result_of
    {
        template <typename Tag, typename Sequence>
        struct convert
        {
            typedef typename
                extension::convert_impl<Tag>::template apply<Sequence>
            gen;

            typedef typename gen::type type;
        };
    }

    template <typename Tag, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename BOOST_FUSION_WA_GCC34(result_of::convert<Tag, Sequence>)::type
    convert(Sequence& seq)
    {
        typedef typename result_of::convert<Tag, Sequence>::gen gen;
        return gen::call(seq);
    }

    template <typename Tag, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::convert<Tag, Sequence const>::type
    convert(Sequence const& seq)
    {
        typedef typename result_of::convert<Tag, Sequence const>::gen gen;
        return gen::call(seq);
    }
}}

#undef BOOST_FUSION_WA_GCC34
#endif

/* convert.hpp
tt6YpHOIOuu0e26YBC5SNdb5bNDXEo67brQ8W56mThbdFlEu1eUdQe+5RMKbo4eLu+tD6vvl6F2+Evrj4yRnob3S7vSGC/4JTflmzVMkz41m4m6Fv0EeupJtpky7nmpVJ7GYrzZfc2nPmTkSeXEHuRp0TWBnPXgdjKW+DSndBep61YVjvgHFPfqCU69ViscW6Yow8W5/7u9ePiFbjnCMfwE8nopEHpeaSDj1omg69Kl7XTuNY9pAPYU5zt3CcV2VD6aWBvrF60QaPmIk7ZPcvS2ezF1II8QhIdAfLj0h8HqZ6voY2lFivq0wLrzoMh4rTSdfoo5fzFjtbjXpx+d10UuYwwwRux0xztUn3j9EuYBj5kY/NRw0AZf/9czx1cNz+30UhuqFnlhctW/tSgcSfIYsl4XFY7Gi4fvnXTPB6/X4OuFoIYr5TuHlen2ptEAj/EK5WAFn8vmSQ60wT/0lSku8HX5JyOGu05uhM69O1KV68XBJtskI8iobbQm+vyBeZ1mmkr5FpW21aB0w8AYK21ubljO7vNZZPSc4u5bjDSLm5G9hODFDjHcj9HVXd1Qvos+rvTzjZKyeLy3Wp4u1UlSBmHBlnxt/+vxpbr12t+I0Qainyc+EOGU+5/v1RK743ZKF0izX4daVPVadrtfiicE9aSrT39QcJ6vTmxrqz+Lxy54ijfzTNWehQkkIvKfx6jxJeXeB72icQDdTMj7xjDS+RLNxbgljqMZdEQ/RWF6XMmxbzkxxscgxt2canAoh+p/FaYYt8VtVGvfnweNyYAzRHOp9R6nFKtXpHHMKz9Ic6oRU2wulnOBspTikjZWSk4g4mHevfCDhLB4pLbjOxf7d3yY6WjtUmor2jwGb/InAYojtw98xdreZ2SkP1zEff+UqCX636frBKfqpyGs6jZE2Hq7Tt/ARpfG54nTDtZAo906aUy/Oligd2c67t76q4vg5DDb7xG1S+Ike1tP5gsRuw2te/Tv1/MNO/w5Df1M49fOFY7VF9m0VDe7sMxo+mdM0nKOkGWQgyz3SmpOM4sX5GT+Sy/n8kOaSDVSuNSJ9rEOnUxynbKUZtm9GIXwhTgS2coAjhC/iXjma3ySPmoXHsPtq7ERP+PMeKtv8tunpuQh/7MMtD1O04I3+dZ7kuQXTUTeDRaUiHvZSsEyW5/0CaJf9uHH+Daz/76e4qh5qGnNfsj17+kCCYb5t1KjVqzOsp5gL4ivg4iLlFtB/Uvjdl4oVz4GO7bSQz0L1nse8JUEkvj6Xx4O24vpUc7Poa2/w5WF7swz7AGVVtia+3QMOY4jz3UEbyrXQLOqqgW/Tfph7wl4KcKQtO/Ex5GH8NOMPXc1jC0Gbfoy0gRubPt80HGPTT35Y5gMxeD2ONIAbu3VkOegUsKNkPo1qsVSLNxXXBWdXcWr1Oigs7x61Nzjc5nXUC8uSucaYXAYnvMZ48SU9Xqd7FCtkg+WOYb/k2w8k2D3JWuK2fIf63c3rx2D/wOZdrLu1+dJCkVRYlFvic/XDjfJc5GORPpj8C8IcXzae4zJ4snw7khOZSbka+2c05tNfxJ7jFC7T3ZaYNwJh+7wohcUJL2KeMDglTDh0jHH17rvSDckhE9ITqrxeD+C+gLB7DAfjK48N30jGOH7Lz1U9fOnv9foV301Vhb/uLd7OFg8IOzrsxwBel++yrcl0+f0YdSewyts99yLGw09KDO/BsA6/X+NUdGC7D9fYQkX42jfTWFzz0P9lg7tKB75jcD127D1O4TxJCE7h8WFO3dUN1qeK4+xVsS7VGO6Ilve7vlFyMPgswP/wdoVT7xDxBIPpOsodN7iqo4LFqY4Y76k2wJskPO9/SumWc38=
*/