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
qgQ0KmJVZkd7bEu1bIF7GhHrC4Uqi1qKikD7w5KiohwY7GRpKfbgIGV4OIUTcw7PVrAe67rHkSneenmff19etCYL2tudr9z/Rw6KgZrvef4lZVqcHIkqKizKlspbd5J+H7tP/zIhRmUUYA+azCx4c/P48/PRIRkHQXaqQL25EhX3uKHZD8YrVgJCezu6xcXXQoI5VC9FVmf4V+YEJ+fnF6bl5PyMNPUehgrmMwbRVQtY1G2xjw4SX8ZkCFSzC0s0bHw0nsKXv0Go6Tnk6hpmfddlVB4mjRDY3Ix1knxa+3AtfnRKKxY+/1zcHgAualmXe2xrbGtrLSPhbm+vAgtKExi3c3DVvmHK51md1HrvEuhzZ2xGV307zvOipTXMT+N651ogasn+MxV3tV76dF7+Mc0U6a5YjHYiLVUS+UuTJvEGn1oJa28rN4uE98YZ7Cm0EhBDnW0ovgwhanpQNODho6Pj/jxpQBB1KZSr1CZfkCi4UtKBmSM+p+oXZWdHsZY0ZN7NFXz7yXngPqfhst2RHENsfM77ij1TvBcPTxlv7pNqUB17UcebglzT1MSMsoR+6xD5Xbpw9hUikxopDqCO3cGv0W8Q6ojeqXLFp0emR4MaU4+NFz0nezjXLNSXHHCMjn7dEE3/2pM3M1FZWlp+7+0FPt1yQfYF5aj2FPNkH9AMHx+k1HtxUlHq4dXXHGh/SKjJu4AOKfha6f98
*/