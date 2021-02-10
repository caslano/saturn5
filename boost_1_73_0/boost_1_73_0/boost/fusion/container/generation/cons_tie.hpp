/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_TIE_07182005_0854)
#define FUSION_CONS_TIE_07182005_0854

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct cons_tie
        {
            typedef cons<Car&, Cdr> type;
        };
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&>
    cons_tie(Car& car)
    {
        return cons<Car&>(car);
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&, Cdr>
    cons_tie(Car& car, Cdr const& cdr)
    {
        return cons<Car&, Cdr>(car, cdr);
    }
}}

#endif


/* cons_tie.hpp
5ksbZ0G824I15zMTmDVzlWvDGI9HuiEfg9PSWZ7XCuXqEOiYbaYBHzHBoVlkMyOudO8Vn4fH61nmbf9WqyPdOkhIxyis7FVBDUpLhzCF4on65kvbb2zkQVh3jMouqLR07Pm6lqlfdyeaUv5UUHcIql/XzqI5jOzIwx9lzJe+IiThGORWddEwZHFr+aOdO+7+SAPbmbuigffdkdDogYgN/NAhlvdYGpUaGQnNGQhFDqJhUHxP3jOmZANA8UAoAy8ZCS0eTGPaSoHJIOU2WNQyOKOF5ZHDql2nsP7kR9OKhnlVZJOUDnFLcwEp6aTGeQXSzdzNw5I2X3cct4m640jV6o6HEqXKk5JuJ5DkmamUdFKxRCBdsPR96qObYXAyYipLl6aREFNeuhAiwtiRU9R1ol4gLVdF6SIaO9UnL10EITWInR7do2qmKeczmT1xcKlEvsQyGZJkgpqdPGq+3cVzPpJWUCxd2ezRt0xysulFrCeeZMgkOTj1e+l6xHGfO2wumKysz5T4G4/yCWW2YGXjTDGV9tn6EpyMoLMwB1p4lCKxDZs4350R9iEA0ygdYx86mIatLc9atSWKpNFWG8g8MsldFq64zB7L7Njs9jTYWMtoVYTfIRDgHx+pB6I9fGVCYl6HJXOT3EO+NiVS
*/