// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_ARGUMENT_PACK_HPP
#define BOOST_PARAMETER_IS_ARGUMENT_PACK_HPP

#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace parameter {

    template <typename T>
    struct is_argument_pack
      : ::boost::mpl::if_<
            ::boost::is_base_of< ::boost::parameter::aux::empty_arg_list,T>
          , ::boost::mpl::true_
          , ::boost::parameter::aux::is_tagged_argument<T>
        >::type
    {
    };
}}

#endif  // include guard


/* is_argument_pack.hpp
bg2gcJwMiUwP4r3sv5pv5+9d5fIJ3Sy5sfkthmvq6xkRBjictjFhGenQy5Duy4AZpNOgRqFfvc5pbvfchgTpXlqwnM2fXCfHjSoP2mTf+f8N4xxFdsNYKQ0HQAcroctFXGEAjOjR/INlXNgtxedLCsunHiSkD9/JPYt5YR8okZkT0zNNJLiA7egz0H6dwgiFKfVJ7mm9BsmaCx74TVkvtcKtl/bnzEzU60LpgJSP3r11+/Rq6tHy43+GcwSdbfF3XpAmEx2d62/YKcXGRQd0hCZ4/kJ8RH3vE8ShXYm10WKEck8d0+KiJd90YteuJ1stQsESEUJLH5uqFex+tEs+t3+RR7/bOYIJ+UllbxxDOD9IRHd5is6S+WD6KuHSUaDywOy8+gU6xy/xlPM9DredHiN5t/QR1MtsSuS8sM1+qdiXrVZD0bfyqs6XsxZdJ/NNz82IdsojL/L5+pXjl/jIQVKrNok0bau308VdFfsmn/6qee5NOCVm4aSl4+/dC9BhsaRSJmuEmMm/Et5Mjhm1y+c85h/64WTPNvrD2OdHOd2AzYTyECmEMpdzb8FvqLqczwwyZdM5Q1Mh5RP4bDFee8K1WnNxg0zUp4p4yrSJ8HILuDqsP07e4vbiN+FgoIgcXWBT5m3jEVD6xUle+vyanLwX8tOxH6kX9hDoYHBKUd9R6tZ0KbMOr1szC6UQKnBOitbpjmaXSpwvyHnp
*/