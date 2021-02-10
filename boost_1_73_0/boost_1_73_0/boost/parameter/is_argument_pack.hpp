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
4TNG3Ib+n8yS5dyEfAH9g6hP+NylpA4ryBdyArshX+A4hpBEy3v1TsguRZ+UbepXXSE/EfWKOwhTyKYfLEI+dSQcN0+gcXb+A7zFR+OsBi3qcebCUDLvnoXTGry3452fHTqfnwr2oQZMAnVPE1EjhwsQ/kQ+0ZABvrvcYp5gNlABNhNWyO/xD+6BdBhMuMug2b+96/SuavDkcMtRQhZ+BMLxI9cGhz4yCJnF+KOWEdBQgj9BOAq3uZAoMJLc905RNwPJwplQMpR66gof6CPlLr1HRVSCI2UgfqrXrSh00fq67VuibqXunzpytvTkDo2Y0QX4gQTpQyRYDRRnDWa+zSfqiQHBzSC6d7lwaitrUJVn1/0QBHNdJQtxnAltNoNhEp6aYoMALeZSPYTvCaXqyfFna4wYRyVlEoUeKsI4IJPtY5hrEGFbhTFz7HmqIolpHOCNqVnZa4PvoTHwxhhCZ/gG7qngogYfO6Pr/ngEH43BwOiN7qDfBqN3p4T90um1MPUclYXA5kHIBCoPgc8ClzM70fl6q17B7oeBH00dd6Hs0zZfMz6zqfutgKkQNOCnDijWI+5ZbmQzeC+kzT1M7If1PZw1am85dHDQEHMw6A+OhaQyEieQvMA3cDb/8Uyvk3XAkDT7N7ddc2TC
*/