/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_SELF_HPP
#define BOOST_PHOENIX_OPERATOR_SELF_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (address_of)
        (dereference)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (assign)
        (subscript)
    )
    
    using proto::exprns_::operator&;
    using proto::exprns_::operator*;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* self.hpp
X2A2EPnEkZ62wBxszvtRHNlCOCS3HHEhywOXETv0A7lgoJldt/f+5mm+qsLXXrp40zDhThStPbVbnwnkUqZ4Ijsydkwiaykbfwm9nW/WJ/Bx2ti/432OlbGK7/TciEfcH7yur4fXC+elwergxdQCQAGzX9iMZAZgWHcxIggTLP4qBE7l2nw7JTxFsDzNkLl0fYWDckPRXglPLeJGWyBUzRDPkxdS8Ade+5IdGX3ywMy84rJvNeHiUrNRAn2GPk4DgpSRToD+8Uc2Mdk+xdkDTEALxWugClTS9HizYz1G90X6ldaGtaZDdTlQCtkpQ6JAItcUMMv0G+vVfdd4zvoUyeWd9dW+uSftPcJI5hwUNToUrGic31fEsZBxcn1KeVMa+o7TNODfi6nsCU7+dWn5yh2IJPplUfsUcAI4NT6xB9flCT5prhUjalVI7zju3sMVB8X1ohr2IVGybDhd/RavUX7j7nXvdX+p9jKaPYZPOq3NCZXTbKbKO2Lvvurh/wlqwm2+744fbUndu3XrJ1UFIUSFIRYSig35u03UOizyJubOi6wOvTDPiDp5FZ2WxkXlAnR9ur+Y3TYZSgGqzL27p4/LXAK1VK1psgKUQL+Vjtx3fZjrRjAt7qRWvoyh2Ft2ub2QeXzXqMtNI4bzU3phoF2PqLYBeDUqACvkHp9TedJAvigek9YJ1jlxzdrzyb8EtJf0t7j+iiV2tzhG
*/