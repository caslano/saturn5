/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_LOGICAL_HPP
#define BOOST_PHOENIX_OPERATOR_LOGICAL_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    
    BOOST_PHOENIX_UNARY_OPERATORS(
        (logical_not)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (logical_and)
        (logical_or)
    )
    
    using proto::exprns_::operator!;
    using proto::exprns_::operator&&;
    using proto::exprns_::operator||;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* logical.hpp
+syERdVKBiyk0OKuaDHk6WkDj1TwB5te1oOLZpOi7B6nUPZv4871B6rWC+8hnaZXdh2ez3jxgcMV0qLVPQn/JTUSPZ6w55r1+dSh3Tgb+folR8l1oqbtdBWyv7qb/ULrK0TdcIl3Z7dq+Z0ntYc42DDlqi25rrG5kXEx5OzHS5GipwLNL3d1vVsKQMLzbp8tF/zMdDRRne0N5fBL+X5xQU8wWs2dvp3cJ8eXO78hXOkWfzkCHNzQCGwrjCwyk+VbowPpjZfe9MAbMrnaavkAP4PmnFemySNMTUhPOCt0FtGOS4GlpMELUhF6nE3DOqtK37AmDpsjIQeclHopKjnz6KosXU+WSKI6TBkTHldZj53wFKifszCey7teCm/Q5UKJH1AevdIedtJK6+z/z97e/xsGfzM+2j7nbdjumUDXNiMx4DuC6D661EuL34c8ngypvXxgbMDBFshkiOXl0PFMKjxEKjx6MZWDg4BcZ/N2XxOtoHZOcTshvnnWZrlaXwZJXk/WFqy8wk1AXKmAeJKAZG2GqpFvherJFYZHe6+qxgyZENzdogVYSSZEd89qFiJEcHOy1iMbW+IlIK5/D4hPA/mylgL0f/bjZZ4t7QVlEq09+X24xuMAnxbnE9nIdQQPJEIwtMq8+iGn9oedB6Gn76OfIJV/kB3W0HnmintpUAMXUCoVLawyz1KpfkolmjWNkxiJ3d/vDp0l8tckjVHgRIIZGG/+7V6b6SkfvVAAi+2BC4KTrao3cEa5rzIkMIXekQTwN3DSZcukC2g+90RKx9LhbHqggnLR/Mpo7nRVmrWcVxsBBKooB8k+f8jvAt+iJJJnztCgeYV0RyoLv1iUmRTrsXom9c/0MtqKAX5x/fHIamdZsbFde1CZ7u+0mWR/B7sYrWwvXXjrwbVa6YuQDwxXWTdcFrgyh3iXYK+KdRSfM9p/p2Y40GzNn6/in6wi2UET6q87t+kzYbhpBjMc6CeVtnSvOiZXmEGYYhK37H4BGsgQiD9TECso8qq+HEPiG48hHA39rHBab73gyTCyxGtYp1IvuHlbhjyisKHe8xtKPedHar+N/XaMhlNMcCA22eMpW9hfWvjVuUwg+QX5P/9eov9z87Ne+rTUdWhf513qicbVF2mMwW8eWlcdPZd7i0vcc+AGIvQNHaPxNlnxH5Ro0Yvn5+ZPhLCm109P65bzMbxdMtVTP31wN5YRzt1HlzqGVvJxmeoPP01YBIciEoRB8VR3MNNCDhBCfo37PPvxJV48gDTPm5oqPdycWdw8/zAFMzSCxhNe1uPLut9l112vAK4xwj252XULkBw8HSMELq/lBzoktNS1q+eowirSiCkYWaOdQx90w3/ov2kfe4DxIuWz3aSWmQgD/F2CJSaUQygFK0yERc/Ruk6cTgnt3jchptX7BjFEFHiPOKQD47yqaHRgXPZnfSf9rDDbVSgxGGGsvYP6II28WATGEie3AtOqzCt+TyMoLa/WIBoaMUND5dgqbJjdfVFR72bdsIZGE9ElpHGkZGrpBrO2kysjycsBM/qOeMgAt2qN+Fgph1EfWdXPLU8xPWBE2tSEiB7kf9LQsik8wWT9gtrDWXACNn0K6ERHSU3Z0vCO09gku8zXgpCg2ab2Tv7cd76RApjP+aH93OuYd7D/TpHvwU74LaZXZ91F9Io5+XLaGp+eLgfONJiW0SKal/0rJTFP+Zn56Ax1hl1yJ1FozOvlwJ8z6M2e9ivZ2yL9WlFtp19ntMAEFbJl6qcONfOEgHXZCFiXJmBXsun3th5aPJA2gYjaADjYywzJpBnTeXCajc59a+O/SecKqe88CdQgdGbAydtopVn4sVqvMXofU+t1jhs=
*/