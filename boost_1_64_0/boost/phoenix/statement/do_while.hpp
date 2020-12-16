/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_DO_WHILE_HPP
#define BOOST_PHOENIX_STATEMENT_DO_WHILE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(do_while)
  , (meta_grammar) // Cond
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct do_while_eval
    {
        typedef void result_type;

        template <typename Cond, typename Do, typename Context>
        result_type
        operator()(Cond const& cond, Do const& do_it, Context const & ctx) const
        {
            do
                boost::phoenix::eval(do_it, ctx);
            while (boost::phoenix::eval(cond, ctx));
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::do_while, Dummy>
        : call<do_while_eval, Dummy>
    {};

    template <typename Do>
    struct do_while_gen
    {
        do_while_gen(Do const& do_it)
            : do_(do_it) {}

        template <typename Cond>
        typename expression::do_while<Cond, Do>::type const
        while_(Cond const& cond) const
        {
            return expression::do_while<Cond, Do>::make(cond, do_);
        }

        Do const& do_;
    };

    struct do_gen
    {
        template <typename Do>
        do_while_gen<Do> const
        operator[](Do const& do_) const
        {
            return do_while_gen<Do>(do_);
        }
    };

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
    do_gen const do_ = {};
#endif

}}

#endif

/* do_while.hpp
EXtO+yz7CbIh/tN7fEONviOC7ylYb5IVW0X4PgfsLGX77sQerA25csYeLKs817sxRz7/3q6zDiqn7+3i8mfnkef7vbVDAHE1oflxjr28sa8pluYx+3z/clrduOy5B5FN4RsYtP2M5+XIGnvRNF2bTHx904dx3kDfG35+jqx535qQucAs05Pp0kXI5oVmmQS2Y4l9O8bOHGr3i/LLZrAvtY9tdMyooj1nQf5ii3yStU2mtwdbLfVK6R7xGF2SW8bYa0f+XmrmpzJraS+NrkiTvcxGVt9ja8hyu5stsr3pVDKjavH+Qg7ffo/f5Tky+ff4bcmRs+zx47quMMsYXYBtv80i8tzvrRa5dAoNwHZE8za70oavxSu1PmrZ83eVjbwYf8l0lGSutpFhxzawjUnfF3iNjQwfvWw7PLXPF/uTMTzj9dhmI0tjTOxCM8X4Wot8Js7k5X3TX8qRse6TvM7Cj2cQd+YizGdTmtz1Fjn8clW0W/dI24//ZYtcGjsgBe8GE4/qxuvyFSvP2IdJe+VvlGV6UxhmnbyON0l07niz2Cq8TN3Ifb85Pz/kbg1UaXX8al45fT7kvm43y7W0ug1Roetr+WQMs1zu6/nkDLPc5i0mudwt18Lmjn5kuEXqk7f2JxfpDscS3C7XeVs/slyKbH/DJMfnoVgUQ5CN+e5Ygvac326So7mKzexczx35+dyc1s++CZRPKcn70+808fjecNr4qLXhXbYy3TiSxwamqNPdtjLG5KSNsW/ZyqVUWOO2vm3Lx+8KrFX1cXiPVcY4niNdE++1yBnXWC0299nIQAUvf78dryeMQ25pdlCC948HrDJ0CYwkjQlGzFnfsZGlqmGR1Kmy6YY3P8XqQXv5Hq3tHsrHT/bq8X7YJMP2W5NNXv/vmvi0f5rzvmfioV5633zElhfqTJFv37fls7BhSUi+PWqSYXNZFYKvtfMP7PlGnyJbj1nljHYmW49bZHJj+UML34ilFo8nTDI0r3Lej4hnOj/EeU8aPOPsEJ1d/bHGC0ciakqcS31Kp0WjVXycCT1PE910xoj3w2ckHlu40j7o3o4zsWRDiydxQcalh/fDZyVZPlHkEdbq/ZwkL84WJKO9cXEe5Cc6Lw4d/DgjndgUcd2Zl49d/BBiOn6aI8OPZuXo+JmVL+vgPj5PMqbzTpz3gs5D8Yw4WKTV7UXiiXNQYkbX+sxLxLOekRJtt4v4QqPQ9/McmrZaFbxfEI/aTpsduK6XiUdnqXg/+CXRtPPHml+/Inq+s8e/Jr7p/BW38xuDl9bOzf6WaJZzV6TvFZlP6jRbv9N51vNUv5d5bLEUZj1IlHtV5yUxJSWiOCS+VqUxsVvn9aY0O3+QaPpme1rrvEY848yW6Dev6/QNqWSaTz6sz/SgEdOxcJzLvGHI4Oyy+GXQ3hQTR8TInzdJRj4T+EeiieuTcXABxbhPf5L5PADCpz9b6PwIb5It97W6viXLGMHjc+JfcnjGDRf+7EpmY2HN/tuynFgRc917cukqOxaPMc95f7XwcH0nv/9GPPuzY0Lm77KMWJTG1Kg+priNvZJMlX4aR5TfJ/OMZqDViPBxvyTDkM2n2rh4R+ZhGgiFMxvxI66d0Yzgvyvxc9aEZP9ADh+9sgvGTTreM2Ryzodo9Xvfys9o/n2g8azn4jj/Hxa+roLzP7ThpzF2kj1C/0c5/N502lDA+87HVn7OsWYtDv+0kWNjKMzHh5D5xJCxeS4jrkmfGjL9Pbvh+hSXRVa7/urj3CXLqOl0kubcATrd+gylwIYXaptbuQC/mYnfmRWX4+gGPs4LZdlO8d0JRRKNjlOr2ncVDNR5luctvOwgnW89IzhY4vGhxjs=
*/