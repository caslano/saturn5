
#ifndef BOOST_MPL_INSERTER_HPP_INCLUDED
#define BOOST_MPL_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

namespace boost { namespace mpl {

template<
      typename Sequence
    , typename Operation
    >
struct inserter
{
    typedef Sequence    state;
    typedef Operation   operation;
};

}}

#endif // BOOST_MPL_INSERTER_HPP_INCLUDED

/* inserter.hpp
PlMdkKVxPodv1AMykxLbMLqiVwMyCNRnHua8Moeg8n+QIZF+wuiXPj3/an8BUEsDBAoAAAAIAC1nSlJgCn2OgAEAAGoCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU5NVVUBQABtkgkYGVS0WrjMBB8F+QflpbCtZyrOG0OYlRDSUPj0sQh0T0fOmmNRR0rSMql+fvKkdsU7sXWamZnZtdmHp2XwmFOmG4rE15veDwYq1xO5pyvTg94nvF4sLhrhEQFNQqF1pHp7/VrueJ/eLGYTcvlU8GLckmKKlkYpSuNKtnoViJh9KzLaLQil7BB+w9t4rQKlE78GGAlvIDWyBrl28PFEd1FzELT2xTGwzuYWWsseRIeM+D1/iekKbzsGxgN0wkMR9noVzaewPOCk6ifQTdm4k4FdQcnG+OQhCCdVReot76EaaOx9X0geSoCHjtzUnu/C+zPkrViizEbrNHbY/JYebT9cgDfvRXSa9PCj4P2tdn7HroOIrGXeWOanDT6bzqe3IfrWDNptlvRqmiZUXo1Lze8WGVXndmqXHMa+OPA/yKGYx+XsJBOV90qd9Z4IzvF8Anh1AOfqxyQuXE+g/+kB+RRStwF6IbeDMggSJ91mPMqDJKTbwNnMOy20gOM
*/