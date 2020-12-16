/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_ITERATOR_05062005_1219)
#define FUSION_IS_ITERATOR_05062005_1219

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_root;

    template <typename T>
    struct is_fusion_iterator : is_base_of<iterator_root, T> {};
}}

#endif

/* is_iterator.hpp
daeImRbS+eWzrv01Q/vRqm9/maiMl1XLBJmhNSrJ8yTaj1Y9PalUUnJetPzNbEBY0e6zl29eRiIPunzb+82Gn2Z8Eu30qt5blrook7KKWv52dFKrUasTOVzTWHF5Foa1iFizYND80N71aN2zrQyFdhySs04A2ksHY52ojeZpQmjnSdLJWVjkQV1VmUmnS6Axp6MpWPvxVZJGygqR50IlFaahZ4t5f4zgetQrQ12AeMky8u078RrCK8O7azo3c57xKA0EtbXsCoQhOXFcXKnpeyJZ8TyIUzO9miXIsOAbFpdHsazW0l2UHQ8Iqz8fX6d9LWWRyqxEHt1Rnh3qlKJ1i8tE+7sUyAR6H7wkhq1r36b5aI8fVp3GoQDhh22XXQ4oP1O9GBFlENa8iAh/s3Tpde/s8nN68Z2frXrxpYqgzhKsM0wjTVstj8/14nb2+OKyLFQQVH3GnY01L87IJdWzGa7qQhVp4PFun1/o+7p+t6Jv7nJZZLlKOlbYNI6Wx2Na1i/2yhoViY7HWvX2jUQnqnVTr5yD9nl+Z4cLQGuoi/EJXjUH6W8RDBrr3hd0V/cFpzZwQ9nfNW1eGGnQVIOJJ2PAktRi5ESMPqVqjD0b/1PXF+2CO7w1DK46WS96NkNpkCShqG/0Atr1afSFQa14Bc/rtbgch5536G8fuHSgHQeMQ1+f7tN171t6PEPoQNMZ2HPHx/YB3fo8snZT+/X3s2DBsb3ZsDl5Hj6gaTAou2YCoyPXVu0Nffr5EfIeOQg0PA/5vG9FOvJi218uqE12GMECISt1o22vdaNfBn0xFQo4Zzq22p8f/LeTg8WmA4r1DwgWe21vrLaBpLqa6b2x2q7zONrJ7o3T2eN+2En7yD6fxximwtWNxb17D5xpBMTdf/9knGkAxL1tT1xztkDcPQ7sgWvNJhD3hj1wx0xrAg5t2CfjdEva/nn1HrglmP6XNrQXDkcXODsZa3Ao769zcGishnRI51BHX7BkN4ZKb76J0zIIiuj/kvmfgh6IP0Xpc7T2gZjwivqi+tyAnKCs7eAAaXhS6vux+qyhmyUby5/2xmwm0rwU2c2OAeOW/6t2zJZBtBQHi0Hjq+IdUC+oU+u5y/h+vIJY6n/zMwO64rk+Ic4MNB32Y7on0N5N23Lr74ZBC4NDW5jp0caW9gdCG0FRrE3U9f2a5q1MxBZr9cBEzERbrH9Nxnb2U2iX9tqDDu7RaCaGZf4LpUNxLO/iLKFhMdA3BqFTm+KVQy4Ni4Vy8s+cygnnURKG+Q0bdqEPhqL3Vl0FhUiDVHuqCqKnLSX16UXTVt3e5YQrJ58e0B2vO6YvDgh9e84A8H3AtKVr0pJ5mEt8wSLGamZc+r9mDJ0ofBxfhvsMnSpKUB6+vV/TdauYOjxnc9xk0vkiNbipg4gjda26PSDtF71xzNIqv+H5x30H9amBqz204+/9A01rPuqRhHL1sBnynfgCmtqHNFhtYIjhGAO+/UD7H2Ps7RpzM8fYwgGC9cYYvvFBnD+G5g4SGmaDfp8J3bcrZbOavre9+1sJHZJ3eGcP9Wg9H+WXkO7byr827+17eV6FMipuVA7wPUtjB++flqYQo+ddxJCDkYt59T4fY/arWHbVk+GKF6KWOb/Rsrsy/MmBc7p18jrSy0sGSR1X9Q230wOdvD4x2ONQrHG4RiPOP/y6+40ZgyOKeFv+32S0n3mW8KAIbvhRlXu++bjJDx8uufQBpZvpCelXpim92So69KszE+hj21fr+zo6ajyAhr4SgabPi3paabdeOFYOapqujUkXEO5c8PaGPvlkCWScX+4xOxGHI9fFvlpjb+ZcdOTQRCza8d6tKyfi8HrW+r+/BaE=
*/