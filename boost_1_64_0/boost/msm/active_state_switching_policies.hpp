// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ACTIVE_STATE_SWITCHING_POLICIES_H
#define BOOST_MSM_ACTIVE_STATE_SWITCHING_POLICIES_H

namespace boost { namespace msm
{
// policy classes

// Default: new active state set after the transition (after entry)
struct active_state_switch_after_entry 
{
    static int after_guard(int current_state,int){return current_state;}
    static int after_exit(int current_state,int){return current_state;}
    static int after_action(int current_state,int){return current_state;}
    static int after_entry(int,int next_state){return next_state;}
};

// new state set before the transition starts
struct active_state_switch_before_transition 
{
    static int after_guard(int,int next_state){return next_state;}
    static int after_exit(int,int next_state){return next_state;}
    static int after_action(int,int next_state){return next_state;}
    static int after_entry(int,int next_state){return next_state;}
};

// new state set after exit action completed
struct active_state_switch_after_exit 
{
    static int after_guard(int current_state,int){return current_state;}
    static int after_exit(int,int next_state){return next_state;}
    static int after_action(int,int next_state){return next_state;}
    static int after_entry(int,int next_state){return next_state;}
};

// new state set after transition action completed
struct active_state_switch_after_transition_action 
{
    static int after_guard(int current_state,int){return current_state;}
    static int after_exit(int current_state,int){return current_state;}
    static int after_action(int,int next_state){return next_state;}
    static int after_entry(int,int next_state){return next_state;}
};

} }//boost::msm
#endif //BOOST_MSM_ACTIVE_STATE_SWITCHING_POLICIES_H

/* active_state_switching_policies.hpp
dccKKfd6OpFhpom/z7oMUmaFjvevCQNMUCOxX30ZZZHYB+QSIyyQ+qC4MkWN2MniSofy9jNK7Tj9frwyiZ/gb8p/9/67tIuufXLP8/RbvEeeOYZfoa9P1Gd0kfEd4kGPJWok3qqNFFkmeZLlyFIivE2Z1mn3uJ8q0b22HfSTx26GmWRePKvHeH+X9+hhjshrlUsvo9TY91xj5livMUfsdeLKBJHd+o4JItq9h1GmWW48xXcb1NH9Tvo9TjBPRNuTVIz7tDZPsszIVm18pT6inwIVVuncqU0UWCB2lJxikEnqtB2truSYZZX2V6kfI5Rp0Jbx+ovFh3iH7dDHia6LDTzL9qgSS2kzeSqskn62ODLCNHWSh2sjBeaIHGH77CPHDKFNXMkyS+dz5B0TrNAmxqP0qsMQRf2zFJdvW2yHEaaok9qqrkzRGZMPLBDdaMxQo3uTvN2sDCZZomb52Db1oJ8SSyQSYs4Ys6xSXnC/g+3qwwQr7NqhHszR8nTLM8NKsy83iJEyW+PK9XxGGyLrlMX+tWLFMskDxYohplim9SCvMUyZSIt20Uf1v2Lhcdg25yL60mMfu73eT5F4sD6LXu9U7pDYtay4BvSo/FvWpxRZJP6Y1ygyT+TPji8YYpIqpSXnmMT/6Poow1QIf/L6I8akx3FWGfW8QdvvXUclz8DD7oHMIonf2T6jzBOtuh8as4SH3AtrUdmUWSX9G9sh6Z5iXQzR+4A60THnPcaYY5XOH3ufIvPEfqLODFBkgXCfddlPgXla77UuC3e5TyKtd4spBWZpvUecmWbpDvG807EYfdRoTGrrjZalTuImdWOUGjM3e/8ryiLxVffJp8g8LRcrmx7yLBAf016GmWWV9kvEhzHmWKHjUu1lnEUSX7MeI8wS8upJPyXqtH9dWYyxQOwyOcAAJWokL1cWeeaJFsSDLFMs03aFdjDKHJErjREGKLFE8ir9zQgVIkX9QZYykautQ5YpVuj4hueUCd9ULlmmWGHnuDKYpEHPNWJJ4lvazihzxL7tPnTkmGGVjgnLskzbd6xLkRr7r9XfVElc5zkFlkiXxJlJVtl1vTqxQu8N+usdyibLJHXa3ik+5Jglsk/59DFOlcS7rMcQUzRIv1vZjLNE63tshwLxbvEkxxzR93pOgUUS77M9crS839/kmKd1v3iQZ57EB6xLngqrdHxQ2ZSo0X6yspmkRqrHOhSZJ3qK3KWfIg1Sp2oj4yzRepoYUaBOslfcydP6Ye8xyQq7PiJXmCferyyylFgk9lFtYIhJ2j+mfswTPi43GKZCdEDukKNK2yfMVcywys5P2jYVkp+yHcapkxmUYywQPm18MMY8qbO0lxlWXuv5serGwOv08W7bZYbBTNTxhHsqv9x9iZvc3ztFhn3U3Ss4uUub3PM8drb2pFyrc2/mxhGW2xn1HbKnutdfM5a+k8dC897M3p/3frx5X233FO91n+xh9xCvUJpUT8uV1KnWvDeKewLOux/cXvcXXznDa/f7Dv7PfI/4dO1nzrXjNq+PfUgZ7CbJpOUqXh9nkC72Plt9vBfvsxyDTDLjtSWPVfd7H7S9Akl2neScrOJ86afOJRlhmiVaXIdrp4t+y+VZplsspjuUQ9J94few/E6P2jnAuLZ22faMZWPHKEsb+nxPaDeNo8XyVe6R596IVSLupTh7pPvnuSdd6mH3GbJspuq+PtbNaN9+hhlS5gT93p85yX0EiLoXRJoJ93hP2XbBvcnz4tZDJxPiH31f1HhzD+rvipN1UrZVcI1xxj1xxr3eMilmHkfIWHZ/0j0rGXffxCHq6talXvmVp7pnv3v5tbsvIPuIL7gPkcd9lttJzN9DScs=
*/