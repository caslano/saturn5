
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/continuation_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/continuation_winfib.hpp>
#else
#include <boost/context/continuation_fcontext.hpp>
#endif

/* continuation.hpp
RR3osXOUm4XIYtuPXMtybql8C6k9y7AHK0tf4hsM4Qji9K5ZAGw9slwNg3f1s8TZp6gjcudiI2RZ6qtBQzZh6wem6pn+goTNhc6FnYC+AjkWNKyzE6YE648UqWWvyNtr3Ox1Cgj1nK4v0smkiP+NYQWbNdIb9vgOhIxaOM0LPYW5W95Bi7GrB6z4TzuFKRI44dA97MF1QXk7zbaGJvvMub5RqQIYfT9koIKdgho/FmaOlgDXCt6hs5MxgE50Z+eI+2PhZrSibmkID7cbFMfI5Bcxnt2LbJYGDB+jJvrjfLAEJOTuL7msDCJSAtA9MxJHFx6ZwjtpTFnUNeFu6jkvWmutkU8BkPymtJE8qPvtmFz6YWKeX36hOWjDZMMDJDefehar7eRbXIE2/FsE3pb+NleJKtkh1YUrTwdzppl+1WT35gDSYlYC+IM+4KK96PiNk0VspvW7LjSWZWwMjwbkMcMAO561qTLsKl+bKeDRJq0SMaphz5R9g1ga37YfJc8PUdcKBpYQFNVoUeDXctrHI0H5oQFXHuJXedmTlTQAJ1VTKs1uI6ePoIgycQ==
*/