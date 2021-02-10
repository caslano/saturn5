/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_LOGICAL_HPP
#define BOOST_PHOENIX_OPERATOR_LOGICAL_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    
    BOOST_PHOENIX_UNARY_OPERATORS(
        (logical_not)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (logical_and)
        (logical_or)
    )
    
    using proto::exprns_::operator!;
    using proto::exprns_::operator&&;
    using proto::exprns_::operator||;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* logical.hpp
9UAurrlBAxEYK5nFTepaRUeRxpr+hhYGCiaHTUNVRirmk+0QPmjuhMNNWSeT0FZGrgp3zXurZaai6xOnLLIMjmnbNltNXRtFqXCtGLoC+ePozycMddEgEqy1KzpkBqGB1T9Pg3+yrToAGVslyQP54xN3A/riSW5WdURqL7Zo/mI89M+cM4dbGfJ8NsEBHW1l/cHADwLoHT/WC+ClT/R6K/upP5xMHd63T2SjoZO92cr830bB3OF99xhvgT92yN522gpzIXr2f9/F6V9QSwMECgAAAAgALWdKUlPbCfjcKAAAEokAACAACQBjdXJsLW1hc3Rlci90ZXN0cy9zZXJ2ZXIvdGZ0cGQuY1VUBQABtkgkYM09e3/auJb/51Oo7K8tpOTVmencW5rM0oS07KQhC6S93U6XNbYAT43N2iZp7jbffc9DkiVjSNrpzC73TgOydHR0dHReOpL3tr/fZ0tsizs/I/pvBB/4Sy0u0uR36efVtUejL4L/B61+g793dbIniiZfRg1xd5Mvok5NRqqXF/h9NLqro98QN/xnD1v+NsKvUALN+P9imIZXoReJSRhJkadenE1kKhZpkid+EolMplcy3dWVZ2Em/CSQIoz9aBnITMy9+EbMkyCchL6Xh0mcifGN+LdwLl4tb/Ik
*/