/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SET_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_SET_FACTORY_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/not_placeholder_expr.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Compare=mpl::na,typename Allocator=mpl::na
>
class set_factory_class;

template<
  typename Compare=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct set_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* set_factory_fwd.hpp
qbNsU/6Nkm19jynP4BW1ulMaTFs0F1rpNn0YzK6C6xl96E4m3dHshoJfqTu6qfW9HYwugQ0FqyXJ+6KUGl6UpJZFqmS8Z/wf7XTPn11R73oyDMazcNKfBsP3fXpOrdOX9N8qA6xPX7Solao5153O/efn/gkW+Fsohd6EWhquMP4BJg190ysadd/1vcdKb4+pKPOViiVFlTaozyLXhjKxlFyJwZhEHNu48ZanK6mtrunNKBhPB1PPzxLvXyqL0goaXrMDDouLXzxrK8qt5n2/DniHni2AkhRgeeRT2/s6E6CcFYjMKtTAp4EW+KsPX1m3LvvT3mQwng2CkTcWcFpQkavMMIzQOWjh7DOgYAWBJgZHdqdpjQrvxF1HitZO8nIpOIWe6xXCArb/qCRsOjHbui4S17S7Nuq+n6N1gPA03dBKpCr2GgdukzdPIrpNxnWYmkuD9oEYsJ5asvHpWkvvNhlsBUJRFDKLD54fsigcjUop0K3GOgND3Iz7EkkpZSjS1MlwcFEq0R1VwT0iM6NKJ+t7Xl9EC9LIExhnLz0uezsxrktlwLFIFK9bVrT58z4efboKprOLcTCZXXQvL1Ho6cd2/fDJ930wg4RFPsRty6LWVIPwNcInU27Y09p8m1hbc7rIQaRZtQS/NzSh
*/