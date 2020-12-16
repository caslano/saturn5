///////////////////////////////////////////////////////////////////////////////
// weight.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_VARIATES_COVARIATE_HPP_EAN_03_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_VARIATES_COVARIATE_HPP_EAN_03_11_2005

#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

BOOST_PARAMETER_KEYWORD(tag, covariate1)
BOOST_PARAMETER_KEYWORD(tag, covariate2)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(covariate1)
BOOST_ACCUMULATORS_IGNORE_GLOBAL(covariate2)

}} // namespace boost::accumulators

#endif

/* covariate.hpp
7cVM062lv3FKIAxVv2rs96O+TwW90NDBWTvUalNRcU8HQ8yiw+DE2HoSjukPHg0IknPdIy9u/ZOTSQkzRzTuPT8WJcwFo7uscd/O/VfemoO4vwkc6MD3WX09hCvFewp2fUkDZdtYUXlp67nZkEevJW4jMmkR3ClVP5Y65l2POrIjwIexGOB0XdX1OgD/l0IqhilM44qUhAT790Hy3adFxR1M4+8IoO1P7nPyhbEYjofRfm3vD2vl/7uQ8ZNsdh3uf1WwpsuS+3/FEi49QJZwCpnCfaLVeZZ+doI6/ytSVbvJst4JaIlIiRIGtFUUAdl9dUKbQnbs/7vQPCi96OmeCUJ/FdnggL9y4+suF9/qMpw+2b32GF4S+2TxcSmOTzN7AUT/AcJVjk5tL4SeRoBcFDeeXjy9eGbhmYVnNp7ZeObimYtnPp75eBbiWYhnMZ7FeKp4qniOxnM0nhPxnIjnZDwn4zkVz6l4TsNzGp6z8IQvydvnMbeZTw+EKiVUKaFFElokocUSWiyhJRJaIqHHJfS4hJ6S0FMSqpJQlYSqJVQtoToJ0eNgafZAP/EKtPBM7k2+MkbOmDNDT/ZEfgvE6QaYTo7cHTMlnd1GHgmIHwICV8cUllquaGqUF9xydcyzyXL30vCe5tUxdzAmLNMT9SynTHvoRCaPxIJqRnAoNaOinSqDonoQV2KP4nKU/0Cp2pAg4//qTEg/R37egUovM35FS5BLY5LpBpVwYk1Lfqcixs7v7GGkIiNl7iXEY2qnIHdTINy2Phb8kpbwj3cG/1RL+KrO4Be1hF/cITxu7mldnxRi4pKY3wspZavv2bbvue18L7Z9V9v5Ps32fVY730fbvk9s5/tk2/ep9L1V/ee1rH9l2/q3XZ/fVmDaSFQYd/x9ciX0zyJqkf7S/t0xtZUL/9Bqx0Fe9if8vPX9yd6W4bvZzUFHIx3fl8j3xzv6/pR8r+ro+yL5vriD72PcrcoHHS/IcOLhbIRzbeHiYMv5axrCs2zh0QhPtIUnIzw1Hr57npSnksrTkf1bf/N+pknY94HLxP2/7t99WO9nsvnnMM7/JWtYVPM+/zPaE1XwKjJoqviWaIUq3YhPvAJh1eNvoH372bS0+ttwXtSehUXtry+XRe0PaVH7kG1Re+RxxlqxhcyQXHO5ZSULUUcxYcwQBZ0XepEmML7vOdF0QFzRhzAy+hmyzS1AbrKni+nP9mKdIo3XRTON+9XwHaS9SX/3m93m2up0turCUhHpP58ipZ1tlZa9jCj6VEbWpKjhiW4o1odzwxPBDKZ5qQnId4c+kw/4/W5qGnJcFKsXiQNOV0/QR5VyaicLYlAt1PpfJCnln9yXlaho7jy3Fq05+O/G+q9fXH95DNY6bfx/275/gPZto/9s+36Mp236L/vGv3/Zre33N2zfq4bbvwfprizyhYVZ63xQMoLuceRhS7zqP2gkNG6F9Bd8TCrmBeQauB5hIrJTyCsKT2eh/YnToYd+DjjfigpPwfoqrCCHq3v3qkUNN2Xwkm4W+RaiZd1aRdZv0Xddauir4TPTSV97wzb4aZqxUbxTTFaRnH8O3LWSCDRBbW/Q8+TngeiHKWpR3cwequfJtUAAjh5V99YHi3bd1J0WuEhqz2lBToNo7rNTmXMjp/d/AeFEDLo6GSdFjTeduvRZYzBskcFw6Q/ju929+u+P5uFwIe2Eh/yZ9Wor3ChwYyn7yXqf+RHu/cMo6Y2EpC75h927Y0HD2Xgv9uG0gjRfpwa1jwLRD1ICzlfwD8slblV9mUKq1HfkVLGYQC4s1e61vDQtMTIoJGdl+bz3N/0t6KE+ojN4v9EbpQHt01GR0wezPIHTSx5lhm8=
*/