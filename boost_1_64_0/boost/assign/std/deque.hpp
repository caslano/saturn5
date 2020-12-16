// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_DEQUE_HPP
#define BOOST_ASSIGN_STD_DEQUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <deque>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::deque<V,A> >, V > 
    operator+=( std::deque<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::deque<V, A> >, V >
    operator+=(std::deque<V, A>& c, V2&& v)
    {
        return push_back(c)(boost::forward<V2>(v));
    }

#endif

}
}

#endif

/* deque.hpp
jaUZofEy4csSL55w2O05+zmtGMzdYRJkHcrCBObaGyBvmEGdjlv0dnL9hGS/u8cafrm4V2Kec/3qLfo42c+4Ra/XMfm2r5iZpOVCnALCr8E878bxL9rjrl8JmuD5EpNIM+D/VbKvfrIv3njTtfl+vKTbVdJdS5pxSZqub3F8ZJqT8Zska3IXn5jsz0z21QvcQzLuEzEnhPwkvSzcJgTT8y8ui3adlZom/rO4d64zkOZU3NdomuonaS7EbVUozdO8aWZomsnJxgzOggmLByfHNbB1zpG9Aakzeu+r5d5b0upT5Zz3k24icYd44kamPTlZ8zV+cfdkX1LUslop6TaS600h/ESM5ml/m57qeGItru65V7txp7vPXovk8H32pkbpk4ui9MmlUfrkiih98qKqfbJdN5fSSGXJAjCu44TWPLuSA3rF5s4pK89HhTVvKYVTCk+NVuc0rM/jN037kqBfmpRHSkPRDaH57SO7o9fh9yROvOT3IsKvbxjM74a2/Nx8NVGPtiMkX7nvRLteMF/sKdY+LSwPvtM8aKYpZGgemIZR8mBmYbRr1rDNouaB+knf0YRzrW2k7cDH//hkP9VJ7vVc3O9vFGwLqT/rver6MXcdvhzBBF3rsa1JKdq9ziqTvtWY6OVEHFtObkKlGLl2CvbHXHeYHq2U6GWSE+06i8ujXl9OzDKxfnLtq7jubik233/UtUfL88OC9UtTStQUEjTPp0a7l5KyaTHyW8P7zf5em/datslf7lNjJGEauHsJRLuWMr51TC+v0t/q9WicuCrXmm79kqvkfZFj/Wq8j7Sw+9Bzaz578z0zRl3fmVb1XhNdodPY98qAIPb9LvLcb7n3fq1fsvp579f6SV3bzpUtT9NnUpKpVV2rLh/KI/Kh3JMPe+Tb0f6v54m+Pi3W+qKfT69+9PVIP2JdmayXu/yk9RuLnzv9sd99MeGAw2ZXPBVrHdfPt67sl15fVyn39afTKj6547KJR3XYMX/kV5eMa7r/6+h+rvVmsdaV7RUZTTmkT13P+WYYeebJ72J+T9LfFfx+TsMs4fez+vsyfg/RMLfye7D+vlfXgJUGv0/qd9Gd2r4L9LxNdG1VpsoCN4eDYUt4JDwIHgM7qmxsJ5Wl7gIvgFkqQ30g/IOG3wVXBb+rwS/1vGmY6/W8p6tM6pnwQJXFHq6y2CPhcjhZZbGnwAtgCbwQLoYXQYzIXC+Dl8AV8DJ4D1ymMt2Xwyd0/9iN8Bq4RdP/Av5WrzfXfluRb05yvZ2NrEWQo6fm00CVoc2BHeBg2AMO0XwaCsfCMngcHKYy6MN1rdhYeC4cp9c/GV4Jp2g+TlWZ6hnwMVgEn9D01sHx8C9wAnwJHquyyMfDTzXeHo33lcb7DhZCxwn4d4ZF8EBYBnvA2bAfLIaHwhKYr/4zYCksh/Pgmeq+CI6AK+AoeIvrrvn5pH1/5/uF5mc/zP2anzfg3Rau0DUPN8M+cCUcqvvsngDvhtNVdvtseJ/K8N+v9e0BeAf8Ej6lMtqvqIz26/BZ+DZ8WtfWrYMfqP0rDfeN2o0TsPuga49Xe321J+t+vm3hczALPg+7q32g2gepzPdgtedqvJFqH6P2CSrjfbzKeJ8I34VT4TY4C/4NFqu9TP1PU/cFaj9T7Wep/Tca/lz4CbwAfgovhDvgdXAnvBt+Ae+Hu+Df4B74JrzV7uOr7ybaftd79/HV/ZyNtrtU+FsbT8fzoFmUeKdrvAqYARd44rXVeClR4v1G4y2BjeG5nng51ZxvtsYr1vOVeOJN1XiJUeIVarwZMAHO9MQr1XjJUeKt1Hi3wiR4myfeomri3aPx7tV498GKun1I6vYh+Rn3IWn1YZw=
*/