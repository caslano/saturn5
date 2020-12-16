/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_CONTAINER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_CONTAINER_HPP_JOFA_081004

#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_container
    { 
        typedef is_interval_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

    template<class Type>
    struct is_interval_map
    {
        typedef is_interval_map<Type> type; 
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<is_interval_container<Type>, is_map<Type> >::value)
            ); 
    };

    template<class Type>
    struct is_interval_set
    { 
        typedef is_interval_set<Type> type; 
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<          is_interval_container<Type>,
                       mpl::not_<is_interval_map<Type> > >::value)
            ); 
    };


}} // namespace boost icl

#endif



/* is_interval_container.hpp
yWR38Mhbn3vFHT/+4iOXzFu69NgHnr/u+le89EEDseF7HfvgC9ZvH3nc/U/e+tmFU7W+rhve8vyHBS+ff/lNb33Z1We/+pn77MxGH3Li059ecOzo/s7uaHRecqTn8mt3Dz764LNfsnRRYNGilcvu9eDDL3/h/QL4rbj3Pe7XEmhpSaZiy/74h8+tP/fDWx7yj9996dGNeu+61Vfc6+pVV9z94UeP7ms/8NwX33PJ/Msuu/GtL37kkbc856Gl0aE1h1753GUD0cGlhWz/VdfWBjYumnePeyyav3jxzR982WPv/PFXrj7/h093nLzlM3fb/9wX3L012NL6j99/+TH5nfFVt3/tyw9a/dDL1vTFNt9zxeWL798yf+FC4yHzHlLIbX5kfrT3YYH58+f/8XefWXvoFc+5/MBzXrR4SWDJkqMffG7HtfWhx5w5cyI4VX/cNfHYprtf94rn3/cnP/zMlaseuvBh+/btC9z05peEbv/6Vx585M3Pfkh7e6C9s+Pu6296y0txCcLCda33vtt9jIfOf2hX+6KuP54/2XnDW1/w8Hg0cbeB7oEl+5797Hl3/PDzV+3ft7/lule+YHln+G5rT336i/c8feuXL9vYvmRjbXc0HLz3vHuf/PTn7n7g2S+8R2N3Yu2FP3zxUbd97Qv3v3D+VNd1h/a3bt/Sf799z3nO/JMnTrb84w9feWxftP8eXeF7bMjnNj38xIkTgdOf/sq9zn79c8uPHz3QtWTBve518Dkvvay7p2e+ccWCKw69/Nn3Lu0cWH3b17/4gBuO7F/V2d7Sef53t4T7uvsWnbj11vml3PDVG8NLH736IUtD3dgGvPkDL33Mxshlj7n56MGNJ265Zd6Nb3nRI45/4EXXDPQMXZbekrhPV8c9H3X7mdMrCzv72q61hh97/aGDK287c2pFX8/jFqdHeu/bsDatP3Jkn3HnD78Uivf0Ljz2/uetbbvino/MZxNXXvj9F6459+NPX3H8/S/ccPT9zw5f/8qXPXjHyNCDLvzu8xt+8qPPPuzoB56Dv6QzL3zHj77wiFJ2MLQjNfzgn5w7uer8+RPtp2/50tID+w4sar184X27Iouv2Z7sW3H2zMnWnaM9D217yD2uallw97u3dyzouOPcqbYVy+75gJZ5d7vb1O7+DYcO7QsWRh/3iLaHLn7E4Ve86P5ooi6Q3IHiroZq34CqOw2VuR0qcBTVdxxqfhO6yE4UNY0mOYmuHkcVlaA+BXTD7VD9E0hyJ5JqR9GOIek2FPcITMA5NPsNMClnUOWH0KRBqF4LuupKVOXNUJNOqGQfVPdOFOMAmqSE7n8jTEYrmvUkitUK1fkjmuQEVCeOrnIOJuoszAQ1z0Y06UF098MwP21oigGYiz+imTbC3NyA6ruAbrwE6nk7muI2VHcbVD0PVZ5CF1uFrrYaTX4eJqEGtehGtZ1F1+2G6pyAGalBjfIwfzehGx5AN/0jVP0mqPw+dOWVMHunYFJWQw1uhOp0woydgWlaBFN2J9T6DpjLHVDR62AuV0BdL8BkpdEtboIpWITueRKmL4imOw3zsx/Nfhzq+w+Yi2uhWifQ1O3oin9ENzyAJipAJY7CVJ2BaTWgzmfRVQPoVgZMSAvUrYCuUkMzt0CVb4PpvR5m5jDM0U6o7M1Qn5+gm2yHKb0dJjuJZj8ENb0dTX4Ypu4ITMuN6N5n0B33oYssQRePwzysgDqeg8m9E+brIEzLzej218FsT8Hs7oApou5+BGZ/J7qSAXM0ADN/CqaS1P56qGEXzMcSmJvV6CLHYbZKUOnrYT63wxyfh4k5BDN1Ht21D6Z0Cmb6NExFK7r3BQwDNXT1BrrQtTAJnTA=
*/