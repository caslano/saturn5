//
//=======================================================================
// Author: Philipp Moeller
//
// Copyright 2012, Philipp Moeller
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_PROPERTY_MAP_FUNCTION_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_FUNCTION_PROPERTY_MAP_HPP

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <utility>

namespace boost {

template<typename Func, typename Key, typename Ret = typename boost::result_of<const Func(const Key&)>::type>
class function_property_map: public put_get_helper<Ret, function_property_map<Func, Key, Ret> > {
  public:
  typedef Key key_type;
  typedef Ret reference;
  typedef typename boost::remove_cv<typename boost::remove_reference<Ret>::type>::type value_type;

  typedef typename boost::mpl::if_<
                     boost::mpl::and_<
                       boost::is_reference<Ret>,
                       boost::mpl::not_<boost::is_const<Ret> >
                     >,
                     boost::lvalue_property_map_tag,
                     boost::readable_property_map_tag>::type
    category;

  function_property_map(Func f = Func()) : f(f) {}

  reference operator[](const Key& k) const {
    return f(k);
  }

  private:
  Func f;
};

template<typename Key, typename Func>
function_property_map<Func, Key>
make_function_property_map(const Func& f) {
  return function_property_map<Func, Key>(f);
}

template<typename Key, typename Ret, typename Func>
function_property_map<Func, Key, Ret>
make_function_property_map(const Func& f) {
  return function_property_map<Func, Key, Ret>(f);
}

} // boost

#endif /* BOOST_PROPERTY_MAP_FUNCTION_PROPERTY_MAP_HPP */

/* function_property_map.hpp
MG/PeEb3Jbpf8f8agbswBaWku38brAe/C24MXsqU49czus+AX6bjw3gcU3Av0unA42m/pwngUHAh9cv91A+PgLuBHwdfAZ4M7g8uBg8HTwWPBE8HjwU/B84CzwLngkvA+eAXwfeAXwE/DJ4LLgbPA08DzwfPAC8AzwQvBD8PfgCstAfdD8AhtbTH+9QeH1B7rAIbwR+Cad9smtfRd7xcH/tmB4NjkWjgvXphBxkDdkImQ7Q2kZcRroRUQy4YD7sEZAzEbSdhVi9byfha7SWqrQSn5raX1MlWstWq2EsO2/UeNpOl+M+X3aRRumo3ETaTaISXIE9fdpNY/F+b7WQizmUBpBxSDYm+T9pSJP5J/3/N2jqvIXQA5742D4oU9xBWrfvvPNP9257d/ivPVrU/Qyn9P/s+5b6xFLwVchDCJuhZBCQWMgSiuY/Q/aJ+94r63Cdwj6jz/aHm3lA/W7qEhISEhISEhISEhMTfZ//Pd2baMp0FDbD/P2z3wh7+2TbuG52ZpzHbW0xmWJhtNhaDNBbYGctEGrzjn2+zKm/8m1Dzu2HadprH2aysK6VbX1s60x35mWlZJk1y1o3KLv/zfLVVahBdRQJ0FZeT7W06bSwwENKYeFJH/H6C60rvT8+0W0y5VjgPpAmjm7CpP4L/dSwz23yb1TTOnGdlGpt6c3FcU49vISAvj28htEAeJeE8D8edZrJhh4C7iHTtUIZePT7Q63gDU+rwmPABSM905DnVyqEOwt55gUgfzEJEWOfOF+FGmmNtZs2hLIR8By7kadHj0cxP+CE8LtLC/p6BbR4wXlpQXY0inZ/wc3jEM43JbLHA1yBPTRsq0kZSWMcGiLBetMPDip+DkwEhVP/W4v/OyL1Dbefg2warfkuimWhn1Mujl1ognrcf2l60POyQ6nsrSZRJT4WELWhYB8gT2vdWzGkYxQ7VC4EP1iylPyYrPhkZuILSM8ehoQB3f6SLPFoL2/bz/ugflNUHY9AQYBD2Urf99KpIdtZzE3ZjqnNLUjv3ovcaroAMRD2KlLF75rs2CDIaP32QTkfXnHgHh3l+v6PIa8y6/UD6oo79IP0hAyLPbm929wXK8ygN56HuN7KV7N/zIQGc6Tze83UeOfaa2SHvT86HxvSnIp9i2O2GaM+R8tehnwbwOlL4NTGmp4j+tNrTsKOJxf1pU42/SacnedqL+Hko1z5C14q4Jqw1+jkCfTMCJ5PI+1k/3ODfxBCMMhT/BvyXgv8Giv8ycLzip6NjeRmZ6U71umkv8utCYcofIT5muIg+oXEziMTto2BgNeDlElQfhXFPqv4IPdiZcfHsz/tO/T5sLmX+GL1jMxGSjPRpT3r0HTxUcux3OTLdE7rq1iOuT/LLygnhbYBLCxvMMM/xiPy8xiPNoeJKNtExmnn4JWqr1up8R1MdTVLatG+KtK3UfvyC+jEKfVWOfqrEjeFqtK1/cEBT/xbNBgUYDC1wrh7X7mC6FiK8/I5cXn5HleR31ALtvftJt09QL9H+u9RwnOpztF6N6xYn6uwRF89CqI9421EreMxrXZowgbY0R7SBJKE9jnj0j8OK1wnzvOY11Q9Np/Ew0vbJEa8+UeexeswLHv5LXvNbAjmmdKa6x0CGd0Q5xdq659u9Z7jW2nrzR6xM/jRlv81rTCEfbf2155vuyMkWjyqa+7BnevS/6pc0pI5zYWvNOXvWTGkPA/2nlk7t4f4209JmTKA3tUcvyAtI301pD5oWlfOYpZxHvp3u79rzRnrva4nmO5pYxWNFzVx3jUgfhv71Ez5A/dAv/VCXoXz+CvY3+IUq89pGxCc0o3nNL0zznIPZM9+qXm8DRH6B3vOe+hw=
*/