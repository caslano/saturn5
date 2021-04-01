/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_COMPARISON_HPP
#define BOOST_PHOENIX_OPERATOR_COMPARISON_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_BINARY_OPERATORS(
        (equal_to)
        (not_equal_to)
        (less_equal)
        (greater_equal)
        (less)
        (greater)
    )
    using proto::exprns_::operator==;
    using proto::exprns_::operator!=;
    using proto::exprns_::operator<=;
    using proto::exprns_::operator>=;
    using proto::exprns_::operator<;
    using proto::exprns_::operator>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* comparison.hpp
Jtzgtp0MvOdTkWTvl/1Xgqh7R35TA47LqrlSMT5/sOjSNjqLlt5VXRLGjUfcd637KGRdx938YmNUuVIqwNuiHEjSLmNhEF+n5J52BI6I/wIMm30qtsIqWA/rMlfhs3oOuPt2MlSP01s2bjwibcSQaJ6oDmAUqYGgrC7sVIuUYFrgVcY+B28tUX+ey+A2Fk3AuIkz3/PF0uomovlHXpKkxDj2ZMeriaPZkXdE/8sH7y6CGFTihDyvk5H3M/aoRnnUK0QM2ovDcJrDbGqKjyD+VY4gGO6zSpL5Zt7IXIY6/im6awh/nbSQcGjmjU0/wmQ5gHQePokCfpuQCWbEZEpNFsv1KvaLsDsF+PiNbTRyA7v21fqLAOswmAsZXPpgySzE2RjgAudZJ7QE2q3NKC8MXF40Qd1+9tPyawTaPTL6eShUKjO12SCCyC3PLm6ewemESC9ajhH4eQPi1klDfd8onRh3C7WzpBGYwoz1hJuq8Xwcj8WJWnYI+ye4MfpHLEp5Zz6SSdE6DFwHUS5H3UQ5Uw5btOKbnFrmCJ+8LIFjzEsN+5gUbJgFlKmEnA==
*/