/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ASYMMETRIC_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_ASYMMETRIC_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_asymmetric_interval
{ 
    typedef is_asymmetric_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_interval<Type>
                    ,   has_static_bounds<Type>
                    ,   has_asymmetric_bounds<Type>
                    >::value)
                );
};

template <class Type> struct is_continuous_asymmetric
{ 
    typedef is_continuous_asymmetric<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_asymmetric_interval<Type>
                    ,   is_continuous<typename domain_type_of<interval_traits<Type> >::type>
                    >::value)
                );
};

template <class Type> struct is_discrete_asymmetric
{ 
    typedef is_discrete_asymmetric<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_asymmetric_interval<Type>
                    ,   mpl::not_<is_continuous<typename domain_type_of<interval_traits<Type> >::type> >
                    >::value)
                );
};

}} // namespace boost icl

#endif



/* is_asymmetric_interval.hpp
gmir212TILaNfk2CaFPCbaDjkd94kMP+Fm45UJnfZnO7Ae0TMS41GCHonFj3LZTIdVbbL9SatR30Kw+YfqC3GHB9rt9ewPUKv7WAzh02lxWIvlYsjgKJrl9lwG0h0zKeUG6hrcxXGUhzhXiVgWBv4RoD4x2xuxrvh+JSoEHME+ucU4eb28G4wkCaF4QrDCQdgisMmH1lu8Qo9feJQizGusxosIqxETGncpHkxxj82Wa9IccqpOsLss36gfoegt0tlFjU4fzqAskPwtUFtJ/pNxKozE4QbiLIYr/12wey8Vu63UCqU4oqtOoamkVe6PvmqwiYXOmGAZWNV+lmARmnTVb5Ak7M61/E8JYbBPJNeHZrAOzxvi+8LaBA+H7xjKfQ36TzvTmWNuBjW78hgNe5cDOA9lu7DSAdv/klAGLMTrt7QBhnNKthnvyb6sECGaeFSrhdE3Nrh93cS7nydN8opp0tXgcgjTlcByDZKewqANEe0PuigNOuAhC/rUm7CkCMYQnXALA5Xs/yD5+4T8/uT2lCUn9RrobNozaCnME/leFqGhtU1hcs2fp5X5ay9HP9zbPzZxu2Br81QLIT9CTfOaIOY+n6VWlsCYZrplj3K6Tv0dPyl8TAaR2hUKQJm8WKTT6l2CkM/9h4QKQL/ZJ+pcmvob2D+XbWDP2inCKJR5wT+iwZ+Fn7eIX2MWfb5/rCktlf6qc0Db/YJ7RU
*/