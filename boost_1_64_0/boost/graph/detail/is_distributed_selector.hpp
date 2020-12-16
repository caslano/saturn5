// Copyright 2012 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

// Selector to determine whether a selector is distributedS (can only be true
// if <boost/graph/distributed/selector.hpp> has been included) so that we can
// disable various sequential-graph-only traits specializations for distributed
// graphs.

#ifndef BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP
#define BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP

#include <boost/mpl/bool.hpp>

namespace boost
{
namespace detail
{
    template < typename > struct is_distributed_selector : boost::mpl::false_
    {
    };
}
}

#endif // BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP

/* is_distributed_selector.hpp
QNu6Eie9beu8D+/D+/A+/pnHH379v+rDuf7f0+36PzG36//E3K7/E8v0+j9x9+v/ugwfld9wivk68jrF/Mz77nXMX9+fb64nq3tfgcQzv7Y/2enavqHGSp9p4zxKVPfjr9PX9qv+Xj+Bp9bLeKE8p7zqer9j+Z76fvz3yOP5fnyd3+36v4ztiq/J/BI2l2v2+vrkhzL/J+tGRo751XJAjedrMSbJenNaaxi93fscpOwiTB2RZbPYPI3Lu1vmh9qO8ypnsTCO7t/YOw/4qIo0gL/dTSMJSAIESAADAqIUA1KCBQkQTKQFEpAiJoEEgoQQSEJHQKoeaA4VOEFFKeIhioqKgooFRUQF5RR7VxQLdjzb/ffbb+dtySrc6ZXf5cHkv/PNN+XNmzdv3pvmfED3qfSGf4/DydvbaEcv6d8cEzAW4A3x/wVu74Scz1+J5DrRS3WF6jdvBR8TnZNcvntTJmg8N90u6zVynlGOBo5ws9/7UyIvMvuxn3eH2z5CxxjY5xDNbKv7+Xp0nqNI53rbbt2scYTre85Oq6p++QSdt79b0lnTtZvrcdDhwC9ycz3OC+ybNnuFbRV/zVxRjnjffvcuuUxDL8GSoGMnDqDHP9f9hP+042fCQ27CT/WZhy4ec0cXTmarXPzrOgz7xH+E6yH8f+V4Ff/Ijf/OVuC6jCn82ih+2riq6Kc1YxZ2iE59KUtR8Z60+/atJ8m1qE3uxUj+D0Z2q/g5zZXEvPvJlKQ5DlfQHP0EvZbPim6Yayfp/sFxIOA6vey5Tvh1Sdxy1mbtzb9I3FVfi3CP/uRi3U94CPprRP9ntdt5G7g/fj90PxXdXtoPHnxfyPnU1jh8+lOHS1msYdbNHC32LpwXdhPOfs5rifQNr0JnFmXORYGPdV2WExseHusazl8Jc3icU/ffNHtwqp+1+Nnl9lPzstLAPTi94R6MwO4Jd6+EmxE63AT18yN+ltXFT/Rlb8W6aluBYV+Bvelx9AF71+vc5bf3ZsD6ncRzld2vigxij8LPo+g9i/0xeABuQ/aJ/n6c37vjj2f//VhAPsg10P0btwTvJTlyS3Af5mBbZvoSB2wJXhehz5bgvs7zbFl704e5Jbj/s+WW4P5Ppy0z6bvUlnXy9k0uRebb98jzKKjvcW4V6w8sqWL9gcoQ/Yyr/sl1A/7b+th+r76rE+2jCtWH906MWz5z8OP5L/8yJT2nOPrNU787e2SoPqE/vm+v6j65P76P9kT75KruK/39+upOtE/x1/rqOmI4pF5f5Zl/bzn19zv83mXLqW9t+ZeYVU5tP2r7NVXW9OQ7jn66aadrDpwBT4Yd4OmwCxwHU+EU2BUuh73gNtjbZ13Rx+AFcDfsC5+B/eBzcAB8GWbBV+Eg+DrMhm/CwfBdOAS+D4fCw3AY/BSOgEfhRfAbeDGs5SB/YSJ8CDaCu2Bz+AhsBx+FqfAx2B3uhsPhKJgLR8PR8Fw4HXaDM+EYuByOhSvheLgFToA7YAncBSfCF2ApfBNOgu/BcvgDrIBh5PE0WANOh4lwJjwFzoHtdU2Bs+FlsBdcAPvC1TAHXgNHwRWwFMoaAXAlvAr+BV6j+n+Ba+B6eD28W/0/AtfCvXAdfAuuhx/DjfCo2r9S+zG4Cf4Eb4VRumZBfbgOtoB3wNPhXbADvBueBbfBTHgv7A+3wyHwfjgS7oAFcLesSRCyj0X6Yb6GKQecVi+Mt08m78Dx96VU96OcWD9K9ZoE/399J9X9Jv/+fpNZB6r7TaqP6qP6qD6qj+qj+qg+qo/q4//t+MP7/9t3cA8A+Jf7/w8nBfX/Iwvq/0cW1P8vMqfIemZmZaTj28hN/33P9EE52T5h1LD79Y0=
*/