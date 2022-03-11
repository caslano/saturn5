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