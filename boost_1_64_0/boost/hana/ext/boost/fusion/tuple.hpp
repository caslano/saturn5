/*!
@file
Adapts `boost::fusion::tuple` for use with Hana.

In the current version of Boost.Fusion, `boost::fusion::tuple` is basically
an alias to `boost::fusion::vector`, so both data types share the same
implementation in Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/ext/boost/fusion/vector.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion tuples.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion tuple is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/tuple.cpp
    template <typename ...T>
    struct tuple { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        // In the current version of Boost.Fusion, `boost::fusion::tuple` is
        // basically an alias to `boost::fusion::vector`, hence the alias.
        using tuple_tag = vector_tag;
    }}}
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP

/* tuple.hpp
Md7F4+JvSrUL+Fu0byPbJ2nNm3wnanHpFF4vpL8uQsBKge4JC5ool+9CC5f9XcD4Jjm+d+wI/hXW1FaO3a6JtsxPeYcQZ4GybVQTbemvUduOsm0n2bZEvn8jTB+33F4jX9LofR9Ie8pDjXLj/TKaUd6B8jCtjNfDyAdk+YWUd5Dl8oGTqfJ9HBeF+aUWrRUOjB0yrr8uHWk19KRLrskaZJf91/LPyE202SA/nhx3XnF1uV3v609r6S++yf7E6Fa3fao6G/k3zyT86TPGy5/kQ2qB711i0WF+HewS5n+XadeAfevG393kvtXIfesu962HbBvT5DxcU0o9g7xzkH/4x79MGb+nMn6vgPF7h/ETMP7lcvw+sm3Tcqh1SG3wzsFXoM4jRplHP2UesQHziAvjJ2Ae8XIe/WXb1EbvPvS/99Zb1kx/V5ym/x0dInRZvPrL+DtC03VYf+fMUKmjAxUd7cA3tVbHBaxIFqlrGvHnOsHLGu3V4j1EPsUILJWY4NL8chisyGRIgEyGhvETIJMrpEyGybZDm5qPsRZnyWSsUlmLUuR7Z9mIv+/nb2Ui+hn1l7oi4oTsHF5RZ/Z2o5T45JKk9tH0XMQGKzORBco8UmQfI6SuJOp7XOrivbEOr64k62W1hD3VTl6nZfeWm/VyZ02FeJWZFkKJFpKqY+Kw2moR3dn61hSXjxCD5zcqYfSucryReh+uqbUinJI4mab3YdNGyPfYpSt6F6bl5mRmJE8YWwBH5XVu3sX9oVRgmBwjWPdZtjj13WD8Ha/aAn/3F38nyHWM1udQWWFNLchOzhf8ylZbVdWgr+UPpYwlbHeUYruZip5mBehpNn9nB+hpjtTT3DD1nXgB/ozyPNnOItv9BeYib9/e+wrUvS8IGGtcWOOxxsuxCv/Sx/ucR2pxlaOy1etxQYONjdJSCd8HZAZx1+PcOfCD30bPHXoZP4Vifb2871puERmsy4/PjAw25CjKmsuym3P9ZS1k2Z4+/rLzZNn3SlkrWbY6xV/WmbJ0ylI1f1kCZTP5e7FSliHbfaWUjaFsPX93VMrqZbtspWyWLLtGKZsry35RyubJMgp8ZUso+1hIVWm3hbJw2uQo7bZRNpG/U4L9ZYdkuxPKs19Qtoayz5WyM3Lc/UpZcLgsM/nL2lJ2kGejlHbdZbtFylxiKIs1NZbLaNmuVimbHW6srVIp+0e4IdMIpewh+ezbylxWhxvr/UwpezLcWJtdeXYfZfo783MVGchxL1HafUmZSCl2UdZxSo67Rml3WpYdVsrOyblsUMpaRhhjDFPKesiyeKWsp7hPbGJtSlksZR9S5lLmMiLCGLelsr8lsr9JyrOTKTufNjuVMjdloyi7TCmbIZ8dp+opZQuCG+/bPDnuvUrZXZQ9F9BupWznUso2yrKIYEVPZdlPyr69TlmgHX0k28UqZd/LspeVslOy7LTSX3hbo+yopuhuW0M3hihl7doasn9FKYtua8glVynrKsvK1T2i7Lxm4JlSFtfWkP1bStkIOe4PSpmTsoJm6K6yv9fKOZ+nlN3Q1sChLUrZfMqW82wnpb9lTaxjbRNzebKtsb/RStlmOcYmpeyYXG93peyrJp49S1mg7or3LI8KaHd5O2O9x+U68rTmkVRrKUOLnC7InbPWXWo3/tNT2bek1lFp6xsXExcTW9Z3mic+Nm6Qr64+YUBfT0WxG97gtlfaeQmwbKGl+vu02acVyefGJRflO52VnqIsC/8ZNyAmLjYmfqCoKXFUF6U7PTWFCQOK6vkprYwxFxJTx8h+YmKK+L8cV86mqNjl8ohfVjdvrowp1XNh//+1iBFiXLYS7XvZd9+M/2Pv0f/X3ooc1aU=
*/