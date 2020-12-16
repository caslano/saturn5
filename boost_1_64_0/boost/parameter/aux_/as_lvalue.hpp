// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_AS_LVALUE_HPP
#define BOOST_PARAMETER_AUX_AS_LVALUE_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    T const& as_lvalue(T const& value)
    {
        return value;
    }

    template <typename T>
    T& as_lvalue(T& value)
    {
        return value;
    }
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_lvalue.hpp
CI/Bi7AC/gqJi4DYx0v4s+KOm3L3hA730lr0kxX24/5V1rWocqkl63/let4YNoaBsAdsAvto5QoHwGBZb9kcjoNhcAZsARNhazgbtoELYVu4DHaAt8GOcC3sBDfAbnAL7A6fhz3gS7AzPAC7wMOwF3wf9obnYB/4k+TrN9gfXqM974J94U1woJt9/xA4UNZtRsAxcDCcC4fAm+BQuAAOg0vgcLgcRsI8OBLeA6PgOngD3APnw2/hLVq+4Ar4K7wV1qNs18OmcANsAR+EHeFGGC7bPWS7P3wYDoAFcAR8TMs3LIRxEk8qfAIuhU/CFXArfBxqx/sEzIHPwIXwZbgIvg4nwEo4GXq4cx2G9eBU2BBOgwEwDraC8bAzTIDdYDqcAjNgFsyEi6EVroQ3wTuhlo974ES4Ft4It8NJ8EXZvwc+DUthMTwm7uUwBJ6HofAncXe8l7XsM9qx3McUVXkva0ytS/4qXPR3xkV/ls9d8+dr8Lff7XJ/nCviDxn8eVXx18/gL9xFfxEu+ot20V+8i/6sBn+lVcrlrMFfbjX+It0v+ct30V+Bi/6KXfRX6qK/Mhf9VRj8lVfxN8FiaH/V+Btt8Gf5wjV/vi76C3PRX7iL/iJc9Bddjb8EY/tz0Z/VRX+5LvrLd9FfgcGfpYq/HgZ/xS76K3XRX5mL/ipc8KdsDcVfM5PnqR5iR1UbhkBPeA2sA3X751Nyv2jynObFerJOCTaCu2EruAcOgq/AIfB1OBS+BkfKtj7/L/GHmIw7Z9eR5+6y3iIdNoFWWTcxFwbLtl4fenzVv9e7Qvw1N0nXJunOg4FwPgyBi2AoXACbybY+3v1SniuajHcfpTy1fY/BhnCzrKcohC3hFtgZ/hX2gkVwINwq646fgmo+Gc6FxQZ7twJJN9Rk/q+ggaQrzx82yzxvodgDPw7PynWu7MvL18E3FpsUVb8WeV8H7KHmjOz1+BqMha/DZLgXWuE+aINvwnvgfrkvOQY3wLdkfHxIxsdvw92wDJ4X91/hO9DDzR7OGx6BDWTbH74Cg2Rbf5/E187nI3eLPeWr0FPLN3S0h/ivndvFuclzc3eZh/aEjaAXbAHrwg6wHtTttb92vp5om7Svp6BaryPtu1jWE5XIeqLnoeP+skziyze5v9xfzz7ffRA21coXtocfwC7w71DNw8Me8G9wsOwfKftHwTIYLe6TxD0WHoUzxD1Z3FPguzANvg+tsBzeKf7uEn+O8yP/tFxHTM6PhlIvAbAebAybwyawDQyC7WFz2AE2hX1gqLwn4Bo4BDaDI8WfPu8i6UaYzLt8VE/sCaAn/BSGwpOwJfwcdoJfwmvhN7A//BYOgCfgQLXtmHeR3w2Hq03mXc7K9fIH6AEvQD/4EwyBP0u6F2Fb+AvsDH+VevsN9rOowlPzMm5wBHSHY6AXnAjrwgRYD6Zp3uFsWBveCj3hKnF31M8Zyfdsk/p5ooG8fxOq+3XYCj4Fu8BnoVpfBvvCHXAyfBpOhS/BJLgLqvdqQrFXkt+V5lpqYq90Wq6b38l7Gf4J/bTykPUXlVDLxznYXys/GKWVG5wg/mLgeThFK3c4D16AC2W/3s99J+u2TPq5k7XlvbzQA34r9rHnYYgWLwzV8gPV+mDYU9z15yvfOZ/XOsF1Q6UDa8PPoOO6nCvh0i1XXpfrSf/tDX2gj5RPiKzXrC/r9RrA5uIeBhvC9tAXdhH3rtAP9ob+8DpxHwAbwaEwAI4U91FaXuB4GAgniXssbALnyLZuV3DGfhwTTc7DNdJPrYXBcJ28p+wBqOaVYATcBAfB9XA03ABvgA/CGNnveH6ZK+ktM3l+2ayu2I/DhjAMNoatYSBsAZvBVnA=
*/