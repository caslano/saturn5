#ifndef BOOST_METAPARSE_V1_CPP11_OR_C_HPP
#define BOOST_METAPARSE_V1_CPP11_OR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <bool... Bs>
        struct or_c;

        template <>
        struct or_c<> : boost::mpl::false_ {};

        template <bool... Bs>
        struct or_c<true, Bs...> : boost::mpl::true_ {};

        template <bool... Bs>
        struct or_c<false, Bs...> : or_c<Bs...> {};
      }
    }
  }
}

#endif


/* or_c.hpp
JLUAu8waYOxVxX3laBhXh73vtCfyZljfAx9fAvOaeHNZX5x6nx7XYjYaHwkV8MALWT3fLa4ZPpEfcq3AHXKKLbO6znB500QOnGzHPuddY77jYOktdOuI6bGwMYHGHK3u2CRn5sTCQ/RqX9pg9GQYz5YHRkYZlR4z30LN4UEruNE7Eo73o3vM4d1ZzruPP+6nNS9ln8/xq5rkGed4pzndS0v9fAfMzga/psRC1df8/l0kfALPHsMLc9ijzIOuPTASrijCZmydxO5ZxeVwNikf6ES6qnVMHOKy9ff5/2QIx2HEXu+yH7M8Gh6rIG6ayHM68UV8PVqOfV8XZ4qJF/fS2i3hOO5f5u+P3RMJ/bbRsKv06XdGwsNraQA/O+LE/mx4CR34mflcTzctmBHCnfJ2PDybL07T6Y4Wao17aJo2rTzrmP8T1GAb6bqKS/ntEuN/lN6bi/OWwuoB4iSn8++NhOVypyo87r2J7v8Udu9lNxh7R/cQFh3Gq1/43Tg2f0CTHzeG4jRQKXbsJf/Zah8ObPkkPDwSCW8+b51C/E8dErE2EQmtEj3bpAhcVp/97Of6jfD1tUj4Spz+WJQf6YbOsDtCfzW6Sv1QLhKqbYrQv/zwked/zOc/9eBv90bDeDmy7YjrPx0LFfigmzlVai1fjb2xOU3EJ23xf8Iuu7lh1QjjONnPueBEFvzVgTaszz5XDoE9n8fCJ2Poo49pflzRNI3GS6BD8d4q8TCNf+9bi9vfjoWaV+OARnLxIWsqS2CMcy+tyWZdIyHpbpyxgIYqKU5mxMLv1RV77hDLcvjbPZ7R/nQkHMPT0cYwNoXuz6q+Tnftaf52CyxUz3VWT6R3iIZoDVielQ0q4je2vQTvrOiH2/0+RcwnNDX222me6/Co+X/Thf44a075PPua1vjEdzeqIRYuiobr/b7BfNZcQ6eoi159wnhuxE8N1Co0SZdq9AQttAemdjCmF76iFY5HQ/O2nod5npbZCZflTL2b1UotdYab03clcDOfLLskEk7S/neZU266I7UODr/bz4X4tQds3SXP89Nq8vmbB4ynZiyMbE/vGufU8WzwZTQ8CV/T2e+wWvOVYbFwjIYdPoYOr83fy4wjwTv7h8IttnlT3K6l/Xvgw7QF/L8j/mybSBikdr4Ot/SsJmdm60yri0e2jIaH3pRv4qgbe1eZzD70XE2xssP3npDXD8DlceI3Zx3r6t8Z0wl4WQ5Oia1G9FNfsT6Mbj14byTcxAet9qhHaYeh30fD7WrPHo95coRzrqHbRsDuyGlxg6P7w++EnNHw4QQx/ntaCO6sXgIr3oCR+ifhlL1uTzp3S7hbJRqq/jaE+58VO7TZfbi/7pPO/TVt3QGeP6DuoZd/VndNyI1fb1IL4O1h9M0wevTxb2iMvOYuf8t/yT+11RGn8GNOmoReT1F/dXmCpqYTTrHdEvP69Av+du4xi8TXVmOENWv6sN1ovn6TLqWxlh+AHf5WRS245jO5+QP9zMf3w99Xh6l51fU14NqWJ9VteGkwrBm9HE6ac13nyQr/kt6BC0uNsxrMxQE1Y+ZURn+Bbmji+GvlRxRuZGarh8TwXXyTmx2WJYnv3+k18cNkefVKBEeLy3wvqP1gxWXH5V6WSPiyIiyZyWZ3RfEVvYRP7nhfXOLk3SNpog/lMD2fIs5Ld3X9cXSxfCh/qV7BEv58DG7WiHjOvXus+KVmVT5yrXXyZP1quMNOdVwnfT+NwV97muHVks5/pfPi/F591PAD1SQ4dWwX9Z66ddBN5nGUPfVMirWFCfo5A+RxovyvWOYXHbnxTRxDb1f/FF9utV5MS71r/FfGbSRfFsCYTey/NlWsfil/atA=
*/