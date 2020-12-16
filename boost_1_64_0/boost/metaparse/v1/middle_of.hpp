#ifndef BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP
#define BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of.hpp>
#include <boost/metaparse/v1/transform_error_message.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>

#include <boost/metaparse/v1/error/unpaired.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P1, class P2, class P3>
      struct middle_of
      {
        typedef middle_of type;

        template <class S, class Pos>
        struct apply :
          nth_of_c<
            1,
            P1,
            P2,
            transform_error_message<
              P3,
              error::unpaired<
                get_line<Pos>::type::value,
                get_col<Pos>::type::value
              >
            >
          >::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* middle_of.hpp
L+S26QDQRCiusNmtGH26MgrqL2jnutjZAgIwW/FgxX2JjqWd0MiFLZwMh5E8H/bolFlre6hO8MTWg3JDicXz5xugXA8a7Op1gdx2b14wbx6aPYS3WFzvLqES7Ufc8pKDKeQV+wCtcw1lcqM9yXymmEskOwfNtsFQKpnja2megXXI7ueS61N5cA+Sg51LOb1UFniX/KRFev9CsY6YAwsWPCbtBmPSo1WOSXuUWc96DMcjz3/4ixiPDuuAYBW4rKerdWXJpisY0B5j3UEOXy6NMmmoH4+jfsyV42gG3MMtKfTBnnD5NkMrtAX6YN563N8CxlQ1nhKknF+C/qZ0MqWt+TvtNxGfaAeWZkbB0Ha7PDvbqT1rvX4vEGC8Qd6fDuA9vhJuIYFzyMQ/h1byB7y26l3d1tfTQU2owdTHn1Hj77PKH/gnjr/PVbQFEDAAdw/D8dwiLdFxGMV8PM/G/hfYmsWLar63vQ5+as3iJeTl35V8AbSHfFotIKhzr6h6v6rq/RqW9TriybvD7M2d5CvD2j1sc5l2n43t+qZoVzNZgfHL5Qb/LquHvWu7OkDxSiMV+0be31K8v614d+ot7zXwL+JBfUnuE+tJ7rX1Uu6T4Bt+Qu6Tkd4UxO0R57cTo4PmCmmgTXepuTBrVxE21YUNJvMJgGHeaS7MjqttOK/eqZ7Nq8e5fjNT+P0nZdLMrte6Pr9TulvjXaycqWPIfH6ZGCd37u1lwU/et3ZBeUm+6Bz6ri4POZOtdBfybvXvzL6H3PzFkn0P83oCz52Dq3KSbwJV3FeucmwwulZfT7oWYbrWoHQtCt9RpWuNqGux+jFjIrLFXDaTL1WEw4iXZsbL7vUy9nk6fCcDYp/fjTzsgfhnClljEQ4/7yrjoacyX3FPoDEN46G9nJ4PFMJ4aDrDlHcB5PcV8zncKz8Ifb8ZrD2nVymHYP1VS3z0SfEBZD/gb5LjrHppf/bGNtwL/jVY+6D89kW84LkRhOmn0iWu7RfZuPfWVzr3lM+PeBnhT97n3ifaGPLD9xz43RSWbbwf8jgX8ReV9wnEzfACgjo2j8lm/4p8Lz+qayleU2v/pDOsnq0AvqfgeucCgB0dcn8Al3fYzIe0KfC/hViPRZjfpC1w0/AsP6Qt9upYw/V4MDlQXA/RGRDEwuIzahEOl3KxOSDGxrpmhnBBr/NZo7FiXggwhQd6Df53EjBJ92NuGyZGUjbOEJIdulPW4uPIwONJ8Bwdju10Rwncw5RFdOT5/VDnFgfpw1QMCkmO8P15oxeOSbDwwRG7D/0BgM8za8TgvuThWvPBzIlu/9kF+t5BrO8tcNrNilp731pPEdl3ufuYxuHfmXY7mPoZ/E06tkT1vw9h/zsE+9+hqBOtXv8T449phta83fLi42PWmwyVxo52PnZUOd8LtNdVjjuG5w6qG/xNdT5M1Xk51nkZ1rkT63w44YFvS/lXqPwrMf+zuM7UhflXKTygL3yrIxGvh5XzFiunj413q9V4twa+16jx7iikt7Z+TP/a514TiOR3tOL/GMX/sVjehxFvfqV1K29NgT7dcsZYi1QNreE0Nh/P2refyW1AyS0B3wklt0GsRxJxl1Wek3JHxeUqMAX5Ws/4GmZ8pRRfG+B7g+JrI/I1grht41jTJ1ubWO1eet6WKuTRH5sIxNOsP06rch9G+p6jKR7LVGviM9h9c1ne38fwbwPt2zjWS42Mcigje8cMveOSB7iRZx3CSH8nO4V6ivWfYXXVXa70vmucAe8yLvauQs7eXD1Ic49apz8F65GtYPZLsf6bRP1xgwmmanA13+p2K18JM/au3L4RnY1rz6Vgp6F/xMG9JKBt7wX32nUzn/M=
*/