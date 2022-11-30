// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/identity_converters.hpp
/// \brief Value and iterators identity converters.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Details of the container adaptor toolbox

namespace detail {

/// \brief Iterator identity converter used by default in container adaptors.
/**
If Iterator and ConstIterator are of the same type one of the convert function is not
included.
                                                                                    **/

template
<
    class BaseIterator              , class Iterator,
    class BaseConstIterator         , class ConstIterator
>
struct iterator_to_base_identity
{
    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }

    BaseConstIterator operator()(ConstIterator iter) const
    {
        return BaseConstIterator(iter);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class BaseIterator, class Iterator >
struct iterator_to_base_identity<BaseIterator,Iterator,BaseIterator,Iterator>
{
    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Iterator from base identity converter used by default in container adaptors.
/**
If Iterator and ConstIterator are of the same type one of the convert function is not
included.
                                                                                    **/

template
<
    class BaseIterator              , class Iterator,
    class BaseConstIterator         , class ConstIterator
>
struct iterator_from_base_identity
{
    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }
    ConstIterator operator()(BaseConstIterator iter) const
    {
        return ConstIterator(iter);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class BaseIterator, class Iterator, class ConstIterator >
struct iterator_from_base_identity<BaseIterator,Iterator,BaseIterator,ConstIterator>
{
    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Value to base identity converter used by default in container adaptors.

template< class BaseValue, class Value >
struct value_to_base_identity
{
    BaseValue operator()(const Value & val) const
    {
        return BaseValue(val);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Value >
struct value_to_base_identity< Value, Value >
{
    const Value & operator()(const Value & val) const
    {
        return val;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Value from base identity converter used by default in container adaptors.

template< class BaseValue, class Value >
struct value_from_base_identity
{
    Value operator()(const BaseValue & val) const
    {
        return Value(val);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Value >
struct value_from_base_identity<Value,Value>
{
    Value & operator()(Value & val) const
    {
        return val;
    }

    const Value & operator()(const Value & val) const
    {
        return val;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Key to base identity converter used by default in container adaptors.

template< class BaseKey, class Key >
struct key_to_base_identity
{
    BaseKey operator()(const Key & k) const
    {
        return BaseKey(k);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Key >
struct key_to_base_identity< Key, Key >
{
    // As default accept any type as key in order to allow container
    // adaptors to work with compatible key types

    template< class CompatibleKey >
    const CompatibleKey & operator()(const CompatibleKey & k) const
    {
        return k;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP



/* identity_converters.hpp
2iLC5HPqNW8TVOxc5vDtpoGU3IyddQOxOTAux6vgfpc8i4dEVdWE8YtvCCRw91wnVQz4oAkkEp9dalRvRXvmYB8NX6QG77Akzq2l1aCZkqalNgYnldTJI00CTttZ9I5tbXhQMKobYgA4IwoJNob8llkfSBlXlmE3JmPieYhWHpfNI4nAQaiHudtiZpKC7+rdhCzuXyzX1LonCUcTaDt6Ecnirg5ivfogQm5NXkPiB/5MzmxfKdhrV38U2/OCsog57lx5WsXH5ONeKDK6JtRXeXnofcNOabDUp8UlxmPZtpjF/E+siv+AejdOJZFAEcT6VscgfE5X7E8rbQ40ZmCda7XBoWlcpPI28nbfm0fzMvg/wR2oUD2NAsNilPsuOLkoKf6siPJK8aKsMetZ1OOAtEz7C0tCGro4jhT1nCLTRO2I2qZQB7Y0GIxKDnlLnHuAcL5NMj6njmPkcgYQq3ONIjdZutGCL3EqNqMAs5nsOhVPwNFw/APrVoXPhZyWASkIxJ6dL/6nV0JwyPktjPujMIM0shvbrvwJNIh8nB5JxjOtjMK7vMFbqevJmomms4vH+a6o/2I8pWstmn8cIzEc6RucNHeAUWFAqmtDJCiUzjw4NTRvaAbVXLJlBzVqcisUEEddVU0oLLL8dk03Uk2vQ2BIQq0shscrXU+WWDO3g0yS87eCaFnuFtpo0dRq0KgyVOqwfbjGyQF1nqkF1di0AxVYUVWmFhE/JNJB2zqxRXz4W/3EKp1gTt0knixSgFSHZttaT88zA/c2WKbF9x/7pPgt/T6lWcMnAVp1i3HxvD4Yo1O8imwIss4dNMWMHyI03BynCwUnMBoBuxEydna1+0yLVTu0cwFFvyIfiH324DCiYLYgMRiYHLGEgQaxn9iQAcmx9SXRSDyH6W44QeW6M+92r8fvDl+eYksrfDnCd0xBCAFyoerDS2Qh+K9JJ4P23oKq0c1EodqWFFesc+vfBlKaGdOEhcr4CWGF9MQhpgi2TCTVT7RDj+1qWhIrhiQ44ZR9NmKovj9alBpCyCDATOuSSJpFpS1I+K1lZRScN82c5URm7CaLssl/N3eTiR6pDq5RuZhFnsULGxCASYmtQTCmPO6em7qliuChUNq87pqrlQtx+EUHVKHQoPDbnwe74sDJQF7qa4a4BxhOuYKDlLsnf9kulavaQvAZU1ez7tBTu91yp1ymsMrXg1weZUagHE4mU2BIxcDZisPtqzTw/wZh+Y2bdlaH79XyOmLVeeiZce5nvb6WydqYYzvE2aEKLvVgW0mGmwSCRUj9Cgl3F4UXotDwOztCFZZkKDwFZ0iR0ph2YXWxq4hp05RwDvIhbgFHsuJHRnV9yhQa1FGH16mOADV1hpDF9jYm1rg4O4sfBCvE1UVETyU0jSkPJjXFZmoupmdLsOy+62QiC/S2bZtFTHD3/jqx7JIIXq0BEyIEnsfpUCgX9poyd6biLkrL4vRFJP8l9XzswF2TZD1NsK1YEQRamgyQ+VcUFLk/KvzVqjBZ/yXHCC0enfHbo7QE7EWQZMSqJP3Vgyx216ih5nhU6P4ZHJWAWQ1R3IHSslx3fFjmJRWwDp7AkSAwT1s8WWLQ2lK6TPrCn26qq6am9AInw+7lmESrTYuDglkJVW5g9MjFQtzGltNRcUFuKTRQbHcldDQrV/wW1UbYEubYPUeZBMSnLP8NUY/JG09e8mq4R+sGn53tN3gUEO5jp68UhHzuLb6376tAh/KyKZ7To78yobf++yU/apuXdt75j/DwKdbH2/4WdUpO/gJNGoHZ9IKLfhFdoT1OMBVvMdVcd75VApvTQLSgNwat0uMthNoKXgyVfpsvql0GfRAEaU7Qabd9tIEbqLRbMlvV7Ng/biHaT8+95YVD171Z3IBa7d7sHMTR2ZFtFPmOqqN0wiS+oY+svMaLsCsm7pVklSGYC71hyNY6sEYmoNPhHyaQ3jhMGntsjJEC94aaAXTU0ObeDcMCHN2moG9vjcfCoR0WjlHQVVm9eZAWiA1F6XmTzvR7q+bf7AWUmU9CmmSpmqgQWnOga+u4+hu2rjiCgjewRMM/GWAt7PlImPyBw43JHvHDGStrc2Q9SO63q1607Mij9NOpfvSSTUXoDJd2q2/RQdUjWs+EmYq74FEk83RWPLiaQGUUMPGmMC4VjMUM9UnMWUJMiaLkSZ1Y7/hgcVNNDPp9oxeJfH+U/8MkC0KSD2IbWAkFFlXVoatMtlucgZKxmeOhFXRszS4W8q6QG5lfAfOW/G9HbWhBjQQZf+A9qNTe3rjJ+dW3w0pdzLnTVHWqU7aCLx/E8mVF28lbmFaMCCKSxuEpZTtQtf7u74bxiOCwEpQVChgq7E9gauo1DKph1P14fzh4uQx7YGjiteScfAt/+LQF9ayhbYB9gBqe7XgPZ2ERA91a6uGvk+Zn6gD6sJKe2gfbH76HjhBK7nGj8hnTOPv0iGYYOs7BF2uuI+gkhK1X1EUiVXFSo+09Rlxg4IuAJLTCa/YP1wmYR70LOWeH+x9J6YMcdHk6s6JQCQkSkBruYVu0dWiTQ64yhK40G6vgra26OvLcrV5Kin+0fXPneOJcYJlHf5qcyTwUbmtSmfM3iG6FIscipHjFGR9JnSVxN+oNhbmiVRqbdbhHspv+6HW8LGili//IdKX1ZC4RTzJa0O3XgzyAPirPvCnywXC0IA7ymQAVITzEW5AksYUGzEH8U1aMqbV8cIL681B+4gjVOk88GfBWXGBWeyXi5d48d/19ieNMcXCeC9wmwoLm/rwHzqpAtqM1pfxYqo8qlq4Dl55KmfyUp+YpR7xTKpMjyiRe0ezWj8q1PuIG40PoezSW0RFiWClZ+BFx0Q4nku3ZTcu3vJd2lOxTcfBx4daH6sUZbwZfs3/Vb1VyBYeaYByZmYm9IysmqmJafOmEXCW9JFAuGMjNYYIVlJo96KD75gmtKrQw2p+8xyXVJz6DAd+6F47TXAkCK85/MmFmXyQK5mV4ZTUs0lQUo56TKTWc0MaFnsNukjJs6mzdmm/VfqsePVq5IEKOtd//0KXEa8wkTIPeLfjNKdkqFUGIHgaB70zByUzWWaIAFGskQqAsBPGLWTpjF9E3+t/Ry6Sq68rycLUmo1IYrAAzFSwUum+RIg0KjFE9sbsArTVRSM58cidLl1iZA8xQOr+VCzyjpaFOaxTSeA4nnOolzWgxcdxJx6s3avg2frzIYwuMyGI4ie5SzBFCQ0eUl/X21biIFboPEYSEKnfu/O/oLmpiSHEbKnn5gPvaiiAnLtjBWA76OIjWzIRtVpMgs0c7QTUliAJ0L6XZJqkoThlnDqcqz2QdOr/vBwk15EUG8eLmP95Yturc8qGqdnJM17MYYWScL5tHSCmx30DNEn7roiUIIvvrBNhI8nB0zKQoUVonWgRiVkpQ6gWyL1SN9aW0MbeGR5S5OJu5EpgTuYu/yndkVvTS/kQg1KwxYb20U7XtxWbrWE+5XIK0akjDN3xQVgGrf3KuqPxAH3PUHNbIWv1q3//+kBtrdaiHyKIZOrq0LpkZCjrQgONGOkXKaEA32XRGFGEiceR5QZNVwgVtx2dz97csnYTAWITE/OWcZoXpTcEMpLL05SmbAo61cmJy8Xiy6zwqHkkBSbDhGGn5dxYnqu6nGRaqG+JoygtTG6/xzmEQqNqimE1AizQJ3B6mq6PN1vx5YCz3a3ky2d+vuA/j1BQpe0IkjVhbIMgfUpxTXkRtyKt273Pu7cUHjKoTwpTSs9KYRKQbs+Xy4g/64C8bm5FMgljwkGpFW6nMsB8in/AwcbsTlp01BEQkrp9sKJw3DQFXJq8mD2W2rCyyTNkOUT6go4hEcQLjrPfXICY/kJyApjMeAmpUbhucTyt81KLNVrj/38diym5lZ2qSA9u3dcFc1rdmt6Oa6bKQDOsulWCRzV/Ey0UMlRrVqTLKxT9UXnE25uChB+j5uEQXqXS8ELzjsN+gr/1fQmWx/sAyf6Y1MQfwIPTI+F1dpE1EoPdpawdTVGYX3FXldlGFM4/+DnUPHps0BtIOg70VanbvzO0HHEdAgVuasHQGjJLkaK+eIWAbQnSC8YbqF3yLq7EMeQ7RR56fzD8WSSmqg2tteqgEYkNzjvhb5ZP2odOdJc+SE9p8Q2FIHvMgHmIdmjBRKi9WzigYub0uarFh1TSH6/kn01krNhCzzmaLkLZjFRI5XqCVRJZQ4Qrc8rPAHr2byCmnPmSjYlH9I1JyCGROOncVRM65aBdAEsI2nturRORTQTNhAcXyN0x46VWN3q7lYIrjvnPHKhG9VRYtQGPFxidLFS7GRTnqF31uKbENnok88bRB5gMTl4Dnw4hCxv3AjuQbDgBmnk6UnX5al57JX/bQsj151P3vRgjlfpoFKom05FxMeu4Rj+UGyxS3ZCMSFUr0hw1DsDTC0E7fiEn6c8R142uouJ4hNwB5kqRoWnwUBhyJUkOWt0+XGSsSCTK0HSg24EZdO5eanLrh3eOKc8JUIz44kRM50pfktdJPDrvk+eeJEFH+zIIq2irSKmjrWhkY1fGaY5FY2iHys1lh8vm+YYONlUs6tBdoo0GrzTIE3EeUaWuKH8gxF8+9OX9ssDTgCJalJ4N7uhKkdf2EglxN8SjrMjEhlCBvc1Fqb6uWEN1y3l6b5oqEyDbKZvuFvsQMYuD7UToctec/tT8GzKO80az3dXvnzA02pFHk9XxQp9BJIsC8HB3isfXU8Vw/E3LCC0VARN+KK1qToHBCJBFkZWpyziIVouQy5UKgxITFl0N0HiygKt4ZpXce0iG+BJtPnmURPcp3rM9pgtCk54O1XROVmenUUe97+WFpN3qiPhDai9CJrjWwp0jynDTiA7HTD/fuqZ7pyAtzIKVHqujRE0FJWUHqSohqwt1cUDXNzE8xN67sPcM+CGJg9pdqrkyakwLgFa984jMOiBG8Lh8we4kJIPEMCOggUGtRA/pD85mQQot2SdzI1O697DA3EsB3ySIpnAO6Nxxr9MU7dzLsyG/5oXDQwWKkWz29O5YOg97SH+M0nQk4wykNmy4fWqLwpBmKIbyqJmFlwQXINI/JvrhDLIgUiHk1voEWIwxYlo44zsvFceCBSsXtHZValMobJSx76sW8ZZA3ddKBzCcYmg98t4ujB3eBqPh0Gr25K7U1KGGWxKDPxhcSEfw2mOAud+OwcFkSiU/GJP4w2UhKuNbBk1shuJaVvUsxKzLLHwW19s+1GFa+nAuyAmDgL7eoiOHXkZ/e32EljZo5/CMuTjJx4S2n4w8VFMHylP7FCp+HSLy0jOrJ1QdL36GSV6ZDVj7u4u8ipujlP10n0HGMwOEzdeF5WmD6qMtqLBrQy1LNwwdVU6RKSAVRQD4W4HHopb1fuZIjYjh6MQ0mvnoRHFGLjaRqg2NAfV3/ig/wA1GRw5KoZG4Pww6sr8bkS63O01QRyTvofeCNZSiJkNGR/CHKZVmFz75zX4t8HgaFWQjhWHOxRxsZD5wO2Ap9ulJo+HmbnqHmIlblqyrRbR6B62FWccuAqMhK0TXBmv5U3Owf1vC9p4Kj/0aT8UNWD3UXmoiKdQZZ9kWsKmtnIg2uVIufh0i3StA19ac7NNwQCMgfTt0IkzM/xWe05BGm8lEpOFDe5iBzB4g1JZ5C4H+UQv1JSWL9D5l06+9vfrLa6Tt/3TYFeRXPtX9YOKrM1YWQGV+qpZMtXSNmrHblzD/TrGto4Ft08s67ETolr/7aWrNSA/OxJ34zGByjwhMMcLkuuGq9FEx5h9KmOWeLQzms2ufOykBh0SRe2gHaQ2zWIXjBtJLRlBzgtfHPPnAQrl1TboRBkaRxa48Q5jFKkvtXMOfnUONH44lHjEz3gMGdEjC3irZ1vxToN3g26YcimKzSLblGKuSFjV5R7EYN5LAh9peBmvfM6tBBI+cCrR88Ftn/HvUGaAewI9jB523rMtBX1YZqxjoPUgkWxO+M/suGgUKCJaw9BXXh9dekfywa7nIgDXxrFU5J5AbXtrlcHpqTNGkT7aLsydrDBrIxSazhpY1wFjqiNMvNbCXYoZvRz8iFoEupjgeb5FGmUatA/TNywNeGG6tfm8J9jXW86wAJQVBRkKlX07Y3Odzje6aodTIGzszI7Ax5GbyBe8A0Of+nhvGeCGVQ1TFXm9T08dwurRp5lSfo5HmlDoKNyYPLPUUj+8R6SH5QAoNibysoKXRpFQKvp4rN5iosnK+r57cwhA5Mi5Qf4WpOCu23GBM/kSJs+wwD1t7ruI5sfpQB9belW4zOdH+PgmtsUB3py3f0Em0gu66LS9ucwoEgXw0rrFugF5ep4GWlJadYmj2AV5Pv3X7Ln5qG5FL/y+Pa57zgFFLMRUu2nMihUPMYnzYQ02h1k1bl3m9OkmNrKfEvlBDf0mWWe/OWFKNw4Qlw/yq8B4hfO6jAotltRg8VbmlbcwOHntHfQH8+2GQ1CGCqPnC/Kxekj/Hd4n8uKBgKAZRGU/Ag54koNWab87G5bTGCDJJsb7w6JKCimUBzU/bDUYmQjZYSNG3/eCZQ9Wzd3McRLW9y9W64/IUmUMhEkkF7ZIANyUePZszvbV0ZEt68h1FNoMGO4SwVOsxa9FwrvMWbmeFmoeq+uBzHWgPwKBKF+4ZjLrOFgYv6/11x6Wf5JpyXRS/pFBMu3Ocf7EqgyFrOHskUiOZCQ5dUN2VkpWQFNBIRRsiZnVdD+MlSgi9jIxXvWfSKWw8HXclXeRFPc40FMd4PcdMXVFdYXezvhSBZ/afG6cElY2I4NCe1vPVqO9S2O0iooaMV/ahJO7KvRigNnYsbbivgK5a6wuse4+vJKmdZPfjNrV+hjNYs4jn8ZF0MUwYS7TbtvVm3cs380YQodY7KwuHpJVBAG6St3c0hQK42l3xYMNeECF3rCCvA26mVpZ4/uTxsMpR/DDWbh91gv8n3b4O3ynpp7kgl5D9i+34iWPGjIGd+HIYmRXH/5RXOWwYySbYYEuyJLE780hJMqsOLRz5SnvhISgfp0q4/jp3NMoKiXXTwtggp7GC0hJs6YHYg4FIFPWp2vMtpWaXjFYP/CSVWbxw0gUrRX4Tc8X03PD7C1/Ls0xBCcN9PhaAG6Ox+Vo7ESAuLLEK+WF7ufVJKlmeFjQwvD9Q+yMzr9qxqDbzExQXMqJ3WdQ7/QxvMTwTDNtkKescK91OnjQhefkadfm8RmgMD1of4NrOuNBYHY3Ji1mg+KM/YUQ6Nmnu7bO1eIHY0UDxQmxa4ffWlsZ9T6r8QlC4hOzDVVo+uQPebTRJLTSwYORWeLy7cojOkWsfNm9scUieTZlTT173tQmujQt8acIWhO8aURj1qh1hwiK7rE/LvP4qmQaq8Mg4WnughsubM8S2SZh6/TQk3dsuFJOyMDkLmUaweYh02SD+NlkGgNvygK8YJ+yOjHBk3d9xID/767oS9XzEGYnQ/EppRcjFi456OsmKY3sqx+xz0X2CjBkjffwF0mZgKltaXyA/sB3fEA7AXUIkg50HfyFujB2ixXgs1mpNlgtfwruy720lm28rPAk3uDK4U851Yp4Xp5Rl8sEJXczAV6QfWZpHWzEV+YzTlaIMxispuUB+o1texo88SasNIrqih
*/