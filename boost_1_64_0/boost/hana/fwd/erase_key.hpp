/*!
@file
Forward declares `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ERASE_KEY_HPP
#define BOOST_HANA_FWD_ERASE_KEY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct erase_key_impl : erase_key_impl<T, when<true>> { };
    //! @endcond

    struct erase_key_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr erase_key_t erase_key{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ERASE_KEY_HPP

/* erase_key.hpp
4WzzrayKdLdJOIciRKVy9oYHkNZQd/3tP5czoUnv8t7f1jNeCnlj0vrcRV5JVhBJkVeeYWGrC/OzyASzTd6a2RpMZ3tNfPlkUMPO6wbUWhr2XpN59MWBT/ONx6MveKvE7Q0LSxUcvWnOi/tidkxKPqmFMtVS+0ChI8rAESoNjnfKTUbuVEbrS6keeZJm7NrmFj6BnomoLBezJ/nyjCy22X3AFBxJCgF+L5fF6kT+5RiLwiM8FsJWAE1D8vk1ZR1WLLrRcvW8lX3UM7UVl/oXiLyvannffycxL4o/h9IS4Tj6Qmi34ei+MB7D/SkAZD5uaoBS6cGfqgUCKhOz2SSUseHfK1YIHwJvAWomtt/6UFBw6X0tZLka0hM+f0N0vUUZYTh1fFyt4eMXDn4MfIyo7669wD4rn0qXkD4ZFmhxnXezKZAJdxsZR194kPpsLg6Mmaj9+IBoQ4/4dfcHp4hfF4Kua/g1p3v8uqZVw6/zVfwi3MqfijUlsEy6B2UmINhXgSTMcetIEqpFxYHpgrsIDqFxuggp167sD2xJj+OC9Ee9pP1aSQ1JJfEQ4/4wrxx7V2ZfnXERYezKfij3j1CfScOJ/oq7pIf1cl7VyrlIK+fTwrqe8I+R74RANZuShlHgphluU0PeOyZCPoI+LLklmZ7fnPK+NuW9OeX92ZR3263J70dS4vOT47kdgoSE476OeojvCb8Zl4tmZAksBgb3aY4RsdxDWh5EbYlM+OQ9rljTYofKlpiP7DnUTBiK5z2HzMdgxTL4V/NR+Rl5O7gG+6atTXUZhNGtMTNd5cOSdi7ZT2AWYnhFky/WsHfVgKUb17e2tlsnRBrhjP2QcfW7MpI2WS489QtNhGCCh3+MxAC46lE3eH16PVSDi2PBfhWPUTtmRS0Vs2Bx57ilbqT0M3ayjwGW1mq+QIFxTx6Kb+TXxaik4GRYPhsHczdrzuNCPLhk/xKu4zjgtMQ13dXWesCauaPoxdojC9Bfk6X7SKLwa1cs+mf7lnRXG8x0Pi3doVf1SkJVVyRUBQ7adHQPKbVQ7/eV6K5k+2Jh88JWo+kEn2JX8Kd7fkXaoGH0WR3JGN1suS0Zv3KT30EHeL318dgv3ehqeVDc0hQo0I7Lmnvazcd59Jssk/WBS+VnphMj8/IjgpH59fv0a1PuY+4NmgROQ+AM//nSptuEkv2Tr3C4fyyHeJWHxHuvzA3V58/iTP5CpT92JNpdqSuUb97PWxklfxdC51hgq4A2T5p37yqlRIUtU4VtcA+wjUuBbYT6not3ZqF+K4Z5tcLD3OsGP+UjHblN83/+bvf7QyaqloT9oY2FCqXaFvD00jdT/ZFkeHD+JRjvSM/w6l/ljfe1xU6P1/dDti4ayc3zf55cH97V9h/prv0crxh7huceLf8H73SXv5niIynpld+n91ge6ktuX3pS+5A/tf3v6fF6fr39DLcttX49/q30rvLyX6jtGd19eyg+Nb1yIK379nB86v43GV6O1+W/XeBJJUhLbnMkBUBnYtCU7w0lLVMgGKg9OY8VifjVGmmbZqEyeqBsXuXSP9K0JfuidEvvDHa1ZosNmohCu2HTlEdwfrjVYojX7zdIRL+V44LSkZqkdNesoQ7FzkIICwL6hFZZDQFzDHrtXeqX7qG0B7cL2mEBHJPh6RtKduAWM7bhwt91KFx6+Bc090diB4vqOMddyAEtW+VpVLu4/fW0FDi7wvd5Hb5BAr6vb9fgYw0MV0vP/v2celQ1L37CSlVW0ckVw6VSDT7/V/xf9ruUI8ziZrGxqki8+pf+rlX/OgKNSp1RM8j2nEe6VC/DprQB3zXLHSOky/SYaVz6DaJ0YUAqouwBCxU=
*/