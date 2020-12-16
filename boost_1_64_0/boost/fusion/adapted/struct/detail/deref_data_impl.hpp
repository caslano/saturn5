/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<struct_iterator_tag>
      : deref_impl<struct_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
6QYljDyu++SDsyUflF+FHs6TPTwHyPOBEo+E15v15XK2/yvY/vHOlXxcxPnRVYaeH1xj6PHQYsqBaykHrgOXqnJFfy/zQHCNsqmi5303gM+q/la3Y7QVNc65WeZl4C2GthP3R/BUWc/m+i3en7KDgzJV9k9Rpsr+zXKwGLyL67l3g2reA5bLerasI8t6tqz7gSvB7SDSpuzEloN7ZX0bbISyeAhsAj4s5QA+IvGDj4LxYIVpX4NnDHV722HY7Ws8YPFXSX+da/HHc3pq/F3p8NfW4i+O/k6pxV8y/Z1Ri7+lUfqror/Oh/bHc1/u5XK/xd8g+jujFn/z6a9zLf4qLeHN99j93WYt52qmrxZ/8dXRhReI0l+FxV+1Ix8T6C9e/kZ/PVzWh4ooB4o5fwxa1nN4VsV4xmU95yuuI/4N7Cr9qUePF3/guOcA7Xn+k3LkR8qPn7i++DO4iHayb5QAOf7yefU81O/V6wExtLtzlNccp/OMiRr7xTvWZd7nOsouUMrlQ3C49N/gOJl3gxNk3t3ALJ+lDK+bS/k8z3WrzR49bnnBUj5V/N0HLuVzLn+X7NH9wHmgpHG8R8v9CZyXp3j0OGAi5+WTPHqccj54v+QRfAy8gONByCg1br7Io9dHJoNShy+2yGOe3TC2usjjJbSD9AdQnt8AdpX80K7SjV4th2/16vd0G+1OL/Nq+XqXV48/7/aqcaey5yyR3QceBd7PefdKiUfkIthD5CLYT+SiV483HvLq+eLD4k/kIthR5CLYW+QiOAZ8jPahHwcvop3nTNp5LqSd52to5/kmcB14K/g01fWul/kHuAFEWpTd59Xgc7Qb/Tz4HLgZfMmr7D/Tfi3Pc/CcR5nDfu0kL9edvVx3ph2si736/V7i1ePONK/uz9NZjhlcv5gi8YLIixqfZHEelwvGItLpnOfM8Op+LE/iA/O5jlHg1etbRWAOWMx1jBKvHrfMot3ueeB68DJJJ/JwJdgTXCC/BxeCsPEOu0e12zhaVwg/K2vXN75xZQSbRXge7HJoe0X7u0S2WRTX1UUXeRQ2i/auNO0WVdToKK+D3aJo9JR3AqmrnHaK6majaAvtFO3uZtdh3rx77faKgnCmTvNwW0UHV5q6zQ92d9FvHu/UcY6/o7F0gXPaLDLtFZm2ioatql3/+Tb5DZiyytSDHsD/98VH0oeuGiztFOH5KndbRZ3wvQuY0sPdZtHmHqbNojWrxG5R7TaLatOjvhXhBHu661Nf1DNcp/ruVaa9ogOrtM2izbXYLTJ6udsuat+L9ovKw+0XLYmggz2uvHb7RQ16H1ovez9wDFyeqy0juPIjq6d9TLndllGcxZ7RIHAnmF5u6m9Px7MAXGm5my53d9tGFfi+BP7XwG2DOwAXhw5qGFwe3BK4CrhtcPvhWj+IfMKlwgXhboFbA7cNbj9c3EP4O1wKXABuKVw53Ga4PXDGauQXLgEuBS4ItwSuAq4Kbh+c/2GEA5cAlwwXgFsGt/lh/B2u0SMoK7hUuHlwZXBb4PbBNX8Uv4PLglsCtw6uCm4fnL8CccMlwKVU1Ouxr//Uf+o/9Z/6T/2n/lP/qf/8ez+/kf7/YF7xVDEA8Kv0/4t9v4TmWMNMFt0+KWMmpA1PHJwycXxiWm4wOz8tGKTOyY79sW+lbAQi2rSp2RnBkqLstOCUPNr/29bdCOlQSOf6W2e447i+eIbcl1uv1pgskUR3B63mLmKa1rlpu5+0zROuazMe+WnCuGwZMtz1a9ruJyGvg/D71udJeShFnfihXUdEvJfr9tQVcAJcF9HT5YxTaQqo/a6lNT/tffoPn/G+78dw3frLJroKO7fnrDRL+LXriKnRaTM=
*/