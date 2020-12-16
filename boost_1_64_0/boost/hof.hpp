/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    boost/hof.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_BOOST_HOF_HPP
#define BOOST_HOF_GUARD_BOOST_HOF_HPP

#include <boost/hof/alias.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/apply_eval.hpp>
#include <boost/hof/apply.hpp>
#include <boost/hof/arg.hpp>
#include <boost/hof/proj.hpp>
#include <boost/hof/capture.hpp>
#include <boost/hof/combine.hpp>
#include <boost/hof/compose.hpp>
#include <boost/hof/fold.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/construct.hpp>
#include <boost/hof/decay.hpp>
#include <boost/hof/decorate.hpp>
#include <boost/hof/eval.hpp>
#include <boost/hof/fix.hpp>
#include <boost/hof/flip.hpp>
#include <boost/hof/flow.hpp>
#include <boost/hof/function.hpp>
#include <boost/hof/identity.hpp>
#include <boost/hof/if.hpp>
#include <boost/hof/implicit.hpp>
#include <boost/hof/indirect.hpp>
#include <boost/hof/infix.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/lambda.hpp>
#include <boost/hof/lazy.hpp>
#include <boost/hof/lift.hpp>
#include <boost/hof/limit.hpp>
#include <boost/hof/match.hpp>
#include <boost/hof/mutable.hpp>
#include <boost/hof/pack.hpp>
#include <boost/hof/partial.hpp>
#include <boost/hof/pipable.hpp>
#include <boost/hof/placeholders.hpp>
#include <boost/hof/protect.hpp>
#include <boost/hof/repeat.hpp>
#include <boost/hof/repeat_while.hpp>
#include <boost/hof/result.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/reverse_fold.hpp>
#include <boost/hof/rotate.hpp>
#include <boost/hof/static.hpp>
#include <boost/hof/tap.hpp>
#include <boost/hof/unpack.hpp>


namespace boost { namespace hof {

}} // namespace boost::hof

#endif

/* hof.hpp
zvyLTf5O8w/oFHlFdAUvmXY51ttG7EHPdwvpwJz17tJtQOt5DTm1vHECLnbavLsRsRr8oYYqu7+tY7dtRLWCoHmfmkNyOJW6fdvmvclHchzqgGLPIAfPWI81XlolXaf+4lu5HtOQUOJXsbuhSn83ZOAAZjalbqul/kKaBnCb4C9igOG/YnkFciAxkYOWoe4bmeE1LYPZG10JAbt3sZGfrrUnt1l7ntQyLJAGfRrmbgVC4fZQIPDp+UA/Gt+zKc80kcc/hqjnA6CebLn/HLG/Q2XabOKejwxG5QQSYNdGxeXUzCYWJcgvSFV8pH616n8BJTX599H423HCk4/s1hYrBU65PM/99eVpuFaXpCqWp1iSkKb0YT2UNswC1bY6GrF4KOu4Qb18JW4N7pLKHYoKQAdhBe8mSWTeWOAusbRhZno5WTjOcGKustqZU+vYY/NtVPYq4shBj3X7Ps4y4z67EROej/WGHImg3vrx6mImJhMTReGYlfqkqiV7JKwwe3RDtArTv4YygYPk/Gv5z3DalrdBdq2YlaIYseU7kB+miwAOl0arhEuXtaXRWblavuyj1msR9fqzIBZdY565UUIR0Ng8zZtIDAARfj5b+6/58DhkwowBE3XkOSoRzzyzUKNkX9WR0p9RgfNALUj6VSDpK0HSJ710WZoJZ4Ijim0XXDJWXrzdArFWTf5jiIHVi3DMF4gTpyr1/OUAht3Bxmjgyna1ag1ufTFe1vAF0fqNZkqy3nwOJFmtmnha1ESSugJ3qfddRgm1A2rmBwejhi1xk5Remy7i3nBBGl01Ib5+AcIFT+A2PgDtEWiFgomULQlB9kkdn3QoilctAoCpTk/UzJnulBZOxJl9MwF8FX2LbsofYcLtP+FHR8xeImZnvjWwK98KdL2/CV1XCnRNpGwr39M9uCLBWUaz/5bV5CNcmgZzjGUGt2EGBFKJxZroUernhC8yL8SOVGBesCrwNZkW0VVG/LxZZjTbaw402JYkPdvQ2QR2pJHEFRuft5klYzvqvDCxI8sEit0TOZNSVDZjHNvLcex/qT6Of1PL6jBN69Wr1kJqcz0kOdKlqEY7JCGuXJhAYbkumvzGOGmBdBoCpVyZIoccd9+8bSAG7Yk7Yt6W/gTCZifgQ/pESoi9HBEAnNfgCnsqla/Iw5pJwJ2JJ8lNzuXT1OCaqPr7twm8gXbyorGAe4IaXCnEXAMRoAjtRpdjMJNHU3LwOdwEOnfYaVYvXCcK+JVAI+CUASqrvkL9fMXN693L9ec69fH3MB+1wr1sjfKOOm0Lo5BBqcNS8meLZKU7C2wPVKsVVYzbCE+XmJO+e0UVKXi8bzWatkaWqI58SZY9k/KhY3ndu4vdf8l0SATnIri7CP5aeClAsFIlOvmTmBJv4hfq/u+/EtNAwm8vI4tw6a2e/rYYW38nw4M8jINrzuN5Q+5cypOwGGY3uFOb9bGmlMWnaw6KDaFCvPOSv+hdlpbgH1x+A8K0cw+XwemXpNF9jzk87HX1ZQy7TN7tRUxAVXy9Mu7CFUxVK+4a8jar3RsI65DeSPSDeXiWFADddLFgHiagcPW9PXqpaTE5sVuqn32nxbxhFly4F1pWKtx0o8A6FCg6rD4BCWYRrSVlqhN2FX+0+WruevVWtfl8FWC+yNbMxXhuGSPlW91CycIBm5tCuvUSjL+YyFgPrFXqkBVyAX0m7vmbTynUBLU5pb1a+2o5pXdqU1qg3rZZn9LJ2pSOlFM6Zgwx22uY1dPUj97hEDP58Oc5uvEtkHElFWJi1EXAaUK4u/LMHrIWzgzwbbKa2jK7MTmOMfrkJHNFMVpL+tNPzlrD/u8XYlI0wZtcdEDGtvBvo8k=
*/