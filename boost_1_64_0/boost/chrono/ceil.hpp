//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CEIL_HPP
#define BOOST_CHRONO_CEIL_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds up
     */
    template <class To, class Rep, class Period>
    To ceil(const duration<Rep, Period>& d)
    {
        To t = duration_cast<To>(d);
        if (t < d)
            ++t;
        return t;
    }

  } // namespace chrono
} // namespace boost

#endif

/* ceil.hpp
z6meJ32Eck71K9KPVs6p/kT6p5Xzg13CjHOqZym9Dzun+gulaS9toHtY5TnVa6H8nGpvyrPVZjWnWj/Mcq5L6gPC+LGUL+nvVM6p+pB+rHJOdTrpA5ScrQ4zzqmOIHmM1pwZSwVRmhayL6yHbJ5TnULnainnVB8i/SjLOdX5pOut9Nd/D+Pnuj4K4+dUy0m/ROmvT4fx/rpBuHi3iijPfkofpPVj5rq+CjPOqTYOrzyWOkxphij9dbNw9VjqpzB2ThUM8DFuCunHKTkbTvrpSs5mhfPz0OvDjWP2fiRPZedUwylNw4o1eMjmMfu4cH5OtTBcPWYPFu2otLNw3s7eDOfHn8+G8+PPk6RfoeSsVoRdf4/kLJ/Sp2mzOTszcVaXrjHBwNkL4fxYqgHlGWbJ2WdOOJsdwc+p3kv6aUrOppN+gJKziaRPVXKWE2Hsm31JnkRRQcXZwghj38yHbO6b8yL4sdSaCHXf9CddJyVnn0XwMeBoBN83D0fw6x3HIvg5iGqRFCMkZ3tFG/VlYsAXEUY7qxVZ+T7nxQj+PqdupPo+53QEb2djIvn76b6kn6PkrD3pFys5G0D6fCVnWdDr/ZlG8gpETvX9tK/I46hjHmSzP+tI57opOVsVqfZnM0nXQ8nZ+5G8P3shkl8j2h/JrxG9QvpkJWe2KCNnKyh9ijaL8WdnIo12ViWqMmflkfycao0oNWenKG9PJWeTo/i4OYD0o5ScdSL9ZCVng0kfq+QshvTjJWc/U3mTEFXUcXNalJGzBMjm/Vtdo/g51RTSd7bkbEIU789ORvH+bG8Ufz9dEsXHzUNRfAy4brKzR6LEWIPxZ++aOPvFws6eonMeSs5uMXb2dhTvz8ZF83bWnfSTlJx5k36ekrNepI9RchYbbZzruhL1mz+bw9jZ5GgjZ4kkjzNw1obOtVVytjxaHQNGRfN987Fo3p8VkX6ukrMHSR+k5KyE9HlKzr6LNtpZGMkp2nDGnz1BabrKOl6DbLazV+hcdSVnN6LVdvYW6ToqORsWw3PWKYaPAZ4xfAzoHsPfO4XGGDm7FO08BoyNMdpZJGQzZ81j+BgQG6PmbHAMb2cvxvB9c1cMHwMeIv0UJWdlpE9TcvaZKJ+Ds0UkJ4Mzdd982cTZ30nub+BskxPOviR9V0vOno3hY8DgWJ6z9rH8mNYjlh/Tdonl42ZQrNHOapA8jZ27vy/WyFlIrIWdxfJj2tBYtZ3dHcvHgKdj+b65JZaPAatj+RhQRPpIJWfnSD9LcjYfMsUApm8eMXF2geThBs7WxfIx4DLp+1hy9kQs3zc7xNHck5Kz2qRfoI6bpB+l5Myd9AVKzhZAr7ezT6i8KZgV8FJy1pPytJB1DIRstrPOcfz95uI4tZ11i+Pnz8rjeDvbGMfHgNw4PgZsieNjwMcmzmbGOY8Bh+OMdvapBWf5cbw/O8dwti+Ot7N28TxnDUk/TMmZWzzvzzzj+XunidDr5zXejfst/SSGsy7xxnmNBSS3NXBWjc71UHI2h/TtLDnrH8/vFdvthLM18XwMSIvn5xw3xPP3AcdMnE0RHE9jODsQb7SzdyCb54Iy4/l7p/fi1XNBxfF8DLgzgYubwAR+rHErnr/fbJjAczZGXN/B2ffCbrl52k4JRs7GkzzVwFnVBH6edhLpx1hy1iaBH2tsSeD38GQn8HGzMIGfc3yA9PFKzt5MMPqz5YJDWIiSs90mzo5DNvuzogQ+BpxKUPuznU44a57I25lbIh8DribwMaBmIh8DRkGv5+yVBErPjmnbJho5GwfZzNn1BD4GTExUc9Y0kY8B6xJ5f5bmhLOIRJ6zbCec/cXE2RCSE9kYsJHStJV1fM2Cs+g=
*/