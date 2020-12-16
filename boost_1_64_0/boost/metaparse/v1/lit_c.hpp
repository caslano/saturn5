#ifndef BOOST_METAPARSE_V1_LIT_C_HPP
#define BOOST_METAPARSE_V1_LIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/literal_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>
#include <boost/metaparse/v1/impl/is_char_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C>
      struct lit_c :
        accept_when<
          change_error_message<one_char, error::literal_expected<C> >,
          impl::is_char_c<C>,
          error::literal_expected<C>
        >
      {};
    }
  }
}

#endif


/* lit_c.hpp
no/A94jS81HkK836SiejkVU0TgjDT9HIIY08o5FS8iiqdtiEeU5UeK0KbwvincRoR1WeU1SeUzHPaYQH4znJ6HRWvzNU/c4Mw0/V76NI7yzqyxX9CjD9uZKO+8Ckq2erepyj6nEulvtxGs8r+xiDAe7FIOnuJyry7w1fm5IjmSyR8oGJ/08ivZ4x+epPD/oIl0snfrdWUe/B1PpknoZgCfP2UKuqdyK3JVsg9vxg2k9FeleiPbYx2NlCDtLR7sJ/ZDPPd79NTe33Be53qcKurb6whANlgThI4jbPxW66rZlnnz9t6VgWkY4dQzMFMMXufu9UmEB+JlxdHPAQ1AfnFmiLaG5RGzAfgXUidznEfttxBeIjhi3P1h8LsTnLJfAdcQadubhveCkbH2IV5nvzy/c3CNn0snjf1O6Xqf51uepfV2D/+hz5OuXGgkKuSFpGECrrSqThrY1/Ab6N7S+I9Y2JzjYs84uIv0GM6S5Rh+Z7Q6XY7qvcsdx9/N4W7dAYPc0xzcjH8v7cemy7ie4YDt/znRcWody/xOVeZf2mKlleo2T5ZazXVyr1NVtWfwHGsYFiIZmnAhWY+trpqtzrsdwWHFe/iuV+LSz3Q2x6Kp8vGp+E+iWsgSZzEMJnYD24H/INJo+pqIc2p9sTbQbSzDLJwDP52LSnqsaXb8M3/OSeKtbhuyS7CnFIcVfRW1cctsoGBAXAsc2+5+n12PT8lJDGjUhjydg04u09K4gOhyKtm2m8qESr+4j23gPjvZ2HdXX0wM7GslVENDC5JPcfMB9hN/x7E+iDbXu/z/x9Vx9GB43LnEfYTbafJXMYc3eLnRPmRjD9VtemsYk7wm9zbRtO/PIO+LG2r93O+9o4xuoNSu9/iDpTRL3/EerMj6sYg9+JLv8U6acryPFnrhx9ZBxvXjLVnS/45iYgVwODNKSTMLJF2XvnGO5k8otgfXJJmGuICVMAHGpg4xLtvN5h8xOMLTM8b+Jxib/gZY1zbmZ8zD2Zj/krZgN+rWzAb8LwUzbgLmzP31bss629XfvH17SuWN3hsUMQWiO5kvFxN+PjD4qPe8LwU3z8Efn4E+J2VWj3Rdh/nO3UB6ayPkDtTH6LtzZ5H19TGYcvdx31C/ib6vmA6i8PYr3ux/7yENbrYcSrMM/MJTdlNlL/VLByse87tC40IfSYJ+dqbGIP7GF3k0ksm+rtESHtC/5PNvAvxgaqNbXHARZz3J6ZgqobbNdWTQEdeILpwPT/wXzhAabrTypd/3sYfkrXn0KdeFrpzv3Kt3kG8Z5l48ue7O9fqfz/wvzPoe49j/lfYHkaVZ7tmOcUzPMS5vk3y/MelecVzHMg5nkV87zG+shC1kfeYPJ5U8nnP2H4Kfm8hfTeVuUeKOUDUIs3oY7KPZuVW1sn80+qs/nPQb4nY/4pLP9lfH+pju0v1an9JfiGn9xfQnq71I3Z1+U6OIFEH92N+IK/ia+wqlcd8hGqs/WqRz4iiDdbrFPL9ejlbj/M9ufAkzdRfItwTIrWMd+0yjX3R6m94G/it0nx24z8xpDf3ZHf6YjXVsFuPG74Vf3a2gC5rt6G++R7sHpMG+daw+xyfGB5tbw8lNsMLrdxzvED9aXK9Ut3r6qOfE/0a1DfrE283OWZ7OledYbHzXZFFsfSo0v+kfRbjI7PcOEwH2dzwFklGdA8bxaTQUtV+7qg06yv7aP62r518FN9rQV15r2Ia/s70XifojGnDn6Kxn5IY67ST9BLYWfmId7+VBbYNJnnAMyzCG3LAsyzUNFermzYgYi3WOHtp/AOQrwPKrxFem8H8ZYwXpuYXA5VcmmF71Yllzak0a7KCim5dCDeMioL9uQ=
*/