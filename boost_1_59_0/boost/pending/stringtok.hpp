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
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
*/