
#ifndef BOOST_MPL_LIST_LIST0_HPP_INCLUDED
#define BOOST_MPL_LIST_LIST0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/list/aux_/push_front.hpp>
#include <boost/mpl/list/aux_/pop_front.hpp>
#include <boost/mpl/list/aux_/push_back.hpp>
#include <boost/mpl/list/aux_/front.hpp>
#include <boost/mpl/list/aux_/clear.hpp>
#include <boost/mpl/list/aux_/O1_size.hpp>
#include <boost/mpl/list/aux_/size.hpp>
#include <boost/mpl/list/aux_/empty.hpp>
#include <boost/mpl/list/aux_/begin_end.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct list0;

template<> struct list0<na>
    : l_end
{
    typedef l_end type;
};

}}

#endif // BOOST_MPL_LIST_LIST0_HPP_INCLUDED

/* list0.hpp
F+FavB8fwodwHe7ER/EtfByLcD1SP57HIduGss1I/aquy8pCbTos9StDL/wcO+AR7IJHcSB+hWF4DEfi1zgWv8VEPI4343d4L/4DV+EJqef3uAFP4qtYjm/iD1iEP+FePIUf4M/4Mf6CX+AZPI1nUWsMaWkAuuCV2AhHYWO8CV1xFrphIjbDm9Edk7E5pmILvBU9cCW2wrewNe5CL9yNbfCf6I3fYzv8ETtgBfqgK/3bEVuiL3piF9SvtZBtS6SfTNdayHg3TsGmOBWb4TRsh9dhAMbgIJyOY/B6vBZvwCScYTyHXspr5uD7vF/K+7OU9xeUOLYR1b+DpyQuT+r1NMq1SLItx3ecZL4WaaN8z57H1viCtONFDMeXMAb/iDNwC96Br+ByfNV43EDKae+gfjukfjuxLf7J2C6J83IQt0viitATdyNxfN9lOwgjHVyz0lna5Yte6IdXoj+Owu54NfbEa7EX3oS9MRMDcQX2wZUYhI9iMD6F/bEAQ/ANHIRFGIpf4GA8ikOxIXUbhi4Yjt44AntgJPbDq3EgjseROAEjcGJ1P8m2FHo46Kc3pJ/exBZYaJwvEtfCQdz7EvcBuuNB43yJVc+XYonbg564V+K2k05IXHeZL1r8ZomLlfkSh144E/1xFl6FCTgc52AkJuFkvBnvwBR8AlPxKUzDzZiOf8X5+BFmoDNlZ2IjXIjuuBjb4BLsjLdgV7zV6fJdG3Kprwu5mPe3ii52u6B7XG3eUfdrQjY/6CbHtSjvA5c6XxuSQN1ySPmkQ6RTJJ89bk7hpATSalI+6QDJaa+bkx8pcq91XMyarMmarMmarMmarMmarMmaft10Ge7/F5+ZcnHu//ej4f5/CTLeqD22qiUORTftGOiXjbRjCBTLnfdjF6VlJGSec+zAVXGsouq59oZjBbkMSMWjHE/idc1jflmkVHl9Sp4fn5zMa44TH9fqwetuoTXv0X9c6h0gfe9PqiQw75it3twk3lBvpzrcc20BKcl037BkW73ldYLpGN1yOV7dU/qvGx6mrmXV9UhZkGzqw8C69mG6qQ95bauLPPdf+pDPkxaZ7q04q59+XP4EfVVIvSbxXu+vqZfhvvndJC/aJJ+lb+Wz2YbPHld8ti3tn8B7+w2fPar4bISznm+Hb+yfLVV8Nl0++4DhswdNn9W+H65fG74fMl+MHdsAW+LpJoyh85m8bw3zhfMXUmbGV58nX1LX+YIyX3ht+G7L65nm+RAs/W173V++66b5lEObFxN/N+8VfWtvd7p8LkmOyWaZ+0xiX3bRv6/zjttjk02xxxWxJyT2U0Nskin2qCI2sBFlau34zh6bYIotVcQmNdLLfd8QG2eKPaiI3SDljvyHPXaGKbZEEVsm5RYbYmNMsUWKWJ/Germh/7THTjXFFihiYyT2OUNstCn2ZUXs2sZ6nb1P2GOjTLGbFbEHJPZJQ2ykKXaDItad387NWsz39tgIU+x6RWxkE73cbENsuCl2rSJ2eRO9r1xO2mPDTLG5ithCic00xIaYYpcrYiuIvZX3fjHEhppis02xxmVPwRVyX1k+0BKXobbsyf/hnGUP78p9EJ0v7rLnVC3LHvM6woUCyknavDr4g73dJypr/x1rsUFN9dgZPxrWGZW1/4612GSJLTHEHqus/XesxW5qqs/nqT8Z1j+Vtf+OtdijUu4uQ2xZZe2/Yy3W100vt/8pw7qssvbfsRY7w00vd4ch9lBl7b9jLXadlNvzZ8N6sbL237EWe1Bi1xliD1TW/jvWYj2a6XVu8os9tqSy9t+xFhslsasMscWVtf+OtdgciT1riC2qrP13rMUWEbuE99JO22MLTbHZjmNZ6LEehuM=
*/