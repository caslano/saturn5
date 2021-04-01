#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct later_result :
          boost::mpl::if_<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* later_result.hpp
lwU1C+GXOprbb/AtC4pcI7Ke3CYPvOMXHjmuEGalCZv8I0hD60n3A1CbCrTBehNC/x0Hl7CblXTkkOaeSkZtkSDp1QVHuyEAkn30j3lfNeF5piiqnwOCF4PZ/H6SeGw5MUoN3nRtROtQOPFHS55CuWQXPSjDTvCKrqjcKECOsYX0PyhFrYoDUgoJno5ZazW15fbmkXjYMOvkLekppsh2ijmOKIXjB8ixnJ+9ZyFTcYU5Hjy0jyt5HfFbeU3lAqaamBBKjzwD/DbaeI8KTKalWP3CqPjEi9Lv9IA8FB/36J12VP1J68gBeP4MPKB9B0b6y7cjeV9yYe+zdLQ3JlTxtM9yJoJTanTfV0AW1atnYCu6zQy0+nqGRDTjizEq/5jvVjvVZBIxsjHgc92AYe/WQjQni6oqmyzqm9+ZPm7hZQq2pEkabaB7UZyd4R1qtP1pmbr5QWwzEy4iW+N90SaTX4phNqgX5bnXN58jjo52Kk+lK9Vlt7p/IE/hkrPq8iOYDUeAiR5hvf3tT11hEBKbGii7+FMZqd73tl75U7H3pDa/f+TISMfFbX0ZrQ==
*/