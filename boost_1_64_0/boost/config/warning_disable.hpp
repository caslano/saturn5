//  Copyright John Maddock 2008
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  This file exists to turn off some overly-pedantic warning emitted
//  by certain compilers.  You should include this header only in:
//
//  * A test case, before any other headers, or,
//  * A library source file before any other headers.
//
//  IT SHOULD NOT BE INCLUDED BY ANY BOOST HEADER.
//
//  YOU SHOULD NOT INCLUDE IT IF YOU CAN REASONABLY FIX THE WARNING.
//
//  The only warnings disabled here are those that are:
//
//  * Quite unreasonably pedantic.
//  * Generally only emitted by a single compiler.
//  * Can't easily be fixed: for example if the vendors own std lib 
//    code emits these warnings!
//
//  Note that THIS HEADER MUST NOT INCLUDE ANY OTHER HEADERS:
//  not even std library ones!  Doing so may turn the warning
//  off too late to be of any use.  For example the VC++ C4996
//  warning can be emitted from <iosfwd> if that header is included
//  before or by this one :-(
//

#ifndef BOOST_CONFIG_WARNING_DISABLE_HPP
#define BOOST_CONFIG_WARNING_DISABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1400) 
   // Error 'function': was declared deprecated
   // http://msdn2.microsoft.com/en-us/library/ttcz0bys(VS.80).aspx
   // This error is emitted when you use some perfectly conforming
   // std lib functions in a perfectly correct way, and also by
   // some of Microsoft's own std lib code !
#  pragma warning(disable:4996)
#endif
#if defined(__INTEL_COMPILER) || defined(__ICL)
   // As above: gives warning when a "deprecated"
   // std library function is encountered.
#  pragma warning(disable:1786)
#endif

#endif // BOOST_CONFIG_WARNING_DISABLE_HPP

/* warning_disable.hpp
FATRuW0n4y1h/W1VtnmPXLYWx7xff2vAO9fibb27DXDYWrytF7sYVithfhFvCzjYzbXaMOFcuR1wwH7uMGevmbfcHjgj55U4c6D59NDdSmaV89bxO1ydq+dIyL8M/FXMc038P39H5I/ojjEFGIZ/p/8qw+bGV/4rv04F8i/eWfFXMZfGeeFdNB/3+4bfR+68q83BWSiO9/8a5kC8EP/y3SiOYSC+fw/go/cNt9yd4Khbz9Ve057Rnm4XVzhmnvtE9zwNdpTNns5dNXfswmgu2apH3RLHYzwNs+eUy4bbB+6oU1VgjrXcs8AdfXrG9J5DbvcpKN0n61vz0CivCqcKVm+jS88J9pI5wRtHx5P1PXdFv5pXl4EekO4zbV/P+KxMyFEQ8tXR/0g+7rsBH8f8/8avhxJM8xPG/xtfDS1gcI6Esfva/01mqXdy0IZx6Wp8rd7O179vuYrMwOwNtvzZ6yr+quq63se8PvJHtSPspz99Q8MFVI/dkz21DaPuwk7Nw6CCbX/mRsjtndR7NXSt8PLtBoe1Qh0S9nd33qGwVZzZGP6l/86HzgX7+I/c7L/y8TwGfSewNpaKpEr9NPBXf68e2phlp/4NY25SQb8JEaFztDWA1XOoZZXHp9g9t7WAyaCoL1yBILHZso5hcM0KcJRdv0HjzcUrAFH2yxwzwji/f/nGThxjiPO7ceAdKZIiwBgym+CbEdeaeNrHrw24nodAKAT7J2D1/AMxnJtc3mJhGDPytsKcIeH9obllWsZj1tpK5rFTJUHyv5fx+PU37RyjIR1Wrydhd7HGrs2xQagsHI7pO4/X4Ri0U6wvr+/QqFvhHrqnOL+um6uHX+wrrlk/ggd9l77pTPV+fkM3H6ow5d1nI/Bw3cTJhPfPTZoHAdo8UrZP2Ay84XtfbF/8uppj3elibw62Ase+G9bq+Nb1Gc7ujmE7uCFwdP20o0zXw9uAp+ujzcM9PPCPDLyr72XO3lhxVrFHKW6ieVFQBoedfLJ0iuAITrzQRvWZWe6XKXZLP3W9Qvy3oUyMoY5zTAf4N0qjIPd98d+GN9HaY7/IdDiiCss8L/JEdAxHvZPtvMC26/5PS4+Xx1GVlMVIPb2FTj0757ieMParwM0yTJOtR09qbD0x1eNKEQZOlQWxN0qPHvaNGtTTt+JTxUHoRqns0qPOxHFeZsfn5VZ8SicvZBJ05vMyy2YenwuWHrdy3azwihF67GzGunN5jte/wkmdNEndUenCY1UxJoyOrY+iOiJR+FHhlfHIvMETHKJDUB1uKYLELYrQTcTI7VBMDeqYZTpyEXm5W8gqFyO2cYl9bWHy9VksLY5wpR9nYC3kv2wFa0WYr+dZXJR4ngaF7wcj9UBkLBvll5gOV1Re5skki4V9zNUITuJdbypXiqosq9SNPUF3I+x3wmMnuU2yyK+KMhdsk8K2jb+dyriZyMooSRJXjDxB0/Jou53JuyIqvSpzZSXsLSvLnoukcgcrJSX9vBTmghbaCTD3yR/BwgmF74AnAccTXUd4Oo6mHJ/MZAshA9+RSVaIqxyl2nYO38h0BML13MABsxcdR/W2P4ALTDYSaeSWRZKUovN4nvs/+CmTzUUYZlmSpp4YeZUL+wdM/9g81VGJyJdl5XkjwjfZYNmDmLfqcZqlbiQdYV2p02LTaA+CykErLp0s8CPRznX5WwpJ+VJU0g/CFPjsZh63xzDLwyjjMPSCIgYZlqemPM5YaQnLzAv8sBJTYHeyyVT9qgHrocnLs0y2EJEs/SCBekh9Lk7Nw1xdeZOA2GJeGh0fYDpS4ftlFrh+yHWgGQXdbHnf9E8rHp4fqbaehaJZGrY2PgbDNj5wfD7F+/w=
*/