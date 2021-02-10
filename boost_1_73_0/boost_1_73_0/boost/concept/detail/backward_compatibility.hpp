// Copyright David Abrahams 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP
# define BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP

namespace boost
{
  namespace concepts {}

# if defined(BOOST_HAS_CONCEPTS) && !defined(BOOST_CONCEPT_NO_BACKWARD_KEYWORD)
  namespace concept = concepts;
# endif 
} // namespace boost::concept

#endif // BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP

/* backward_compatibility.hpp
pPV7xwIXAvcfZDkyP8GeCd6gjB7P0Ot9RVXlGvZMju34nUX/OEunizDJwjhyEoIHRqAVjGsjJeyeu374PHTjTaWeaeg1K6RQtBBYoucwYyg+QyV79TpKm7Z9SAnacxyzk1tqEMAYSLoW2D61UBo25A5dvmMlaynGdW0MUL6UwxWVW+CUyF2MZRXesJEsZhnKNT2aLQY6Rq/Gyypx+grodUGxvStUakEUtqfqitqMm+MsS6BlLW0YZ/wS+5HKvnSUtpaEq8qwZLIpCHdWFOdcQ7bYPGVni9kQppVhCANQC2Cd+4h2PmANErvSOa+xCIKVl0yaVw9WV4mmERtaereyspRSgtlJ+qWjytqRsrRjACWB+WGslA6jz/iZelMQyM8Vo5vd+EV2HmrJcoLTjuOcvTSjAs8oWcRZPI3nqROYIYY7s7+C02Q+c3xeObaHDu/IEnnSIxQWq0Zmcwz/OHBXQcORv9vtWidFNTabdeglHCdZjgtONAxhbHGQ3IPBGYlkrnsMY4B4xnGWxydweGjse+iHrrtib9Eea5hfh2QtwPcgAOWADVON3AwP6S08c23c/ChenAZZbu/joyMcE67/bP91U7rejgj8z+DFvr08594rfNQIfjke7cye7czGQzbfnP4zwTddsyFbbJKG
*/