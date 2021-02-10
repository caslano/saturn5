// Copyright 2011 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H
#define BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

#include <boost/phoenix/core/argument.hpp>
// provide some meaningful placeholders (instead of arg1...arg4)
namespace boost { namespace msm { namespace front { namespace euml
{
    boost::phoenix::expression::argument<1>::type const _event = {};
    boost::phoenix::expression::argument<2>::type const _fsm = {};
    boost::phoenix::expression::argument<3>::type const _source = {};
    boost::phoenix::expression::argument<4>::type const _target = {};
    // this is for state actions
    boost::phoenix::expression::argument<3>::type const _state = {};
}}}}

#endif //BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

/* phoenix_placeholders.hpp
cM788jONmbKU2nhky+nT9HkZf94YR/DrTqgcr9YPUEsDBAoAAAAIAC1nSlL0FAAIHgIAAGcDAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTYwVVQFAAG2SCRgbVPbbptAEH1fiX+YOIpiSyX0Ilcu3aBEDlEsYeNiXKlP1hqGGgV20e46qf+n/YX+QH6sA7brVu0TM7PnzJkb3KKxmTAYMF7KQtHnEXfPSucmYItpOmfcOwW4t8ewc3YOC9RPqF1T5si4xqbatYCD0SHGVYnSHhBZ5xDEdLyAmdo2RDi6vEBhtxpJ5qzMJTt7LuW7twQ4xYlqUT4FLBqvbqPoGuVqubhapvfuqA2N0y/z8K9gm33P4I3GbIPZY8Aa1BW408mb0cz3IyG/tj1dVwfj1Ti+CxdhCi7CZV4i9GaIuQEBXUqoVCYq7EFZQL/K+kda/0DrDwYDkMTa2sId9QYfL6mIkzZwKWrcTxaeS7tRWwutQ8lHYLZNo7QF96C1pr3kQOSyaWcH/Y0yFhpBECWr3YDSeft83Ni8lAG716r2IS+LAjUxHJYqH4RUdoPaYQ5bq3zntGPZw3mm6lrIfL8M3/MuHuJFOpn7F21N8zhJvQ/vX4Pr1qKsXJ019lTNzcuPl+8vP68M
*/