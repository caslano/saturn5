//  (C) Copyright Jeremy Siek 2004
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STRINGTOK_HPP
#define BOOST_STRINGTOK_HPP

/*
 * stringtok.hpp -- Breaks a string into tokens.  This is an example for lib3.
 *
 * Template function looks like this:
 *
 *    template <typename Container>
 *    void stringtok (Container &l,
 *                    string const &s,
 *                    char const * const ws = " \t\n");
 *
 * A nondestructive version of strtok() that handles its own memory and can
 * be broken up by any character(s).  Does all the work at once rather than
 * in an invocation loop like strtok() requires.
 *
 * Container is any type that supports push_back(a_string), although using
 * list<string> and deque<string> are indicated due to their O(1) push_back.
 * (I prefer deque<> because op[]/at() is available as well.)  The first
 * parameter references an existing Container.
 *
 * s is the string to be tokenized.  From the parameter declaration, it can
 * be seen that s is not affected.  Since references-to-const may refer to
 * temporaries, you could use stringtok(some_container, readline("")) when
 * using the GNU readline library.
 *
 * The final parameter is an array of characters that serve as whitespace.
 * Whitespace characters default to one or more of tab, space, and newline,
 * in any combination.
 *
 * 'l' need not be empty on entry.  On return, 'l' will have the token
 * strings appended.
 *
 *
 * [Example:
 *       list<string>       ls;
 *       stringtok (ls, " this  \t is\t\n  a test  ");
 *       for (list<string>::const_iterator i = ls.begin();
 *            i != ls.end(); ++i)
 *       {
 *            cerr << ':' << (*i) << ":\n";
 *       }
 *
 *  would print
 *       :this:
 *       :is:
 *       :a:
 *       :test:
 * -end example]
 *
 * pedwards@jaj.com  May 1999
 */

#include <string>
#include <cstring> // for strchr

/*****************************************************************
 * This is the only part of the implementation that I don't like.
 * It can probably be improved upon by the reader...
 */

inline bool isws(char c, char const* const wstr)
{
    using namespace std;
    return (strchr(wstr, c) != NULL);
}

namespace boost
{

/*****************************************************************
 * Simplistic and quite Standard, but a bit slow.  This should be
 * templatized on basic_string instead, or on a more generic StringT
 * that just happens to support ::size_type, .substr(), and so on.
 * I had hoped that "whitespace" would be a trait, but it isn't, so
 * the user must supply it.  Enh, this lets them break up strings on
 * different things easier than traits would anyhow.
 */
template < typename Container >
void stringtok(
    Container& l, std::string const& s, char const* const ws = " \t\n")
{
    typedef std::string::size_type size_type;
    const size_type S = s.size();
    size_type i = 0;

    while (i < S)
    {
        // eat leading whitespace
        while ((i < S) && (isws(s[i], ws)))
            ++i;
        if (i == S)
            return; // nothing left but WS

        // find end of word
        size_type j = i + 1;
        while ((j < S) && (!isws(s[j], ws)))
            ++j;

        // add word
        l.push_back(s.substr(i, j - i));

        // set up for next loop
        i = j + 1;
    }
}

} // namespace boost

#endif // BOOST_STRINGTOK_HPP

/* stringtok.hpp
RsEQPwKjn+UMtS96n6dUMNLuT7HAP6ktdCSOqjkatz/zVe2lJXiyZn12A3AvOLlq/siFZ1B85a/GPvG56zqKtZgDHxE9iqIJIPR6HMW+OUO8gAddbbi5wLxPPgFEtwVYEaxLiufZ4VtXTIklSllPXe7JregWmuKUVic0m/BmnGxatJiBUWn+KwrCagUmrq62U2vOrGAx1xGNYZJOpt1x//sBbpx4RUgH7xHoxInXufCvm/CxA19NaoQluivy+M3z17vfqxsjoWELUA22AtV8FTedTOmVdvtV++RneK6LR7DZLm3TP6bKEl8paepk4JnqfHHwW68xWGv87d2HRxs3K62gVqOSBt04RsQVDO6FB2vWVoShvzBEAX0W4wAEH2CpmyjSmaGcYdjgypID9Qi0xNyT5AVe/OsHPnUkMwElCrryJdDKYWHnakakdN6hoKWZq88RNmEU9Nf/7/S0oJaP/52m96eXy4WLLWGQlUNjx/a+TJVdmddu46+42zVVi3oQvgz3wVfXQSkU5a3DW2es1SUafN+LpdYtadyBgrJd4XItXAz9StN/73dge62uAqNcrVl+ASsjYe6tJCCFkPznQiLGXAEWLigYcnfn9a5tyqcbPBbUrh6t5Wz5qrJbw5AfvyBr/qecqFFMbp6Z
*/