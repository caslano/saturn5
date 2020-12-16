#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete1 :
        foldl_reject_incomplete1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete1.hpp
+kf4Do2zvtDBjbX8PeaYLK/MC+XRWLP8kt5H/ELuB8bgHCf67RjTbyeI+cqeVX1S9BPJIGzrF2t1vINjVHny70O6A/R2QR8SLXV+8wlO87cqw9uXaqN1B+vD+0X+lxvfaExwZq32VbtnZ75fnMRax+rU2TF1PD/B/1i/OC7Kudx+gjm65txV9Afxhfi2Oo7ChbV6rZUowX32YtPvqAN8cT8QjUtq+XzP5W0SP6Kjzvcu4/4HjGV8uZmr5uIb3Gwxv11l7MLVSv/p/e1IJoBRPtN0PoGRTKBT9TE6eq3nkcaB8As09W429V4v6t0MmlIXbwTNWYLmTYbmtw3NmyOagFG+slO3AH9M9EbYBK9z+2J/sozvtIs+0X33/VpegzOOxcsLfsi8GLjn5XbWXUPH4nvdvVPUOyZWX3y9d3F/CTwT15f1b/h6Sf9+JmQMvjEeOM0yi/8mdS/6sibwfelkfj9kTlYX8fT0t4xklBYx8B4M+9GvYx8K/+7Lxtf7RS3hjiBm1JEqnp4/Y3B1zwka/V0RpBcGjWuj9C+J9tJgMPse86PYM0bpx929TMROjNZyvxLrhCeDloVzP77vdPfdkpcJnGX2gmR34uMnPjLUXDVC+mFcADOGHjNj6DfcnwSLj6H421o5D1sadGZsbPm0gGNC2fJUltqr1xvPUJ7UiQegI+/k+3SA71uDIk5iO/q1mPvVyxD9GqVrRb/+keqZZGJjrjV92xXTt8+Jvu1zsp/+8ZlW9pw1zB2pEZYN34My/faC6bctot9eGKLftup+Izxzxm36LSH6zZZ/IabfXqa889Wd57XTpOzpzvi+Mk2xkafrc5W1+8l0frB2hkwXmb4sMX2ZMH15OPoyegf9FdFvRznZa8EjPcxd3uHL+DfM0U9SztuMnF8TfbVN9RXL+nWe9015inUg+mFbTD+8LfFBy48XtqmF6Kf3nEwgN9fmUUTgfSGnE7PnAlGbOe3aLG1WEmdYsh3/xh7ng9rhfIiHr8PNHaPqeB0wuk6da6FuxNMhWFL6EGDtl1fH8aAY3/HL+EGdLLMTBW3lOdeX8fQzgV4Djq3j/mQ8LYddbP25/IIu1z+OYHtSmbE5PMsylu+xwUfqtiObQMsmX+PbekCf8QsprexxnrfHRXXyXtpo6jMxFkB7gqJFfpCi7gxwBsX/55g1/B6E72iX1g2nT+09rWvSPalstBeRxjhN1Onz1OVEJYM1U3mdXlNVoM5KlJk6Kj726mCxw+6nGAp9g+2tVB/pa5Q/NpvfkZb543x+f+d6V4Dp5HM+FfD5J1B+UZjfTYFR0xv7QOdUyi9xbUZ2ZBPPpPwEnTGRI1g2nQxWU8bAWhkTsxZ+4FGbJgVtfX3Cf/t8KjclrNf5vPu8MpLFNJeHq/kRvSTlz3D5bviSzF2+66OPUGdX1XEPzXI4YYzXqI847fpo9lD92k6f9TpElE2VxfNlDfrq7FHyrL+vrYPg/F1H3zG+tYj6ScQmnuxjDves6exJyzOh/KAniP4uCtLZv0uwNh0Tyr0PfzuZr8PfTtYd3X37Bllakyi9jtMk58517jtCFPN4Wm7MYyffNIXMJ31JD8h+nCX68aRi54uPILqhYvRk8+eo/L5s/nyVvy6rDwuDdur3wW7JRy3Jd0kQST7I5i0NujPZDhH3ApYhLvNk6tcJpAt1QhdWOl0QasBrplGFu2FsjjG/TUP+7PjdLdgLaSqHfTPH+RuO5rE5tHYOJiO9iff7ai8/Zpi9/D7MB/Zq1v5Y/j3eNJ6HfB3AtXu/6XWyXfY3fLtmcB2YI/j8Q9Yxs47ba/FsHNtZsbad34tabmz7bEH7XUdT0B80tA+ATT6v2J3/Dj8=
*/