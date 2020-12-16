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
LN+4cXyM7bDew3Nsz3es5yfG6W/1+UmR/Xrc/s90vT9W+Y1obz/Ub37ecXcdstG4t+wx+/N6/e1u/bZ6cpf+edHVzp8xPt84W/u63HhgvM8v5tneeO1Wf7e9WzmE48g/6hcetp1f1i4LbccW9X+K7b5fP5TkOusM/fB8+7/LOKnf+XOW6z/H7Xrtq3CucfNz1nuzcvuD+vs114tvVz7h96ob9RMN+s3JxltJzhMr9Cf6+T3tzi/vDb//Nl45Tf0LP6e7VXk2WP/boixHP9Ln/Kufved7jrvryHzls2+75fzBefFR8xVHGQca117iuF5teeO0G/Xx6dlRrhP1S53OG1ON91L0N/Zvd7PP0c50PLK1h0fs31TjpSv0a8r7rmifJyrXHc5Hs2Icv4D+yueOd1vfunPUpy3qo3axQDve0Gz9T1qfx3u+4TroQft7WP8433lzu/P5h4yHV6ivPi9ZWqxfuUw9utR2mj6g/LZ+1DRG+cxTn55zvMLrLe1yt/PBHu1qlu/5dhhfLnU8b/uj7R3RT5zt8S/tb5N+6jHnlTjtp0w5ztM/KafN6sfe+yxPuW6ynsWzldtK/bnvYSa+ST3y+czGOPt5ls8hw+ugi42rXa/MnKN9h7/zydIOrvD9xsuue3uNR+Y5fj4n3NfpOKiHj45xHMLfk+gvFxTanyXOE7ttd4P2ql7sdH4c3+s8nWv79Y8z7Pfm8PO4s43n3qX+fN3xmm17J9veaP35r5XvAf2X8+F6447Fq23Pt9XfZ9WnOO1hs37e9j6vHd3e5Lho1+Met7/z9atvs3+O07N/Vu+Szf+M8ip3fbbUef0px824csZD9ttx3vc9x9t5jcc0oeva+x379JfnGY8FtPPwdznbtYMj2qnPt283Ttq9Uj870fJdX0a9qJ/e5rruPP2PfnP7Dtt/luV0GX/PctxX6NeU010+x7tnpfN/wPF5IOyP1VfXvVFP6X/D68Tw+2717rD+527n5anGi7lf0A436V+ilO+jruNPdx33I/Von3p1wHm03PXMCvW/QP/zKeOGixz32R7/Pvw8y+cWt3ifcWmh70fWm/95j/c4D2y9SbmplwumqTeT7a9+fvWvLXfMWL9XMF7w/OS5yv0y5bFAu3c+uMv374Ufd56xvXPvc546I3Q8b4/xXfj7m7D9+5xy4pnh7/FcX2rPe523D71G/T/LfCn6Dfs168e2p1L/fYbzs/5w8Vv147vV50L1xPbOGOM4TTL+H7C/yer1WOW7SX3TLg7Y3ke/4TzgfHK17Vl/l+NUr11t0C+lqB9PKF/9zpH52mWL9qze3OE8d+S8MeqB88BO49t91vtb2+9zpAcTjce1/1z1YcMDxhfGt7fvdZ18rfb3WuMJ1wMXvTe8XlGP36IdWE6UerP6bdqPz50OaJ/jPug64QXLcR6evMr0w+rt15TDc943znjPclfMt/+71BPj8Hz9woJdjpv6NcPvPWaHn/vNUo+itb97lP96592XHa/vq9cZxhnner004HMA/fs01/+XGC/u185muj50vJdeYzseV276mahU/dMe49CnHU/jjYnVzmvOV+ufsNxJxge3G09c7zwS/p6wxOtf1t9Z33n6tdk9tvt89fk1+rmbvV6ufxjyeIX+pEM/eJlxxEet9wHbXWf/z9bujet2veh4bIoy7g/HM/qJ1farzHL1c7d/0zgn/J1MnPG447S4yeN9ltfuOm2p8+aFlrfd+UY7nj9RPTtNf1Ko/Me6XnFdufud6kn4u9Mvhf2cenuO41sTZXsdz8362fc67uHnUJPUqzL96FjbuUr/3+M6+3Xqv/NW/uXK80n13/noauOpjbZ74h3GSef6HNE=
*/