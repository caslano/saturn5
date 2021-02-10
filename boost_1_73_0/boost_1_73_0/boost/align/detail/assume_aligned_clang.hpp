/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP

#if __has_builtin(__builtin_assume_aligned)
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))
#else
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n)
#endif

#endif

/* assume_aligned_clang.hpp
J+Vx1VjUa8CmqKSihQiA56+Onj7e/8KG8GoYCbAcUFVi/osehRDDQpMadv54P63rZxj0POjWGvfVUJ+OFYtg75J7QNrl6SwqccPwx3ewhd5Lu1ruhfyIT4RvVGDeytSuJoR0HVR6hOLtBWlh+5iVjQ+y/UePht41edsrehq/cR+Ysb/UnILyj9XajLjukFEPtRu7fTfMg6SznVKlVamNlfhUxDPPejxQWalojiREPTMgrl/eGv/S9iiE9WvVaQaxAR5ouhrby5A0jwX71rWuRLA3WC3injEiZvJqjMIum2Qz1m7Py7fsQzqvk4RBJeMG063M2jsQvZK4oUQRdsLsCp0NtNNqQcGr3qpDno75wzwY1V42MUafGngg0utszO7K784uPwAZYQ05Pvd2cyiKoimyLlASYfdHjxyLv8je1tUw2qliJp5QPNT0sygv3sAgiqAOQOsnnfuzFMLcT/XYodcqa6jqrSypuDqwCE6CVCPcAcgn2eXRWXbx57c0PhZGx4XLeIPZwkalbRNPWB1fprX7hMo0u+DocVIhp4rMCQQupk8aVdXPRghITTRaHTmsxqzqA64plqyl+KkI5sBQ1hUKwRrhu5wu3+R3Rwrk84KKNxUMawysKqawvlQM84L8CzcZUhArquGqHX+c
*/