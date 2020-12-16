/*!
@file
Defines `boost::hana::EuclideanRing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP
#define BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

#include <boost/hana/fwd/concept/euclidean_ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/div.hpp>
#include <boost/hana/mod.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct EuclideanRing
        : hana::integral_constant<bool,
            !is_default<mod_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value &&
            !is_default<div_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

/* euclidean_ring.hpp
C68XsnsVC8gfWI/bfSCNeRTL/y2Q11ksMMdAzz7f5fzSr7hMGuVMV2zAgdZ9eD9BZlP7Wa9L5nDuG7Idgbrpt8NcO6uLUzc5lrvrnCgaFmn3a9aZHSTeGaGdZnceTcsEBYgcer+il+AXHfbkdVGJ013/z+tYTn/1ErPkHR6L/ZGfgP5zh3n5ENXSOXbPMadwjTnpdZVIXGi8m9XFD7m06D8mZeHgkqvqU9rTuBNC5XVz/shhPcKZHkUX45oVt1o6n3/QznfVRUbs2jZX/+aMp4zorhSrJsr759r7IfZRJqVFlOVyjpkFdGyQxw1tU7a+fFTbd+pPIGwn57jL/JE7a1SKIznJrKZWClf3ay/R+bbcr9XS8p2+FCLPei8Xhdca79Y39UN+nVFpZsWdVjnmuI30vYbM260NHtb2tMk9eE+RU994N9Mf2/aoTJMSYFLBlXOVb6NzfLkPr6317G33HjH0MlFWx3i3xx85s6hq0Q6TkrQrZfO1mjtpf1bHiFs7QU8OryWPXT30fJ/0ohw7fog7cYzTpKw6XDJ/Z0cj2/21jZi1sc6herMf15Hu8i6S+7O5/ujfickmZirnwj2fpUOzaPZaRuxatx42fclyQ7uJUPldxRR/9HPTHp5EBVfOh3ecrg2XMWshroufOsjQrqKvjNnuj5xhVDUzG5xLV/Mo/UrHbhm71rXftryZqSPNOHSTfb3CH+2dZFIiQFkux0tH51l1jXjradfMHFwoU7V0EeHnGu/CzvFLvCY2NRfumbu6rvtZOiEe97J0Fna5L98f7I/Y081qbCq4Uv7DCyziQnnc1pp32VvLrze0k8gNk+eddf0wNk1KH5OSblJyUy5byQnX3t3WoR5tHS12yNFafkDVcbvyfYfnHZrBx4hzaf6H3rgs4OXSHD7Xpck6mgRn++GDYW15rNzAKlopyy0Y+vb5nHP5PKugdNtsb4d8s5r77flW7Ttnto0f3J7KY9FGNB+jlPnlVYErue0bW4VDscdyrujFZTaxiumKNez2aSAv15QqYnPb0dPfXMXWnHLlKst9NuelGI6dJpPrKfbm7qvqcz3Daa5bKOss4dhujr0lzckrlpLRtTmPRchuVuynoK8mcU6JVlYRrljYc/1TuS5k8Yp9HVU6nvsG2TTFsibu+4DrcpFnDDu/b3Uvl9naKkIUc2SI9zm+NlaxSbE+owuu43pebBVlyuelXZ53NfeJdlYxR7Gkzl+M4nqS9VbKXFlrRgm3Q3ua51eWa5mx8xAvF0Fz+UpfCr+SAnbVhTrZDGW5JiN2zUH53rkdIvU+yHbvbzvsvNylNHep2OTGiz/jepIdUey7glNTeNxBN4v/rJijd14GW5RVPF3bbc3nFwzgMXl3q/bdBNvRSy/i9nNcRm0b5bZO64dU8LpOo+/SlM+bdvMF5/FxkaytUqblw5QdvFwGzUEqy72dO/17Xtdk8xS76Yamb3F/cVhFH6XMy+zLeFvJvdMq7lFsYcw3F6Dc89w/yfZY3HZnWLiFlxtvFdcrdsXCVgN4e8+2iodsbpvx4CM3cRvdbRVfKJ/3nuXGUF4v1JEKFHsj75K63A6TrGK5YpM/iunLsefo2y3b+xsKvuB1Rra5ltsePvxeMbffVKsYpCx39ZoptbkuZKGKlT7cPJn7C5lNsZe2vN+I4yM7rqyXBQmbT7NNo3l+q9t23pT/MW8rM6zi0wC3vVD4bU9e7mGr6NzSbblz1xVyG71qpTZzW86rnw7i5ch+USzwwZ5vsy2ltq3jtjXTd7fk2N+2iuHBbivsN2whytfP/Wy9VcyyuG3+eV2LUa57bqNPaL7+HLe99MUL81CueN4PbrMKSjPNtu6BtGs=
*/