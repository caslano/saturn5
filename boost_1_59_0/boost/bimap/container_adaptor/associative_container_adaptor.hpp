// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/container_adaptor.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator, class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter, class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct associative_container_adaptor_base
{
    typedef container_adaptor
    <
        Base,

        Iterator, ConstIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter   , ValueFromBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyToBaseConverter>,
            // {
                    detail::key_to_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::key_type, KeyType
                    >,
            // }
            // else
            // {
                    KeyToBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief Container adaptor to build a type that is compliant to the concept of an associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class KeyType,

    class IteratorToBaseConverter   = ::boost::mpl::na,
    class IteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter      = ::boost::mpl::na,
    class ValueFromBaseConverter    = ::boost::mpl::na,
    class KeyToBaseConverter        = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class associative_container_adaptor :

    public associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type
{

    // MetaData -------------------------------------------------------------

    typedef typename associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    public:

    typedef KeyType key_type;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyToBaseConverter>,
    // {
            detail::key_to_base_identity
            <
                BOOST_DEDUCED_TYPENAME Base::key_type, KeyType
            >,
    // }
    // else
    // {
            KeyToBaseConverter
    // }

    >::type key_to_base;

    public:

    explicit associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef associative_container_adaptor associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type erase(const CompatibleKey & k)
    {
        return this->base().erase
        (
            this->template functor<key_to_base>()(k)
        );
    }

    // As we redefine erase, the other overloads need to be manually routed

    BOOST_DEDUCED_TYPENAME base_::iterator erase(
        BOOST_DEDUCED_TYPENAME base_::iterator pos)
    {
        return base_::container_adaptor_::erase(pos);
    }

    BOOST_DEDUCED_TYPENAME base_::iterator erase(
        BOOST_DEDUCED_TYPENAME base_::iterator first,
        BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        return base_::container_adaptor_::erase(first,last);
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type count(const CompatibleKey & k) const
    {
        return this->base().count(
            this->template functor<key_to_base>()(k)
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator find(const CompatibleKey & k)
    {
        return this->template functor<typename base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator
        find(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }

    template< class CompatibleKey >
    std::pair
    <
        BOOST_DEDUCED_TYPENAME base_::iterator,
        BOOST_DEDUCED_TYPENAME base_::iterator
    >
        equal_range(const CompatibleKey & k)
    {
        std::pair<

            BOOST_DEDUCED_TYPENAME Base::iterator,
            BOOST_DEDUCED_TYPENAME Base::iterator

        > r( this->base().equal_range(
                this->template functor<key_to_base>()(k)
            )
        );

        return std::pair
        <
            BOOST_DEDUCED_TYPENAME base_::iterator,
            BOOST_DEDUCED_TYPENAME base_::iterator
        >(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.first ),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.second )
        );
    }

    template< class CompatibleKey >
    std::pair
    <
        BOOST_DEDUCED_TYPENAME base_::const_iterator,
        BOOST_DEDUCED_TYPENAME base_::const_iterator
    >
        equal_range(const CompatibleKey & k) const
    {
        std::pair<

            BOOST_DEDUCED_TYPENAME Base::const_iterator,
            BOOST_DEDUCED_TYPENAME Base::const_iterator

        > r( this->base().equal_range(
                this->template functor<key_to_base>()(k)
            )
        );

        return std::pair
        <
            BOOST_DEDUCED_TYPENAME base_::const_iterator,
            BOOST_DEDUCED_TYPENAME base_::const_iterator
        >(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.first ),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.second )
        );
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP




/* associative_container_adaptor.hpp
T8uzIazfhHkE/h4nvcWIN4xipcfw4sWWySt0O8h1l4YQq7NmLK5d+hGmTjpaCWc0UG5qHx7aJBH4RTDZBjSTTKUqd5XUCklo/TiK2+v1TaT0mq7RvnS1ljIeQMPdZX+o2awDj8yUBGoq3gXycxEGrMG6PZwaLqBMgZOgxS8t5fAqLEoPUoLpKSrjkAUGuwNg+UC9fF+A6d0HOpdXl90Mj3JBZU2m4AkC2Ebj755fZDEzqk0d8tunpUKkP3J7JPBUlxgYoyvvE6GnbYHoM6/ieN5zeXMH2j8mqE6paC9csHIwtCSQeUv2Xb+cY4eVeal3/a19VG6Eqa2N4qf2bEyVumJOwpX8OI+SZDDdQ8mfCSfZLcS1HHDZZkn2GRNlQ8touyMps4UHBzR8T9Zv0V7QqRURoXnxlvgd94mmbHYWf/BXwqw6MbfbGKvWEfcTt2UFDaYDShY3VyYb6E4SNmdU1RZqHjGnp9d37xckE1kZxpssKe6vzCVr97zI2wJwUWxIIDRSazUEyioAhN9EKtK51AT5NEo7P15N5TzSo2RmntReVbntRnO4ciDW+17/TF8EecCOi1jwlSs52VlANLfaaqkgfV15O+V0XEOGyHdRL6sp1QOrnuTr6rukuBNv/dy5ClUHZfhUpISDjLhqtcQuj6J8p2qbkuR06i4bB2dDcJH0KWlnwtxnevVYcjSTk5zeDObpItnsSZYLJ6dBbr6vQPayMFn5mzSEoUGCJQ7aTtTMJ5ZToWFwYF4AAx8CRlqW7DEGdRR/my2QlNTMPuxvv90nbjeTnzf282NtPgGP38kZ1lhPzyz520H0J81B6RAZCfFCZ8xG2Ju5/3PwETXzbUEKzR4ocRrklEA7Me2POzK5EFSy/G+mvm3PfA+UWv/d84jH5CB/nhAq85Oz8pqP8x/EOnBoOgqtNlcNC9OKix6Hy0LrpLS8aGrRvAScjCG0MudsIvB/ch65N5PBELfh+tDlO9739HnOWrm39p1soQpQxCOCBWfRSzVT2LMEPVcOIZ8tUIQqqrOvzY6tmVJH5RWXiapCdM5zVa7f9luW7Kn4hixmLd8NJY0BPafTcavLRCLxVeoDvigXvdC+Xfv/AaTArtPefYD56Y4B9AaIvRYMwUjyW/hs93butfySBaNRlAFbJXVPR7ptFwlwVfjpRZeJpeeOi6lKOmLdj3cAKvNzud0axdkurfu4xYX4Xnrbkxgil5Zl8j3ZaUT5y/UpnMHiczLuQMTsFQcehCMyl4UgWm4yBQjhZW7ttSmnvMxyddHwppxfvhaDVRkdGJq2RuB54JpYgdAP/0rhYbIS2VYzkK0ryPTgxGqWqShXrouwfNZVU46eZRhhfmtviSLxoIVA45CZG/XrErSJkAb4YXcQighAYGq8mlysVL+yuUaaiSuhc45Pj7+cfI5Yu27artZ6L/byfw9s5WfBDd6qpOYn83DhGTTA3NfcJFVaVOwGifykbfcdq0bwdxZdHTo3yYmRPaQduUk64jdtuvQIiFxoGTKkCiMgRWB2PazbyKH73B3JbnYVF2SLoRPhOBdopLFExvC8RbN8t8IvPDiHnqvv1cUtYj7L0N667UGgdlZh4sj7mvfLBTbU2EHrJq7P3u7JcFZYEL921eEqaycHLltIczdhYeQXzvR8x7PRqvjic8HAMLJaO8/ZcwM3zpd+HBJu+KZp+NCMvjWdJVAiXvcv8Rrt8hN8G1r7KPLav+MzsPrnWU1KDNXzMWeqRhxhoU7tQ7E9i2TAgCd0IQNxbwlLtdRq5M2l/nA699403E1vmH9TOvIgIGLIH8iOSLMR1fB+DVxdwQcSomOPsONBZfovnk85uzgwZdg5XDNr8kYWULqHqiCOUb1efcIGTaYyUoK4QFUrZocR4zMsQywl9RZ4IT4TI9BRJ1uCgJnP+cgqnBoQswDWoJ3VHV333wiTyJlb5d3dIZQyRTvr8AOelh4+csCCaxtAc7kbZUl6O5X+g05iYJ/bVNWT+wAKLPXTT2U54bcIJ3mzPwNMfwyglcrXPuj3NKvWOTuCjWo+JCpAUOo/Eawnc6wHtFI0+VRR9gMHvnZwVeJgOtMyzcrNR8zIg1wyu6jtlt3bV/AwUys3rVU8Y1+yp+j1J4wm0+cmgcSLViK8u87lXELKeIP/dpN/pmCOhHZXQ82odDV1qF1OBccH/Q2feilp7W9DCl9eEjEiF7r5HLP9P8FN/X+IF+LBKm6XRaAdzkRtShCRTzvjcrEgX9hhHHhKGQggFNmrJefA3/vAQVoFY2YRS+Frkqr/68L6oo5EXQJcvz/PQRo11b7ki5wtDKjmwPc/TGHwJffrJx5FUqNranyTDYzy0fxnkAegrKTaZCOZh7JsEXsT9PBy0XW661Pe13/ptU2iBvczMlTbHG4oifg4fP/EweVQI1AhzJuLzYTq01lmD8fAfoZ2ZtksLw5u9fjiK3GJRIB/iY2Fn4ElOyuCE7NWOFN/7AD12RYRKTFZ4kFTVnemJK8FSnO1uTp83BqR1Cy7iGygbjHdsROZ+NH/z3rpHLjcTZDxAsiCO4XnWIdpsDNP3bjNf89yCA18w0nLNAzYvEJSBoGmnMHFTdU9F3n0ns9ZvI+oPCoEcACA1IQhsOxCcVqKt/yqz1FNCtD5vc3GwR9/PGxsbJJre5LG5J0xYbC+p2D76rsXPLu504QVOfXO/gI77Hasqgr2M+vRl9gE8pgTLE+RsfqJW3DQy1rs9PCip/fH6VCoIK1vy01qNqJWJR+L159UuH6s3t/y6aYoVpkxRKK8GlevU0IytDK40sgw03ULh2H1wUJBaX4+2k+gSrmiN+8ZukXly8JPkfu4sxV+7usC2IhahZgNqiJ84EOfZCn+2xeg1ohZCNwPwE9YGhDA79e3Hdgo0mHUsDbc6cAkdZzANJ0gFiaU5wHwOL5cuZRMNoOFMl4PzQdVhM7A610qrZf12xlgdADfVgn/9zooIvxEk6AGewBOfIxsK2Kc2GtOfw5lfVN0XNeuqVCQNm/un3/wuabu5fpIULaOp5dSVFARx9E86QdMo8f24ShBSZWClnLpAbJhMnHKaynIbhIevfLpjIp6Feq6obrlrmbd9Gswea3i7tcIQW66lB4kBwTCBi63i4p9Day3Di46OrtnfwBoqBfZCWEAPWaRlgfuw9hPKV5UDjxA1VqDiTQqAj6fw9GYW0BgMjkDCM5BR2UscN7bte+MSmTudsmKr5v6sACo1XDrm/fV5/BsHTthQAZyA0paeDAxQhyY2QZun4GofhkuHH4fai5GpeEVoHG93ddx6u6dHwwnSSH1hei05jeoLq64vt9AYETcg/gB8MvFbK2qMrlZ83Nr6UqSveBqU67PhwUrGhESjraUw63367br2GbafVJP7/42EALaSbleJe3vvcCTcNnUpHYt6FEoPAYDgRzVrJSU6LCzWriETEDX2xPrGtqFgm3Vh7aowSSFz5rps21hn+m+WFGYBEAowX5qaJg+z/aezHpINLYdh2FhE4BcnNMwgINaba1UGjI6eQ4NZ/6FYLEIAzkHUh6D+ssBDKuLsaYWv2dFo9+gcTnGSLZ/cHCw9oBc/tcOPLwMneYZZTxBsGs7jGEKstAnlooVKdVmh812B5RGDBFBfMi+LQhDzha5D4si77s54NMl4huXPV/fgT0tH7oP7ZTyogmt4jw0XrnO/AgvB8uyRIyqPSTjR4SwXEJw1a+1gk+HNi6301IJnsJhgbxbxPQeIOVFtgn7XkSASu63pWtcCdaTowwCRRv5YrvBIBivcgzj01Ao+CO7e8ZQEkvAvgs2aPwA36MUh+lGIXGdjuvORvO/SXs+y9yjI2NvCrRjJLW4sdutdlevf2ET2BlVeB6GlRUcapHRjCs80CTOBDA+spJWsJhP21/E+3N+IM5zylFsoPl3WKlhWmVCKoM6yp6wh/ENZnJJ5VhWinONhwqXbAHTBQw+h86BS7N4k6PLezx9gnwKN4lGvWlixnC6O0Hwlpw+u0B2Xc/9/uPUbWS13DKtEOc3VA+3u/88MAnSZd1BCMYlZGSikjhhG1jJju1ePZmvrNyzPZ7OrS9suaWrE5UY8Psgh8YobFQK8K/QBjnqIfLOHtus/GN1kGBTJhBP3/e4mGvjeo2gl/S5hYbLGxU2NS+PRXb8SMrQfH2zOj5f9nF99/YlfZtYPjd7AOK9h5PbK/+rpgrkagVlGuW+vf3diJ0m+bmblDwx6vMpC+v+KRkFGFACJJEGTMiETFhvNHuVk5aOdAFHGnl+fjbI2qX51aZ937YZw572KA8FAxdALG/WAQiFReIFtgUenqfWBA7qhcf81RLQu9bRrMli5bFMutDG+wwyoU+rvEjNLtP1eMFipWFfNwsQYgUhKMICAdPJkWgwnc5oBAGnGN343WQ/F1wFWe3mWWelyDPTAzh3QZuk4QV5xrfbEwb1Yk6BTgIkOcfExGSEMQpsV0LUI9B4y+bRPkkDpF11wQlXjv6eyhOJLxLjoQVm7mhyizHGcJkeFvzFh1zARxqa1r2/Ob1yg5XL5dTTtQAEziPgaIsNpFnuWhdeLvxl+q9RpWdD9UO9T1BtjYpOZxQqysGLgTKuVuf3HcSv0HONqhHUIymgjsCoNOa/X6dl8t/gQHwb4cOgfackFcvWoIQ5Uoaiem//IAuHHuPx3yvFyV0+v0t/LcJMu8fYfkv/aykZeUXGuaqgqF9ahVhW3WUz6idCmwzDM1IShXPDf0Jit27PUweSVL5Cn/GyO0psgoK9CrAzRvcvGlMJanevAKPcly6xt33/pZ/bqB94r+Zjrmbjn3dC20BfKkINKNlZDG5sH+L1OD/x942wTRUyuHw/r7YeHR8PP3b7BUZT7CGk3m5jzqTyNJg3dZx3+FzUn0aojM9LyTztU8jmk5ytWfKGJ5cZItkZR6OtbRejQBlBswiZeAKqFMI5Yi9BOeQEVqJdSLLaQU3ztp6Wg9/ihsPH2wpmndfTD8/RqwTu9X3jnuZPVBtzgN1OsOZGe1eRU4Qm1Z4CFqwqUD73/mJ0u820bXsCJJjZpcxz1ulMc7yyh+vnofqNMVPvQVMMgpFXqNbOqFDv8Bb5PH56T4QLrzWVQF8mjNkowmp40ikNk5ECUKz1owFFREFfI2HMVGgu7x1paFxHCmMDRoHVKR+KFRu1j6kns4OsSvVDJK/C2/y0AwXONhXhNWm3xFxvdOFFWy0fvLrEeHSS9/dTaYMBWKh9V/8cVRzv5tSV4hBoPMyL46seKnSg0chKxre4gKPoEezbnu6mVNq05+dqPnzoNnt4Q8bUWoHEWt2Gn3DKvBFxUf9jkcBRbyuFr06R6ew7flXOJbCV/2/hdiau4+Ax79TwzCXVYii43JnDoKS+B47afp4vaXvvYa7Ng4ZJRjpaNdbHtinj+dlKh0SvT58EMNQvgI4S3B/Q97JENpPKrngElOfR7xwUA5qDYsM1+/v8d6ZJKxZYxDaX1bLu4pb4x+2zyBsVYBwKZ1sJmFVvsUqjcUHAZ1MMEXu42UA7N5qkmZ2RT4r3ZQ6D9XVF0JKybLykmlyVJchZKSnlBMKLsB2iQZHTvjwWuCEcWHp1MP8ZKqTfFQm76y75SBCi5Zlax9uyADURwAJMP6POoT29lA1sXeGNjOHin6Uq8qqMf/CCA8EWmbqNf8zwf5v4tDg1Np0WfaSNymQMY0r5uZmEtlm89gciwH2KsKo3uLbosL9VpZShLLax0OeDZLDJDU52t2P8DCjRr1RclOyEhIQB4pklRUUij9Rik7UpEHdAGHoEjMxrvm2a36/Yn8spuCtbkMdo09DKw+azqSJ24vraVRFDfXObntMgX3fICIocYbRIkeQWHBwyavzaA/wBxZANAsCsEtmA0Hxz0wDCyOplYjgroy9NN/FFI7ENYpF8yBxg/1pv3k8JL15s4VTs6398WdT1FhM0w0g57IDkeE1HJ9trgfc9AWJue9u9ze0JZB9OTfTgST5E7e3bBkUNTAVigY3HhghN3bneeh2f952smjwA/drgAtmtTqbSx9tsCHUFCrhRsqX0ERiAEOy5SU729wH8Gg66iS0P9eT8ngdquIBAN43W49H02xwZcQj62/vXWCXm8lZ5i0xBHaHrgMERzNki7E3y7pq/N1tQvIqWUxAvJIhlwCltaWu4iLHRyixApdeDskNBgvmGEbiBJBmrFmHtPbjLQOEnyaidV7P6L1I0vlW8avv8+pkgm+euzRuVQcBoZ6Z5e90fT6iesOmXtsLa63JpdrnKqOY6vo5bF4G/JUPfUnkFHMhhbhT0XeEfe1p+TxWAZw/7Rsej6xdLZKWHAeDIFUBIQML8RACIajpZdAZn9Nl8jj2HL2J9uWLc08XMFe6eQxnk7eoCKVPV8/rVEFCCBQih0VZm3s/nsf29HxA/qrQiR1dUBsEgHpdmN6xfO1OGFxuXSjGdnVtYAGiA0OV76wbbOxHFO1v0C5EoQ3b4C0+DafTtsrFap5V0pPWj+h6y3VvhgqLigztaBdfFya6fESsMgAKtxfXzejXtDjze44nFLzDgH0a0bFFhe4++cYJrp+806GwR6Tz9YPD4x7TeN3e2Ve3M4QQeOLDa4DXoygKU7YcsoqhZGQUHAEkDK2gJ8fEq6KBbk8v5rXhCJrmpAZAqsAUFIdCAQLOl5s5QB7ZchVoAPxUHCvvE9u8AoaRgFic1rPTPdvXz5of5pVlaQR2/l9jANnlcKK0B+ub1BbzdaiSF1T99HFuXDbohIWCh6gqNJSVJWSjayqdK2gDEeAEEIwRRr6OZG/KnziKxjXn1Qk/Z+EEabEpMtBBRgGACCpualsKTt1DXDDYC7HZYPrcmroXZ3KQWc+9mgECSJv+x8c4YwmKd4guoR3bWciYAxn3B5LX5A+Nj1yKNRGOnBsVAMvsTLYn0DeyCQaH8nEQiN198DyhfyGtJLd8rN3/YwAORIZXWBAn7lWiqAwcHAgMLAQP7ACaAEmFyaGoV+g42mTAg0j55soCAX0gFJtqrMM/yMMGCcS/JWJMX/tNfY8LyLd0EEEDwlWYOsqcgkaBsM27XJ7LBz8kpLjl+BfO0GJcyfej5UnLpEGIEwQEBpX2woaSiqihYCL5HaEG03BrtV8p+Tu6pfc3Uy92njlh9/ctAsBjcs2agG90dVbu7UIAh4rMvhiqQmCw+bw+o1LI0AsJLVJq8OhjSUUtWhZaf5yguFQe8bJgJoJcI/XAQ0X6KVrBuBcxMw7sh1MslVAW0fCKBYDx1MA6EABZty3/KcNAEbuOfjAAQ3m54gv7+s6S7RRBccMsDdVtwk2bdQ/h0t6jkBBkAMRRJ7gdpKqyHFzCsqHlhsY96LQzSp7AYQqxtM5AblOTG0Y5tJmiriiHshFfo1Hx4DxHp/5l9ZYNCpHC7T/eMUo4VAwSxArFiQls+QPgxBAYaDIUh2iuXyEgKkpuvi/QJxSHQRBX2lthZPPkt9PT93o9sFmSjWv6bx2y+fJRS1dgGiNublJDu00ew1Fc/EgQObFf/61WekA2AIgzfq1+/bDE70z4EJ6TUPqO5xhp3sP3taHSAENzaQNXJ3955jPUDJvBzS8iiJPtZVyitj+O7gOx1/PvNDIpBMIqwzH9N5b72L46hXbL4
*/