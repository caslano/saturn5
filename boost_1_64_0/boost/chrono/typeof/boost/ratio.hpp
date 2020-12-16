//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 20010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the unique_threader/unique_joiner design from of Kevlin Henney (n1883)
//
// See http://www.boost.org/libs/chrono for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CHRONO_TYPEOF_RATIO_HPP
#define BOOST_CHRONO_TYPEOF_RATIO_HPP

#include <boost/ratio/ratio.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::ratio, (boost::intmax_t)(boost::intmax_t))

#endif

/* ratio.hpp
MHwHp2eOaCdwCtgVLDLjB68Ce4ArwZ5sV5PAjWBv8G6wD/gE2Bd8GuwPbgcHgB+BA8Fj4CDwO3Aw+AM4FDTbo2FgAjjCTAc4GuwIjgG7gGPBvuBZ4FBwIjgSPJvta4WTY7bUCpjXZz4X1rF9betAOZvpAAvBZLDcTA+43EwPeC04BNwAjgafBseAL4JjwV3gOPA98CzwQ3A8+DE4AWxopguMMdMFxoLngIngNLAjeB7YG5wBpoAzwTHgLDAVPB9MBy8As8A5YDGYBi4Cs8Cl4DxwGZgLXgPmgb8GnwTXgolOz9oCZbBvA8vBJ8BLwKfAJeAOcCn4Fng1+A54Lfg32j+h3XxfuA6cAa4GLwCvBy8C14AZYBfQDd4IIozaAN4I3gTeAW4EnwVvB7eDXcFdYAV4BLwTPAreBX4N3g2eBO8BnSjDTWAiuBkcCt4PTgAfBGeDD4EZYDfQDT4GbgT/DG4GHwf/BJr5sw2sBP8CPg3uA18AT4AvgT+CL4P1QnB/gI3BXWAvcDc4HHwTTAHfAi8C94Lp4D4wB3wHdIP7wevBv4E3gs2daNfA92GvAA+CT4MfgK+AH4GHwE9BFSp7EaH99Nj7gUfBseBXYA74DegGj4Prab8Z/B6sAH8w4wd/AreDBs7/OlgfPA6Ggd+D4WAC7psIsDXYEBwGNgZHgtFgDu3zwTjQDTYHrwcTwHV0vwFsCVaAZjndC25kO7RC92lLv73cpz0V6iGouC9/EvfjH8j99Rdwf/2F3F9/MfhH8HLwT+BV4EPgSu67v4H77N/N/fUrub/+Ae6r/wP4HBhlePafbwm+CLYBXwLb0d6T9jJwJ7gY3AVeAb4OLgd3gxvBvWAFuA98GnwH3A6eBF8D3wMRVh0AD4MfgArX/yHYGvwY7A5+DiaBX4BTwcPgTPArMB08Bl5B+9Xgt+Bq8CT4B/B7cCvd/wj+CD4K/gS+Cb4N7gO38zn1gu6XQdvA50Ks7Evl+RVyTYWF4FyufVBs+gWXgIvBy8Al4JUK4bnGwhXgjeCvuMbCCq6V8mvwXfC3XCtlJfgheB14AlwFtjDfB8H24DowCVwPTgU3gLPAm8ELwVtYPr/Rz132OYCJAb5DwlAPTYaD9cEIMAaMBOPAhmBLsLHDF18q42sZIL4YxhfL+JrxuRsHxoPNwRZgAnjIs29VjesN9Ouu1xiAVqPBGVtn4D+5xsC/Y32BwGsLnP7eVJa1BPQ6AhUqXD0BsxfmGEwU9gluDzMUZjqMG+YqmI0wD8HsgKn71f3qfv/5388y/z+rrMB9Btb/N+f//z0G70Scf/oE34t6ca2+rjB/bWIubKPnn5pnts6bdlvmeNJfBxXmGw+llsF7LNE33mMZC831HOfev5MbP+RZb0l9gLRFtIzU80E/jOFc8lquR8t5wkwjdOG+OQ1c09K6h759HvkBB9ejYl7Ew8SZa4vb8yItc66Sa4qVtWBh0/lBvwgZptfzLGN+6GNV8irVdyxgXuX5jtvyRfKkFmt9Ip24XqTTlydc17OMGnl7Hs2qJo+OOKvWlxYJcPfLoxyuvb62sYwn2urMkWrqzJFq6wyPs87gmwbf36dfZ5BGcxzrlOqMd/52Z+410J350QmmoJlSSd3t+YEF8LMx+BfsPqL/toHyhMcSguUJj8dZx8l4NtYf7adpbevPad1T9j2ymRa/NULXcRmkc1F+vcl4cz5RwHyTW67qPcc1kx+SMI2czEvGcZbWizwq9gjnG/j6+8lRz35vco7oFvHTzMk8ZxxzVazYDfWl2Hc5uqhQlY3ekQD3MMOMkDDTYX9A7DHO99VtxpWOlRzDh+qmh4whO5YaHSxlatf07JWwnzsOOpw=
*/