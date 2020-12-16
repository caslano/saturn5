#ifndef BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct front_inserter
        {
          typedef front_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_front<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* front_inserter.hpp
vzyW/Y0NxrMirpxn3y5GWVbZW+bp99ZsemFz8DG+S0EylESPi4r1e/7RiSxFsbctrQO76Y9eGIQBmFHNGu5G86S2L492TesIbfQ8da455i5zkz6fucWalS87mf+zxDXjfla+OpRuZVz05T5+ZRtr4xaXg7EUOiXP/veNi7472omN+IiejxA3lT6mLxvUg96YP9dr37HPxNWln7450ncx8T1HiVe3jBQTV2ZJ/u93xko/dh/Nx5cvqlDwTCL9mWmuH23/wRrxTrp14VPr7eFsTwM2Q76nLrjmFzGszNZcrezvCn4/q+cZZ9roYzJ53nPq582BO+RdsdocxnYMZ+eTbvXckD5GbrBPeTtfYCXfrQz/r6L57Qz9jubXk+Fkcb1mKcZ8FB0+wU8jVye+Y3f54H2qsUnB3/pHGVRADuRBTiTS+0X0Z/pzYuDel94uDu+1A9rjRna9WpJnjXQraTLb6d7lPGscZN3Xsav477N0iG5ty8NXkn8AhqATehrjidZzFQ6o13my+gPdINMPPWYeGkI3+aslrUc/ZlOaBZ8rNIy4sie9/1zniV+V/hmZ56eeMp73G+dZyqzsXou1ccV+vlA9Y/m8mNxGcibu8Z41XKWhfPYH6YO8S7AYD7h3ATZru/67+xbzoGcFkSvItLVdFB+t5Ag+6l6xS21bzk+OCp7vtD6IPsgXKaoufOBC1tGTyFzivQHP2fidnpV/Z63+U5Q1dFv3/8KcRM72ul9zdW61zdzu72B882Nx/ydqh34Fbaa1UZmd+pEtPu79R8v0c3fjy1Yd1y8fSdsVrPM54/te9QhNNFjiahXMfear30Vevhwt6bI5yT/ncUNs9ffJ1CtJv/4G/4sBa1sFRAXSv186mDY7KT0tUzjto6rpaVeF077PkJY1nPZkQnpavnBaXOP0tALhtDEZ0kpIi4ggExHpaWWldfQ+ISo9rUI439eB9LRK0h6WVihDWj1pJ6UVyZDWNFzeV5HpaT3DdXktQ3v7hvM9H0hPGx7Ot6lRetoIafWU9WGGfFOkjZR2PkPaTeFrb8zQ3lukvRxpzDLkmy7tG2kVMqTdEb726wzXzpFWN+rP2/aQtBnSKmZIezRcv7cypK2U9qZ8tTKkrQrXZXuGtNV/o7w10vJE67+I9LTnpfWRVjRDvk1/474v/417vPM3+m9ruA9iM6RtD9+XqZKW/vusCQ1SRo8ZPGr86InjBg4O/Tk+rdqAicPTBlWrHlc9Ln5ItUnja8RXr/vrZ1Pq1ak2flj/cYMHVQv/IlU4R6BVepmDBk9KCV/XvUVK8pUvjO7Y1Z/Va8VVj4+rUTv4yYDho1LajB4/oWe9OilTMDAtrmXPloHv4sLlxMWl+C9833BtfO301DETRqf8+ptu2jLgf9+WlNE+Dv7Ohh8/iBszaEAgW0ToHtXa/g/vEvs/Le1PXTPcb0ROHDT4f1x4qNQrv6vwp774m3dIH6p/8vG/Wt1Q7vRsCZ2SWiZ27dohtVvXlqnNkpI6tE1sLzWha6fUHm0Ta9bwd2JCy+bdWmfImtymS8tmCV0zpCR2Sk3oldisY9sWqS0TW7dNbJnhs6S2LbwLJXdNaNulcUppVctYt18rF4gM98UgP9rwF336L3RqStrwASkpg0cNHT5q8Phq1VOrp5ROr8c/vvN/eEMfB+/Ro2ZstcmDasXXj4+t1np88H+tMDW22qjRaaOHjs7QGV17df21X6+8pnZo2SwxtVliQmpHfwTl4VJY/+TooDcT2jZL9Gdqiy7JqV1btujWpeWV3m6Z1KVli2bJwY7ulti2RaeElsFMv/7ZMSG2Wic36T08ttpAwvCvGpFmyR06tmrxJ/H4Ny5Mv6I=
*/