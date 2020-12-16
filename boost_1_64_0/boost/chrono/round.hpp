//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_ROUND_HPP
#define BOOST_CHRONO_ROUND_HPP

#include <boost/chrono/duration.hpp>
#include <boost/chrono/duration.hpp>
//#include <boost/chrono/typeof/boost/chrono/chrono.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds to nearest, to even on tie
     */
    template <class To, class Rep, class Period>
    To round(const duration<Rep, Period>& d)
    {
        typedef typename common_type<To, duration<Rep, Period> >::type  result_type;
        result_type diff0;
        result_type diff1;

        To t0 = duration_cast<To>(d);
        To t1 = t0;
        if (t0>d) {
          --t1;
          diff0 = t0 - d;
          diff1 = d - t1;
        } else {
          ++t1;
          diff0 = d - t0;
          diff1 = t1 - d;
        }

        if (diff0 == diff1)
        {
            if (t0.count() & 1)
                return t1;
            return t0;
        }
        else if (diff0 < diff1)
            return t0;
        return t1;
    }

  } // namespace chrono
} // namespace boost

#endif

/* round.hpp
d/eOrjrtVdwrTy1Tc1WSuUyttU5RjSPL1WOOqaqLc45KAn8h86eRLr9JrC+y8cRtTvB/Rm4YhDxE9fZnW5gAq8kWnliv6K3mq4vkfs0m7eZ2ssASKVdaW8uDNqesH9lCXmd3yHWO1vLHKLNs5OwrK2O8cruro6R3CXNZOZ3pufbViWgbSP8CoiUw7X2qe2Ps/VI9idbhEp02yOnB2+nuU+WqKer5GGzYMbJQbXdcr3Teycy7qBudZQHvFPCWqXTzFPWotQK85eoZx2ylP7u/Yt5dVL934rziTU+SbgumJ5GdtiY2wYmyFJmdQDbhPaUfSMYU60D/6CVby3mqg3xW6yYjzJfIYZY28jZrB/m+rb1MjOwsx9tbyzWO7vKvUU1lmvMG9YTrMunVbcJlDe2nl3VMayxWaF7dLkx30/27JN0lJ8a34brp9ASy1y6Xl9p7qoo3T0F7l6h01O0Rx3UqwzlP6fzXMv8ysvkazxQxWH0Iu403z1DfWIvVdZGl6qRjilrgNJuv4ro5AJlU/pA4p2gq+8hO8mbVTu7VukqXubMcabkIbd5FfmzrKNMi28k8ezv5a9Tt26j2sq2zm5wbc5F8xZUhLbExiurIZTrJXgviOgtrHOtG9AK61x7w/UqtgG6J5gr1gLVcNUNdfgvdOjtnU98tYX472eSVxI5ilvxOrol3s94xgA8oTwnqb0yL61815nfX+xbTfqCx4LHEPjhfkyxnqzVagXJYKtVK23zV0D5XbYiarS6KmaW2upeo3nEz1K74r9CHSWeS7zK46v35Xh5fPIDX6bmJl9hlwTwSOjH9EN3rp/hMcVB0lqvU21qxutxyg3rDtkANs9+o9kfdoHJjZqvP3LepGXHXq0667izbkdptjtcmSvBUl6rjpgVqgXWWioycq27X+7BzvnrAtVC191yhBvNzost9SDbtFGsXFXKZPCIWq/ky3vS9iDPPkWstR8S91rmyacRRkRq5QD5i/15scMyQGdGnREfnIrkr5oTYDWvr9Z3M5fWnMSeG7Porpl3VmcditoFu25/JBkqM0+vPtEKSnRePLzLIOHmrfFj9VdypLZap5u+F17JCbrQeFffbVsj2kUdEE/syuc1xQvw2aqns7jwhOsfcJHe5Tonn3HfKEZ7jYnDcdPmq93Gyu5fL/5zs2yZpgLg5cQTrrNMfJf2ejdPwprJV8j28n3K5jDV9Kn403S3XWL4Qt1hvkvUj/ipiIm+XG+2fi3scS2Xz6O9EY+dC+WTM52KD607ZM/ao6O6ZbbR9gm5bqo9m1Lse4LnAehPtz8Q3DK+p+0mY5Cx5vfpSFGp4e5r5qDhuvkUutJ4W19uWSGfkUWGyL5d3OY6IJVHLZYrzuIiLuUU+5Doo7nSvkR09fxPt4sbI5d4XfP2ayh9KfdDs+4YD0exUZ03odriWaW567hbBDsVyujyE94XeKI9rJ8QR002y0nJKzLIukJaIE0JGLpK3oi8sciyW3ujTwu28Ud4Xc1KsdS2WF8WeEi08o2nMKuJyj5Hdv04cKO5N7M62SAXcSPfr7HHhzaiz1RRlMU9VK6x4riOvU/c7SlW6c7s8FNNUNHHlijtcTrHDVUhjVSzL9yf5qzytxSPydvW5bGB+E33koGwXuUfucLwhuzlzTVxn4m9CdsggOxQybTeNAyOoXDfv+6+4WKd962qNN7NuVeNUT/NI9ap1uBoWOVz9wZGr8pzjfHoQ/1EqY61nnHjaVGTupE5aO6vKyE7KGtVRLXZ2VTHuPor1IP5vqp4H6islTHudfsN2y/5sn2a6bvRsvu1KFF1UHkbIlaqv+taUIBqZL1MV1gSxwdpL/RjRVLSL7KEWOLxiu+M=
*/