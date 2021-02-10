/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_STATIC_HOLDER_HPP
#define BOOST_FLYWEIGHT_STATIC_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/static_holder_fwd.hpp>
#include <boost/flyweight/holder_tag.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* Simplest holder storing the T object as a local static variable.
 */

namespace boost{

namespace flyweights{

template<typename C>
struct static_holder_class:holder_marker
{
  static C& get()
  {
    static C c;
    return c;
  }

  typedef static_holder_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,static_holder_class,(C))
};

/* static_holder_class specifier */

struct static_holder:holder_marker
{
  template<typename C>
  struct apply
  {
    typedef static_holder_class<C> type;
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* static_holder.hpp
N1BLAwQKAAAACAAtZ0pSm2ArmNoDAAD2CAAAOwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUkVTT0xWRVJfU1RBUlRfREFUQS4zVVQFAAG2SCRgrVX9b5tIEP2dv2LE6SQ7oji53umaS1oddUiDSo0FOD1LltACS9g7zCJ2cRJd+r/f7ALNR5uPk4plLx7PvPeYfTu2Nybs/bDLsBUcPHsl+p3ghetYtGz53zST3y9IkhvoX1i4wfUFVDO4rbpJpvCiqhuY6Kpk4DpW90nyArqNEqk+Zqp4k6hbjPSVQ/2cN9ctuyglTOZTODg8fAOv4Jf9gzcWnJCa0QoiSeuUthcWHOc68mdJrq5sQd9ZQCWQyr4HGJdMgOCFvCQtBbyvWEZrQXMgAnIqspal+IXVIEsKBasozIPl2lt8sOCyZFk54FzzDkTJuyqHkuwotDSjbNfDNKSVwAtEQPycCYmYnWS8tpGegqTtVgwwSgSpBAeyI6wiKdIRCaWUjfhjNsu6tsInmeU8E7NsbIVdyu2Dp1qjmi25Bt5IkBw6QS1Q+RZsec4KtWKLMNh0acVEad3KQsI6n/EWBK2qAQ5LGRX9I1CIhm5ZKhMaVM+kWgSvhWK7LPn2XiK2dQAqurZG
*/